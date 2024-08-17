#pragma once

#include <QtQml/qqmlregistration.h>
#include <QAbstractTableModel>
#include <QColor>

#include "global.h"

class GameModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QColor deadColor READ deadColor CONSTANT FINAL)
public:
    GameModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    QColor deadColor() const noexcept { return {Qt::white}; }

    Q_INVOKABLE void step() noexcept;
    Q_INVOKABLE void clear() noexcept;


private:
    Global::field m_field;

    void resizeField();

    Global::neighbors getNeighbors(int row, int column);
    Global::cell getResultColor(const Global::neighbors& neighbors);
};
