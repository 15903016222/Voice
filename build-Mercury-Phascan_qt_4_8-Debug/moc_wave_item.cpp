/****************************************************************************
** Meta object code from reading C++ file 'wave_item.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/display/wave_item.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wave_item.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WaveItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   33,    9,    9, 0x0a,
      72,   67,    9,    9, 0x2a,
      93,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WaveItem[] = {
    "WaveItem\0\0painter_path_changed()\0"
    "beam,rf\0set_wave(QByteArray,bool)\0"
    "beam\0set_wave(QByteArray)\0update()\0"
};

void WaveItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WaveItem *_t = static_cast<WaveItem *>(_o);
        switch (_id) {
        case 0: _t->painter_path_changed(); break;
        case 1: _t->set_wave((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->set_wave((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->update(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WaveItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WaveItem::staticMetaObject = {
    { &QGraphicsObject::staticMetaObject, qt_meta_stringdata_WaveItem,
      qt_meta_data_WaveItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WaveItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WaveItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WaveItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WaveItem))
        return static_cast<void*>(const_cast< WaveItem*>(this));
    return QGraphicsObject::qt_metacast(_clname);
}

int WaveItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void WaveItem::painter_path_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
