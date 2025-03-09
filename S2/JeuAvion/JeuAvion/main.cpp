#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include "Interface.h"
#include "Menu.h"
#include "globalobjects.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/jeuavion/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    app.exec();
    setConsoleSize();
    loadsettings();
    Gerer_Menu menu;
    menu.peser();

}
