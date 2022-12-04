#include "neighborfinder.h"
#include "cell.h"

NeighborFinder::NeighborFinder(QObject* parent)
    : QObject(parent)
{
}

void NeighborFinder::fillNeighbors(Global::Field& field)
{
    const auto fieldSize = field.size();
    for (auto i = 0; i < fieldSize; ++i) {
        for (auto j = 0; j < fieldSize; ++j) {
            auto& neighbors = field[i][j]->neighbors();
            neighbors[qint32(Neighbor::TopLeft)] = getTopLeftNeighbor(field, i, j);
            neighbors[qint32(Neighbor::Top)] = getTopNeighbor(field, i, j);
            neighbors[qint32(Neighbor::TopRight)] = getTopRightNeighbor(field, i, j);
            neighbors[qint32(Neighbor::Left)] = getLeftNeighbor(field, i, j);
            neighbors[qint32(Neighbor::Right)] = getRightNeighbor(field, i, j);
            neighbors[qint32(Neighbor::BottomLeft)] = getBottomLeftNeighbor(field, i, j);
            neighbors[qint32(Neighbor::Bottom)] = getBottomNeighbor(field, i, j);
            neighbors[qint32(Neighbor::BottomRight)] = getBottomRightNeighbor(field, i, j);
        }
    }
    Q_EMIT neighborsFilled();
}

qint32 NeighborFinder::getTopRowIndex(const Global::Field &field, const qint32 row)
{
    auto result = row - 1;
    if (result < 0) {
        result = field.size() - 1;
    }
    return result;
}

qint32 NeighborFinder::getBottomRowIndex(const Global::Field &field, const qint32 row)
{
    return (row + 1) % field.size();
}

qint32 NeighborFinder::getLeftColumnIndex(const Global::Field &field, const qint32 column)
{
    auto result = column - 1;
    if (result < 0) {
        result = field.constFirst().size() - 1;
    }
    return result;
}

qint32 NeighborFinder::getRightColumnIndex(const Global::Field &field, const qint32 column)
{
    return (column + 1) % field.constFirst().size();
}

const Global::CellPtr& NeighborFinder::getTopLeftNeighbor(const Global::Field& field, const qint32 row, const qint32 column)
{
    auto resultRow = getTopRowIndex(field, row);
    auto resultColumn = getLeftColumnIndex(field, column);
    return field[resultRow][resultColumn];
}

const Global::CellPtr& NeighborFinder::getTopNeighbor(const Global::Field& field, const qint32 row, const qint32 column)
{
    auto resultRow = getTopRowIndex(field, row);
    return field[resultRow][column];
}

const Global::CellPtr& NeighborFinder::getTopRightNeighbor(const Global::Field& field, const qint32 row, const qint32 column)
{
    auto resultRow = getTopRowIndex(field, row);
    auto resultColumn = getRightColumnIndex(field, column);
    return field[resultRow][resultColumn];
}

const Global::CellPtr& NeighborFinder::getLeftNeighbor(const Global::Field& field, const qint32 row, const qint32 column)
{
    auto resultColumn = getLeftColumnIndex(field, column);
    return field[row][resultColumn];
}

const Global::CellPtr& NeighborFinder::getRightNeighbor(const Global::Field& field, const qint32 row, const qint32 column)
{
    auto resultColumn = getRightColumnIndex(field, column);
    return field[row][resultColumn];
}

const Global::CellPtr& NeighborFinder::getBottomLeftNeighbor(const Global::Field& field, const qint32 row, const qint32 column)
{
    auto resultRow = getBottomRowIndex(field, row);
    auto resultColumn = getLeftColumnIndex(field, column);
    return field[resultRow][resultColumn];
}

const Global::CellPtr& NeighborFinder::getBottomNeighbor(const Global::Field& field, const qint32 row, const qint32 column)
{
    auto resultRow = getBottomRowIndex(field, row);
    return field[resultRow][column];
}

const Global::CellPtr& NeighborFinder::getBottomRightNeighbor(const Global::Field& field, const qint32 row, const qint32 column)
{
    auto resultRow = getBottomRowIndex(field, row);
    auto resultColumn = getRightColumnIndex(field, column);
    return field[resultRow][resultColumn];
}
