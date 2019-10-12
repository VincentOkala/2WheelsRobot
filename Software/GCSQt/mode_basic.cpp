#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_mode_basic_mav_recv(mavlink_message_t *msg){
    switch(msg->msgid) {
    case MAVLINK_MSG_ID_EVT_RPY:
        mavlink_evt_rpy_t evt_rpy;
        mavlink_msg_evt_rpy_decode(msg, &evt_rpy);
        ui->txtBoxRoll->setText(QString::number(evt_rpy.roll));
        ui->txtBoxPitch->setText(QString::number(evt_rpy.pitch));
        break;
    case MAVLINK_MSG_ID_EVT_SENSOR_STATUS:
        mavlink_evt_sensor_status_t sensor_status;
        mavlink_msg_evt_sensor_status_decode(msg,&sensor_status);
        if(sensor_status.imu_status == SENSOR_STATUS_IMU_OK){
            ui->txtBoxMPU->setText("GOOD");
        }
        else{
            ui->txtBoxMPU->setText("BAD");
        }
        break;
    }
}
