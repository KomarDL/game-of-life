#pragma once

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
    void fillNeighbors(Global::Field& field);

private:
    qint32 getTopRowIndex(const Global::Field& field, const qint32 row);
    qint32 getBottomRowIndex(const Global::Field& field, const qint32 row);
    qint32 getLeftColumnIndex(const Global::Field& field, const qint32 column);
    qint32 getRightColumnIndex(const Global::Field& field, const qint32 column);
    const Global::CellPtr &getTopLeftNeighbor(const Global::Field& field, const qint32 row, const qint32 column);
    const Global::CellPtr &getTopNeighbor(const Global::Field& field, const qint32 row, const qint32 column);
    const Global::CellPtr &getTopRightNeighbor(const Global::Field& field, const qint32 row, const qint32 column);
    const Global::CellPtr &getLeftNeighbor(const Global::Field& field, const qint32 row, const qint32 column);
    const Global::CellPtr &getRightNeighbor(const Global::Field& field, const qint32 row, const qint32 column);
    const Global::CellPtr &getBottomLeftNeighbor(const Global::Field& field, const qint32 row, const qint32 column);
    const Global::CellPtr &getBottomNeighbor(const Global::Field& field, const qint32 row, const qint32 column);
    const Global::CellPtr &getBottomRightNeighbor(const Global::Field& field, const qint32 row, const qint32 column);
};
