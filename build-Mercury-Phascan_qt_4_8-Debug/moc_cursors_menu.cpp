/****************************************************************************
** Meta object code from reading C++ file 'cursors_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/measurement/cursors_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cursors_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplMeasurementMenu__CursorsMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   32,   32,   32, 0x09,
      49,   32,   32,   32, 0x09,
      65,   32,   32,   32, 0x09,
      81,   32,   32,   32, 0x09,
      97,   32,   32,   32, 0x09,
     113,   32,   32,   32, 0x09,
     129,   32,   32,   32, 0x09,
     151,  147,   32,   32, 0x08,
     189,  183,   32,   32, 0x08,
     223,  219,   32,   32, 0x08,
     248,  219,   32,   32, 0x08,
     273,  219,   32,   32, 0x08,
     299,  219,   32,   32, 0x08,
     325,  219,   32,   32, 0x08,
     351,  219,   32,   32, 0x08,
     377,  219,   32,   32, 0x08,
     403,  219,   32,   32, 0x08,
     429,  219,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DplMeasurementMenu__CursorsMenu[] = {
    "DplMeasurementMenu::CursorsMenu\0\0"
    "update_srItem()\0update_smItem()\0"
    "update_urItem()\0update_umItem()\0"
    "update_irItem()\0update_imItem()\0"
    "update_beamItem()\0grp\0"
    "update(DplDevice::GroupPointer)\0index\0"
    "do_selectionItem_changed(int)\0val\0"
    "do_rItem_changed(double)\0"
    "do_mItem_changed(double)\0"
    "do_srItem_changed(double)\0"
    "do_smItem_changed(double)\0"
    "do_urItem_changed(double)\0"
    "do_umItem_changed(double)\0"
    "do_irItem_changed(double)\0"
    "do_imItem_changed(double)\0"
    "do_angleItem_changed(double)\0"
};

void DplMeasurementMenu::CursorsMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CursorsMenu *_t = static_cast<CursorsMenu *>(_o);
        switch (_id) {
        case 0: _t->update_srItem(); break;
        case 1: _t->update_smItem(); break;
        case 2: _t->update_urItem(); break;
        case 3: _t->update_umItem(); break;
        case 4: _t->update_irItem(); break;
        case 5: _t->update_imItem(); break;
        case 6: _t->update_beamItem(); break;
        case 7: _t->update((*reinterpret_cast< const DplDevice::GroupPointer(*)>(_a[1]))); break;
        case 8: _t->do_selectionItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->do_rItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->do_mItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->do_srItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->do_smItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->do_urItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->do_umItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->do_irItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->do_imItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->do_angleItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplMeasurementMenu::CursorsMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplMeasurementMenu::CursorsMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplMeasurementMenu__CursorsMenu,
      qt_meta_data_DplMeasurementMenu__CursorsMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplMeasurementMenu::CursorsMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplMeasurementMenu::CursorsMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplMeasurementMenu::CursorsMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplMeasurementMenu__CursorsMenu))
        return static_cast<void*>(const_cast< CursorsMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplMeasurementMenu::CursorsMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
