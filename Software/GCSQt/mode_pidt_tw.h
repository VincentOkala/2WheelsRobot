#ifndef MODE_PIDT_TW_H
#define MODE_PIDT_TW_H

#include <QWidget>

namespace Ui {
class Mode_pidt_tw;
}

class Mode_pidt_tw : public QWidget
{
    Q_OBJECT

public:
    explicit Mode_pidt_tw(QWidget *parent = nullptr);
    ~Mode_pidt_tw();

private:
    Ui::Mode_pidt_tw *ui;
};

#endif // MODE_PIDT_TW_H
