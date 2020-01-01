#include "mode_run.h"
#include "ui_mode_run.h"

Mode_run::Mode_run(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mode_run)
{
    ui->setupUi(this);
    g_controller_timer = new QTimer(this);
    connect(g_controller_timer, SIGNAL(timeout()), this, SLOT(remote_controll_cmd()));
}

Mode_run::~Mode_run()
{
    delete ui;
}

void Mode_run::set_status_bar(QStatusBar *q_status_bar){
    g_q_status_bar = q_status_bar;
}

void Mode_run::show_status(QString q_str, int timeout){
    if(g_q_status_bar != nullptr){
        g_q_status_bar->showMessage(q_str,timeout);
    }
}

void Mode_run::mode_run_mav_recv(mavlink_message_t *msg){
    switch(msg->msgid) {
    case MAVLINK_MSG_ID_EVT_RPY:
        mavlink_evt_rpy_t evt_rpy;
        mavlink_msg_evt_rpy_decode(msg, &evt_rpy);
        ui->txtBoxRoll->setText(QString::number(static_cast<double>(evt_rpy.roll)));
        ui->txtBoxPitch->setText(QString::number(static_cast<double>(evt_rpy.pitch)));
        break;
    case MAVLINK_MSG_ID_EVT_SENSOR:
        mavlink_evt_sensor_t sensor_status;
        mavlink_msg_evt_sensor_decode(msg,&sensor_status);
        if(sensor_status.imu_status == SENSOR_IMU_OK){
            show_status("IMU OK", 1000);
        }
        else{
            show_status("IMU ERROR", 1000);
        }
        break;
    case MAVLINK_MSG_ID_EVT_TILT:
        mavlink_evt_tilt_t tilt_msg;
        mavlink_msg_evt_tilt_decode(msg,&tilt_msg);
        // on_tilt_recv(tilt_msg.tilt);
        break;
    }
}

void Mode_run::remote_controll_cmd(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    int16_t VX = static_cast<int16_t>(ui->txtBoxVX->text().toDouble()*100);
    int16_t OMEGA = static_cast<int16_t>(ui->txtBoxOMEGA->text().toDouble()*100);

    mavlink_msg_cmd_velocity_pack(0,0,&msg,VX,OMEGA);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);

    emit mode_run_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));
}

void Mode_run::on_btn_control_enable_clicked()
{
    if(g_control_enable == false){
        g_control_enable=true;
        ui->btn_control_enable->setText("Enabled");
        g_controller_timer->start(100);
    }
    else{
        g_control_enable = false;
        ui->btn_control_enable->setText("Disabled");
        g_controller_timer->stop();
    }
}

void Mode_run::on_btn_change_mode_run_clicked()
{
    emit mode_change(MODE_RUN);
}
