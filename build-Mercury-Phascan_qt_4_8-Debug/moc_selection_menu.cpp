/****************************************************************************
** Meta object code from reading C++ file 'selection_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/probe_part/selection_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selection_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplProbeMenu__SelectionMenu[] = {

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
      29,   28,   28,   28, 0x08,
      52,   28,   28,   28, 0x08,
      81,   75,   28,   28, 0x08,
     117,  111,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DplProbeMenu__SelectionMenu[] = {
    "DplProbeMenu::SelectionMenu\0\0"
    "do_probeItem_clicked()\0do_wedgeItem_clicked()\0"
    "index\0do_groupModeItem_changed(int)\0"
    "group\0update(DplDevice::GroupPointer)\0"
};

void DplProbeMenu::SelectionMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SelectionMenu *_t = static_cast<SelectionMenu *>(_o);
        switch (_id) {
        case 0: _t->do_probeItem_clicked(); break;
        case 1: _t->do_wedgeItem_clicked(); break;
        case 2: _t->do_groupModeItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->update((*reinterpret_cast< const DplDevice::GroupPointer(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplProbeMenu::SelectionMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplProbeMenu::SelectionMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplProbeMenu__SelectionMenu,
      qt_meta_data_DplProbeMenu__SelectionMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplProbeMenu::SelectionMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplProbeMenu::SelectionMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplProbeMenu::SelectionMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplProbeMenu__SelectionMenu))
        return static_cast<void*>(const_cast< SelectionMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplProbeMenu::SelectionMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
