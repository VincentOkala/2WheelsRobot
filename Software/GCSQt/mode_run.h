#ifndef MODE_RUN_H
#define MODE_RUN_H

#include <QWidget>
#include <QTimer>
#include <QtWidgets/QStatusBar>

#include <MAV/protocol/mavlink.h>

namespace Ui {
class Mode_run;
}

class Mode_run : public QWidget
{
    Q_OBJECT

public:
    explicit Mode_run(QWidget *parent = nullptr);
    ~Mode_run();

    void mode_run_mav_recv(mavlink_message_t *msg);
    void set_status_bar(QStatusBar *q_status_bar);

signals:
    void mode_run_mav_send(QByteArray ba);
    void mode_change(rmode_t mode);

private slots:
    void remote_controll_cmd();

    void on_btn_control_enable_clicked();
    void on_btn_change_mode_run_clicked();

private:
    Ui::Mode_run *ui;
    QStatusBar *g_q_status_bar = nullptr;
    QTimer *g_controller_timer;

    bool g_control_enable;

    void show_status(QString q_str, int timeout);
};

#endif // MODE_RUN_H
