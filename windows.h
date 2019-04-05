#ifndef WINDOWS_H
#define WINDOWS_H

#include <QMainWindow>
#include <QImage>
#include <QPoint>
#include <QList>
#include <QColor>
#include "global.h"
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
private slots:
    void on_btnOpen_clicked();

private:
    Ui::Windows *ui;
public slots:
    void showImg();
};

#endif // WINDOWS_H
