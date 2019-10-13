#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::app_main_on_data_recv(QByteArray bytes){
    for(uint16_t i = 0; i < bytes.size(); i++){
        uint8_t msg_received = mavlink_parse_char(MAVLINK_COMM_0, bytes[i], &msg, &status);
        if(msg_received == 1){
            qDebug() << "recv msgid: " << msg.msgid;
            if(msg.msgid == MAVLINK_MSG_ID_EVT_RESPOND && isChangeMode){
                isChangeMode = false;
                mavlink_evt_respond_t evt_respond;
                mavlink_msg_evt_respond_decode(&msg, &evt_respond);
                if(evt_respond.EVT_RESPOND == RESPOND_OK){
                    changeModeSuccess = true;
                    showStatus("Succeed to change mode",3000);
                    switch (changeToMode) {
                    case MODE_BASIC:
                        currentMode = MODE_BASIC;
                        break;
                    case MODE_IMU_CALIBRATION:
                        currentMode = MODE_IMU_CALIBRATION;
                        break;
                    case MODE_PID_TUNNING:
                        currentMode = MODE_PID_TUNNING;
                        break;
                    default:
                        break;
                    }
                }
            }
            else{
                switch (currentMode) {
                case MODE_BASIC:
                    on_mode_basic_mav_recv(&msg);
                    break;
                case MODE_IMU_CALIBRATION:
                    on_mode_imu_mav_recv(&msg);
                    break;
                case MODE_PID_TUNNING:
                    on_mode_pidt_mav_recv(&msg);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void MainWindow::app_main_init(){
    currentMode = MODE_BASIC;
}

void MainWindow::app_command_timeout(){
    isChangeMode = false;
    if(!changeModeSuccess){
        showStatus("Unable to change mode",3000);
    }
}

void MainWindow::app_command_change_mode(robot_mode_t mode){
    isChangeMode = true;
    changeToMode = mode;
    changeModeSuccess = false;
    mavlink_message_t msg;
    uint8_t gmav_send_buf[255];
    mavlink_msg_cmd_change_mode_pack(0,0,&msg, mode);
    uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
    if(send(QByteArray::fromRawData((char*)(gmav_send_buf),len))){
         showStatus("Requesting to change mode",1000);
         QTimer::singleShot(2000, this, SLOT(app_command_timeout()));
    }
    else{
        showStatus("Cannot request to change mode",1000);
    }
}

void MainWindow::on_btn_change_mode_basic_clicked()
{
    app_command_change_mode(MODE_BASIC);
}

void MainWindow::on_btn_change_mode_imu_calibration_clicked()
{
    app_command_change_mode(MODE_IMU_CALIBRATION);
}

void MainWindow::on_btn_change_mode_pid_tunning_clicked()
{
     app_command_change_mode(MODE_PID_TUNNING);
}
