/****************************************************************************
** Meta object code from reading C++ file 'sample.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ut/sample.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sample.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplUt__Sample[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      46,   40,   14,   14, 0x05,
      73,   67,   14,   14, 0x05,
     100,   94,   14,   14, 0x05,
     130,  126,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DplUt__Sample[] = {
    "DplUt::Sample\0\0gain\0gain_changed(float)\0"
    "start\0start_changed(float)\0range\0"
    "range_changed(float)\0ratio\0"
    "scale_factor_changed(int)\0qty\0"
    "point_qty_changed(int)\0"
};

void DplUt::Sample::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Sample *_t = static_cast<Sample *>(_o);
        switch (_id) {
        case 0: _t->gain_changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->start_changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->range_changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->scale_factor_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->point_qty_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplUt::Sample::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplUt::Sample::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DplUt__Sample,
      qt_meta_data_DplUt__Sample, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplUt::Sample::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplUt::Sample::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplUt::Sample::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplUt__Sample))
        return static_cast<void*>(const_cast< Sample*>(this));
    return QObject::qt_metacast(_clname);
}

int DplUt::Sample::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DplUt::Sample::gain_changed(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DplUt::Sample::start_changed(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DplUt::Sample::range_changed(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DplUt::Sample::scale_factor_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DplUt::Sample::point_qty_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
