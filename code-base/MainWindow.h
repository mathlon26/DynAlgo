#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "trading/TradingController.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TradingController *controller;
};
#endif // MAINWINDOW_H
