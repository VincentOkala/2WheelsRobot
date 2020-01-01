#include "mode_pidt_ta.h"
#include "ui_mode_pidt_ta.h"

Mode_pidt_ta::Mode_pidt_ta(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mode_pidt_ta)
{
    ui->setupUi(this);
}

Mode_pidt_ta::~Mode_pidt_ta()
{
    delete ui;
}
