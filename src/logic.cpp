#include "logic.h"
#include <QList>
#include <QByteArray>
#include <QHash>
#include <QFile>
#include <QDataStream>
#include <iostream>


struct Logic::Impl
{
    QList<Figure> figures;

    int findByPosition(int x, int y);
};

int Logic::Impl::findByPosition(int x, int y) {
    for (int i(0); i<figures.size(); ++i) {
        if (figures[i].x != x || figures[i].y != y ) {
            continue;
        }
        return i;
    }
    return -1;
}


Logic::Logic(QObject *parent)
    : QAbstractListModel(parent)
    , impl(new Impl())
{
    impl->figures = GameFigures;
}

Logic::~Logic() {
}

int Logic::boardSize() const {
    return BOARD_SIZE;
}

int Logic::rowCount(const QModelIndex & ) const {
    return impl->figures.size();
}

QHash<int, QByteArray> Logic::roleNames() const { 
    QHash<int, QByteArray> names;
    names.insert(Roles::Type      , "type");
    names.insert(Roles::PositionX , "positionX");
    names.insert(Roles::PositionY , "positionY");
    names.insert(Roles::Alive     , "alive");
    return names;
}

QVariant Logic::data(const QModelIndex & modelIndex, int role) const { 
    if (!modelIndex.isValid()) {
        return QVariant();
    }
    
    int index = static_cast<int>(modelIndex.row());

    if (index >= impl->figures.size() || index < 0) {
        return QVariant();
    }

    Figure & figure = impl->figures[index];
    
    switch (role) {
    case Roles::Type     : return figure.type;
    case Roles::PositionX: return figure.x;
    case Roles::PositionY: return figure.y;
    case Roles::Alive    : return figure.alive;
    }
    return QVariant();
}

void Logic::clear() {
    beginResetModel();
    impl->figures.clear();
    endResetModel();
}

void Logic::newGame(){
    impl->figures = newGameFigures();
    for (int Index = 0; Index < 32; Index++){
        QModelIndex topLeft = createIndex(Index, 0);
        QModelIndex bottomRight = createIndex(Index, 0);
        emit dataChanged(topLeft, bottomRight);
    }
}

void Logic::loadGame(){
    impl->figures = loadGameFigures();
    for (int Index = 0; Index < 32; Index++){
        QModelIndex topLeft = createIndex(Index, 0);
        QModelIndex bottomRight = createIndex(Index, 0);
        emit dataChanged(topLeft, bottomRight);
    }
}

void Logic::saveGame(){
    QFile FsavedGame("src/SavedGame");
    FsavedGame.open(QFile::WriteOnly);
    QDataStream out(&FsavedGame);
    for (int i = 0; i < 32; ++i){
        out << impl->figures[i].type;
        out << impl->figures[i].x;
        out << impl->figures[i].y;
        out << impl->figures[i].alive;
    }
    out << WhiteMove;
    out << indexMove;
    out << ThisGame.size();
    std::cout << ThisGame.size();
    for (int i = 0; i < ThisGame.size(); ++i){
        out << ThisGame[i].fromX;
        out << ThisGame[i].fromY;
        out << ThisGame[i].toX;
        out << ThisGame[i].toY;
        out << ThisGame[i].deadIndex;
    }
    FsavedGame.close();
}

QList<Figure> Logic::newGameFigures(){
    QList<Figure> NewGameFigures;
    Figure NewFigure;
    QFile FnewGame("src/NewGame");
    FnewGame.open(QFile::ReadOnly);
    QDataStream in(&FnewGame);
    for (int i = 0; i < 32; ++i){
        in >> NewFigure.type;
        in >> NewFigure.x;
        in >> NewFigure.y;
        in >> NewFigure.alive;
        NewGameFigures.append(NewFigure);
    }
    FnewGame.close();
    indexMove = 0;
    WhiteMove = true;
    while (ThisGame.size() != 0)
        ThisGame.removeAt(0);
    return NewGameFigures;
}

QList<Figure> Logic::loadGameFigures(){
    int SizeOfThisGame;
    std::cout << "01";
    QList<Figure> LoadGameFigures;
    Figure LoadFigure;
    FullMove thisMove;
    while (ThisGame.size() != 0)
        ThisGame.removeAt(0);
    std::cout << "02";
    QFile FloadGame("src/SavedGame");
    FloadGame.open(QFile::ReadOnly);
    QDataStream in(&FloadGame);
    for (int i = 0; i < 32; ++i){
        in >> LoadFigure.type;
        in >> LoadFigure.x;
        in >> LoadFigure.y;
        in >> LoadFigure.alive;
        LoadGameFigures.append(LoadFigure);
        std::cout << i;
    }
    in >> WhiteMove;
    in >> indexMove;
    in >> SizeOfThisGame;
    std::cout << SizeOfThisGame;
    for (int i = 0; i < SizeOfThisGame; ++i){
        in >> thisMove.fromX;
        in >> thisMove.fromY;
        in >> thisMove.toX;
        in >> thisMove.toY;
        in >> thisMove.deadIndex;
        ThisGame.append(thisMove);
        std::cout << i;
    }
    FloadGame.close();
    return LoadGameFigures;
}

bool Logic::move(int fromX, int fromY, int toX, int toY) {

    FullMove ThisMove;
    ThisMove.fromX = fromX;
    ThisMove.fromY = fromY;
    ThisMove.toX = toX;
    ThisMove.toY = toY;
    ThisMove.deadIndex = -1;

    int fromIndex = impl->findByPosition(fromX, fromY);
    int toIndex = impl->findByPosition(toX, toY);

    if ((fromIndex >= 0) && impl->figures[fromIndex].alive){
        if (((impl->figures[fromIndex].type % 2 == 0) && WhiteMove) || ((impl->figures[fromIndex].type % 2 == 1) && (!WhiteMove))){

            QList<Move> possibleMovesfromXfromY;
            possibleMovesfromXfromY = possibleMoves(fromX, fromY);

            for(int pmIndex = 0; pmIndex < possibleMovesfromXfromY.size(); ++pmIndex){
                if ((toX == possibleMovesfromXfromY[pmIndex].x) && (toY == possibleMovesfromXfromY[pmIndex].y)){
                    if (freeCell(toX, toY)){
                        impl->figures[fromIndex].x = toX;
                        impl->figures[fromIndex].y = toY;

                        QModelIndex topLeftFrom = createIndex(fromIndex, 0);
                        QModelIndex bottomRightFrom = createIndex(fromIndex, 0);
                        emit dataChanged(topLeftFrom, bottomRightFrom);

                        ThisGame.append(ThisMove);
                        WhiteMove = !WhiteMove;
                        indexMove++;
                        return true;
                    }
                    else if (enemies(fromX, fromY, toX, toY)){

                        impl->figures[toIndex].alive = false;
                        impl->figures[toIndex].x = 8;       /// temporary
                        impl->figures[toIndex].y = 8;       /// temporary
                        QModelIndex topLeftTo = createIndex(toIndex, 0);
                        QModelIndex bottomRightTo = createIndex(toIndex, 0);
                        emit dataChanged(topLeftTo, bottomRightTo);

                        impl->figures[fromIndex].x = toX;
                        impl->figures[fromIndex].y = toY;
                        QModelIndex topLeftFrom = createIndex(fromIndex, 0);
                        QModelIndex bottomRightFrom = createIndex(fromIndex, 0);
                        emit dataChanged(topLeftFrom, bottomRightFrom);

                        ThisMove.deadIndex = toIndex;
                        ThisGame.append(ThisMove);
                        WhiteMove = !WhiteMove;
                        indexMove++;
                        return true;

                    }
                }
            }
        }
    }
    impl->figures[fromIndex].x = fromX;
    impl->figures[fromIndex].y = fromY;
    QModelIndex topLeft = createIndex(fromIndex, 0);
    QModelIndex bottomRight = createIndex(fromIndex, 0);
    emit dataChanged(topLeft, bottomRight);
    return false;
}

int Logic::endGame(){
    if (!impl->figures[30].alive){
        WhiteMove = true;
        lastGameOut();
        return 2;
    }
    else if (!impl->figures[31].alive){
        WhiteMove = true;
        lastGameOut();
        return 1;
    }
    else
        return 0;
}

void Logic::lastGame(){
    ThisGame = lastGameIn();
    indexMove = 0;
}

QList<FullMove> Logic::lastGameIn(){
    QList<FullMove> LastGameIn;
    FullMove LastGameMove;
    QFile FlastGameIn("src/LastGame");
    FlastGameIn.open(QFile::ReadOnly);
    QDataStream in(&FlastGameIn);
    for (int i = 0; i < (FlastGameIn.size() / 20); ++i){
        in >> LastGameMove.fromX;
        in >> LastGameMove.fromY;
        in >> LastGameMove.toX;
        in >> LastGameMove.toY;
        in >> LastGameMove.deadIndex;
        LastGameIn.append(LastGameMove);
    }
    FlastGameIn.close();
    return LastGameIn;
}

void Logic::lastGameOut(){
    QFile FlastGameOut("src/LastGame");
    FlastGameOut.open(QFile::WriteOnly);
    QDataStream out(&FlastGameOut);
    for (int i = 0; i < ThisGame.size(); ++i){
        out << ThisGame[i].fromX;
        out << ThisGame[i].fromY;
        out << ThisGame[i].toX;
        out << ThisGame[i].toY;
        out << ThisGame[i].deadIndex;
    }
    FlastGameOut.close();
}

bool Logic::prevMove(){

    if (indexMove > 0){

        FullMove move = ThisGame[indexMove - 1];

        int toIndex = impl->findByPosition(move.toX, move.toY);

        impl->figures[toIndex].x = move.fromX;
        impl->figures[toIndex].y = move.fromY;
        QModelIndex topLeftFrom = createIndex(toIndex, 0);
        QModelIndex bottomRightFrom = createIndex(toIndex, 0);
        emit dataChanged(topLeftFrom, bottomRightFrom);

        if (move.deadIndex >= 0){
            impl->figures[move.deadIndex].alive = true;
            impl->figures[move.deadIndex].x = move.toX;       /// temporary
            impl->figures[move.deadIndex].y = move.toY;       /// temporary
            QModelIndex topLeftTo = createIndex(move.deadIndex, 0);
            QModelIndex bottomRightTo = createIndex(move.deadIndex, 0);
            emit dataChanged(topLeftTo, bottomRightTo);
        }

        indexMove--;
        return true;
    }
    return false;
}

bool Logic::nextMove(){

    if (indexMove < ThisGame.size()){

        FullMove move = ThisGame[indexMove];

        int fromIndex = impl->findByPosition(move.fromX, move.fromY);
        int toIndex = impl->findByPosition(move.toX, move.toY);

        if (move.deadIndex >= 0){
            impl->figures[toIndex].alive = false;
            impl->figures[toIndex].x = 8;       /// temporary
            impl->figures[toIndex].y = 8;       /// temporary
            QModelIndex topLeftTo = createIndex(toIndex, 0);
            QModelIndex bottomRightTo = createIndex(toIndex, 0);
            emit dataChanged(topLeftTo, bottomRightTo);
        }

        impl->figures[fromIndex].x = move.toX;
        impl->figures[fromIndex].y = move.toY;
        QModelIndex topLeftFrom = createIndex(fromIndex, 0);
        QModelIndex bottomRightFrom = createIndex(fromIndex, 0);
        emit dataChanged(topLeftFrom, bottomRightFrom);

        indexMove++;
        return true;
    }
    return false;
}

bool Logic::trueCell(int X, int Y){
    return ((X >= 0) && (X < BOARD_SIZE) && (Y >= 0) && (Y < BOARD_SIZE));
}

bool Logic::freeCell(int X, int Y){
    return (trueCell(X, Y) && (impl->findByPosition(X, Y) == -1));
}

bool Logic::enemies(int fromX, int fromY, int toX, int toY) {
    if ((impl->findByPosition(toX, toY) != -1) && (impl->findByPosition(fromX, fromY) != -1)){
        int fromIndex = impl->findByPosition(fromX, fromY);
        int fromType = impl->figures[fromIndex].type;
        int toIndex = impl->findByPosition(toX, toY);
        int toType = impl->figures[toIndex].type;
        return (((fromType % 2 == 1) && (toType % 2 == 0)) || ((fromType % 2 == 0) && (toType % 2 == 1)));
    }
    else
        return false;
}

bool Logic::alive(int X, int Y){
    int Index = impl->findByPosition(X, Y);
    return impl->figures[Index].alive;
}

QList<Move> Logic::possibleMoves(int fromX, int fromY) {

    int index = impl->findByPosition(fromX, fromY);
    int type = impl->figures[index].type;
    QList<Move> noMove;

    switch (type) {
    case 0: return possibleMovesPawnW(fromX, fromY);
        break;
    case 1: return possibleMovesPawnB(fromX, fromY);
        break;
    case 2: return possibleMovesRook(fromX, fromY);
        break;
    case 3: return possibleMovesRook(fromX, fromY);
        break;
    case 4: return possibleMovesKnight(fromX, fromY);
        break;
    case 5: return possibleMovesKnight(fromX, fromY);
        break;
    case 6: return possibleMovesBishop(fromX, fromY);
        break;
    case 7: return possibleMovesBishop(fromX, fromY);
        break;
    case 8: return possibleMovesQueen(fromX, fromY);
        break;
    case 9: return possibleMovesQueen(fromX, fromY);
        break;
    case 10: return possibleMovesKing(fromX, fromY);
        break;
    case 11: return possibleMovesKing(fromX, fromY);
        break;
    default: return noMove;
        break;
    }
}

QList<Move> Logic::possibleMovesPawnW(int fromX, int fromY){
    QList<Move> possibleMoves;
    Move tempMove;

    if (freeCell(fromX, fromY - 1)){
        tempMove.x = fromX;
        tempMove.y = fromY - 1;
        possibleMoves.append(tempMove);
        if ((fromY == BOARD_SIZE - 2) && freeCell(fromX, fromY - 2)){
            tempMove.x = fromX;
            tempMove.y = fromY - 2;
            possibleMoves.append(tempMove);
        }
    }

    if (enemies(fromX, fromY, fromX - 1, fromY - 1)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY - 1;
        possibleMoves.append(tempMove);
    }

    if (enemies(fromX, fromY, fromX + 1, fromY - 1)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY - 1;
        possibleMoves.append(tempMove);
    }

    return possibleMoves;
}

QList<Move> Logic::possibleMovesPawnB(int fromX, int fromY){
    QList<Move> possibleMoves;
    Move tempMove;

    if (freeCell(fromX, fromY + 1)){
        tempMove.x = fromX;
        tempMove.y = fromY + 1;
        possibleMoves.append(tempMove);
        if ((fromY == 1) && freeCell(fromX, fromY + 2)){
            tempMove.x = fromX;
            tempMove.y = fromY + 2;
            possibleMoves.append(tempMove);
        }
    }

    if (enemies(fromX, fromY, fromX - 1, fromY + 1)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY + 1;
        possibleMoves.append(tempMove);
    }

    if (enemies(fromX, fromY, fromX + 1, fromY + 1)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY + 1;
        possibleMoves.append(tempMove);
    }

    return possibleMoves;
}

QList<Move> Logic::possibleMovesRook(int fromX, int fromY){
    QList<Move> possibleMoves;
    Move tempMove;

    int i = 1;
    while (freeCell(fromX + i, fromY)){
        tempMove.x = fromX + i;
        tempMove.y = fromY;
        possibleMoves.append(tempMove);
        i++;
    }
    if (enemies(fromX, fromY, fromX + i,fromY)){
        tempMove.x = fromX + i;
        tempMove.y = fromY;
        possibleMoves.append(tempMove);
    }

    i = 1;
    while (freeCell(fromX - i, fromY)){
        tempMove.x = fromX - i;
        tempMove.y = fromY;
        possibleMoves.append(tempMove);
        i++;
    }
    if (enemies(fromX, fromY, fromX - i,fromY)){
        tempMove.x = fromX - i;
        tempMove.y = fromY;
        possibleMoves.append(tempMove);
    }

    i = 1;
    while (freeCell(fromX, fromY + i)){
        tempMove.x = fromX;
        tempMove.y = fromY + i;
        possibleMoves.append(tempMove);
        i++;
    }
    if (enemies(fromX, fromY, fromX,fromY + i)){
        tempMove.x = fromX;
        tempMove.y = fromY + i;
        possibleMoves.append(tempMove);
    }

    i = 1;
    while (freeCell(fromX, fromY - i)){
        tempMove.x = fromX;
        tempMove.y = fromY - i;
        possibleMoves.append(tempMove);
        i++;
    }
    if (enemies(fromX, fromY, fromX,fromY - i)){
        tempMove.x = fromX;
        tempMove.y = fromY - i;
        possibleMoves.append(tempMove);
    }

    return possibleMoves;
}

QList<Move> Logic::possibleMovesKnight(int fromX, int fromY){
    QList<Move> possibleMoves;
    Move tempMove;

    if (freeCell(fromX - 2, fromY - 1) || enemies(fromX, fromY, fromX - 2, fromY - 1)){
        tempMove.x = fromX - 2;
        tempMove.y = fromY - 1;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX - 2, fromY + 1) || enemies(fromX, fromY, fromX - 2, fromY + 1)){
        tempMove.x = fromX - 2;
        tempMove.y = fromY + 1;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX - 1, fromY - 2) || enemies(fromX, fromY, fromX - 1, fromY - 2)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY - 2;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX - 1, fromY + 2) || enemies(fromX, fromY, fromX - 1, fromY + 2)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY + 2;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX + 1, fromY - 2) || enemies(fromX, fromY, fromX + 1, fromY - 2)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY - 2;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX + 1, fromY + 2) || enemies(fromX, fromY, fromX + 1, fromY + 2)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY + 2;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX + 2, fromY - 1) || enemies(fromX, fromY, fromX + 2, fromY - 1)){
        tempMove.x = fromX + 2;
        tempMove.y = fromY - 1;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX + 2, fromY + 1) || enemies(fromX, fromY, fromX + 2, fromY + 1)){
        tempMove.x = fromX + 2;
        tempMove.y = fromY + 1;
        possibleMoves.append(tempMove);
    }

    return possibleMoves;
}

QList<Move> Logic::possibleMovesBishop(int fromX, int fromY){
    QList<Move> possibleMoves;
    Move tempMove;

    int i = 1;
    while (freeCell(fromX + i, fromY + i)){
        tempMove.x = fromX + i;
        tempMove.y = fromY + i;
        possibleMoves.append(tempMove);
        i++;
    }
    if (enemies(fromX, fromY, fromX + i,fromY + i)){
        tempMove.x = fromX + i;
        tempMove.y = fromY + i;
        possibleMoves.append(tempMove);
    }

    i = 1;
    while (freeCell(fromX - i, fromY - i)){
        tempMove.x = fromX - i;
        tempMove.y = fromY - i;
        possibleMoves.append(tempMove);
        i++;
    }
    if (enemies(fromX, fromY, fromX - i,fromY - i)){
        tempMove.x = fromX - i;
        tempMove.y = fromY - i;
        possibleMoves.append(tempMove);
    }

    i = 1;
    while (freeCell(fromX - i, fromY + i)){
        tempMove.x = fromX - i;
        tempMove.y = fromY + i;
        possibleMoves.append(tempMove);
        i++;
    }
    if (enemies(fromX, fromY, fromX - i,fromY + i)){
        tempMove.x = fromX - i;
        tempMove.y = fromY + i;
        possibleMoves.append(tempMove);
    }

    i = 1;
    while (freeCell(fromX + i, fromY - i)){
        tempMove.x = fromX + i;
        tempMove.y = fromY - i;
        possibleMoves.append(tempMove);
        i++;
    }
    if (enemies(fromX, fromY, fromX + i,fromY - i)){
        tempMove.x = fromX + i;
        tempMove.y = fromY - i;
        possibleMoves.append(tempMove);
    }

    return possibleMoves;
}

QList<Move> Logic::possibleMovesQueen(int fromX, int fromY){
    QList<Move> possibleMoves;

    possibleMoves = possibleMovesRook(fromX, fromY) + possibleMovesBishop(fromX, fromY);

    return possibleMoves;
}

QList<Move> Logic::possibleMovesKing(int fromX, int fromY){
    QList<Move> possibleMoves;
    Move tempMove;

    if (freeCell(fromX + 1, fromY + 1) || enemies(fromX, fromY, fromX + 1, fromY + 1)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY + 1;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX + 1, fromY) || enemies(fromX, fromY, fromX + 1, fromY)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX + 1, fromY - 1) || enemies(fromX, fromY, fromX + 1, fromY - 1)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY - 1;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX, fromY + 1) || enemies(fromX, fromY, fromX, fromY + 1)){
        tempMove.x = fromX;
        tempMove.y = fromY + 1;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX, fromY - 1) || enemies(fromX, fromY, fromX, fromY - 1)){
        tempMove.x = fromX;
        tempMove.y = fromY - 1;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX - 1, fromY + 1) || enemies(fromX, fromY, fromX - 1, fromY + 1)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY + 1;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX - 1, fromY) || enemies(fromX, fromY, fromX - 1, fromY)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY;
        possibleMoves.append(tempMove);
    }

    if (freeCell(fromX - 1, fromY - 1) || enemies(fromX, fromY, fromX - 1, fromY - 1)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY - 1;
        possibleMoves.append(tempMove);
    }

    return possibleMoves;
}

