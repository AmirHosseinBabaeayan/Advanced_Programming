/****************************************************************************
** Meta object code from reading C++ file 'turingwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Advanced-Programming-Final-Project/turingwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'turingwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TuringWindow_t {
    QByteArrayData data[16];
    char stringdata0[360];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TuringWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TuringWindow_t qt_meta_stringdata_TuringWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TuringWindow"
QT_MOC_LITERAL(1, 13, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(4, 60, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(5, 84, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(6, 108, 35), // "on_horizontalSlider_actionTri..."
QT_MOC_LITERAL(7, 144, 6), // "action"
QT_MOC_LITERAL(8, 151, 20), // "on_runButton_clicked"
QT_MOC_LITERAL(9, 172, 21), // "on_nextButton_clicked"
QT_MOC_LITERAL(10, 194, 23), // "on_deleteButton_clicked"
QT_MOC_LITERAL(11, 218, 29), // "on_actionRun_Turing_triggered"
QT_MOC_LITERAL(12, 248, 27), // "on_backToMainWindow_clicked"
QT_MOC_LITERAL(13, 276, 31), // "on_actionMultiple_Run_triggered"
QT_MOC_LITERAL(14, 308, 27), // "on_actionMake_PDF_triggered"
QT_MOC_LITERAL(15, 336, 23) // "on_actionSave_triggered"

    },
    "TuringWindow\0on_pushButton_clicked\0\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked\0"
    "on_pushButton_6_clicked\0"
    "on_horizontalSlider_actionTriggered\0"
    "action\0on_runButton_clicked\0"
    "on_nextButton_clicked\0on_deleteButton_clicked\0"
    "on_actionRun_Turing_triggered\0"
    "on_backToMainWindow_clicked\0"
    "on_actionMultiple_Run_triggered\0"
    "on_actionMake_PDF_triggered\0"
    "on_actionSave_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TuringWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    1,   83,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TuringWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TuringWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->on_pushButton_3_clicked(); break;
        case 3: _t->on_pushButton_6_clicked(); break;
        case 4: _t->on_horizontalSlider_actionTriggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_runButton_clicked(); break;
        case 6: _t->on_nextButton_clicked(); break;
        case 7: _t->on_deleteButton_clicked(); break;
        case 8: _t->on_actionRun_Turing_triggered(); break;
        case 9: _t->on_backToMainWindow_clicked(); break;
        case 10: _t->on_actionMultiple_Run_triggered(); break;
        case 11: _t->on_actionMake_PDF_triggered(); break;
        case 12: _t->on_actionSave_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TuringWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_TuringWindow.data,
    qt_meta_data_TuringWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TuringWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TuringWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TuringWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TuringWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
