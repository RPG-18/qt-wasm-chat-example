#include <QtCore/QtDebug>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>


#include "room.h"
#include "config.h"

Room::Room(QObject *parent)
    : QObject (parent)
    , m_messages(new MessageModel(this))
    , m_connected(false)
{
    connect(&m_webSocket, &QWebSocket::connected,
            this, &Room::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected,
            this, &Room::onClosed);

    const auto url = Config::wsUrl();
    qDebug()<<"Open"<< url;
    m_webSocket.open(url);
}

void Room::joinToChat(const QString& nickName)
{
    m_nickName = nickName;
}

Room::MessageModel* Room::messagesModel() const
{
    return m_messages;
}

void Room::onConnected()
{
    m_connected = true;

    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &Room::onProcessMessage);

    emit connectedChanged();
}

void Room::onClosed()
{
    m_connected = false;
    emit connectedChanged();
}

void Room::onProcessMessage(const QString &message)
{
    qDebug()<<message;

    const auto doc = QJsonDocument::fromJson(message.toUtf8());
    const auto obj = doc.object();

    m_messages->append(obj["from"].toString()
            , obj["message"].toString()
            , false);
}

bool Room::isConnected() const
{
    return m_connected;
}

void Room::sendMessage(const QString& message)
{
    if (!m_connected || message.isEmpty())
    {
        return;
    }

    QJsonObject obj;
    obj["from"] = m_nickName;
    obj["message"] = message;

    QJsonDocument doc(obj);
    m_webSocket.sendTextMessage(doc.toJson(QJsonDocument::Compact));
    m_messages->append(m_nickName
            , message
            , true);
}

Room::MessageModel::MessageModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int Room::MessageModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }

    return m_messages.size();
}

QVariant Room::MessageModel::data(const QModelIndex &index, int role) const
{
    const auto r = index.row();
    switch (role) {
    case Name:
        return m_messages[r].nick;
    case Message:
        return m_messages[r].message;
    case SentByMe:
        return m_messages[r].sentByMe;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Room::MessageModel::roleNames() const
{
    static const QHash<int, QByteArray> roles = {
        {Name, "nick"},
        {Message, "message"},
        {SentByMe, "sentByMe"},
    };

    return roles;
}

void Room::MessageModel::append(const QString& nick, const QString& message, bool sentByMe)
{
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.push_back({nick, message, sentByMe});
    endInsertRows();
}

