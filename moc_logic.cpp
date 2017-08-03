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
    QByteArrayData data[24];
    char stringdata0[193];
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
QT_MOC_LITERAL(3, 13, 7), // "newGame"
QT_MOC_LITERAL(4, 21, 8), // "loadGame"
QT_MOC_LITERAL(5, 30, 8), // "saveGame"
QT_MOC_LITERAL(6, 39, 8), // "lastGame"
QT_MOC_LITERAL(7, 48, 7), // "endGame"
QT_MOC_LITERAL(8, 56, 4), // "move"
QT_MOC_LITERAL(9, 61, 5), // "fromX"
QT_MOC_LITERAL(10, 67, 5), // "fromY"
QT_MOC_LITERAL(11, 73, 3), // "toX"
QT_MOC_LITERAL(12, 77, 3), // "toY"
QT_MOC_LITERAL(13, 81, 8), // "prevMove"
QT_MOC_LITERAL(14, 90, 8), // "nextMove"
QT_MOC_LITERAL(15, 99, 18), // "lastEnablePrevMove"
QT_MOC_LITERAL(16, 118, 18), // "lastEnableNextMove"
QT_MOC_LITERAL(17, 137, 9), // "whiteMove"
QT_MOC_LITERAL(18, 147, 5), // "alive"
QT_MOC_LITERAL(19, 153, 1), // "X"
QT_MOC_LITERAL(20, 155, 1), // "Y"
QT_MOC_LITERAL(21, 157, 13), // "possibleMoves"
QT_MOC_LITERAL(22, 171, 11), // "QList<Move>"
QT_MOC_LITERAL(23, 183, 9) // "boardSize"

    },
    "Logic\0clear\0\0newGame\0loadGame\0saveGame\0"
    "lastGame\0endGame\0move\0fromX\0fromY\0toX\0"
    "toY\0prevMove\0nextMove\0lastEnablePrevMove\0"
    "lastEnableNextMove\0whiteMove\0alive\0X\0"
    "Y\0possibleMoves\0QList<Move>\0boardSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Logic[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       1,  114, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x02 /* Public */,
       3,    0,   85,    2, 0x02 /* Public */,
       4,    0,   86,    2, 0x02 /* Public */,
       5,    0,   87,    2, 0x02 /* Public */,
       6,    0,   88,    2, 0x02 /* Public */,
       7,    0,   89,    2, 0x02 /* Public */,
       8,    4,   90,    2, 0x02 /* Public */,
      13,    0,   99,    2, 0x02 /* Public */,
      14,    0,  100,    2, 0x02 /* Public */,
      15,    0,  101,    2, 0x02 /* Public */,
      16,    0,  102,    2, 0x02 /* Public */,
      17,    0,  103,    2, 0x02 /* Public */,
      18,    2,  104,    2, 0x02 /* Public */,
      21,    2,  109,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,   12,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   19,   20,
    0x80000000 | 22, QMetaType::Int, QMetaType::Int,    9,   10,

 // properties: name, type, flags
      23, QMetaType::Int, 0x00095401,

       0        // eod
};

void Logic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Logic *_t = static_cast<Logic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clear(); break;
        case 1: _t->newGame(); break;
        case 2: _t->loadGame(); break;
        case 3: _t->saveGame(); break;
        case 4: _t->lastGame(); break;
        case 5: { int _r = _t->endGame();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->prevMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->nextMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->lastEnablePrevMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->lastEnableNextMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->whiteMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->alive((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { QList<Move> _r = _t->possibleMoves((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
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
