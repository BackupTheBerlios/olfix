/****************************************************************************
** frmListFunk meta object code from reading C++ file 'frmlistfunk.h'
**
** Created: Wed Mar 19 09:59:21 2003
**      by: The Qt MOC ($Id: moc_frmlistfunk.cpp,v 1.1 2003/05/08 08:54:53 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmlistfunk.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmListFunk::className() const
{
    return "frmListFunk";
}

QMetaObject *frmListFunk::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmListFunk;

#ifndef QT_NO_TRANSLATION
QString frmListFunk::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListFunk", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmListFunk::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListFunk", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmListFunk::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"GetFunc", 0, 0 };
    static const QUMethod slot_1 = {"init", 0, 0 };
    static const QUMethod slot_2 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_3 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_4 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_5 = {"slotReloadFunc", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "GetFunc()", &slot_0, QMetaData::Public },
	{ "init()", &slot_1, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_2, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_3, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_4, QMetaData::Public },
	{ "slotReloadFunc()", &slot_5, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmListFunk", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmListFunk.setMetaObject( metaObj );
    return metaObj;
}

void* frmListFunk::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmListFunk" ) ) return (frmListFunk*)this;
    return QWidget::qt_cast( clname );
}

bool frmListFunk::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: GetFunc(); break;
    case 1: init(); break;
    case 2: slotDataOnStdout(); break;
    case 3: slotEndOfProcess(); break;
    case 4: slotDataOnStderr(); break;
    case 5: slotReloadFunc(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmListFunk::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmListFunk::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
