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
    loadAlarmList();
    receiverTimer=new QTimer;
    connect(receiverTimer,SIGNAL(timeout()),this,SLOT(onReceived()));
    alarmTimer=new QTimer;
    connect(alarmTimer,SIGNAL(timeout()),this,SLOT(alarm()));
    //alarmTimer->start(100);
    //receiverTimer->start(100);
}
void Global::startLink(QString name)
{
    //qDebug()<<"link";
    if(!(serialPort==NULL))
    {
        delete serialPort;
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
        data.clear();
        g->receiverTimer->start(100);
        alarmTimer->start(100);
        emit startOk();
        return;

    }
    else
    {

        //qDebug()<<"link No";
        return;

    }
}
void Global::stopReceive()
{
    receiverTimer->stop();
    serialPort->close();
    delete serialPort;
    serialPort=NULL;
    data.clear();

}
void Global::onReceived()
{

    //qDebug()<<"========================";
    if(!(serialPort==NULL))
    {
        if(serialPort->isOpen())
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



    }


//qDebug()<<"========================";
    workImg();

//qDebug()<<"========================";
}
void Global::workImg()
{
    //qDebug()<<"work start";
    //判断数据包
    short s16[768];
    while (1)
    {
        //qDebug()<<data.toHex();
        //qDebug()<<"========================";
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
            int count=0;
            for(int i=23;i>=0;i--)
            {
                for(int j=0;j<32;j++)
                {
                    temp[i][j]=((s16[count]/100.0)*0.3)+(0.7*temp[i][j]);
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
            if(houqi)
            {
                /*
                float min=300;
                float max=-100;
                for(int i=0;i<23;i++)
                {
                    for(int j=0;j<32;j++)
                    {
                        if(temp[i][j]>max)
                        {
                            max=temp[i][j];
                        }
                        if(temp[i][j]<min)
                        {
                            min=temp[i][j];
                        }

                    }
                }
                maxTemp=max;
                minTemp=min;
                */
                *img=img->scaled(32,24,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                    .scaled(320,240,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                    .scaled(32,24,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                    .scaled(320,240,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                    .scaled(32,24,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)

                        .scaled(320,240,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                        .scaled(32,24,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            }


            data.remove(0,1544);


            emit imgOk();



        }
        else
        {
            data.remove(0,1);
            //qDebug()<<"========================"<<data.count();
        }

    }









}
QColor Global::tempToColor(float temp)
{
    if(temp<minTemp)temp=minTemp;
    if(temp>maxTemp)temp=maxTemp;

    return colorList.at(((temp - minTemp)/(maxTemp - minTemp))*180);
}
QColor Global::tempToColorF(float temp)
{
    QColor col=tempToColor(temp);

    return QColor(255-col.red(),255-col.green(),255-col.blue());
}

void Global::refAlarmListSlot()
{

}
void Global::savAlarmList()
{
    QString str;
    for(int i=0;i<alarmList.count();i++)
    {
        str+=alarmList[i].name+"|";
        str+=QString::number(alarmList[i].x)+"|";
        str+=QString::number(alarmList[i].y)+"|";
        str+=QString::number(alarmList[i].temp)+"\r\n";
    }
    QString filename;
    filename+=(qApp->applicationDirPath()+"/alarm.txt");
    //判断文件是否存在
    QFile *file = new QFile(filename);
    if(file->open(QIODevice::WriteOnly))
    {
        file->write(str.toStdString().data());
        file->flush();
        file->close();
    }
    file->deleteLater();
}
void Global::loadAlarmList()
{
    QString filename;
    filename+=(qApp->applicationDirPath()+"/alarm.txt");
    //判断文件是否存在
    QFile *file = new QFile(filename);
    if(file->open(QIODevice::ReadOnly))
    {
        for(int i=0;i<1000;i++)
        {
            {
                QString ba(file->readLine());
                ba.remove("\r");ba.remove("\n");
                QStringList list=ba.split("|");
                if(list.count()<4)
                {
                    continue;
                }
                AlarmBase alarm;

                alarm.name=list.at(0);
                alarm.x=list.at(1).toInt();
                alarm.y=list.at(2).toInt();
                alarm.temp=list.at(3).toInt();
                alarmList.append(alarm);
            }


            if(file->atEnd())break;
        }
        file->close();
    }
    file->deleteLater();
}
void Global::alarm()
{
    for(int i=0;i<alarmList.count();i++)
    {
        //AlarmBase alm=alarmList[i];
        //qDebug()<<"alarmList[i]"<<alarmList[i].alarmCount<<"i"<<i;
        if(alarmList[i].alarmCount<alarmDelay)
        {
            if(temp[alarmList[i].y][alarmList[i].x]<alarmList[i].temp)
            {
                alarmList[i].alarmCount=0;
            }
            else
            {
                alarmList[i].alarmCount++;
            }
        }
        else if(alarmList[i].alarmCount==alarmDelay)
        {
            if(temp[alarmList[i].y][alarmList[i].x]<alarmList[i].temp)
            {
                alarmList[i].alarmCount=0;
            }
            else
            {
                alarmList[i].alarmCount++;
                qDebug()<<"emit doAlarm"<<i;
                emit doAlarm(i);
            }
        }
        else
        {
            if(temp[alarmList[i].y][alarmList[i].x]<alarmList[i].temp)
            {
                alarmList[i].alarmCount=0;
                emit celAlarm(i);
                qDebug()<<"emit celAlarm"<<i;
            }
            else
            {

            }
        }

    }
}
