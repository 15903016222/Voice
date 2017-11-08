/****************************************************************************
** Meta object code from reading C++ file 'transceiver.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ut/transceiver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transceiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplUt__Transceiver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      59,   19,   19,   19, 0x05,
      77,   19,   19,   19, 0x05,
      97,   19,   19,   19, 0x05,
     143,   19,   19,   19, 0x05,
     170,   19,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DplUt__Transceiver[] = {
    "DplUt::Transceiver\0\0"
    "mode_changed(DplUt::Transceiver::Mode)\0"
    "pw_changed(float)\0filter_changed(int)\0"
    "recitifier_changed(DplFpga::Group::Rectifier)\0"
    "video_filter_changed(bool)\0"
    "work_time_changed()\0"
};

void DplUt::Transceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Transceiver *_t = static_cast<Transceiver *>(_o);
        switch (_id) {
        case 0: _t->mode_changed((*reinterpret_cast< DplUt::Transceiver::Mode(*)>(_a[1]))); break;
        case 1: _t->pw_changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->filter_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->recitifier_changed((*reinterpret_cast< DplFpga::Group::Rectifier(*)>(_a[1]))); break;
        case 4: _t->video_filter_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->work_time_changed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplUt::Transceiver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplUt::Transceiver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DplUt__Transceiver,
      qt_meta_data_DplUt__Transceiver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplUt::Transceiver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplUt::Transceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplUt::Transceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplUt__Transceiver))
        return static_cast<void*>(const_cast< Transceiver*>(this));
    return QObject::qt_metacast(_clname);
}

int DplUt::Transceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void DplUt::Transceiver::mode_changed(DplUt::Transceiver::Mode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DplUt::Transceiver::pw_changed(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DplUt::Transceiver::filter_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DplUt::Transceiver::recitifier_changed(DplFpga::Group::Rectifier _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DplUt::Transceiver::video_filter_changed(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DplUt::Transceiver::work_time_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
