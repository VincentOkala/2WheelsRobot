#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::app_main_on_data_recv(QByteArray bytes){
    for(uint16_t i = 0; i < bytes.size(); i++){
        uint8_t msg_received = mavlink_parse_char(MAVLINK_COMM_0, bytes[i], &msg, &status);
        if(msg_received == 1){
            qDebug() << "Recv msgid: " << msg.msgid;
            if(msg.msgid == MAVLINK_MSG_ID_RESPOND && isChangeMode){
                isChangeMode = false;
                mavlink_respond_t evt_respond;
                mavlink_msg_respond_decode(&msg, &evt_respond);
                if(evt_respond.respond == RESPOND_OK){
                    changeModeSuccess = true;
                    showStatus("Succeed to change mode",1000);
                    switch (changeToMode) {
                    case MODE_RUN:
                        currentMode = MODE_RUN;
                        break;
                    case MODE_IMU:
                        currentMode = MODE_IMU;
                        break;
                    case MODE_PIDT:
                        currentMode = MODE_PIDT;
                        break;
                    case MODE_HW:
                        currentMode = MODE_HW;
                        break;
                    default:
                        break;
                    }
                }
                qDebug() << "Mode: " << currentMode;
            }
            else{
                switch (currentMode) {
                case MODE_RUN:
                    on_mode_basic_mav_recv(&msg);
                    break;
                case MODE_IMU:
                    on_mode_imu_mav_recv(&msg);
                    break;
                case MODE_PIDT:
                    on_mode_pidt_mav_recv(&msg);
                    break;
                case MODE_HW:
                    on_mode_hw_mav_recv(&msg);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void MainWindow::app_main_init(){
    currentMode = MODE_RUN;
}

void MainWindow::app_command_timeout(){
    isChangeMode = false;
    if(!changeModeSuccess){
        showStatus("Unable to change mode",1000);
    }
}

void MainWindow::app_command_change_mode(rmode_t mode){
    isChangeMode = true;
    changeToMode = mode;
    changeModeSuccess = false;
    mavlink_message_t msg;
    uint8_t gmav_send_buf[255];
    mavlink_msg_cmd_change_mode_pack(0,0,&msg, mode);
    uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
    if(send(QByteArray::fromRawData((char*)(gmav_send_buf),len))){
         showStatus("Requesting to change mode",500);
         QTimer::singleShot(1000, this, SLOT(app_command_timeout()));
    }
    else{
        showStatus("Cannot request to change mode",1000);
    }
}

void MainWindow::on_btn_change_mode_basic_clicked()
{
    app_command_change_mode(MODE_RUN);
}

void MainWindow::on_btn_change_mode_imu_calibration_clicked()
{
    app_command_change_mode(MODE_IMU);
}

void MainWindow::on_btn_change_mode_pid_tunning_clicked()
{
     app_command_change_mode(MODE_PIDT);
}

void MainWindow::on_btn_change_mode_hw_clicked()
{
    app_command_change_mode(MODE_HW);
}

void MainWindow::on_tilt_recv(float tilt){
    ui->txtb_tilt_0->setText(QString::number(tilt));
    ui->txtb_tilt_1->setText(QString::number(tilt));

    static uint32_t cnt = 0;
    tilt_x.append(cnt);
    tilt_y.append(tilt);

    truncate_vector(tilt_x);
    truncate_vector(tilt_y);

    ui->plot_0->xAxis->setRange(cnt-40, cnt);
    float min = *std::min_element(tilt_y.constBegin(), tilt_y.constEnd());
    float max = *std::max_element(tilt_y.constBegin(), tilt_y.constEnd());
    if (min > -10) min = -10;
    if(max < 10) max = 10;
    ui->plot_0->yAxis->setRange(min,max);
    ui->plot_0->graph(0)->setData(tilt_x,tilt_y);
    cnt++;
    ui->plot_0->replot();
}

