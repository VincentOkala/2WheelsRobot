#include "mode_common.h"

Mode_common::Mode_common(QWidget *parent) : QWidget(parent)
{

}

Mode_common::~Mode_common()
{

}

void Mode_common::mav_recv(mavlink_message_t *msg){
    Q_UNUSED(msg)
    show_status("Mav receive is not implement yet", 1000);
}

void Mode_common::set_status_bar(QStatusBar *q_status_bar){
    g_q_status_bar = q_status_bar;
}

void Mode_common::show_status(QString q_str, int timeout){
    if(g_q_status_bar != nullptr){
        g_q_status_bar->showMessage(q_str,timeout);
    }
}

void Mode_common::load_timeout(){
    if(!g_does_st_successfullly){
        g_does_st_successfullly = true;
        show_status("Unable to load imu params",2000);
    }
}

void Mode_common::write_timeout(){
    if(!g_does_st_successfullly){
        g_does_st_successfullly = true;
        show_status("Unable to write imu params",2000);
    }
}

void Mode_common::save_timeout(){
    if(!g_does_st_successfullly){
        g_does_st_successfullly = true;
        show_status("Unable to save imu params",2000);
    }
}

void Mode_common::load_params(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_cmd_params_pack(0,0,&msg,CMD_LOAD);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);

    emit mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));
    show_status("Loading hardware params",1000);
    g_does_st_successfullly = false;
    QTimer::singleShot(1000, this, SLOT(load_timeout()));
}

void Mode_common::save_params(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_cmd_params_pack(0,0,&msg,CMD_SAVE);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);

    emit mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));
    g_does_st_successfullly = false;
    QTimer::singleShot(1000, this, SLOT(mode_hw_save_timeout()));
}

