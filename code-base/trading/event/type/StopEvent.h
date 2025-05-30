#ifndef STOPEVENT_H
#define STOPEVENT_H


#include <QObject>

#include "trading/event/Event.h"

class StopEvent : public Event
{
public:
    StopEvent() : Event() {}

    On type() const override { return On::Stop; }

signals:
};


#endif // STOPEVENT_H
