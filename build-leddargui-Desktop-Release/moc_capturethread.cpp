/****************************************************************************
** Meta object code from reading C++ file 'capturethread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../leddargui/capturethread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'capturethread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CaptureThread_t {
    QByteArrayData data[20];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CaptureThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CaptureThread_t qt_meta_stringdata_CaptureThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CaptureThread"
QT_MOC_LITERAL(1, 14, 8), // "newFrame"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "cv::Mat*"
QT_MOC_LITERAL(4, 33, 7), // "running"
QT_MOC_LITERAL(5, 41, 7), // "stopped"
QT_MOC_LITERAL(6, 49, 6), // "cancel"
QT_MOC_LITERAL(7, 56, 12), // "StartCapture"
QT_MOC_LITERAL(8, 69, 6), // "string"
QT_MOC_LITERAL(9, 76, 11), // "videoStream"
QT_MOC_LITERAL(10, 88, 11), // "StopCapture"
QT_MOC_LITERAL(11, 100, 11), // "StartRecord"
QT_MOC_LITERAL(12, 112, 12), // "videFileName"
QT_MOC_LITERAL(13, 125, 9), // "doCapture"
QT_MOC_LITERAL(14, 135, 13), // "videoFileName"
QT_MOC_LITERAL(15, 149, 17), // "captureDataPoints"
QT_MOC_LITERAL(16, 167, 5), // "index"
QT_MOC_LITERAL(17, 173, 18), // "std::vector<float>"
QT_MOC_LITERAL(18, 192, 10), // "dataPoints"
QT_MOC_LITERAL(19, 203, 12) // "aOrientation"

    },
    "CaptureThread\0newFrame\0\0cv::Mat*\0"
    "running\0stopped\0cancel\0StartCapture\0"
    "string\0videoStream\0StopCapture\0"
    "StartRecord\0videFileName\0doCapture\0"
    "videoFileName\0captureDataPoints\0index\0"
    "std::vector<float>\0dataPoints\0"
    "aOrientation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CaptureThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,
       5,    0,   68,    2, 0x06 /* Public */,
       6,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   70,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    2,   74,    2, 0x0a /* Public */,
      13,    1,   79,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x28 /* Private | MethodCloned */,
      15,    3,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   12,
    QMetaType::Void, 0x80000000 | 8,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 17, QMetaType::Bool,   16,   18,   19,

       0        // eod
};

void CaptureThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CaptureThread *_t = static_cast<CaptureThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newFrame((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 1: _t->running(); break;
        case 2: _t->stopped(); break;
        case 3: _t->cancel(); break;
        case 4: _t->StartCapture((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 5: _t->StopCapture(); break;
        case 6: _t->StartRecord((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 7: _t->doCapture((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 8: _t->doCapture(); break;
        case 9: _t->captureDataPoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<float>(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CaptureThread::*_t)(cv::Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CaptureThread::newFrame)) {
                *result = 0;
            }
        }
        {
            typedef void (CaptureThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CaptureThread::running)) {
                *result = 1;
            }
        }
        {
            typedef void (CaptureThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CaptureThread::stopped)) {
                *result = 2;
            }
        }
        {
            typedef void (CaptureThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CaptureThread::cancel)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject CaptureThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CaptureThread.data,
      qt_meta_data_CaptureThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CaptureThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CaptureThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CaptureThread.stringdata0))
        return static_cast<void*>(const_cast< CaptureThread*>(this));
    return QObject::qt_metacast(_clname);
}

int CaptureThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void CaptureThread::newFrame(cv::Mat * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CaptureThread::running()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void CaptureThread::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void CaptureThread::cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
