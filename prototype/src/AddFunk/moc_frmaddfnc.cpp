/****************************************************************************
** frmAddFnc meta object code from reading C++ file 'frmaddfnc.h'
**
** Created: Tue Jun 3 06:58:02 2003
**      by: The Qt MOC ($Id: moc_frmaddfnc.cpp,v 1.2 2003/09/28 05:49:13 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddfnc.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddFnc::className() const
{
    return "frmAddFnc";
}

QMetaObject *frmAddFnc::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddFnc( "frmAddFnc", &frmAddFnc::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmAddFnc::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddFnc", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddFnc::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddFnc", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddFnc::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotFuncEntered", 0, 0 };
    static const QUMethod slot_1 = {"slotLedTextEntered", 0, 0 };
    static const QUMethod slot_2 = {"slotAddFnc", 0, 0 };
    static const QUMethod slot_3 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_4 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_5 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_6 = {"languageChange", 0, 0 };
    static const QUMethod slot_7 = {"init", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotFuncEntered()", &slot_0, QMetaData::Public },
	{ "slotLedTextEntered()", &slot_1, QMetaData::Public },
	{ "slotAddFnc()", &slot_2, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_3, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_4, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_5, QMetaData::Public },
	{ "languageChange()", &slot_6, QMetaData::Protected },
	{ "init()", &slot_7, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddFnc", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddFnc.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddFnc::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddFnc" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmAddFnc::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotFuncEntered(); break;
    case 1: slotLedTextEntered(); break;
    case 2: slotAddFnc(); break;
    case 3: slotDataOnStdout(); break;
    case 4: slotDataOnStderr(); break;
    case 5: slotEndOfProcess(); break;
    case 6: languageChange(); break;
    case 7: init(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddFnc::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddFnc::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmAddFnc::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
