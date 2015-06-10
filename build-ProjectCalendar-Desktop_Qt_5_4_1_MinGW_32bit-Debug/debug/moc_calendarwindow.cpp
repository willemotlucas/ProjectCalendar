/****************************************************************************
** Meta object code from reading C++ file 'calendarwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../calendarwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calendarwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CalendarWindow_t {
    QByteArrayData data[11];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalendarWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalendarWindow_t qt_meta_stringdata_CalendarWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CalendarWindow"
QT_MOC_LITERAL(1, 15, 17), // "changeCurrentWeek"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 6), // "QDate*"
QT_MOC_LITERAL(4, 41, 4), // "date"
QT_MOC_LITERAL(5, 46, 12), // "isCurrentDay"
QT_MOC_LITERAL(6, 59, 8), // "nextWeek"
QT_MOC_LITERAL(7, 68, 8), // "prevWeek"
QT_MOC_LITERAL(8, 77, 7), // "setWeek"
QT_MOC_LITERAL(9, 85, 3), // "num"
QT_MOC_LITERAL(10, 89, 15) // "openQFileDialog"

    },
    "CalendarWindow\0changeCurrentWeek\0\0"
    "QDate*\0date\0isCurrentDay\0nextWeek\0"
    "prevWeek\0setWeek\0num\0openQFileDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalendarWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,
       8,    1,   46,    2, 0x08 /* Private */,
      10,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

       0        // eod
};

void CalendarWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalendarWindow *_t = static_cast<CalendarWindow *>(_o);
        switch (_id) {
        case 0: _t->changeCurrentWeek((*reinterpret_cast< QDate*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->nextWeek(); break;
        case 2: _t->prevWeek(); break;
        case 3: _t->setWeek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->openQFileDialog(); break;
        default: ;
        }
    }
}

const QMetaObject CalendarWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CalendarWindow.data,
      qt_meta_data_CalendarWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CalendarWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalendarWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CalendarWindow.stringdata))
        return static_cast<void*>(const_cast< CalendarWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CalendarWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
