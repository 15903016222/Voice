/****************************************************************************
** Meta object code from reading C++ file 'preference_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/preference/preference_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'preference_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplPreferenceMenu__PreferenceMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      41,   35,   34,   34, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   35,   34,   34, 0x08,
      88,   34,   34,   34, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DplPreferenceMenu__PreferenceMenu[] = {
    "DplPreferenceMenu::PreferenceMenu\0\0"
    "value\0opacity_changed(double)\0"
    "set_brightness(double)\0do_deployItem_changed()\0"
};

void DplPreferenceMenu::PreferenceMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PreferenceMenu *_t = static_cast<PreferenceMenu *>(_o);
        switch (_id) {
        case 0: _t->opacity_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->set_brightness((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->do_deployItem_changed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplPreferenceMenu::PreferenceMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplPreferenceMenu::PreferenceMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplPreferenceMenu__PreferenceMenu,
      qt_meta_data_DplPreferenceMenu__PreferenceMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplPreferenceMenu::PreferenceMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplPreferenceMenu::PreferenceMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplPreferenceMenu::PreferenceMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplPreferenceMenu__PreferenceMenu))
        return static_cast<void*>(const_cast< PreferenceMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplPreferenceMenu::PreferenceMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DplPreferenceMenu::PreferenceMenu::opacity_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
