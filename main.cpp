#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mainimagedownloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<MainImageDownloader>("ImageDownloader", 1, 0, "MainImageDownloader");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/poehali_v2/Main.qml")));

    return app.exec();
}
