#ifndef WINDOWS_H
#define WINDOWS_H

#include <QMainWindow>

namespace Ui {
class Windows;
}

class Windows : public QMainWindow
{
    Q_OBJECT

public:
    explicit Windows(QWidget *parent = 0);
    ~Windows();

private:
    Ui::Windows *ui;
};

#endif // WINDOWS_H
