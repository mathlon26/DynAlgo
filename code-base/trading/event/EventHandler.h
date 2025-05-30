#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QMap>
#include <QList>
#include <QObject>
#include "trading/event/IEventListener.h"

class EventHandler : public QObject
{
    Q_OBJECT
public:
    explicit EventHandler(QObject *parent = nullptr)
        : QObject(parent)
    {}

    // Subscribe registers listener and connects to its destroyed signal
    void subscribe(IEventListener* listener) {
        listeners[listener->type()].append(listener);
    }

    void dispatch(const Event& event) {
        auto it = listeners.find(event.type());
        if (it != listeners.end()) {
            // Use a copy of the list to prevent issues if listeners are removed during iteration
            QList<IEventListener*> currentListeners = it.value();
            for (auto* listener : currentListeners) {
                if (listener) {
                    listener->handleEvent(event);
                }
            }
        }
    }

    // Clears all listeners (called when you want to reset the handler)
    void reset() {
        for (auto it = listeners.begin(); it != listeners.end(); ++it) {
            QList<IEventListener*>& lst = it.value();
            for (IEventListener* listener : lst) {
                if (listener) {
                    delete listener;
                }
            }
        }
        listeners.clear();
    }

private:
    QMap<Event::On, QList<IEventListener*>> listeners;
};

#endif // EVENTHANDLER_H
