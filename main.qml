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
                    id:validstring
                    maximumLength: 20
                    onEditingFinished:
                    {
                        validstring.readOnly=true
                        consout+="Validation String:"+validstring.text+'/n'
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


