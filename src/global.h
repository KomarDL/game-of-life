#pragma once

#include <memory>

#include <QObject>
#include <QVector>


class Cell;

namespace  Global {
    using CellPtr = std::shared_ptr<Cell>;
    using CellWeakPtr = std::weak_ptr<Cell>;
    using Row = QVector<CellPtr>;
    using Field = QVector<Row>;
    static constexpr auto DEAD_COLOR = Qt::white;
    static constexpr auto LIFE_COLOR = Qt::black;
}

Q_DECLARE_METATYPE(Global::Field)
