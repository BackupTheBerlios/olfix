/****************************************************************************
** frmAddUser meta object code from reading C++ file 'frmadduser.h'
**
** Created: Thu Mar 20 07:57:00 2003
**      by: The Qt MOC ($Id: moc_frmadduser.cpp,v 1.1 2003/05/08 08:54:24 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmadduser.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddUser::className() const
{
    return "frmAddUser";
}

QMetaObject *frmAddUser::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddUser;

#ifndef QT_NO_TRANSLATION
QString frmAddUser::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddUser", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddUser::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddUser", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddUser::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotAddUser", 0, 0 };
    static const QUMethod slot_1 = {"slotUserIdEntered", 0, 0 };
    static const QUMethod slot_2 = {"slotNameEntered", 0, 0 };
    static const QUMethod slot_3 = {"slotAvdEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotGruppEntered", 0, 0 };
    static const QUMethod slot_5 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_6 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_7 = {"slotEndOfProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotAddUser()", &slot_0, QMetaData::Public },
	{ "slotUserIdEntered()", &slot_1, QMetaData::Public },
	{ "slotNameEntered()", &slot_2, QMetaData::Public },
	{ "slotAvdEntered()", &slot_3, QMetaData::Public },
	{ "slotGruppEntered()", &slot_4, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_5, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_6, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_7, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddUser", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddUser.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddUser::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddUser" ) ) return (frmAddUser*)this;
    return QWidget::qt_cast( clname );
}

bool frmAddUser::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotAddUser(); break;
    case 1: slotUserIdEntered(); break;
    case 2: slotNameEntered(); break;
    case 3: slotAvdEntered(); break;
    case 4: slotGruppEntered(); break;
    case 5: slotDataOnStdout(); break;
    case 6: slotDataOnStderr(); break;
    case 7: slotEndOfProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddUser::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddUser::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
