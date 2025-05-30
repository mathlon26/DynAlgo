#ifndef IEVENTLISTENER_H
#define IEVENTLISTENER_H

#include "Event.h"

class IEventListener {
public:
    virtual ~IEventListener() = default;
    virtual Event::On type() const = 0;
    virtual void handleEvent(const Event &event) = 0;
};

#endif // IEVENTLISTENER_H
