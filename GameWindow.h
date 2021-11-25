#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

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

private:
    Ui::GameWindow *ui;

    GameFieldWidget *m_gameField = nullptr;
};

#endif // GAMEWINDOW_H
