#pragma once 

#include <opencv2\opencv.hpp>

struct jointHisto{
	cv::Mat1f R;
	cv::Mat1f G;
	cv::Mat1f B;
};

class Model{
public:
	Model();
	Model(unsigned nBin);
	~Model();

	void InsertPixelInJointHistogram(cv::Vec3b pixel, char joint);

	std::vector<jointHisto> model;

private:
	unsigned char			NUM_BIN;

};
