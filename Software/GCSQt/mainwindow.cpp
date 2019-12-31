#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("GCS");

    ledIndicator = new LedIndicator();
    ui->statusBar->addPermanentWidget(ledIndicator);

    app_main_init();

    qjs = QJoysticks::getInstance();
    qjs->setVirtualJoystickRange(1);
    connect(qjs,SIGNAL(axisChanged(const int, const int, const qreal)),this,SLOT(on_js_axis_change(const int, const int, const qreal)));

    controller_timer = new QTimer(this);

    for(int i=0;i<=3;i++){
        ui->plot_0->addGraph();
        ui->plot_0->graph(i)->setPen(QPen(QColor(0,50*i,50*i)));

        ui->plot_2->addGraph();
        ui->plot_2->graph(i)->setPen(QPen(QColor(50*i,0,50*i)));

        ui->plot_4->addGraph();
        ui->plot_4->graph(i)->setPen(QPen(QColor(50*i,50*i,0)));
    }

    for(int i=0;i<=1;i++){
        ui->plot_1->addGraph();
        ui->plot_1->graph(i)->setPen(QPen(QColor(0,50*i,50*i)));

        ui->plot_3->addGraph();
        ui->plot_3->graph(i)->setPen(QPen(QColor(50*i,0,50*i)));

        ui->plot_5->addGraph();
        ui->plot_5->graph(i)->setPen(QPen(QColor(50*i,50*i,0)));
    }

    // Com
    connect(ui->wg_com,SIGNAL(on_ba_recv(QByteArray)),this,SLOT(receive(QByteArray)));
    connect(ui->wg_com,SIGNAL(on_connection_evt(Com::com_evt_t)),this,SLOT(com_connection_evt(Com::com_evt_t)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showStatus(QString qstr, int timeout){
    ui->statusBar->showMessage(qstr,timeout);
}

QString MainWindow::ByteArrayToString(QByteArray ba)
{
    QString qstr;
    char tmp[20];
    for (uint8_t byte : ba) {
        sprintf(tmp, "{%02x}", byte);
        qstr.append(QString(tmp));
    }
    return qstr;
}

void MainWindow::ledIndicatorOff(){
    ledIndicator->setState(false);
}

void MainWindow::receive(QByteArray ba){
    ledIndicator->setState(true);
    QTimer::singleShot(100, this, SLOT(ledIndicatorOff()));
    QString qstr = ByteArrayToString(ba);
    ui->tbReceive->appendHtml("<font color=\"blue\">"+qstr+"</font>");
    app_main_on_data_recv(ba);
}

bool MainWindow::send(QByteArray ba){
    if(ui->wg_com->send(ba) == Com::COM_SEND_SUCCESS){
        ledIndicator->setState(true);
        QTimer::singleShot(100, this, SLOT(ledIndicatorOff()));
        QString qstr = ByteArrayToString(ba);
        ui->tbReceive->appendHtml("<font color=\"green\">"+qstr+"</font>");
        return true;
    }
    return false;
}

bool MainWindow::send(uint8_t* arr, uint16_t len){
    return send(QByteArray::fromRawData(reinterpret_cast<char*>(arr),len));
}

void MainWindow::com_connection_evt(Com::com_evt_t evt){
    switch (evt) {
    case Com::SERIAL_OPEN_SUCCESS:
        showStatus("Serial port opened",1000);
        break;
    case Com::SERIAL_OPEN_FAIL:
        showStatus("Unable to open serial port",1000);
        break;
    case Com::SERIAL_CLOSED:
        showStatus("Serial port closed",1000);
        break;
    case Com::TCP_SERVER_OPEN_SUCCESS:
        showStatus("TCP server opened",1000);
        break;
    case Com::TCP_SERVER_OPEN_FAIL:
        showStatus("Unable to open TCP server",1000);
        break;
    case Com::TCP_SERVER_CLOSED:
        showStatus("TCP server closed",1000);
        break;
    case Com::SOCKET_CONNECTION_OPEN:
        showStatus("Socket opened",1000);
        break;
    case Com::SOCKET_CONNECTION_CLOSE:
        showStatus("Socket closed",1000);
        break;
    }
}

void MainWindow::on_btn_respond_ok_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_respond_pack(0,0,&msg,RESPOND_OK);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    if(send(mav_send_buf, len)){
        showStatus("Respond OK",1000);
   }
   else{
       showStatus("Cannot send respond OK",1000);
   }
}

void MainWindow::on_btnSend_clicked()
{
    if(!send(ui->tbSend->text().toStdString().c_str())){
        showStatus("Unable to send",1000);
    }
}
