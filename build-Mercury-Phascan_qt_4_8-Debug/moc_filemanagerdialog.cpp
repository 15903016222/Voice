/****************************************************************************
** Meta object code from reading C++ file 'filemanagerdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/dialog/filemanagerdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filemanagerdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileManagerDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      55,   49,   18,   18, 0x08,
      90,   49,   18,   18, 0x08,
     114,   49,   18,   18, 0x08,
     138,   49,   18,   18, 0x08,
     174,   49,   18,   18, 0x08,
     210,   18,   18,   18, 0x08,
     241,   18,   18,   18, 0x08,
     275,   18,   18,   18, 0x08,
     311,  306,   18,   18, 0x08,
     354,  306,   18,   18, 0x08,
     397,   18,   18,   18, 0x08,
     426,   18,   18,   18, 0x08,
     455,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FileManagerDialog[] = {
    "FileManagerDialog\0\0on_pushButton_close_clicked()\0"
    "index\0on_listWidget_clicked(QModelIndex)\0"
    "do_header1_clicked(int)\0do_header2_clicked(int)\0"
    "on_tableView_1_pressed(QModelIndex)\0"
    "on_tableView_2_pressed(QModelIndex)\0"
    "on_pushButton_select_clicked()\0"
    "on_pushButton_selectAll_clicked()\0"
    "on_pushButton_rename_clicked()\0arg1\0"
    "on_comboBox_1_currentIndexChanged(QString)\0"
    "on_comboBox_2_currentIndexChanged(QString)\0"
    "on_pushButton_copy_clicked()\0"
    "on_pushButton_move_clicked()\0"
    "on_pushButton_delete_clicked()\0"
};

void FileManagerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileManagerDialog *_t = static_cast<FileManagerDialog *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_close_clicked(); break;
        case 1: _t->on_listWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->do_header1_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->do_header2_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_tableView_1_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_tableView_2_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_select_clicked(); break;
        case 7: _t->on_pushButton_selectAll_clicked(); break;
        case 8: _t->on_pushButton_rename_clicked(); break;
        case 9: _t->on_comboBox_1_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_comboBox_2_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_copy_clicked(); break;
        case 12: _t->on_pushButton_move_clicked(); break;
        case 13: _t->on_pushButton_delete_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FileManagerDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileManagerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FileManagerDialog,
      qt_meta_data_FileManagerDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileManagerDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileManagerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileManagerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileManagerDialog))
        return static_cast<void*>(const_cast< FileManagerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int FileManagerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
