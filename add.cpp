#include "add.h"
#include "ui_add.h"

Add::Add(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    chGroup.setExclusive(true);
    for(int i=0;i<768;i++)
    {
        chGroup.addButton(&chButton[i],i);
        chButton[i].setCheckable(true);
        chButton[i].setChecked(false);
        chButton[i].setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    }
    for(int i=0;i<24;i++)
    {
        for(int j=0;j<32;j++)
        {
            gBox.addWidget(&chButton[(i*32+j)],i,j);
        }
    }
    gBox.setMargin(1);
    gBox.setSpacing(1);
    ui->groupBox->setLayout(&gBox);

    connect(&chGroup,SIGNAL(buttonClicked(int)),this,SLOT(onCellChanged(int)));

}

Add::~Add()
{
    delete ui;
}


void Add::onCellChanged(int key)
{
    ui->txtX->setText(QString::number(key%32+1));
    ui->txtY->setText(QString::number(key/32+1));
    refUi();
}
void Add::refUi()
{
    for(int i=0;i<24;i++)
    {
        for(int j=0;j<32;j++)
        {
            chButton[i*32+j].setText(QString::number(g->temp[i][j],'f',1));
            //ui->tableWidget->item(j,i)->setText(QString::number(j)+"|"+QString::number(i));
            QColor a=g->tempToColor(g->temp[i][j]);
            QColor b=g->tempToColorF(g->temp[i][j]);
            QString str;
            str+="background-color: rgb("+QString::number(a.red())+", "+QString::number(a.green())+", "+QString::number(a.blue())+");"
                      +"color: rgb("+QString::number(b.red())+", "+QString::number(b.green())+", "+QString::number(b.blue())+");";
            chButton[i*32+j].setStyleSheet(str);
        }
    }
}
