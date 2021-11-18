#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QPushButton>

#include "Cell.h"

class CellWidget : public QPushButton
{
public:
    CellWidget(const Cell cell);

private:
    Cell m_cell;
};

#endif // CELLWIDGET_H
