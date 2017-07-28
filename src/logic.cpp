#include "logic.h"
#include <QList>
#include <QByteArray>
#include <QHash>
#include <iostream>

struct Figure
{
  int type;
  int x;
  int y;
};

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
  impl->figures << Figure { 0, 0, 6 };
  impl->figures << Figure { 0, 1, 6 };
  impl->figures << Figure { 0, 2, 6 };
  impl->figures << Figure { 0, 3, 6 };
  impl->figures << Figure { 0, 4, 6 };
  impl->figures << Figure { 0, 5, 6 };
  impl->figures << Figure { 0, 6, 6 };
  impl->figures << Figure { 0, 7, 6 };
  impl->figures << Figure { 1, 0, 1 };
  impl->figures << Figure { 1, 1, 1 };
  impl->figures << Figure { 1, 2, 1 };
  impl->figures << Figure { 1, 3, 1 };
  impl->figures << Figure { 1, 4, 1 };
  impl->figures << Figure { 1, 5, 1 };
  impl->figures << Figure { 1, 6, 1 };
  impl->figures << Figure { 1, 7, 1 };
  impl->figures << Figure { 2, 0, 7 };
  impl->figures << Figure { 2, 7, 7 };
  impl->figures << Figure { 3, 0, 0 };
  impl->figures << Figure { 3, 7, 0 };
  impl->figures << Figure { 4, 1, 7 };
  impl->figures << Figure { 4, 6, 7 };
  impl->figures << Figure { 5, 1, 0 };
  impl->figures << Figure { 5, 6, 0 };
  impl->figures << Figure { 6, 2, 7 };
  impl->figures << Figure { 6, 5, 7 };
  impl->figures << Figure { 7, 2, 0 };
  impl->figures << Figure { 7, 5, 0 };
  impl->figures << Figure { 8, 3, 7 };
  impl->figures << Figure { 9, 3, 0 };
  impl->figures << Figure { 10, 4, 7 };
  impl->figures << Figure { 11, 4, 0 };
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
  }
  return QVariant(); 
}

void Logic::clear() {
  beginResetModel();
  impl->figures.clear();
  endResetModel();
}

bool Logic::move(int fromX, int fromY, int toX, int toY) {

    int index = impl->findByPosition(fromX, fromY);
    QList<Move> possibleMovesfromXfromY;
    possibleMovesfromXfromY = possibleMoves(fromX, fromY);

    for(int pmIndex = 0; pmIndex < possibleMovesfromXfromY.size(); ++pmIndex){
        if ((index >= 0) && (toX == possibleMovesfromXfromY[pmIndex].x) && (toY == possibleMovesfromXfromY[pmIndex].y)){
            impl->figures[index].x = toX;
            impl->figures[index].y = toY;
            if (enemies(fromX, fromY, toX, toY)){
                int enemyIndex = impl->findByPosition(toX, toY);
                impl->figures.removeAt(enemyIndex);
            }
            QModelIndex topLeft = createIndex(index, 0);
            QModelIndex bottomRight = createIndex(index, 0);
            emit dataChanged(topLeft, bottomRight);
            return true;
        }
    }

    return false;



/*  int index = impl->findByPosition(fromX, fromY);

  if (index < 0) return false;
  
  if (toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE || impl->findByPosition(toX, toY) >= 0) {
    return false;
  }
  impl->figures[index].x = toX;
  impl->figures[index].y = toY;
  QModelIndex topLeft = createIndex(index, 0);
  QModelIndex bottomRight = createIndex(index, 0);
  emit dataChanged(topLeft, bottomRight);
  return true;*/
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
        possibleMoves << tempMove;
        if ((fromY == BOARD_SIZE - 2) && freeCell(fromX, fromY - 2)){
            tempMove.x = fromX;
            tempMove.y = fromY - 2;
            possibleMoves << tempMove;
        }
    }

    if (enemies(fromX, fromY, fromX - 1, fromY - 1)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY - 1;
        possibleMoves << tempMove;
    }

    if (enemies(fromX, fromY, fromX + 1, fromY - 1)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY - 1;
        possibleMoves << tempMove;
    }

    return possibleMoves;
}

QList<Move> Logic::possibleMovesPawnB(int fromX, int fromY){
    QList<Move> possibleMoves;
    Move tempMove;

    if (freeCell(fromX, fromY + 1)){
        tempMove.x = fromX;
        tempMove.y = fromY + 1;
        possibleMoves << tempMove;
        if ((fromY == 1) && freeCell(fromX, fromY + 2)){
            tempMove.x = fromX;
            tempMove.y = fromY + 2;
            possibleMoves << tempMove;
        }
    }

    if (enemies(fromX, fromY, fromX - 1, fromY + 1)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY + 1;
        possibleMoves << tempMove;
    }

    if (enemies(fromX, fromY, fromX + 1, fromY + 1)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY + 1;
        possibleMoves << tempMove;
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
        possibleMoves << tempMove;
        i++;
    }
    if (enemies(fromX, fromY, fromX + i,fromY)){
        tempMove.x = fromX + i;
        tempMove.y = fromY;
        possibleMoves << tempMove;
    }

    i = 1;
    while (freeCell(fromX - i, fromY)){
        tempMove.x = fromX - i;
        tempMove.y = fromY;
        possibleMoves << tempMove;
        i++;
    }
    if (enemies(fromX, fromY, fromX - i,fromY)){
        tempMove.x = fromX - i;
        tempMove.y = fromY;
        possibleMoves << tempMove;
    }

    i = 1;
    while (freeCell(fromX, fromY + i)){
        tempMove.x = fromX;
        tempMove.y = fromY + i;
        possibleMoves << tempMove;
        i++;
    }
    if (enemies(fromX, fromY, fromX,fromY + i)){
        tempMove.x = fromX;
        tempMove.y = fromY + i;
        possibleMoves << tempMove;
    }

    i = 1;
    while (freeCell(fromX, fromY - i)){
        tempMove.x = fromX;
        tempMove.y = fromY - i;
        possibleMoves << tempMove;
        i++;
    }
    if (enemies(fromX, fromY, fromX,fromY - i)){
        tempMove.x = fromX;
        tempMove.y = fromY - i;
        possibleMoves << tempMove;
    }

    return possibleMoves;
}

QList<Move> Logic::possibleMovesKnight(int fromX, int fromY){
    QList<Move> possibleMoves;
    Move tempMove;

    if (freeCell(fromX - 2, fromY - 1) || enemies(fromX, fromY, fromX - 2, fromY - 1)){
        tempMove.x = fromX - 2;
        tempMove.y = fromY - 1;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX - 2, fromY + 1) || enemies(fromX, fromY, fromX - 2, fromY + 1)){
        tempMove.x = fromX - 2;
        tempMove.y = fromY + 1;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX - 1, fromY - 2) || enemies(fromX, fromY, fromX - 1, fromY - 2)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY - 2;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX - 1, fromY + 2) || enemies(fromX, fromY, fromX - 1, fromY + 2)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY + 2;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX + 1, fromY - 2) || enemies(fromX, fromY, fromX + 1, fromY - 2)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY - 2;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX + 1, fromY + 2) || enemies(fromX, fromY, fromX + 1, fromY + 2)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY + 2;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX + 2, fromY - 1) || enemies(fromX, fromY, fromX + 2, fromY - 1)){
        tempMove.x = fromX + 2;
        tempMove.y = fromY - 1;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX + 2, fromY + 1) || enemies(fromX, fromY, fromX + 2, fromY + 1)){
        tempMove.x = fromX + 2;
        tempMove.y = fromY + 1;
        possibleMoves << tempMove;
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
        possibleMoves << tempMove;
        i++;
    }
    if (enemies(fromX, fromY, fromX + i,fromY + i)){
        tempMove.x = fromX + i;
        tempMove.y = fromY + i;
        possibleMoves << tempMove;
    }

    i = 1;
    while (freeCell(fromX - i, fromY - i)){
        tempMove.x = fromX - i;
        tempMove.y = fromY - i;
        possibleMoves << tempMove;
        i++;
    }
    if (enemies(fromX, fromY, fromX - i,fromY - i)){
        tempMove.x = fromX - i;
        tempMove.y = fromY - i;
        possibleMoves << tempMove;
    }

    i = 1;
    while (freeCell(fromX - i, fromY + i)){
        tempMove.x = fromX - i;
        tempMove.y = fromY + i;
        possibleMoves << tempMove;
        i++;
    }
    if (enemies(fromX, fromY, fromX - i,fromY + i)){
        tempMove.x = fromX - i;
        tempMove.y = fromY + i;
        possibleMoves << tempMove;
    }

    i = 1;
    while (freeCell(fromX + i, fromY - i)){
        tempMove.x = fromX + i;
        tempMove.y = fromY - i;
        possibleMoves << tempMove;
        i++;
    }
    if (enemies(fromX, fromY, fromX + i,fromY - i)){
        tempMove.x = fromX + i;
        tempMove.y = fromY - i;
        possibleMoves << tempMove;
    }

    return possibleMoves;
}

QList<Move> Logic::possibleMovesQueen(int fromX, int fromY){
    QList<Move> possibleMoves;

    possibleMoves.append(possibleMovesRook(fromX, fromY));
    possibleMoves.append(possibleMovesBishop(fromX, fromY));

    return possibleMoves;
}

QList<Move> Logic::possibleMovesKing(int fromX, int fromY){
    QList<Move> possibleMoves;
    Move tempMove;

    if (freeCell(fromX + 1, fromY + 1) || enemies(fromX, fromY, fromX + 1, fromY + 1)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY + 1;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX + 1, fromY) || enemies(fromX, fromY, fromX + 1, fromY)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX + 1, fromY - 1) || enemies(fromX, fromY, fromX + 1, fromY - 1)){
        tempMove.x = fromX + 1;
        tempMove.y = fromY - 1;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX, fromY + 1) || enemies(fromX, fromY, fromX, fromY + 1)){
        tempMove.x = fromX;
        tempMove.y = fromY + 1;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX, fromY - 1) || enemies(fromX, fromY, fromX, fromY - 1)){
        tempMove.x = fromX;
        tempMove.y = fromY - 1;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX - 1, fromY + 1) || enemies(fromX, fromY, fromX - 1, fromY + 1)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY + 1;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX - 1, fromY) || enemies(fromX, fromY, fromX - 1, fromY)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY;
        possibleMoves << tempMove;
    }

    if (freeCell(fromX - 1, fromY - 1) || enemies(fromX, fromY, fromX - 1, fromY - 1)){
        tempMove.x = fromX - 1;
        tempMove.y = fromY - 1;
        possibleMoves << tempMove;
    }

    return possibleMoves;
}

