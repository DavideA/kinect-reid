#include "Engine.h"
#include <fstream>
#include <thread>
#include <direct.h>

using namespace std;
using namespace cv;


acquisition_type Engine::m_acqType = KINECT_ACQUISITION;
Ptr<Acquisition> Engine::acquisition = nullptr;
unsigned Engine::frameCounter = 0;
unsigned Engine::nSkeletons = 0;
Ptr<ModelExtractor> Engine::extractor = new ModelExtractor();
vector<Player> Engine::playersOnScene = vector<Player>();
PlayerDatabase Engine::playersDatabase;
int Engine::lastId = -1;
int Engine::guessedId = -1;
Player Engine::lastPlayer;
Settings Engine::settings = Settings();
string Engine::_status = "";
bool Engine::lastPlayerIdentificated = false;
unsigned Engine::tp = 0;
unsigned Engine::fp = 0;
unsigned Engine::tn = 0;
unsigned Engine::fn = 0;
bool Engine::_updateTable = false;


Engine::Engine(HINSTANCE hInstance, int nCmdShow){

	InitSettings();
	acquisition_type acqType = settings.acqType;

	if (settings.recordMode){
		if (acqType == FILE_ACQUISITION)
			exit(2);

		ostringstream rmFolder;
		rmFolder << "rm -r " << settings.saveFolder;
		system(rmFolder.str().c_str());

		_mkdir(settings.saveFolder.c_str());
	}

	if (acqType == KINECT_ACQUISITION){
		acquisition = new KinectAcquisition();
	}
	else if (acqType == FILE_ACQUISITION){
		acquisition = new FileAcquisition(settings.dataFolder);
	}
	else{
		cout << "Error: seems like someone should develop another acquisition method here...\n";
	}
	
}


Engine::~Engine(){

}
void CALLBACK Engine::Update(Frame& f, string& status, PlayerDatabase& pdb, bool& updateTable){
	frameCounter++;

	Frame currFrame = acquisition->GetNextFrame();

	if (currFrame.RGB.empty() || currFrame.depth.empty()){
		Uninitialize();
		exit(1);
	}

	if (settings.recordMode){
		SaveFrame(currFrame);

		UpdateStatusBar("Recording into" + settings.saveFolder);
	}
	else{

		thread t1(UpdatePlayersAndTrigger, currFrame);
		t1.join();

		PlotLabels(currFrame);

	}
	f = currFrame;
	status = _status;
	pdb = playersDatabase;
	updateTable = _updateTable;

	_updateTable = false;
}

void Engine::SaveFrame(Frame& currFrame){


	stringstream ssRGB, ssDepth, ssSkel, ssPlayer;
	ssRGB << settings.saveFolder << "/frame" << frameCounter << "_RGB.jpg";
	ssDepth << settings.saveFolder << "/frame" << frameCounter << "_Depth.jpg";
	ssPlayer << settings.saveFolder << "/frame" << frameCounter << "_PlayerIdxs.png";
	ssSkel << settings.saveFolder << "/frame" << frameCounter << "_skeletons.bin";

	vector<int> compParams;
	compParams.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compParams.push_back(0);

	imwrite(ssRGB.str(), currFrame.RGB);
	imwrite(ssDepth.str(), currFrame.depth);
	imwrite(ssPlayer.str(), currFrame.playerIdx, compParams);

	ofstream out_skel(ssSkel.str(), ios::binary);
	out_skel.write((const char*)&currFrame.skeletonFrame, sizeof(NUI_SKELETON_FRAME));
	out_skel.close();
}

unsigned CountNonZero(NUI_SKELETON_DATA *skeletons){
	unsigned ret = 0;
	for (unsigned i = 0; i < 6; ++i){
		if ((skeletons + i)->eTrackingState == NUI_SKELETON_TRACKED){
			ret++;
		}
	}
	return ret;
}


void Engine::UpdatePlayersAndTrigger(Frame currFrame){

	NUI_SKELETON_DATA *skeletons = currFrame.skeletonFrame.SkeletonData;

	for (unsigned i = 0; i < NUI_SKELETON_COUNT; ++i){
		unsigned id = (skeletons + i)->dwTrackingID;
		if ((skeletons+i)->eTrackingState==NUI_SKELETON_POSITION_TRACKED){
			//search the position of top left pixel
			bool found=false;
			Point2d posLabel;
			for (int r = 0; r < currFrame.playerIdx.rows && !found; ++r){
				for (int c = 0; c < currFrame.playerIdx.cols && !found; ++c){
					if (currFrame.playerIdx.at<char>(r, c) == i + 1){
						found = true;
						posLabel.x = c;
						posLabel.y = r;
					}
				}
			}
			//

			found = false;
			for (unsigned j = 0; j < playersOnScene.size() && !found; ++j){
				Player& p = playersOnScene[j];

				if (p.skeleton_index == i){
					found = true;
					p.frameCounter = frameCounter;
					p.labelPosition = posLabel;
					if ((p.frameCounter - p.enterFrame) == 20 && !p.checked){
						ostringstream oss;
						oss << "New player! Number of players actually on scene: " << playersOnScene.size() << endl;
						UpdateStatusBar(oss.str());

						ModelMap models = extractor->EvalModels(currFrame, settings.nBins);
						p.checked = true;
						p.models.push_back(models.find(id)->second);

						lastId = id;
						lastPlayer = p;
						//check se esiste il modello nel db
						CompareAll(p);
					}
				}
			}

			if (!found){
				Player newPlayer;
				newPlayer.skeleton_index = i;
				newPlayer.enterFrame = frameCounter;
				newPlayer.frameCounter = frameCounter;
				newPlayer.checked = false;
				newPlayer.label = "Unknown";
				newPlayer.labelPosition = posLabel;

				playersOnScene.push_back(newPlayer);
			}

		}
	}

	RemovePlayers();
}

void Engine::RemovePlayers(){
	vector<Player> players;
	for (unsigned i = 0; i < playersOnScene.size(); ++i){
		Player p = playersOnScene[i];
		if ((frameCounter - p.frameCounter) < 5){
			players.push_back(p);
		}
	}

	playersOnScene = players;
}

void applyMask(Mat1f& mat, const Mat1b& mask){
	Mat1f old = mat.clone();
	mat = Mat1f(1, countNonZero(mask));

	unsigned mat_counter = 0;
	for (int i = 0; i < mask.cols; ++i){
		if (mask.at<char>(i) != 0){
			mat.at<float>(mat_counter) = old.at<float>(i);
			++mat_counter;
		}
	}
}

double Engine::CompareModels(Model m1, Model m2){
	double distance = 0;

	Mat1f totalRed1, totalGreen1, totalBlue1;
	Mat1f totalRed2, totalGreen2, totalBlue2;

	int normMethod;
	int distanceMethod;

	for (unsigned i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i){

		//extract joint histograms and normalize them


		if (settings.jointNormalization == Method::L1) normMethod = NORM_L1;
		else if (settings.jointNormalization == Method::L2) normMethod = NORM_L2;
		else if (settings.jointNormalization == Method::Linf) normMethod = NORM_INF;

		Mat jointRed1 = m1.model[i].R.clone();
		normalize(jointRed1, jointRed1, 100, 0, normMethod);
		Mat jointRed2 = m2.model[i].R.clone();
		normalize(jointRed2, jointRed2, 100, 0, normMethod);
		Mat jointGreen1 = m1.model[i].G.clone();
		normalize(jointGreen1, jointGreen1, 100, 0, normMethod);
		Mat jointGreen2 = m2.model[i].G.clone();
		normalize(jointGreen2, jointGreen2, 100, 0, normMethod);
		Mat jointBlue1 = m1.model[i].B.clone();
		normalize(jointBlue1, jointBlue1, 100, 0, normMethod);
		Mat jointBlue2 = m2.model[i].B.clone();
		normalize(jointBlue2, jointBlue2, 100, 0, normMethod);
		
		if (i == 0){
			totalRed1 = jointRed1;
			totalGreen1 = jointGreen1;
			totalBlue1 = jointBlue1;
			totalRed2 = jointRed2;
			totalGreen2 = jointGreen2;
			totalBlue2 = jointBlue2;
		}
		else{
			hconcat(totalRed1, jointRed1, totalRed1);
			hconcat(totalGreen1, jointGreen1, totalGreen1);
			hconcat(totalBlue1, jointBlue1, totalBlue1);
			hconcat(totalRed2, jointRed2, totalRed2);
			hconcat(totalGreen2, jointGreen2, totalGreen2);
			hconcat(totalBlue2, jointBlue2, totalBlue2);
		}
	}

	vector<char> suppressedJoints; //giunti segati
	for (unsigned i = 0; i < NUI_SKELETON_POSITION_COUNT;++i){
		if (settings.jointMask[i] == 0){//è da segare
			suppressedJoints.push_back(i);
		}
	}

	Mat1b mask(1,settings.nBins*NUI_SKELETON_POSITION_COUNT,255);

	for (char sj : suppressedJoints){
		for (unsigned i = 0; i < settings.nBins; ++i){
			mask.at<char>(settings.nBins*sj + i) = 0;
		}
	}

	applyMask(totalRed1, mask);
	applyMask(totalRed2, mask);
	applyMask(totalGreen1, mask);
	applyMask(totalGreen2, mask);
	applyMask(totalBlue1, mask);
	applyMask(totalBlue2, mask);

	if (settings.histoNormalization == Method::L1) normMethod = NORM_L1;
	else if (settings.histoNormalization == Method::L2) normMethod = NORM_L2;
	else if (settings.histoNormalization == Method::Linf) normMethod = NORM_INF;

	Mat1f cumulative1 = totalRed1;
	hconcat(cumulative1, totalGreen1, cumulative1);
	hconcat(cumulative1, totalBlue1, cumulative1);
	normalize(cumulative1, cumulative1, 100, 0, normMethod);
	cout << norm(cumulative1, normMethod);

	Mat1f cumulative2 = totalRed2;
	hconcat(cumulative2, totalGreen2, cumulative2);
	hconcat(cumulative2, totalBlue2, cumulative2);
	normalize(cumulative2, cumulative2, 100, 0, normMethod);

	distanceMethod = settings.histoDifference;
	switch (distanceMethod){
	case Method::L1:
		distance = norm(cumulative1, cumulative2, NORM_L1);
		break;
	case Method::L2:
		distance = norm(cumulative1, cumulative2, NORM_L2);
		break;
	case Method::Linf:
		distance = norm(cumulative1, cumulative2, NORM_INF);
		break;
	case Method::BHATTACHARYYA:
		distance = compareHist(cumulative1, cumulative2, CV_COMP_BHATTACHARYYA);
		break;
	case Method::INTERSECTION:
		distance = compareHist(cumulative1, cumulative2, CV_COMP_INTERSECT);
		break;
	case Method::CORRELATION:
		distance = compareHist(cumulative1, cumulative2, CV_COMP_CORREL);
		break;
	case Method::CHISQ:
		distance = compareHist(cumulative1, cumulative2, CV_COMP_CHISQR);
		break;
	}

	return distance;
}

void Engine::CompareAll(Player& newPlayer){
	stringstream ss;
	ss << "logs/Player_entered_at_" << newPlayer.enterFrame << ".txt";
	ofstream out(ss.str());

	vector<idxVal> ivals;

	for (PlayerDatabaseIterator pdIt = playersDatabase.begin(); pdIt != playersDatabase.end(); ++pdIt){
		int id = (pdIt)->first;
		Player p = (pdIt)->second;
		
		out << "Distances from ID-->" << id << ":" << endl;
		for (unsigned i = 0; i < p.models.size(); ++i){
			idxVal pair;
			double distance = CompareModels(newPlayer.models[0], p.models[i]);
			out << distance << endl;

			pair.id = id;
			pair.val = distance;
			ivals.push_back(pair);
		}
	}

	sort(ivals.begin(), ivals.end());
	if (settings.histoDifference == Method::CORRELATION || settings.histoDifference == Method::INTERSECTION){
		//it is a score, not a distance
		reverse(ivals.begin(), ivals.end());
	}

	ostringstream oss;
	if (settings.histoDifference == Method::CORRELATION || settings.histoDifference == Method::INTERSECTION){
			if (ivals.size()>0 && ivals[0].val > settings.thresholds[settings.histoDifference]){ //search for high values
				if (playersDatabase.find(ivals[0].id)->second.label != "Unknown"){
					oss << "I think i already seen you, buddy! Are you " << playersDatabase.find(ivals[0].id)->second.label << "?";
				}
				else{
					oss << "Already seen you, buddy! ID:" << ivals[0].id << endl;
				}
				lastPlayerIdentificated = true;
				guessedId = ivals[0].id;
			}
			else{
				oss << "Sorry mister, i don't know you =(" << endl;
				lastPlayerIdentificated = false;
			}
	}
	else{//Minkowski, Bhattahcaryya, chi-square
		if (ivals.size() > 0 && ivals[0].val < settings.thresholds[settings.histoDifference]){ //search for low values
			if (playersDatabase.find(ivals[0].id)->second.label != "Unknown"){
				oss << "I think i already seen you, buddy! Are you " << playersDatabase.find(ivals[0].id)->second.label << "?";
			}
			else{
				oss << "Already seen you, buddy! ID:" << ivals[0].id << endl;
			}
			lastPlayerIdentificated = true;
			guessedId = ivals[0].id;
		}
		else{
			oss << "Sorry mister, i don't know you =(" << endl;
			lastPlayerIdentificated = false;
		}
	}
	UpdateStatusBar(oss.str());
}

void Engine::InitSettings(){
	ifstream in("settings.ini");

	string line;
	while (getline(in, line)){
		stringstream ss(line);

		string field;
		ss >> field;

		if (field == "Acquisition"){
			string value;
			ss >> value;
			if (value == "KINECT") settings.acqType = acquisition_type::KINECT_ACQUISITION;
			else if (value == "FILE"){
				settings.acqType = acquisition_type::FILE_ACQUISITION;
				ss >> settings.dataFolder;
				settings.dataFolder += "/";
			}
		}
		else if (field == "record"){
			string value;
			ss >> value >> settings.saveFolder;
			if (value == "true") settings.recordMode = true;
			else if (value == "false") settings.recordMode = false;
		}
		else if (field == "distance"){
			string value;
			ss >> value;
			if (value == "L1") settings.histoDifference = Method::L1;
			else if (value == "L2") settings.histoDifference = Method::L2;
			else if (value == "LINF") settings.histoDifference = Method::Linf;
			else if (value == "BHATTACHARYYA") settings.histoDifference = Method::BHATTACHARYYA;
			else if (value == "CORRELATION") settings.histoDifference = Method::CORRELATION;
			else if (value == "INTERSECTION") settings.histoDifference = Method::INTERSECTION;
			else if (value == "CHI-SQUARE") settings.histoDifference = Method::CHISQ;
		}
		else if (field == "jNorm"){
			string value;
			ss >> value;
			if (value == "L1") settings.jointNormalization = Method::L1;
			else if (value == "L2") settings.jointNormalization = Method::L2;
			else if (value == "LINF") settings.jointNormalization = Method::Linf;
		}
		else if (field == "hNorm"){
			string value;
			ss >> value;
			if (value == "L1") settings.histoNormalization = Method::L1;
			else if (value == "L2") settings.histoNormalization = Method::L2;
			else if (value == "LINF") settings.histoNormalization = Method::Linf;
		}
		else if (field == "thresholds"){
			for (unsigned i = 0; i < DISTANCE_MEASURES_COUNT; ++i){
				ss >> settings.thresholds[i];
			}
		}
		else if (field == "binsPerJoints"){
			unsigned char nBins;
			ss >> nBins;
			settings.nBins = nBins-'0';
		}
		else{//reading a joint
			int value;
			ss >> value;
			if (field == "NUI_SKELETON_POSITION_HIP_CENTER") settings.jointMask[NUI_SKELETON_POSITION_HIP_CENTER] = value;
			else if (field == "NUI_SKELETON_POSITION_SPINE") settings.jointMask[NUI_SKELETON_POSITION_SPINE] = value;
			else if (field == "NUI_SKELETON_POSITION_SHOULDER_CENTER") settings.jointMask[NUI_SKELETON_POSITION_SHOULDER_CENTER] = value;
			else if (field == "NUI_SKELETON_POSITION_HEAD") settings.jointMask[NUI_SKELETON_POSITION_HEAD] = value;
			else if (field == "NUI_SKELETON_POSITION_SHOULDER_LEFT") settings.jointMask[NUI_SKELETON_POSITION_SHOULDER_LEFT] = value;
			else if (field == "NUI_SKELETON_POSITION_ELBOW_LEFT") settings.jointMask[NUI_SKELETON_POSITION_ELBOW_LEFT] = value;
			else if (field == "NUI_SKELETON_POSITION_WRIST_LEFT") settings.jointMask[NUI_SKELETON_POSITION_WRIST_LEFT] = value;
			else if (field == "NUI_SKELETON_POSITION_HAND_LEFT") settings.jointMask[NUI_SKELETON_POSITION_HAND_LEFT] = value;
			else if (field == "NUI_SKELETON_POSITION_SHOULDER_RIGHT") settings.jointMask[NUI_SKELETON_POSITION_SHOULDER_RIGHT] = value;
			else if (field == "NUI_SKELETON_POSITION_ELBOW_RIGHT") settings.jointMask[NUI_SKELETON_POSITION_ELBOW_RIGHT] = value;
			else if (field == "NUI_SKELETON_POSITION_WRIST_RIGHT") settings.jointMask[NUI_SKELETON_POSITION_WRIST_RIGHT] = value;
			else if (field == "NUI_SKELETON_POSITION_HAND_RIGHT") settings.jointMask[NUI_SKELETON_POSITION_HAND_RIGHT] = value;
			else if (field == "NUI_SKELETON_POSITION_HIP_LEFT") settings.jointMask[NUI_SKELETON_POSITION_HIP_LEFT] = value;
			else if (field == "NUI_SKELETON_POSITION_KNEE_LEFT") settings.jointMask[NUI_SKELETON_POSITION_KNEE_LEFT] = value;
			else if (field == "NUI_SKELETON_POSITION_ANKLE_LEFT") settings.jointMask[NUI_SKELETON_POSITION_ANKLE_LEFT] = value;
			else if (field == "NUI_SKELETON_POSITION_FOOT_LEFT") settings.jointMask[NUI_SKELETON_POSITION_FOOT_LEFT] = value;
			else if (field == "NUI_SKELETON_POSITION_HIP_RIGHT") settings.jointMask[NUI_SKELETON_POSITION_HIP_RIGHT] = value;
			else if (field == "NUI_SKELETON_POSITION_KNEE_RIGHT") settings.jointMask[NUI_SKELETON_POSITION_KNEE_RIGHT] = value;
			else if (field == "NUI_SKELETON_POSITION_ANKLE_RIGHT") settings.jointMask[NUI_SKELETON_POSITION_ANKLE_RIGHT] = value;
			else if (field == "NUI_SKELETON_POSITION_FOOT_RIGHT") settings.jointMask[NUI_SKELETON_POSITION_FOOT_RIGHT] = value;
		}

	}
}

void Engine::PlotLabels(Frame& currFrame){
	for (Player p : playersOnScene){
		bool found = false;
		for (PlayerDatabaseIterator pdbIt = playersDatabase.begin(); pdbIt != playersDatabase.end() && !found; ++pdbIt){
			if (p.enterFrame == pdbIt->second.enterFrame){
				found = true;
				if (pdbIt->second.label != "Unknown"){ 
					//put the label
					putText(currFrame.RGB, pdbIt->second.label, p.labelPosition, FONT_ITALIC, 0.6, Scalar(0, 150, 0), 2);
				}
				else{
					//put the id
					ostringstream oss;
					oss << pdbIt->first;
					putText(currFrame.RGB, oss.str() , p.labelPosition, FONT_ITALIC, 0.6, Scalar(0, 150, 0), 2);
				}
			}
		}
		if (!found){
			putText(currFrame.RGB, "TODO...", p.labelPosition, FONT_ITALIC, 0.6, Scalar(0, 0, 150), 2);
		}
	}
}

void Engine::SetDistance(Method m){
	settings.histoDifference = m;
	UpdateStatusBar("Histogram distance changed!");
}

void Engine::SetJointNormalization(Method m){
	settings.jointNormalization = m;
	UpdateStatusBar("Joint normalization changed!");
}

void Engine::SetHistoNormalization(Method m){
	settings.histoNormalization = m;
	UpdateStatusBar("Histogram normalization changed!");
}

void Engine::ButtonClicked(bool right){
	if (lastPlayerIdentificated && right){
		tp++;
		playersDatabase.find(guessedId)->second.models.push_back(lastPlayer.models[0]);
		playersDatabase.find(guessedId)->second.enterFrame = lastPlayer.enterFrame;
	}
	else if (lastPlayerIdentificated && !right){
		fp++;
		playersDatabase.insert(pair<int, Player>(lastId, lastPlayer));
	}
	else if (!lastPlayerIdentificated && right){
		tn++;
		playersDatabase.insert(pair<int, Player>(lastId, lastPlayer));
	}
	else if (!lastPlayerIdentificated && !right){
		fn++;
		playersDatabase.insert(pair<int, Player>(lastId, lastPlayer));
	}
	_updateTable = true;
	
	UpdateStatusBar("Feedback achieved, thanks!");
	WritePerfOnFile("performance.txt");
}

void Engine::WritePerfOnFile(const string& filename)
{
	ofstream out(filename);

	out << "tp: " << tp << endl;
	out << "fp: " << fp << endl;
	out << "tn: " << tn << endl;
	out << "fn: " << fn << endl;
	out << endl;
	out << "Precision: " << (double)tp / (tp + fp) << endl;
	out << "Recall: " << (double)tp / (tp + fn) << endl;
	out << "Error Rate: " << (double)(fp + fn) / (tp + fp + tn + fn) << endl;
	out << "Accuracy: " << (double)(tp + tn) / (tp + fp + tn + fn) << endl;

	out.close();
}

void Engine::JointsChanged(int jointId, bool checked){
	if (checked){
		settings.jointMask[jointId] = 1;
	}
	else{
		settings.jointMask[jointId] = 0;
	}

	UpdateStatusBar("Joint selection updated!");
}

Settings Engine::getSettings(){
	return settings;
}

void Engine::updatePlayerLabel(int id, const std::string& label){
	playersDatabase.find(id)->second.label = label;
	UpdateStatusBar("Player label stored");
}

void Engine::UpdateStatusBar(const string& msg){
	_status = msg;
}

void Engine::Uninitialize(){
	acquisition->UnInitialize();
}