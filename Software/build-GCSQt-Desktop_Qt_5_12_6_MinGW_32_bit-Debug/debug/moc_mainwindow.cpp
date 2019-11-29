/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GCSQt/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[34];
    char stringdata0[830];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_btnOpenCOM_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 18), // "on_btnSend_clicked"
QT_MOC_LITERAL(4, 53, 16), // "on_COMData_ready"
QT_MOC_LITERAL(5, 70, 24), // "on_btnOpenServer_clicked"
QT_MOC_LITERAL(6, 95, 16), // "on_newConnection"
QT_MOC_LITERAL(7, 112, 12), // "on_ReadyRead"
QT_MOC_LITERAL(8, 125, 21), // "on_SocketStateChanged"
QT_MOC_LITERAL(9, 147, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(10, 176, 11), // "socketState"
QT_MOC_LITERAL(11, 188, 32), // "on_btn_change_mode_basic_clicked"
QT_MOC_LITERAL(12, 221, 42), // "on_btn_change_mode_imu_calibr..."
QT_MOC_LITERAL(13, 264, 38), // "on_btn_change_mode_pid_tunnin..."
QT_MOC_LITERAL(14, 303, 19), // "app_command_timeout"
QT_MOC_LITERAL(15, 323, 15), // "ledIndicatorOff"
QT_MOC_LITERAL(16, 339, 22), // "mode_pidt_load_timeout"
QT_MOC_LITERAL(17, 362, 23), // "mode_pidt_write_timeout"
QT_MOC_LITERAL(18, 386, 22), // "mode_pidt_save_timeout"
QT_MOC_LITERAL(19, 409, 21), // "mode_imu_load_timeout"
QT_MOC_LITERAL(20, 431, 22), // "mode_imu_write_timeout"
QT_MOC_LITERAL(21, 454, 21), // "mode_imu_save_timeout"
QT_MOC_LITERAL(22, 476, 36), // "on_btn_mode_pidt_load_params_..."
QT_MOC_LITERAL(23, 513, 25), // "on_btn_respond_ok_clicked"
QT_MOC_LITERAL(24, 539, 37), // "on_btn_mode_pidt_write_params..."
QT_MOC_LITERAL(25, 577, 26), // "on_sb_step_KP_valueChanged"
QT_MOC_LITERAL(26, 604, 4), // "arg1"
QT_MOC_LITERAL(27, 609, 26), // "on_sb_step_KI_valueChanged"
QT_MOC_LITERAL(28, 636, 21), // "on_sb_KD_valueChanged"
QT_MOC_LITERAL(29, 658, 36), // "on_btn_mode_pidt_save_params_..."
QT_MOC_LITERAL(30, 695, 35), // "on_btn_mode_imu_load_params_c..."
QT_MOC_LITERAL(31, 731, 36), // "on_btn_mode_imu_write_params_..."
QT_MOC_LITERAL(32, 768, 35), // "on_btn_mode_imu_save_params_c..."
QT_MOC_LITERAL(33, 804, 25) // "on_btn_gyro_calib_clicked"

    },
    "MainWindow\0on_btnOpenCOM_clicked\0\0"
    "on_btnSend_clicked\0on_COMData_ready\0"
    "on_btnOpenServer_clicked\0on_newConnection\0"
    "on_ReadyRead\0on_SocketStateChanged\0"
    "QAbstractSocket::SocketState\0socketState\0"
    "on_btn_change_mode_basic_clicked\0"
    "on_btn_change_mode_imu_calibration_clicked\0"
    "on_btn_change_mode_pid_tunning_clicked\0"
    "app_command_timeout\0ledIndicatorOff\0"
    "mode_pidt_load_timeout\0mode_pidt_write_timeout\0"
    "mode_pidt_save_timeout\0mode_imu_load_timeout\0"
    "mode_imu_write_timeout\0mode_imu_save_timeout\0"
    "on_btn_mode_pidt_load_params_clicked\0"
    "on_btn_respond_ok_clicked\0"
    "on_btn_mode_pidt_write_params_clicked\0"
    "on_sb_step_KP_valueChanged\0arg1\0"
    "on_sb_step_KI_valueChanged\0"
    "on_sb_KD_valueChanged\0"
    "on_btn_mode_pidt_save_params_clicked\0"
    "on_btn_mode_imu_load_params_clicked\0"
    "on_btn_mode_imu_write_params_clicked\0"
    "on_btn_mode_imu_save_params_clicked\0"
    "on_btn_gyro_calib_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  159,    2, 0x08 /* Private */,
       3,    0,  160,    2, 0x08 /* Private */,
       4,    0,  161,    2, 0x08 /* Private */,
       5,    0,  162,    2, 0x08 /* Private */,
       6,    0,  163,    2, 0x08 /* Private */,
       7,    0,  164,    2, 0x08 /* Private */,
       8,    1,  165,    2, 0x08 /* Private */,
      11,    0,  168,    2, 0x08 /* Private */,
      12,    0,  169,    2, 0x08 /* Private */,
      13,    0,  170,    2, 0x08 /* Private */,
      14,    0,  171,    2, 0x08 /* Private */,
      15,    0,  172,    2, 0x08 /* Private */,
      16,    0,  173,    2, 0x08 /* Private */,
      17,    0,  174,    2, 0x08 /* Private */,
      18,    0,  175,    2, 0x08 /* Private */,
      19,    0,  176,    2, 0x08 /* Private */,
      20,    0,  177,    2, 0x08 /* Private */,
      21,    0,  178,    2, 0x08 /* Private */,
      22,    0,  179,    2, 0x08 /* Private */,
      23,    0,  180,    2, 0x08 /* Private */,
      24,    0,  181,    2, 0x08 /* Private */,
      25,    1,  182,    2, 0x08 /* Private */,
      27,    1,  185,    2, 0x08 /* Private */,
      28,    1,  188,    2, 0x08 /* Private */,
      29,    0,  191,    2, 0x08 /* Private */,
      30,    0,  192,    2, 0x08 /* Private */,
      31,    0,  193,    2, 0x08 /* Private */,
      32,    0,  194,    2, 0x08 /* Private */,
      33,    0,  195,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnOpenCOM_clicked(); break;
        case 1: _t->on_btnSend_clicked(); break;
        case 2: _t->on_COMData_ready(); break;
        case 3: _t->on_btnOpenServer_clicked(); break;
        case 4: _t->on_newConnection(); break;
        case 5: _t->on_ReadyRead(); break;
        case 6: _t->on_SocketStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 7: _t->on_btn_change_mode_basic_clicked(); break;
        case 8: _t->on_btn_change_mode_imu_calibration_clicked(); break;
        case 9: _t->on_btn_change_mode_pid_tunning_clicked(); break;
        case 10: _t->app_command_timeout(); break;
        case 11: _t->ledIndicatorOff(); break;
        case 12: _t->mode_pidt_load_timeout(); break;
        case 13: _t->mode_pidt_write_timeout(); break;
        case 14: _t->mode_pidt_save_timeout(); break;
        case 15: _t->mode_imu_load_timeout(); break;
        case 16: _t->mode_imu_write_timeout(); break;
        case 17: _t->mode_imu_save_timeout(); break;
        case 18: _t->on_btn_mode_pidt_load_params_clicked(); break;
        case 19: _t->on_btn_respond_ok_clicked(); break;
        case 20: _t->on_btn_mode_pidt_write_params_clicked(); break;
        case 21: _t->on_sb_step_KP_valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->on_sb_step_KI_valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->on_sb_KD_valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->on_btn_mode_pidt_save_params_clicked(); break;
        case 25: _t->on_btn_mode_imu_load_params_clicked(); break;
        case 26: _t->on_btn_mode_imu_write_params_clicked(); break;
        case 27: _t->on_btn_mode_imu_save_params_clicked(); break;
        case 28: _t->on_btn_gyro_calib_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
