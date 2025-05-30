#ifndef STARTEVENTLISTENER_H
#define STARTEVENTLISTENER_H

#include "trading/event/EventListener.h"
#include "trading/event/type/StartEvent.h"

class StartEventListener : public EventListener<StartEvent>
{
public:
    StartEventListener(std::function<void(const StartEvent&)> action)
        : EventListener<StartEvent>(Event::On::Start, std::move(action)) {}
};

#endif // STARTEVENTLISTENER_H
