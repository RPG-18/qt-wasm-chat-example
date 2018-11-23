#include <QtCore/QByteArray>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "config.h"

QUrl Config::wsUrl()
{
    QByteArray buff(1024, 0);
    EM_ASM_({
       var url = "ws://"+ window.location.hostname + ":" + window.location.port + "/ws";
       stringToUTF8(url, $0, $1);
    }, buff.data(), buff.size());
    return QUrl(QString::fromUtf8(buff));
}
