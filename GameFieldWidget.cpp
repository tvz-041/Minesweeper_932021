#include <QGridLayout>

#include "CellWidget.h"

#include "GameFieldWidget.h"

GameFieldWidget::GameFieldWidget(const int size, const int minesCount, QWidget *parent) :
    QWidget(parent)
{
    if (size > 0) {
        m_size = size;
    } else {
        m_size = 10;
    }

    if (minesCount > 0 && minesCount < m_size * m_size) {
        m_minesCount = minesCount;
    } else {
        m_minesCount = m_size;
    }

    m_flagsLeft = m_minesCount;

    QGridLayout *layout = new QGridLayout;

    for (int i = 0; i < m_size; ++i) {
        QVector<CellWidget *> row;

        for (int j = 0; j < m_size; ++j) {
            CellWidget *cellWidget = new CellWidget(Cell(i, j));
            connect(cellWidget, &CellWidget::opened, this, &GameFieldWidget::onCellOpened);
            connect(cellWidget, &CellWidget::flagStateChanged, this, &GameFieldWidget::onCellFlagChanged);

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
            m_cells[i][j]->setValue(Cell::Value::Digit0);
        }
    }

    m_hasOpenedCells = false;
    m_flagsLeft = m_minesCount;
}

//private slots:

void GameFieldWidget::onCellOpened(CellWidget *cell)
{
    if (!m_hasOpenedCells) {
        m_hasOpenedCells = true;
        generateCellValues(cell);
    }

    tryOpenCells(cell);
}

void GameFieldWidget::onCellFlagChanged(CellWidget &cell)
{
    if (cell.hasFlag()) { //Снимаем флаг, если он уже стоит
        m_flagsLeft++;
        flagsCountChanged(m_flagsLeft);
        cell.setFlag(false);
    } else if (m_flagsLeft > 0) { //Иначе, если можем, ставим флаг
        m_flagsLeft--;
        flagsCountChanged(m_flagsLeft);
        cell.setFlag(true);
    }
}

//private:

void GameFieldWidget::generateCellValues(CellWidget *startCell)
{
    QVector<CellWidget *> freeCells;

    for (QVector<CellWidget *> row : m_cells) {
        freeCells.append(row);
    }

    freeCells.removeOne(startCell);

    for (int i = 0; i < m_minesCount; ++i) {
        CellWidget *minedCell = freeCells.takeAt(rand() % freeCells.size());
        minedCell->setValue(Cell::Value::Mine);
        increaseNeighbourCellsValues(minedCell);
    }
}

void GameFieldWidget::addNeighbourCellToOpeningQueue(const int row, const int column)
{
    if (row > -1 && row < m_size && column > -1 && column < m_size) {
        CellWidget *cell = m_cells[row][column];

        if (cell->isClosed() && !cell->hasFlag() && !m_cellOpeningQueue.contains(cell)) {
            m_cellOpeningQueue.enqueue(cell);
        }
    }
}

void GameFieldWidget::addNeighbourCellsToOpeningQueue(CellWidget *cell)
{
    if (cell->value() == Cell::Digit0) {
        addNeighbourCellToOpeningQueue(cell->row() - 1, cell->column() - 1);
        addNeighbourCellToOpeningQueue(cell->row() - 1, cell->column());
        addNeighbourCellToOpeningQueue(cell->row() - 1, cell->column() + 1);

        addNeighbourCellToOpeningQueue(cell->row(), cell->column() - 1);
        addNeighbourCellToOpeningQueue(cell->row(), cell->column() + 1);

        addNeighbourCellToOpeningQueue(cell->row() + 1, cell->column() - 1);
        addNeighbourCellToOpeningQueue(cell->row() + 1, cell->column());
        addNeighbourCellToOpeningQueue(cell->row() + 1, cell->column() + 1);
    }
}

void GameFieldWidget::increaseNeighbourCellValue(const int row, const int column)
{
    if (row > -1 && row < m_size && column > -1 && column < m_size) {
        CellWidget *cell = m_cells[row][column];

        if (cell->value() >= 0) {
            cell->setValue(Cell::Value(cell->value() + 1));
        }
    }
}

void GameFieldWidget::increaseNeighbourCellsValues(CellWidget *cell)
{
    increaseNeighbourCellValue(cell->row() - 1, cell->column() - 1);
    increaseNeighbourCellValue(cell->row() - 1, cell->column());
    increaseNeighbourCellValue(cell->row() - 1, cell->column() + 1);

    increaseNeighbourCellValue(cell->row(), cell->column() - 1);
    increaseNeighbourCellValue(cell->row(), cell->column() + 1);

    increaseNeighbourCellValue(cell->row() + 1, cell->column() - 1);
    increaseNeighbourCellValue(cell->row() + 1, cell->column());
    increaseNeighbourCellValue(cell->row() + 1, cell->column() + 1);
}

void GameFieldWidget::tryOpenCells(CellWidget *startCell)
{
    m_cellOpeningQueue.enqueue(startCell);

    while (!m_cellOpeningQueue.isEmpty()) {
        CellWidget *cell = m_cellOpeningQueue.dequeue();
        cell->open();
        emit cellOpened(cell->value());
        addNeighbourCellsToOpeningQueue(cell);
    }
}
