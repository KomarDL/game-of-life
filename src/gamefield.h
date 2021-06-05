#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include "cell.h"

class GameField : public QWidget
{
    Q_OBJECT
public:
    explicit GameField(QWidget *parent = nullptr);

Q_SIGNALS:

private:

};

#endif // GAMEFIELD_H
