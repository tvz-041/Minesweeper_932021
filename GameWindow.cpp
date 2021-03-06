#include <QDebug>
#include <QMessageBox>

#include "GameFieldWidget.h"

#include "GameWindow.h"
#include "ui_GameWindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    m_size = 10;
    m_minesCount = 3;
    m_score = 0;
    m_timerId = 0;
    ui->lcdNumber_flagsLeft->display(m_minesCount);

    m_gameField = new GameFieldWidget(m_size, m_minesCount, this);
    ui->horizontalLayout_gameField->insertWidget(1, m_gameField);

    connect(m_gameField, &GameFieldWidget::cellOpened, this, &GameWindow::onCellOpened);
    connect(m_gameField, &GameFieldWidget::flagsCountChanged, this, &GameWindow::onFlagsCountChanged);
    connect(ui->pushButton_newGame, &QPushButton::clicked, this, &GameWindow::startNewGame);

    this->adjustSize();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::startNewGame()
{
    m_score = 0;
    stopTimer();
    ui->lcdNumber_timer->display(0);
    ui->lcdNumber_flagsLeft->display(m_minesCount);
    m_gameField->reset();
    m_gameField->setEnabled(true);
}

void GameWindow::stopGame()
{
    m_gameField->setDisabled(true);
    stopTimer();
}

void GameWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId) {
        if (ui->lcdNumber_timer->intValue() < 99999) {
            ui->lcdNumber_timer->display(ui->lcdNumber_timer->intValue() + 1);
        }
    }
}

void GameWindow::onCellOpened(Cell::Value cellValue)
{
    startTimer();

    if (cellValue == Cell::Mine) {
        stopGame();
        QMessageBox::critical(this, "Конец игры", "Вы подорвались на мине!");
    } else {
        ++m_score;

        if (m_score == m_size * m_size - m_minesCount) {
            stopGame();
            QMessageBox::information(this, "Конец игры", "Вы выиграли!");
        }
    }
}

void GameWindow::onFlagsCountChanged(const int flagsLeft)
{
    startTimer();
    ui->lcdNumber_flagsLeft->display(flagsLeft);
}

void GameWindow::startTimer()
{
    if (m_timerId == 0) {
        m_timerId = QObject::startTimer(1000);
    }
}

void GameWindow::stopTimer()
{
    if (m_timerId != 0) {
        killTimer(m_timerId);
        m_timerId = 0;
    }
}
