/****************************************************************************
** frmListUser meta object code from reading C++ file 'frmlistuser.h'
**
** Created: Tue May 27 06:52:15 2003
**      by: The Qt MOC ($Id: moc_frmlistuser.cpp,v 1.2 2003/09/28 08:27:53 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmlistuser.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmListUser::className() const
{
    return "frmListUser";
}

QMetaObject *frmListUser::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmListUser( "frmListUser", &frmListUser::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmListUser::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListUser", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmListUser::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListUser", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmListUser::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"GetUser", 0, 0 };
    static const QUMethod slot_1 = {"init", 0, 0 };
    static const QUMethod slot_2 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_3 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_4 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_5 = {"slotReloadUser", 0, 0 };
    static const QUMethod slot_6 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "GetUser()", &slot_0, QMetaData::Public },
	{ "init()", &slot_1, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_2, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_3, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_4, QMetaData::Public },
	{ "slotReloadUser()", &slot_5, QMetaData::Public },
	{ "languageChange()", &slot_6, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmListUser", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmListUser.setMetaObject( metaObj );
    return metaObj;
}

void* frmListUser::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmListUser" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmListUser::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: GetUser(); break;
    case 1: init(); break;
    case 2: slotDataOnStdout(); break;
    case 3: slotEndOfProcess(); break;
    case 4: slotDataOnStderr(); break;
    case 5: slotReloadUser(); break;
    case 6: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmListUser::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmListUser::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmListUser::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
