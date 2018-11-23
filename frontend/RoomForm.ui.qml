import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Page {
    width: 640
    height: 480
    anchors.fill: parent
    title: qsTr("Chat room")


    ColumnLayout {
        anchors.rightMargin: 8
        anchors.leftMargin: 8
        anchors.bottomMargin: 8
        anchors.topMargin: 8
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            displayMarginBeginning: 40
            displayMarginEnd: 40
            spacing: 12

            model: chatRoom.messages
            delegate: Column {
                anchors.right: sentByMe ? parent.right : undefined
                spacing: 6

                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined
                    Label {
                        id: nickName
                        visible: !sentByMe
                        text: model.nick
                        font.bold: true
                    }
                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24, listView.width - messageRow.spacing)
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "lightgrey" : "steelblue"


                        Label {
                            id: messageText
                            text: model.message
                            color: sentByMe ? "black" : "white"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.minimumHeight: 20
            TextField {
                id: messageField
                placeholderText: "Message"
                Layout.fillWidth: true
            }

            Button {
                id: sendButton
                text: qsTr("Send")
            }
        }
    }

    Connections {
        target: sendButton
        onClicked: {
            chatRoom.sendMessage(messageField.text)
            messageField.text = ""
        }
    }

    Connections {
        target: messageField
        onEditingFinished: {
            chatRoom.sendMessage(messageField.text)
            messageField.text = ""
        }
    }
}
