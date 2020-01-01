#include "mode_pidt_tw.h"
#include "ui_mode_pidt_tw.h"

Mode_pidt_tw::Mode_pidt_tw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mode_pidt_tw)
{
    ui->setupUi(this);
    g_controller_timer = new QTimer(this);
    connect(g_controller_timer, SIGNAL(timeout()), this, SLOT(remote_control_pidt()));
}

Mode_pidt_tw::~Mode_pidt_tw()
{
    delete ui;
}

void Mode_pidt_tw::set_status_bar(QStatusBar *q_status_bar){
    g_q_status_bar = q_status_bar;
}

void Mode_pidt_tw::show_status(QString q_str, int timeout){
    if(g_q_status_bar != nullptr){
        g_q_status_bar->showMessage(q_str,timeout);
    }
}

void Mode_pidt_tw::mode_pidt_mav_recv(mavlink_message_t *msg){
    switch(msg->msgid) {
    case MAVLINK_MSG_ID_PID_PARAMS:
        if(g_does_st_successfullly == false){
            g_does_st_successfullly = true;
            mavlink_pid_params_t pid;
            mavlink_msg_pid_params_decode(msg, &pid);
            show_status("Succeed to load PID params",2000);
            switch (pid.pid_control) {
                case PID_WHE0:
                    ui->sb_pid_tilt_kp->setValue(static_cast<double>(pid.KP));
                    ui->sb_pid_tilt_ki->setValue(static_cast<double>(pid.KI));
                    ui->sb_pid_tilt_kd->setValue(static_cast<double>(pid.KD));
                break;
                case PID_WHE1:
                    ui->sb_pid_vel_kp->setValue(static_cast<double>(pid.KP));
                    ui->sb_pid_vel_ki->setValue(static_cast<double>(pid.KI));
                    ui->sb_pid_vel_kd->setValue(static_cast<double>(pid.KD));
                break;
                case PID_SYNC:
                    ui->sb_pid_pos_kp->setValue(static_cast<double>(pid.KP));
                    ui->sb_pid_pos_ki->setValue(static_cast<double>(pid.KI));
                    ui->sb_pid_pos_kd->setValue(static_cast<double>(pid.KD));
                break;
            }
        }
        break;
    case MAVLINK_MSG_ID_RESPOND:
        if(g_does_st_successfullly == false){
            mavlink_respond_t evt_respond;
            mavlink_msg_respond_decode(msg,&evt_respond);
            if(evt_respond.respond == RESPOND_OK){
                g_does_st_successfullly = true;
                show_status("Succeed to write or save params",2000);
            }
        }
        break;
    case MAVLINK_MSG_ID_EVT_TILT:
        mavlink_evt_tilt_t tilt_msg;
        mavlink_msg_evt_tilt_decode(msg,&tilt_msg);
//        on_tilt_recv(tilt_msg.tilt);
        break;
    case MAVLINK_MSG_ID_PID_REPORT:
//        on_pid_report_recv(msg);
        break;
    }
}

//void truncate_vector(QVector<double> &v){
//    if(v.size() > PID_VECTOR_LEN){
//        v.pop_front();
//    }
//}

//void pid_w0_plot(uint32_t len){
//    double min_y, max_y;

//    min_y = *std::min_element(pid_w0_p_y.constBegin(), pid_w0_p_y.constEnd());
//    min_y = std::min(min_y, *std::min_element(pid_w0_i_y.constBegin(), pid_w0_i_y.constEnd()));
//    min_y = std::min(min_y, *std::min_element(pid_w0_d_y.constBegin(), pid_w0_d_y.constEnd()));
//    min_y = std::min(min_y, *std::min_element(pid_w0_u_y.constBegin(), pid_w0_u_y.constEnd()));
//    max_y = *std::max_element(pid_w0_p_y.constBegin(), pid_w0_p_y.constEnd());
//    max_y = std::max(max_y, *std::max_element(pid_w0_i_y.constBegin(), pid_w0_i_y.constEnd()));
//    max_y = std::max(max_y, *std::max_element(pid_w0_d_y.constBegin(), pid_w0_d_y.constEnd()));
//    max_y = std::max(max_y, *std::max_element(pid_w0_u_y.constBegin(), pid_w0_u_y.constEnd()));
//    ui->plot_0->xAxis->setRange(len-PID_VECTOR_LEN, len);
//    ui->plot_0->yAxis->setRange(min_y-10,max_y+10);
//    ui->plot_0->graph(0)->setData(pid_w0_x,pid_w0_p_y);
//    ui->plot_0->graph(1)->setData(pid_w0_x,pid_w0_i_y);
//    ui->plot_0->graph(2)->setData(pid_w0_x,pid_w0_d_y);
//    ui->plot_0->graph(3)->setData(pid_w0_x,pid_w0_u_y);
//    ui->plot_0->replot();

//    min_y = *std::min_element(pid_w0_sp_y.constBegin(), pid_w0_sp_y.constEnd());
//    min_y = std::min(min_y, *std::min_element(pid_w0_fb_y.constBegin(), pid_w0_fb_y.constEnd()));
//    max_y = *std::max_element(pid_w0_sp_y.constBegin(), pid_w0_sp_y.constEnd());
//    max_y = std::max(max_y, *std::max_element(pid_w0_fb_y.constBegin(), pid_w0_fb_y.constEnd()));
//    min_y = min_y < 0 ? -150 : min_y;
//    max_y = max_y > 0 ? 150 : max_y;
//    ui->plot_1->xAxis->setRange(len-PID_VECTOR_LEN, len);
//    ui->plot_1->yAxis->setRange(min_y-10,max_y+10);
//    ui->plot_1->graph(0)->setData(pid_w0_x,pid_w0_sp_y);
//    ui->plot_1->graph(1)->setData(pid_w0_x,pid_w0_fb_y);
//    ui->plot_1->replot();
//}

//void pid_w1_plot(uint32_t len){
//    double min_y, max_y;

//    min_y = *std::min_element(pid_w1_p_y.constBegin(), pid_w1_p_y.constEnd());
//    min_y = std::min(min_y, *std::min_element(pid_w1_i_y.constBegin(), pid_w1_i_y.constEnd()));
//    min_y = std::min(min_y, *std::min_element(pid_w1_d_y.constBegin(), pid_w1_d_y.constEnd()));
//    min_y = std::min(min_y, *std::min_element(pid_w1_u_y.constBegin(), pid_w1_u_y.constEnd()));
//    max_y = *std::max_element(pid_w1_p_y.constBegin(), pid_w1_p_y.constEnd());
//    max_y = std::max(max_y, *std::max_element(pid_w1_i_y.constBegin(), pid_w1_i_y.constEnd()));
//    max_y = std::max(max_y, *std::max_element(pid_w1_d_y.constBegin(), pid_w1_d_y.constEnd()));
//    max_y = std::max(max_y, *std::max_element(pid_w1_u_y.constBegin(), pid_w1_u_y.constEnd()));
//    ui->plot_2->xAxis->setRange(len-PID_VECTOR_LEN, len);
//    ui->plot_2->yAxis->setRange(min_y-10,max_y+10);
//    ui->plot_2->graph(0)->setData(pid_w1_x,pid_w1_p_y);
//    ui->plot_2->graph(1)->setData(pid_w1_x,pid_w1_i_y);
//    ui->plot_2->graph(2)->setData(pid_w1_x,pid_w1_d_y);
//    ui->plot_2->graph(3)->setData(pid_w1_x,pid_w1_u_y);
//    ui->plot_2->replot();

//    min_y = *std::min_element(pid_w1_sp_y.constBegin(), pid_w1_sp_y.constEnd());
//    min_y = std::min(min_y, *std::min_element(pid_w1_fb_y.constBegin(), pid_w1_fb_y.constEnd()));
//    max_y = *std::max_element(pid_w1_sp_y.constBegin(), pid_w1_sp_y.constEnd());
//    max_y = std::max(max_y, *std::max_element(pid_w1_fb_y.constBegin(), pid_w1_fb_y.constEnd()));
//    min_y = min_y < 0 ? -150 : min_y;
//    max_y = max_y > 0 ? 150 : max_y;
//    ui->plot_3->xAxis->setRange(len-PID_VECTOR_LEN, len);
//    ui->plot_3->yAxis->setRange(min_y-10,max_y+10);
//    ui->plot_3->graph(0)->setData(pid_w1_x,pid_w1_sp_y);
//    ui->plot_3->graph(1)->setData(pid_w1_x,pid_w1_fb_y);
//    ui->plot_3->replot();
//}

//void pid_sync_plot(uint32_t len){
//    double min_y, max_y;

//    min_y = *std::min_element(pid_s_p_y.constBegin(), pid_s_p_y.constEnd());
//    min_y = std::min(min_y, *std::min_element(pid_s_i_y.constBegin(), pid_s_i_y.constEnd()));
//    min_y = std::min(min_y, *std::min_element(pid_s_d_y.constBegin(), pid_s_d_y.constEnd()));
//    min_y = std::min(min_y, *std::min_element(pid_s_u_y.constBegin(), pid_s_u_y.constEnd()));
//    max_y = *std::max_element(pid_s_p_y.constBegin(), pid_s_p_y.constEnd());
//    max_y = std::max(max_y, *std::max_element(pid_s_i_y.constBegin(), pid_s_i_y.constEnd()));
//    max_y = std::max(max_y, *std::max_element(pid_s_d_y.constBegin(), pid_s_d_y.constEnd()));
//    max_y = std::max(max_y, *std::max_element(pid_s_u_y.constBegin(), pid_s_u_y.constEnd()));
//    ui->plot_4->xAxis->setRange(len-PID_VECTOR_LEN, len);
//    ui->plot_4->yAxis->setRange(min_y-1,max_y+1);
//    ui->plot_4->graph(0)->setData(pid_s_x,pid_s_p_y);
//    ui->plot_4->graph(1)->setData(pid_s_x,pid_s_i_y);
//    ui->plot_4->graph(2)->setData(pid_s_x,pid_s_d_y);
//    ui->plot_4->graph(3)->setData(pid_s_x,pid_s_u_y);
//    ui->plot_4->replot();

//    min_y = *std::min_element(pid_s_sp_y.constBegin(), pid_s_sp_y.constEnd());
//    min_y = std::min(min_y, *std::min_element(pid_s_fb_y.constBegin(), pid_s_fb_y.constEnd()));
//    max_y = *std::max_element(pid_s_sp_y.constBegin(), pid_s_sp_y.constEnd());
//    max_y = std::max(max_y, *std::max_element(pid_s_fb_y.constBegin(), pid_s_fb_y.constEnd()));
//    min_y = min_y < -4 ? min_y : -4;
//    max_y = max_y > 4 ? max_y : 4;
//    ui->plot_5->xAxis->setRange(len-PID_VECTOR_LEN, len);
//    ui->plot_5->yAxis->setRange(min_y-1,max_y+1);
//    ui->plot_5->graph(0)->setData(pid_s_x,pid_s_sp_y);
//    ui->plot_5->graph(1)->setData(pid_s_x,pid_s_fb_y);
//    ui->plot_5->replot();
//}


//void on_pid_report_recv(mavlink_message_t *msg){
//    static uint32_t w0_cnt = 0;
//    static uint32_t w1_cnt = 0;
//    static uint32_t s_cnt = 0;


//    mavlink_pid_report_t pid_report_msg;
//    mavlink_msg_pid_report_decode(msg,&pid_report_msg);
//    switch(pid_report_msg.pid_control){
//    case PID_WHE0:
//        pid_w0_x.append(w0_cnt);
//        pid_w0_sp_y.append(pid_report_msg.sp);
//        pid_w0_fb_y.append(pid_report_msg.fb);
//        pid_w0_p_y.append(pid_report_msg.P_Part);
//        pid_w0_i_y.append(pid_report_msg.I_Part);
//        pid_w0_d_y.append(pid_report_msg.D_Part);
//        pid_w0_u_y.append(pid_report_msg.U);
//        truncate_vector(pid_w0_x);
//        truncate_vector(pid_w0_sp_y);
//        truncate_vector(pid_w0_fb_y);
//        truncate_vector(pid_w0_p_y);
//        truncate_vector(pid_w0_i_y);
//        truncate_vector(pid_w0_d_y);
//        truncate_vector(pid_w0_u_y);
//        w0_cnt++;
//        pid_w0_plot(w0_cnt);
//        break;
//    case PID_WHE1:
//        pid_w1_x.append(w1_cnt);
//        pid_w1_sp_y.append(pid_report_msg.sp);
//        pid_w1_fb_y.append(pid_report_msg.fb);
//        pid_w1_p_y.append(pid_report_msg.P_Part);
//        pid_w1_i_y.append(pid_report_msg.I_Part);
//        pid_w1_d_y.append(pid_report_msg.D_Part);
//        pid_w1_u_y.append(pid_report_msg.U);
//        truncate_vector(pid_w1_x);
//        truncate_vector(pid_w1_sp_y);
//        truncate_vector(pid_w1_fb_y);
//        truncate_vector(pid_w1_p_y);
//        truncate_vector(pid_w1_i_y);
//        truncate_vector(pid_w1_d_y);
//        truncate_vector(pid_w1_u_y);
//        pid_w1_plot(w1_cnt);
//        w1_cnt++;
//        break;
//    case PID_SYNC:
//        pid_s_x.append(s_cnt);
//        pid_s_sp_y.append(pid_report_msg.sp);
//        pid_s_fb_y.append(pid_report_msg.fb);
//        pid_s_p_y.append(pid_report_msg.P_Part);
//        pid_s_i_y.append(pid_report_msg.I_Part);
//        pid_s_d_y.append(pid_report_msg.D_Part);
//        pid_s_u_y.append(pid_report_msg.U);
//        truncate_vector(pid_s_x);
//        truncate_vector(pid_s_sp_y);
//        truncate_vector(pid_s_fb_y);
//        truncate_vector(pid_s_p_y);
//        truncate_vector(pid_s_i_y);
//        truncate_vector(pid_s_d_y);
//        truncate_vector(pid_s_u_y);
//        pid_sync_plot(s_cnt);
//        s_cnt++;
//        break;
//    }
//}

void Mode_pidt_tw::mode_pidt_load_timeout(){
    if(!g_does_st_successfullly){
        g_does_st_successfullly = true;
        show_status("Unable to load PID params",2000);
    }
}

void Mode_pidt_tw::mode_pidt_write_timeout(){
    if(!g_does_st_successfullly){
        g_does_st_successfullly = true;
        show_status("Unable to write PID params",2000);
    }
}

void Mode_pidt_tw::mode_pidt_save_timeout(){
    if(!g_does_st_successfullly){
        g_does_st_successfullly = true;
        show_status("Unable to save PID params",2000);
    }
}

void Mode_pidt_tw::on_btn_mode_pidt_load_params_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_cmd_params_pack(0,0,&msg,CMD_LOAD);

    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    emit mode_pidt_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));
    show_status("Loading PID params",1000);

    g_does_st_successfullly = false;
    QTimer::singleShot(3000, this, SLOT(mode_pidt_load_timeout()));
}

void Mode_pidt_tw::on_btn_mode_pidt_write_params_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    uint16_t len;

    float tilt_KP = static_cast<float>(ui->sb_pid_tilt_kp->value());
    float tilt_KI = static_cast<float>(ui->sb_pid_tilt_ki->value());
    float tilt_KD = static_cast<float>(ui->sb_pid_tilt_kd->value());
    mavlink_msg_pid_params_pack(0,0,&msg,PID_SYNC,tilt_KP,tilt_KI,tilt_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    emit mode_pidt_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));

    float vel_KP = static_cast<float>(ui->sb_pid_vel_kp->value());
    float vel_KI = static_cast<float>(ui->sb_pid_vel_ki->value());
    float vel_KD = static_cast<float>(ui->sb_pid_vel_kd->value());
    mavlink_msg_pid_params_pack(0,0,&msg,PID_WHE0,vel_KP,vel_KI,vel_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    emit mode_pidt_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));

    float pos_KP = static_cast<float>(ui->sb_pid_pos_kp->value());
    float pos_KI = static_cast<float>(ui->sb_pid_pos_ki->value());
    float pos_KD = static_cast<float>(ui->sb_pid_pos_kd->value());
    mavlink_msg_pid_params_pack(0,0,&msg,PID_WHE1,pos_KP,pos_KI,pos_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    emit mode_pidt_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));

    show_status("Writing PID params",2000);
    g_does_st_successfullly = false;
    QTimer::singleShot(3000, this, SLOT(mode_pidt_write_timeout()));
}

void Mode_pidt_tw::on_btn_mode_pidt_save_params_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_cmd_params_pack(0,0,&msg,CMD_SAVE);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);

    emit mode_pidt_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));
    show_status("Saving PID params",1000);

    g_does_st_successfullly = false;
    QTimer::singleShot(3000, this, SLOT(mode_pidt_save_timeout()));
}

void Mode_pidt_tw::on_btn_mode_pidt_write_params_pidt_tilt_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    uint16_t len;

    float tilt_KP = static_cast<float>(ui->sb_pid_tilt_kp->value());
    float tilt_KI = static_cast<float>(ui->sb_pid_tilt_ki->value());
    float tilt_KD = static_cast<float>(ui->sb_pid_tilt_kd->value());
    mavlink_msg_pid_params_pack(0,0,&msg,PID_SYNC,tilt_KP,tilt_KI,tilt_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    emit mode_pidt_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));

    show_status("Writing PID tilt params",2000);
    g_does_st_successfullly = false;
    QTimer::singleShot(3000, this, SLOT(mode_pidt_write_timeout()));
}

void Mode_pidt_tw::on_btn_mode_pidt_write_params_pidt_vel_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    uint16_t len;

    float vel_KP = static_cast<float>(ui->sb_pid_vel_kp->value());
    float vel_KI = static_cast<float>(ui->sb_pid_vel_ki->value());
    float vel_KD = static_cast<float>(ui->sb_pid_vel_kd->value());
    mavlink_msg_pid_params_pack(0,0,&msg,PID_WHE0,vel_KP,vel_KI,vel_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    emit mode_pidt_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));

    show_status("Writing PID velocity params",2000);
    g_does_st_successfullly = false;
    QTimer::singleShot(3000, this, SLOT(mode_pidt_write_timeout()));
}

void Mode_pidt_tw::on_btn_mode_pidt_write_params_pidt_pos_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    uint16_t len;

    float pos_KP = static_cast<float>(ui->sb_pid_pos_kp->value());
    float pos_KI = static_cast<float>(ui->sb_pid_pos_ki->value());
    float pos_KD = static_cast<float>(ui->sb_pid_pos_kd->value());
    mavlink_msg_pid_params_pack(0,0,&msg,PID_WHE1,pos_KP,pos_KI,pos_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    emit mode_pidt_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));

    show_status("Writing PID params",2000);
    g_does_st_successfullly = false;
    QTimer::singleShot(3000, this, SLOT(mode_pidt_write_timeout()));
}

void Mode_pidt_tw::remote_control_pidt(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    int16_t VX = static_cast<int16_t>(ui->txtb_pidt_vx->text().toDouble()*100);
    int16_t OMEGA = static_cast<int16_t>(ui->txtb_pidt_w->text().toDouble()*100);
    mavlink_msg_cmd_velocity_pack(0,0,&msg,VX,OMEGA);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    emit mode_pidt_mav_send(QByteArray::fromRawData(reinterpret_cast<char*>(mav_send_buf),len));
}

void Mode_pidt_tw::on_btn_control_enable_clicked()
{
    if(g_control_enable == false){
        g_control_enable = true;
        ui->btn_control_enable->setText("Enabled");
        g_controller_timer->start(100);
    }
    else{
        g_control_enable = false;
        ui->btn_control_enable->setText("Disabled");
        g_controller_timer->stop();
    }
}

void Mode_pidt_tw::on_btn_change_mode_pidt_clicked()
{
    emit mode_change(MODE_PIDT);
}

void Mode_pidt_tw::on_sb_pid_tilt_kp_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    ui->sb_pid_tilt_kp->setSingleStep(ui->sb_pid_tilt_kp_step->value());
}

void Mode_pidt_tw::on_sb_pid_tilt_ki_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    ui->sb_pid_tilt_ki->setSingleStep(ui->sb_pid_tilt_ki_step->value());
}

void Mode_pidt_tw::on_sb_pid_tilt_kd_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    ui->sb_pid_tilt_kd->setSingleStep(ui->sb_pid_tilt_kd_step->value());
}

void Mode_pidt_tw::on_sb_pid_vel_kp_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    ui->sb_pid_vel_kp->setSingleStep(ui->sb_pid_vel_kp_step->value());
}

void Mode_pidt_tw::on_sb_pid_vel_ki_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    ui->sb_pid_vel_ki->setSingleStep(ui->sb_pid_vel_ki_step->value());
}

void Mode_pidt_tw::on_sb_pid_vel_kd_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    ui->sb_pid_vel_kd->setSingleStep(ui->sb_pid_vel_kd_step->value());
}

void Mode_pidt_tw::on_sb_pid_pos_kp_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    ui->sb_pid_pos_kp->setSingleStep(ui->sb_pid_pos_kp_step->value());
}

void Mode_pidt_tw::on_sb_pid_pos_ki_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    ui->sb_pid_pos_ki->setSingleStep(ui->sb_pid_pos_ki_step->value());
}

void Mode_pidt_tw::on_sb_pid_pos_kd_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    ui->sb_pid_pos_kd->setSingleStep(ui->sb_pid_pos_kd_step->value());
}
