#include "CustomTradingStrategy.h"

#include "trading/event/type/StartEvent.h"
#include "trading/event/type/StopEvent.h"
#include "trading/event/type/PauseEvent.h"
#include "trading/event/type/UnpauseEvent.h"

CustomTradingStrategy::CustomTradingStrategy(TradingAPI *api, TradingBot *tradingBot)
    : TradingStrategy{api, tradingBot}
{

    tradingBot->listenTo(this, { On::Start });
}

void CustomTradingStrategy::on_Start(const StartEvent& event)
{
    // qDebug() << "Event (" << static_cast<int>(event.type()) << ") called";
}

void CustomTradingStrategy::on_Pause(const PauseEvent& event)
{
    // qDebug() << "Event (" << static_cast<int>(event.type()) << ") called";
}

void CustomTradingStrategy::on_Unpause(const UnpauseEvent& event)
{
    // qDebug() << "Event (" << static_cast<int>(event.type()) << ") called";
}

void CustomTradingStrategy::on_Stop(const StopEvent& event)
{
    // qDebug() << "Event (" << static_cast<int>(event.type()) << ") called";
}
