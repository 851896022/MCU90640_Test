#include "add.h"
#include "ui_add.h"

Add::Add(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
}

Add::~Add()
{
    delete ui;
}


void Add::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int , int )
{
    ui->txtX->setText(QString::number(currentColumn+1));
    ui->txtY->setText(QString::number(currentRow+1));
}
