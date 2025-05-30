#ifndef STARTEVENT_H
#define STARTEVENT_H

#include <QObject>

#include "trading/event/Event.h"

class StartEvent : public Event
{
public:
    StartEvent() : Event() {}

    On type() const override { return On::Start; }
signals:
};

#endif // STARTEVENT_H
