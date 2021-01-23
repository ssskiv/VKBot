import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    id: mainw
    objectName: "Main"
    width: 640
    height: 480
    visible: true
    title: qsTr("VKBotServer")
    color:"grey"
    property string consout


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
                    property string cppcin
                   /* function consOut(msg: string) : string {
                            consout+=msg+'\n'
                        }*/
                    onCppcinChanged: {
                    consout+=cppcin
                    }
                    objectName: "TOKEN"
                    id:_accessToken
                    maximumLength: 20
                    onEditingFinished://Когда нажат Enter/Return:
                    {
                        _accessToken.readOnly=true // Поле перестает редактироваться
                        consout+="Access token:"+_accessToken.text+'\n'//Строка добавляется в консоль

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


