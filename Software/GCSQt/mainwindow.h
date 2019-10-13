#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include "MAV/protocol/mavlink.h"
#include "ledindicator.h"

#define MAV_BUFF_SIZE 256

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

//    typedef void (*func_t)(void);
//    typedef void (*on_mav_recv_t)(mavlink_message_t*);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOpenCOM_clicked();
    void on_btnSend_clicked();
    void on_COMData_ready();
    void on_btnOpenServer_clicked();
    void on_newConnection();
    void on_ReadyRead();
    void on_SocketStateChanged(QAbstractSocket::SocketState socketState);

    void on_btn_change_mode_basic_clicked();
    void on_btn_change_mode_imu_calibration_clicked();
    void on_btn_change_mode_pid_tunning_clicked();
    void app_command_timeout();

    void ledIndicatorOff();

    void mode_pidt_load_timeout();
    void mode_pidt_write_timeout();
    void mode_pidt_save_timeout();

    void mode_imu_load_timeout();
    void mode_imu_write_timeout();
    void mode_imu_save_timeout();

    void on_btn_mode_pidt_load_params_clicked();

    void on_btn_respond_ok_clicked();

    void on_btn_mode_pidt_write_params_clicked();

    void on_sb_step_KP_valueChanged(const QString &arg1);

    void on_sb_step_KI_valueChanged(const QString &arg1);

    void on_sb_KD_valueChanged(const QString &arg1);

    void on_btn_mode_pidt_save_params_clicked();

    void on_btn_mode_imu_load_params_clicked();

    void on_btn_mode_imu_write_params_clicked();

    void on_btn_mode_imu_save_params_clicked();

    void on_btn_gyro_calib_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial;
    QTcpServer *tcpServer;
    QTcpSocket *socket;
    LedIndicator *ledIndicator;


    uint8_t mavbuf[MAV_BUFF_SIZE];
    mavlink_message_t msg;
    mavlink_status_t  status;
    bool isChangeMode = false;
    bool changeModeSuccess = false;
    robot_mode_t changeToMode = MODE_BASIC;
    robot_mode_t currentMode = MODE_BASIC;
    bool isDoStSuccessfull = false;
    int16_t gx_offset;
    int16_t gy_offset;
    int16_t gz_offset;
    float stand_point;
    bool is_imu_calibrating = false;

    bool send(QByteArray bytes);
    void receive(QByteArray bytes);
    QString ByteArrayToString(QByteArray ba);
    void showStatus(QString qstr, int timeout);

    void app_main_init();
    void app_main_on_data_recv(QByteArray bytes);
    void app_command_change_mode(robot_mode_t mode);
    void on_mode_basic_mav_recv(mavlink_message_t *msg);

    void load_pid_params();
    void write_pid_params();
    void save_pid_params();
    void on_mode_pidt_mav_recv(mavlink_message_t *msg);

    void on_mode_imu_mav_recv(mavlink_message_t *msg);
};

#endif // MAINWINDOW_H
