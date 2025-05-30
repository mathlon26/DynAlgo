#ifndef CANDLE_H
#define CANDLE_H

#include <QDateTime>
#include "TimeFrame.h"

class Candle
{
public:
    QString symbol;
    TimeFrame timeframe;

    QDateTime openTime;
    double open = 0.0;
    double high = 0.0;
    double low = 0.0;
    double close = 0.0;
    double volume = 0.0;
};

#endif // CANDLE_H
