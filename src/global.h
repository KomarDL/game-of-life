#ifndef GLOBAL_H
#define GLOBAL_H

#include <memory>

#include <QObject>
#include <QVector>


class Cell;

namespace  Global {
    using cell_ptr = std::shared_ptr<Cell>;
    using row = QVector<cell_ptr>;
    using field = QVector<row>;
    static constexpr auto DEAD_COLOR = Qt::white;
    static constexpr auto LIFE_COLOR = Qt::black;
}

Q_DECLARE_METATYPE(Global::field)

#endif // GLOBAL_H
