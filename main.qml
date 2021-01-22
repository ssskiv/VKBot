import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    id: mainw
    objectName: "main"
    width: 640
    height: 480
    visible: true
    title: qsTr("VKBotServer")
    color:"grey"
    property string cppcin
    property string consout
    onCppcinChanged: {
    consout+=cppcin
    }
    TabView {
        objectName: "TabView"
        width:parent.width
        height: parent.height
        Tab
        {
            objectName: "VKTab"
            title:"VK"
            Rectangle
            {
                objectName: "rect"
                TextField
                {
                    objectName: "TOKEN"
                    id:_accessToken
                    maximumLength: 20
                    onEditingFinished://Когда нажат Enter/Return:
                    {
                        _accessToken.readOnly=true // Поле перестает редактироваться
                        consout+="Access roken:"+_accessToken.text+'\n'//Строка добавляется в консоль
                    }
                }
            }
        }

        Tab
        {
            id:cons
            objectName: "Console"
            title:"Console"
            Rectangle{
                objectName: "rect"
                color:"black"
                Label
                {
                    id:consolelab
                    color:"green"
                    Text{
                        text:consout
                        color:"green"
                    }
                }
            }
        }
    }
}


