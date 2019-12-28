#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_mode_hw_mav_recv(mavlink_message_t *msg){
    switch(msg->msgid) {
    case MAVLINK_MSG_ID_MOTOR_SPEED:
        mavlink_motor_speed_t motor_speed_msg;
        mavlink_msg_motor_speed_decode(msg, &motor_speed_msg);
        ui->txtb_enc0_speed->setText(QString::number(motor_speed_msg.motor_speed_0));
        ui->txtb_enc1_speed->setText(QString::number(motor_speed_msg.motor_speed_1));
        break;
    case MAVLINK_MSG_ID_RESPOND:
        if(isDoStSuccessfull == false){
            mavlink_respond_t evt_respond;
            mavlink_msg_respond_decode(msg,&evt_respond);
            if(evt_respond.respond == RESPOND_OK){
                isDoStSuccessfull = true;
                showStatus("Succeed to write or save params",2000);
            }
        }
        break;
    case MAVLINK_MSG_ID_HW_PARAMS:
        {
            mavlink_hw_params_t hw_params_msg;
            mavlink_msg_hw_params_decode(msg,&hw_params_msg);
            ui->cb_motor0_invert->setCheckState(hw_params_msg.motor0_invert == MAV_TRUE  ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
            ui->cb_motor1_invert->setCheckState(hw_params_msg.motor1_invert == MAV_TRUE  ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
            ui->cb_enc0_invert->setCheckState(hw_params_msg.encoder0_invert == MAV_TRUE  ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
            ui->cb_enc1_invert->setCheckState(hw_params_msg.encoder1_invert == MAV_TRUE  ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
            ui->cb_enc_exchange->setCheckState(hw_params_msg.encoder_exchange == MAV_TRUE  ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
            isDoStSuccessfull = true;
        }
        break;
    }
}

void MainWindow::on_btn_set_duty(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    int32_t motor0_duty = ui->txtb_motor0_duty->text().toInt();
    int32_t motor1_duty = ui->txtb_motor1_duty->text().toInt();

    mavlink_msg_motor_speed_pack(0,0,&msg,motor0_duty,motor1_duty);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    send(QByteArray::fromRawData((char*)(mav_send_buf),len));
}

void MainWindow::mode_hw_load_timeout(){
    if(!isDoStSuccessfull){
        isDoStSuccessfull = true;
        showStatus("Unable to load PID params",2000);
    }
}

void MainWindow::mode_hw_write_timeout(){
    if(!isDoStSuccessfull){
        isDoStSuccessfull = true;
        showStatus("Unable to write PID params",2000);
    }
}

void MainWindow::mode_hw_save_timeout(){
    if(!isDoStSuccessfull){
        isDoStSuccessfull = true;
        showStatus("Unable to save PID params",2000);
    }
}

void MainWindow::on_btn_set_duty1_clicked()
{
    on_btn_set_duty();
}
void MainWindow::on_btn_set_duty0_clicked()
{
    on_btn_set_duty();
}


void MainWindow::load_hw_params(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_cmd_params_pack(0,0,&msg,CMD_LOAD);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
        showStatus("Loading hardware params",1000);
   }
   else{
       showStatus("Cannot load hardware params",1000);
   }
   isDoStSuccessfull = false;
   QTimer::singleShot(1000, this, SLOT(mode_hw_load_timeout()));
}

void MainWindow::write_hw_params(){

    mavlink_message_t msg;
    uint8_t mav_send_buf[255];

    int8_t motor0_invert = ui->cb_motor0_invert->checkState() == Qt::CheckState::Checked ? MAV_TRUE : MAV_FALSE;
    int8_t motor1_invert = ui->cb_motor1_invert->checkState() == Qt::CheckState::Checked ? MAV_TRUE : MAV_FALSE;
    int8_t encoder0_invert = ui->cb_enc0_invert->checkState() == Qt::CheckState::Checked ? MAV_TRUE : MAV_FALSE;
    int8_t encoder1_invert = ui->cb_enc1_invert->checkState() == Qt::CheckState::Checked ? MAV_TRUE : MAV_FALSE;
    int8_t encoder_ex = ui->cb_enc_exchange->checkState() == Qt::CheckState::Checked ? MAV_TRUE : MAV_FALSE;

    mavlink_msg_hw_params_pack(0,0,&msg,motor0_invert,motor1_invert,encoder0_invert,encoder1_invert, encoder_ex);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
        showStatus("Writing hardware params",1000);
   }
   else{
       showStatus("Cannot hardware params",1000);
   }
   isDoStSuccessfull = false;
   QTimer::singleShot(1000, this, SLOT(mode_hw_write_timeout()));
}

void MainWindow::save_hw_params(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_cmd_params_pack(0,0,&msg,CMD_SAVE);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
        showStatus("Saving gyro offset params",1000);
   }
   else{
       showStatus("Cannot save gyro offset params",1000);
   }
   isDoStSuccessfull = false;
   QTimer::singleShot(1000, this, SLOT(mode_hw_save_timeout()));
}

void MainWindow::on_btn_mode_hw_load_params_clicked()
{
    if(currentMode == MODE_HW){
        load_hw_params();
    }
    else{
        showStatus("Change mode to hardware first",2000);
    }
}

void MainWindow::on_btn_mode_hw_write_params_clicked()
{
    if(currentMode == MODE_HW){
        write_hw_params();
    }
    else{
        showStatus("Change mode to hardware first",2000);
    }
}

void MainWindow::on_btn_mode_hw_save_params_clicked()
{
    if(currentMode == MODE_HW){
        save_hw_params();
    }
    else{
        showStatus("Change mode to hardware first",2000);
    }
}
