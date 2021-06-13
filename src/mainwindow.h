#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

#include "gamelogic.h"
#include "gamefield.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startGame();

    void stopGame();

    void clearField();

private:
    Ui::MainWindow *ui;
    QPushButton* m_startGamePushButton;
    QPushButton* m_stopGamePushButton;
    QPushButton* m_clearFieldPushButton;
    GameField* m_gameField;
    QColorDialog* m_colorDialog;
    GameLogic* m_gameLogic;

    void setupUi();
};
#endif // MAINWINDOW_H
