#include "mode_pidt_tw.h"
#include "ui_mode_pidt_tw.h"

Mode_pidt_tw::Mode_pidt_tw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mode_pidt_tw)
{
    ui->setupUi(this);
}

Mode_pidt_tw::~Mode_pidt_tw()
{
    delete ui;
}
