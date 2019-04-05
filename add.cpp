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
    gBox.setMargin(0);
    gBox.setSpacing(0);
    ui->groupBox->setLayout(&gBox);

    connect(&chGroup,SIGNAL(buttonClicked(int)),this,SLOT(onCellChanged(int)));
    connect(&timer,SIGNAL(timeout()),this,SLOT(refUi()));
    refUi();
    //timer.start(1000);
}

Add::~Add()
{
    delete ui;
}


void Add::onCellChanged(int key)
{
    ui->txtX->setText(QString::number(key%32+1));
    ui->txtY->setText(QString::number(key/32+1));

}
void Add::refUi()
{
    for(int i=0;i<24;i++)
    {
        for(int j=0;j<32;j++)
        {
            chButton[i*32+j].setText(QString::number(g->temp[i][j],'f',0));
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

void Add::on_btnAdd_clicked()
{
    AlarmBase base;
    base.name=ui->txtName->text();
    base.x=ui->txtX->text().toInt()-1;
    base.y=ui->txtY->text().toInt()-1;
    base.temp=ui->txtTemp->text().toInt();
    g->alarmList.append(base);

    g->savAlarmList();
    emit addAlarm();
    this->close();
}

void Add::on_txtTemp_textChanged(const QString &arg1)
{
    int tmp=arg1.toInt();
    if(tmp>200)
    {
        ui->txtTemp->setText("200");
    }
    if(tmp<-30)
    {
        ui->txtTemp->setText("-30");
    }

}

void Add::on_txtY_textChanged(const QString &arg1)
{
    int tmp=arg1.toInt();
    if(tmp>24)
    {
        ui->txtY->setText("24");
    }
    if(tmp<1)
    {
        ui->txtY->setText("1");
    }
}

void Add::on_txtX_textChanged(const QString &arg1)
{
    int tmp=arg1.toInt();
    if(tmp>32)
    {
        ui->txtX->setText("32");
    }
    if(tmp<1)
    {
        ui->txtX->setText("1");
    }
}
