#pragma once

#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtCore/QAbstractListModel>

#include <QtWebSockets/QWebSocket>

class Room : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MessageModel* messages READ messagesModel FINAL)
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)

public:

    class MessageModel;

    explicit Room(QObject *parent = nullptr);

    MessageModel* messagesModel() const;

    bool isConnected() const;

signals:

    void connectedChanged();

public slots:

    void joinToChat(const QString& nickName);
    void sendMessage(const QString& message);

private slots:

    void onConnected();
    void onClosed();
    void onProcessMessage(const QString &message);

private:

    MessageModel *m_messages;
    QWebSocket m_webSocket;
    bool m_connected;

    QString m_nickName;
};


class Room::MessageModel final: public QAbstractListModel
{
    Q_OBJECT

public:

    enum Roles {
        Name = Qt::UserRole + 1,
        Message,
        SentByMe
    };

    MessageModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void append(const QString& nick, const QString& message, bool sentByMe);

private:

    struct msg
    {
        QString nick;
        QString message;
        bool    sentByMe;
    };

private:

    QVector<msg> m_messages;
};
