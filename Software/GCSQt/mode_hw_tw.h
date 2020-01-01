#ifndef MODE_HW_TW_H
#define MODE_HW_TW_H

#include <QWidget>
#include <QtWidgets/QStatusBar>

#include <MAV/protocol/mavlink.h>
#include <mode_common.h>

namespace Ui {
class Mode_hw_tw;
}

class Mode_hw_tw : public QWidget
{
    Q_OBJECT

public:
    explicit Mode_hw_tw(QWidget *parent = nullptr);
    ~Mode_hw_tw();

    void mav_recv(mavlink_message_t *msg);

private slots:

    void on_btn_change_mode_hw_clicked();
    void on_btn_mode_hw_load_params_clicked();
    void on_btn_mode_hw_write_params_clicked();
    void on_btn_mode_hw_save_params_clicked();

private:
    Ui::Mode_hw_tw *ui;
};

#endif // MODE_HW_TW_H
