/****************************************************************************
** Meta object code from reading C++ file 'battery_label.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/icons_bar/battery_label.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'battery_label.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BatteryLabel[] = {

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
      21,   14,   13,   13, 0x0a,
      58,   52,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BatteryLabel[] = {
    "BatteryLabel\0\0status\0"
    "set_status(Mcu::BatteryStatus)\0value\0"
    "set_quantity(int)\0"
};

void BatteryLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BatteryLabel *_t = static_cast<BatteryLabel *>(_o);
        switch (_id) {
        case 0: _t->set_status((*reinterpret_cast< Mcu::BatteryStatus(*)>(_a[1]))); break;
        case 1: _t->set_quantity((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BatteryLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BatteryLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_BatteryLabel,
      qt_meta_data_BatteryLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BatteryLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BatteryLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BatteryLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BatteryLabel))
        return static_cast<void*>(const_cast< BatteryLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int BatteryLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
