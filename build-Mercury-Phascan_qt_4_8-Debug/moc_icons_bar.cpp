/****************************************************************************
** Meta object code from reading C++ file 'icons_bar.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/icons_bar/icons_bar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icons_bar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IconsBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   27,    9,    9, 0x0a,
      98,   85,    9,    9, 0x0a,
     158,  146,    9,    9, 0x0a,
     193,    9,    9,    9, 0x0a,
     219,  214,    9,    9, 0x0a,
     234,  214,    9,    9, 0x0a,
     249,  214,    9,    9, 0x0a,
     284,  214,    9,    9, 0x0a,
     316,  214,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IconsBar[] = {
    "IconsBar\0\0keyboard_event()\0type,value\0"
    "do_temperature_event(Mcu::TemperatureType,int)\0"
    "index,status\0"
    "do_battery_status_event(int,Mcu::BatteryStatus)\0"
    "index,value\0do_battery_quantity_event(int,int)\0"
    "do_driving_changed()\0flag\0show_tcg(bool)\0"
    "show_dac(bool)\0show_sensitivity_calibration(bool)\0"
    "show_velocity_calibration(bool)\0"
    "show_delay_calibration(bool)\0"
};

void IconsBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IconsBar *_t = static_cast<IconsBar *>(_o);
        switch (_id) {
        case 0: _t->keyboard_event(); break;
        case 1: _t->do_temperature_event((*reinterpret_cast< Mcu::TemperatureType(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->do_battery_status_event((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Mcu::BatteryStatus(*)>(_a[2]))); break;
        case 3: _t->do_battery_quantity_event((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->do_driving_changed(); break;
        case 5: _t->show_tcg((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->show_dac((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->show_sensitivity_calibration((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->show_velocity_calibration((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->show_delay_calibration((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IconsBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IconsBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_IconsBar,
      qt_meta_data_IconsBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IconsBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IconsBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IconsBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IconsBar))
        return static_cast<void*>(const_cast< IconsBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int IconsBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void IconsBar::keyboard_event()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
