/****************************************************************************
** Meta object code from reading C++ file 'law_config_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/focal_law/law_config_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'law_config_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplFocalLawMenu__LawConfigMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      38,   32,   31,   31, 0x08,
      70,   66,   31,   31, 0x08,
      99,   66,   31,   31, 0x08,
     137,  131,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DplFocalLawMenu__LawConfigMenu[] = {
    "DplFocalLawMenu::LawConfigMenu\0\0index\0"
    "do_lawTypeItem_changed(int)\0val\0"
    "do_pulseItem_changed(double)\0"
    "do_receiverItem_changed(double)\0group\0"
    "update(DplDevice::GroupPointer)\0"
};

void DplFocalLawMenu::LawConfigMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LawConfigMenu *_t = static_cast<LawConfigMenu *>(_o);
        switch (_id) {
        case 0: _t->do_lawTypeItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->do_pulseItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->do_receiverItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->update((*reinterpret_cast< const DplDevice::GroupPointer(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplFocalLawMenu::LawConfigMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplFocalLawMenu::LawConfigMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplFocalLawMenu__LawConfigMenu,
      qt_meta_data_DplFocalLawMenu__LawConfigMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplFocalLawMenu::LawConfigMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplFocalLawMenu::LawConfigMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplFocalLawMenu::LawConfigMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplFocalLawMenu__LawConfigMenu))
        return static_cast<void*>(const_cast< LawConfigMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplFocalLawMenu::LawConfigMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
