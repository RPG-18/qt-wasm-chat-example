import QtQuick 2.11
import QtQuick.Controls 2.4

import io.chat 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stack")

    header: ToolBar {
        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    StackView {
        id: stackView
        initialItem: "LoginForm.ui.qml"
        anchors.fill: parent
    }

    function joinToChat(name) {
        chatRoom.joinToChat(name);
        stackView.push("RoomForm.ui.qml");
    }

    Room {
        id: chatRoom
    }
}
