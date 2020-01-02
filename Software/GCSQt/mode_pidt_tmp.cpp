#include "mainwindow.h"
#include "ui_mainwindow.h"

//void MainWindow::pid_w0_plot(uint32_t len){
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
////    min_y = min_y < 0 ? -150 : min_y;
////    max_y = max_y > 0 ? 150 : max_y;
//    ui->plot_1->xAxis->setRange(len-PID_VECTOR_LEN, len);
//    ui->plot_1->yAxis->setRange(min_y-10,max_y+10);
//    ui->plot_1->graph(0)->setData(pid_w0_x,pid_w0_sp_y);
//    ui->plot_1->graph(1)->setData(pid_w0_x,pid_w0_fb_y);
//    ui->plot_1->replot();
//}

//void MainWindow::pid_w1_plot(uint32_t len){
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
////    min_y = min_y < 0 ? -150 : min_y;
////    max_y = max_y > 0 ? 150 : max_y;
//    ui->plot_3->xAxis->setRange(len-PID_VECTOR_LEN, len);
//    ui->plot_3->yAxis->setRange(min_y-10,max_y+10);
//    ui->plot_3->graph(0)->setData(pid_w1_x,pid_w1_sp_y);
//    ui->plot_3->graph(1)->setData(pid_w1_x,pid_w1_fb_y);
//    ui->plot_3->replot();
//}

//void MainWindow::pid_sync_plot(uint32_t len){
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


//void MainWindow::on_pid_report_recv(mavlink_message_t *msg){
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
