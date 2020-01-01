#ifndef MODE_IMU_H
#define MODE_IMU_H

#include <QWidget>
#include <QtWidgets/QStatusBar>

#include <MAV/protocol/mavlink.h>
#include <com.h>

namespace Ui {
class Mode_imu;
}

class Mode_imu : public QWidget
{
    Q_OBJECT

public:
    explicit Mode_imu(QWidget *parent = nullptr);
    ~Mode_imu();

    void mode_imu_mav_recv(mavlink_message_t *msg);
    void set_status_bar(QStatusBar *q_status_bar);

signals:
    void mode_imu_mav_send(QByteArray ba);
    void mode_change(rmode_t mode);

private slots:
    void mode_imu_load_timeout();
    void mode_imu_write_timeout();
    void mode_imu_save_timeout();

    void on_btn_mode_imu_load_params_clicked();
    void on_btn_mode_imu_write_params_clicked();
    void on_btn_mode_imu_save_params_clicked();

    void on_btn_gyro_calib_clicked();
    void on_btn_change_mode_imu_clicked();

private:
    Ui::Mode_imu *ui;
    QStatusBar *g_q_status_bar = nullptr;

    int16_t g_gx_offset;
    int16_t g_gy_offset;
    int16_t g_gz_offset;
    float g_angle_adjust;
    float g_gbelive;
    bool g_is_imu_calibrating = false;
    bool g_does_st_successfullly = false;

    void show_status(QString q_str, int timeout);
};

#endif // MODE_IMU_H
