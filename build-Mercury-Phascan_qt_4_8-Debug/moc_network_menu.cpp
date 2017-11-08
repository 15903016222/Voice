/****************************************************************************
** Meta object code from reading C++ file 'network_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/preference/network_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplPreferenceMenu__NetworkMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x08,
      57,   31,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DplPreferenceMenu__NetworkMenu[] = {
    "DplPreferenceMenu::NetworkMenu\0\0"
    "show_ip_address_dialog()\0"
    "show_subnet_mask_dialog()\0"
};

void DplPreferenceMenu::NetworkMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NetworkMenu *_t = static_cast<NetworkMenu *>(_o);
        switch (_id) {
        case 0: _t->show_ip_address_dialog(); break;
        case 1: _t->show_subnet_mask_dialog(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DplPreferenceMenu::NetworkMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplPreferenceMenu::NetworkMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplPreferenceMenu__NetworkMenu,
      qt_meta_data_DplPreferenceMenu__NetworkMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplPreferenceMenu::NetworkMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplPreferenceMenu::NetworkMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplPreferenceMenu::NetworkMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplPreferenceMenu__NetworkMenu))
        return static_cast<void*>(const_cast< NetworkMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplPreferenceMenu::NetworkMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
