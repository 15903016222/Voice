/****************************************************************************
** Meta object code from reading C++ file 'group.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../device/group.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'group.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplDevice__Group[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   18,   17,   17, 0x05,
      65,   60,   17,   17, 0x05,
     111,  107,   17,   17, 0x05,
     150,  141,   17,   17, 0x05,
     197,  191,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     233,   17,   17,   17, 0x0a,
     242,   17,   17,   17, 0x0a,
     257,   17,   17,   17, 0x08,
     279,  273,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DplDevice__Group[] = {
    "DplDevice::Group\0\0mode\0"
    "mode_changed(DplDevice::Group::Mode)\0"
    "type\0ut_unit_changed(DplDevice::Group::UtUnit)\0"
    "val\0current_angle_changed(double)\0"
    "probePtr\0probe_changed(DplFocallaw::ProbePointer)\0"
    "beams\0data_event(DplSource::BeamsPointer)\0"
    "deploy()\0deploy_beams()\0update_source()\0"
    "delay\0do_wedge_delay_changed(int)\0"
};

void DplDevice::Group::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Group *_t = static_cast<Group *>(_o);
        switch (_id) {
        case 0: _t->mode_changed((*reinterpret_cast< DplDevice::Group::Mode(*)>(_a[1]))); break;
        case 1: _t->ut_unit_changed((*reinterpret_cast< DplDevice::Group::UtUnit(*)>(_a[1]))); break;
        case 2: _t->current_angle_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->probe_changed((*reinterpret_cast< DplFocallaw::ProbePointer(*)>(_a[1]))); break;
        case 4: _t->data_event((*reinterpret_cast< const DplSource::BeamsPointer(*)>(_a[1]))); break;
        case 5: _t->deploy(); break;
        case 6: _t->deploy_beams(); break;
        case 7: _t->update_source(); break;
        case 8: _t->do_wedge_delay_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplDevice::Group::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplDevice::Group::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DplDevice__Group,
      qt_meta_data_DplDevice__Group, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplDevice::Group::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplDevice::Group::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplDevice::Group::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplDevice__Group))
        return static_cast<void*>(const_cast< Group*>(this));
    return QObject::qt_metacast(_clname);
}

int DplDevice::Group::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DplDevice::Group::mode_changed(DplDevice::Group::Mode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DplDevice::Group::ut_unit_changed(DplDevice::Group::UtUnit _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DplDevice::Group::current_angle_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DplDevice::Group::probe_changed(DplFocallaw::ProbePointer _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DplDevice::Group::data_event(const DplSource::BeamsPointer & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
