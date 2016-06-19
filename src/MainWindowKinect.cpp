#include "MainWindowKinect.h"


void MainWindowKinect::distL1Slot()
{
	_pEngine->SetDistance(Method::L1);

}

void MainWindowKinect::distL2Slot()
{
	_pEngine->SetDistance(Method::L2);
}

void MainWindowKinect::distLInfSlot()
{
	_pEngine->SetDistance(Method::Linf);
}

void MainWindowKinect::distBhatSlot()
{
	_pEngine->SetDistance(Method::BHATTACHARYYA);
}

void MainWindowKinect::distIntersSlot()
{
	_pEngine->SetDistance(Method::INTERSECTION);
}

void MainWindowKinect::distCorrSlot()
{
	_pEngine->SetDistance(Method::CORRELATION);
}

void MainWindowKinect::distChisqrSlot()
{
	_pEngine->SetDistance(Method::CHISQ);
}

void MainWindowKinect::distJNormL1Slot()
{
	_pEngine->SetJointNormalization(Method::L1);
}

void MainWindowKinect::distJNormL2Slot()
{
	_pEngine->SetJointNormalization(Method::L2);
}

void MainWindowKinect::distJNormLInfSlot()
{
	_pEngine->SetHistoNormalization(Method::L1);
}

void MainWindowKinect::distHNormL1Slot()
{
	_pEngine->SetJointNormalization(Method::L1);
}

void MainWindowKinect::distHNormL2Slot()
{
	_pEngine->SetHistoNormalization(Method::L2);
}

void MainWindowKinect::distHNormLInfSlot()
{
	_pEngine->SetHistoNormalization(Method::Linf);
}

void MainWindowKinect::buttonRightSlot()
{
	_pEngine->ButtonClicked(true);
}

void MainWindowKinect::buttonWrongSlot()
{
	_pEngine->ButtonClicked(false);
}

void MainWindowKinect::hipSlot()
{
	if (hip->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HIP_CENTER, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HIP_CENTER, false);
	}

}

void MainWindowKinect::spineSlot()
{
	if (spine->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_SPINE, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_SPINE, false);
	}

}

void MainWindowKinect::shoulderCenterSlot()
{
	if (shoulderCenter->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_SHOULDER_CENTER, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_SHOULDER_CENTER, false);
	}

}

void MainWindowKinect::headSlot()
{
	if (head->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HEAD, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HEAD, false);
	}

}

void MainWindowKinect::shoulderLeftSlot()
{
	if (shoulderLeft->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_SHOULDER_LEFT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_SHOULDER_LEFT, false);
	}

}

void MainWindowKinect::elbowLeftSlot()
{
	if (elbowLeft->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_ELBOW_LEFT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_ELBOW_LEFT, false);
	}

}

void MainWindowKinect::wristLeftSlot()
{
	if (wristLeft->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_WRIST_LEFT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_WRIST_LEFT, false);
	}

}

void MainWindowKinect::handLeftSlot()
{
	if (handLeft->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HAND_LEFT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HAND_LEFT, false);
	}

}

void MainWindowKinect::shoulderRightSlot()
{
	if (shoulderRight->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_SHOULDER_RIGHT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_SHOULDER_RIGHT, false);
	}

}

void MainWindowKinect::elbowRightSlot()
{
	if (elbowRight->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_ELBOW_RIGHT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_ELBOW_RIGHT, false);
	}

}

void MainWindowKinect::wristRightSlot()
{
	if (wristRight->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_WRIST_RIGHT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_WRIST_RIGHT, false);
	}

}

void MainWindowKinect::handRightSlot()
{
	if (handRight->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HAND_RIGHT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HAND_RIGHT, false);
	}

}

void MainWindowKinect::hipLeftSlot()
{
	if (hipLeft->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HIP_LEFT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HIP_LEFT, false);
	}

}

void MainWindowKinect::kneeLeftSlot()
{
	if (kneeLeft->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_KNEE_LEFT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_KNEE_LEFT, false);
	}

}

void MainWindowKinect::ankleLeftSlot()
{
	if (ankleLeft->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_ANKLE_LEFT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_ANKLE_LEFT, false);
	}

}

void MainWindowKinect::footLeftSlot()
{
	if (footLeft->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_FOOT_LEFT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_FOOT_LEFT, false);
	}

}

void MainWindowKinect::hipRightSlot()
{
	if (hipRight->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HIP_RIGHT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_HIP_RIGHT, false);
	}

}

void MainWindowKinect::kneeRightSlot()
{
	if (kneeRight->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_KNEE_RIGHT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_KNEE_RIGHT, false);
	}

}

void MainWindowKinect::ankleRightSlot()
{
	if (ankleRight->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_ANKLE_RIGHT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_ANKLE_RIGHT, false);
	}

}

void MainWindowKinect::footRightSlot()
{
	if (footRight->isChecked())
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_FOOT_RIGHT, true);
	}
	else
	{
		_pEngine->JointsChanged(NUI_SKELETON_POSITION_FOOT_RIGHT, false);
	}

}

void MainWindowKinect::InitJointCheckboxes(){

	Settings set = _pEngine->getSettings();

	if (!set.jointMask[NUI_SKELETON_POSITION_HIP_CENTER]) hip->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_SPINE]) spine->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_SHOULDER_CENTER]) shoulderCenter->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_HEAD]) head->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_SHOULDER_LEFT]) shoulderLeft->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_WRIST_LEFT]) wristLeft->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_HAND_LEFT]) handLeft->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_SHOULDER_RIGHT]) shoulderRight->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_ELBOW_RIGHT]) elbowRight->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_WRIST_RIGHT]) wristRight->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_HAND_RIGHT]) handRight->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_HIP_LEFT]) hipLeft->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_KNEE_LEFT]) kneeLeft->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_ANKLE_LEFT]) ankleLeft->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_FOOT_LEFT]) footLeft->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_HIP_RIGHT]) hipRight->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_KNEE_RIGHT]) kneeRight->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_ANKLE_RIGHT]) ankleRight->setChecked(false);
	if (!set.jointMask[NUI_SKELETON_POSITION_FOOT_RIGHT]) footRight->setChecked(false);

}

void MainWindowKinect::InitMenuActions(){

	Settings set = _pEngine->getSettings();

	switch (set.histoDifference){
	case Method::L1:
		distL1->setChecked(true);
		break;
	case Method::L2:
		distL2->setChecked(true);
		break;
	case Method::Linf:
		distLInf->setChecked(true);
		break;
	case Method::BHATTACHARYYA:
		distBhat->setChecked(true);
		break;
	case Method::CORRELATION:
		distCorr->setChecked(true);
		break;
	case Method::INTERSECTION:
		distInters->setChecked(true);
		break;
	case Method::CHISQ:
		distChisqr->setChecked(true);
		break;
	default:
		exit(4);
	}

	switch (set.histoNormalization){
	case Method::L1:
		HNormL1->setChecked(true);
		break;
	case Method::L2:
		HNormL2->setChecked(true);
		break;
	case Method::Linf:
		HNormLInf->setChecked(true);
		break;
	default:
		exit(4);
	}

	switch (set.jointNormalization){
	case Method::L1:
		JNormL1->setChecked(true);
		break;
	case Method::L2:
		JNormL2->setChecked(true);
		break;
	case Method::Linf:
		JNormLInf->setChecked(true);
		break;
	default:
		exit(4);
	}
}

void MainWindowKinect::UpdateImages(){
	cvtColor(frame.RGB, frame.RGB, CV_BGR2RGB);
	cvtColor(frame.depth, frame.depth, CV_BGR2RGB);
	imageRGB = new QImage((uchar*)frame.RGB.data, frame.RGB.cols, frame.RGB.rows, frame.RGB.step, QImage::Format_RGB888);
	imageDepth = new QImage((uchar*)frame.depth.data, frame.depth.cols, frame.depth.rows, frame.depth.step, QImage::Format_RGB888);

	labelRGB->setPixmap((QPixmap::fromImage(*imageRGB)));
	labelDepth->setPixmap((QPixmap::fromImage(*imageDepth)));
}

void MainWindowKinect::UpdateStatus(){
	infoLabel->setText(QString::fromStdString(status));
}

void MainWindowKinect::UpdateTable(){

	for (PlayerDatabaseIterator pdIt = database.begin(); pdIt != database.end(); ++pdIt){
		int id = pdIt->first;
		QTableWidgetItem *item = tableModels->item(0, 0);
		if (item != NULL){
			for (int r = 0; r < tableModels->rowCount(); ++r){
				QTableWidgetItem *item = tableModels->item(r, 0);
				if (item!=NULL && id != item->text().toInt()){
					disconnect(tableModels, SIGNAL(cellChanged(int, int)), this, SLOT(cellChangedTextSlot(int, int)));

					QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(id));
					itemId->setTextAlignment(Qt::AlignCenter);
					itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
					tableModels->setItem(database.size()-1, 0, itemId);

					QTableWidgetItem *itemLabel = new QTableWidgetItem(QString::fromStdString(pdIt->second.label));
					itemLabel->setTextAlignment(Qt::AlignCenter);
					tableModels->setItem(database.size()-1, 1, itemLabel);

					connect(tableModels, SIGNAL(cellChanged(int, int)), this, SLOT(cellChangedTextSlot(int, int)));
				}
			}
		}
		else{
			disconnect(tableModels, SIGNAL(cellChanged(int, int)), this, SLOT(cellChangedTextSlot(int, int)));

			QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(id));
			itemId->setTextAlignment(Qt::AlignCenter);
			itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
			tableModels->setItem(0, 0, itemId);

			QTableWidgetItem *itemLabel = new QTableWidgetItem(QString::fromStdString(pdIt->second.label));
			itemLabel->setTextAlignment(Qt::AlignCenter);
			tableModels->setItem(0, 1, itemLabel);

			connect(tableModels, SIGNAL(cellChanged(int, int)), this, SLOT(cellChangedTextSlot(int, int)));
		}
		
	}
}

void MainWindowKinect::cellChangedTextSlot(int nRow, int nCol)
{
	QTableWidgetItem *itemId = tableModels->item(nRow, 0);
	QTableWidgetItem *itemLabel = tableModels->item(nRow, 1);
	QString id = itemId->text();
	QString label = itemLabel->text();

	_pEngine->updatePlayerLabel(id.toInt(), label.toStdString());
}