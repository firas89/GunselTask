#include "bmscheckup.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BMSCheckUp w;
    w.setFixedSize(w.size());
    //w.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    w.show();

    return a.exec();
}
