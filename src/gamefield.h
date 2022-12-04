#pragma once

#include <memory>

#include <QWidget>
#include <QVector>
#include <QRect>
#include <QColor>
#include <QSize>

#include "global.h"
#include "cell.h"

class GameField : public QWidget {
    Q_OBJECT
public:
    static constexpr QSize DEFAULT_SIZE{50, 50};

    explicit GameField(QWidget* parent = nullptr);
    explicit GameField(const QSize& fieldSize = DEFAULT_SIZE, QWidget* parent = nullptr);

    QSize fieldSize() const noexcept { return m_fieldSize; }
    QColor cellBrushColor() const noexcept { return m_cellBrushColor; }
    Global::Field field() const noexcept { return m_field; }

Q_SIGNALS:
    void fieldSizeChanged(QSize fieldSize);
    void cellBrushColorChanged(QColor color);
public Q_SLOTS:
    void setFieldSize(QSize fieldSize);
    void setCellBrushColor(QColor color);
    void clearField();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QSize m_fieldSize;
    Global::Field m_field;
    QColor m_cellBrushColor = Qt::black;

    void createField();
    void resizeField();
    QRectF generateInitialRect();
    void handleMouseEvents(QMouseEvent *event);
    Global::CellPtr getCellThatIncludesGivenCoord(const QPoint& coord);
    int getCellRowThatIncledusGivenCoord(int y);
    int getCellColumnThatIncledusGivenCoord(int x);
};

