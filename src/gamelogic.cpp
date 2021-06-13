#include "gamelogic.h"

#include <QTimerEvent>

#include "cell.h"

using namespace std::chrono_literals;

GameLogic::GameLogic(QObject *parent) : QObject(parent), neighborFinder(new NeighborFinder)
{
    qRegisterMetaType<Global::field>("Global::field");
}

void GameLogic::startGame(const Global::field &field)
{
    if (m_timerStarted) {
        return;
    }

    m_field = field;
    if (m_needNeighbors) {
        neighborFinder->fillNeighbors(m_field);
    }
    m_timerId = startTimer(300ms);
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
    auto prevField = createFieldCopy();
    for(auto i = 0; i < m_field.size(); ++i) {
        for (auto j = 0; j < m_field[i].size(); ++j) {
            auto neighborColors = getNeighborsColors(prevField[i][j]);
            const auto size = neighborColors.size();
            auto& cell = m_field[i][j];
            if (size < 2 || size > 3) {
                cell->setColor(Qt::white);
            } else if (size == 3 && cell->color() == Qt::white) {
                cell->setColor(Qt::black);
            }
        }
    }
    event->accept();
    emit updateUi();
}

Global::field GameLogic::createFieldCopy()
{
    Global::field result;
    result.resize(m_field.size());
    for (auto i = 0; i < m_field.size(); ++i) {
        result[i].reserve(m_field[i].size());
        for (auto j = 0; j < m_field[i].size(); ++j) {
            result[i].push_back(std::make_shared<Cell>(*m_field[i][j].get()));
        }
    }
    neighborFinder->fillNeighbors(result);
    return result;
}

QVector<QColor> GameLogic::getNeighborsColors(const Global::cell_ptr &cell)
{
    QVector<QColor> result;
    for (const auto& neighbor: cell->neighbors()) {
        if (auto item = neighbor.lock()) {
            if (item->color() != Qt::white) {
                result.push_back(item->color());
            }
        }
    }
    return result;
}
