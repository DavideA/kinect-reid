#include <string>
#include <opencv2\opencv.hpp>
#include "OpenCVFrameHelper.h"
#include "OpenCVHelper.h"

#pragma once


typedef struct Frame{
	cv::Mat					RGB;
	cv::Mat					depth;
	cv::Mat1b				playerIdx;
	NUI_SKELETON_FRAME		skeletonFrame;
} Frame;


typedef enum{
	KINECT_ACQUISITION,
	FILE_ACQUISITION
}acquisition_type;

class Acquisition{

public:
	virtual Frame	GetNextFrame() = 0;
	virtual void	UnInitialize() = 0;
};