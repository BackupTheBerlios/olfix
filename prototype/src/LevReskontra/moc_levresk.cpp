/****************************************************************************
** frmLevResk meta object code from reading C++ file 'levresk.h'
**
** Created: Mon Jun 30 07:23:49 2003
**      by: The Qt MOC ($Id: moc_levresk.cpp,v 1.1 2003/09/28 08:20:33 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "levresk.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmLevResk::className() const
{
    return "frmLevResk";
}

QMetaObject *frmLevResk::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmLevResk( "frmLevResk", &frmLevResk::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmLevResk::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmLevResk", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmLevResk::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmLevResk", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmLevResk::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotGetLevReskPost", 0, 0 };
    static const QUMethod slot_1 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_2 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_3 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_4 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotGetLevReskPost()", &slot_0, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_1, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_2, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_3, QMetaData::Public },
	{ "languageChange()", &slot_4, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmLevResk", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmLevResk.setMetaObject( metaObj );
    return metaObj;
}

void* frmLevResk::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmLevResk" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmLevResk::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotGetLevReskPost(); break;
    case 1: slotDataOnStdout(); break;
    case 2: slotDataOnStderr(); break;
    case 3: slotEndOfProcess(); break;
    case 4: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmLevResk::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmLevResk::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmLevResk::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
