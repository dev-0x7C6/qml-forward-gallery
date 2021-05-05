#pragma once

#include <QObject>

namespace model {

class ImageDatabase final : public QObject {
	Q_OBJECT
public:
	virtual ~ImageDatabase() final = default;

	Q_INVOKABLE QString time() const noexcept;
	Q_INVOKABLE int count() const noexcept;
	Q_INVOKABLE QString path(int index) const noexcept;

	void setList(QStringList &&rhs);

private:
	QStringList m_list;
};

} // namespace model
