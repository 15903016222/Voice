/****************************************************************************
** Meta object code from reading C++ file 'wedge_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/probe_part/wedge_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wedge_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WedgeDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   36,   12,   12, 0x08,
      93,   36,   12,   12, 0x08,
     139,   12,   12,   12, 0x08,
     165,   12,   12,   12, 0x08,
     195,   12,   12,   12, 0x08,
     231,   12,   12,   12, 0x08,
     259,   12,   12,   12, 0x08,
     292,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WedgeDialog[] = {
    "WedgeDialog\0\0wedge_changed(QString)\0"
    "currentText\0on_dirListWidget_currentTextChanged(QString)\0"
    "on_fileListWidget_currentTextChanged(QString)\0"
    "on_okPushButton_clicked()\0"
    "on_cancelPushButton_clicked()\0"
    "on_cancelDefinePushButton_clicked()\0"
    "on_savePushButton_clicked()\0"
    "on_saveApplyPushButton_clicked()\0"
    "on_delPushButton_clicked()\0"
};

void WedgeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WedgeDialog *_t = static_cast<WedgeDialog *>(_o);
        switch (_id) {
        case 0: _t->wedge_changed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_dirListWidget_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_fileListWidget_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_okPushButton_clicked(); break;
        case 4: _t->on_cancelPushButton_clicked(); break;
        case 5: _t->on_cancelDefinePushButton_clicked(); break;
        case 6: _t->on_savePushButton_clicked(); break;
        case 7: _t->on_saveApplyPushButton_clicked(); break;
        case 8: _t->on_delPushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WedgeDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WedgeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WedgeDialog,
      qt_meta_data_WedgeDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WedgeDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WedgeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WedgeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WedgeDialog))
        return static_cast<void*>(const_cast< WedgeDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int WedgeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void WedgeDialog::wedge_changed(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
