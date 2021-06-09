#include "gamefield.h"
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

GameField::GameField(QWidget *parent) : GameField(DEFAULT_SIZE, parent)
{

}

GameField::GameField(const QSize &fieldSize, QWidget *parent) : QWidget(parent)
    , m_fieldSize(fieldSize)
{
    auto palette = this->palette();
    palette.setBrush(QPalette::Window, Qt::white);
    setPalette(palette);
    setAutoFillBackground(true);

    resizeField();
    createField();
}

void GameField::setFieldSize(QSize fieldSize)
{
    if (m_fieldSize == fieldSize) {
        return;
    }
    m_fieldSize = fieldSize;
    resizeField();
    createField();
    emit fieldSizeChanged(m_fieldSize);
}

void GameField::setCellBrushColor(QColor color)
{
    if (m_cellBrushColor == color) {
        return;
    }
    m_cellBrushColor = color;
    emit cellBrushColorChanged(m_cellBrushColor);
}

void GameField::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::black);
    for (const auto& row : m_field) {
        for (const auto& cell : row) {
            p.setBrush(cell->color());
            p.drawRect(cell->rect());
        }
    }
    event->accept();
}

void GameField::resizeEvent(QResizeEvent *event)
{
    createField();
    event->accept();
}

void GameField::mousePressEvent(QMouseEvent *event)
{
    handleMouseEvents(event);
    update();
    event->accept();
}

void GameField::mouseMoveEvent(QMouseEvent *event)
{
    handleMouseEvents(event);
    update();
    event->accept();
}

void GameField::createField()
{
    auto rowRect = generateInitialRect();
    for (auto i = 0; i < m_field.size(); ++i) {
        auto& row = m_field[i];
        auto columnRect = rowRect;
        for (auto j = 0; j < row.size(); ++j) {
            auto& cell = row[j];
            if (cell == nullptr) {
                cell = std::make_shared<Cell>();
            }
            cell->setRect(columnRect);
            columnRect.moveRight(columnRect.right() + columnRect.width());
        }
        rowRect.moveBottom(rowRect.bottom() + rowRect.height());
    }
}

void GameField::resizeField()
{
    m_field.resize(fieldSize().height());
    for (auto& row : m_field) {
        row.resize(fieldSize().width());
    }
}

QRectF GameField::generateInitialRect()
{
//    qDebug() << "width:" << this->width() << "height:" << this->height();
    auto rectWidth = qreal(this->width()) / fieldSize().width();
    auto rectHeigth = qreal(this->height()) / fieldSize().height();
    return QRectF(0, 0, rectWidth, rectHeigth);
}

void GameField::handleMouseEvents(QMouseEvent *event)
{
    if (!rect().contains(event->pos())) {
        return;
    }

    auto cell = getCellThatIncludesGivenCoord(event->pos());
    if (event->buttons() & Qt::MouseButton::LeftButton) {
        cell->setColor(m_cellBrushColor);
    } else if (event->buttons() & Qt::MouseButton::RightButton) {
        cell->setColor(Qt::white);
    }
}

Global::cell_ptr GameField::getCellThatIncludesGivenCoord(const QPoint &coord)
{
    auto row = getCellRowThatIncledusGivenCoord(coord.y());
    auto column = getCellColumnThatIncledusGivenCoord(coord.x());
    return m_field[row][column];
}

int GameField::getCellRowThatIncledusGivenCoord(int y)
{
    auto cellHeight = m_field.first().first()->rect().height();
    return y / cellHeight;
}

int GameField::getCellColumnThatIncledusGivenCoord(int x)
{
    auto cellWidth = m_field.first().first()->rect().width();
    return x / cellWidth;
}
