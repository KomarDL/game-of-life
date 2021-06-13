#ifndef GAMELOGIC_H
#define GAMELOGIC_H

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

    void startGame(const Global::field &field);
    void stopGame();

    //    void pauseGame();
    //    void continueGame();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    Global::field m_field;
    bool m_needNeighbors = true;
    std::unique_ptr<NeighborFinder> neighborFinder;
    bool m_timerStarted = false;
    int m_timerId = 0;

    Global::field createFieldCopy();
    QVector<QColor> getNeighborsColors(const Global::cell_ptr &cell);
};

#endif // GAMELOGIC_H
