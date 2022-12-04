#pragma once

#include <memory>
#include <array>

#include <QRect>
#include <QColor>

#include "global.h"

enum class Neighbor {
    TopLeft = 0,
    Top = 1,
    TopRight = 2,
    Left = 3,
    Right = 4,
    BottomLeft = 5,
    Bottom = 6,
    BottomRight = 7
};

class Cell
{
public:
    static constexpr auto NEIGHBORS_AMOUNT = 8;

    explicit Cell(const QRectF& rect = {}, const QColor& color = Global::DEAD_COLOR);

    const QRectF& rect() const noexcept { return m_rect; };
    void setRect(const QRectF& rect) noexcept { m_rect = rect; };

    QColor color() const noexcept { return m_color; }
    void setColor(const QColor& color) noexcept { m_color = color; };

    std::array<Global::CellWeakPtr, NEIGHBORS_AMOUNT>& neighbors() noexcept
    {
        return m_neighbors;
    }

private:
    QRectF m_rect;
    QColor m_color;
    std::array<Global::CellWeakPtr, NEIGHBORS_AMOUNT> m_neighbors;
};
