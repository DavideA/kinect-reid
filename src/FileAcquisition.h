#pragma once

#include "Acquisition.h"

class FileAcquisition : public Acquisition
{
public:

	FileAcquisition(const string& folder);
	~FileAcquisition();

	Frame						GetNextFrame();
	void						UnInitialize();
	void						Init(const string& folder);
	void						Restart();

private:
	unsigned					frameNumber;
	string						dataFolder;

	// this part handles kinect device. why do we need it if we acquire from file?
	// we need to initialize kinect because some api function need its intrinsic
	// parameters to work :(

	INuiSensor*					m_pNuiSensor;

	Microsoft::KinectBridge::OpenCVFrameHelper m_frameHelper;


	HRESULT					    CreateFirstConnected();



};
