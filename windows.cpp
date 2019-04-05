#include "windows.h"
#include "ui_windows.h"
#include "QDebug"
Windows::Windows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Windows)
{
    ui->setupUi(this);
    /*
    img = new QImage(32,24,QImage::Format_ARGB32);
    //img->scaled(32,24);

    img->setPixelColor(10,10,QColor(15,15,15));

    QColor tmp;
    tmp.setHsv(180,255,255);
    for(int j=0;j<180;j++)
    {

        colorList.append(tmp);
        tmp.setHsv(tmp.hsvHue()+1,255,255);

    }
    colorList.append(tmp);

    for(int i=0;i<32;i++)
    {
        for(int j=0;j<24;j++)
        {
            img->setPixelColor(i,j,colorList[((24.0*i)/768)*180].rgb());
        }

    }
    //img->scaled(320,240);
    ui->imgLabel->setPixmap(QPixmap::fromImage(img->scaled(640,480,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
*/
    ui->comBox->addItems(g->comNameList);
    connect(g,SIGNAL(imgOk()),this,SLOT(showImg()));
}

Windows::~Windows()
{
    delete ui;
}

void Windows::on_btnOpen_clicked()
{
    if(g->startLink(ui->comBox->currentText()))
    {
        ui->btnOpen->setEnabled(false);
        ui->comBox->setEnabled(false);
    }
    else
    {

    }
}
void Windows::showImg()
{
    ui->imgLabel->setPixmap(QPixmap::fromImage(g->img->scaled(640,480/*,Qt::IgnoreAspectRatio, Qt::SmoothTransformation*/)));
}
