#ifndef CUSTOMTRADINGSTRATEGY_H
#define CUSTOMTRADINGSTRATEGY_H

#include "trading/TradingStrategy.h"


class CustomTradingStrategy : public TradingStrategy
{
public:
    explicit CustomTradingStrategy(TradingAPI *api, TradingBot *parent = nullptr);

    void on_Start(const StartEvent& event) override;
    void on_Pause(const PauseEvent& event) override;
    void on_Unpause(const UnpauseEvent& event) override;
    void on_Stop(const StopEvent& event) override;

};

#endif // CUSTOMTRADINGSTRATEGY_H
