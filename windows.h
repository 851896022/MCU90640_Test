#ifndef WINDOWS_H
#define WINDOWS_H

#include <QMainWindow>
#include <QImage>
#include <QPoint>
#include <QList>
#include <QColor>
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
private:
    Ui::Windows *ui;
};

#endif // WINDOWS_H
