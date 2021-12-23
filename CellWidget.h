#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QPushButton>

#include "Cell.h"

class CellWidget : public QPushButton
{
    Q_OBJECT

public:
    CellWidget(const Cell cell);

    inline bool isClosed() const;
    inline Cell::Value value() const;

    inline int row() const;
    inline int column() const;

    void setOpenedStyleSheet();
    void setClosedStyleSheet();
    void setFlaggedStyleSheet();

    void setFlag(const bool isFlagged);
    void setValue(Cell::Value cellValue);

public slots:
    void open();
    void close();

signals:
    void opened(CellWidget *cell);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Cell m_cell;
};



inline bool CellWidget::isClosed() const
{
    return m_cell.isClosed();
}

inline Cell::Value CellWidget::value() const
{
    return m_cell.value();
}

inline int CellWidget::row() const
{
    return m_cell.row();
}

inline int CellWidget::column() const
{
    return m_cell.column();
}

#endif // CELLWIDGET_H
