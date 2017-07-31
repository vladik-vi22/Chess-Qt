#pragma once
#include <memory>
#include <QAbstractListModel>

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
};

class Logic: public QAbstractListModel
{
    Q_OBJECT
public:

    enum GlobalConstants {
        BOARD_SIZE = 8
    };

    enum Roles {
        Type = Qt::UserRole,
        PositionX,
        PositionY,
        Alive,
    };
    
public:
    explicit Logic(QObject *parent = 0);
    ~Logic();

    Q_PROPERTY(int boardSize READ boardSize CONSTANT);
    int boardSize() const;

    Q_INVOKABLE void clear();
    Q_INVOKABLE QList<Figure> newGameFigures();
    Q_INVOKABLE QList<Figure> loadGameFigures();
    Q_INVOKABLE void saveGame();
    Q_INVOKABLE bool move(int fromX, int fromY, int toX, int toY);
    Q_INVOKABLE bool trueCell(int X, int Y);
    Q_INVOKABLE bool freeCell(int X, int Y);
    Q_INVOKABLE bool enemies(int fromX, int fromY, int toX, int toY);
    Q_INVOKABLE bool alive(int X, int Y);
    Q_INVOKABLE QList<Move> possibleMoves(int fromX, int fromY);
    Q_INVOKABLE QList<Move> possibleMovesPawnW(int fromX, int fromY);
    Q_INVOKABLE QList<Move> possibleMovesPawnB(int fromX, int fromY);
    Q_INVOKABLE QList<Move> possibleMovesRook(int fromX, int fromY);
    Q_INVOKABLE QList<Move> possibleMovesKnight(int fromX, int fromY);
    Q_INVOKABLE QList<Move> possibleMovesBishop(int fromX, int fromY);
    Q_INVOKABLE QList<Move> possibleMovesQueen(int fromX, int fromY);
    Q_INVOKABLE QList<Move> possibleMovesKing(int fromX, int fromY);

protected:
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
