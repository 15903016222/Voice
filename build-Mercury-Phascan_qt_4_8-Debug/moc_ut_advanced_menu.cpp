/****************************************************************************
** Meta object code from reading C++ file 'ut_advanced_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/ut_setting/ut_advanced_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ut_advanced_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplUtSettingMenu__UtAdvancedMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      40,   34,   33,   33, 0x09,
      72,   33,   33,   33, 0x09,
      97,   33,   33,   33, 0x09,
     133,  127,   33,   33, 0x09,
     159,  127,   33,   33, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DplUtSettingMenu__UtAdvancedMenu[] = {
    "DplUtSettingMenu::UtAdvancedMenu\0\0"
    "group\0update(DplDevice::GroupPointer)\0"
    "update_scaleFactorItem()\0"
    "do_eightPercentItem_clicked()\0index\0"
    "do_dbRefItem_changed(int)\0"
    "do_pointQtyItem(int)\0"
};

void DplUtSettingMenu::UtAdvancedMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UtAdvancedMenu *_t = static_cast<UtAdvancedMenu *>(_o);
        switch (_id) {
        case 0: _t->update((*reinterpret_cast< const DplDevice::GroupPointer(*)>(_a[1]))); break;
        case 1: _t->update_scaleFactorItem(); break;
        case 2: _t->do_eightPercentItem_clicked(); break;
        case 3: _t->do_dbRefItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->do_pointQtyItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplUtSettingMenu::UtAdvancedMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplUtSettingMenu::UtAdvancedMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplUtSettingMenu__UtAdvancedMenu,
      qt_meta_data_DplUtSettingMenu__UtAdvancedMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplUtSettingMenu::UtAdvancedMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplUtSettingMenu::UtAdvancedMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplUtSettingMenu::UtAdvancedMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplUtSettingMenu__UtAdvancedMenu))
        return static_cast<void*>(const_cast< UtAdvancedMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplUtSettingMenu::UtAdvancedMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
