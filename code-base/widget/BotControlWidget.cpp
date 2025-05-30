#include "BotControlWidget.h"
#include "ui_BotControlWidget.h"

#include "trading/TradingController.h"

BotControlWidget::BotControlWidget(TradingController *controller, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BotControlWidget)
{
    ui->setupUi(this);

    connect(ui->StartButton, &QPushButton::clicked, controller, &TradingController::onStartPress);
    connect(ui->PauseButton, &QPushButton::clicked, controller, &TradingController::onPausePress);
    connect(ui->StopButton, &QPushButton::clicked, controller, &TradingController::onStopPress);

    connect(controller, &TradingController::started, this, &BotControlWidget::onStarted);
    connect(controller, &TradingController::paused, this, &BotControlWidget::onPaused);
    connect(controller, &TradingController::unpaused, this, &BotControlWidget::onUnpaused);
    connect(controller, &TradingController::stopped, this, &BotControlWidget::onStopped);

    ui->StartButton->setDisabled(false);
    ui->PauseButton->setDisabled(true);
    ui->StopButton->setDisabled(true);
}

void BotControlWidget::onStarted()
{
    ui->StartButton->setDisabled(true);
    ui->PauseButton->setDisabled(false);
    ui->StopButton->setDisabled(false);
}

void BotControlWidget::onPaused()
{
    ui->PauseButton->setText("Resume");
}

void BotControlWidget::onUnpaused()
{
    ui->PauseButton->setText("Pause");
}

void BotControlWidget::onStopped()
{
    ui->StartButton->setDisabled(false);
    ui->PauseButton->setText("Pause");
    ui->PauseButton->setDisabled(true);
    ui->StopButton->setDisabled(true);
}

BotControlWidget::~BotControlWidget()
{
    delete ui;
}
