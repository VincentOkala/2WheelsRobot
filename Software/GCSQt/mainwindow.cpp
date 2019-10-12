#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("GCS");

    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        ui->cbCOM->addItem(port.portName());
    }

    ui->cbBaud->addItem("115200");
    ui->cbBaud->addItem("9600");

    m_serial = new QSerialPort();
    connect(m_serial,  SIGNAL(readyRead()), this, SLOT(on_COMData_ready()));

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             ui->tbIPAddress->setText(address.toString());
    }

    tcpServer = new QTcpServer();
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(on_newConnection()));
    socket = new QTcpSocket();
    ledIndicator = new LedIndicator();
    ui->statusBar->addPermanentWidget(ledIndicator);

//    ui->txtBoxRoll->setDisabled(true);
//    ui->txtBoxPitch->setDisabled(true);
//    ui->txtBoxYaw->setDisabled(true);
//    ui->txtBoxMPU->setDisabled(true);

    app_main_init();
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

bool MainWindow::send(QByteArray bytes){
    bool serialSuccess = false;
    bool socketSuccess = false;
    if(m_serial->isOpen()){
        if(m_serial->write(bytes)){
            serialSuccess = true;
        }

    }
    if(socket->isOpen()){
        if(socket->write(bytes)){
            socketSuccess = true;
        }
    }
    if(serialSuccess || socketSuccess){
        ledIndicator->setState(true);
        QTimer::singleShot(100, this, SLOT(ledIndicatorOff()));
        QString qstr = ByteArrayToString(bytes);
        ui->tbReceive->appendHtml("<font color=\"green\">"+qstr+"</font>");
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::receive(QByteArray bytes){
    ledIndicator->setState(true);
    QTimer::singleShot(100, this, SLOT(ledIndicatorOff()));
    QString qstr = ByteArrayToString(bytes);
    ui->tbReceive->appendHtml("<font color=\"blue\">"+qstr+"</font>");
    app_main_on_data_recv(bytes);
}

void MainWindow::on_btnOpenCOM_clicked()
{
    if(m_serial->isOpen()){
        m_serial->clear();
        ui->btnOpenCOM->setText("Open");
        ui->cbCOM->setEnabled(true);
        ui->cbBaud->setEnabled(true);
        m_serial->close();
    }
    else{
        m_serial->setPortName(ui->cbCOM->currentText());
        m_serial->setBaudRate(ui->cbBaud->currentText().toInt());
        if(m_serial->open(QIODevice::ReadWrite)){
            ui->btnOpenCOM->setText("Close");
            ui->cbCOM->setEnabled(false);
            ui->cbBaud->setEnabled(false);
        }
        else{
            showStatus("Cannot open com port",2000);
        }
    }
}

void MainWindow::on_btnSend_clicked()
{
    if(!send(ui->tbSend->text().toStdString().c_str())){
        showStatus("Error to send",1000);
    }
}

void MainWindow::on_COMData_ready()
{
    const QByteArray data = m_serial->readAll();
    receive(data);
}

void MainWindow::on_newConnection(){
    if(!socket->isOpen()){
        socket = tcpServer->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), this, SLOT(on_ReadyRead()));
        connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(on_SocketStateChanged(QAbstractSocket::SocketState)));
        tcpServer->pauseAccepting();
        showStatus("Connected from:" +socket->peerAddress().toString(),2000);
        ui->tbConnectedIP->setText(socket->peerAddress().toString());
    }
}

void MainWindow::on_ReadyRead(){
    if(socket->isOpen()){
        const QByteArray data = socket->readAll();
        receive(data);
    }
}

void MainWindow::on_SocketStateChanged(QAbstractSocket::SocketState socketState){
    if(socket->isOpen() && socketState==QAbstractSocket::SocketState::ClosingState){
        socket->close();
        tcpServer->resumeAccepting();
        ui->tbConnectedIP->setText("");
    }
}

void MainWindow::on_btnOpenServer_clicked()
{
    if(tcpServer->isListening()){
        ui->tbIPAddress->setEnabled(true);
        ui->tbPort->setEnabled(true);
        ui->btnOpenServer->setText("Open");
        if(socket->isOpen()) socket->close();
        ui->tbConnectedIP->setText("");
        tcpServer->close();
    }
    else{
        if(tcpServer->listen(QHostAddress::Any, static_cast<quint16>(ui->tbPort->text().toInt()))){
            ui->tbIPAddress->setEnabled(false);
            ui->tbPort->setEnabled(false);
            ui->btnOpenServer->setText("Close");
        }
        else{
            showStatus("Cannot open tcp server",2000);
        }
    }
}

void MainWindow::on_btn_respond_ok_clicked()
{
    mavlink_message_t msg;
    uint8_t mav_send_buf[255];
    mavlink_msg_evt_respond_pack(0,0,&msg,RESPOND_OK);
    uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &msg);
    if(send(QByteArray::fromRawData((char*)(mav_send_buf),len))){
        showStatus("Sending Respond OK",1000);
   }
   else{
       showStatus("Cannot Send Respond OK",1000);
   }
}
