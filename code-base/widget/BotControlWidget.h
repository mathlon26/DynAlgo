#ifndef BOTCONTROLWIDGET_H
#define BOTCONTROLWIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class BotControlWidget;
}

class TradingController;

class BotControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BotControlWidget(TradingController *controller, QWidget *parent = nullptr);
    ~BotControlWidget();

public slots:
    void onStarted();
    void onPaused();
    void onUnpaused();
    void onStopped();

private:
    Ui::BotControlWidget *ui;
};

#endif // BOTCONTROLWIDGET_H
