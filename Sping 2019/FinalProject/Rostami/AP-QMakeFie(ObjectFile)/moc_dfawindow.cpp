/****************************************************************************
** Meta object code from reading C++ file 'dfawindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Advanced-Programming-Final-Project/dfawindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dfawindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DfaWindow_t {
    QByteArrayData data[16];
    char stringdata0[356];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DfaWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DfaWindow_t qt_meta_stringdata_DfaWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DfaWindow"
QT_MOC_LITERAL(1, 10, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(4, 57, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(5, 81, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(6, 105, 26), // "on_actionRun_DFA_triggered"
QT_MOC_LITERAL(7, 132, 35), // "on_horizontalSlider_actionTri..."
QT_MOC_LITERAL(8, 168, 6), // "action"
QT_MOC_LITERAL(9, 175, 20), // "on_runButton_clicked"
QT_MOC_LITERAL(10, 196, 21), // "on_nextButton_clicked"
QT_MOC_LITERAL(11, 218, 23), // "on_deleteButton_clicked"
QT_MOC_LITERAL(12, 242, 27), // "on_backToMainWindow_clicked"
QT_MOC_LITERAL(13, 270, 33), // "on_actionMultiple_input_trigg..."
QT_MOC_LITERAL(14, 304, 27), // "on_actionMake_PDF_triggered"
QT_MOC_LITERAL(15, 332, 23) // "on_actionSave_triggered"

    },
    "DfaWindow\0on_pushButton_clicked\0\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked\0"
    "on_pushButton_6_clicked\0"
    "on_actionRun_DFA_triggered\0"
    "on_horizontalSlider_actionTriggered\0"
    "action\0on_runButton_clicked\0"
    "on_nextButton_clicked\0on_deleteButton_clicked\0"
    "on_backToMainWindow_clicked\0"
    "on_actionMultiple_input_triggered\0"
    "on_actionMake_PDF_triggered\0"
    "on_actionSave_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DfaWindow[] = {

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
       6,    0,   83,    2, 0x08 /* Private */,
       7,    1,   84,    2, 0x08 /* Private */,
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
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DfaWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DfaWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->on_pushButton_3_clicked(); break;
        case 3: _t->on_pushButton_6_clicked(); break;
        case 4: _t->on_actionRun_DFA_triggered(); break;
        case 5: _t->on_horizontalSlider_actionTriggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_runButton_clicked(); break;
        case 7: _t->on_nextButton_clicked(); break;
        case 8: _t->on_deleteButton_clicked(); break;
        case 9: _t->on_backToMainWindow_clicked(); break;
        case 10: _t->on_actionMultiple_input_triggered(); break;
        case 11: _t->on_actionMake_PDF_triggered(); break;
        case 12: _t->on_actionSave_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DfaWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_DfaWindow.data,
    qt_meta_data_DfaWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DfaWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DfaWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DfaWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int DfaWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
