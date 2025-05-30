#ifndef PAUSEEVENT_H
#define PAUSEEVENT_H


#include "trading/event/Event.h"

class PauseEvent : public Event
{
public:
    PauseEvent() : Event() {}

    On type() const override { return On::Pause; }
signals:
};


#endif // PAUSEEVENT_H
