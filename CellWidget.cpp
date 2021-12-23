#include <QMouseEvent>

#include "CellWidget.h"

CellWidget::CellWidget(const Cell cell) :
    m_cell(cell)
{
    setClosedStyleSheet();

    //TODO: Добавить настройку опций ниже
    setFixedSize(40, 40);
    QFont font = this->font();
    font.setPointSize(14);
    this->setFont(font);
}

void CellWidget::setOpenedStyleSheet()
{
    this->setStyleSheet(
        "QPushButton {"
            "border: 0px;"
            "background-color: white;"
        "}"
    );
}

void CellWidget::setClosedStyleSheet()
{
    this->setStyleSheet(
        "QPushButton {"
            "background-color: lightgray;"
        "}"
    );
}

void CellWidget::setFlaggedStyleSheet()
{
    this->setStyleSheet(
        "QPushButton {"
            "background-color: darkred;"
        "}"
    );
}

void CellWidget::setFlag(const bool isFlagged)
{
    if (m_cell.hasFlag() == isFlagged) {
        return;
    }

    if (isFlagged) {
        m_cell.setFlag(true);
        setFlaggedStyleSheet();
    } else {
        m_cell.setFlag(false);

        if (m_cell.isClosed()) {
            setClosedStyleSheet();
        } else {
            setOpenedStyleSheet();
        }
    }
}

void CellWidget::setValue(Cell::Value cellValue)
{
    if (m_cell.value() == cellValue) {
        return;
    }

    m_cell.setValue(cellValue);

    if (!m_cell.isClosed()) {
        update();
    }
}

void CellWidget::open()
{
    if (m_cell.isClosed()) {
        m_cell.open();

        switch (m_cell.value()) {
            case Cell::Mine:
                this->setText("*");
            break;

            case Cell::Digit0:
            break;

            default:
                this->setText(QString::number(m_cell.value()));
            break;
        }

        this->setOpenedStyleSheet();
    }
}

void CellWidget::close()
{
    if (!m_cell.isClosed()) {
        m_cell.close();
        this->setText("");

        this->setClosedStyleSheet();
    }
}

void CellWidget::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
        case Qt::MouseButton::LeftButton:
            if (!m_cell.hasFlag()) {
                QPushButton::mousePressEvent(event);
            }
        break;

        case Qt::MouseButton::RightButton:
            if (m_cell.isClosed()) {
                emit flagStateChangeNeeded(*this);
            }

            QPushButton::mousePressEvent(event);
        break;

        default:
            QPushButton::mousePressEvent(event);
        break;
    }
}

void CellWidget::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
        case Qt::MouseButton::LeftButton:
            if (!m_cell.hasFlag()) {
                open();
                emit opened(this);
            }
        break;

        default:
            QPushButton::mouseReleaseEvent(event);
        break;
    }
}
