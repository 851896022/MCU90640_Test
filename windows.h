#ifndef WINDOWS_H
#define WINDOWS_H

#include <QMainWindow>
#include <QImage>
#include <QPoint>
#include <QList>
#include <QColor>
#include "global.h"
#include <QThread>
#include "add.h"
namespace Ui {
class Windows;
}

class Windows : public QMainWindow
{
    Q_OBJECT

public:
    explicit Windows(QWidget *parent = 0);
    ~Windows();
    QImage *img;
    QList<QColor> colorList;
    Add * add=NULL;
private slots:
    void on_btnOpen_clicked();

    void on_btnClose_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();
signals:
    void stopRead();
    void startRead(QString);
private:
    Ui::Windows *ui;
    void closeEvent(QCloseEvent *event);
public slots:
    void showImg();
    void refAlarmList();
    void startOk();
    void doAlarm(int);
    void celAlarm(int);
};

#endif // WINDOWS_H
