﻿#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <src/database.hpp>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDirIterator>
#include <QQmlContext>

#include <iostream>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	QGuiApplication app(argc, argv);

	QCommandLineParser parser;
	parser.addHelpOption();
	parser.addVersionOption();

	parser.addOptions({{{"d", "directory"}, QCoreApplication::translate("main", "open directory."), QCoreApplication::translate("main", "directory")}});
	parser.process(app);

	const auto paths = parser.values("directory");

	if (paths.isEmpty()) {
		std::cerr << "please use directory path with --directory parameter" << std::endl;
		return -1;
	}

	QStringList list;
	model::ImageDatabase database;

	for (auto &&path : paths) {
		QDirIterator iter(path, QDir::Filter::NoDotAndDotDot | QDir::Filter::Files, QDirIterator::Subdirectories);

		while (iter.hasNext())
			list.append(iter.next());

		database.setList(std::move(list));
	}

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("database", &database);

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
