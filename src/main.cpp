#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <src/downloader.hpp>
#include <src/tokei.hpp>

#include <functional>

#include <QFile>
#include <QQmlContext>
#include <QDir>
#include <QSettings>

auto save_to_file(const QString &path, model::tokei &model) {
	return [path, &model](const QByteArray &data) {
		QFile file(path);
		file.open(QIODevice::ReadWrite);
		file.write(data);
		file.close();

		model::entries entries;

		QSettings settings(path, QSettings::IniFormat);
		for (auto &&group : settings.childGroups()) {
			settings.beginGroup(group);
			auto name = settings.value("name", group).toString();
			auto url = settings.value("url").toString();

			model::entry entry;
			entry.name = name;
			entry.url = url.replace("${name}", name);

			settings.endGroup();

			entries.emplace_back(std::move(entry));
		}

		model.setEntries(std::move(entries));
	};
}

const auto metadata = QDir::homePath() + QDir::separator() + ".foto-tokei" + QDir::separator();

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);

	QDir dir;
	dir.mkpath(metadata);

	network::downloader downloader;
	model::tokei model;

	downloader.download(QUrl("https://devwork.space/tokei/index.ini"), save_to_file(metadata + "index.ini", model));

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("tokeiModel", &model);

	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
