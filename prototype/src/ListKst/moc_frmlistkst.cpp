/****************************************************************************
** frmListKst meta object code from reading C++ file 'frmlistkst.h'
**
** Created: Wed Mar 19 09:56:19 2003
**      by: The Qt MOC ($Id: moc_frmlistkst.cpp,v 1.2 2003/09/28 08:25:41 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmlistkst.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmListKst::className() const
{
    return "frmListKst";
}

QMetaObject *frmListKst::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmListKst;

#ifndef QT_NO_TRANSLATION
QString frmListKst::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListKst", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmListKst::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListKst", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmListKst::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"GetKstalle", 0, 0 };
    static const QUMethod slot_2 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_3 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_4 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_5 = {"slotReloadKstalle", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "GetKstalle()", &slot_1, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_2, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_3, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_4, QMetaData::Public },
	{ "slotReloadKstalle()", &slot_5, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmListKst", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmListKst.setMetaObject( metaObj );
    return metaObj;
}

void* frmListKst::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmListKst" ) ) return (frmListKst*)this;
    return QWidget::qt_cast( clname );
}

bool frmListKst::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: GetKstalle(); break;
    case 2: slotDataOnStdout(); break;
    case 3: slotDataOnStderr(); break;
    case 4: slotEndOfProcess(); break;
    case 5: slotReloadKstalle(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmListKst::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmListKst::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
