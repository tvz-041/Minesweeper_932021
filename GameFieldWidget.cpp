#include <QGridLayout>

#include "CellWidget.h"

#include "GameFieldWidget.h"

GameFieldWidget::GameFieldWidget(const int size, QWidget *parent) :
    QWidget(parent)
{
    if (size > 0) {
        m_size = size;
    } else {
        m_size = 10;
    }

    QGridLayout *layout = new QGridLayout;

    for (int i = 0; i < m_size; ++i) {
        QVector<CellWidget *> row;

        for (int j = 0; j < m_size; ++j) {
            Cell cell(Cell::Value(rand() % 10 - 1));
            CellWidget *cellWidget = new CellWidget(cell);
            connect(cellWidget, &CellWidget::opened, this, &GameFieldWidget::cellOpened);

            layout->addWidget(cellWidget, i, j);
            row.append(cellWidget);
        }

        m_cells.append(row);
    }

    layout->setSpacing(0);
    this->setLayout(layout);
}

void GameFieldWidget::open()
{
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            m_cells[i][j]->open();
        }
    }
}

void GameFieldWidget::close()
{
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            m_cells[i][j]->close();
        }
    }
}
