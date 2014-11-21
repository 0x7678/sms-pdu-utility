import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.2
ApplicationWindow {
    visible: true

    width: groupBox.width + 10
    height: 580

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

            GroupBox {
                id: groupBox
                title: "Address of the SMSC"

                Column {
                    Row {
                        spacing: 5
                        MyLabel {
                            text: "Type-of-number"
                        }
                        ComboBox {
                            id: typeOfNum
                            width: 200
                            currentIndex: pdu.typeOfNum
                            model: [ "Unknown", "International number", "National number" ]
                            onCurrentIndexChanged: pdu.typeOfNum = currentIndex;
                        }
                    }
                    Row {

                        spacing: 5
                        MyLabel {
                            text: "Numbering-plan-id"
                        }
                        ComboBox {
                            id: numPlanId
                            width: 200
                            currentIndex: pdu.numPlanId
                            model: [ "Unknown", "ISDN/telephone" ]
                            onCurrentIndexChanged: pdu.numPlanId = currentIndex;
                        }
                    }
                    // Address-Value
                    Row {
                        spacing: 5
                        MyLabel {
                            text: "Address-Value"
                        }

                        TextField {
                            width: 200
                            text: "8613800592500"
                            onTextChanged: pdu.addrValue = text;
                        }
                    }
                }

            }

            GroupBox {
                title: "TP-Destination-Address"

                Column {
                    Row {
                        spacing: 5
                        MyLabel {
                            text: "Type-of-number"
                        }
                        ComboBox {

                            width: 200
                            currentIndex: pdu.daTypeOfNum
                            model: [ "Unknown", "International number", "National number" ]
                            onCurrentIndexChanged: pdu.daTypeOfNum = currentIndex;
                        }
                    }
                    Row {

                        spacing: 5
                        MyLabel {
                            text: "Numbering-plan-id"
                        }
                        ComboBox {

                            width: 200
                            currentIndex: pdu.daNumPlanId
                            model: [ "Unknown", "ISDN/telephone" ]
                            onCurrentIndexChanged: pdu.daNumPlanId = currentIndex;
                        }
                    }
                    // Address-Value
                    Row {
                        spacing: 5
                        MyLabel {
                            text: "<font color=\"red\">*</font>Address-Value"
                        }

                        TextField {
                            width: 200
                            text: "15259206728"
                            onTextChanged: pdu.destAddr = text;
                        }
                    }
                }

            }

            GroupBox {
                title: "TP-User Data"
                width: groupBox.width
                TextArea  {
                    anchors.fill: parent
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
                    onClicked: textArea.text = "analyze"
                }
            }

            GroupBox {
                title: "Result"
                width: groupBox.width

                TextArea  {
                    id: textArea
                    anchors.fill: parent
                }
            }
        }
    }
}
