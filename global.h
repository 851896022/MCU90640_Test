#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QColor>
#include <QImage>
#include <QTimer>
#include <QList>
#include <QApplication>
struct AlarmBase
{
    AlarmBase() {}
    QString name;
    int x;
    int y;
    int temp;
    int alarmCount=0;
};
class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);
    QSerialPort *serialPort=NULL;
    QStringList comNameList;
    QImage *img;
    QList<QColor> colorList;
    QByteArray data;
    float temp[24][32];
    float TA;
    QTimer *receiverTimer;
    QTimer *alarmTimer;
    int maxTemp=40;
    int minTemp=20;
    QList<AlarmBase> alarmList;
    int alarmDelay=20;
signals:
    void receiveNewData();
    void imgOk();
    void refAlarmListSignal();
    void startOk();
    void doAlarm(int);
    void celAlarm(int);
public slots:
    void startLink(QString name);
    void onReceived();
    void workImg();
    QColor tempToColor(float temp);
    QColor tempToColorF(float temp);
    void initThis();
    void refAlarmListSlot();
    void savAlarmList();
    void loadAlarmList();
    void stopReceive();
    void alarm();
};
extern Global *g;
#endif // GLOBAL_H
