#ifndef STOPEVENTLISTENER_H
#define STOPEVENTLISTENER_H

#include "trading/event/EventListener.h"
#include "trading/event/type/StopEvent.h"

class StopEventListener : public EventListener<StopEvent>
{
public:
    StopEventListener(std::function<void(const StopEvent&)> action)
        : EventListener<StopEvent>(Event::On::Stop, std::move(action)) {}
};


#endif // STOPEVENTLISTENER_H
