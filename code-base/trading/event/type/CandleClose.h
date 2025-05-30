#ifndef CANDLECLOSE_H
#define CANDLECLOSE_H

#include <QDateTime>
#include "trading/event/Event.h"
#include "trading/model/Candle.h"

// Abstract base class for all candle close events (e.g., M5, M1)
class CandleClose : public Event
{
public:
    CandleClose() : Event() {}

    // Every derived candle close event must implement this
    virtual void setCloseTime(const QDateTime& time) = 0;
    virtual void setCandle(const Candle& candle) = 0;

    // Optional: base class can offer read access if desired
    virtual QDateTime closeTime() const = 0;
    virtual Candle candle() const = 0;
};

#endif // CANDLECLOSE_H
