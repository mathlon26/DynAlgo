#ifndef TRADINGBOT_H
#define TRADINGBOT_H

#include <QObject>
#include "trading/TradingController.h"
#include <initializer_list>


class IEventListener;
class TradingStrategy;

class TradingBot : public QObject
{
    Q_OBJECT
public:
    explicit TradingBot(TradingStrategy *strategy, TradingController *controller);

    static void setFactory(std::function<TradingBot*(TradingController*)> factory);
    static TradingBot *create(TradingController*);

    void listenTo(TradingStrategy* strategy, std::initializer_list<Event::On> eventTypes);
    void listenTo(TradingStrategy *strategy, Event::On eventType);

private:
    void subscribe(IEventListener *listener);

    static std::function<TradingBot*(TradingController*)> FACTORY;
    TradingController *controller;
    TradingStrategy *strategy;
signals:
};

#endif // TRADINGBOT_H
