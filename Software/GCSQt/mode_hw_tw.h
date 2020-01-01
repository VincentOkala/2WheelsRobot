#ifndef MODE_HW_TW_H
#define MODE_HW_TW_H

#include <QWidget>

namespace Ui {
class mode_hw_tw;
}

class mode_hw_tw : public QWidget
{
    Q_OBJECT

public:
    explicit mode_hw_tw(QWidget *parent = nullptr);
    ~mode_hw_tw();

private:
    Ui::mode_hw_tw *ui;
};

#endif // MODE_HW_TW_H
