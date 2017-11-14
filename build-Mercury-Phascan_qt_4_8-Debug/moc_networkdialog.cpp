/****************************************************************************
** Meta object code from reading C++ file 'networkdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/dialog/networkdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetworkDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      46,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NetworkDialog[] = {
    "NetworkDialog\0\0on_pushButton_cancel_clicked()\0"
    "on_pushButton_ok_clicked()\0"
};

void NetworkDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NetworkDialog *_t = static_cast<NetworkDialog *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_cancel_clicked(); break;
        case 1: _t->on_pushButton_ok_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NetworkDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NetworkDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NetworkDialog,
      qt_meta_data_NetworkDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NetworkDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NetworkDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NetworkDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkDialog))
        return static_cast<void*>(const_cast< NetworkDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NetworkDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
