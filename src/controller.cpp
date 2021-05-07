#include "controller.hpp"

#include <QDateTime>

using namespace Logic;

namespace {
constexpr auto FILE_URL_PREFIX = "file://";
}

Controller::Controller(Options &&options)
		: m_options(std::move(options)) {
}

auto Controller::stretch() const noexcept -> bool {
	return m_options.stretch;
}

auto Controller::timeout() const noexcept -> int {
	return m_options.timeout;
}

auto Controller::time() const noexcept -> QString {
	return QDateTime::currentDateTime().toString("hh:mm");
}

auto Controller::count() const noexcept -> int {
	return m_list.count();
}

QString Controller::next() noexcept {
	return FILE_URL_PREFIX + m_list[m_history.next([this]() {
		if (m_index.has_value())
			m_index = m_index.value() + 1;
		else
			m_index = 0;

		if (m_index.value() >= m_list.size())
			m_index = 0;

		return m_index.value();
	})];
}

QString Controller::prev() noexcept {
	return FILE_URL_PREFIX + m_list[m_history.prev()];
}

void Controller::setList(QStringList &&rhs) {
	m_list = std::move(rhs);
}
