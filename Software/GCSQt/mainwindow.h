#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QtGamepad/QGamepad>

#include "MAV/protocol/mavlink.h"
#include "led_indicator.h"
#include <QJoysticks.h>
#include <qcustomplot/qcustomplot.h>

#include <com.h>
#include <mode_run.h>
#include <mode_imu.h>
#include <mode_pidt_tw.h>

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

    void mode_pidt_load_timeout();
    void mode_pidt_write_timeout();
    void mode_pidt_save_timeout();

    void mode_hw_load_timeout();
    void mode_hw_write_timeout();
    void mode_hw_save_timeout();

    void on_sb_step_KP_valueChanged(const QString &arg1);
    void on_sb_step_KI_valueChanged(const QString &arg1);
    void on_sb_KD_valueChanged(const QString &arg1);


    void on_controller_cmd();
    void on_controller_pidt();


    void on_btn_set_duty0_clicked();

    void on_btn_set_duty1_clicked();

    void on_btn_set_speed0_clicked();

    void on_btn_set_speed1_clicked();

    void on_btn_mode_pidt_write_params_pid_whe0_clicked();

    void on_btn_mode_pidt_write_params_pid_whe1_clicked();

    void on_btn_mode_pidt_write_params_pid_sync_clicked();


    // Com
    void app_main_on_data_recv(QByteArray bytes);
    void com_connection_evt(Com::com_evt_t evt);

    // Joystick
    void js_axis_change(const int js, const int axis, const qreal value);

    // Mode
    void app_command_change_mode(rmode_t mode);
    void app_command_change_mode_timeout();

    // Mode messgage forward
    void app_main_message_forward(QByteArray bytes);

private:
    Ui::MainWindow *ui;

    QJoysticks *g_qjs;
    Com_gui *g_com_gui;
    Led_indicator *g_led_indicator;

    Mode_run *g_mode_run;
    Mode_imu *g_mode_imu;
    Mode_pidt_tw *g_mode_pidt_tw;

    bool g_is_changing_mode = false;
    rmode_t g_change_to_mode = MODE_RUN;
    rmode_t g_current_mode = MODE_RUN;
    bool g_change_mode_success = false;

    QTimer *controller_timer;
    QVector<double> tilt_x, tilt_y;

    QVector<double> pid_w0_x, pid_w0_sp_y, pid_w0_fb_y, pid_w0_p_y, pid_w0_i_y, pid_w0_d_y, pid_w0_u_y;
    QVector<double> pid_w1_x, pid_w1_sp_y, pid_w1_fb_y, pid_w1_p_y, pid_w1_i_y, pid_w1_d_y, pid_w1_u_y;
    QVector<double> pid_s_x, pid_s_sp_y, pid_s_fb_y, pid_s_p_y, pid_s_i_y, pid_s_d_y, pid_s_u_y;

    uint8_t mavbuf[MAV_BUFF_SIZE];
    mavlink_message_t msg;
    mavlink_status_t  status;

    bool isDoStSuccessfull = false;


    void show_status(QString qstr, int timeout);

    void app_main_init();


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
