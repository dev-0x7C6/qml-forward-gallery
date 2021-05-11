#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <src/controller.hpp>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDirIterator>
#include <QQmlContext>

#include <iostream>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	QCoreApplication::setApplicationName("qml-forward-gallery");
	QCoreApplication::setOrganizationName("qml-forward-gallery");
	QGuiApplication app(argc, argv);

	QCommandLineParser parser;
	parser.addHelpOption();
	parser.addVersionOption();

	parser.addOptions({//
		{{"d", "directory"}, QCoreApplication::translate("main", "open directory."), QCoreApplication::translate("main", "directory")},
		{{"", "sort"}, QCoreApplication::translate("main", "sort file order by name.")},
		{{"", "random"}, QCoreApplication::translate("main", "random sequence.")},
		{{"s", "stretch"}, QCoreApplication::translate("main", "stretch image")},
		{{"t", "timeout"}, QCoreApplication::translate("main", "next slide timeout"), QCoreApplication::translate("main", "time-ms")}});
	parser.process(app);

	const auto paths = parser.values("directory");

	if (paths.isEmpty()) {
		std::cerr << "please use directory path with --directory parameter" << std::endl;
		return -1;
	}

	Logic::Options opts;
	opts.stretch = parser.isSet("stretch");
	opts.strategy = parser.isSet("random") ? Logic::Strategy::Random : Logic::Strategy::Order;

	if (parser.isSet("timeout"))
		opts.timeout = parser.value("timeout").toInt();

	QStringList list;
	Logic::Controller controller(std::move(opts));

	for (auto &&path : paths) {
		QDirIterator iter(path, QDir::Filter::NoDotAndDotDot | QDir::Filter::Files, QDirIterator::Subdirectories);

		while (iter.hasNext())
			list.append(iter.next());
	}

	if (parser.isSet("sort"))
		list.sort();

	controller.setList(std::move(list));

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("controller", &controller);

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
