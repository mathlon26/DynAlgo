#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QObject>
#include <functional>
#include "trading/event/Event.h"
#include "trading/event/IEventListener.h"
#include "trading/TradingBot.h"

template <typename TEvent>
class EventListener : public IEventListener
{
    static_assert(std::is_base_of<Event, TEvent>::value, "TEvent must derive from Event");

public:
    EventListener(Event::On type, std::function<void(const TEvent&)> action)
        : m_type(type), m_action(std::move(action)) {}

    Event::On type() const override { return m_type; }

    void handleEvent(const Event &event) override {
        if (event.type() == m_type) {
            if (const TEvent *specific = dynamic_cast<const TEvent*>(&event)) {
                m_action(*specific);
            }
        }
    }

protected:
    Event::On m_type;
    std::function<void(const TEvent&)> m_action;
};

#endif // EVENTLISTENER_H
