#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <memory>

#include <QWidget>
#include <QVector>
#include <QRect>

#include "cell.h"

class GameField : public QWidget {
    Q_OBJECT
public:
    using row = QVector<std::shared_ptr<Cell>>;
    static constexpr QSize DEFAULT_SIZE{10, 10};

    explicit GameField(QWidget* parent = nullptr);
    explicit GameField(const QSize& fieldSize = DEFAULT_SIZE, QWidget* parent = nullptr);

    QSize fieldSize() const noexcept { return m_fieldSize; }

Q_SIGNALS:
    void fieldSizeChanged(QSize fieldSize);
public Q_SLOTS:
    void setFieldSize(QSize fieldSize);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QSize m_fieldSize;
    QVector<row> m_field;

    void createField();
    void resizeField();
    QRect generateInitialRect();
};

#endif // GAMEFIELD_H
