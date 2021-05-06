#pragma once

#include <QObject>

namespace model {

struct Options {
	bool stretch{false};
};

class ImageDatabase final : public QObject {
	Q_OBJECT
public:
	ImageDatabase(Options &&options);
	virtual ~ImageDatabase() final = default;

	Q_INVOKABLE bool stretch() const noexcept;
	Q_INVOKABLE QString time() const noexcept;
	Q_INVOKABLE int count() const noexcept;
	Q_INVOKABLE QString path(int index) const noexcept;

	void setList(QStringList &&rhs);

private:
	Options m_options;
	QStringList m_list;
};

} // namespace model
