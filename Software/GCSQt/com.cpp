#include "com.h"
#include "ui_com.h"

Com::Com(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Com)
{
    ui->setupUi(this);

    ui->cb_serial_port->clear();
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        ui->cb_serial_port->addItem(port.portName());
    }

    g_serial = new QSerialPort();
    connect(g_serial,  SIGNAL(readyRead()), this, SLOT(on_serial_data_ready()));

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             ui->tb_server_ip->setText(address.toString());
    }

    g_tcp_server = new QTcpServer();
    connect(g_tcp_server, SIGNAL(newConnection()), this, SLOT(on_new_connection()));
    g_socket = new QTcpSocket();
}

Com::~Com()
{
    delete ui;
}

void Com::on_btn_open_server_clicked()
{
    if(g_tcp_server->isListening()){
        ui->tb_server_ip->setEnabled(true);
        ui->tb_server_port->setEnabled(true);
        ui->btn_open_server->setText("Open");
        if(g_socket->isOpen()) g_socket->close();
        ui->tb_connected_ip->setText("");
        g_tcp_server->close();
        emit on_connection_evt(TCP_SERVER_CLOSED);
    }
    else{
        if(g_tcp_server->listen(QHostAddress::Any, static_cast<quint16>(ui->tb_server_port->text().toInt()))){
            ui->tb_server_ip->setEnabled(false);
            ui->tb_server_port->setEnabled(false);
            ui->btn_open_server->setText("Close");
            emit on_connection_evt(TCP_SERVER_OPEN_SUCCESS);
        }
        else{
            emit on_connection_evt(TCP_SERVER_OPEN_FAIL);
        }
    }
}

void Com::on_btn_open_com_clicked()
{

    if(g_serial->isOpen()){
        g_serial->clear();
        ui->btn_open_com->setText("Open");
        ui->cb_serial_port->setEnabled(true);
        ui->cb_baud->setEnabled(true);
        g_serial->close();
        emit on_connection_evt(SERIAL_CLOSED);
    }
    else{
        g_serial->setPortName(ui->cb_serial_port->currentText());
        g_serial->setBaudRate(ui->cb_baud->currentText().toInt());
        if(g_serial->open(QIODevice::ReadWrite)){
            ui->btn_open_com->setText("Close");
            ui->cb_serial_port->setEnabled(false);
            ui->cb_baud->setEnabled(false);
            emit on_connection_evt(SERIAL_OPEN_SUCCESS);
        }
        else{
            emit on_connection_evt(SERIAL_OPEN_FAIL);
        }
    }
}


void Com::on_serial_data_ready()
{
    const QByteArray ba = g_serial->readAll();
    emit on_ba_recv(ba);
}

void Com::on_new_connection(){
    if(!g_socket->isOpen()){
        g_socket = g_tcp_server->nextPendingConnection();
        connect(g_socket, SIGNAL(readyRead()), this, SLOT(on_socket_data_ready()));
        connect(g_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(on_socket_state_changed(QAbstractSocket::SocketState)));
        g_tcp_server->pauseAccepting();
        ui->tb_connected_ip->setText(g_socket->peerAddress().toString());
        emit on_connection_evt(SOCKET_CONNECTION_OPEN);
    }
}

void Com::on_socket_data_ready(){
    const QByteArray ba = g_socket->readAll();
    emit on_ba_recv(ba);
}

void Com::on_socket_state_changed(QAbstractSocket::SocketState socketState){
    if(g_socket->isOpen() && socketState==QAbstractSocket::SocketState::ClosingState){
        g_socket->close();
        g_tcp_server->resumeAccepting();
        ui->tb_connected_ip->setText("");
        emit on_connection_evt(SOCKET_CONNECTION_CLOSE);
    }
}

Com::com_send_t Com::send(QByteArray bytes){
    bool serialSuccess = false;
    bool socketSuccess = false;

    if(g_serial->isOpen()){
        if(g_serial->write(bytes)){
            serialSuccess = true;
        }

    }
    if(g_socket->isOpen()){
        if(g_socket->write(bytes)){
            socketSuccess = true;
        }
    }

    if(serialSuccess || socketSuccess){
        return Com::COM_SEND_SUCCESS;
    }
    else{
        return Com::COM_SEND_FAIL;
    }
}
