/****************************************************************************
** Meta object code from reading C++ file 'device_p.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../device/device_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'device_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplDevice__DevicePrivate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   26,   25,   25, 0x09,
      68,   63,   25,   25, 0x09,
     124,  115,   25,   25, 0x09,
     179,   26,   25,   25, 0x09,
     209,   63,   25,   25, 0x09,
     256,  115,   25,   25, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DplDevice__DevicePrivate[] = {
    "DplDevice::DevicePrivate\0\0enable\0"
    "do_encX_enabled_changed(bool)\0mode\0"
    "do_encX_mode_changed(DplSource::Encoder::Mode)\0"
    "polarity\0"
    "do_encX_polarity_changed(DplSource::Encoder::Polarity)\0"
    "do_encY_enabled_changed(bool)\0"
    "do_encY_mode_changed(DplSource::Encoder::Mode)\0"
    "do_encY_polarity_changed(DplSource::Encoder::Polarity)\0"
};

void DplDevice::DevicePrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DevicePrivate *_t = static_cast<DevicePrivate *>(_o);
        switch (_id) {
        case 0: _t->do_encX_enabled_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->do_encX_mode_changed((*reinterpret_cast< DplSource::Encoder::Mode(*)>(_a[1]))); break;
        case 2: _t->do_encX_polarity_changed((*reinterpret_cast< DplSource::Encoder::Polarity(*)>(_a[1]))); break;
        case 3: _t->do_encY_enabled_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->do_encY_mode_changed((*reinterpret_cast< DplSource::Encoder::Mode(*)>(_a[1]))); break;
        case 5: _t->do_encY_polarity_changed((*reinterpret_cast< DplSource::Encoder::Polarity(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplDevice::DevicePrivate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplDevice::DevicePrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DplDevice__DevicePrivate,
      qt_meta_data_DplDevice__DevicePrivate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplDevice::DevicePrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplDevice::DevicePrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplDevice::DevicePrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplDevice__DevicePrivate))
        return static_cast<void*>(const_cast< DevicePrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int DplDevice::DevicePrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
