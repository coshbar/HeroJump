#include "herojump.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HeroJump w;
    w.show();

    return a.exec();
}
