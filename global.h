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
signals:
    void receiveNewData();
    void imgOk();

public slots:
    bool startLink(QString name);
    void onReceived();
    void workImg();
    QColor tempToColor(float temp);
    QColor tempToColorF(float temp);
    void initThis();
};
extern Global *g;
#endif // GLOBAL_H
