/****************************************************************************
** ADMIN meta object code from reading C++ file 'admin.h'
**
** Created: Tue Jan 7 07:02:47 2003
**      by: The Qt MOC ($Id: moc_admin.cpp,v 1.1 2003/05/08 08:54:27 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "admin.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ADMIN::className() const
{
    return "ADMIN";
}

QMetaObject *ADMIN::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ADMIN;

#ifndef QT_NO_TRANSLATION
QString ADMIN::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ADMIN", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ADMIN::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ADMIN", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ADMIN::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"rightAddSlot", 0, 0 };
    static const QUMethod slot_1 = {"rightDeleteSlot", 0, 0 };
    static const QUMethod slot_2 = {"rightListSlot", 0, 0 };
    static const QUMethod slot_3 = {"userAddSlot", 0, 0 };
    static const QUMethod slot_4 = {"userChangeSlot", 0, 0 };
    static const QUMethod slot_5 = {"userDeleteSlot", 0, 0 };
    static const QUMethod slot_6 = {"userListSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "rightAddSlot()", &slot_0, QMetaData::Public },
	{ "rightDeleteSlot()", &slot_1, QMetaData::Public },
	{ "rightListSlot()", &slot_2, QMetaData::Public },
	{ "userAddSlot()", &slot_3, QMetaData::Public },
	{ "userChangeSlot()", &slot_4, QMetaData::Public },
	{ "userDeleteSlot()", &slot_5, QMetaData::Public },
	{ "userListSlot()", &slot_6, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ADMIN", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ADMIN.setMetaObject( metaObj );
    return metaObj;
}

void* ADMIN::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ADMIN" ) ) return (ADMIN*)this;
    return QMainWindow::qt_cast( clname );
}

bool ADMIN::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: rightAddSlot(); break;
    case 1: rightDeleteSlot(); break;
    case 2: rightListSlot(); break;
    case 3: userAddSlot(); break;
    case 4: userChangeSlot(); break;
    case 5: userDeleteSlot(); break;
    case 6: userListSlot(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ADMIN::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ADMIN::qt_property( int _id, int _f, QVariant* _v)
{
    return QMainWindow::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
