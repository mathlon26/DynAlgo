#ifndef APPLICATION_H
#define APPLICATION_H

#include "trading/TradingBot.h"
#include "trading/api/TradingAPI.h"

template <typename TStrategy, typename TApi>
class Application : public TradingBot
{
    static_assert(std::is_base_of<TradingStrategy, TStrategy>::value, "TStrategy must inherit from TradingStrategy");
    static_assert(std::is_base_of<TradingAPI, TApi>::value, "TApi must inherit from TradingAPI");
public:
    explicit Application(TradingController *controller)
        : TradingBot{&strategy, controller}
        , api{}
        , strategy(&api, this)
    {}

private:
    TApi api;
    TStrategy strategy;
};

namespace DynalgoApplication {
    template<typename Strategy, typename Api>
    static void Start()
    {
        TradingBot::setFactory([=](TradingController *controller){
            return new Application<Strategy, Api>{controller};
        });
    }
}

#endif // APPLICATION_H
