/****************************************************************************
** frmDspUsr meta object code from reading C++ file 'frmdspusr.h'
**
** Created: Thu Mar 20 08:15:03 2003
**      by: The Qt MOC ($Id: moc_frmdspusr.cpp,v 1.2 2003/09/28 07:58:13 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmdspusr.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmDspUsr::className() const
{
    return "frmDspUsr";
}

QMetaObject *frmDspUsr::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmDspUsr;

#ifndef QT_NO_TRANSLATION
QString frmDspUsr::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspUsr", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmDspUsr::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspUsr", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmDspUsr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotPushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_1 = {"slotGetUserData", 0, 0 };
    static const QUMethod slot_2 = {"slotGetRightData", 0, 0 };
    static const QUMethod slot_3 = {"slotUseridEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotRightDataOnStdout", 0, 0 };
    static const QUMethod slot_5 = {"slotEndOfRightProcess", 0, 0 };
    static const QUMethod slot_6 = {"slotUsrDataOnStdout", 0, 0 };
    static const QUMethod slot_7 = {"slotEndOfUsrProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotPushButtonOK_clicked()", &slot_0, QMetaData::Public },
	{ "slotGetUserData()", &slot_1, QMetaData::Public },
	{ "slotGetRightData()", &slot_2, QMetaData::Public },
	{ "slotUseridEntered()", &slot_3, QMetaData::Public },
	{ "slotRightDataOnStdout()", &slot_4, QMetaData::Public },
	{ "slotEndOfRightProcess()", &slot_5, QMetaData::Public },
	{ "slotUsrDataOnStdout()", &slot_6, QMetaData::Public },
	{ "slotEndOfUsrProcess()", &slot_7, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmDspUsr", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmDspUsr.setMetaObject( metaObj );
    return metaObj;
}

void* frmDspUsr::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmDspUsr" ) ) return (frmDspUsr*)this;
    return QWidget::qt_cast( clname );
}

bool frmDspUsr::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotPushButtonOK_clicked(); break;
    case 1: slotGetUserData(); break;
    case 2: slotGetRightData(); break;
    case 3: slotUseridEntered(); break;
    case 4: slotRightDataOnStdout(); break;
    case 5: slotEndOfRightProcess(); break;
    case 6: slotUsrDataOnStdout(); break;
    case 7: slotEndOfUsrProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmDspUsr::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmDspUsr::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
