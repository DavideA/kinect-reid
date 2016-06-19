#pragma once
#include "mainwindow.h"
#include "Engine.h"
#include "Acquisition.h"
#include <QTimer>
#include <QLabel>
#include <QAction>

class MainWindowKinect : public MainWindow
{

	Q_OBJECT
	
	public:
	MainWindowKinect()
	{
		_pEngine = new Engine(NULL, 0);
		
		InitJointCheckboxes();
		InitMenuActions();
		
		_Timer.setInterval(150);
		_Timer.start();
		
		connect(&_Timer, SIGNAL(timeout()), this, SLOT(Update()));

		//override connect
		connect(right, SIGNAL(released()), this, SLOT(buttonRightSlot()));
		connect(wrong, SIGNAL(released()), this, SLOT(buttonWrongSlot()));

		connect(distL1, SIGNAL(triggered()), this, SLOT(distL1Slot()));
		connect(distL2, SIGNAL(triggered()), this, SLOT(distL2Slot()));
		connect(distLInf, SIGNAL(triggered()), this, SLOT(distLInfSlot()));
		connect(distBhat, SIGNAL(triggered()), this, SLOT(distBhatSlot()));
		connect(distCorr, SIGNAL(triggered()), this, SLOT(distCorrSlot()));
		connect(distInters, SIGNAL(triggered()), this, SLOT(distIntersSlot()));
		connect(distChisqr, SIGNAL(triggered()), this, SLOT(distChisqrSlot()));

		connect(JNormL1, SIGNAL(triggered()), this, SLOT(distJNormL1Slot()));
		connect(JNormL2, SIGNAL(triggered()), this, SLOT(distJNormL2Slot()));
		connect(JNormLInf, SIGNAL(triggered()), this, SLOT(distJNormLInfSlot()));

		connect(HNormL1, SIGNAL(triggered()), this, SLOT(distHNormL1Slot()));
		connect(HNormL2, SIGNAL(triggered()), this, SLOT(distHNormL2Slot()));
		connect(HNormLInf, SIGNAL(triggered()), this, SLOT(distHNormLInfSlot()));

		connect(hip, SIGNAL(stateChanged(int)), this, SLOT(hipSlot()));
		connect(spine, SIGNAL(stateChanged(int)), this, SLOT(spineSlot()));
		connect(shoulderCenter, SIGNAL(stateChanged(int)), this, SLOT(shoulderCenterSlot()));
		connect(head, SIGNAL(stateChanged(int)), this, SLOT(headSlot()));
		connect(shoulderLeft, SIGNAL(stateChanged(int)), this, SLOT(shoulderLeftSlot()));
		connect(elbowLeft, SIGNAL(stateChanged(int)), this, SLOT(elbowLeftSlot()));
		connect(wristLeft, SIGNAL(stateChanged(int)), this, SLOT(wristLeftSlot()));
		connect(handLeft, SIGNAL(stateChanged(int)), this, SLOT(handLeftSlot()));
		connect(shoulderRight, SIGNAL(stateChanged(int)), this, SLOT(shoulderRightSlot()));
		connect(elbowRight, SIGNAL(stateChanged(int)), this, SLOT(elbowRightSlot()));
		connect(wristRight, SIGNAL(stateChanged(int)), this, SLOT(wristRightSlot()));
		connect(handRight, SIGNAL(stateChanged(int)), this, SLOT(handRightSlot()));
		connect(hipLeft, SIGNAL(stateChanged(int)), this, SLOT(hipLeftSlot()));
		connect(kneeLeft, SIGNAL(stateChanged(int)), this, SLOT(kneeLeftSlot()));
		connect(ankleLeft, SIGNAL(stateChanged(int)), this, SLOT(ankleLeftSlot()));
		connect(footLeft, SIGNAL(stateChanged(int)), this, SLOT(footLeftSlot()));
		connect(hipRight, SIGNAL(stateChanged(int)), this, SLOT(hipRightSlot()));
		connect(kneeRight, SIGNAL(stateChanged(int)), this, SLOT(kneeRightSlot()));
		connect(ankleRight, SIGNAL(stateChanged(int)), this, SLOT(ankleRightSlot()));
		connect(footRight, SIGNAL(stateChanged(int)), this, SLOT(footRightSlot()));

		connect(tableModels, SIGNAL(cellChanged(int, int)), this, SLOT(cellChangedTextSlot(int, int)));

		updateTable = false;
	}

	~MainWindowKinect(){
		_pEngine->Uninitialize();
	}
	
	public slots:
	void Update(){

		_pEngine->Update(frame, status, database, updateTable);

		UpdateImages();
		UpdateStatus();
		if (updateTable)
			UpdateTable();
	}

protected:
	Ptr<Engine> _pEngine;
	QTimer _Timer;
	Frame frame;
	std::string status;
	bool updateTable;
	PlayerDatabase database;

	void InitJointCheckboxes();
	void InitMenuActions();

	void UpdateImages();
	void UpdateStatus();
	void UpdateTable();

protected slots:
	void distL1Slot();
	void distL2Slot();
	void distLInfSlot();
	void distBhatSlot();
	void distIntersSlot();
	void distCorrSlot();
	void distChisqrSlot();
	void distJNormL1Slot();
	void distJNormL2Slot();
	void distJNormLInfSlot();
	void distHNormL1Slot();
	void distHNormL2Slot();
	void distHNormLInfSlot();

	void buttonRightSlot();
	void buttonWrongSlot();

	void hipSlot();
	void spineSlot();
	void shoulderCenterSlot();
	void headSlot();
	void shoulderLeftSlot();
	void elbowLeftSlot();
	void wristLeftSlot();
	void handLeftSlot();
	void shoulderRightSlot();
	void elbowRightSlot();
	void wristRightSlot();
	void handRightSlot();
	void hipLeftSlot();
	void kneeLeftSlot();
	void ankleLeftSlot();
	void footLeftSlot();
	void hipRightSlot();
	void kneeRightSlot();
	void ankleRightSlot();
	void footRightSlot();

	void cellChangedTextSlot(int nRow, int nCol);

};