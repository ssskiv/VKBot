import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    id: mainw
    width: 640
    height: 480
    visible: true
    title: qsTr("VKBotServer")
    color:"grey"
    property string consout
    TabView {
        width:parent.width
        height: parent.height
        Tab
        {
            title:"VK"
            Rectangle
            {
                TextField
                {
                    id:_accessToken
                    maximumLength: 20
                    onEditingFinished://Когда нажат Enter/Return:
                    {
                        _accessToken.readOnly=true // Поле перестает редактироваться
                        consout+="Access roken:"+_accessToken.text+'/n'//Строка добавляется в консоль
                    }
                }
            }
        }

        Tab
        {
            id:cons
            title:"Console"
            Rectangle{
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


