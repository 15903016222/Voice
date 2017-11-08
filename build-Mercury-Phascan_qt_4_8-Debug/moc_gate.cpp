/****************************************************************************
** Meta object code from reading C++ file 'gate.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gate/gate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplGate__Gate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   15,   14,   14, 0x05,
      39,   15,   14,   14, 0x05,
      60,   15,   14,   14, 0x05,
      89,   81,   14,   14, 0x05,
     117,  111,   14,   14, 0x05,
     144,  139,   14,   14, 0x05,
     194,  139,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DplGate__Gate[] = {
    "DplGate::Gate\0\0val\0height_changed(int)\0"
    "start_changed(float)\0width_changed(float)\0"
    "visible\0visible_changed(bool)\0color\0"
    "color_changed(QColor)\0mode\0"
    "measure_mode_changed(DplFpga::Group::MeasureMode)\0"
    "synchro_mode_changed(DplFpga::Group::SynchroMode)\0"
};

void DplGate::Gate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Gate *_t = static_cast<Gate *>(_o);
        switch (_id) {
        case 0: _t->height_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->start_changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->width_changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->visible_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->color_changed((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 5: _t->measure_mode_changed((*reinterpret_cast< DplFpga::Group::MeasureMode(*)>(_a[1]))); break;
        case 6: _t->synchro_mode_changed((*reinterpret_cast< DplFpga::Group::SynchroMode(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplGate::Gate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplGate::Gate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DplGate__Gate,
      qt_meta_data_DplGate__Gate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplGate::Gate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplGate::Gate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplGate::Gate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplGate__Gate))
        return static_cast<void*>(const_cast< Gate*>(this));
    return QObject::qt_metacast(_clname);
}

int DplGate::Gate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DplGate::Gate::height_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DplGate::Gate::start_changed(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DplGate::Gate::width_changed(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DplGate::Gate::visible_changed(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DplGate::Gate::color_changed(const QColor & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DplGate::Gate::measure_mode_changed(DplFpga::Group::MeasureMode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DplGate::Gate::synchro_mode_changed(DplFpga::Group::SynchroMode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
