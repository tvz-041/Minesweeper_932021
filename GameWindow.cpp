#include "GameFieldWidget.h"

#include "GameWindow.h"
#include "ui_GameWindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    m_gameField = new GameFieldWidget(10, this);
    ui->horizontalLayout_gameField->insertWidget(1, m_gameField);
    this->adjustSize();
}

GameWindow::~GameWindow()
{
    delete ui;
}
