#include "global.h"
Global *g;
#include <QThread>
#include "windows.h"
Global::Global(QObject *parent) : QObject(parent)
{


    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        comNameList << info.portName();
    }
    QColor tmp;
    tmp.setHsv(180,255,255);
    for(int j=0;j<180;j++)
    {

        colorList.append(tmp);
        tmp.setHsv(tmp.hsvHue()+1,255,255);

    }
    colorList.append(tmp);

    img = new QImage(32,24,QImage::Format_ARGB32);

}
void Global::initThis()
{
    //connect(this,SIGNAL(receiveNewData()),this,SLOT(workImg()));
    receiverTimer=new QTimer;
    connect(receiverTimer,SIGNAL(timeout()),this,SLOT(onReceived()));
    receiverTimer->start(100);
}
bool Global::startLink(QString name)
{
    //qDebug()<<"link";
    if(!(serialPort==NULL))
    {
        serialPort->deleteLater();
    }
    //qDebug()<<"delet ok";
    serialPort=new QSerialPort(name);
    //connect(serialPort,SIGNAL(readyRead()),this,SLOT(onReceived()));
    serialPort->setBaudRate(115200,QSerialPort::AllDirections);//设置波特率和读写方向
    serialPort->setDataBits(QSerialPort::Data8);      //数据位为8位
    serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    serialPort->setParity(QSerialPort::NoParity); //无校验位
    serialPort->setStopBits(QSerialPort::OneStop); //一位停止位
    if(serialPort->open(QIODevice::ReadWrite))
    {

        //qDebug()<<"link ok";
        return true;

    }
    else
    {

        //qDebug()<<"link No";
        return  false;

    }
}
void Global::onReceived()
{


    if(serialPort&&serialPort->isOpen())
    {
        char ch[65536];
        int realsize=0;
        if(serialPort->waitForReadyRead())
        {
            realsize=serialPort->read(ch,65536);

            data.append(ch,realsize);
        }
        //qDebug()<<"read end "<<realsize;


    }



    workImg();


}
void Global::workImg()
{
    //qDebug()<<"work start";
    //判断数据包
    short s16[768];
    while (1)
    {
        //qDebug()<<data.toHex();
        if(data.count()<1544)
        {
            //qDebug()<<"work data too short";
            return;
        }
        if(data[0]==(char)0x5A
                &&data[1]==(char)0x5A
                &&data[2]==(char)0x02
                &&data[3]==(char)0x06)
        {

            for(int i=0;i<768;i++)
            {
                s16[i]=data[(i+2)*2]+(data[(i+2)*2+1]*256);
            }
            break;

        }
        else
        {
            data.remove(0,1);
        }

    }








    int count=0;
    for(int i=23;i>=0;i--)
    {
        for(int j=0;j<32;j++)
        {
            temp[i][j]=s16[count]/100;
            count++;
        }
    }
    for(int i=0;i<23;i++)
    {
        for(int j=0;j<32;j++)
        {
            img->setPixelColor(j,i,tempToColor(temp[i][j]));
        }
    }
    data.remove(0,1544);
    emit imgOk();

}
QColor Global::tempToColor(float temp)
{
    if(temp<0)temp=0;
    if(temp>100)temp=100;

    return colorList.at((temp/100)*180);
}
QColor Global::tempToColorF(float temp)
{
    QColor col=tempToColor(temp);

    return QColor(255-col.red(),255-col.green(),255-col.blue());
}
