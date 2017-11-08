/****************************************************************************
** Meta object code from reading C++ file 'display_select_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/display/display_select_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'display_select_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DisplaySelectDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   21,   20,   20, 0x08,
      59,   20,   20,   20, 0x08,
      75,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DisplaySelectDialog[] = {
    "DisplaySelectDialog\0\0checked\0"
    "on_checkBox_all_clicked(bool)\0"
    "update_widget()\0on_buttonBox_accepted()\0"
};

void DisplaySelectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DisplaySelectDialog *_t = static_cast<DisplaySelectDialog *>(_o);
        switch (_id) {
        case 0: _t->on_checkBox_all_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->update_widget(); break;
        case 2: _t->on_buttonBox_accepted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DisplaySelectDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DisplaySelectDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DisplaySelectDialog,
      qt_meta_data_DisplaySelectDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DisplaySelectDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DisplaySelectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DisplaySelectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DisplaySelectDialog))
        return static_cast<void*>(const_cast< DisplaySelectDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DisplaySelectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
