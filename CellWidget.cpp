#include "CellWidget.h"

CellWidget::CellWidget(const Cell cell)
{
    m_cell = cell;

    switch (m_cell.value()) {
        case Cell::Mine:
            //TODO: implement
        break;

        case Cell::Digit0:
            //TODO: implement
        break;

        default:
            this->setText(QString::number(m_cell.value()));
        break;
    }
}
