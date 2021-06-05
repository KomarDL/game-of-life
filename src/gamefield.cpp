#include "gamefield.h"
#include <QPaintEvent>
#include <QResizeEvent>
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

void GameField::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    p.setPen(Qt::black);
    for (const auto& row : m_field) {
        for (const auto& cell : row) {
            p.drawRect(cell->rect());
        }
    }
}

void GameField::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    createField();
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
    m_field.resize(m_fieldSize.height());
    for (auto& row : m_field) {
        row.resize(m_fieldSize.width());
    }
}

QRectF GameField::generateInitialRect()
{
//    qDebug() << "width:" << this->width() << "height:" << this->height();
    auto rectWidth = qreal(this->width()) / m_fieldSize.width();
    auto rectHeigth = qreal(this->height()) / m_fieldSize.height();
    return QRectF(0, 0, rectWidth, rectHeigth);
}
