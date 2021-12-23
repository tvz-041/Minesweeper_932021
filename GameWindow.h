#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include "Cell.h"

class GameFieldWidget;

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void startNewGame();
    void stopGame();

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void onCellOpened(Cell::Value cellValue);
    void onFlagsCountChanged(const int flagsLeft);

private:
    void startTimer();
    void stopTimer();

    Ui::GameWindow *ui;
    int m_size;
    int m_minesCount;
    int m_score;
    int m_timerId;

    GameFieldWidget *m_gameField = nullptr;
};

#endif // GAMEWINDOW_H
