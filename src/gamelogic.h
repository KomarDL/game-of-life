#pragma once

#include <QObject>
#include "global.h"
#include "neighborfinder.h"

class GameLogic : public QObject
{
    Q_OBJECT
public:
    explicit GameLogic(QObject *parent = nullptr);

Q_SIGNALS:
    void gameStarted();
    void gameStopped();
    //    void gamePaused();
    //    void gameContinues();

    void updateUi();

public Q_SLOTS:
    void fieldWasChanged() { m_needNeighbors = true; }

    void startGame(const Global::Field &field);
    void stopGame();

    //    void pauseGame();
    //    void continueGame();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    Global::Field m_field;
    bool m_needNeighbors = true;
    std::unique_ptr<NeighborFinder> neighborFinder;
    bool m_timerStarted = false;
    int m_timerId = 0;

    Global::Field createFieldCopy();
    QVector<QColor> getNeighborsColors(const Global::CellPtr &cell);
    QColor getResultColor(const QVector<QColor> &colors);
};
