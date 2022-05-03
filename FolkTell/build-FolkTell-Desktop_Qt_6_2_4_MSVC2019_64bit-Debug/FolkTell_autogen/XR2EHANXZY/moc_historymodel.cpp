/****************************************************************************
** Meta object code from reading C++ file 'historymodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../FolkTell/src/history/historymodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'historymodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HistoryModel_t {
    const uint offsetsAndSize[34];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_HistoryModel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_HistoryModel_t qt_meta_stringdata_HistoryModel = {
    {
QT_MOC_LITERAL(0, 12), // "HistoryModel"
QT_MOC_LITERAL(13, 15), // "addHistoryEntry"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 13), // "HistoryEntry&"
QT_MOC_LITERAL(44, 12), // "historyEntry"
QT_MOC_LITERAL(57, 15), // "findHistoryItem"
QT_MOC_LITERAL(73, 12), // "HistoryItem*"
QT_MOC_LITERAL(86, 12), // "HistoryEntry"
QT_MOC_LITERAL(99, 18), // "deleteHistoryEntry"
QT_MOC_LITERAL(118, 8), // "dayIndex"
QT_MOC_LITERAL(127, 10), // "entryIndex"
QT_MOC_LITERAL(138, 17), // "clearHistoryEntry"
QT_MOC_LITERAL(156, 17), // "queryDayTimestamp"
QT_MOC_LITERAL(174, 13), // "QList<qint64>"
QT_MOC_LITERAL(188, 20), // "queryDayHistoryEntry"
QT_MOC_LITERAL(209, 19), // "QList<HistoryEntry>"
QT_MOC_LITERAL(229, 5) // "index"

    },
    "HistoryModel\0addHistoryEntry\0\0"
    "HistoryEntry&\0historyEntry\0findHistoryItem\0"
    "HistoryItem*\0HistoryEntry\0deleteHistoryEntry\0"
    "dayIndex\0entryIndex\0clearHistoryEntry\0"
    "queryDayTimestamp\0QList<qint64>\0"
    "queryDayHistoryEntry\0QList<HistoryEntry>\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HistoryModel[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x0a,    1 /* Public */,
       5,    1,   59,    2, 0x0a,    3 /* Public */,
       8,    1,   62,    2, 0x0a,    5 /* Public */,
       8,    2,   65,    2, 0x0a,    7 /* Public */,
      11,    0,   70,    2, 0x0a,   10 /* Public */,
      12,    0,   71,    2, 0x0a,   11 /* Public */,
      14,    1,   72,    2, 0x0a,   12 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    0x80000000 | 6, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void,
    0x80000000 | 13,
    0x80000000 | 15, QMetaType::Int,   16,

       0        // eod
};

void HistoryModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HistoryModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addHistoryEntry((*reinterpret_cast< std::add_pointer_t<HistoryEntry&>>(_a[1]))); break;
        case 1: { HistoryItem* _r = _t->findHistoryItem((*reinterpret_cast< std::add_pointer_t<HistoryEntry>>(_a[1])));
            if (_a[0]) *reinterpret_cast< HistoryItem**>(_a[0]) = std::move(_r); }  break;
        case 2: _t->deleteHistoryEntry((*reinterpret_cast< std::add_pointer_t<HistoryEntry&>>(_a[1]))); break;
        case 3: _t->deleteHistoryEntry((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->clearHistoryEntry(); break;
        case 5: { QList<qint64> _r = _t->queryDayTimestamp();
            if (_a[0]) *reinterpret_cast< QList<qint64>*>(_a[0]) = std::move(_r); }  break;
        case 6: { QList<HistoryEntry> _r = _t->queryDayHistoryEntry((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<HistoryEntry>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject HistoryModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QStandardItemModel::staticMetaObject>(),
    qt_meta_stringdata_HistoryModel.offsetsAndSize,
    qt_meta_data_HistoryModel,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_HistoryModel_t
, QtPrivate::TypeAndForceComplete<HistoryModel, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<HistoryEntry &, std::false_type>, QtPrivate::TypeAndForceComplete<HistoryItem *, std::false_type>, QtPrivate::TypeAndForceComplete<const HistoryEntry &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<HistoryEntry &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QList<qint64>, std::false_type>, QtPrivate::TypeAndForceComplete<QList<HistoryEntry>, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>


>,
    nullptr
} };


const QMetaObject *HistoryModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HistoryModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HistoryModel.stringdata0))
        return static_cast<void*>(this);
    return QStandardItemModel::qt_metacast(_clname);
}

int HistoryModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStandardItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
