#include <QApplication>
#include <QQmlApplicationEngine>
#include <framelesswindow.h>
#include <QScreen>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<FramelessWindow>("QuickFrameless", 1, 0, "FramelessWindow");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    qDebug() << app.primaryScreen()->devicePixelRatio();

    return app.exec();
}
