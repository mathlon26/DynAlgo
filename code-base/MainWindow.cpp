#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QVBoxLayout>
#include "widget/BotControlWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(new TradingController{})
{
    ui->setupUi(this);

    QWidget* central = new QWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout(central);
    BotControlWidget* botWidget = new BotControlWidget(controller, central);
    vbox->addWidget(botWidget);
    setCentralWidget(central);
}

MainWindow::~MainWindow()
{
    delete ui;
}
