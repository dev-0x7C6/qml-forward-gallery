#include "downloader.hpp"

#include <QNetworkReply>

namespace network {

void downloader::download(const QUrl &source, std::function<void(const QByteArray &)> &&callable) {
	QNetworkRequest request(source);
	auto reply = m_manager.get(request);

	QObject::connect(reply, &QNetworkReply::finished, [reply, callable{std::move(callable)}]() {
		callable(reply->readAll());
	});
}

} // namespace network
