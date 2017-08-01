import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: gameWindow
    title: qsTr("Chess")
    visible: true
    width: gameBoard.width + 222
    height: gameBoard.height
    
    property int squareSize: 70

    property var images: [
        {'imgPath' : "/images/white_pawn.svg"},
        {'imgPath' : "/images/black_pawn.svg"},
        {'imgPath' : "/images/white_rook.svg"},
        {'imgPath' : "/images/black_rook.svg"},
        {'imgPath' : "/images/white_knight.svg"},
        {'imgPath' : "/images/black_knight.svg"},
        {'imgPath' : "/images/white_bishop.svg"},
        {'imgPath' : "/images/black_bishop.svg"},
        {'imgPath' : "/images/white_queen.svg"},
        {'imgPath' : "/images/black_queen.svg"},
        {'imgPath' : "/images/white_king.svg"},
        {'imgPath' : "/images/black_king.svg"}
    ]

    Item {
        id: gameBoard
        x: 0
        y: 0
        width : logic.boardSize * squareSize
        height: logic.boardSize * squareSize

        Image {
            source: "/images/chess_board.jpg"
            height: gameBoard.height
            width: gameBoard.width
        }

        Repeater {
            model: logic

            Image {
                visible: alive
                enabled: alive

                height: squareSize
                width : squareSize

                x: squareSize * positionX
                y: squareSize * positionY

                source: images[type].imgPath

                MouseArea {
                    anchors.fill: parent
                    drag.target: parent

                    property int startX: 0
                    property int startY: 0

                    onPressed: {
                        startX = parent.x;
                        startY = parent.y;
                    }

                    onReleased: {
                        var fromX = startX / squareSize;
                        var fromY = startY / squareSize;
                        var toX   = (parent.x + mouseX) / squareSize;
                        var toY   = (parent.y + mouseY) / squareSize;

                        logic.move(fromX, fromY, toX, toY);
                    }
                }
            }
        }
    }

    Button {
        id: saveGame
        anchors.left: gameBoard.right
        anchors.right: parent.right
        anchors.top: gameBoard.top
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        height: 44

        text: "Save Game"

        onClicked: logic.saveGame();
    }

    Button{
        id: exit
        anchors.left: gameBoard.right
        anchors.right: parent.right
        anchors.bottom: gameBoard.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        height: 44

        text: "Exit"

        onClicked: gameWindow.close();

    }

}

