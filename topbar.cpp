#include "topbar.h"
#include "ui_topbar.h"
#include "global.h"
TopBar::TopBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TopBar)
{
    ui->setupUi(this);
}

TopBar::~TopBar()
{
    delete ui;
}
void TopBar::refListenInfo(QString msg)
{
    return;
    ui->listenInfo->setText(msg);
}
void TopBar::refListenInfo(int type,int ch)
{
    return;

}
void TopBar::refListenInfo(int ch)
{
    return;
}

void TopBar::on_fullScreen_clicked()
{
    return;
}
