#include <QApplication>

#include "Cell.h"
#include "GameWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameWindow widget;
    widget.show();

    return a.exec();
}
