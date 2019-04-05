#ifndef ADD_H
#define ADD_H

#include <QFrame>
#include <global.h>
#include <QToolButton>
#include <QButtonGroup>
#include <QGridLayout>
namespace Ui {
class Add;
}

class Add : public QFrame
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = 0);
    ~Add();
    QToolButton chButton[768];

    QButtonGroup chGroup;
    QGridLayout gBox;

private slots:

    void onCellChanged(int key);
    void refUi();
private:
    Ui::Add *ui;
};

#endif // ADD_H
