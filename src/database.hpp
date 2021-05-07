#pragma once

#include <QObject>

#include <functional>
#include <optional>

namespace model {

struct Options {
	bool stretch{false};
	int timeout{60000};
};

class HistoryIndex {
public:
	HistoryIndex() {
		indexes.reserve(4096);
	}

	auto next(std::function<int()> &&get_index) -> int {
		if (delta == 0) {
			indexes.emplace_back(get_index());
		} else {
			delta--;
		}
		return indexes[indexes.size() - delta - 1];
	};

	auto prev() -> int {
		if ((delta + 1) >= indexes.size())
			return indexes[0];

		delta++;
		return indexes[indexes.size() - delta - 1];
	};

private:
	std::vector<int> indexes;
	int delta{};
};

class ImageDatabase final : public QObject {
	Q_OBJECT
public:
	ImageDatabase(Options &&options);
	virtual ~ImageDatabase() final = default;

	Q_INVOKABLE bool stretch() const noexcept;
	Q_INVOKABLE int timeout() const noexcept;
	Q_INVOKABLE QString time() const noexcept;
	Q_INVOKABLE int count() const noexcept;
	Q_INVOKABLE QString path(int index) const noexcept;
	Q_INVOKABLE QString next() noexcept;
	Q_INVOKABLE QString prev() noexcept;

	void setList(QStringList &&rhs);

private:
	HistoryIndex m_history;
	std::optional<int> m_index;

	Options m_options;
	QStringList m_list;
};

} // namespace model
