#ifndef MODE_PIDT_TW_H
#define MODE_PIDT_TW_H

#include <QWidget>
#include <QTimer>
#include <QtWidgets/QStatusBar>

#include <MAV/protocol/mavlink.h>

namespace Ui {
class Mode_pidt_tw;
}

class Mode_pidt_tw : public QWidget
{
    Q_OBJECT

public:
    explicit Mode_pidt_tw(QWidget *parent = nullptr);
    ~Mode_pidt_tw();
    void mode_pidt_mav_recv(mavlink_message_t *msg);
    void set_status_bar(QStatusBar *q_status_bar);

signals:
    void mode_pidt_mav_send(QByteArray ba);
    void mode_change(rmode_t mode);

private slots:
    void mode_pidt_load_timeout();
    void mode_pidt_write_timeout();
    void mode_pidt_save_timeout();
    void remote_control_pidt();

    void on_btn_mode_pidt_load_params_clicked();
    void on_btn_mode_pidt_write_params_clicked();
    void on_btn_mode_pidt_save_params_clicked();

    void on_btn_mode_pidt_write_params_pidt_tilt_clicked();
    void on_btn_mode_pidt_write_params_pidt_vel_clicked();
    void on_btn_mode_pidt_write_params_pidt_pos_clicked();

    void on_btn_control_enable_clicked();

    void on_sb_pid_tilt_kp_step_valueChanged(double arg1);
    void on_sb_pid_tilt_ki_step_valueChanged(double arg1);
    void on_sb_pid_tilt_kd_step_valueChanged(double arg1);

    void on_sb_pid_vel_kp_step_valueChanged(double arg1);
    void on_sb_pid_vel_ki_step_valueChanged(double arg1);
    void on_sb_pid_vel_kd_step_valueChanged(double arg1);

    void on_sb_pid_pos_kp_step_valueChanged(double arg1);
    void on_sb_pid_pos_ki_step_valueChanged(double arg1);
    void on_sb_pid_pos_kd_step_valueChanged(double arg1);

    void on_btn_change_mode_pidt_clicked();

private:
    Ui::Mode_pidt_tw *ui;
    QStatusBar *g_q_status_bar = nullptr;
    QTimer *g_controller_timer;

    bool g_does_st_successfullly = false;
    bool g_control_enable = false;

    void show_status(QString q_str, int timeout);
};

#endif // MODE_PIDT_TW_H
