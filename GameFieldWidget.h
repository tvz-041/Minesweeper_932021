#ifndef GAMEFIELDWIDGET_H
#define GAMEFIELDWIDGET_H

#include <QStack>
#include <QWidget>

#include "Cell.h"

class CellWidget;

class GameFieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameFieldWidget(const int size, QWidget *parent = nullptr);
    ~GameFieldWidget() = default;

    void open();
    void close();

    void reset();

signals:
    void cellOpened(Cell::Value cellValue);

private slots:
    void onCellOpened(CellWidget *cell);

private:
    void tryAddNeighbourCell(const int row, const int column);
    void tryAddNeighbourCells(CellWidget *cell);

    void tryOpenCells(CellWidget *startCell);

    int m_size;
    QVector<QVector<CellWidget *>> m_cells;

    QStack<CellWidget *> m_unprocessedCells;
};

#endif // GAMEFIELDWIDGET_H
