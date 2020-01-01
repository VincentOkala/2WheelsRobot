#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_mode_pidt_mav_recv(mavlink_message_t *msg){
    switch(msg->msgid) {
    case MAVLINK_MSG_ID_PID_PARAMS:
        if(isDoStSuccessfull == false){
            isDoStSuccessfull = true;
            mavlink_pid_params_t pid;
            mavlink_msg_pid_params_decode(msg, &pid);
            showStatus("Succeed to load PID params",2000);

            switch (pid.pid_control) {
                case PID_WHE0:
                    ui->sb_w0_kp->setValue(pid.KP);
                    ui->sb_w0_ki->setValue(pid.KI);
                    ui->sb_w0_kd->setValue(pid.KD);
                break;
                case PID_WHE1:
                    ui->sb_w1_kp->setValue(pid.KP);
                    ui->sb_w1_ki->setValue(pid.KI);
                    ui->sb_w1_kd->setValue(pid.KD);
                break;
                case PID_SYNC:
                    ui->sb_sta_kp->setValue(pid.KP);
                    ui->sb_sta_ki->setValue(pid.KI);
                    ui->sb_sta_kd->setValue(pid.KD);
                break;
            }
        }
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
    case MAVLINK_MSG_ID_EVT_TILT:
        mavlink_evt_tilt_t tilt_msg;
        mavlink_msg_evt_tilt_decode(msg,&tilt_msg);
        on_tilt_recv(tilt_msg.tilt);
        break;
    case MAVLINK_MSG_ID_PID_REPORT:
        on_pid_report_recv(msg);
        break;
    case MAVLINK_MSG_ID_MOTOR_SPEED:
        mavlink_motor_speed_t motor_speed_msg;
        mavlink_msg_motor_speed_decode(msg, &motor_speed_msg);
        ui->txtb_enc0_a_speed->setText(QString::number(motor_speed_msg.motor_speed_0));
        ui->txtb_enc1_a_speed->setText(QString::number(motor_speed_msg.motor_speed_1));
        break;
    }
}

void MainWindow::load_pid_params(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_cmd_params_pack(0,0,&msg,CMD_LOAD);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
//        showStatus("Loading PID params",1000);
//   }
//   else{
//       showStatus("Cannot load PID params",1000);
//   }
   isDoStSuccessfull = false;
   QTimer::singleShot(3000, this, SLOT(mode_pidt_load_timeout()));
}


void MainWindow::mode_pidt_load_timeout(){
    if(!isDoStSuccessfull){
        isDoStSuccessfull = true;
        showStatus("Unable to load PID params",2000);
    }
}

void MainWindow::mode_pidt_write_timeout(){
    if(!isDoStSuccessfull){
        isDoStSuccessfull = true;
        showStatus("Unable to write PID params",2000);
    }
}

void MainWindow::mode_pidt_save_timeout(){
    if(!isDoStSuccessfull){
        isDoStSuccessfull = true;
        showStatus("Unable to save PID params",2000);
    }
}

void MainWindow::write_pid_params(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    uint16_t len;

    double sync_KP = ui->sb_sta_kp->value();
    double sync_KI = ui->sb_sta_ki->value();
    double sync_KD = ui->sb_sta_kd->value();
    mavlink_msg_pid_params_pack(0,0,&msg,PID_SYNC,sync_KP,sync_KI,sync_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
//        showStatus("Writing PID params",2000);
//    }
//    else{
//       showStatus("Cannot write PID params",2000);
//    }

    double w0_KP = ui->sb_w0_kp->value();
    double w0_KI = ui->sb_w0_ki->value();
    double w0_KD = ui->sb_w0_kd->value();
    mavlink_msg_pid_params_pack(0,0,&msg,PID_WHE0,w0_KP,w0_KI,w0_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
//        showStatus("Writing PID params",2000);
//    }
//    else{
//       showStatus("Cannot write PID params",2000);
//    }

    double w1_KP = ui->sb_w1_kp->value();
    double w1_KI = ui->sb_w1_ki->value();
    double w1_KD = ui->sb_w1_kd->value();
    mavlink_msg_pid_params_pack(0,0,&msg,PID_WHE1,w1_KP,w1_KI,w1_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
//        showStatus("Writing PID params",2000);
//    }
//    else{
//       showStatus("Cannot write PID params",2000);
//    }

   isDoStSuccessfull = false;
   QTimer::singleShot(3000, this, SLOT(mode_pidt_write_timeout()));
}

void MainWindow::save_pid_params(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_cmd_params_pack(0,0,&msg,CMD_SAVE);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
//        showStatus("Saving PID params",1000);
//   }
//   else{
//       showStatus("Cannot save PID params",1000);
//   }
   isDoStSuccessfull = false;
   QTimer::singleShot(3000, this, SLOT(mode_pidt_save_timeout()));
}

void MainWindow::on_btn_mode_pidt_load_params_clicked()
{
    if(currentMode == MODE_PIDT){
        load_pid_params();
    }
    else{
        showStatus("Change mode to pid tunning first",2000);
    }
}

void MainWindow::on_btn_mode_pidt_write_params_clicked()
{
    if(currentMode == MODE_PIDT){
        write_pid_params();
    }
    else{
        showStatus("Change mode to pid tunning first",2000);
    }
}

void MainWindow::on_btn_mode_pidt_save_params_clicked()
{
    if(currentMode == MODE_PIDT){
        save_pid_params();
    }
    else{
        showStatus("Change mode to pid tunning first",2000);
    }
}

void MainWindow::on_sb_step_KP_valueChanged(const QString &arg1)
{
    ui->sb_sta_kp->setSingleStep(ui->sb_step_sta_kp->value());
}

void MainWindow::on_sb_step_KI_valueChanged(const QString &arg1)
{
    ui->sb_sta_ki->setSingleStep(ui->sb_step_sta_ki->value());
}

void MainWindow::on_sb_KD_valueChanged(const QString &arg1)
{
    ui->sb_sta_kd->setSingleStep(ui->sb_step_sta_kd->value());
}

void MainWindow::truncate_vector(QVector<double> &v){
    if(v.size() > PID_VECTOR_LEN){
        v.pop_front();
    }
}

void MainWindow::on_btn_set_speed0_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    int32_t motor0_duty = ui->txtb_motor0_speed->text().toInt();
    int32_t motor1_duty = ui->txtb_motor1_speed->text().toInt();

    mavlink_msg_motor_speed_pack(0,0,&msg,motor0_duty,motor1_duty);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    send(QByteArray::fromRawData((char*)(mav_send_buf),len));
}

void MainWindow::on_btn_set_speed1_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    int32_t motor0_duty = ui->txtb_motor0_speed->text().toInt();
    int32_t motor1_duty = ui->txtb_motor1_speed->text().toInt();

    mavlink_msg_motor_speed_pack(0,0,&msg,motor0_duty,motor1_duty);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    send(QByteArray::fromRawData((char*)(mav_send_buf),len));
}

void MainWindow::pid_w0_plot(uint32_t len){
    double min_y, max_y;

    min_y = *std::min_element(pid_w0_p_y.constBegin(), pid_w0_p_y.constEnd());
    min_y = std::min(min_y, *std::min_element(pid_w0_i_y.constBegin(), pid_w0_i_y.constEnd()));
    min_y = std::min(min_y, *std::min_element(pid_w0_d_y.constBegin(), pid_w0_d_y.constEnd()));
    min_y = std::min(min_y, *std::min_element(pid_w0_u_y.constBegin(), pid_w0_u_y.constEnd()));
    max_y = *std::max_element(pid_w0_p_y.constBegin(), pid_w0_p_y.constEnd());
    max_y = std::max(max_y, *std::max_element(pid_w0_i_y.constBegin(), pid_w0_i_y.constEnd()));
    max_y = std::max(max_y, *std::max_element(pid_w0_d_y.constBegin(), pid_w0_d_y.constEnd()));
    max_y = std::max(max_y, *std::max_element(pid_w0_u_y.constBegin(), pid_w0_u_y.constEnd()));
    ui->plot_0->xAxis->setRange(len-PID_VECTOR_LEN, len);
    ui->plot_0->yAxis->setRange(min_y-10,max_y+10);
    ui->plot_0->graph(0)->setData(pid_w0_x,pid_w0_p_y);
    ui->plot_0->graph(1)->setData(pid_w0_x,pid_w0_i_y);
    ui->plot_0->graph(2)->setData(pid_w0_x,pid_w0_d_y);
    ui->plot_0->graph(3)->setData(pid_w0_x,pid_w0_u_y);
    ui->plot_0->replot();

    min_y = *std::min_element(pid_w0_sp_y.constBegin(), pid_w0_sp_y.constEnd());
    min_y = std::min(min_y, *std::min_element(pid_w0_fb_y.constBegin(), pid_w0_fb_y.constEnd()));
    max_y = *std::max_element(pid_w0_sp_y.constBegin(), pid_w0_sp_y.constEnd());
    max_y = std::max(max_y, *std::max_element(pid_w0_fb_y.constBegin(), pid_w0_fb_y.constEnd()));
//    min_y = min_y < 0 ? -150 : min_y;
//    max_y = max_y > 0 ? 150 : max_y;
    ui->plot_1->xAxis->setRange(len-PID_VECTOR_LEN, len);
    ui->plot_1->yAxis->setRange(min_y-10,max_y+10);
    ui->plot_1->graph(0)->setData(pid_w0_x,pid_w0_sp_y);
    ui->plot_1->graph(1)->setData(pid_w0_x,pid_w0_fb_y);
    ui->plot_1->replot();
}

void MainWindow::pid_w1_plot(uint32_t len){
    double min_y, max_y;

    min_y = *std::min_element(pid_w1_p_y.constBegin(), pid_w1_p_y.constEnd());
    min_y = std::min(min_y, *std::min_element(pid_w1_i_y.constBegin(), pid_w1_i_y.constEnd()));
    min_y = std::min(min_y, *std::min_element(pid_w1_d_y.constBegin(), pid_w1_d_y.constEnd()));
    min_y = std::min(min_y, *std::min_element(pid_w1_u_y.constBegin(), pid_w1_u_y.constEnd()));
    max_y = *std::max_element(pid_w1_p_y.constBegin(), pid_w1_p_y.constEnd());
    max_y = std::max(max_y, *std::max_element(pid_w1_i_y.constBegin(), pid_w1_i_y.constEnd()));
    max_y = std::max(max_y, *std::max_element(pid_w1_d_y.constBegin(), pid_w1_d_y.constEnd()));
    max_y = std::max(max_y, *std::max_element(pid_w1_u_y.constBegin(), pid_w1_u_y.constEnd()));
    ui->plot_2->xAxis->setRange(len-PID_VECTOR_LEN, len);
    ui->plot_2->yAxis->setRange(min_y-10,max_y+10);
    ui->plot_2->graph(0)->setData(pid_w1_x,pid_w1_p_y);
    ui->plot_2->graph(1)->setData(pid_w1_x,pid_w1_i_y);
    ui->plot_2->graph(2)->setData(pid_w1_x,pid_w1_d_y);
    ui->plot_2->graph(3)->setData(pid_w1_x,pid_w1_u_y);
    ui->plot_2->replot();

    min_y = *std::min_element(pid_w1_sp_y.constBegin(), pid_w1_sp_y.constEnd());
    min_y = std::min(min_y, *std::min_element(pid_w1_fb_y.constBegin(), pid_w1_fb_y.constEnd()));
    max_y = *std::max_element(pid_w1_sp_y.constBegin(), pid_w1_sp_y.constEnd());
    max_y = std::max(max_y, *std::max_element(pid_w1_fb_y.constBegin(), pid_w1_fb_y.constEnd()));
//    min_y = min_y < 0 ? -150 : min_y;
//    max_y = max_y > 0 ? 150 : max_y;
    ui->plot_3->xAxis->setRange(len-PID_VECTOR_LEN, len);
    ui->plot_3->yAxis->setRange(min_y-10,max_y+10);
    ui->plot_3->graph(0)->setData(pid_w1_x,pid_w1_sp_y);
    ui->plot_3->graph(1)->setData(pid_w1_x,pid_w1_fb_y);
    ui->plot_3->replot();
}

void MainWindow::pid_sync_plot(uint32_t len){
    double min_y, max_y;

    min_y = *std::min_element(pid_s_p_y.constBegin(), pid_s_p_y.constEnd());
    min_y = std::min(min_y, *std::min_element(pid_s_i_y.constBegin(), pid_s_i_y.constEnd()));
    min_y = std::min(min_y, *std::min_element(pid_s_d_y.constBegin(), pid_s_d_y.constEnd()));
    min_y = std::min(min_y, *std::min_element(pid_s_u_y.constBegin(), pid_s_u_y.constEnd()));
    max_y = *std::max_element(pid_s_p_y.constBegin(), pid_s_p_y.constEnd());
    max_y = std::max(max_y, *std::max_element(pid_s_i_y.constBegin(), pid_s_i_y.constEnd()));
    max_y = std::max(max_y, *std::max_element(pid_s_d_y.constBegin(), pid_s_d_y.constEnd()));
    max_y = std::max(max_y, *std::max_element(pid_s_u_y.constBegin(), pid_s_u_y.constEnd()));
    ui->plot_4->xAxis->setRange(len-PID_VECTOR_LEN, len);
    ui->plot_4->yAxis->setRange(min_y-1,max_y+1);
    ui->plot_4->graph(0)->setData(pid_s_x,pid_s_p_y);
    ui->plot_4->graph(1)->setData(pid_s_x,pid_s_i_y);
    ui->plot_4->graph(2)->setData(pid_s_x,pid_s_d_y);
    ui->plot_4->graph(3)->setData(pid_s_x,pid_s_u_y);
    ui->plot_4->replot();

    min_y = *std::min_element(pid_s_sp_y.constBegin(), pid_s_sp_y.constEnd());
    min_y = std::min(min_y, *std::min_element(pid_s_fb_y.constBegin(), pid_s_fb_y.constEnd()));
    max_y = *std::max_element(pid_s_sp_y.constBegin(), pid_s_sp_y.constEnd());
    max_y = std::max(max_y, *std::max_element(pid_s_fb_y.constBegin(), pid_s_fb_y.constEnd()));
    min_y = min_y < -4 ? min_y : -4;
    max_y = max_y > 4 ? max_y : 4;
    ui->plot_5->xAxis->setRange(len-PID_VECTOR_LEN, len);
    ui->plot_5->yAxis->setRange(min_y-1,max_y+1);
    ui->plot_5->graph(0)->setData(pid_s_x,pid_s_sp_y);
    ui->plot_5->graph(1)->setData(pid_s_x,pid_s_fb_y);
    ui->plot_5->replot();
}


void MainWindow::on_pid_report_recv(mavlink_message_t *msg){
    static uint32_t w0_cnt = 0;
    static uint32_t w1_cnt = 0;
    static uint32_t s_cnt = 0;


    mavlink_pid_report_t pid_report_msg;
    mavlink_msg_pid_report_decode(msg,&pid_report_msg);
    switch(pid_report_msg.pid_control){
    case PID_WHE0:
        pid_w0_x.append(w0_cnt);
        pid_w0_sp_y.append(pid_report_msg.sp);
        pid_w0_fb_y.append(pid_report_msg.fb);
        pid_w0_p_y.append(pid_report_msg.P_Part);
        pid_w0_i_y.append(pid_report_msg.I_Part);
        pid_w0_d_y.append(pid_report_msg.D_Part);
        pid_w0_u_y.append(pid_report_msg.U);
        truncate_vector(pid_w0_x);
        truncate_vector(pid_w0_sp_y);
        truncate_vector(pid_w0_fb_y);
        truncate_vector(pid_w0_p_y);
        truncate_vector(pid_w0_i_y);
        truncate_vector(pid_w0_d_y);
        truncate_vector(pid_w0_u_y);
        w0_cnt++;
        pid_w0_plot(w0_cnt);
        break;
    case PID_WHE1:
        pid_w1_x.append(w1_cnt);
        pid_w1_sp_y.append(pid_report_msg.sp);
        pid_w1_fb_y.append(pid_report_msg.fb);
        pid_w1_p_y.append(pid_report_msg.P_Part);
        pid_w1_i_y.append(pid_report_msg.I_Part);
        pid_w1_d_y.append(pid_report_msg.D_Part);
        pid_w1_u_y.append(pid_report_msg.U);
        truncate_vector(pid_w1_x);
        truncate_vector(pid_w1_sp_y);
        truncate_vector(pid_w1_fb_y);
        truncate_vector(pid_w1_p_y);
        truncate_vector(pid_w1_i_y);
        truncate_vector(pid_w1_d_y);
        truncate_vector(pid_w1_u_y);
        pid_w1_plot(w1_cnt);
        w1_cnt++;
        break;
    case PID_SYNC:
        pid_s_x.append(s_cnt);
        pid_s_sp_y.append(pid_report_msg.sp);
        pid_s_fb_y.append(pid_report_msg.fb);
        pid_s_p_y.append(pid_report_msg.P_Part);
        pid_s_i_y.append(pid_report_msg.I_Part);
        pid_s_d_y.append(pid_report_msg.D_Part);
        pid_s_u_y.append(pid_report_msg.U);
        truncate_vector(pid_s_x);
        truncate_vector(pid_s_sp_y);
        truncate_vector(pid_s_fb_y);
        truncate_vector(pid_s_p_y);
        truncate_vector(pid_s_i_y);
        truncate_vector(pid_s_d_y);
        truncate_vector(pid_s_u_y);
        pid_sync_plot(s_cnt);
        s_cnt++;
        break;
    }
}

void MainWindow::on_btn_control_enable_clicked()
{
    if(control_enable == false){
        control_enable=true;
        ui->btn_control_enable->setText("Enabled");
        ui->btn_control_enable_2->setText("Enabled");
        connect(controller_timer, SIGNAL(timeout()), this, SLOT(on_controller_pidt()));
        controller_timer->start(100);
    }
    else{
        control_enable = false;
        ui->btn_control_enable->setText("Disabled");
        ui->btn_control_enable_2->setText("Disabled");
        controller_timer->stop();
    }
}

void MainWindow::on_controller_pidt(){
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    int16_t VX = ui->txtb_pidt_vx->text().toDouble()*100;
    int16_t OMEGA = ui->txtb_pidt_w->text().toDouble()*100;
    qDebug() << VX << " " << OMEGA;
    mavlink_msg_cmd_velocity_pack(0,0,&msg,VX,OMEGA);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    send(QByteArray::fromRawData((char*)(mav_send_buf),len));
}

void MainWindow::on_btn_mode_pidt_write_params_pid_whe0_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    uint16_t len;

    double w0_KP = ui->sb_w0_kp->value();
    double w0_KI = ui->sb_w0_ki->value();
    double w0_KD = ui->sb_w0_kd->value();
    mavlink_msg_pid_params_pack(0,0,&msg,PID_WHE0,w0_KP,w0_KI,w0_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
//        showStatus("Writing PID params",2000);
//    }
//    else{
//       showStatus("Cannot write PID params",2000);
//    }

    isDoStSuccessfull = false;
    QTimer::singleShot(3000, this, SLOT(mode_pidt_write_timeout()));
}


void MainWindow::on_btn_mode_pidt_write_params_pid_whe1_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    uint16_t len;

    double w1_KP = ui->sb_w1_kp->value();
    double w1_KI = ui->sb_w1_ki->value();
    double w1_KD = ui->sb_w1_kd->value();
    mavlink_msg_pid_params_pack(0,0,&msg,PID_WHE1,w1_KP,w1_KI,w1_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
//        showStatus("Writing PID params",2000);
//    }
//    else{
//       showStatus("Cannot write PID params",2000);
//    }

    isDoStSuccessfull = false;
    QTimer::singleShot(3000, this, SLOT(mode_pidt_write_timeout()));
}

void MainWindow::on_btn_mode_pidt_write_params_pid_sync_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    uint16_t len;

    double sync_KP = ui->sb_sta_kp->value();
    double sync_KI = ui->sb_sta_ki->value();
    double sync_KD = ui->sb_sta_kd->value();
    mavlink_msg_pid_params_pack(0,0,&msg,PID_SYNC,sync_KP,sync_KI,sync_KD);
    len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
//    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
//        showStatus("Writing PID params",2000);
//    }
//    else{
//       showStatus("Cannot write PID params",2000);
//    }

    isDoStSuccessfull = false;
    QTimer::singleShot(3000, this, SLOT(mode_pidt_write_timeout()));
}


