#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <memory>

#include <QWidget>
#include <QVector>
#include <QRect>
#include <QColor>

#include "global.h"
#include "cell.h"

class GameField : public QWidget {
    Q_OBJECT
public:
    static constexpr QSize DEFAULT_SIZE{50, 50};

    explicit GameField(QWidget* parent = nullptr);
    explicit GameField(const QSize& fieldSize = DEFAULT_SIZE, QWidget* parent = nullptr);

    QSize fieldSize() const noexcept { return m_fieldSize; }
    QColor cellColor() const noexcept { return m_cellColor; }

Q_SIGNALS:
    void fieldSizeChanged(QSize fieldSize);
    void cellColorChanged(QColor color);
public Q_SLOTS:
    void setFieldSize(QSize fieldSize);
    void setCellColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QSize m_fieldSize;
    Global::field m_field;
    QColor m_cellColor = Qt::black;

    void createField();
    void resizeField();
    QRectF generateInitialRect();
    void handleMouseEvents(QMouseEvent *event);
    Global::cell_ptr getCellThatIncledusGivenCoord(const QPoint& coord);
    int getCellRowThatIncledusGivenCoord(int y);
    int getCellColumnThatIncledusGivenCoord(int x);
};

#endif // GAMEFIELD_H
