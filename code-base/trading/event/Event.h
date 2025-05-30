#ifndef EVENT_H
#define EVENT_H

#include <QObject>

class Event
{
public:
    enum class On {
        Start = 0, Pause, Unpause, Stop,

        m1CandleClose,
        m5CandleClose,
        m15CandleClose,
        m30CandleClose,
        H1CandleClose,
        H2CandleClose,
        H4CandleClose,
        H8CandleClose,
        H12CandleClose,
        D1CandleClose,
        W1CandleClose,
        M1CandleClose,
        M4CandleClose,
        M6CandleClose,
        Y1CandleClose,

    };

    Event() {}
    virtual ~Event() = default;

    virtual On type() const = 0;
signals:
};

#endif // EVENT_H
