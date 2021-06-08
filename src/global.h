#ifndef GLOBAL_H
#define GLOBAL_H

#include <memory>

#include <QVector>


class Cell;

namespace  Global {
    using cell_ptr = std::shared_ptr<Cell>;
    using row = QVector<cell_ptr>;
    using field = QVector<row>;
}

#endif // GLOBAL_H
