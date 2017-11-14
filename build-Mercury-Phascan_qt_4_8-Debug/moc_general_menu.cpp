/****************************************************************************
** Meta object code from reading C++ file 'general_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/ut_setting/general_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'general_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplUtSettingMenu__GeneralMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      36,   31,   30,   30, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   31,   30,   30, 0x0a,
      74,   31,   30,   30, 0x09,
     108,  102,   30,   30, 0x09,
     137,  102,   30,   30, 0x09,
     166,  102,   30,   30, 0x09,
     198,  102,   30,   30, 0x09,
     238,  232,   30,   30, 0x09,
     271,  265,   30,   30, 0x09,
     303,   30,   30,   30, 0x09,
     322,   30,   30,   30, 0x09,
     342,   30,   30,   30, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DplUtSettingMenu__GeneralMenu[] = {
    "DplUtSettingMenu::GeneralMenu\0\0gain\0"
    "gain_changed(double)\0set_gain(double)\0"
    "do_gainItem_changed(double)\0value\0"
    "do_startItem_changed(double)\0"
    "do_rangeItem_changed(double)\0"
    "do_velocityItem_changed(double)\0"
    "do_wedgeDelayItem_changed(double)\0"
    "index\0do_utUnitItem_changed(int)\0group\0"
    "update(DplDevice::GroupPointer)\0"
    "update_gain_item()\0update_start_item()\0"
    "update_range_item()\0"
};

void DplUtSettingMenu::GeneralMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeneralMenu *_t = static_cast<GeneralMenu *>(_o);
        switch (_id) {
        case 0: _t->gain_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->set_gain((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->do_gainItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->do_startItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->do_rangeItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->do_velocityItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->do_wedgeDelayItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->do_utUnitItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->update((*reinterpret_cast< const DplDevice::GroupPointer(*)>(_a[1]))); break;
        case 9: _t->update_gain_item(); break;
        case 10: _t->update_start_item(); break;
        case 11: _t->update_range_item(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplUtSettingMenu::GeneralMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplUtSettingMenu::GeneralMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplUtSettingMenu__GeneralMenu,
      qt_meta_data_DplUtSettingMenu__GeneralMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplUtSettingMenu::GeneralMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplUtSettingMenu::GeneralMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplUtSettingMenu::GeneralMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplUtSettingMenu__GeneralMenu))
        return static_cast<void*>(const_cast< GeneralMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplUtSettingMenu::GeneralMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void DplUtSettingMenu::GeneralMenu::gain_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
