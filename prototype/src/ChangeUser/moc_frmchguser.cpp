/****************************************************************************
** frmChgUser meta object code from reading C++ file 'frmchguser.h'
**
** Created: Sun Mar 23 14:33:44 2003
**      by: The Qt MOC ($Id: moc_frmchguser.cpp,v 1.2 2003/09/28 06:49:18 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmchguser.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmChgUser::className() const
{
    return "frmChgUser";
}

QMetaObject *frmChgUser::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmChgUser;

#ifndef QT_NO_TRANSLATION
QString frmChgUser::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgUser", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmChgUser::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgUser", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmChgUser::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotGetUser", 0, 0 };
    static const QUMethod slot_1 = {"slotChgUser", 0, 0 };
    static const QUMethod slot_2 = {"slotUseridEntered", 0, 0 };
    static const QUMethod slot_3 = {"slotNameEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotAvdEntered", 0, 0 };
    static const QUMethod slot_5 = {"slotGruppEntered", 0, 0 };
    static const QUMethod slot_6 = {"slotPushButtonGet_clicked", 0, 0 };
    static const QUMethod slot_7 = {"slotPushButtonUpdate_clicked", 0, 0 };
    static const QUMethod slot_8 = {"slotUsrDataOnStdout", 0, 0 };
    static const QUMethod slot_9 = {"slotEndOfUsrProcess", 0, 0 };
    static const QUMethod slot_10 = {"slotChgDataOnStdout", 0, 0 };
    static const QUMethod slot_11 = {"slotChgDataOnStderr", 0, 0 };
    static const QUMethod slot_12 = {"slotEndOfChgProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotGetUser()", &slot_0, QMetaData::Public },
	{ "slotChgUser()", &slot_1, QMetaData::Public },
	{ "slotUseridEntered()", &slot_2, QMetaData::Public },
	{ "slotNameEntered()", &slot_3, QMetaData::Public },
	{ "slotAvdEntered()", &slot_4, QMetaData::Public },
	{ "slotGruppEntered()", &slot_5, QMetaData::Public },
	{ "slotPushButtonGet_clicked()", &slot_6, QMetaData::Public },
	{ "slotPushButtonUpdate_clicked()", &slot_7, QMetaData::Public },
	{ "slotUsrDataOnStdout()", &slot_8, QMetaData::Public },
	{ "slotEndOfUsrProcess()", &slot_9, QMetaData::Public },
	{ "slotChgDataOnStdout()", &slot_10, QMetaData::Public },
	{ "slotChgDataOnStderr()", &slot_11, QMetaData::Public },
	{ "slotEndOfChgProcess()", &slot_12, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmChgUser", parentObject,
	slot_tbl, 13,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmChgUser.setMetaObject( metaObj );
    return metaObj;
}

void* frmChgUser::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmChgUser" ) ) return (frmChgUser*)this;
    return QWidget::qt_cast( clname );
}

bool frmChgUser::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotGetUser(); break;
    case 1: slotChgUser(); break;
    case 2: slotUseridEntered(); break;
    case 3: slotNameEntered(); break;
    case 4: slotAvdEntered(); break;
    case 5: slotGruppEntered(); break;
    case 6: slotPushButtonGet_clicked(); break;
    case 7: slotPushButtonUpdate_clicked(); break;
    case 8: slotUsrDataOnStdout(); break;
    case 9: slotEndOfUsrProcess(); break;
    case 10: slotChgDataOnStdout(); break;
    case 11: slotChgDataOnStderr(); break;
    case 12: slotEndOfChgProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmChgUser::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmChgUser::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
