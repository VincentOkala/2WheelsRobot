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
    void send()

private:
    Ui::Mode_run *ui;
};

#endif // MODE_RUN_H
