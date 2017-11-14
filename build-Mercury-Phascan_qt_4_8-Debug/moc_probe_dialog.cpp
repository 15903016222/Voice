/****************************************************************************
** Meta object code from reading C++ file 'probe_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/probe_part/probe_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'probe_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProbeDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   13,   12,   12, 0x08,
      70,   13,   12,   12, 0x08,
     116,   12,   12,   12, 0x08,
     142,   12,   12,   12, 0x08,
     172,   12,   12,   12, 0x08,
     208,   12,   12,   12, 0x08,
     236,   12,   12,   12, 0x08,
     269,   12,   12,   12, 0x08,
     301,  296,   12,   12, 0x08,
     338,  296,   12,   12, 0x08,
     382,  376,   12,   12, 0x08,
     423,  296,   12,   12, 0x08,
     465,  296,   12,   12, 0x08,
     504,  296,   12,   12, 0x08,
     543,  296,   12,   12, 0x08,
     589,  296,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ProbeDialog[] = {
    "ProbeDialog\0\0currentText\0"
    "on_dirListWidget_currentTextChanged(QString)\0"
    "on_fileListWidget_currentTextChanged(QString)\0"
    "on_okPushButton_clicked()\0"
    "on_cancelPushButton_clicked()\0"
    "on_cancelDefinePushButton_clicked()\0"
    "on_savePushButton_clicked()\0"
    "on_saveApplyPushButton_clicked()\0"
    "on_delPushButton_clicked()\0arg1\0"
    "on_modelLineEdit_textEdited(QString)\0"
    "on_serialLineEdit_textEdited(QString)\0"
    "index\0on_typeComboBox_currentIndexChanged(int)\0"
    "on_freqDoubleSpinBox_valueChanged(double)\0"
    "on_priElemQtySpinBox_valueChanged(int)\0"
    "on_secElemQtySpinBox_valueChanged(int)\0"
    "on_priPitchDoubleSpinBox_valueChanged(double)\0"
    "on_secPitchDoubleSpinBox_valueChanged(double)\0"
};

void ProbeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProbeDialog *_t = static_cast<ProbeDialog *>(_o);
        switch (_id) {
        case 0: _t->on_dirListWidget_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_fileListWidget_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_okPushButton_clicked(); break;
        case 3: _t->on_cancelPushButton_clicked(); break;
        case 4: _t->on_cancelDefinePushButton_clicked(); break;
        case 5: _t->on_savePushButton_clicked(); break;
        case 6: _t->on_saveApplyPushButton_clicked(); break;
        case 7: _t->on_delPushButton_clicked(); break;
        case 8: _t->on_modelLineEdit_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_serialLineEdit_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_typeComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_freqDoubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->on_priElemQtySpinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_secElemQtySpinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_priPitchDoubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->on_secPitchDoubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProbeDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProbeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProbeDialog,
      qt_meta_data_ProbeDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProbeDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProbeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProbeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProbeDialog))
        return static_cast<void*>(const_cast< ProbeDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProbeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
