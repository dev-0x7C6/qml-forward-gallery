#pragma once

#include <QObject>
#include <QSettings>

#include <optional>
#include <stack>
#include <src/history-index.hpp>

namespace Logic {

enum Strategy {
	Order,
	Random
};

struct Options {
	Strategy strategy{Strategy::Random};
	bool stretch{false};
	int timeout{60000};
};

class Controller final : public QObject {
	Q_OBJECT
	Q_PROPERTY(double display_brightness READ display_brightness WRITE set_display_brightness NOTIFY display_brightness_changed)
	Q_PROPERTY(double display_contrast READ display_contrast WRITE set_display_contrast NOTIFY display_contrast_changed)
	Q_PROPERTY(double display_gamma READ display_gamma WRITE set_display_gamma NOTIFY display_gamma_changed)
public:
	Controller(Options &&options);
	virtual ~Controller() final = default;

	Q_ENUM(Strategy)
	Q_INVOKABLE bool stretch() const noexcept;
	Q_INVOKABLE int timeout() const noexcept;
	Q_INVOKABLE QString time() const noexcept;
	Q_INVOKABLE int count() const noexcept;
	Q_INVOKABLE QString next() noexcept;
	Q_INVOKABLE QString prev() noexcept;

	auto display_brightness() const noexcept -> double;
	auto display_contrast() const noexcept -> double;
	auto display_gamma() const noexcept -> double;
	auto set_display_brightness(double) noexcept -> void;
	auto set_display_contrast(double) noexcept -> void;
	auto set_display_gamma(double) noexcept -> void;

	void setList(QStringList &&rhs);

signals:
	void display_brightness_changed();
	void display_contrast_changed();
	void display_gamma_changed();

private:
	QSettings m_settings;
	std::function<int()> generator();

	HistoryIndex m_history;
	std::optional<int> m_index;
	std::stack<int> m_random_indexes;

	Options m_options;
	QStringList m_list;
};

} // namespace Logic
