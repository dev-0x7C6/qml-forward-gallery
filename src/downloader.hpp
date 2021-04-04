#pragma once

#include <QNetworkAccessManager>
#include <QUrl>

namespace network {

class downloader {
public:
	void download(const QUrl &source, std::function<void(const QByteArray &)> &&callable);

private:
	QNetworkAccessManager m_manager;
};

} // namespace network
