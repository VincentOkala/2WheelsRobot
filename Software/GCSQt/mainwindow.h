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
#include <QtGamepad/QGamepad>

#include "MAV/protocol/mavlink.h"
#include "ledindicator.h"
#include <QJoysticks.h>
#include <qcustomplot/qcustomplot.h>

#define MAV_BUFF_SIZE   256
#define PID_VECTOR_LEN  40

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

    void mode_hw_load_timeout();
    void mode_hw_write_timeout();
    void mode_hw_save_timeout();

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

    void on_js_axis_change(const int js, const int axis, const qreal value);
    void on_controller_cmd();
    void on_controller_pidt();

    void on_btn_change_mode_hw_clicked();


    void on_btn_mode_hw_load_params_clicked();

    void on_btn_mode_hw_write_params_clicked();

    void on_btn_mode_hw_save_params_clicked();

    void on_btn_set_duty0_clicked();

    void on_btn_set_duty1_clicked();

    void on_btn_set_speed0_clicked();

    void on_btn_set_speed1_clicked();

    void on_btn_control_enable_clicked();

    void on_btn_mode_pidt_write_params_pid_whe0_clicked();

    void on_btn_mode_pidt_write_params_pid_whe1_clicked();

    void on_btn_mode_pidt_write_params_pid_sync_clicked();

    void on_btn_control_enable_2_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial;
    QTcpServer *tcpServer;
    QTcpSocket *socket;
    LedIndicator *ledIndicator;
    QJoysticks* qjs;
    QTimer *controller_timer;
    QVector<double> tilt_x, tilt_y;

    QVector<double> pid_w0_x, pid_w0_sp_y, pid_w0_fb_y, pid_w0_p_y, pid_w0_i_y, pid_w0_d_y, pid_w0_u_y;
    QVector<double> pid_w1_x, pid_w1_sp_y, pid_w1_fb_y, pid_w1_p_y, pid_w1_i_y, pid_w1_d_y, pid_w1_u_y;
    QVector<double> pid_s_x, pid_s_sp_y, pid_s_fb_y, pid_s_p_y, pid_s_i_y, pid_s_d_y, pid_s_u_y;

    uint8_t mavbuf[MAV_BUFF_SIZE];
    mavlink_message_t msg;
    mavlink_status_t  status;
    bool isChangeMode = false;
    bool changeModeSuccess = false;
    rmode_t changeToMode = MODE_RUN;
    rmode_t currentMode = MODE_RUN;
    bool isDoStSuccessfull = false;
    int16_t gx_offset;
    int16_t gy_offset;
    int16_t gz_offset;
    float angle_adjust,gbelive;
    bool is_imu_calibrating = false;
    bool control_enable = false;

    bool send(QByteArray bytes);
    void receive(QByteArray bytes);
    QString ByteArrayToString(QByteArray ba);
    void showStatus(QString qstr, int timeout);

    void app_main_init();
    void app_main_on_data_recv(QByteArray bytes);
    void app_command_change_mode(rmode_t mode);
    void on_mode_basic_mav_recv(mavlink_message_t *msg);

    void load_pid_params();
    void write_pid_params();
    void save_pid_params();
    void on_mode_pidt_mav_recv(mavlink_message_t *msg);

    void on_mode_imu_mav_recv(mavlink_message_t *msg);
    void on_tilt_recv(float tilt);

    void load_hw_params();
    void write_hw_params();
    void save_hw_params();
    void on_mode_hw_mav_recv(mavlink_message_t *msg);
    void on_btn_set_duty();

    void on_pid_report_recv(mavlink_message_t *msg);

    void truncate_vector(QVector<double> &v);

    void pid_w0_plot(uint32_t len);
    void pid_w1_plot(uint32_t len);
    void pid_sync_plot(uint32_t len);


};

#endif // MAINWINDOW_H
