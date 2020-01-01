#ifndef MODE_PIDT_TA_H
#define MODE_PIDT_TA_H

#include <QWidget>

namespace Ui {
class Mode_pidt_ta;
}

class Mode_pidt_ta : public QWidget
{
    Q_OBJECT

public:
    explicit Mode_pidt_ta(QWidget *parent = nullptr);
    ~Mode_pidt_ta();

private:
    Ui::Mode_pidt_ta *ui;
};

#endif // MODE_PIDT_TA_H
