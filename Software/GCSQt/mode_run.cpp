#include "mode_run.h"
#include "ui_mode_run.h"

Mode_run::Mode_run(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mode_run)
{
    ui->setupUi(this);
}

Mode_run::~Mode_run()
{
    delete ui;
}

void Mode_run::mav_recv(mavlink_message_t *msg){
    switch(msg->msgid) {
    case MAVLINK_MSG_ID_EVT_RPY:
        mavlink_evt_rpy_t evt_rpy;
        mavlink_msg_evt_rpy_decode(msg, &evt_rpy);
        ui->txtBoxRoll->setText(QString::number(evt_rpy.roll));
        ui->txtBoxPitch->setText(QString::number(evt_rpy.pitch));
        break;
    case MAVLINK_MSG_ID_EVT_SENSOR:
        mavlink_evt_sensor_t sensor_status;
        mavlink_msg_evt_sensor_decode(msg,&sensor_status);
        if(sensor_status.imu_status == SENSOR_IMU_OK){
//            ui->statusBar->showMessage("IMU OK", 1000);
        }
        else{
//           ui->statusBar->showMessage("IMU ERROR", 1000);
        }
        break;
    case MAVLINK_MSG_ID_EVT_TILT:
        mavlink_evt_tilt_t tilt_msg;
        mavlink_msg_evt_tilt_decode(msg,&tilt_msg);
//        on_tilt_recv(tilt_msg.tilt);
        break;
    }
}

void Mode_run::controller_cmd(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    int16_t VX = ui->txtBoxVX->text().toDouble()*100;
    int16_t OMEGA = ui->txtBoxOMEGA->text().toDouble()*100;
//    qDebug() << VX << " " << OMEGA;
    mavlink_msg_cmd_velocity_pack(0,0,&msg,VX,OMEGA);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    send(QByteArray::fromRawData((char*)(mav_send_buf),len));
}

void Mode_run::on_btn_control_enable_clicked()
{
    if(control_enable == false){
        control_enable=true;
        ui->btn_control_enable->setText("Enabled");
//        connect(controller_timer, SIGNAL(timeout()), this, SLOT(on_controller_pidt()));
//        controller_timer->start(100);
    }
    else{
        control_enable = false;
        ui->btn_control_enable->setText("Disabled");
//        controller_timer->stop();
    }
}
