/****************************************************************************
** frmDelUsr meta object code from reading C++ file 'frmdelusr.h'
**
** Created: Thu Mar 20 08:11:59 2003
**      by: The Qt MOC ($Id: moc_frmdelusr.cpp,v 1.2 2003/09/28 07:46:06 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmdelusr.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmDelUsr::className() const
{
    return "frmDelUsr";
}

QMetaObject *frmDelUsr::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmDelUsr;

#ifndef QT_NO_TRANSLATION
QString frmDelUsr::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDelUsr", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmDelUsr::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDelUsr", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmDelUsr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotPushButtonGet_clicked", 0, 0 };
    static const QUMethod slot_1 = {"slotGetUserData", 0, 0 };
    static const QUMethod slot_2 = {"slotGetRightData", 0, 0 };
    static const QUMethod slot_3 = {"slotUseridEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotRightDataOnStdout", 0, 0 };
    static const QUMethod slot_5 = {"slotEndOfRightProcess", 0, 0 };
    static const QUMethod slot_6 = {"slotUsrDataOnStdout", 0, 0 };
    static const QUMethod slot_7 = {"slotEndOfUsrProcess", 0, 0 };
    static const QUMethod slot_8 = {"slotPushButtonOK_clicked", 0, 0 };
    static const QUParameter param_slot_9[] = {
	{ "anvID", &static_QUType_QString, 0, QUParameter::In },
	{ "fncID", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"slotDelRightData", 2, param_slot_9 };
    static const QUMethod slot_10 = {"slotEndOfRgtDelProcess", 0, 0 };
    static const QUMethod slot_11 = {"slotRgtDelDataOnStderr", 0, 0 };
    static const QUMethod slot_12 = {"slotRgtDelDataOnStdout", 0, 0 };
    static const QUParameter param_slot_13[] = {
	{ "anvID", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"slotDelUsrData", 1, param_slot_13 };
    static const QUMethod slot_14 = {"slotUsrDelDataOnStdout", 0, 0 };
    static const QUMethod slot_15 = {"slotUsrDelDataOnStderr", 0, 0 };
    static const QUMethod slot_16 = {"slotEndOfUsrDelProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotPushButtonGet_clicked()", &slot_0, QMetaData::Public },
	{ "slotGetUserData()", &slot_1, QMetaData::Public },
	{ "slotGetRightData()", &slot_2, QMetaData::Public },
	{ "slotUseridEntered()", &slot_3, QMetaData::Public },
	{ "slotRightDataOnStdout()", &slot_4, QMetaData::Public },
	{ "slotEndOfRightProcess()", &slot_5, QMetaData::Public },
	{ "slotUsrDataOnStdout()", &slot_6, QMetaData::Public },
	{ "slotEndOfUsrProcess()", &slot_7, QMetaData::Public },
	{ "slotPushButtonOK_clicked()", &slot_8, QMetaData::Public },
	{ "slotDelRightData(QString,QString)", &slot_9, QMetaData::Public },
	{ "slotEndOfRgtDelProcess()", &slot_10, QMetaData::Public },
	{ "slotRgtDelDataOnStderr()", &slot_11, QMetaData::Public },
	{ "slotRgtDelDataOnStdout()", &slot_12, QMetaData::Public },
	{ "slotDelUsrData(QString)", &slot_13, QMetaData::Public },
	{ "slotUsrDelDataOnStdout()", &slot_14, QMetaData::Public },
	{ "slotUsrDelDataOnStderr()", &slot_15, QMetaData::Public },
	{ "slotEndOfUsrDelProcess()", &slot_16, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmDelUsr", parentObject,
	slot_tbl, 17,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmDelUsr.setMetaObject( metaObj );
    return metaObj;
}

void* frmDelUsr::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmDelUsr" ) ) return (frmDelUsr*)this;
    return QWidget::qt_cast( clname );
}

bool frmDelUsr::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotPushButtonGet_clicked(); break;
    case 1: slotGetUserData(); break;
    case 2: slotGetRightData(); break;
    case 3: slotUseridEntered(); break;
    case 4: slotRightDataOnStdout(); break;
    case 5: slotEndOfRightProcess(); break;
    case 6: slotUsrDataOnStdout(); break;
    case 7: slotEndOfUsrProcess(); break;
    case 8: slotPushButtonOK_clicked(); break;
    case 9: slotDelRightData((QString)static_QUType_QString.get(_o+1),(QString)static_QUType_QString.get(_o+2)); break;
    case 10: slotEndOfRgtDelProcess(); break;
    case 11: slotRgtDelDataOnStderr(); break;
    case 12: slotRgtDelDataOnStdout(); break;
    case 13: slotDelUsrData((QString)static_QUType_QString.get(_o+1)); break;
    case 14: slotUsrDelDataOnStdout(); break;
    case 15: slotUsrDelDataOnStderr(); break;
    case 16: slotEndOfUsrDelProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmDelUsr::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmDelUsr::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
