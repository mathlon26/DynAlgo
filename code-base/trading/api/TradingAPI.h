#ifndef TRADINGAPI_H
#define TRADINGAPI_H

#include "WebAPI.h"

class TradingAPI : public WebAPI
{
    Q_OBJECT
public:
    explicit TradingAPI(QObject *parent = nullptr);
};

#endif // TRADINGAPI_H
