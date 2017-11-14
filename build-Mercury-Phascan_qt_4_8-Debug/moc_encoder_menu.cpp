/****************************************************************************
** Meta object code from reading C++ file 'encoder_menu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/menu/scan/encoder_menu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'encoder_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DplScanMenu__EncoderMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   26,   25,   25, 0x09,
      58,   26,   25,   25, 0x09,
      94,   90,   25,   25, 0x09,
     128,   26,   25,   25, 0x09,
     157,   90,   25,   25, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DplScanMenu__EncoderMenu[] = {
    "DplScanMenu::EncoderMenu\0\0pos\0"
    "do_encoderItem_changed(int)\0"
    "do_encoderTypeItem_changed(int)\0val\0"
    "do_resolutionItem_changed(double)\0"
    "do_polarityItem_changed(int)\0"
    "do_originItem_changed(double)\0"
};

void DplScanMenu::EncoderMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EncoderMenu *_t = static_cast<EncoderMenu *>(_o);
        switch (_id) {
        case 0: _t->do_encoderItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->do_encoderTypeItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->do_resolutionItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->do_polarityItem_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->do_originItem_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DplScanMenu::EncoderMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DplScanMenu::EncoderMenu::staticMetaObject = {
    { &BaseMenu::staticMetaObject, qt_meta_stringdata_DplScanMenu__EncoderMenu,
      qt_meta_data_DplScanMenu__EncoderMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DplScanMenu::EncoderMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DplScanMenu::EncoderMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DplScanMenu::EncoderMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DplScanMenu__EncoderMenu))
        return static_cast<void*>(const_cast< EncoderMenu*>(this));
    return BaseMenu::qt_metacast(_clname);
}

int DplScanMenu::EncoderMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
