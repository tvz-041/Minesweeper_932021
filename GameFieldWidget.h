#ifndef GAMEFIELDWIDGET_H
#define GAMEFIELDWIDGET_H

#include <QQueue>
#include <QWidget>

#include "Cell.h"

class CellWidget;

class GameFieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameFieldWidget(const int size, const int minesCount, QWidget *parent = nullptr);
    ~GameFieldWidget() = default;

    void open();
    void close();

    void reset();

signals:
    void cellOpened(Cell::Value cellValue);
    void flagsCountChanged(const int flagsLeft);

private slots:
    void onCellOpened(CellWidget *cell);
    void onCellFlagChanged(CellWidget &cell);

private:
    void addNeighbourCellToOpeningQueue(const int row, const int column);
    void addNeighbourCellsToOpeningQueue(CellWidget *cell);

    void increaseNeighbourCellValue(const int row, const int column);
    void increaseNeighbourCellsValues(CellWidget *cell);

    void generateCellValues(CellWidget *startCell);
    void tryOpenCells(CellWidget *startCell);

    int m_hasOpenedCells = false;
    int m_size;
    int m_minesCount;
    int m_flagsLeft;
    QVector<QVector<CellWidget *>> m_cells;

    QQueue<CellWidget *> m_cellOpeningQueue;
};

#endif // GAMEFIELDWIDGET_H
