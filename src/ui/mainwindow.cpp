#include <QtGui>
#include <QLabel>
#include <QBoxLayout>
#include <QStatusBar>
#include <QMenu>
#include <QMessageBox>
#include <QMenuBar>
#include <QGroupBox>
#include <QCheckBox>
#include <QHeaderView>

 #include "mainwindow.h"
#include "Engine.h"

 MainWindow::MainWindow()
 {
     QWidget *widget = new QWidget;
     setCentralWidget(widget);

     infoLabel = new QLabel(tr(""));
     infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
     infoLabel->setAlignment(Qt::AlignLeft);
     infoLabel->setMaximumHeight(40);

	 titleLabel = new QLabel(tr("3D People re-identification by Kinect"));
	 titleLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	 titleLabel->setAlignment(Qt::AlignRight);
	 titleLabel->setMaximumHeight(40);

	 QFont font = infoLabel->font();
	 font.setBold(true);
	 font.setPointSize(15);
	 infoLabel->setFont(font);
	 titleLabel->setFont(font);

     QWidget *ijWidget = new QWidget();
     QGridLayout *ijGrid = new QGridLayout();
	 QGridLayout *tlGrid = new QGridLayout();
	 QWidget *tlWidget = new QWidget();
     QVBoxLayout *layout = new QVBoxLayout;
     layout->setMargin(5);
     widget->setLayout(layout);

     createActions();
     createMenus();
     createButtons();

     ijGrid->addWidget(createImageGrid(), 0, 0, 1, 1);
     ijGrid->addWidget(createJoints(), 0, 1, 1, 1);
     ijGrid->addWidget(createTableModels(), 0, 2, 1, 1);
	 tlGrid->addWidget(infoLabel, 0, 0, 1, 1);
	 tlGrid->addWidget(titleLabel, 0, 1, 1, 1);
     ijWidget->setLayout(ijGrid);
	 tlWidget->setLayout(tlGrid);
     layout->addWidget(ijWidget);
     layout->addWidget(buttonWidget);
	 layout->addWidget(tlWidget);

     setWindowTitle(tr("RE-Identification by Kinect"));
     //setFixedSize(1830,725);

 }

 void MainWindow::distL1Slot()
 {
     infoLabel->setText(tr("Changing histogram distance to <b>L1</b>"));
 }

 void MainWindow::distL2Slot()
 {
     infoLabel->setText(tr("Changing histogram distance to <b>L2</b>"));
 }

 void MainWindow::distLInfSlot()
 {
     infoLabel->setText(tr("Changing histogram distance to <b>LInf</b>"));
 }

 void MainWindow::distBhatSlot()
 {
     infoLabel->setText(tr("Changing histogram distance to <b>Bhatacharyya</b>"));
 }

 void MainWindow::distIntersSlot()
 {
     infoLabel->setText(tr("Changing histogram distance to <b>Intersection</b>"));
 }

 void MainWindow::distCorrSlot()
 {
     infoLabel->setText(tr("Changing histogram distance to <b>Correlation</b>"));
 }

 void MainWindow::distChisqrSlot()
 {
     infoLabel->setText(tr("Changing histogram distance to <b>Chi-Square</b>"));
 }

 void MainWindow::distJNormL1Slot()
 {
     infoLabel->setText(tr("Changing joint normalization to <b>L1</b>"));
 }

 void MainWindow::distJNormL2Slot()
 {
     infoLabel->setText(tr("Changing joint normalization to <b>L2</b>"));
 }

 void MainWindow::distJNormLInfSlot()
 {
     infoLabel->setText(tr("Changing joint normalization to <b>LInf</b>"));
 }

 void MainWindow::distHNormL1Slot()
 {
     infoLabel->setText(tr("Changing histogram normalization to <b>L1</b>"));
 }

 void MainWindow::distHNormL2Slot()
 {
     infoLabel->setText(tr("Changing histogram normalization to <b>L2</b>"));
 }

 void MainWindow::distHNormLInfSlot()
 {
     infoLabel->setText(tr("Changing histogram normalization to <b>LInf</b>"));
 }

 void MainWindow::buttonRightSlot()
 {
     infoLabel->setText(tr("Right Click"));
 }

 void MainWindow::buttonWrongSlot()
 {
     infoLabel->setText(tr("Wrong Click"));
 }

 void MainWindow::hipSlot()
 {
     if(hip->isChecked())
     {
         infoLabel->setText(tr("Hip Checked"));
     }
     else
     {
         infoLabel->setText(tr("Hip Unchecked"));
     }

 }

 void MainWindow::spineSlot()
 {
     if(spine->isChecked())
     {
         infoLabel->setText(tr("Spine Checked"));
     }
     else
     {
         infoLabel->setText(tr("Spine Unchecked"));
     }

 }

 void MainWindow::shoulderCenterSlot()
 {
     if(shoulderCenter->isChecked())
     {
         infoLabel->setText(tr("Center Shoulder Checked"));
     }
     else
     {
         infoLabel->setText(tr("Center Shoulder Unchecked"));
     }

 }

 void MainWindow::headSlot()
 {
     if(head->isChecked())
     {
         infoLabel->setText(tr("Head Checked"));
     }
     else
     {
         infoLabel->setText(tr("Head Unchecked"));
     }

 }

 void MainWindow::shoulderLeftSlot()
 {
     if(shoulderLeft->isChecked())
     {
         infoLabel->setText(tr("Left Shoulder Checked"));
     }
     else
     {
         infoLabel->setText(tr("Left Shoulder Unchecked"));
     }

 }

 void MainWindow::elbowLeftSlot()
 {
     if(elbowLeft->isChecked())
     {
         infoLabel->setText(tr("Left Elbow Checked"));
     }
     else
     {
         infoLabel->setText(tr("Left Elbow Unchecked"));
     }

 }

 void MainWindow::wristLeftSlot()
 {
     if(wristLeft->isChecked())
     {
         infoLabel->setText(tr("Left Wrist Checked"));
     }
     else
     {
         infoLabel->setText(tr("Left Wrist Unchecked"));
     }

 }

 void MainWindow:: handLeftSlot()
 {
     if(handLeft->isChecked())
     {
         infoLabel->setText(tr("Left Hand Checked"));
     }
     else
     {
         infoLabel->setText(tr("Left Hand Unchecked"));
     }

 }

 void MainWindow::shoulderRightSlot()
 {
     if(shoulderRight->isChecked())
     {
         infoLabel->setText(tr("Right Shoulder Checked"));
     }
     else
     {
         infoLabel->setText(tr("Right Shoulder Unchecked"));
     }

 }

 void MainWindow::elbowRightSlot()
 {
     if(elbowRight->isChecked())
     {
         infoLabel->setText(tr("Right Elbow Checked"));
     }
     else
     {
         infoLabel->setText(tr("Right Elbow Unchecked"));
     }

 }

 void MainWindow::wristRightSlot()
 {
     if(wristRight->isChecked())
     {
         infoLabel->setText(tr("Right Wrist Checked"));
     }
     else
     {
         infoLabel->setText(tr("Right Wrist Unchecked"));
     }

 }

 void MainWindow::handRightSlot()
 {
     if(handRight->isChecked())
     {
         infoLabel->setText(tr("Right Hand Checked"));
     }
     else
     {
         infoLabel->setText(tr("Right Hand Unchecked"));
     }

 }

 void MainWindow::hipLeftSlot()
 {
     if(hipLeft->isChecked())
     {
         infoLabel->setText(tr("Left Hip Checked"));
     }
     else
     {
         infoLabel->setText(tr("Left Hip Unchecked"));
     }

 }

 void MainWindow::kneeLeftSlot()
 {
     if(kneeLeft->isChecked())
     {
         infoLabel->setText(tr("Left Knee Checked"));
     }
     else
     {
         infoLabel->setText(tr("Left Knee Unchecked"));
     }

 }

 void MainWindow::ankleLeftSlot()
 {
     if(ankleLeft->isChecked())
     {
         infoLabel->setText(tr("Left Ankle Checked"));
     }
     else
     {
         infoLabel->setText(tr("Left Ankle Unchecked"));
     }

 }

 void MainWindow::footLeftSlot()
 {
     if(footLeft->isChecked())
     {
         infoLabel->setText(tr("Left Foot Checked"));
     }
     else
     {
         infoLabel->setText(tr("Left Foot Unchecked"));
     }

 }

 void MainWindow::hipRightSlot()
 {
     if(hipRight->isChecked())
     {
         infoLabel->setText(tr("Right Hip Checked"));
     }
     else
     {
         infoLabel->setText(tr("Right Hip Unchecked"));
     }

 }

 void MainWindow::kneeRightSlot()
 {
     if(kneeRight->isChecked())
     {
         infoLabel->setText(tr("Right Knee Checked"));
     }
     else
     {
         infoLabel->setText(tr("Right Knee Unchecked"));
     }

 }

 void MainWindow::ankleRightSlot()
 {
     if(ankleRight->isChecked())
     {
         infoLabel->setText(tr("Right Ankle Checked"));
     }
     else
     {
         infoLabel->setText(tr("Right Ankle Unchecked"));
     }

 }

 void MainWindow::footRightSlot()
 {
     if(footRight->isChecked())
     {
         infoLabel->setText(tr("Right Foot Checked"));
     }
     else
     {
         infoLabel->setText(tr("Right Foot Unchecked"));
     }

 }

 void MainWindow::cellChangedTextSlot(int nRow, int nCol)
 {
     QTableWidgetItem *item = tableModels->item(nRow,nCol);
     QString str = item->text();
     infoLabel->setText(str);
 }


 void MainWindow::createActions()
 {
	 distance = new QActionGroup(this);
	 JNorm = new QActionGroup(this);
	 HNorm = new QActionGroup(this);

     distL1=new QAction(tr("&L1"), this);
     distL1->setStatusTip(tr("L1 distance"));
	 distL1->setCheckable(true);
     //connect(distL1, SIGNAL(triggered()), this, SLOT(distL1Slot()));
	 distance->addAction(distL1);
	 

     distL2=new QAction(tr("&L2"), this);
     distL2->setStatusTip(tr("L2 distance"));
	 distL2->setCheckable(true);
     //connect(distL2, SIGNAL(triggered()), this, SLOT(distL2Slot()));
	 distance->addAction(distL2);

     distLInf=new QAction(tr("&LInf"), this);
     distLInf->setStatusTip(tr("LInf distance"));
	 distLInf->setCheckable(true);
     //connect(distLInf, SIGNAL(triggered()), this, SLOT(distLInfSlot()));
	 distance->addAction(distLInf);

     distBhat=new QAction(tr("&Bhattacharyya"), this);
     distBhat->setStatusTip(tr("Bhattacharyya distance"));
	 distBhat->setCheckable(true);
     //connect(distBhat, SIGNAL(triggered()), this, SLOT(distBhatSlot()));
	 distance->addAction(distBhat);

     distInters=new QAction(tr("&Intersection"), this);
     distInters->setStatusTip(tr("Intersection distance"));
	 distInters->setCheckable(true);
     //connect(distInters, SIGNAL(triggered()), this, SLOT(distIntersSlot()));
	 distance->addAction(distInters);

     distChisqr=new QAction(tr("&Chi-Square"), this);
     distChisqr->setStatusTip(tr("Chi-Square distance"));
	 distChisqr->setCheckable(true);
     //connect(distChisqr, SIGNAL(triggered()), this, SLOT(distChisqrSlot()));
	 distance->addAction(distChisqr);

     distCorr=new QAction(tr("&Correlation"), this);
     distCorr->setStatusTip(tr("Correlation distance"));
	 distCorr->setCheckable(true);
     //connect(distCorr, SIGNAL(triggered()), this, SLOT(distCorrSlot()));
	 distance->addAction(distCorr);

     JNormL1=new QAction(tr("&L1"), this);
     JNormL1->setStatusTip(tr("L1"));
	 JNormL1->setCheckable(true);
     //connect(JNormL1, SIGNAL(triggered()), this, SLOT(distJNormL1Slot()));
	 JNorm->addAction(JNormL1);

     JNormL2=new QAction(tr("&L2"), this);
     JNormL2->setStatusTip(tr("L2"));
	 JNormL2->setCheckable(true);
     //connect(JNormL2, SIGNAL(triggered()), this, SLOT(distJNormL2Slot()));
	 JNorm->addAction(JNormL2);

     JNormLInf=new QAction(tr("&LInf"), this);
     JNormLInf->setStatusTip(tr("LInf"));
	 JNormLInf->setCheckable(true);
     //connect(JNormLInf, SIGNAL(triggered()), this, SLOT(distJNormLInfSlot()));
	 JNorm->addAction(JNormLInf);

     HNormL1=new QAction(tr("&L1"), this);
     HNormL1->setStatusTip(tr("L1"));
	 HNormL1->setCheckable(true);
     //connect(HNormL1, SIGNAL(triggered()), this, SLOT(distHNormL1Slot()));
	 HNorm->addAction(HNormL1);

     HNormL2=new QAction(tr("&L2"), this);
     HNormL2->setStatusTip(tr("L2"));
	 HNormL2->setCheckable(true);
     //connect(HNormL2, SIGNAL(triggered()), this, SLOT(distHNormL2Slot()));
	 HNorm->addAction(HNormL2);

     HNormLInf=new QAction(tr("&LInf"), this);
     HNormLInf->setStatusTip(tr("LInf"));
	 HNormLInf->setCheckable(true);
     //connect(HNormLInf, SIGNAL(triggered()), this, SLOT(distHNormLInfSlot()));
	 HNorm->addAction(HNormLInf);

 }

 void MainWindow::createMenus()
 {
     distanceMenu = menuBar()->addMenu(tr("&Distance"));

     distMinkowski=distanceMenu->addMenu(tr("&Minkowski"));
     distMinkowski->addAction(distL1);
     distMinkowski->addAction(distL2);
     distMinkowski->addAction(distLInf);
     //distMinkowski->addSeparator()->setText(tr("Alignment"));

     distanceMenu->addAction(distBhat);
     distanceMenu->addAction(distInters);
     distanceMenu->addAction(distCorr);
     distanceMenu->addAction(distChisqr);

     normalizationMenu = menuBar()->addMenu(tr("&Normalization"));

     normalizationJoint=normalizationMenu->addMenu(tr("&Joint Normalization"));
     normalizationJoint->addAction(JNormL1);
     normalizationJoint->addAction(JNormL2);
     normalizationJoint->addAction(JNormLInf);

     normalizationHisto=normalizationMenu->addMenu(tr("&Histogram Normalization"));
     normalizationHisto->addAction(HNormL1);
     normalizationHisto->addAction(HNormL2);
     normalizationHisto->addAction(HNormLInf);
 }

 QGroupBox* MainWindow::createJoints()
 {
     QGroupBox *groupBox = new QGroupBox(tr("Active Joints"));
     groupBox->setFlat(true);

     hip = new QCheckBox(tr("&Hip"));
     hip->setChecked(true);
     //connect(hip, SIGNAL(stateChanged(int)), this, SLOT(hipSlot()));

     spine = new QCheckBox(tr("&Spine"));
     spine->setChecked(true);
     //connect(spine, SIGNAL(stateChanged(int)), this, SLOT(spineSlot()));

     shoulderCenter = new QCheckBox(tr("&Shoulder Center"));
     shoulderCenter->setChecked(true);
     //connect(shoulderCenter, SIGNAL(stateChanged(int)), this, SLOT(shoulderCenterSlot()));

     head = new QCheckBox(tr("&Head"));
     head->setChecked(true);
     //connect(head, SIGNAL(stateChanged(int)), this, SLOT(headSlot()));

     shoulderLeft = new QCheckBox(tr("&Left Shoulder"));
     shoulderLeft->setChecked(true);
     //connect(shoulderLeft, SIGNAL(stateChanged(int)), this, SLOT(shoulderLeftSlot()));

     elbowLeft = new QCheckBox(tr("&Left Elbow"));
     elbowLeft->setChecked(true);
     //connect(elbowLeft, SIGNAL(stateChanged(int)), this, SLOT(elbowLeftSlot()));

     wristLeft = new QCheckBox(tr("&Left Wrist"));
     wristLeft->setChecked(true);
     //connect(wristLeft, SIGNAL(stateChanged(int)), this, SLOT(wristLeftSlot()));

     handLeft = new QCheckBox(tr("&Left Hand"));
     handLeft->setChecked(true);
     //connect(handLeft, SIGNAL(stateChanged(int)), this, SLOT(handLeftSlot()));

     shoulderRight = new QCheckBox(tr("&Right Shoulder"));
     shoulderRight->setChecked(true);
     //connect(shoulderRight, SIGNAL(stateChanged(int)), this, SLOT(shoulderRightSlot()));

     elbowRight = new QCheckBox(tr("&Right Elbow"));
     elbowRight->setChecked(true);
     //connect(elbowRight, SIGNAL(stateChanged(int)), this, SLOT(elbowRightSlot()));

     wristRight = new QCheckBox(tr("&Right Wrist"));
     wristRight->setChecked(true);
     //connect(wristRight, SIGNAL(stateChanged(int)), this, SLOT(wristRightSlot()));

     handRight = new QCheckBox(tr("&Right Hand"));
     handRight->setChecked(true);
     //connect(handRight, SIGNAL(stateChanged(int)), this, SLOT(handRightSlot()));

     hipLeft = new QCheckBox(tr("&Left Hip"));
     hipLeft->setChecked(true);
     //connect(hipLeft, SIGNAL(stateChanged(int)), this, SLOT(hipLeftSlot()));

     kneeLeft = new QCheckBox(tr("&Left Knee"));
     kneeLeft->setChecked(true);
     //connect(kneeLeft, SIGNAL(stateChanged(int)), this, SLOT(kneeLeftSlot()));

     ankleLeft = new QCheckBox(tr("&Left Ankle"));
     ankleLeft->setChecked(true);
     //connect(ankleLeft, SIGNAL(stateChanged(int)), this, SLOT(ankleLeftSlot()));

     footLeft = new QCheckBox(tr("&Left Foot"));
     footLeft->setChecked(true);
     //connect(footLeft, SIGNAL(stateChanged(int)), this, SLOT(footLeftSlot()));

     hipRight = new QCheckBox(tr("&Right Hip"));
     hipRight->setChecked(true);
     //connect(hipRight, SIGNAL(stateChanged(int)), this, SLOT(hipRightSlot()));

     kneeRight = new QCheckBox(tr("&Right Knee"));
     kneeRight->setChecked(true);
     //connect(kneeRight, SIGNAL(stateChanged(int)), this, SLOT(kneeRightSlot()));

     ankleRight = new QCheckBox(tr("&Right Ankle"));
     ankleRight->setChecked(true);
     //connect(ankleRight, SIGNAL(stateChanged(int)), this, SLOT(ankleRightSlot()));

     footRight = new QCheckBox(tr("&Right Foot"));
     footRight->setChecked(true);
     //connect(footRight, SIGNAL(stateChanged(int)), this, SLOT(footRightSlot()));

     QVBoxLayout *vbox = new QVBoxLayout;
     vbox->addWidget(hip);
     vbox->addWidget(spine);
     vbox->addWidget(shoulderCenter);
     vbox->addWidget(head);
     vbox->addWidget(shoulderLeft);
     vbox->addWidget(elbowLeft);
     vbox->addWidget(wristLeft);
     vbox->addWidget(handLeft);
     vbox->addWidget(shoulderRight);
     vbox->addWidget(elbowRight);
     vbox->addWidget(wristRight);
     vbox->addWidget(handRight);
     vbox->addWidget(hipLeft);
     vbox->addWidget(kneeLeft);
     vbox->addWidget(ankleLeft);
     vbox->addWidget(footLeft);
     vbox->addWidget(hipRight);
     vbox->addWidget(kneeRight);
     vbox->addWidget(ankleRight);
     vbox->addWidget(footRight);
     //vbox->addStretch(1);
     groupBox->setLayout(vbox);
     vbox->setAlignment((Qt::AlignRight));
     //groupBox->setMaximumWidth(200);

     return groupBox;
 }

 QWidget* MainWindow::createButtons()
 {
     buttonWidget = new QWidget();
     QGridLayout *buttonGrid = new QGridLayout();
     right = new QPushButton("Right", this);
     right->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
     //connect(right, SIGNAL(released()), this, SLOT(buttonRightSlot()));
     buttonGrid->addWidget(right, 0, 0, 1, 1);

     wrong = new QPushButton("Wrong", this);
     wrong->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
     //connect(wrong, SIGNAL(released()), this, SLOT(buttonWrongSlot()));
     buttonGrid->addWidget(wrong, 0, 1, 1, 1);

     buttonWidget->setLayout(buttonGrid);
     buttonWidget->setMaximumWidth(300);
     return buttonWidget;
 }

 QWidget* MainWindow::createImageGrid()
 {
     imageWidget = new QWidget();
     QGridLayout *imageGrid = new QGridLayout();
     labelRGB = new QLabel();
     QLabel *labelTitleRGB = new QLabel();
     labelTitleRGB->setText("RGB");
     labelTitleRGB->setAlignment(Qt::AlignCenter);
     //imageRGB = new QImage();
     //imageRGB->load(QCoreApplication::applicationDirPath()+"/immagine1.jpg");
     //labelRGB->setPixmap((QPixmap::fromImage(*imageRGB)));
     labelRGB->setFixedSize(640,480);
     imageGrid->addWidget(labelTitleRGB, 0, 0, 1, 1);
     imageGrid->addWidget(labelRGB, 1, 0, 1, 1);

     labelDepth = new QLabel();
     QLabel *labelTitleDepth = new QLabel();
     labelTitleDepth->setText("DEPTH");
     labelTitleDepth->setAlignment(Qt::AlignCenter);
     //imageDepth = new QImage();
     //imageDepth->load(QCoreApplication::applicationDirPath()+"/immagine2.jpg");
     //labelDepth->setPixmap((QPixmap::fromImage(*imageDepth)));
     labelDepth->setFixedSize(640,480);
     imageGrid->addWidget(labelTitleDepth, 0, 1, 1, 1);
     imageGrid->addWidget(labelDepth, 1, 1, 1, 1);

     imageWidget->setLayout(imageGrid);
     return imageWidget;
 }

  QTableWidget* MainWindow::createTableModels()
  {
      tableModels = new QTableWidget();
      tableModels->setRowCount(ROW_COUNT);
      tableModels->setColumnCount(2);
      tableModels->setColumnWidth(0, 100);
      tableModels->setColumnWidth(1, 200);
      tableModels->setFixedWidth(302);
      tableHeader<<"ID"<<"LABEL";
      tableModels->setHorizontalHeaderLabels(tableHeader);
      tableModels->verticalHeader()->setVisible(false);
      tableModels->setSelectionBehavior(QAbstractItemView::SelectRows);
      tableModels->setSelectionMode(QAbstractItemView::SingleSelection);
      tableModels->setShowGrid(true);

      connect( tableModels, SIGNAL( cellChanged(int,int) ),this, SLOT( cellChangedTextSlot( int, int ) ) );

      return tableModels;

  }


