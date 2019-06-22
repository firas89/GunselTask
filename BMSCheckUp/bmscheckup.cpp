#include "bmscheckup.h"
#include "ui_bmscheckup.h"
#include <QDebug>
BMSCheckUp::BMSCheckUp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BMSCheckUp)
{
    ui->setupUi(this);
    setBalance(); // initial balance (temp1 and temp2 are in initial value)

    //=========== Updating Balance Every 100 ms ============//

    //Note: this is unnessecary process because balance will be updated in every
    //change in temp1,temp2.. but as it's requiered in task I did it..
    balanceTimer = new QTimer(this);
    connect(balanceTimer, SIGNAL(timeout()), this, SLOT(setBalance()) );
    balanceTimer->start(100);
    //=====================================================//
}

BMSCheckUp::~BMSCheckUp()
{
    delete ui;
}

void BMSCheckUp::keyPressEvent(QKeyEvent *event)
{
    //============= Detect Key Kept down================//
    if (event->isAutoRepeat() ) //key is kept down
    {
        if(pressTimer.elapsed() < 100){  //when time of press < 100 ms we ignore the event
            return;
        }
        else { // when time of press >= 100 ms we restart the timer
            pressTimer.start();
        }
    }
    else    // when key is pressed first time (not kept down) we start the timer
    {
        pressTimer.start();
    }
    //================================================//

    QStringList valueParts; // split target value to two parts (value, unit)
    int newValue; //take value of target and add 1

    switch (event->key()) {
    //============= Change In Current================//
    case Qt::Key_Q :    //Q is pressed
        valueParts = ui->Current->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() +1;    // add 1 to value
        ui->Current->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        break;

    case Qt::Key_A :    //A is pressed
        valueParts = ui->Current->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() -1;    // substract 1 from value
        ui->Current->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        break;

    //============= Change In Voltage================//
    case Qt::Key_W :    //W is pressed
        valueParts = ui->Voltage->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() +1;    // add 1 to value
        ui->Voltage->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        break;

    case Qt::Key_S :    //S is pressed
        valueParts = ui->Voltage->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() -1;    // substract 1 from value
        ui->Voltage->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        break;

    //============= Change In Capacity================//
    case Qt::Key_E :    //E is pressed
        valueParts = ui->Capacity->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() +1;    // add 1 to value
        ui->Capacity->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        break;

    case Qt::Key_D :    //D is pressed
        valueParts = ui->Capacity->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() -1;    // substract 1 from value
        ui->Capacity->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        break;

    //============= Change In Temp1================//
    case Qt::Key_R :    //R is pressed
        valueParts = ui->Temp1->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() +1;    // add 1 to value
        ui->Temp1->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        setBalance(); // change in temp1 means change in balance, setting new balance
        break;

    case Qt::Key_F :    //F is pressed
        valueParts = ui->Temp1->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() -1;    // substract 1 from value
        ui->Temp1->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        setBalance(); // change in temp1 means change in balance, setting new balance
        break;

    //============= Change In Temp2================//
    case Qt::Key_T :    //T is pressed
        valueParts = ui->Temp2->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() +1;    // add 1 to value
        ui->Temp2->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        setBalance(); // change in temp2 means change in balance, setting new balance
        break;

    case Qt::Key_G :    //G is pressed
        valueParts = ui->Temp2->text().split(" ");    //split (value,unit)
        newValue = valueParts[0].toInt() -1;    // substract 1 from value
        ui->Temp2->setText(QString::number(newValue) + " " + valueParts[1]); //set newValue then space then unit
        setBalance(); // change in temp2 means change in balance, setting new balance
        break;
    }
}
    //============= Setting/Calculating Balance================//
void BMSCheckUp::setBalance(){
    QStringList temp1Parts = ui->Temp1->text().split(" ");  // split temp1 to (value, unit)
    QStringList temp2Parts = ui->Temp2->text().split(" ");  // split temp1 to (value, unit)
    int temp1Value = temp1Parts[0].toInt(); //temp1 value
    int temp2Value = temp2Parts[0].toInt(); //temp2 value
    double balanceValue = (double) (abs(25 - temp1Value) + abs(25 - temp2Value)) / 2 ;  //calculate balance
    ui->Balance->setText(QString::number(balanceValue));    // set balance
}

