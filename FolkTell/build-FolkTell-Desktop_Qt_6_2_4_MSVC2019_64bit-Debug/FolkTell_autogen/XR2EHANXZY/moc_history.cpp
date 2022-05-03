/****************************************************************************
** Meta object code from reading C++ file 'history.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../FolkTell/src/history/history.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'history.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_History_t {
    const uint offsetsAndSize[52];
    char stringdata0[344];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_History_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_History_t qt_meta_stringdata_History = {
    {
QT_MOC_LITERAL(0, 7), // "History"
QT_MOC_LITERAL(8, 17), // "historyEntryAdded"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 13), // "HistoryEntry&"
QT_MOC_LITERAL(41, 12), // "historyEntry"
QT_MOC_LITERAL(54, 19), // "historyEntryDeleted"
QT_MOC_LITERAL(74, 19), // "historyEntryCleared"
QT_MOC_LITERAL(94, 15), // "addHistoryEntry"
QT_MOC_LITERAL(110, 8), // "WebView*"
QT_MOC_LITERAL(119, 7), // "webview"
QT_MOC_LITERAL(127, 16), // "makeHistoryEntry"
QT_MOC_LITERAL(144, 12), // "HistoryEntry"
QT_MOC_LITERAL(157, 5), // "title"
QT_MOC_LITERAL(163, 3), // "url"
QT_MOC_LITERAL(167, 7), // "iconUrl"
QT_MOC_LITERAL(175, 19), // "addHistoryEntryHelp"
QT_MOC_LITERAL(195, 22), // "deleteHistoryEntryHelp"
QT_MOC_LITERAL(218, 4), // "date"
QT_MOC_LITERAL(223, 8), // "dayIndex"
QT_MOC_LITERAL(232, 10), // "entryIndex"
QT_MOC_LITERAL(243, 21), // "clearHistoryEntryHelp"
QT_MOC_LITERAL(265, 17), // "queryDayTimestamp"
QT_MOC_LITERAL(283, 13), // "QList<qint64>"
QT_MOC_LITERAL(297, 20), // "queryDayHistoryEntry"
QT_MOC_LITERAL(318, 19), // "QList<HistoryEntry>"
QT_MOC_LITERAL(338, 5) // "index"

    },
    "History\0historyEntryAdded\0\0HistoryEntry&\0"
    "historyEntry\0historyEntryDeleted\0"
    "historyEntryCleared\0addHistoryEntry\0"
    "WebView*\0webview\0makeHistoryEntry\0"
    "HistoryEntry\0title\0url\0iconUrl\0"
    "addHistoryEntryHelp\0deleteHistoryEntryHelp\0"
    "date\0dayIndex\0entryIndex\0clearHistoryEntryHelp\0"
    "queryDayTimestamp\0QList<qint64>\0"
    "queryDayHistoryEntry\0QList<HistoryEntry>\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_History[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,
       5,    1,   83,    2, 0x06,    3 /* Public */,
       6,    0,   86,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   87,    2, 0x0a,    6 /* Public */,
      10,    3,   90,    2, 0x0a,    8 /* Public */,
      15,    3,   97,    2, 0x0a,   12 /* Public */,
      16,    4,  104,    2, 0x0a,   16 /* Public */,
      16,    2,  113,    2, 0x0a,   21 /* Public */,
      20,    0,  118,    2, 0x0a,   24 /* Public */,
      21,    0,  119,    2, 0x0a,   25 /* Public */,
      23,    1,  120,    2, 0x0a,   26 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    0x80000000 | 11, QMetaType::QString, QMetaType::QUrl, QMetaType::QUrl,   12,   13,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QUrl, QMetaType::QUrl,   12,   13,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QUrl, QMetaType::QUrl, QMetaType::QDateTime,   12,   13,   14,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,
    QMetaType::Void,
    0x80000000 | 22,
    0x80000000 | 24, QMetaType::Int,   25,

       0        // eod
};

void History::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<History *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->historyEntryAdded((*reinterpret_cast< std::add_pointer_t<HistoryEntry&>>(_a[1]))); break;
        case 1: _t->historyEntryDeleted((*reinterpret_cast< std::add_pointer_t<HistoryEntry&>>(_a[1]))); break;
        case 2: _t->historyEntryCleared(); break;
        case 3: _t->addHistoryEntry((*reinterpret_cast< std::add_pointer_t<WebView*>>(_a[1]))); break;
        case 4: { HistoryEntry _r = _t->makeHistoryEntry((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[3])));
            if (_a[0]) *reinterpret_cast< HistoryEntry*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->addHistoryEntryHelp((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[3]))); break;
        case 6: _t->deleteHistoryEntryHelp((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[4]))); break;
        case 7: _t->deleteHistoryEntryHelp((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 8: _t->clearHistoryEntryHelp(); break;
        case 9: { QList<qint64> _r = _t->queryDayTimestamp();
            if (_a[0]) *reinterpret_cast< QList<qint64>*>(_a[0]) = std::move(_r); }  break;
        case 10: { QList<HistoryEntry> _r = _t->queryDayHistoryEntry((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<HistoryEntry>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< WebView* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (History::*)(HistoryEntry & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&History::historyEntryAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (History::*)(HistoryEntry & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&History::historyEntryDeleted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (History::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&History::historyEntryCleared)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject History::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_History.offsetsAndSize,
    qt_meta_data_History,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_History_t
, QtPrivate::TypeAndForceComplete<History, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<HistoryEntry &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<HistoryEntry &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<WebView *, std::false_type>, QtPrivate::TypeAndForceComplete<HistoryEntry, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>, QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>, QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>, QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>, QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QList<qint64>, std::false_type>, QtPrivate::TypeAndForceComplete<QList<HistoryEntry>, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>


>,
    nullptr
} };


const QMetaObject *History::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *History::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_History.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int History::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void History::historyEntryAdded(HistoryEntry & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void History::historyEntryDeleted(HistoryEntry & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void History::historyEntryCleared()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
