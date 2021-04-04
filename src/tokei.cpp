#include "tokei.hpp"

using namespace model;

int tokei::rowCount(const QModelIndex &) const {
	return static_cast<int>(m_entries.size());
}

QVariant tokei::data(const QModelIndex &index, int) const {
	const auto i = static_cast<std::size_t>(index.row());
	return m_entries[i].name;
}

void tokei::setEntries(entries &&rhs) {
	beginResetModel();
	m_entries = std::move(rhs);
	endResetModel();
}

QHash<int, QByteArray> tokei::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[Name] = "name";
	return roles;
}
