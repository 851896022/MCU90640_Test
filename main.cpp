#include "windows.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Windows w;
    w.show();

    return a.exec();
}
