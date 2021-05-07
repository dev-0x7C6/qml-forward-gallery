#pragma once

#include <QObject>
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

	void setList(QStringList &&rhs);

private:
	std::function<int()> generator();

	HistoryIndex m_history;
	std::optional<int> m_index;
	std::stack<int> m_random_indexes;

	Options m_options;
	QStringList m_list;
};

} // namespace Logic
