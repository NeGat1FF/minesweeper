#include "minesweeper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MineSweeper w(nullptr);
    w.show();
    return a.exec();
}
