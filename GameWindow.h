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

private slots:
    void onCellOpened(Cell::Value cellValue);

private:
    Ui::GameWindow *ui;
    int m_size;
    int m_minesCount;
    int m_score;

    GameFieldWidget *m_gameField = nullptr;
};

#endif // GAMEWINDOW_H
