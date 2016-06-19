#include "Model.h"

using namespace std;
using namespace cv;

Model::Model(){

}

Model::Model(unsigned nBin){
	NUM_BIN = nBin;
	for (unsigned i = 0; i < 20; ++i){
		jointHisto jh;
		jh.R = cv::Mat1f(1, NUM_BIN, 0.f);
		jh.G = cv::Mat1f(1, NUM_BIN, 0.f);
		jh.B = cv::Mat1f(1, NUM_BIN, 0.f);
		model.push_back(jh);
	}
}

void Model::InsertPixelInJointHistogram(cv::Vec3b pixel, char joint){
	jointHisto& histo = model[joint];

	uchar b = pixel[0];
	uchar g = pixel[1];
	uchar r = pixel[2];

	histo.R.at<float>(r*NUM_BIN / 256)++;
	histo.G.at<float>(g*NUM_BIN / 256)++;
	histo.B.at<float>(b*NUM_BIN / 256)++;

}

Model::~Model(){
	model.clear();
}
