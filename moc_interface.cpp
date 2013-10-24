/****************************************************************************
** Meta object code from reading C++ file 'interface.h'
**
** Created: Tue Apr 9 19:22:58 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "interface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Interface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      39,   11,   10,   10, 0x08,
      80,   10,   10,   10, 0x08,
      90,   10,   10,   10, 0x08,
      99,   10,   10,   10, 0x08,
     112,   10,   10,   10, 0x08,
     124,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Interface[] = {
    "Interface\0\0mode,N,ip1,ip2,ip3,ip4,port\0"
    "getVariable(int,int,int,int,int,int,int)\0"
    "newgame()\0regret()\0switchZero()\0"
    "switchOne()\0switchTwo()\0"
};

void Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Interface *_t = static_cast<Interface *>(_o);
        switch (_id) {
        case 0: _t->getVariable((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7]))); break;
        case 1: _t->newgame(); break;
        case 2: _t->regret(); break;
        case 3: _t->switchZero(); break;
        case 4: _t->switchOne(); break;
        case 5: _t->switchTwo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Interface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Interface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Interface,
      qt_meta_data_Interface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Interface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Interface))
        return static_cast<void*>(const_cast< Interface*>(this));
    return QWidget::qt_metacast(_clname);
}

int Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
