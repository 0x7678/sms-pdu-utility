#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "pdu.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Pdu pdu;
    engine.rootContext()->setContextProperty("pdu", &pdu);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
