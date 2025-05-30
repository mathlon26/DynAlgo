#ifndef PAUSEEVENTLISTENER_H
#define PAUSEEVENTLISTENER_H

#include "trading/event/EventListener.h"
#include "trading/event/type/PauseEvent.h"

class PauseEventListener : public EventListener<PauseEvent>
{
public:
    PauseEventListener(std::function<void(const PauseEvent&)> action)
        : EventListener<PauseEvent>(Event::On::Pause, std::move(action)) {}
};



#endif // PAUSEEVENTLISTENER_H
