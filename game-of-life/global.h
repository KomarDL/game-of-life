#pragma once

#include <QObject>
#include <QVector>


class Cell;

namespace  Global {
using cell = QColor;
using row = QVector<cell>;
using neighbors = row;
using field = QVector<row>;
static constexpr auto DEAD_COLOR = Qt::white;
static constexpr auto LIFE_COLOR = Qt::black;
}

Q_DECLARE_METATYPE(Global::field)
