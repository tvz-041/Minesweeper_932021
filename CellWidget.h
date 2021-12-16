#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QPushButton>

#include "Cell.h"

class CellWidget : public QPushButton
{
    Q_OBJECT

public:
    CellWidget(const Cell cell);

    void setOpenedStyleSheet();
    void setClosedStyleSheet();
    void setFlaggedStyleSheet();

    void setFlag(const bool isFlagged);
    void setValue(Cell::Value cellValue);

public slots:
    void open();
    void close();

signals:
    void opened(Cell::Value cellValue);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Cell m_cell;
};

#endif // CELLWIDGET_H
