#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    //w.setGeometry(0,0,width,height);
    w.resize(width,height);
    w.show();

    return a.exec();
}
