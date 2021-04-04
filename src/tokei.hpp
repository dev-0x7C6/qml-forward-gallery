#pragma once

#include <QAbstractListModel>

namespace model {

struct entry {
    QString name;
	QString url;
};

using entries = std::vector<entry>;

class tokei final : public QAbstractListModel
{
public:
    virtual ~tokei() final = default;

    QModelIndex index(int row, int column, const QModelIndex &parent) const final;
    QModelIndex parent(const QModelIndex &child) const final;
    int rowCount(const QModelIndex &parent) const final;
    int columnCount(const QModelIndex &parent) const final;
    QVariant data(const QModelIndex &index, int role) const final;

    void setEntries(entries &&);

private:
    entries m_entries;
};

}
