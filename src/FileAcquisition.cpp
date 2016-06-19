#include "FileAcquisition.h"
#include <fstream>

using namespace std;
using namespace cv;

FileAcquisition::FileAcquisition(const string& folder):
m_pNuiSensor(NULL)
{
	CreateFirstConnected();
	frameNumber = 0;
	dataFolder = folder;
}

FileAcquisition::~FileAcquisition(){

}

void FileAcquisition::Restart(){
	frameNumber = 0;
}

Frame FileAcquisition::GetNextFrame(){

	Frame ret;

	frameNumber++;

	stringstream ssRGB, ssDepth, ssSkel, ssPlayer;
	ssRGB << dataFolder << "frame" << frameNumber << "_RGB.jpg";
	ssDepth << dataFolder << "frame" << frameNumber << "_Depth.jpg";
	ssPlayer << dataFolder << "frame" << frameNumber << "_PlayerIdxs.png";
	ssSkel << dataFolder << "frame" << frameNumber << "_skeletons.bin";

	ret.RGB = imread(ssRGB.str());
	ret.depth = imread(ssDepth.str());
	ret.playerIdx = imread(ssPlayer.str(),0);

	ifstream in_skel(ssSkel.str(), ios::binary);
	in_skel.read((char*)&ret.skeletonFrame, sizeof(NUI_SKELETON_FRAME));
	in_skel.close();

	//TODO gestire fine video

	

	return ret;
}

/// <summary>
/// Create the first connected Kinect found 
/// </summary>
/// <returns>indicates success or failure</returns>
HRESULT FileAcquisition::CreateFirstConnected()
{
	INuiSensor * pNuiSensor = NULL;
	HRESULT hr;

	int iSensorCount = 0;
	hr = NuiGetSensorCount(&iSensorCount);
	if (FAILED(hr))
	{
		return hr;
	}

	// Look at each Kinect sensor
	for (int i = 0; i < iSensorCount; ++i)
	{
		// Create the sensor so we can check status, if we can't create it, move on to the next
		hr = NuiCreateSensorByIndex(i, &pNuiSensor);
		if (FAILED(hr))
		{
			continue;
		}

		hr = m_frameHelper.Initialize(pNuiSensor);

		// Get the status of the sensor, and if connected, then we can initialize it
		hr = pNuiSensor->NuiStatus();
		if (S_OK == hr)
		{
			m_pNuiSensor = pNuiSensor;
			break;
		}

		// This sensor wasn't OK, so release it since we're not using it
		pNuiSensor->Release();
	}

	//if (NULL != m_pNuiSensor)
	//{
	//	// Initialize the Kinect and specify that we'll be using color, depth and skeleton
	//	hr = m_pNuiSensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_SKELETON);

	//	if (SUCCEEDED(hr))
	//	{
	//		// Create an event that will be signaled when depth data is available
	//		m_hNextDepthFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//		// Open a color image stream to receive depth frames
	//		hr = m_pNuiSensor->NuiImageStreamOpen(
	//			NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX,
	//			NUI_IMAGE_RESOLUTION_640x480,
	//			0,
	//			2,
	//			m_hNextDepthFrameEvent,
	//			&m_pDepthStreamHandle);

	//		if (FAILED(hr)) return hr;

	//		// Create an event that will be signaled when color data is available
	//		m_hNextColorFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//		// Open a color image stream to receive color frames
	//		hr = m_pNuiSensor->NuiImageStreamOpen(
	//			NUI_IMAGE_TYPE_COLOR,
	//			NUI_IMAGE_RESOLUTION_640x480,
	//			0,
	//			2,
	//			m_hNextColorFrameEvent,
	//			&m_pColorStreamHandle);

	//		if (FAILED(hr)) return hr;

	//	}
	//}

	return hr;
}


void FileAcquisition::UnInitialize(){


}