#ifndef MODE_RUN_H
#define MODE_RUN_H

#include <QWidget>

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

signals:
    void send();

private slots:
    void mav_recv(mavlink_message_t *msg);

    void on_btn_control_enable_clicked();

private:
    Ui::Mode_run *ui;

    bool control_enable;

    void controller_cmd();
};

#endif // MODE_RUN_H
