/****************************************************************************
** Meta object code from reading C++ file 'b_scan_display.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/display/b_scan_display.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'b_scan_display.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BscanDisplay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x05,
      46,   41,   13,   13, 0x05,
      68,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      93,   87,   13,   13, 0x09,
     132,   13,   13,   13, 0x09,
     163,  158,   13,   13, 0x09,
     191,   13,   13,   13, 0x09,
     215,  213,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_BscanDisplay[] = {
    "BscanDisplay\0\0value\0update_ruler(double)\0"
    "time\0update_label(QString)\0"
    "refresh_scan_env()\0beams\0"
    "do_data_event(DplSource::BeamsPointer)\0"
    "update_sound_path_ruler()\0size\0"
    "do_view_size_changed(QSize)\0"
    "do_refresh_scan_env()\0x\0do_update_ruler(double)\0"
};

void BscanDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BscanDisplay *_t = static_cast<BscanDisplay *>(_o);
        switch (_id) {
        case 0: _t->update_ruler((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->update_label((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->refresh_scan_env(); break;
        case 3: _t->do_data_event((*reinterpret_cast< const DplSource::BeamsPointer(*)>(_a[1]))); break;
        case 4: _t->update_sound_path_ruler(); break;
        case 5: _t->do_view_size_changed((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 6: _t->do_refresh_scan_env(); break;
        case 7: _t->do_update_ruler((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BscanDisplay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BscanDisplay::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BscanDisplay,
      qt_meta_data_BscanDisplay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BscanDisplay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BscanDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BscanDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BscanDisplay))
        return static_cast<void*>(const_cast< BscanDisplay*>(this));
    return QWidget::qt_metacast(_clname);
}

int BscanDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void BscanDisplay::update_ruler(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BscanDisplay::update_label(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BscanDisplay::refresh_scan_env()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
