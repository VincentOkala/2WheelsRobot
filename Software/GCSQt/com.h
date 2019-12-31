#ifndef COM_H
#define COM_H

#include <QWidget>

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Com;
}

class Com : public QWidget
{
    Q_OBJECT

public:
    explicit Com(QWidget *parent = nullptr);
    ~Com();

    typedef enum{
        // Serial event
        SERIAL_OPEN_SUCCESS,
        SERIAL_OPEN_FAIL,
        SERIAL_CLOSED,

        // TCP event
        TCP_SERVER_OPEN_SUCCESS,
        TCP_SERVER_OPEN_FAIL,
        TCP_SERVER_CLOSED,

        // Socket event
        SOCKET_CONNECTION_OPEN,
        SOCKET_CONNECTION_CLOSE
    }com_evt_t;

    typedef enum{
        COM_SEND_SUCCESS,
        COM_SEND_FAIL
    }com_send_t;

    com_send_t send(QByteArray bytes);

signals:
    void on_ba_recv(QByteArray ba);
    void on_connection_evt(Com::com_evt_t evt);

private slots:

    // Serial slot
    void on_serial_data_ready();

    // Socker slot
    void on_new_connection();
    void on_socket_data_ready();
    void on_socket_state_changed(QAbstractSocket::SocketState socketState);

    void on_btn_open_com_clicked();
    void on_btn_open_server_clicked();

private:
    Ui::Com *ui;
    QSerialPort *g_serial;
    QTcpServer *g_tcp_server;
    QTcpSocket *g_socket;


};

#endif // COM_H
