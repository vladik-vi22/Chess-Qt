import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow{
    id: menuWindow
    title: qsTr("Menu")
    visible: true
    width: 400
    height: 400

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

    property string winner: "End of Game"

    property bool visiblePrevNext: false
    property bool enabledFigure: false

    Button{
        id: newGame
        anchors.left: menuWindow.left
        anchors.right: menuWindow.right
        anchors.top: menuWindow.top
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        width: menuWindow.width
        height: menuWindow.height / 4 - 10

        text: "New Game"

        onClicked: {
            logic.newGame();
            menuWindow.hide();
            visiblePrevNext = false
            gameWindow.show();
        }
    }

    Button{
        id: loadGame
        anchors.left: menuWindow.left
        anchors.right: menuWindow.right
        anchors.top: newGame.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        width: menuWindow.width
        height: menuWindow.height / 4 - 10

        text: "Load Game"

        onClicked: {
            logic.loadGame();
            menuWindow.hide();
            visiblePrevNext = true
            gameWindow.show();
        }
    }

    Button{
        id: lastGame
        anchors.left: menuWindow.left
        anchors.right: menuWindow.right
        anchors.top: loadGame.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        width: menuWindow.width
        height: menuWindow.height / 4 - 10

        text: "Show Last Game"

        onClicked: {
            logic.newGame();
            menuWindow.hide();
            showLastGameWindow.show();
            logic.lastGame();
        }
    }

    Button{
        id: exit
        anchors.left: menuWindow.left
        anchors.right: menuWindow.right
        anchors.top: lastGame.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        width: menuWindow.width
        height: menuWindow.height / 4 - 10

        text: "Exit"

        onClicked: menuWindow.close();
    }

    ApplicationWindow {
        id: gameWindow
        title: qsTr("Chess")
        width: gameBoard.width + 222
        height: gameBoard.height

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
                enabled: true

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

                            if(logic.endGame() === 1){
                                winner = " White Win! "
                                gameWindow.hide();
                                endWindow.show();
                            }

                            if(logic.endGame() === 2){
                                winner = " Black Win! "
                                gameWindow.hide();
                                endWindow.show();
                            }

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

        Button {
            id: prevMove
            visible: visiblePrevNext
            anchors.left: gameBoard.right
            anchors.right: parent.right
            anchors.top: saveGame.bottom
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            height: 44

            text: "prev"

            onClicked: logic.prevMove()
        }

        Button {
            id: nextMove
            visible: visiblePrevNext
            anchors.left: gameBoard.right
            anchors.right: parent.right
            anchors.top: prevMove.bottom
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            height: 44

            text: "next"

            onClicked: logic.nextMove()

        }

        Button{
            id: menu
            anchors.left: gameBoard.right
            anchors.right: parent.right
            anchors.bottom: gameBoard.bottom
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            height: 44

            text: "Menu"

            onClicked: {
                gameWindow.hide();
                menuWindow.show();
            }
        }
    }

    ApplicationWindow{
        id: endWindow
        title: qsTr("End of game")
        width: 400
        height: 222

        Text {
            id: endGame
            text: winner
            font.bold: true
            font.pixelSize: 44
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        Button{
            id: menu2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            height: parent.height / 3

            text: "Menu"

            onClicked: {
                endWindow.hide();
                menuWindow.show();
            }
        }
    }

    ApplicationWindow {
        id: showLastGameWindow
        title: qsTr("Chess")
        width: gameBoard.width + 222
        height: gameBoard.height

        Item {
            id: showLastGameBoard
            x: 0
            y: 0
            width : logic.boardSize * squareSize
            height: logic.boardSize * squareSize

            Image {
                source: "/images/chess_board.jpg"
                height: showLastGameBoard.height
                width: showLastGameBoard.width
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

                }
            }

            Button{
                id: next
                anchors.left: showLastGameBoard.right
                anchors.top: showLastGameBoard.top
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.topMargin: 10
                anchors.bottomMargin: 10
                height: showLastGameBoard.height / 3
                width: showLastGameWindow.width - showLastGameBoard.width - 10

                text: "next"

                onClicked:{
                    logic.nextMove();
                }
            }

            Button {
                id: prev
                anchors.left: showLastGameBoard.right
                anchors.top: next.bottom
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.topMargin: 10
                anchors.bottomMargin: 10
                height: showLastGameBoard.height / 3
                width: showLastGameWindow.width - showLastGameBoard.width - 10

                text: "prev"

                onClicked:{
                    logic.prevMove();
                }
            }

            Button{
                id: menu3
                anchors.left: showLastGameBoard.right
                anchors.bottom: showLastGameBoard.bottom
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.topMargin: 10
                anchors.bottomMargin: 10
                height: 44
                width: showLastGameWindow.width - showLastGameBoard.width - 10

                text: "Menu"

                onClicked: {
                    showLastGameWindow.hide();
                    menuWindow.show();
                }
            }
        }
    }
}
