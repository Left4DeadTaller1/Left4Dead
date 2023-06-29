/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../client/menuQT/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "exitApp"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "exitCode"
QT_MOC_LITERAL(4, 29, 19), // "createButtonClicked"
QT_MOC_LITERAL(5, 49, 17), // "joinButtonClicked"
QT_MOC_LITERAL(6, 67, 13), // "sliderChanged"
QT_MOC_LITERAL(7, 81, 5), // "value"
QT_MOC_LITERAL(8, 87, 18), // "handleCreateClosed"
QT_MOC_LITERAL(9, 106, 4), // "code"
QT_MOC_LITERAL(10, 111, 16), // "handleJoinClosed"
QT_MOC_LITERAL(11, 128, 15), // "StringToTypeMap"
QT_MOC_LITERAL(12, 144, 9), // "TypeMap_t"
QT_MOC_LITERAL(13, 154, 11), // "std::string"
QT_MOC_LITERAL(14, 166, 3), // "map"
QT_MOC_LITERAL(15, 170, 18), // "StringToTypeWeapon"
QT_MOC_LITERAL(16, 189, 12), // "TypeWeapon_t"
QT_MOC_LITERAL(17, 202, 12), // "weaponPlayer"
QT_MOC_LITERAL(18, 215, 14), // "handlerTypeMap"
QT_MOC_LITERAL(19, 230, 7) // "typeMap"

    },
    "MainWindow\0exitApp\0\0exitCode\0"
    "createButtonClicked\0joinButtonClicked\0"
    "sliderChanged\0value\0handleCreateClosed\0"
    "code\0handleJoinClosed\0StringToTypeMap\0"
    "TypeMap_t\0std::string\0map\0StringToTypeWeapon\0"
    "TypeWeapon_t\0weaponPlayer\0handlerTypeMap\0"
    "typeMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   62,    2, 0x08 /* Private */,
       5,    0,   63,    2, 0x08 /* Private */,
       6,    1,   64,    2, 0x08 /* Private */,
       8,    1,   67,    2, 0x08 /* Private */,
      10,    1,   70,    2, 0x08 /* Private */,
      11,    1,   73,    2, 0x08 /* Private */,
      15,    1,   76,    2, 0x08 /* Private */,
      18,    1,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    0x80000000 | 12, 0x80000000 | 13,   14,
    0x80000000 | 16, 0x80000000 | 13,   17,
    QMetaType::Void, QMetaType::QString,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->exitApp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->createButtonClicked(); break;
        case 2: _t->joinButtonClicked(); break;
        case 3: _t->sliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->handleCreateClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->handleJoinClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { TypeMap_t _r = _t->StringToTypeMap((*reinterpret_cast< const std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< TypeMap_t*>(_a[0]) = std::move(_r); }  break;
        case 7: { TypeWeapon_t _r = _t->StringToTypeWeapon((*reinterpret_cast< const std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< TypeWeapon_t*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->handlerTypeMap((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::exitApp)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::exitApp(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
