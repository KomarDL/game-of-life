#include "gamefield.h"
#include <QPaintEvent>

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
}

void GameField::setFieldSize(QSize fieldSize)
{
    if (m_fieldSize == fieldSize) {
        return;
    }
    m_fieldSize = fieldSize;
    createField();
    emit fieldSizeChanged(m_fieldSize);
}

void GameField::paintEvent(QPaintEvent *event)
{

}

void GameField::createField()
{
    resizeField();
    auto rowRect = generateInitialRect();
    for (auto i = 0; i < m_field.size(); ++i) {
        auto& row = m_field[i];
        rowRect.moveBottom(rowRect.bottom() + rowRect.height());
        auto columnRect = rowRect;
        for (auto j = 0; j < row.size(); ++j) {
            auto& cell = row[j];
            columnRect.moveRight(columnRect.right() + columnRect.width());
            if (cell == nullptr) {
                cell = std::make_shared<Cell>();
            }
            cell->setRect(columnRect);
        }
    }
}

void GameField::resizeField()
{
    m_field.resize(m_fieldSize.height());
    for (auto& row : m_field) {
        row.resize(m_fieldSize.width());
    }
}

QRect GameField::generateInitialRect()
{
    auto rectWidth = this->width() / m_fieldSize.width();
    auto rectHeigth = this->height() / m_fieldSize.height();
    return QRect(0, 0, rectWidth, rectHeigth);
}
