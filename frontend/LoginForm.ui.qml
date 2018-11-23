import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Page {
    width: 600
    height: 400
    anchors.fill: parent

    title: qsTr("Login")

    Connections {
        target: goButton
        onClicked: {
            window.joinToChat(nameField.text)
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.centerIn: parent
        Label {
            id: label
            text: qsTr("Welcome to chat")
        }

        RowLayout {
            id: rowLayout
            width: 100
            height: 100

            TextField {
                id: nameField
                placeholderText: qsTr("Text Field")
            }

            Button {
                id: goButton
                text: qsTr("Go")
            }
        }
    }
}
