/****************************************************************************
** Meta object code from reading C++ file 'combo_menu_item.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/menu_item/combo_menu_item.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'combo_menu_item.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ComboMenuItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   40,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ComboMenuItem[] = {
    "ComboMenuItem\0\0index\0value_changed(int)\0"
    "text\0set_label_text(QString)\0"
};

void ComboMenuItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ComboMenuItem *_t = static_cast<ComboMenuItem *>(_o);
        switch (_id) {
        case 0: _t->value_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->set_label_text((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ComboMenuItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ComboMenuItem::staticMetaObject = {
    { &MenuItem::staticMetaObject, qt_meta_stringdata_ComboMenuItem,
      qt_meta_data_ComboMenuItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ComboMenuItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ComboMenuItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ComboMenuItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ComboMenuItem))
        return static_cast<void*>(const_cast< ComboMenuItem*>(this));
    return MenuItem::qt_metacast(_clname);
}

int ComboMenuItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MenuItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ComboMenuItem::value_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
