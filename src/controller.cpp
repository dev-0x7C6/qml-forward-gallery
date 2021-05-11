#include "controller.hpp"

#include <QDateTime>

#include <algorithm>
#include <random>

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
	m_settings.sync();
	return FILE_URL_PREFIX + m_list[m_history.next(generator())];
}

QString Controller::prev() noexcept {
	return FILE_URL_PREFIX + m_list[m_history.prev()];
}

auto Controller::display_brightness() const noexcept -> double {
	return m_settings.value("display/brightness", 0.5).toDouble();
}

double Controller::display_contrast() const noexcept {
	return m_settings.value("display/contrast", 0.5).toDouble();
}

double Controller::display_gamma() const noexcept {
	return m_settings.value("display/gamma", 1.0).toDouble();
}

void Controller::set_display_brightness(const double value) noexcept {
	m_settings.setValue("display/brightness", value);
}

void Controller::set_display_contrast(const double value) noexcept {
	m_settings.setValue("display/contrast", value);
}

void Controller::set_display_gamma(const double value) noexcept {
	m_settings.setValue("display/gamma", value);
}

void Controller::setList(QStringList &&rhs) {
	m_list = std::move(rhs);
}

std::function<int()> Controller::generator() {
	switch (m_options.strategy) {
		case Strategy::Random:
			return [this]() -> int {
				if (m_random_indexes.empty()) {
					std::vector<int> indexes;
					indexes.reserve(m_list.count());

					for (auto i = 0; i < m_list.count(); ++i)
						indexes.emplace_back(i);

					std::random_device rd;
					std::mt19937 g(rd());
					std::shuffle(indexes.begin(), indexes.end(), g);

					for (auto &&index : indexes)
						m_random_indexes.emplace(index);
				}

				auto ret = m_random_indexes.top();
				m_random_indexes.pop();
				return ret;
			};
		case Strategy::Order:
			return [this]() -> int {
				if (m_index.has_value())
					m_index = m_index.value() + 1;
				else
					m_index = 0;

				if (m_index.value() >= m_list.size())
					m_index = 0;

				return m_index.value();
			};
	}

	return nullptr;
}
