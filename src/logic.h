#pragma once
#include <memory>
#include <QAbstractListModel>
#include <QList>
#include <QByteArray>
#include <QHash>
#include <QFile>
#include <QDir>
#include <QDataStream>
#include <iostream>

struct Move
{
    int x;
    int y;
};

struct Figure
{
    int type;
    int x;
    int y;
    bool alive;
};

struct FullMove
{
    int fromX;
    int fromY;
    int toX;
    int toY;
    int deadIndex;
};

class Logic: public QAbstractListModel
{
    Q_OBJECT
public:

    enum GlobalConstants {
        BOARD_SIZE = 8,
        NUMBER_OF_FIGURES = 32,
        INDEX_OF_WHITE_KING = 30,
        INDEX_OF_BLACK_KING = 31,
        XY_OUT_OF_DESK = 8
    };

    enum Roles {
        Type = Qt::UserRole,
        PositionX,
        PositionY,
        Alive
    };

    int indexMove = 0;
    bool WhiteMove = true;
    QList<FullMove> ThisGame;
    QList<Figure> GameFigures = newGameFigures();
    
public:
    explicit Logic(QObject *parent = 0);
    ~Logic();

    Q_PROPERTY(int boardSize READ boardSize CONSTANT)
    int boardSize() const;

    Q_INVOKABLE void clear();
    Q_INVOKABLE void newGame();
    Q_INVOKABLE void loadGame();
    Q_INVOKABLE void saveGame();
    Q_INVOKABLE void lastGame();
    Q_INVOKABLE int endGame();
    Q_INVOKABLE bool move(int fromX, int fromY, int toX, int toY);
    Q_INVOKABLE bool prevMove();
    Q_INVOKABLE bool nextMove();
    Q_INVOKABLE bool lastEnablePrevMove();
    Q_INVOKABLE bool lastEnableNextMove();
    Q_INVOKABLE bool whiteMove();
    Q_INVOKABLE bool alive(int X, int Y);
    Q_INVOKABLE QList<Move> possibleMoves(int fromX, int fromY);
protected:
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
    QList<Figure> newGameFigures();
    QList<Figure> loadGameFigures();
    QList<FullMove> lastGameIn();
    void lastGameOut();
    bool enablePrevMove();
    bool enableNextMove();
    bool trueCell(int X, int Y);
    bool freeCell(int X, int Y);
    bool enemies(int fromX, int fromY, int toX, int toY);
    QList<Move> possibleMovesPawnW(int fromX, int fromY);
    QList<Move> possibleMovesPawnB(int fromX, int fromY);
    QList<Move> possibleMovesRook(int fromX, int fromY);
    QList<Move> possibleMovesKnight(int fromX, int fromY);
    QList<Move> possibleMovesBishop(int fromX, int fromY);
    QList<Move> possibleMovesQueen(int fromX, int fromY);
    QList<Move> possibleMovesKing(int fromX, int fromY);
};
