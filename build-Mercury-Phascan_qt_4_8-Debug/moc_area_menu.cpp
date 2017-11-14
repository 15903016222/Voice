/****************************************************************************
** Meta object code from reading C++ file 'area_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/scan/area_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'area_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplScanMenu__AreaMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   23,   22,   22, 0x09,
      60,   23,   22,   22, 0x09,
      91,   23,   22,   22, 0x09,
     129,   23,   22,   22, 0x09,
     163,   23,   22,   22, 0x09,
     195,   23,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DplScanMenu__AreaMenu[] = {
    "DplScanMenu::AreaMenu\0\0val\0"
    "do_scanStartItem_changed(double)\0"
    "do_scanEndItem_changed(double)\0"
    "do_scanResolutionItem_changed(double)\0"
    "do_indexStartItem_changed(double)\0"
    "do_indexEndItem_changed(double)\0"
    "do_indexResolutionItem_changed(double)\0"
};

void DplScanMenu::AreaMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AreaMenu *_t = static_cast<AreaMenu *>(_o);
        switch (_id) {
        case 0: _t->do_scanStartItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->do_scanEndItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->do_scanResolutionItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->do_indexStartItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->do_indexEndItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->do_indexResolutionItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplScanMenu::AreaMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplScanMenu::AreaMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplScanMenu__AreaMenu,
      qt_meta_data_DplScanMenu__AreaMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplScanMenu::AreaMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplScanMenu::AreaMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplScanMenu::AreaMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplScanMenu__AreaMenu))
        return static_cast<void*>(const_cast< AreaMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplScanMenu::AreaMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
