#ifndef CELL_H
#define CELL_H

#include <memory>
#include <array>

#include <QRect>
#include <QColor>


class Cell
{
public:
    static constexpr auto NEIGHBORS_AMOUNT = 8;

    explicit Cell(const QRect& rect = {}, const QColor& color = Qt::black);

    QRect rect() const noexcept { return m_rect; };
    void setRect(const QRect& rect) noexcept { m_rect = rect; };

    QColor color() const noexcept { return m_color; }
    void setColor(const QColor& color) noexcept { m_color = color; };

    std::array<std::weak_ptr<Cell>, NEIGHBORS_AMOUNT> neighbors() const noexcept { return m_neighbors; }

private:
    QRect m_rect;
    QColor m_color;
    std::array<std::weak_ptr<Cell>, NEIGHBORS_AMOUNT> m_neighbors;
};

#endif // CELL_H
