#ifndef MODE_COMMON_H
#define MODE_COMMON_H

#include <QTimer>
#include <QtWidgets/QStatusBar>

#include <MAV/protocol/mavlink.h>

class Mode_common : public QWidget
{
    Q_OBJECT

public:
    Mode_common(QWidget *parent);
    virtual ~Mode_common();

    virtual void mav_recv(mavlink_message_t *msg);
    void set_status_bar(QStatusBar *q_status_bar);

protected:
    bool g_does_st_successfullly = false;

    void show_status(QString q_str, int timeout);

    void load_params();
    void save_params();

signals:
    void mav_send(QByteArray ba);
    void mode_change(rmode_t mode);

protected slots:
    void load_timeout();
    void write_timeout();
    void save_timeout();

private:
    QStatusBar *g_q_status_bar = nullptr;

};

#endif // MODE_COMMON_H
