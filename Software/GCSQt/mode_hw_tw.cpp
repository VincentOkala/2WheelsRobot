#include "mode_hw_tw.h"
#include "ui_mode_hw_tw.h"

mode_hw_tw::mode_hw_tw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mode_hw_tw)
{
    ui->setupUi(this);
}

mode_hw_tw::~mode_hw_tw()
{
    delete ui;
}
