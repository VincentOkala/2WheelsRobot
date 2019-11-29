/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *Maintab;
    QWidget *modeBasic;
    QPushButton *btn_change_mode_basic;
    QGroupBox *groupBox_11;
    QLabel *label_47;
    QLineEdit *txtBoxRoll;
    QLabel *label_48;
    QLineEdit *txtBoxPitch;
    QLabel *label_54;
    QLineEdit *txtBoxYaw;
    QLineEdit *txtBoxVY;
    QLineEdit *txtBoxVX;
    QLineEdit *txtBoxOMEGA;
    QLabel *label_61;
    QLabel *label_62;
    QLabel *label_63;
    QGroupBox *groupBox_13;
    QLabel *label_55;
    QLineEdit *txtBoxMPU;
    QWidget *modeIMUCalibration;
    QGroupBox *groupBox_7;
    QLineEdit *tb_gx;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_22;
    QLabel *label_23;
    QLineEdit *tb_gy;
    QLineEdit *tb_gz;
    QLineEdit *tb_gx_offset;
    QLineEdit *tb_gy_offset;
    QLabel *label_24;
    QLineEdit *tb_gz_offset;
    QPushButton *btn_gyro_calib;
    QLineEdit *tb_stand_point;
    QLineEdit *tb_stand_point_current;
    QLabel *label_25;
    QLabel *label_26;
    QPushButton *btn_mode_imu_write_params;
    QPushButton *btn_mode_imu_save_params;
    QPushButton *btn_change_mode_imu_calibration;
    QPushButton *btn_mode_imu_load_params;
    QWidget *modePIDTunnig;
    QPushButton *btn_change_mode_pid_tunning;
    QPushButton *btn_mode_pidt_load_params;
    QPushButton *btn_mode_pidt_write_params;
    QPushButton *btn_mode_pidt_save_params;
    QGroupBox *groupBox_2;
    QDoubleSpinBox *sb_KP;
    QLabel *label_40;
    QLabel *label_49;
    QDoubleSpinBox *sb_KI;
    QLabel *label_50;
    QDoubleSpinBox *sb_KD;
    QLabel *label_51;
    QDoubleSpinBox *sb_step_KP;
    QLabel *label_52;
    QDoubleSpinBox *sb_step_KI;
    QLabel *label_53;
    QDoubleSpinBox *sb_step_KD;
    QGroupBox *groupBox_3;
    QDoubleSpinBox *sb_KP_2;
    QLabel *label_41;
    QLabel *label_56;
    QDoubleSpinBox *sb_KI_2;
    QLabel *label_57;
    QDoubleSpinBox *sb_KD_2;
    QLabel *label_58;
    QDoubleSpinBox *sb_step_KP_2;
    QLabel *label_59;
    QDoubleSpinBox *sb_step_KI_2;
    QLabel *label_60;
    QDoubleSpinBox *sb_step_KD_2;
    QWidget *com;
    QLineEdit *tbSend;
    QPushButton *btnSend;
    QPlainTextEdit *tbReceive;
    QPushButton *btn_respond_ok;
    QGroupBox *groupBox;
    QComboBox *cbCOM;
    QLabel *label;
    QLabel *label_3;
    QComboBox *cbBaud;
    QPushButton *btnOpenCOM;
    QPushButton *btnOpenServer;
    QLineEdit *tbIPAddress;
    QLabel *label_4;
    QLineEdit *tbPort;
    QLabel *label_5;
    QLineEdit *tbConnectedIP;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(662, 436);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Maintab = new QTabWidget(centralWidget);
        Maintab->setObjectName(QString::fromUtf8("Maintab"));
        Maintab->setGeometry(QRect(10, 80, 651, 301));
        modeBasic = new QWidget();
        modeBasic->setObjectName(QString::fromUtf8("modeBasic"));
        btn_change_mode_basic = new QPushButton(modeBasic);
        btn_change_mode_basic->setObjectName(QString::fromUtf8("btn_change_mode_basic"));
        btn_change_mode_basic->setGeometry(QRect(10, 10, 81, 23));
        groupBox_11 = new QGroupBox(modeBasic);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setGeometry(QRect(10, 140, 621, 131));
        label_47 = new QLabel(groupBox_11);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setGeometry(QRect(10, 30, 31, 16));
        txtBoxRoll = new QLineEdit(groupBox_11);
        txtBoxRoll->setObjectName(QString::fromUtf8("txtBoxRoll"));
        txtBoxRoll->setGeometry(QRect(40, 30, 113, 20));
        label_48 = new QLabel(groupBox_11);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setGeometry(QRect(230, 30, 31, 16));
        txtBoxPitch = new QLineEdit(groupBox_11);
        txtBoxPitch->setObjectName(QString::fromUtf8("txtBoxPitch"));
        txtBoxPitch->setGeometry(QRect(270, 30, 113, 20));
        label_54 = new QLabel(groupBox_11);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setGeometry(QRect(450, 30, 31, 16));
        txtBoxYaw = new QLineEdit(groupBox_11);
        txtBoxYaw->setObjectName(QString::fromUtf8("txtBoxYaw"));
        txtBoxYaw->setGeometry(QRect(490, 30, 113, 20));
        txtBoxVY = new QLineEdit(groupBox_11);
        txtBoxVY->setObjectName(QString::fromUtf8("txtBoxVY"));
        txtBoxVY->setGeometry(QRect(270, 70, 113, 20));
        txtBoxVX = new QLineEdit(groupBox_11);
        txtBoxVX->setObjectName(QString::fromUtf8("txtBoxVX"));
        txtBoxVX->setGeometry(QRect(40, 70, 113, 20));
        txtBoxOMEGA = new QLineEdit(groupBox_11);
        txtBoxOMEGA->setObjectName(QString::fromUtf8("txtBoxOMEGA"));
        txtBoxOMEGA->setGeometry(QRect(490, 70, 113, 20));
        label_61 = new QLabel(groupBox_11);
        label_61->setObjectName(QString::fromUtf8("label_61"));
        label_61->setGeometry(QRect(10, 70, 31, 16));
        label_62 = new QLabel(groupBox_11);
        label_62->setObjectName(QString::fromUtf8("label_62"));
        label_62->setGeometry(QRect(230, 70, 31, 16));
        label_63 = new QLabel(groupBox_11);
        label_63->setObjectName(QString::fromUtf8("label_63"));
        label_63->setGeometry(QRect(450, 70, 41, 16));
        groupBox_13 = new QGroupBox(modeBasic);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        groupBox_13->setGeometry(QRect(10, 40, 621, 101));
        label_55 = new QLabel(groupBox_13);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setGeometry(QRect(10, 30, 51, 16));
        txtBoxMPU = new QLineEdit(groupBox_13);
        txtBoxMPU->setObjectName(QString::fromUtf8("txtBoxMPU"));
        txtBoxMPU->setGeometry(QRect(70, 30, 541, 20));
        Maintab->addTab(modeBasic, QString());
        modeIMUCalibration = new QWidget();
        modeIMUCalibration->setObjectName(QString::fromUtf8("modeIMUCalibration"));
        groupBox_7 = new QGroupBox(modeIMUCalibration);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 40, 631, 231));
        tb_gx = new QLineEdit(groupBox_7);
        tb_gx->setObjectName(QString::fromUtf8("tb_gx"));
        tb_gx->setGeometry(QRect(70, 20, 91, 20));
        label_13 = new QLabel(groupBox_7);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 20, 21, 16));
        label_14 = new QLabel(groupBox_7);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(200, 20, 21, 16));
        label_15 = new QLabel(groupBox_7);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(400, 20, 21, 16));
        label_22 = new QLabel(groupBox_7);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(10, 60, 51, 16));
        label_23 = new QLabel(groupBox_7);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(200, 60, 51, 16));
        tb_gy = new QLineEdit(groupBox_7);
        tb_gy->setObjectName(QString::fromUtf8("tb_gy"));
        tb_gy->setGeometry(QRect(270, 20, 91, 20));
        tb_gz = new QLineEdit(groupBox_7);
        tb_gz->setObjectName(QString::fromUtf8("tb_gz"));
        tb_gz->setGeometry(QRect(460, 20, 91, 20));
        tb_gx_offset = new QLineEdit(groupBox_7);
        tb_gx_offset->setObjectName(QString::fromUtf8("tb_gx_offset"));
        tb_gx_offset->setGeometry(QRect(70, 60, 91, 20));
        tb_gy_offset = new QLineEdit(groupBox_7);
        tb_gy_offset->setObjectName(QString::fromUtf8("tb_gy_offset"));
        tb_gy_offset->setGeometry(QRect(270, 60, 91, 20));
        label_24 = new QLabel(groupBox_7);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(400, 60, 51, 16));
        tb_gz_offset = new QLineEdit(groupBox_7);
        tb_gz_offset->setObjectName(QString::fromUtf8("tb_gz_offset"));
        tb_gz_offset->setGeometry(QRect(460, 60, 91, 20));
        btn_gyro_calib = new QPushButton(groupBox_7);
        btn_gyro_calib->setObjectName(QString::fromUtf8("btn_gyro_calib"));
        btn_gyro_calib->setGeometry(QRect(560, 20, 61, 61));
        tb_stand_point = new QLineEdit(groupBox_7);
        tb_stand_point->setObjectName(QString::fromUtf8("tb_stand_point"));
        tb_stand_point->setGeometry(QRect(270, 100, 91, 20));
        tb_stand_point_current = new QLineEdit(groupBox_7);
        tb_stand_point_current->setObjectName(QString::fromUtf8("tb_stand_point_current"));
        tb_stand_point_current->setGeometry(QRect(70, 100, 91, 20));
        label_25 = new QLabel(groupBox_7);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(10, 100, 51, 16));
        label_26 = new QLabel(groupBox_7);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(200, 100, 61, 16));
        btn_mode_imu_write_params = new QPushButton(modeIMUCalibration);
        btn_mode_imu_write_params->setObjectName(QString::fromUtf8("btn_mode_imu_write_params"));
        btn_mode_imu_write_params->setGeometry(QRect(320, 10, 141, 23));
        btn_mode_imu_save_params = new QPushButton(modeIMUCalibration);
        btn_mode_imu_save_params->setObjectName(QString::fromUtf8("btn_mode_imu_save_params"));
        btn_mode_imu_save_params->setGeometry(QRect(490, 10, 141, 23));
        btn_change_mode_imu_calibration = new QPushButton(modeIMUCalibration);
        btn_change_mode_imu_calibration->setObjectName(QString::fromUtf8("btn_change_mode_imu_calibration"));
        btn_change_mode_imu_calibration->setGeometry(QRect(10, 10, 121, 23));
        btn_mode_imu_load_params = new QPushButton(modeIMUCalibration);
        btn_mode_imu_load_params->setObjectName(QString::fromUtf8("btn_mode_imu_load_params"));
        btn_mode_imu_load_params->setGeometry(QRect(160, 10, 131, 23));
        Maintab->addTab(modeIMUCalibration, QString());
        modePIDTunnig = new QWidget();
        modePIDTunnig->setObjectName(QString::fromUtf8("modePIDTunnig"));
        btn_change_mode_pid_tunning = new QPushButton(modePIDTunnig);
        btn_change_mode_pid_tunning->setObjectName(QString::fromUtf8("btn_change_mode_pid_tunning"));
        btn_change_mode_pid_tunning->setGeometry(QRect(10, 10, 131, 23));
        btn_mode_pidt_load_params = new QPushButton(modePIDTunnig);
        btn_mode_pidt_load_params->setObjectName(QString::fromUtf8("btn_mode_pidt_load_params"));
        btn_mode_pidt_load_params->setGeometry(QRect(170, 10, 131, 23));
        btn_mode_pidt_write_params = new QPushButton(modePIDTunnig);
        btn_mode_pidt_write_params->setObjectName(QString::fromUtf8("btn_mode_pidt_write_params"));
        btn_mode_pidt_write_params->setGeometry(QRect(330, 10, 131, 23));
        btn_mode_pidt_save_params = new QPushButton(modePIDTunnig);
        btn_mode_pidt_save_params->setObjectName(QString::fromUtf8("btn_mode_pidt_save_params"));
        btn_mode_pidt_save_params->setGeometry(QRect(490, 10, 131, 23));
        groupBox_2 = new QGroupBox(modePIDTunnig);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 40, 621, 111));
        sb_KP = new QDoubleSpinBox(groupBox_2);
        sb_KP->setObjectName(QString::fromUtf8("sb_KP"));
        sb_KP->setGeometry(QRect(30, 20, 371, 22));
        sb_KP->setMaximum(1000.000000000000000);
        sb_KP->setSingleStep(0.100000000000000);
        label_40 = new QLabel(groupBox_2);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setGeometry(QRect(10, 20, 21, 16));
        label_49 = new QLabel(groupBox_2);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        label_49->setGeometry(QRect(10, 50, 21, 16));
        sb_KI = new QDoubleSpinBox(groupBox_2);
        sb_KI->setObjectName(QString::fromUtf8("sb_KI"));
        sb_KI->setGeometry(QRect(30, 50, 371, 22));
        sb_KI->setMaximum(1000.000000000000000);
        sb_KI->setSingleStep(0.100000000000000);
        label_50 = new QLabel(groupBox_2);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setGeometry(QRect(10, 80, 21, 16));
        sb_KD = new QDoubleSpinBox(groupBox_2);
        sb_KD->setObjectName(QString::fromUtf8("sb_KD"));
        sb_KD->setGeometry(QRect(30, 80, 371, 22));
        sb_KD->setMaximum(1000.000000000000000);
        sb_KD->setSingleStep(0.100000000000000);
        label_51 = new QLabel(groupBox_2);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        label_51->setGeometry(QRect(410, 20, 31, 16));
        sb_step_KP = new QDoubleSpinBox(groupBox_2);
        sb_step_KP->setObjectName(QString::fromUtf8("sb_step_KP"));
        sb_step_KP->setGeometry(QRect(450, 20, 161, 22));
        sb_step_KP->setSingleStep(0.100000000000000);
        sb_step_KP->setValue(0.100000000000000);
        label_52 = new QLabel(groupBox_2);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        label_52->setGeometry(QRect(410, 50, 31, 16));
        sb_step_KI = new QDoubleSpinBox(groupBox_2);
        sb_step_KI->setObjectName(QString::fromUtf8("sb_step_KI"));
        sb_step_KI->setGeometry(QRect(450, 50, 161, 22));
        sb_step_KI->setSingleStep(0.100000000000000);
        sb_step_KI->setValue(0.100000000000000);
        label_53 = new QLabel(groupBox_2);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setGeometry(QRect(410, 80, 31, 16));
        sb_step_KD = new QDoubleSpinBox(groupBox_2);
        sb_step_KD->setObjectName(QString::fromUtf8("sb_step_KD"));
        sb_step_KD->setGeometry(QRect(450, 80, 161, 22));
        sb_step_KD->setSingleStep(0.100000000000000);
        sb_step_KD->setValue(0.100000000000000);
        groupBox_3 = new QGroupBox(modePIDTunnig);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 160, 621, 111));
        sb_KP_2 = new QDoubleSpinBox(groupBox_3);
        sb_KP_2->setObjectName(QString::fromUtf8("sb_KP_2"));
        sb_KP_2->setGeometry(QRect(30, 20, 371, 22));
        sb_KP_2->setSingleStep(0.100000000000000);
        label_41 = new QLabel(groupBox_3);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setGeometry(QRect(10, 20, 21, 16));
        label_56 = new QLabel(groupBox_3);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setGeometry(QRect(10, 50, 21, 16));
        sb_KI_2 = new QDoubleSpinBox(groupBox_3);
        sb_KI_2->setObjectName(QString::fromUtf8("sb_KI_2"));
        sb_KI_2->setGeometry(QRect(30, 50, 371, 22));
        sb_KI_2->setSingleStep(0.100000000000000);
        label_57 = new QLabel(groupBox_3);
        label_57->setObjectName(QString::fromUtf8("label_57"));
        label_57->setGeometry(QRect(10, 80, 21, 16));
        sb_KD_2 = new QDoubleSpinBox(groupBox_3);
        sb_KD_2->setObjectName(QString::fromUtf8("sb_KD_2"));
        sb_KD_2->setGeometry(QRect(30, 80, 371, 22));
        sb_KD_2->setSingleStep(0.100000000000000);
        label_58 = new QLabel(groupBox_3);
        label_58->setObjectName(QString::fromUtf8("label_58"));
        label_58->setGeometry(QRect(410, 20, 31, 16));
        sb_step_KP_2 = new QDoubleSpinBox(groupBox_3);
        sb_step_KP_2->setObjectName(QString::fromUtf8("sb_step_KP_2"));
        sb_step_KP_2->setGeometry(QRect(450, 20, 161, 22));
        sb_step_KP_2->setSingleStep(0.100000000000000);
        sb_step_KP_2->setValue(0.100000000000000);
        label_59 = new QLabel(groupBox_3);
        label_59->setObjectName(QString::fromUtf8("label_59"));
        label_59->setGeometry(QRect(410, 50, 31, 16));
        sb_step_KI_2 = new QDoubleSpinBox(groupBox_3);
        sb_step_KI_2->setObjectName(QString::fromUtf8("sb_step_KI_2"));
        sb_step_KI_2->setGeometry(QRect(450, 50, 161, 22));
        sb_step_KI_2->setSingleStep(0.100000000000000);
        sb_step_KI_2->setValue(0.100000000000000);
        label_60 = new QLabel(groupBox_3);
        label_60->setObjectName(QString::fromUtf8("label_60"));
        label_60->setGeometry(QRect(410, 80, 31, 16));
        sb_step_KD_2 = new QDoubleSpinBox(groupBox_3);
        sb_step_KD_2->setObjectName(QString::fromUtf8("sb_step_KD_2"));
        sb_step_KD_2->setGeometry(QRect(450, 80, 161, 22));
        sb_step_KD_2->setSingleStep(0.100000000000000);
        sb_step_KD_2->setValue(0.100000000000000);
        Maintab->addTab(modePIDTunnig, QString());
        com = new QWidget();
        com->setObjectName(QString::fromUtf8("com"));
        tbSend = new QLineEdit(com);
        tbSend->setObjectName(QString::fromUtf8("tbSend"));
        tbSend->setGeometry(QRect(10, 10, 451, 20));
        btnSend = new QPushButton(com);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setGeometry(QRect(470, 10, 81, 21));
        tbReceive = new QPlainTextEdit(com);
        tbReceive->setObjectName(QString::fromUtf8("tbReceive"));
        tbReceive->setGeometry(QRect(10, 40, 631, 231));
        btn_respond_ok = new QPushButton(com);
        btn_respond_ok->setObjectName(QString::fromUtf8("btn_respond_ok"));
        btn_respond_ok->setGeometry(QRect(560, 10, 81, 21));
        Maintab->addTab(com, QString());
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 651, 80));
        groupBox->setFlat(true);
        cbCOM = new QComboBox(groupBox);
        cbCOM->setObjectName(QString::fromUtf8("cbCOM"));
        cbCOM->setGeometry(QRect(60, 20, 171, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 31, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 50, 31, 16));
        cbBaud = new QComboBox(groupBox);
        cbBaud->setObjectName(QString::fromUtf8("cbBaud"));
        cbBaud->setGeometry(QRect(60, 50, 171, 22));
        btnOpenCOM = new QPushButton(groupBox);
        btnOpenCOM->setObjectName(QString::fromUtf8("btnOpenCOM"));
        btnOpenCOM->setGeometry(QRect(240, 22, 61, 51));
        btnOpenServer = new QPushButton(groupBox);
        btnOpenServer->setObjectName(QString::fromUtf8("btnOpenServer"));
        btnOpenServer->setGeometry(QRect(580, 20, 61, 51));
        tbIPAddress = new QLineEdit(groupBox);
        tbIPAddress->setObjectName(QString::fromUtf8("tbIPAddress"));
        tbIPAddress->setGeometry(QRect(400, 20, 121, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(310, 20, 81, 16));
        tbPort = new QLineEdit(groupBox);
        tbPort->setObjectName(QString::fromUtf8("tbPort"));
        tbPort->setGeometry(QRect(530, 20, 41, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(310, 50, 81, 16));
        tbConnectedIP = new QLineEdit(groupBox);
        tbConnectedIP->setObjectName(QString::fromUtf8("tbConnectedIP"));
        tbConnectedIP->setGeometry(QRect(400, 50, 171, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 662, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        Maintab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_change_mode_basic->setText(QApplication::translate("MainWindow", "Mode basic", nullptr));
        groupBox_11->setTitle(QApplication::translate("MainWindow", "Roll Pitch Yaw", nullptr));
        label_47->setText(QApplication::translate("MainWindow", "Roll:", nullptr));
        label_48->setText(QApplication::translate("MainWindow", "Pitch:", nullptr));
        label_54->setText(QApplication::translate("MainWindow", "Yaw:", nullptr));
        label_61->setText(QApplication::translate("MainWindow", "VX:", nullptr));
        label_62->setText(QApplication::translate("MainWindow", "VY:", nullptr));
        label_63->setText(QApplication::translate("MainWindow", "OMEGA:", nullptr));
        groupBox_13->setTitle(QApplication::translate("MainWindow", "Sensor Status", nullptr));
        label_55->setText(QApplication::translate("MainWindow", "MPU6050:", nullptr));
        Maintab->setTabText(Maintab->indexOf(modeBasic), QApplication::translate("MainWindow", "Mode Basic", nullptr));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Gyro", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Gx:", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "Gy:", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "Gz:", nullptr));
        label_22->setText(QApplication::translate("MainWindow", "Gx offset:", nullptr));
        label_23->setText(QApplication::translate("MainWindow", "Gy offset:", nullptr));
        label_24->setText(QApplication::translate("MainWindow", "Gz offset:", nullptr));
        btn_gyro_calib->setText(QApplication::translate("MainWindow", "Calibrate", nullptr));
        label_25->setText(QApplication::translate("MainWindow", "Tilt Angle:", nullptr));
        label_26->setText(QApplication::translate("MainWindow", "Offset:", nullptr));
        btn_mode_imu_write_params->setText(QApplication::translate("MainWindow", "Write gyro offset", nullptr));
        btn_mode_imu_save_params->setText(QApplication::translate("MainWindow", "Save params", nullptr));
        btn_change_mode_imu_calibration->setText(QApplication::translate("MainWindow", "Mode IMU Calibration", nullptr));
        btn_mode_imu_load_params->setText(QApplication::translate("MainWindow", "Load params", nullptr));
        Maintab->setTabText(Maintab->indexOf(modeIMUCalibration), QApplication::translate("MainWindow", "Mode IMU Calibration", nullptr));
        btn_change_mode_pid_tunning->setText(QApplication::translate("MainWindow", "Mode PID tunnning", nullptr));
        btn_mode_pidt_load_params->setText(QApplication::translate("MainWindow", "Load params", nullptr));
        btn_mode_pidt_write_params->setText(QApplication::translate("MainWindow", "Write params", nullptr));
        btn_mode_pidt_save_params->setText(QApplication::translate("MainWindow", "Save params", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Stability Control", nullptr));
        label_40->setText(QApplication::translate("MainWindow", "KP:", nullptr));
        label_49->setText(QApplication::translate("MainWindow", "KI:", nullptr));
        label_50->setText(QApplication::translate("MainWindow", "KD:", nullptr));
        label_51->setText(QApplication::translate("MainWindow", "Step:", nullptr));
        label_52->setText(QApplication::translate("MainWindow", "Step:", nullptr));
        label_53->setText(QApplication::translate("MainWindow", "Step:", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Speed Control", nullptr));
        label_41->setText(QApplication::translate("MainWindow", "KP:", nullptr));
        label_56->setText(QApplication::translate("MainWindow", "KI:", nullptr));
        label_57->setText(QApplication::translate("MainWindow", "KD:", nullptr));
        label_58->setText(QApplication::translate("MainWindow", "Step:", nullptr));
        label_59->setText(QApplication::translate("MainWindow", "Step:", nullptr));
        label_60->setText(QApplication::translate("MainWindow", "Step:", nullptr));
        Maintab->setTabText(Maintab->indexOf(modePIDTunnig), QApplication::translate("MainWindow", "Mode PID Tunning", nullptr));
        btnSend->setText(QApplication::translate("MainWindow", "Send", nullptr));
        btn_respond_ok->setText(QApplication::translate("MainWindow", "Respond OK", nullptr));
        Maintab->setTabText(Maintab->indexOf(com), QApplication::translate("MainWindow", "COM", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Connection", nullptr));
        label->setText(QApplication::translate("MainWindow", "COM:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Baud:", nullptr));
        btnOpenCOM->setText(QApplication::translate("MainWindow", "Open", nullptr));
        btnOpenServer->setText(QApplication::translate("MainWindow", "Open", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Sever address:", nullptr));
        tbPort->setText(QApplication::translate("MainWindow", "9000", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Connected from:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
