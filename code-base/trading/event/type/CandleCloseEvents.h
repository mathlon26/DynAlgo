#ifndef CANDLECLOSEEVENTS_H
#define CANDLECLOSEEVENTS_H


#include "trading/event/type/CandleClose.h"

// Macro to reduce boilerplate
#define DECLARE_CANDLE_CLOSE_EVENT_CLASS(className, enumName)      \
class className##CandleCloseEvent : public CandleClose             \
{                                                      \
    public:                                                           \
    className##CandleCloseEvent() \
    : CandleClose() {}                                   \
                                                                  \
        On type() const override { return On::enumName; }             \
                                                                  \
        void setCloseTime(const QDateTime& time) override {           \
            m_closeTime = time;                                        \
    }                                                             \
                                                                  \
        void setCandle(const Candle& candle) override {               \
            m_candle = candle;                                         \
    }                                                             \
                                                                  \
        QDateTime closeTime() const override { return m_closeTime; }  \
        Candle candle() const override { return m_candle; }           \
                                                                  \
    private:                                                          \
    QDateTime m_closeTime;                                         \
        Candle m_candle;                                               \
};

// Declare all classes here

DECLARE_CANDLE_CLOSE_EVENT_CLASS(m1, m1CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(m5, m5CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(m15, m15CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(m30, m30CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(H1, H1CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(H2, H2CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(H4, H4CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(H8, H8CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(H12, H12CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(D1, D1CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(W1, W1CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(M1, M1CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(M4, M4CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(M6, M6CandleClose)
DECLARE_CANDLE_CLOSE_EVENT_CLASS(Y1, Y1CandleClose)

#undef DECLARE_CANDLE_CLOSE_EVENT_CLASS

#endif // CANDLECLOSEEVENTS_H
