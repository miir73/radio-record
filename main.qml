import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import Stations 1.0

ApplicationWindow {
    property string backgroundColor: "#151414"
    property string elementColor: "#e3601e"
    property string activeColor: "#636361"

    visible: true
    x: 0; y: 0
    width: 640
    height: 480
    title: qsTr("RRecord Stations")
    color: backgroundColor
    StationsModel {
        id: _stationModel
    }

    GridView {
        id: _view
        property int countColumns: (Screen.width <= 400 ? 3 : Screen.width <= 700 ? 5 : 8) * 3
        anchors.fill: parent
        anchors.margins: 10
        cellHeight: (Screen.desktopAvailableWidth / countColumns) - (_view.anchors.margins - (_view.anchors.margins / 3))
        cellWidth: cellHeight
        currentIndex: -1;
        model: _stationModel
        clip: true
        focus: true

        delegate: FocusScope {
            property var view: GridView.view
            property var isCurrent: GridView.isCurrentItem
            property bool isActive: false
            property bool isActiveKey: false
            height: _view.cellHeight
            width: _view.cellWidth
            Keys.onPressed: {
                if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                    if (isActive) {
                        _stationModel.stop()
                        _view.currentIndex = -1;
                        isActive = false;
                    } else {
                        _view.currentIndex = model.index
                        _stationModel.setStation(model.index)
                        isActive = true
                    }
                }
            }

            Rectangle {
                id: _circle
                color: backgroundColor
                anchors.margins: 10
                height: parent.height * 0.75
                width: parent.width * 0.75
                anchors.horizontalCenter: parent.horizontalCenter
                radius: parent.width
                border {
                    color: isCurrent ? elementColor : activeColor
                    width: 3
                }

                Image {
                    id: _img
                    sourceSize.width: parent.width
                    sourceSize.height: parent.height
                    source: "qrc:/icons/%1".arg(name)
                }

                ColorOverlay {
                    anchors.fill: _img
                    source: _img
                    color: isCurrent ? elementColor : activeColor
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (isActive) {
                            _stationModel.stop()
                            _view.currentIndex = -1
                            isActive = false
                        } else {
                            _view.currentIndex = model.index
                            _stationModel.setStation(model.index)
                            isActive = true
                            console.log(_text.font.pointSize)
                        }
                    }
                }
            }

            Text {
                id: _text
                anchors.top: _circle.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                font.pointSize: Math.max((parent.width / 13), 13)
                horizontalAlignment: Text.AlignHCenter
                renderType: Text.NativeRendering
                text: name
                color: isCurrent ? elementColor : activeColor
            }
        }
    }
}

