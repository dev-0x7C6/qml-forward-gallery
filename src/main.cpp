#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <src/downloader.hpp>
#include <src/tokei.hpp>

#include <functional>

#include <QFile>
#include <QDir>

auto save_to_file(const QString &path) {
	return [path](const QByteArray &data) {
		QFile file(path);
		file.open(QIODevice::ReadWrite);
		file.write(data);
		file.close();
	};
}

const auto metadata = QDir::homePath() + QDir::separator() + ".foto-tokei" + QDir::separator();

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);

	QDir dir;
	dir.mkpath(metadata);

	network::downloader downloader;
    model::tokei model;

	downloader.download(QUrl("https://devwork.space/tokei/index.ini"), save_to_file(metadata + "index.ini"));



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
