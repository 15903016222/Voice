/****************************************************************************
** Meta object code from reading C++ file 'inputpanelcontext.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/dialog/inputpanelcontext.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputpanelcontext.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InputPanelContext[] = {

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
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   18,   18,   18, 0x08,
      57,   18,   18,   18, 0x08,
      90,   18,   18,   18, 0x08,
     120,   18,   18,   18, 0x08,
     154,   18,   18,   18, 0x08,
     181,   18,   18,   18, 0x08,
     216,   18,   18,   18, 0x08,
     230,   18,   18,   18, 0x08,
     266,   18,   18,   18, 0x08,
     297,   18,   18,   18, 0x08,
     328,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InputPanelContext[] = {
    "InputPanelContext\0\0textEditFinished(QString)\0"
    "edit_text()\0on_pushButton_capsLock_clicked()\0"
    "on_pushButton_space_clicked()\0"
    "on_pushButton_backSpace_clicked()\0"
    "on_pushButton_ok_clicked()\0"
    "on_pushButton_arrow_left_clicked()\0"
    "show_cursor()\0on_pushButton_arrow_right_clicked()\0"
    "on_pushButton_cancel_clicked()\0"
    "on_pushButton_symbol_clicked()\0"
    "on_pushButton_backSpace2_clicked()\0"
};

void InputPanelContext::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InputPanelContext *_t = static_cast<InputPanelContext *>(_o);
        switch (_id) {
        case 0: _t->textEditFinished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->edit_text(); break;
        case 2: _t->on_pushButton_capsLock_clicked(); break;
        case 3: _t->on_pushButton_space_clicked(); break;
        case 4: _t->on_pushButton_backSpace_clicked(); break;
        case 5: _t->on_pushButton_ok_clicked(); break;
        case 6: _t->on_pushButton_arrow_left_clicked(); break;
        case 7: _t->show_cursor(); break;
        case 8: _t->on_pushButton_arrow_right_clicked(); break;
        case 9: _t->on_pushButton_cancel_clicked(); break;
        case 10: _t->on_pushButton_symbol_clicked(); break;
        case 11: _t->on_pushButton_backSpace2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InputPanelContext::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InputPanelContext::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InputPanelContext,
      qt_meta_data_InputPanelContext, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InputPanelContext::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InputPanelContext::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InputPanelContext::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InputPanelContext))
        return static_cast<void*>(const_cast< InputPanelContext*>(this));
    return QDialog::qt_metacast(_clname);
}

int InputPanelContext::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void InputPanelContext::textEditFinished(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
