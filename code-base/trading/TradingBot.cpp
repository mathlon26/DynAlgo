#include "TradingBot.h"
#include "trading/event/listener/CandleCloseEventListeners.h"
#include "trading/event/listener/StartEventListener.h"
#include "trading/event/listener/PauseEventListener.h"
#include "trading/event/listener/UnpauseEventListener.h"
#include "trading/event/listener/StopEventListener.h"
#include "trading/TradingStrategy.h"

std::function<TradingBot*(TradingController*)> TradingBot::FACTORY = nullptr;

TradingBot::TradingBot(TradingStrategy *strategy, TradingController *controller)
    : QObject{controller}
    , controller{controller}
    , strategy{strategy}
{
}

void TradingBot::setFactory(std::function<TradingBot*(TradingController*)> factory)
{
    FACTORY = std::move(factory);
}

TradingBot *TradingBot::create(TradingController* controller)
{
    if (FACTORY)
        return FACTORY(controller);
    else
        return nullptr;
}

void TradingBot::listenTo(TradingStrategy* strategy, std::initializer_list<Event::On> eventTypes)
{
    for (auto eventType : eventTypes) {
        listenTo(strategy, eventType);
    }
}

void TradingBot::subscribe(IEventListener *listener)
{
    controller->registerListener(listener);
}


void TradingBot::listenTo(TradingStrategy* strategy, Event::On eventType)
{
    using ListenerFactory = std::function<IEventListener*()>;

    const std::unordered_map<Event::On, ListenerFactory> factoryMap = {
        { Event::On::Start,        [=]() { return new StartEventListener([=](const StartEvent& e) { strategy->on_Start(e); }); } },
        { Event::On::Pause,        [=]() { return new PauseEventListener([=](const PauseEvent& e) { strategy->on_Pause(e); }); } },
        { Event::On::Unpause,      [=]() { return new UnpauseEventListener([=](const UnpauseEvent& e) { strategy->on_Unpause(e); }); } },
        { Event::On::Stop,         [=]() { return new StopEventListener([=](const StopEvent& e) { strategy->on_Stop(e); }); } },

        { Event::On::m1CandleClose,  [=]() { return new m1CandleCloseEventListener([=](const m1CandleCloseEvent& e) { strategy->on_m1CandleClose(e); }); } },
        { Event::On::m5CandleClose,  [=]() { return new m5CandleCloseEventListener([=](const m5CandleCloseEvent& e) { strategy->on_m5CandleClose(e); }); } },
        { Event::On::m15CandleClose, [=]() { return new m15CandleCloseEventListener([=](const m15CandleCloseEvent& e) { strategy->on_m15CandleClose(e); }); } },
        { Event::On::m30CandleClose, [=]() { return new m30CandleCloseEventListener([=](const m30CandleCloseEvent& e) { strategy->on_m30CandleClose(e); }); } },

        { Event::On::H1CandleClose,  [=]() { return new H1CandleCloseEventListener([=](const H1CandleCloseEvent& e) { strategy->on_H1CandleClose(e); }); } },
        { Event::On::H2CandleClose,  [=]() { return new H2CandleCloseEventListener([=](const H2CandleCloseEvent& e) { strategy->on_H2CandleClose(e); }); } },
        { Event::On::H4CandleClose,  [=]() { return new H4CandleCloseEventListener([=](const H4CandleCloseEvent& e) { strategy->on_H4CandleClose(e); }); } },
        { Event::On::H8CandleClose,  [=]() { return new H8CandleCloseEventListener([=](const H8CandleCloseEvent& e) { strategy->on_H8CandleClose(e); }); } },
        { Event::On::H12CandleClose, [=]() { return new H12CandleCloseEventListener([=](const H12CandleCloseEvent& e) { strategy->on_H12CandleClose(e); }); } },

        { Event::On::D1CandleClose,  [=]() { return new D1CandleCloseEventListener([=](const D1CandleCloseEvent& e) { strategy->on_D1CandleClose(e); }); } },
        { Event::On::W1CandleClose,  [=]() { return new W1CandleCloseEventListener([=](const W1CandleCloseEvent& e) { strategy->on_W1CandleClose(e); }); } },
        { Event::On::M1CandleClose,  [=]() { return new M1CandleCloseEventListener([=](const M1CandleCloseEvent& e) { strategy->on_M1CandleClose(e); }); } },
        { Event::On::M4CandleClose,  [=]() { return new M4CandleCloseEventListener([=](const M4CandleCloseEvent& e) { strategy->on_M4CandleClose(e); }); } },
        { Event::On::M6CandleClose,  [=]() { return new M6CandleCloseEventListener([=](const M6CandleCloseEvent& e) { strategy->on_M6CandleClose(e); }); } },
        { Event::On::Y1CandleClose,  [=]() { return new Y1CandleCloseEventListener([=](const Y1CandleCloseEvent& e) { strategy->on_Y1CandleClose(e); }); } },
    };

    auto it = factoryMap.find(eventType);
    if (it != factoryMap.end())
    {
        IEventListener* listener = it->second();
        subscribe(listener);
    }
}
