/****************************************************************************
** Meta object code from reading C++ file 'status_bar.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/status_bar/status_bar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'status_bar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StatusBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   10,   10,   10, 0x09,
      51,   47,   10,   10, 0x09,
     106,  101,   10,   10, 0x09,
     156,  150,   10,   10, 0x09,
     195,   10,   10,   10, 0x09,
     221,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_StatusBar[] = {
    "StatusBar\0\0encoder_text_changed()\0"
    "do_timeout()\0grp\0"
    "do_current_group_changed(DplDevice::GroupPointer)\0"
    "mode\0do_scan_mode_changed(DplSource::Scan::Mode)\0"
    "beams\0do_data_event(DplSource::BeamsPointer)\0"
    "do_encoder_text_changed()\0"
    "do_acquisition_rate_changed()\0"
};

void StatusBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StatusBar *_t = static_cast<StatusBar *>(_o);
        switch (_id) {
        case 0: _t->encoder_text_changed(); break;
        case 1: _t->do_timeout(); break;
        case 2: _t->do_current_group_changed((*reinterpret_cast< const DplDevice::GroupPointer(*)>(_a[1]))); break;
        case 3: _t->do_scan_mode_changed((*reinterpret_cast< DplSource::Scan::Mode(*)>(_a[1]))); break;
        case 4: _t->do_data_event((*reinterpret_cast< const DplSource::BeamsPointer(*)>(_a[1]))); break;
        case 5: _t->do_encoder_text_changed(); break;
        case 6: _t->do_acquisition_rate_changed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StatusBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StatusBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StatusBar,
      qt_meta_data_StatusBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StatusBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StatusBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StatusBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StatusBar))
        return static_cast<void*>(const_cast< StatusBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int StatusBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void StatusBar::encoder_text_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
