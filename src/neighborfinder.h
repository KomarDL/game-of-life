#ifndef NEIGHBORFINDER_H
#define NEIGHBORFINDER_H

#include <QObject>

#include "global.h"

class NeighborFinder : public QObject
{
    Q_OBJECT
public:
    explicit NeighborFinder(QObject *parent = nullptr);

Q_SIGNALS:
    void neighborsFilled();
public Q_SLOTS:
    void fillNeighbors(Global::field& field);

private:
    qint32 getTopRowIndex(const Global::field& field, const qint32 row);
    qint32 getBottomRowIndex(const Global::field& field, const qint32 row);
    qint32 getLeftColumnIndex(const Global::field& field, const qint32 column);
    qint32 getRightColumnIndex(const Global::field& field, const qint32 column);
    const Global::cell_ptr &getTopLeftNeighbor(const Global::field& field, const qint32 row, const qint32 column);
    const Global::cell_ptr &getTopNeighbor(const Global::field& field, const qint32 row, const qint32 column);
    const Global::cell_ptr &getTopRightNeighbor(const Global::field& field, const qint32 row, const qint32 column);
    const Global::cell_ptr &getLeftNeighbor(const Global::field& field, const qint32 row, const qint32 column);
    const Global::cell_ptr &getRightNeighbor(const Global::field& field, const qint32 row, const qint32 column);
    const Global::cell_ptr &getBottomLeftNeighbor(const Global::field& field, const qint32 row, const qint32 column);
    const Global::cell_ptr &getBottomNeighbor(const Global::field& field, const qint32 row, const qint32 column);
    const Global::cell_ptr &getBottomRightNeighbor(const Global::field& field, const qint32 row, const qint32 column);
};

#endif // NEIGHBORFINDER_H
