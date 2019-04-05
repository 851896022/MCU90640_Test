#include "windows.h"
#include "ui_windows.h"
#include "QDebug"
Windows::Windows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Windows)
{
    ui->setupUi(this);
    img = new QImage(32,24,QImage::Format_ARGB32);
    //img->scaled(32,24);

    img->setPixelColor(10,10,QColor(15,15,15));

    QColor tmp(0,0,0);
    for(int j=0;j<255;j++)
    {

        colorList.append(tmp);
        tmp.setRed(tmp.red()+1);
    }
    colorList.append(tmp);
    for(int j=0;j<255;j++)
    {

        colorList.append(tmp);
        tmp.setGreen(tmp.green()+1);
    }
    colorList.append(tmp);
    for(int j=0;j<255;j++)
    {

        colorList.append(tmp);
        tmp.setBlue(tmp.blue()+1);
    }
    colorList.append(tmp);
    for(int i=0;i<32;i++)
    {
        for(int j=0;j<24;j++)
        {
            img->setPixelColor(i,j,colorList[24*i].rgb());
        }

    }
    //img->scaled(320,240);
    ui->imgLabel->setPixmap(QPixmap::fromImage(img->scaled(640,480,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

}

Windows::~Windows()
{
    delete ui;
}
