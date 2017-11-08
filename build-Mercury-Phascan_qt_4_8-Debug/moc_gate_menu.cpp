/****************************************************************************
** Meta object code from reading C++ file 'gate_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/gate_curves/gate_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gate_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplGateCurvesMenu__GateMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   29,   28,   28, 0x09,
      58,   29,   28,   28, 0x09,
      87,   29,   28,   28, 0x09,
     116,   29,   28,   28, 0x09,
     155,  149,   28,   28, 0x09,
     182,  149,   28,   28, 0x09,
     209,   28,   28,   28, 0x09,
     229,  149,   28,   28, 0x09,
     257,  149,   28,   28, 0x09,
     295,  289,   28,   28, 0x09,
     327,   28,   28,   28, 0x09,
     346,   28,   28,   28, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DplGateCurvesMenu__GateMenu[] = {
    "DplGateCurvesMenu::GateMenu\0\0val\0"
    "do_gateItem_changed(int)\0"
    "do_startItem_changed(double)\0"
    "do_widthItem_changed(double)\0"
    "do_thresholdItem_changed(double)\0index\0"
    "do_switchItem_changed(int)\0"
    "do_paramsItem_changed(int)\0"
    "do_sample_changed()\0do_synchroItem_changed(int)\0"
    "do_measureModeItem_changed(int)\0group\0"
    "update(DplDevice::GroupPointer)\0"
    "update_startItem()\0update_thresholdItem()\0"
};

void DplGateCurvesMenu::GateMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GateMenu *_t = static_cast<GateMenu *>(_o);
        switch (_id) {
        case 0: _t->do_gateItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->do_startItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->do_widthItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->do_thresholdItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->do_switchItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->do_paramsItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->do_sample_changed(); break;
        case 7: _t->do_synchroItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->do_measureModeItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->update((*reinterpret_cast< const DplDevice::GroupPointer(*)>(_a[1]))); break;
        case 10: _t->update_startItem(); break;
        case 11: _t->update_thresholdItem(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplGateCurvesMenu::GateMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplGateCurvesMenu::GateMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplGateCurvesMenu__GateMenu,
      qt_meta_data_DplGateCurvesMenu__GateMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplGateCurvesMenu::GateMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplGateCurvesMenu::GateMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplGateCurvesMenu::GateMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplGateCurvesMenu__GateMenu))
        return static_cast<void*>(const_cast< GateMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplGateCurvesMenu::GateMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
