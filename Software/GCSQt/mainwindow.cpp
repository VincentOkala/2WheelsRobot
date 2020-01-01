#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("GCS");

    g_led_indicator = new Led_indicator();
    ui->statusBar->addPermanentWidget(g_led_indicator);

    g_mode_run = new Mode_run();
    ui->Maintab->addTab(g_mode_run,"Mode Run");

    g_com_gui = new Com_gui();
    ui->Maintab->addTab(g_com_gui,"Com");

    // Com
    connect(ui->wg_com,SIGNAL(ba_recv(QByteArray)),this,SLOT(app_main_on_data_recv(QByteArray)));
    connect(ui->wg_com,SIGNAL(connection_evt(Com::com_evt_t)),this,SLOT(com_connection_evt(Com::com_evt_t)));

    ui->wg_com->set_com_gui(g_com_gui);
    ui->wg_com->set_led_indicator(g_led_indicator);

    // Joystick
    g_qjs = QJoysticks::getInstance();
    g_qjs->setVirtualJoystickRange(1);
    connect(g_qjs,SIGNAL(axisChanged(const int, const int, const qreal)),this,SLOT(js_axis_change(const int, const int, const qreal)));

    controller_timer = new QTimer(this);

    for(int i=0;i<=3;i++){
        ui->plot_0->addGraph();
        ui->plot_0->graph(i)->setPen(QPen(QColor(0,50*i,50*i)));

        ui->plot_2->addGraph();
        ui->plot_2->graph(i)->setPen(QPen(QColor(50*i,0,50*i)));

        ui->plot_4->addGraph();
        ui->plot_4->graph(i)->setPen(QPen(QColor(50*i,50*i,0)));
    }

    for(int i=0;i<=1;i++){
        ui->plot_1->addGraph();
        ui->plot_1->graph(i)->setPen(QPen(QColor(0,50*i,50*i)));

        ui->plot_3->addGraph();
        ui->plot_3->graph(i)->setPen(QPen(QColor(50*i,0,50*i)));

        ui->plot_5->addGraph();
        ui->plot_5->graph(i)->setPen(QPen(QColor(50*i,50*i,0)));
    }

    app_main_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showStatus(QString qstr, int timeout){
    ui->statusBar->showMessage(qstr,timeout);
}

void MainWindow::com_connection_evt(Com::com_evt_t evt){
    switch (evt) {
    case Com::SERIAL_OPEN_SUCCESS:
        showStatus("Serial port opened",1000);
        break;
    case Com::SERIAL_OPEN_FAIL:
        showStatus("Unable to open serial port",1000);
        break;
    case Com::SERIAL_CLOSED:
        showStatus("Serial port closed",1000);
        break;
    case Com::TCP_SERVER_OPEN_SUCCESS:
        showStatus("TCP server opened",1000);
        break;
    case Com::TCP_SERVER_OPEN_FAIL:
        showStatus("Unable to open TCP server",1000);
        break;
    case Com::TCP_SERVER_CLOSED:
        showStatus("TCP server closed",1000);
        break;
    case Com::SOCKET_CONNECTION_OPEN:
        showStatus("Socket opened",1000);
        break;
    case Com::SOCKET_CONNECTION_CLOSE:
        showStatus("Socket closed",1000);
        break;
    }
}

void MainWindow::js_axis_change(const int js, const int axis, const qreal value){
    Q_UNUSED(js)
    if(axis == 0){
            ui->txtBoxOMEGA->setText((QString::number(-value)));
            ui->txtb_pidt_w->setText((QString::number(-value)));
    }
    else if(axis == 1){
            ui->txtBoxVX->setText(QString::number((-value)));
            ui->txtb_pidt_vx->setText((QString::number(-value)));
    }
}
