#include "windows.h"
#include "ui_windows.h"

Windows::Windows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Windows)
{
    ui->setupUi(this);
}

Windows::~Windows()
{
    delete ui;
}
