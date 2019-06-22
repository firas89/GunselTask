#ifndef BMSCHECKUP_H
#define BMSCHECKUP_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QElapsedTimer>
#include <QString>

namespace Ui {
class BMSCheckUp;
}

class BMSCheckUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit BMSCheckUp(QWidget *parent = nullptr);
    ~BMSCheckUp();


private:
    Ui::BMSCheckUp *ui;
    void keyPressEvent(QKeyEvent *event);
    QTimer *balanceTimer ;  //timer to update balance every 100s
    QElapsedTimer pressTimer;   //timer to act with keeping pressing key

private slots:
    void setBalance();  //to calculate and set balance
};

#endif // BMSCHECKUP_H
