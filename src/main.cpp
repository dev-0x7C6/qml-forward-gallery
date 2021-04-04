#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <src/downloader.hpp>
#include <src/tokei.hpp>

#include <functional>

#include <QFile>
#include <QQmlContext>
#include <QDir>
#include <QSettings>
#include <QTimer>

auto save_to_file(const QString &path, std::function<void(const QString &)> &&callable) {
	return [path, callable{std::move(callable)}](const QByteArray &data) {
		QFile file(path);
		file.open(QIODevice::ReadWrite);
		file.write(data);
		file.close();
		callable(path);
	};
}

auto save_to_model(const QString &path, model::tokei &model) {
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

	downloader.download(QUrl("https://devwork.space/tokei/index.ini"), save_to_model(metadata + "index.ini", model));

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("tokeiModel", &model);

	QTimer timer;
	timer.start(1000);

	QObject::connect(&timer, &QTimer::timeout, [&downloader, &model]() {
		const auto now = QTime::currentTime();
		const auto entry = model.selected();
		if (!entry)
			return;
		auto url = entry->url;
		url = url.replace("${hh}", now.toString("hh"));
		url = url.replace("${mm}", now.toString("mm"));

		QDir dir;
		dir.mkpath(metadata + entry->name);

		auto filename = now.toString("hhmm") + ".jpg";
		auto path = metadata + entry->name + QDir::separator() + filename;

		if (QFile::exists(path))
			emit model.imageReady(path);

		downloader.download({url}, save_to_file(path, [&model](auto &&path) {
			emit model.imageReady(path);
		}));
	});

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
