#pragma once

#include <QObject>
#include <optional>
#include <src/history-index.hpp>

namespace Logic {

struct Options {
	bool stretch{false};
	int timeout{60000};
};

class Controller final : public QObject {
	Q_OBJECT
public:
	Controller(Options &&options);
	virtual ~Controller() final = default;

	Q_INVOKABLE bool stretch() const noexcept;
	Q_INVOKABLE int timeout() const noexcept;
	Q_INVOKABLE QString time() const noexcept;
	Q_INVOKABLE int count() const noexcept;
	Q_INVOKABLE QString next() noexcept;
	Q_INVOKABLE QString prev() noexcept;

	void setList(QStringList &&rhs);

private:
	HistoryIndex m_history;
	std::optional<int> m_index;

	Options m_options;
	QStringList m_list;
};

} // namespace Logic
