#include "gamemodel.h"

#include <QColor>
#include "cell.h"

static constexpr auto FIELD_SIZE = 50;

GameModel::GameModel(QObject *parent) : QAbstractTableModel(parent)
{
    resizeField();
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return FIELD_SIZE;
}

int GameModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return FIELD_SIZE;
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    if (index.row() >= FIELD_SIZE || index.column() >= FIELD_SIZE) {
        return {};
    }

    if (role == Qt::BackgroundRole) {
        return m_field[index.row()][index.column()]->color();
    }

    return {};
}

QVariant GameModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

Qt::ItemFlags GameModel::flags(const QModelIndex &index) const
{
    return Qt::NoItemFlags;
}

bool GameModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::BackgroundRole) {
        return {};
    }

    if (index.row() >= FIELD_SIZE || index.column() >= FIELD_SIZE) {
        return {};
    }

    if (!value.canConvert<QColor>()) {
        qWarning() << "Can't convert from QVariant to QColor";
        return {};
    }

    m_field[index.row()][index.column()]->setColor(value.value<QColor>());

    Q_EMIT dataChanged(index, index, {role});
    return true;
}

void GameModel::resizeField()
{
    m_field.resize(FIELD_SIZE);
    quint8 color = 0;
    for (auto& row : m_field) {
        row.resize(FIELD_SIZE);
        for (auto& cell : row) {
            cell = std::make_shared<Cell>(QRect{}, QColor(color, 0, 0));
            color += 25;
        }
    }
}
