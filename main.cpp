#include "windows.h"
#include <QApplication>
#include "add.h"
#include <QThread>
#include <QObject>
#include "qlog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(QLog::messageHandler);
    g=new Global;

    QThread globalThread;
    g->moveToThread(&globalThread);
    QObject::connect(&globalThread,SIGNAL(started()),g,SLOT(initThis()));
    globalThread.start();

    Windows w;

    w.setWindowState(Qt::WindowMaximized);
    w.show();
    QObject::connect(g,SIGNAL(startOk()),&w,SLOT(startOk()));
    QObject::connect(&w,SIGNAL(startRead(QString)),g,SLOT(startLink(QString)));
    QObject::connect(&w,SIGNAL(stopRead()),g,SLOT(stopReceive()));
    QObject::connect(g,SIGNAL(doAlarm(int)),&w,SLOT(doAlarm(int)));
    QObject::connect(g,SIGNAL(celAlarm(int)),&w,SLOT(celAlarm(int)));
    return a.exec();
}
