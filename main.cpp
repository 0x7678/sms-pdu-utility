#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include "pdu.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/title.png"));
    QQmlApplicationEngine engine;

    Pdu pdu;
    engine.rootContext()->setContextProperty("pdu", &pdu);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    QObject *rootObject = engine.rootObjects().value(0);

    pdu.resultTextArea = rootObject->findChild<QObject*>("resultTextObj");

    return app.exec();
}
