/****************************************************************************
** Meta object code from reading C++ file 's_scan_scene.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/display/s_scan_scene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 's_scan_scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SscanScene[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   28,   11,   11, 0x0a,
      55,   49,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SscanScene[] = {
    "SscanScene\0\0image_changed()\0size\0"
    "set_size(QSize)\0beams\0"
    "set_beams(DplSource::BeamsPointer)\0"
};

void SscanScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SscanScene *_t = static_cast<SscanScene *>(_o);
        switch (_id) {
        case 0: _t->image_changed(); break;
        case 1: _t->set_size((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 2: _t->set_beams((*reinterpret_cast< const DplSource::BeamsPointer(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SscanScene::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SscanScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_SscanScene,
      qt_meta_data_SscanScene, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SscanScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SscanScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SscanScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SscanScene))
        return static_cast<void*>(const_cast< SscanScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int SscanScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SscanScene::image_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
