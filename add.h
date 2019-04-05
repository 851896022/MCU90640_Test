#ifndef ADD_H
#define ADD_H

#include <QFrame>

namespace Ui {
class Add;
}

class Add : public QFrame
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = 0);
    ~Add();

private slots:

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::Add *ui;
};

#endif // ADD_H
