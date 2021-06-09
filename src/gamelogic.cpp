#include "gamelogic.h"

#include <QTimerEvent>

using namespace std::chrono_literals;

GameLogic::GameLogic(QObject *parent) : QObject(parent)
    , neighborFinder(new NeighborFinder)
{
    qRegisterMetaType<Global::field>("Global::field");
}

void GameLogic::startGame(Global::field field)
{
    if (m_timerStarted) {
        return;
    }

    m_field = field;
    neighborFinder->fillNeighbors(m_field);
    startTimer(300ms);
    m_timerStarted = true;
    emit gameStarted();
}

void GameLogic::stopGame()
{
    if (!m_timerStarted) {
        return;
    }

    killTimer(m_timerId);
    m_timerStarted = false;
    emit gameStopped();
}

void GameLogic::timerEvent(QTimerEvent *event)
{

    event->accept();
}
