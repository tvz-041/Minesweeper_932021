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
            Cell cell(i, j, Cell::Value(rand() % 10 - 1));
            CellWidget *cellWidget = new CellWidget(cell);
            connect(cellWidget, &CellWidget::opened, this, &GameFieldWidget::onCellOpened);

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

void GameFieldWidget::reset()
{
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            m_cells[i][j]->close();
            m_cells[i][j]->setFlag(false);
            m_cells[i][j]->setValue(Cell::Value(rand() % 10 - 1));
    }
    }

}

//private slots:

void GameFieldWidget::onCellOpened(CellWidget *cell)
{
    tryOpenCells(cell);
}

//private:

void GameFieldWidget::tryAddNeighbourCell(const int row, const int column)
{
    if (row > -1 && row < m_size && column > -1 && column < m_size) {
        CellWidget *cell = m_cells[row][column];

        if (cell->isClosed() && !m_unprocessedCells.contains(cell)) {
            m_unprocessedCells.append(cell);
        }
    }
}

void GameFieldWidget::tryAddNeighbourCells(CellWidget *cell)
{
    if (cell->value() == Cell::Digit0) {
        tryAddNeighbourCell(cell->row() - 1, cell->column() - 1);
        tryAddNeighbourCell(cell->row() - 1, cell->column());
        tryAddNeighbourCell(cell->row() - 1, cell->column() + 1);

        tryAddNeighbourCell(cell->row(), cell->column() - 1);
        tryAddNeighbourCell(cell->row(), cell->column() + 1);

        tryAddNeighbourCell(cell->row() + 1, cell->column() - 1);
        tryAddNeighbourCell(cell->row() + 1, cell->column());
        tryAddNeighbourCell(cell->row() + 1, cell->column() + 1);
    }
}

void GameFieldWidget::tryOpenCells(CellWidget *startCell)
{
    m_unprocessedCells.append(startCell);

    while (!m_unprocessedCells.isEmpty()) {
        CellWidget *cell = m_unprocessedCells.pop();
        cell->open();
        emit cellOpened(cell->value());
        tryAddNeighbourCells(cell);
    }
}
