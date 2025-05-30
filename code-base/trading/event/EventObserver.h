#ifndef EVENTOBSERVER_H
#define EVENTOBSERVER_H

#include <QObject>
#include <QTimer>
#include "trading/event/EventHandler.h"
#include "trading/event/Event.h"
#include "trading/event/observer/CandleCloseEventObserver.h"

class EventObserver : public QObject
{
    Q_OBJECT
public:
    explicit EventObserver(EventHandler* handler, QObject* parent = nullptr)
        : QObject(parent), eventHandler(handler)
        , candleObserver(new CandleCloseEventObserver(handler, this))
    {
        timer.setInterval(100);
        connect(&timer, &QTimer::timeout, this, &EventObserver::pollEvents);
        timer.start();
    }

    void raiseEvent(const Event& event) {
        if (eventHandler) {
            eventHandler->dispatch(event);
        }
    }

private slots:
    void pollEvents() {

        // poll for candle close events
        candleObserver->poll();
    }

private:
    EventHandler* eventHandler = nullptr;  // Not owned
    QScopedPointer<CandleCloseEventObserver> candleObserver;
    QTimer timer;
};

#endif // EVENTOBSERVER_H
