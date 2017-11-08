/****************************************************************************
** Meta object code from reading C++ file 'virtualkeyboard.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/dialog/virtualkeyboard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'virtualkeyboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VirtualKeyboard[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   16,   16,   16, 0x08,
      52,   16,   16,   16, 0x08,
      79,   16,   16,   16, 0x08,
     105,   16,   16,   16, 0x08,
     131,   16,   16,   16, 0x08,
     157,   16,   16,   16, 0x08,
     183,   16,   16,   16, 0x08,
     209,   16,   16,   16, 0x08,
     235,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VirtualKeyboard[] = {
    "VirtualKeyboard\0\0close_keyboard()\0"
    "do_click_button()\0on_panelButton_0_clicked()\0"
    "on_pushButton_1_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_7_clicked()\0"
};

void VirtualKeyboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VirtualKeyboard *_t = static_cast<VirtualKeyboard *>(_o);
        switch (_id) {
        case 0: _t->close_keyboard(); break;
        case 1: _t->do_click_button(); break;
        case 2: _t->on_panelButton_0_clicked(); break;
        case 3: _t->on_pushButton_1_clicked(); break;
        case 4: _t->on_pushButton_2_clicked(); break;
        case 5: _t->on_pushButton_3_clicked(); break;
        case 6: _t->on_pushButton_4_clicked(); break;
        case 7: _t->on_pushButton_5_clicked(); break;
        case 8: _t->on_pushButton_6_clicked(); break;
        case 9: _t->on_pushButton_7_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData VirtualKeyboard::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VirtualKeyboard::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VirtualKeyboard,
      qt_meta_data_VirtualKeyboard, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VirtualKeyboard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VirtualKeyboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VirtualKeyboard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VirtualKeyboard))
        return static_cast<void*>(const_cast< VirtualKeyboard*>(this));
    return QWidget::qt_metacast(_clname);
}

int VirtualKeyboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void VirtualKeyboard::close_keyboard()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
