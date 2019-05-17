#include "timerkiller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimerKiller w;
    w.show();

    return a.exec();
}
