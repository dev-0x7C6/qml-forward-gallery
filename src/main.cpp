#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QFile>
#include <QDebug>

class FileDownloader {
public:
	void download(const QUrl &source, const QString &path) {
		QNetworkRequest request(source);
		auto reply = m_manager.get(request);

		QObject::connect(reply, &QNetworkReply::finished, [reply, path]() {
			QFile file(path);
			file.open(QIODevice::ReadWrite);
			file.write(reply->readAll());
			file.close();
		});
	}

private:
	QNetworkAccessManager m_manager;
};


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);

	FileDownloader downloader;
	downloader.download(QUrl("https://devwork.space/clock/hiroshima/0000.jpg"), "/home/dev/0000.jpg");

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
						  &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
