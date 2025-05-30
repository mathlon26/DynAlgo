#ifndef TRADINGSTRATEGY_H
#define TRADINGSTRATEGY_H

#include <QObject>

#include "trading/api/TradingAPI.h"
#include "trading/TradingController.h"
#include "trading/event/type/CandleCloseEvents.h"
#include "trading/event/type/StartEvent.h"
#include "trading/event/type/PauseEvent.h"
#include "trading/event/type/UnpauseEvent.h"
#include "trading/event/type/StopEvent.h"
#include "trading/TradingBot.h"

using On = Event::On;

class TradingBot;

class TradingStrategy : public QObject
{
    Q_OBJECT
public:
    explicit TradingStrategy(TradingAPI *api, TradingBot *tradingBot)
        : QObject{tradingBot}, API(api)
    {
        tradingBot->listenTo(this, On::Stop);
    }

    virtual void on_Start(const StartEvent&) {}
    virtual void on_Pause(const PauseEvent&) {}
    virtual void on_Unpause(const UnpauseEvent&) {}
    virtual void on_Stop(const StopEvent&) {}

    virtual void on_m1CandleClose(const m1CandleCloseEvent&) {}
    virtual void on_m5CandleClose(const m5CandleCloseEvent&) {}
    virtual void on_m15CandleClose(const m15CandleCloseEvent&) {}
    virtual void on_m30CandleClose(const m30CandleCloseEvent&) {}
    virtual void on_H1CandleClose(const H1CandleCloseEvent&) {}
    virtual void on_H2CandleClose(const H2CandleCloseEvent&) {}
    virtual void on_H4CandleClose(const H4CandleCloseEvent&) {}
    virtual void on_H8CandleClose(const H8CandleCloseEvent&) {}
    virtual void on_H12CandleClose(const H12CandleCloseEvent&) {}
    virtual void on_D1CandleClose(const D1CandleCloseEvent&) {}
    virtual void on_W1CandleClose(const W1CandleCloseEvent&) {}
    virtual void on_M1CandleClose(const M1CandleCloseEvent&) {}
    virtual void on_M4CandleClose(const M4CandleCloseEvent&) {}
    virtual void on_M6CandleClose(const M6CandleCloseEvent&) {}
    virtual void on_Y1CandleClose(const Y1CandleCloseEvent&) {}

protected:
    TradingAPI *API;
};

#endif // TRADINGSTRATEGY_H
