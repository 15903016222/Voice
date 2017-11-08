/****************************************************************************
** Meta object code from reading C++ file 'display_selection_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/display/display_selection_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'display_selection_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplDisplayMenu__SelectionMenu[] = {

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
      31,   30,   30,   30, 0x09,
      61,   56,   30,   30, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DplDisplayMenu__SelectionMenu[] = {
    "DplDisplayMenu::SelectionMenu\0\0"
    "do_displayItem_clicked()\0type\0"
    "do_mcu_key_event(Mcu::KeyType)\0"
};

void DplDisplayMenu::SelectionMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SelectionMenu *_t = static_cast<SelectionMenu *>(_o);
        switch (_id) {
        case 0: _t->do_displayItem_clicked(); break;
        case 1: _t->do_mcu_key_event((*reinterpret_cast< Mcu::KeyType(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplDisplayMenu::SelectionMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplDisplayMenu::SelectionMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplDisplayMenu__SelectionMenu,
      qt_meta_data_DplDisplayMenu__SelectionMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplDisplayMenu::SelectionMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplDisplayMenu::SelectionMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplDisplayMenu::SelectionMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplDisplayMenu__SelectionMenu))
        return static_cast<void*>(const_cast< SelectionMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplDisplayMenu::SelectionMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
