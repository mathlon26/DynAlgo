#ifndef UNPAUSEEVENT_H
#define UNPAUSEEVENT_H

#include <QObject>

#include "trading/event/Event.h"

class UnpauseEvent : public Event
{
public:
    UnpauseEvent() : Event() {}

    On type() const override { return On::Unpause; }
signals:
};


#endif // UNPAUSEEVENT_H
