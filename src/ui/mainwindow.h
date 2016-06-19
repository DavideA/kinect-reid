#ifndef MAINWINDOW_H
 #define MAINWINDOW_H

#define ROW_COUNT 18

#include <QMainWindow>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QTableWidget>

 class QAction;
 class QActionGroup;
 class QLabel;
 class QMenu;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

 protected:
     //void contextMenuEvent(QContextMenuEvent *event);

protected slots :
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


 protected:
     void createActions();
     void createMenus();
     QWidget *createButtons();
     QGroupBox *createJoints();
     QWidget *createImageGrid();
     QTableWidget *createTableModels();

     QMenu *distanceMenu;
     QMenu *normalizationMenu;
     QMenu *distMinkowski;
     QMenu *normalizationJoint;
     QMenu *normalizationHisto;

     QActionGroup *alignmentGroup;
     QAction *distL1;
     QAction *distL2;
     QAction *distLInf;
     QAction *distBhat;
     QAction *distCorr;
     QAction *distInters;
     QAction *distChisqr;
     QAction *JNormL1;
     QAction *JNormL2;
     QAction *JNormLInf;
     QAction *HNormL1;
     QAction *HNormL2;
     QAction *HNormLInf;
     QLabel *infoLabel;
	 QLabel *titleLabel;
	 QActionGroup *distance;
	 QActionGroup *JNorm;
	 QActionGroup *HNorm;

     QGroupBox *activeJoints;
     QCheckBox *hip;
     QCheckBox *spine;
     QCheckBox *shoulderCenter;
     QCheckBox *head;
     QCheckBox *shoulderLeft;
     QCheckBox *elbowLeft;
     QCheckBox *wristLeft;
     QCheckBox *handLeft;
     QCheckBox *shoulderRight;
     QCheckBox *elbowRight;
     QCheckBox *wristRight;
     QCheckBox *handRight;
     QCheckBox *hipLeft;
     QCheckBox *kneeLeft;
     QCheckBox *ankleLeft;
     QCheckBox *footLeft;
     QCheckBox *hipRight;
     QCheckBox *kneeRight;
     QCheckBox *ankleRight;
     QCheckBox *footRight;

     QWidget *buttonWidget;
     QPushButton *right;
     QPushButton *wrong;

	 QLabel *labelRGB;
	 QLabel *labelDepth;
     QWidget *imageWidget;
     QImage *imageRGB;
     QImage *imageDepth;

     QTableWidget* tableModels;
     QStringList tableHeader;
 };

 #endif
