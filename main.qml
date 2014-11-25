import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.2
ApplicationWindow {
    visible: true
    id: mainWindow
    width: groupBox.width + 10
    height: 480

    minimumWidth: width
    minimumHeight: height
    maximumWidth: width
    maximumHeight: height

    title: qsTr("sms-pdu")
    Rectangle {
        x: 5
        y: 5
        Column {
            spacing: 5

            // Address-Value
            Row {
                spacing: 5
                MyLabel {
                    text: "SMSC-Address"
                }

                TextField {
                    width: 200
                    text: pdu.addrValue
                    onTextChanged: pdu.addrValue = text;
                    Component.onCompleted: {

                        //text = "8613800592500";
                        console.debug("textFiled com");
                    }
                }
            }

            // Address-Value
            Row {
                spacing: 5
                MyLabel {
                    text: "<font color=\"red\">*</font>Dest-Address"
                }

                TextField {
                    width: 200
                    text: pdu.destAddr
                    onTextChanged: pdu.destAddr = text;
                }
            }



            GroupBox {
                title: "TP-User Data"
                id: groupBox
                width: 340
                TextArea  {
                    anchors.fill: parent
                    wrapMode: TextEdit.Wrap
                    text: pdu.userData
                    onTextChanged: pdu.userData = text;
                }
            }
            // Button
            Row {
                Button {
                    text: "Generate"
                    onClicked: {
                        textArea.text = pdu.generate();
                    }
                }
                Button {
                    text: "analyze"
                    onClicked: pdu.analyze();
                }
            }

            GroupBox {
                title: "Result"
                width: groupBox.width

                TextArea  {
                    id: textArea
                    objectName: "resultTextObj"
                    anchors.fill: parent
                    wrapMode: TextEdit.Wrap
                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.RightButton
                        cursorShape: Qt.IBeamCursor
                        onClicked: {
                            contextMenu.popup();
                        }

                    }

                }
            }

            Menu {
                id: contextMenu

                MenuItem {
                    text: "Cut"
                    shortcut: "Ctrl+X"
                    onTriggered: textArea.cut()

                }

                MenuItem {
                    text: "Copy"
                    shortcut: "Ctrl+C"
                    onTriggered: textArea.copy()

                }

                MenuItem {
                    text: "Paste"
                    shortcut: "Ctrl+V"
                    onTriggered: textArea.paste()

                }

            }
        }
    }
}
