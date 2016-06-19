#include "ModelExtractor.h"
#include "OpenCVHelper.h"
#include <omp.h>
#include <map>

using namespace std;

ModelExtractor::ModelExtractor(){

}

ModelExtractor::~ModelExtractor(){
	
}

void copyPositions(Vector4* src, Vector4* dst){
	for (unsigned i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i){
		dst[i].x = src[i].x;
		dst[i].y = src[i].y;
		dst[i].z = src[i].z;
		dst[i].w = src[i].w;
	}

}

ModelMap ModelExtractor::EvalModels(Frame currFrame, unsigned char nBins){
	
	ModelMap models;

	Mat playerIdx = currFrame.playerIdx;
	Mat RGB = currFrame.RGB.clone();

	vector<Point2d> joints[6];
	Scalar color=Scalar(255, 0, 0);

	for (char i = 0; i < 6; ++i){
		if (currFrame.skeletonFrame.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED){

			unsigned id = currFrame.skeletonFrame.SkeletonData[i].dwTrackingID;
			Model m(nBins);
			models.insert(pair<char, Model>(id, m));

			Vector4 jointPositions[NUI_SKELETON_POSITION_COUNT];
			copyPositions(currFrame.skeletonFrame.SkeletonData[i].SkeletonPositions, jointPositions);
			
			for (unsigned j = 0; j < NUI_SKELETON_POSITION_COUNT; ++j){

				LONG plDepthX, plDepthY;
				CVHelper.GetCoordinatesForSkeletonPoint(jointPositions[j], &plDepthX, &plDepthY, NUI_IMAGE_RESOLUTION_640x480, NUI_IMAGE_RESOLUTION_640x480);
				Point2d p(plDepthX, plDepthY);
				
				//circle(RGB, p, 1, Scalar(0, 255, 0), 2);
				joints[i].push_back(p);
			}
		}
	}

	vector<Scalar> colors;
	colors.push_back(Scalar(0, 255, 255));		//Giallo
	colors.push_back(Scalar(92, 11, 227));		//Lampone
	colors.push_back(Scalar(105, 140, 255));	//Salmone
	colors.push_back(Scalar(0, 255, 0));		//Verde
	colors.push_back(Scalar(0, 0, 255));		//Rosso
	colors.push_back(Scalar(255, 0, 0));		//Blu
	colors.push_back(Scalar(0, 77, 255));		//Viola
	colors.push_back(Scalar(180, 229, 255));	//Pesca
	colors.push_back(Scalar(226, 228, 229));	//Platino
	colors.push_back(Scalar(145, 176, 195));	//Kaki
	colors.push_back(Scalar(255, 0, 111));		//Indaco Elettrico
	colors.push_back(Scalar(69, 89, 69));		//Grigio Asparago
	colors.push_back(Scalar(255, 255, 224));	//Carta da Zucchero
	colors.push_back(Scalar(53, 132, 144));		//Beige-oliva chiaro
	colors.push_back(Scalar(171, 189, 218));	//Marrone sabbia chiaro
	colors.push_back(Scalar(0, 0, 0));			//Nero
	colors.push_back(Scalar(255, 255, 255));	//Bianco
	colors.push_back(Scalar(102, 0, 102));		//Prugna
	colors.push_back(Scalar(51, 155, 184));		//Rame
	colors.push_back(Scalar(192, 15, 252));		//Rosa shocking


//#pragma omp parallel for
	for (int r = 0; r < playerIdx.rows; ++r){
		for (int c = 0; c < playerIdx.cols; ++c){
			uchar idx = playerIdx.at<uchar>(r, c);
			
			if ( idx> 0 ){
				LONG plDepthX = c;
				LONG plDepthY = r;
				LONG plColorX=c, plColorY=r;
				NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(NUI_IMAGE_RESOLUTION_640x480, NUI_IMAGE_RESOLUTION_640x480, NULL, plDepthX, plDepthY, 0, &plColorX, &plColorY);
				Point2d pt(plColorX, plColorY);
				if (pt.x>0 && pt.x<RGB.cols && pt.y>0 && pt.y < RGB.rows){ //if the point is inside image
					unsigned id = currFrame.skeletonFrame.SkeletonData[idx - 1].dwTrackingID;
					double minDist = INFINITY;
					unsigned minDistIdx = 1; //hip
					//circle(RGB, pt, 3, Scalar(255, 0, 0), 3);
					vector<Point2d> jointsOfPlayer = joints[idx - 1];
					for (unsigned j = 0; j < NUI_SKELETON_POSITION_COUNT; ++j){
						double dist = norm(Mat(pt), Mat(jointsOfPlayer[j]));
						if (dist < minDist){
							minDist = dist;
							minDistIdx = j;
						}

					}
					ModelIterator it = models.find(id);
					if (plColorX >= 0 && plColorX < RGB.cols && plColorY >= 0 && plColorY < RGB.rows){//within the image
						(it->second).InsertPixelInJointHistogram(RGB.at<Vec3b>(plColorY,plColorX), minDistIdx);
						circle(RGB, pt, 0, colors[minDistIdx], 1);
					}
				}

			}

		}
	}

	cvNamedWindow("player", CV_WINDOW_AUTOSIZE);
	imshow("player", RGB);
	waitKey(5000);
	cvDestroyWindow("player");

	return models;
}