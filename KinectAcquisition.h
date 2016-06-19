
#pragma once


#include "Acquisition.h"

class KinectAcquisition : public Acquisition
{
    static const int        cColorWidth  = 640;
    static const int        cColorHeight = 480;

public:
    /// <summary>
    /// Constructor
    /// </summary>
	KinectAcquisition();

    /// <summary>
    /// Destructor
    /// </summary>
	~KinectAcquisition();

	Frame					GetNextFrame();
	void					UnInitialize();





private:

	// Current Kinect
    INuiSensor*             m_pNuiSensor;

	HANDLE					m_hProcessStopEvent;
   
    HANDLE                  m_pColorStreamHandle;
    HANDLE                  m_hNextColorFrameEvent;

	HANDLE                  m_pDepthStreamHandle;
	HANDLE                  m_hNextDepthFrameEvent;

	HRESULT					CreateFirstConnected();


   
	


    /// <summary>
    /// Handle new color data
    /// </summary>
    cv::Mat                    ProcessColor();

	/// <summary>
	/// Handle new depth data
	/// </summary>
	cv::Mat                    ProcessDepth();

	Microsoft::KinectBridge::OpenCVFrameHelper m_frameHelper;
	OpenCVHelper m_openCVHelper;


	cv::Mat						colorMat;
	cv::Mat						depthMat;
	NUI_SKELETON_FRAME			skeletonFrame;
	cv::Mat1b					playerIdxMat;


	void					SaveFrame(const std::string& folder, unsigned index); //obsolete
};
