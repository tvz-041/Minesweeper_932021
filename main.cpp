#include <QApplication>

#include "Cell.h"
#include "GameWindow.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameWindow gameWindow;
    gameWindow.show();

    return app.exec();
}
