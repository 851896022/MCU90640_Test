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
    QTimer timer;
private slots:

    void onCellChanged(int key);
    void refUi();
    void on_btnAdd_clicked();

    void on_txtTemp_textChanged(const QString &arg1);

    void on_txtY_textChanged(const QString &arg1);

    void on_txtX_textChanged(const QString &arg1);
signals:
    void addAlarm();
    void refAlarmListSignal();
private:
    Ui::Add *ui;
};

#endif // ADD_H
