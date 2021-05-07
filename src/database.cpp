#include "database.hpp"

#include <QDateTime>

using namespace model;

namespace {
constexpr auto FILE_URL_PREFIX = "file://";
}

ImageDatabase::ImageDatabase(Options &&options)
		: m_options(std::move(options)) {
}

auto ImageDatabase::stretch() const noexcept -> bool {
	return m_options.stretch;
}

auto ImageDatabase::timeout() const noexcept -> int {
	return m_options.timeout;
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

QString ImageDatabase::next() noexcept {
	return FILE_URL_PREFIX + m_list[m_history.next([this]() {
		if (m_index.has_value())
			m_index = m_index.value() + 1;
		else
			m_index = 0;

		return m_index.value();
	})];
}

QString ImageDatabase::prev() noexcept {
	return FILE_URL_PREFIX + m_list[m_history.prev()];
}

void ImageDatabase::setList(QStringList &&rhs) {
	m_list = std::move(rhs);
}
