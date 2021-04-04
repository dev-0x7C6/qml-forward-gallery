#include "tokei.hpp"

using namespace model;

QModelIndex tokei::index(int row, int column, const QModelIndex &parent) const
{

}

QModelIndex tokei::parent(const QModelIndex &child) const
{

}

int tokei::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return {};

    return m_entries.size();
}

int tokei::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return {};

    return 1;
}

QVariant tokei::data(const QModelIndex &index, int) const
{
    return m_entries[index.row()].name;
}

void tokei::setEntries(entries &&rhs)
{
    beginResetModel();
    m_entries = std::move(rhs);
    endResetModel();
}
