#ifndef GAMEFIELDWIDGET_H
#define GAMEFIELDWIDGET_H

#include <QWidget>

#include <Cell.h>

class CellWidget;

class GameFieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameFieldWidget(const int size, QWidget *parent = nullptr);
    ~GameFieldWidget() = default;

    void open();
    void close();

signals:
    void cellOpened(Cell::Value cellValue);

private:
    int m_size;
    QVector<QVector<CellWidget *>> m_cells;
};

#endif // GAMEFIELDWIDGET_H
