/****************************************************************************
** Meta object code from reading C++ file 'cursor.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../measure/cursor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cursor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplMeasure__Cursor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   20,   19,   19, 0x05,
      60,   20,   19,   19, 0x05,
      98,   20,   19,   19, 0x05,
     135,   20,   19,   19, 0x05,
     174,   20,   19,   19, 0x05,
     205,   20,   19,   19, 0x05,
     238,   20,   19,   19, 0x05,
     270,   20,   19,   19, 0x05,
     309,  304,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DplMeasure__Cursor[] = {
    "DplMeasure::Cursor\0\0val\0"
    "amplitude_reference_changed(double)\0"
    "amplitude_measurement_changed(double)\0"
    "ultrasound_reference_changed(double)\0"
    "ultrasound_measurement_changed(double)\0"
    "scan_reference_changed(double)\0"
    "scan_measurement_changed(double)\0"
    "index_reference_changed(double)\0"
    "index_measurement_changed(double)\0"
    "flag\0visible_changed(bool)\0"
};

void DplMeasure::Cursor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Cursor *_t = static_cast<Cursor *>(_o);
        switch (_id) {
        case 0: _t->amplitude_reference_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->amplitude_measurement_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->ultrasound_reference_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->ultrasound_measurement_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->scan_reference_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->scan_measurement_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->index_reference_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->index_measurement_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->visible_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplMeasure::Cursor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplMeasure::Cursor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DplMeasure__Cursor,
      qt_meta_data_DplMeasure__Cursor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplMeasure::Cursor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplMeasure::Cursor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplMeasure::Cursor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplMeasure__Cursor))
        return static_cast<void*>(const_cast< Cursor*>(this));
    return QObject::qt_metacast(_clname);
}

int DplMeasure::Cursor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DplMeasure::Cursor::amplitude_reference_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DplMeasure::Cursor::amplitude_measurement_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DplMeasure::Cursor::ultrasound_reference_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DplMeasure::Cursor::ultrasound_measurement_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DplMeasure::Cursor::scan_reference_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DplMeasure::Cursor::scan_measurement_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DplMeasure::Cursor::index_reference_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DplMeasure::Cursor::index_measurement_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DplMeasure::Cursor::visible_changed(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
