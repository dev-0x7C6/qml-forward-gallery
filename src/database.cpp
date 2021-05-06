#include "database.hpp"

#include <QDateTime>

using namespace model;

ImageDatabase::ImageDatabase(Options &&options)
		: m_options(std::move(options)) {
}

auto ImageDatabase::stretch() const noexcept -> bool {
	return m_options.stretch;
}

auto ImageDatabase::time() const noexcept -> QString {
	return QDateTime::currentDateTime().toString("hh:mm");
}

auto model::ImageDatabase::count() const noexcept -> int {
	return m_list.count();
}

auto ImageDatabase::path(int index) const noexcept -> QString {
	return m_list[index];
}

void ImageDatabase::setList(QStringList &&rhs) {
	m_list = std::move(rhs);
}
