/****************************************************************************
** frmListRights meta object code from reading C++ file 'frmlistrights.h'
**
** Created: Thu Mar 20 15:14:29 2003
**      by: The Qt MOC ($Id: moc_frmlistrights.cpp,v 1.2 2003/09/28 08:26:38 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmlistrights.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmListRights::className() const
{
    return "frmListRights";
}

QMetaObject *frmListRights::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmListRights;

#ifndef QT_NO_TRANSLATION
QString frmListRights::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListRights", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmListRights::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListRights", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmListRights::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"GetRights", 0, 0 };
    static const QUMethod slot_1 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_2 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_3 = {"slotReloadRights", 0, 0 };
    static const QUMethod slot_4 = {"init", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "GetRights()", &slot_0, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_1, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_2, QMetaData::Public },
	{ "slotReloadRights()", &slot_3, QMetaData::Public },
	{ "init()", &slot_4, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmListRights", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmListRights.setMetaObject( metaObj );
    return metaObj;
}

void* frmListRights::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmListRights" ) ) return (frmListRights*)this;
    return QWidget::qt_cast( clname );
}

bool frmListRights::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: GetRights(); break;
    case 1: slotDataOnStdout(); break;
    case 2: slotEndOfProcess(); break;
    case 3: slotReloadRights(); break;
    case 4: init(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmListRights::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmListRights::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
