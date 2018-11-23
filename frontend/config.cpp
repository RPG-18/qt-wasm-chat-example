#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include "config.h"

QUrl Config::wsUrl()
{
    QCommandLineParser parser;

    QCommandLineOption wsOption(QStringList() << "u" << "url"
                                , "WebSocket url"
                                , "url"
                                , "ws://localhost:1234");
    parser.addOption(wsOption);

    parser.process(*QCoreApplication::instance());
    return QUrl(parser.value(wsOption));
}
