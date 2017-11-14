/****************************************************************************
** Meta object code from reading C++ file 'a_scan_hdisplay.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/display/a_scan_hdisplay.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'a_scan_hdisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AscanHDisplay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AscanHDisplay[] = {
    "AscanHDisplay\0\0update_bottom_ruler()\0"
};

void AscanHDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AscanHDisplay *_t = static_cast<AscanHDisplay *>(_o);
        switch (_id) {
        case 0: _t->update_bottom_ruler(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AscanHDisplay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AscanHDisplay::staticMetaObject = {
    { &AscanDisplay::staticMetaObject, qt_meta_stringdata_AscanHDisplay,
      qt_meta_data_AscanHDisplay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AscanHDisplay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AscanHDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AscanHDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AscanHDisplay))
        return static_cast<void*>(const_cast< AscanHDisplay*>(this));
    return AscanDisplay::qt_metacast(_clname);
}

int AscanHDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AscanDisplay::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
