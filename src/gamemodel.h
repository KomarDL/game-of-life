#pragma once

#include <QAbstractTableModel>

#include "global.h"

class GameModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GameModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    // bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;
    // bool removeRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;

private:
    Global::field m_field;

    void resizeField();
};
