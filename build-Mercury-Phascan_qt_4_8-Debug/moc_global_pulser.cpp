/****************************************************************************
** Meta object code from reading C++ file 'global_pulser.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ut/global_pulser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'global_pulser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplUt__GlobalPulser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   21,   20,   20, 0x05,
      74,   20,   20,   20, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DplUt__GlobalPulser[] = {
    "DplUt::GlobalPulser\0\0,\0"
    "voltage_changed(bool,DplUt::GlobalPulser::Voltage)\0"
    "prf_changed()\0"
};

void DplUt::GlobalPulser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GlobalPulser *_t = static_cast<GlobalPulser *>(_o);
        switch (_id) {
        case 0: _t->voltage_changed((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< DplUt::GlobalPulser::Voltage(*)>(_a[2]))); break;
        case 1: _t->prf_changed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplUt::GlobalPulser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplUt::GlobalPulser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DplUt__GlobalPulser,
      qt_meta_data_DplUt__GlobalPulser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplUt::GlobalPulser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplUt::GlobalPulser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplUt::GlobalPulser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplUt__GlobalPulser))
        return static_cast<void*>(const_cast< GlobalPulser*>(this));
    return QObject::qt_metacast(_clname);
}

int DplUt::GlobalPulser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DplUt::GlobalPulser::voltage_changed(bool _t1, DplUt::GlobalPulser::Voltage _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DplUt::GlobalPulser::prf_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
