#ifndef TOPBAR_H
#define TOPBAR_H

#include <QFrame>

namespace Ui {
class TopBar;
}

class TopBar : public QFrame
{
    Q_OBJECT

public:
    explicit TopBar(QWidget *parent = 0);
    ~TopBar();

private:
    Ui::TopBar *ui;
    bool isFull=false;
public slots:
    void refListenInfo(QString msg);
    void refListenInfo(int type,int ch);
    void refListenInfo(int ch);
private slots:
    void on_fullScreen_clicked();
signals:
    void toFullScreen();
};

#endif // TOPBAR_H
