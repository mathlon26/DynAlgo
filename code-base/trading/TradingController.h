#ifndef TRADINGCONTROLLER_H
#define TRADINGCONTROLLER_H

#include <QObject>

#include "trading/event/EventHandler.h"
#include "trading/event/EventObserver.h"

class TradingBot;

class TradingController : public QObject
{
    Q_OBJECT
public:
    explicit TradingController(QObject *parent = nullptr);

    void registerListener(IEventListener *listener);

public slots:
    void onStartPress();
    void onStopPress();
    void onPausePress();
private:
    TradingBot *tradingBot;
    EventHandler *eventHandler;
    EventObserver *eventObserver;

    bool isPaused;
    bool isActive;

signals:
    void started();
    void paused();
    void unpaused();
    void stopped();
};

#endif // TRADINGCONTROLLER_H
