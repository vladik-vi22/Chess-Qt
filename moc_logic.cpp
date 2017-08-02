/****************************************************************************
** Meta object code from reading C++ file 'logic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/logic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Logic_t {
    QByteArrayData data[35];
    char stringdata0[333];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Logic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Logic_t qt_meta_stringdata_Logic = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Logic"
QT_MOC_LITERAL(1, 6, 5), // "clear"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 14), // "newGameFigures"
QT_MOC_LITERAL(4, 28, 13), // "QList<Figure>"
QT_MOC_LITERAL(5, 42, 15), // "loadGameFigures"
QT_MOC_LITERAL(6, 58, 10), // "lastGameIn"
QT_MOC_LITERAL(7, 69, 15), // "QList<FullMove>"
QT_MOC_LITERAL(8, 85, 7), // "newGame"
QT_MOC_LITERAL(9, 93, 8), // "loadGame"
QT_MOC_LITERAL(10, 102, 8), // "saveGame"
QT_MOC_LITERAL(11, 111, 11), // "lastGameOut"
QT_MOC_LITERAL(12, 123, 8), // "lastGame"
QT_MOC_LITERAL(13, 132, 7), // "endGame"
QT_MOC_LITERAL(14, 140, 4), // "move"
QT_MOC_LITERAL(15, 145, 5), // "fromX"
QT_MOC_LITERAL(16, 151, 5), // "fromY"
QT_MOC_LITERAL(17, 157, 3), // "toX"
QT_MOC_LITERAL(18, 161, 3), // "toY"
QT_MOC_LITERAL(19, 165, 8), // "prevMove"
QT_MOC_LITERAL(20, 174, 8), // "nextMove"
QT_MOC_LITERAL(21, 183, 14), // "enablePrevMove"
QT_MOC_LITERAL(22, 198, 14), // "enableNextMove"
QT_MOC_LITERAL(23, 213, 18), // "lastEnablePrevMove"
QT_MOC_LITERAL(24, 232, 18), // "lastEnableNextMove"
QT_MOC_LITERAL(25, 251, 9), // "whiteMove"
QT_MOC_LITERAL(26, 261, 8), // "trueCell"
QT_MOC_LITERAL(27, 270, 1), // "X"
QT_MOC_LITERAL(28, 272, 1), // "Y"
QT_MOC_LITERAL(29, 274, 8), // "freeCell"
QT_MOC_LITERAL(30, 283, 7), // "enemies"
QT_MOC_LITERAL(31, 291, 5), // "alive"
QT_MOC_LITERAL(32, 297, 13), // "possibleMoves"
QT_MOC_LITERAL(33, 311, 11), // "QList<Move>"
QT_MOC_LITERAL(34, 323, 9) // "boardSize"

    },
    "Logic\0clear\0\0newGameFigures\0QList<Figure>\0"
    "loadGameFigures\0lastGameIn\0QList<FullMove>\0"
    "newGame\0loadGame\0saveGame\0lastGameOut\0"
    "lastGame\0endGame\0move\0fromX\0fromY\0toX\0"
    "toY\0prevMove\0nextMove\0enablePrevMove\0"
    "enableNextMove\0lastEnablePrevMove\0"
    "lastEnableNextMove\0whiteMove\0trueCell\0"
    "X\0Y\0freeCell\0enemies\0alive\0possibleMoves\0"
    "QList<Move>\0boardSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Logic[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       1,  184, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,  129,    2, 0x02 /* Public */,
       3,    0,  130,    2, 0x02 /* Public */,
       5,    0,  131,    2, 0x02 /* Public */,
       6,    0,  132,    2, 0x02 /* Public */,
       8,    0,  133,    2, 0x02 /* Public */,
       9,    0,  134,    2, 0x02 /* Public */,
      10,    0,  135,    2, 0x02 /* Public */,
      11,    0,  136,    2, 0x02 /* Public */,
      12,    0,  137,    2, 0x02 /* Public */,
      13,    0,  138,    2, 0x02 /* Public */,
      14,    4,  139,    2, 0x02 /* Public */,
      19,    0,  148,    2, 0x02 /* Public */,
      20,    0,  149,    2, 0x02 /* Public */,
      21,    0,  150,    2, 0x02 /* Public */,
      22,    0,  151,    2, 0x02 /* Public */,
      23,    0,  152,    2, 0x02 /* Public */,
      24,    0,  153,    2, 0x02 /* Public */,
      25,    0,  154,    2, 0x02 /* Public */,
      26,    2,  155,    2, 0x02 /* Public */,
      29,    2,  160,    2, 0x02 /* Public */,
      30,    4,  165,    2, 0x02 /* Public */,
      31,    2,  174,    2, 0x02 /* Public */,
      32,    2,  179,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void,
    0x80000000 | 4,
    0x80000000 | 4,
    0x80000000 | 7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   15,   16,   17,   18,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   27,   28,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   27,   28,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   15,   16,   17,   18,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   27,   28,
    0x80000000 | 33, QMetaType::Int, QMetaType::Int,   15,   16,

 // properties: name, type, flags
      34, QMetaType::Int, 0x00095401,

       0        // eod
};

void Logic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Logic *_t = static_cast<Logic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clear(); break;
        case 1: { QList<Figure> _r = _t->newGameFigures();
            if (_a[0]) *reinterpret_cast< QList<Figure>*>(_a[0]) = _r; }  break;
        case 2: { QList<Figure> _r = _t->loadGameFigures();
            if (_a[0]) *reinterpret_cast< QList<Figure>*>(_a[0]) = _r; }  break;
        case 3: { QList<FullMove> _r = _t->lastGameIn();
            if (_a[0]) *reinterpret_cast< QList<FullMove>*>(_a[0]) = _r; }  break;
        case 4: _t->newGame(); break;
        case 5: _t->loadGame(); break;
        case 6: _t->saveGame(); break;
        case 7: _t->lastGameOut(); break;
        case 8: _t->lastGame(); break;
        case 9: { int _r = _t->endGame();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->prevMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->nextMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->enablePrevMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->enableNextMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = _t->lastEnablePrevMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: { bool _r = _t->lastEnableNextMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 17: { bool _r = _t->whiteMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: { bool _r = _t->trueCell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: { bool _r = _t->freeCell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 20: { bool _r = _t->enemies((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 21: { bool _r = _t->alive((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 22: { QList<Move> _r = _t->possibleMoves((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QList<Move>*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Logic *_t = static_cast<Logic *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->boardSize(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject Logic::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_Logic.data,
      qt_meta_data_Logic,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Logic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Logic::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Logic.stringdata0))
        return static_cast<void*>(const_cast< Logic*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int Logic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
