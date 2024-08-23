#include "gamemodel.h"

#include <QPoint>

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

    if (role == ColorRole) {
        return m_field[index.row()][index.column()];
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
    if (!index.isValid() || role != ColorRole) {
        return {};
    }

    if (index.row() >= FIELD_SIZE || index.column() >= FIELD_SIZE) {
        return {};
    }

    if (!value.canConvert<QColor>()) {
        qWarning() << "Can't convert from QVariant to QColor";
        return {};
    }

    m_field[index.row()][index.column()] = value.value<QColor>();

    Q_EMIT dataChanged(index, index, {role});
    return true;
}

QHash<int, QByteArray> GameModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ColorRole] = "color";
    return roles;
}

void GameModel::step() noexcept
{
    auto newField = m_field;
    for (auto i = 0; i < m_field.size(); ++i) {
        for (auto j = 0; j < m_field[i].size(); ++j) {
            auto neighbors = getNeighbors(i, j);
            const auto neighboursAmount = neighbors.size();
            auto &cell = newField[i][j];
            if (neighboursAmount < 2 || neighboursAmount > 3) {
                cell = deadColor();
            } else if (neighboursAmount == 3 && cell == deadColor()) {
                cell = getResultColor(neighbors);
            }
        }
    }

    m_field = std::move(newField);
    emit dataChanged(index(0, 0), index(FIELD_SIZE - 1, FIELD_SIZE - 1), {ColorRole});
}

void GameModel::clear() noexcept
{
    beginResetModel();
    resizeField();
    endResetModel();
}

void GameModel::resizeField()
{
    m_field.resize(FIELD_SIZE);;
    for (auto& row : m_field) {
        row.resize(FIELD_SIZE);
        for (auto& cell : row) {
            cell = Qt::white;
        }
    }
}

Global::neighbors GameModel::getNeighbors(int row, int column)
{
    Global::neighbors result;

    const int columnCount = m_field.front().size();
    const int rowCount = m_field.size();

    const auto topRow = (row - 1) < 0 ? rowCount - 1 : row - 1;
    const auto midRow = row;
    const auto bottomRow = (row + 1) % rowCount;

    const auto leftColumn = (column - 1) < 0 ? columnCount - 1 : column - 1;
    const auto midColumn = column;
    const auto rightColumn = (column + 1) % columnCount;

    QVector<QPoint> neighborsIndexes{{topRow, leftColumn},    {topRow, midColumn},    {topRow, rightColumn},
                                     {midRow, leftColumn},    /* current cell */      {midRow, rightColumn},
                                     {bottomRow, leftColumn}, {bottomRow, midColumn}, {bottomRow, rightColumn}};
    for (const auto &index : neighborsIndexes) {
        const auto& item = m_field[index.x()][index.y()];
        if (item != Global::DEAD_COLOR) {
            result.emplace_back(item);
        }
    }
    return result;
}

Global::cell GameModel::getResultColor(const Global::neighbors &neighbors)
{
    auto result = neighbors.first();
    for (auto i = 1; i < neighbors.size(); ++i) {
        auto hue = (result.hue() + neighbors[i].hue()) / 2;
        auto saturation = (result.saturation() + neighbors[i].saturation()) / 2;
        auto value = (result.value() + neighbors[i].value()) / 2;
        auto alpha = (result.alpha() + neighbors[i].alpha()) / 2;
        result.setHsv(hue, saturation, value, alpha);
        if (result == deadColor()) {
            result = Global::LIFE_COLOR;
        }
    }
    return result;
}
