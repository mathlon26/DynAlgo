#include "TradingController.h"
#include "TradingBot.h"

#include "trading/event/type/StartEvent.h"
#include "trading/event/type/StopEvent.h"
#include "trading/event/type/PauseEvent.h"
#include "trading/event/type/UnpauseEvent.h"

TradingController::TradingController(QObject *parent)
    : QObject{parent}
    , tradingBot{nullptr}
    , eventHandler{new EventHandler{this}}
    , eventObserver{new EventObserver{eventHandler, this}}
    , isPaused{false}
    , isActive{false}
{}

void TradingController::registerListener(IEventListener *listener)
{
    eventHandler->subscribe(listener);
}

void TradingController::onStartPress()
{
    if (isActive)
        return;

    eventHandler->reset();

    if (tradingBot)
        delete tradingBot;

    TradingBot *newBot = TradingBot::create(this);
    tradingBot = newBot;

    eventObserver->raiseEvent(StartEvent{});
    isActive = true;

    emit started();
}

void TradingController::onPausePress()
{
    if (!tradingBot || !isActive)
        return;

    if (isPaused) {
        eventObserver->raiseEvent( UnpauseEvent{} );
        isPaused = false;
        emit unpaused();
    }

    else {
        eventObserver->raiseEvent( PauseEvent{} );
        isPaused = true;
        emit paused();
    }
}

void TradingController::onStopPress()
{
    if (!tradingBot || !isActive)
        return;

    eventObserver->raiseEvent( StopEvent{} );

    delete tradingBot;
    tradingBot = nullptr;

    isActive = false;
    isPaused = false;

    emit stopped();
}

