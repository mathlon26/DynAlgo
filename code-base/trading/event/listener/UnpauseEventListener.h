#ifndef UNPAUSEEVENTLISTENER_H
#define UNPAUSEEVENTLISTENER_H

#include "trading/event/EventListener.h"
#include "trading/event/type/UnpauseEvent.h"

class UnpauseEventListener : public EventListener<UnpauseEvent>
{
public:
    UnpauseEventListener(std::function<void(const UnpauseEvent&)> action)
        : EventListener<UnpauseEvent>(Event::On::Unpause, std::move(action)) {}
};


#endif // UNPAUSEEVENTLISTENER_H
