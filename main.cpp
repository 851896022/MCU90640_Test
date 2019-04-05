#include "windows.h"
#include <QApplication>
#include "add.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Windows w;
    w.show();
    Add add;
    add.show();

    return a.exec();
}
