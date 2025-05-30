#include "MainWindow.h"
#include "trading/Application.h"

#include "custom/CustomTradingAPI.h"
#include "custom/CustomTradingStrategy.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    DynalgoApplication::Start<CustomTradingStrategy, CustomTradingAPI>();

    w.show();
    return a.exec();
}
