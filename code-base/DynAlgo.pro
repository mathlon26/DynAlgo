QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    custom/CustomTradingAPI.cpp \
    custom/CustomTradingStrategy.cpp \
    main.cpp \
    MainWindow.cpp \
    trading/TradingBot.cpp \
    trading/TradingController.cpp \
    trading/api/TradingAPI.cpp \
    trading/api/WebAPI.cpp \
    trading/event/observer/CandleCloseEventObserver.cpp \
    widget/BotControlWidget.cpp

HEADERS += \
    MainWindow.h \
    custom/CustomTradingAPI.h \
    custom/CustomTradingStrategy.h \
    trading/Application.h \
    trading/TradingBot.h \
    trading/TradingController.h \
    trading/TradingStrategy.h \
    trading/api/TradingAPI.h \
    trading/api/WebAPI.h \
    trading/event/Event.h \
    trading/event/EventHandler.h \
    trading/event/EventListener.h \
    trading/event/EventObserver.h \
    trading/event/IEventListener.h \
    trading/event/listener/CandleCloseEventListeners.h \
    trading/event/listener/PauseEventListener.h \
    trading/event/listener/StopEventListener.h \
    trading/event/listener/UnpauseEventListener.h \
    trading/event/observer/CandleCloseEventObserver.h \
    trading/event/type/CandleClose.h \
    trading/event/type/CandleCloseEvents.h \
    trading/event/type/PauseEvent.h \
    trading/event/type/StartEvent.h \
    trading/event/listener/StartEventListener.h \
    trading/event/type/StopEvent.h \
    trading/event/type/UnpauseEvent.h \
    trading/model/Candle.h \
    trading/model/TimeFrame.h \
    widget/BotControlWidget.h

FORMS += \
    MainWindow.ui \
    widget/BotControlWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
