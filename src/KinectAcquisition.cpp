
#include "stdafx.h"
#include <strsafe.h>
#include "KinectAcquisition.h"
#include "resource.h"

using namespace std;
using namespace cv;

/// <summary>
/// Constructor
/// </summary>

KinectAcquisition::KinectAcquisition() :
m_hNextColorFrameEvent(INVALID_HANDLE_VALUE),
m_pColorStreamHandle(INVALID_HANDLE_VALUE),
m_hProcessStopEvent(NULL),
m_pNuiSensor(NULL)
{
	CreateFirstConnected();

	DWORD width, height;
	m_frameHelper.GetColorFrameSize(&width, &height);
	Size size(width, height);
	colorMat.create(size, m_frameHelper.COLOR_TYPE);

	DWORD width_d, height_d;
	m_frameHelper.GetDepthFrameSize(&width_d, &height_d);
	Size size_d(width_d, height_d);
	depthMat.create(size_d, m_frameHelper.DEPTH_RGB_TYPE);

	playerIdxMat=Mat_<char>(size_d);
}

/// <summary>
/// Destructor
/// </summary>
KinectAcquisition::~KinectAcquisition()
{
	if (m_pNuiSensor)
	{
		m_pNuiSensor->NuiShutdown();
	}

	if (m_hNextColorFrameEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hNextColorFrameEvent);
	}

	SafeRelease(m_pNuiSensor);
}


Frame KinectAcquisition::GetNextFrame()
{
	// Initialize array of events to wait for
	HANDLE hEvents[4] = { m_hProcessStopEvent, NULL, NULL, NULL };
	int numEvents;
	if (m_frameHelper.IsInitialized())
	{
		m_frameHelper.GetColorHandle(hEvents + 1);
		m_frameHelper.GetDepthHandle(hEvents + 2);
		m_frameHelper.GetSkeletonHandle(hEvents + 3);
		numEvents = 4;
	}
	else
	{
		numEvents = 1;
	}

	Frame f;

	int eventId = WaitForMultipleObjects(numEvents, hEvents, FALSE, 100);

	bool skeletonAcquired = false, colorAcquired = false, depthAcquired = false;

	if (eventId != WAIT_TIMEOUT && eventId != WAIT_OBJECT_0){
		
		while (!skeletonAcquired || !colorAcquired || !depthAcquired){

			// Update skeleton frame

			if (SUCCEEDED(m_frameHelper.UpdateSkeletonFrame())&&!skeletonAcquired)
			{
				m_frameHelper.GetSkeletonFrame(&skeletonFrame);
				skeletonAcquired = true;
			}

			// Update color frame
			if (SUCCEEDED(m_frameHelper.UpdateColorFrame())&&!colorAcquired)
			{
				m_frameHelper.GetColorImage(&colorMat);
				colorAcquired = true;
			}

			// Update depth frame
			if (SUCCEEDED(m_frameHelper.UpdateDepthFrame()) && !depthAcquired && skeletonAcquired)
			{

				HRESULT hr = m_frameHelper.GetDepthImageAsArgb(&depthMat, &playerIdxMat);
				hr = m_openCVHelper.DrawSkeletonsInDepthImage(&depthMat, &skeletonFrame, NUI_IMAGE_RESOLUTION_640x480);
				depthAcquired = true;
			}

		}

		f.RGB = colorMat;
		f.depth = depthMat;
		f.playerIdx = playerIdxMat;
		f.skeletonFrame = skeletonFrame;


	}
	return f;
}

Mat KinectAcquisition::ProcessColor(){

	Mat RGB;

	HRESULT hr;
	NUI_IMAGE_FRAME imageFrame;

	// Attempt to get the color frame
	hr = m_pNuiSensor->NuiImageStreamGetNextFrame(m_pColorStreamHandle, 0, &imageFrame);
	if (FAILED(hr))
	{
		return RGB;
	}

	INuiFrameTexture * pTexture = imageFrame.pFrameTexture;
	NUI_LOCKED_RECT LockedRect;

	// Lock the frame data so the Kinect knows not to modify it while we're reading it
	pTexture->LockRect(0, &LockedRect, NULL, 0);

	// Make sure we've received valid data
	if (LockedRect.Pitch != 0)
	{
		BYTE * pBuffer = (BYTE*)LockedRect.pBits;
		Mat imgtmp(480, 640, CV_8UC4, pBuffer);
		RGB = imgtmp;
	}

	// We're done with the texture so unlock it
	pTexture->UnlockRect(0);

	// Release the frame
	m_pNuiSensor->NuiImageStreamReleaseFrame(m_pColorStreamHandle, &imageFrame);

	return RGB;
}

Mat KinectAcquisition::ProcessDepth(){

	Mat depth;

	HRESULT hr;
	NUI_IMAGE_FRAME imageFrame;

	// Attempt to get the color frame
	hr = m_pNuiSensor->NuiImageStreamGetNextFrame(m_pDepthStreamHandle, 0, &imageFrame);
	if (FAILED(hr))
	{
		return depth;
	}

	INuiFrameTexture* pTexture;

	// Get the depth image pixel texture
	hr = m_pNuiSensor->NuiImageFrameGetDepthImagePixelFrameTexture(
		m_pDepthStreamHandle, &imageFrame, false, &pTexture);

	NUI_LOCKED_RECT LockedRect;

	// Lock the frame data so the Kinect knows not to modify it while we're reading it
	pTexture->LockRect(0, &LockedRect, NULL, 0);



	// Make sure we've received valid data
	if (LockedRect.Pitch != 0)
	{


		DWORD depthHeight, depthWidth;
		NuiImageResolutionToSize(NUI_IMAGE_RESOLUTION_640x480, depthWidth, depthHeight);

		Mat depthImage(depthHeight, depthWidth, CV_16U);


		// Copy image information into Mat
		USHORT* pBufferRun = reinterpret_cast<USHORT*>(pTexture);

		for (UINT y = 0; y < depthHeight; ++y)
		{
			// Get row pointer for depth Mat
			USHORT* pDepthRow = depthImage.ptr<USHORT>(y);

			for (UINT x = 0; x < depthWidth; ++x)
			{
				pDepthRow[x] = pBufferRun[y * depthWidth + x];
			}
		}

		depth = depthImage;
	}

	// We're done with the texture so unlock it
	pTexture->UnlockRect(0);

	// Release the frame
	m_pNuiSensor->NuiImageStreamReleaseFrame(m_pDepthStreamHandle, &imageFrame);

	return depth;
}

/// <summary>
/// Create the first connected Kinect found 
/// </summary>
/// <returns>indicates success or failure</returns>
HRESULT KinectAcquisition::CreateFirstConnected()
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

	if (NULL != m_pNuiSensor)
	{
		// Initialize the Kinect and specify that we'll be using color, depth and skeleton
		hr = m_pNuiSensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_SKELETON);

		if (SUCCEEDED(hr))
		{
			// Create an event that will be signaled when depth data is available
			m_hNextDepthFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

			// Open a color image stream to receive depth frames
			hr = m_pNuiSensor->NuiImageStreamOpen(
				NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX,
				NUI_IMAGE_RESOLUTION_640x480,
				0,
				2,
				m_hNextDepthFrameEvent,
				&m_pDepthStreamHandle);

			if (FAILED(hr)) return hr;

			// Create an event that will be signaled when color data is available
			m_hNextColorFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

			// Open a color image stream to receive color frames
			hr = m_pNuiSensor->NuiImageStreamOpen(
				NUI_IMAGE_TYPE_COLOR,
				NUI_IMAGE_RESOLUTION_640x480,
				0,
				2,
				m_hNextColorFrameEvent,
				&m_pColorStreamHandle);

			if (FAILED(hr)) return hr;

		}
	}

	return hr;
}


void KinectAcquisition::UnInitialize()
{
	// Close Kinect
	if (m_pNuiSensor)
	{
		m_pNuiSensor->NuiShutdown();
		m_pNuiSensor = NULL;
	}

	// Close handles for created events
	if (m_hNextColorFrameEvent && (m_hNextColorFrameEvent != INVALID_HANDLE_VALUE))
	{
		CloseHandle(m_hNextColorFrameEvent);
		m_hNextColorFrameEvent = NULL;
	}

	if (m_hNextDepthFrameEvent && (m_hNextDepthFrameEvent != INVALID_HANDLE_VALUE))
	{
		CloseHandle(m_hNextDepthFrameEvent);
		m_hNextDepthFrameEvent = NULL;
	}
/*
	if (m_hNextSkeletonFrameEvent && (m_hNextSkeletonFrameEvent != INVALID_HANDLE_VALUE))
	{
		CloseHandle(m_hNextSkeletonFrameEvent);
		m_hNextSkeletonFrameEvent = NULL;
	}*/
}