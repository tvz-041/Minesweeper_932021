#include <QApplication>

#include "Cell.h"
#include "CellWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Cell cell(Cell::Digit5);
    CellWidget cellWidget(cell);
    cellWidget.show();

    return a.exec();
}
