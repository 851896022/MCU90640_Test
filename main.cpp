#include "windows.h"
#include <QApplication>
#include "add.h"
#include <QThread>
#include <QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g=new Global;
    Windows w;
    w.show();
    QThread globalThread;
    g->moveToThread(&globalThread);
    QObject::connect(&globalThread,SIGNAL(started()),g,SLOT(initThis()));
    globalThread.start();
    Add add;
    add.show();

    return a.exec();
}
