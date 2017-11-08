/****************************************************************************
** Meta object code from reading C++ file 'receiver_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/ut_setting/receiver_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'receiver_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplUtSettingMenu__ReceiverMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   32,   31,   31, 0x09,
      74,   68,   31,   31, 0x09,
     101,   68,   31,   31, 0x09,
     131,   68,   31,   31, 0x09,
     163,   68,   31,   31, 0x09,
     197,  193,   31,   31, 0x09,
     229,   31,   31,   31, 0x09,
     249,   31,   31,   31, 0x09,
     271,   31,   31,   31, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DplUtSettingMenu__ReceiverMenu[] = {
    "DplUtSettingMenu::ReceiverMenu\0\0val\0"
    "do_receiverItem_changed(double)\0index\0"
    "do_filterItem_changed(int)\0"
    "do_rectifierItem_changed(int)\0"
    "do_videoFilterItem_changed(int)\0"
    "do_averagingItem_changed(int)\0grp\0"
    "update(DplDevice::GroupPointer)\0"
    "update_filterItem()\0update_receiverItem()\0"
    "update_rectifierItem()\0"
};

void DplUtSettingMenu::ReceiverMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReceiverMenu *_t = static_cast<ReceiverMenu *>(_o);
        switch (_id) {
        case 0: _t->do_receiverItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->do_filterItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->do_rectifierItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->do_videoFilterItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->do_averagingItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->update((*reinterpret_cast< const DplDevice::GroupPointer(*)>(_a[1]))); break;
        case 6: _t->update_filterItem(); break;
        case 7: _t->update_receiverItem(); break;
        case 8: _t->update_rectifierItem(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplUtSettingMenu::ReceiverMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplUtSettingMenu::ReceiverMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplUtSettingMenu__ReceiverMenu,
      qt_meta_data_DplUtSettingMenu__ReceiverMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplUtSettingMenu::ReceiverMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplUtSettingMenu::ReceiverMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplUtSettingMenu::ReceiverMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplUtSettingMenu__ReceiverMenu))
        return static_cast<void*>(const_cast< ReceiverMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplUtSettingMenu::ReceiverMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
