// 13413120 JBM HERTZOG
#include "gui.h"
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui w;
    w.show();
    return a.exec();
}
