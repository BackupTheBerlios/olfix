/****************************************************************************
** frmDspValuta meta object code from reading C++ file 'frmdspvaluta.h'
**
** Created: Thu Mar 20 08:19:16 2003
**      by: The Qt MOC ($Id: moc_frmdspvaluta.cpp,v 1.1 2003/05/08 08:54:50 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmdspvaluta.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmDspValuta::className() const
{
    return "frmDspValuta";
}

QMetaObject *frmDspValuta::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmDspValuta;

#ifndef QT_NO_TRANSLATION
QString frmDspValuta::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspValuta", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmDspValuta::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspValuta", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmDspValuta::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotGetValuta", 0, 0 };
    static const QUMethod slot_2 = {"LineEditValuta_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"PushButtonGet_clicked", 0, 0 };
    static const QUMethod slot_4 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_5 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_6 = {"slotEndOfProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotGetValuta()", &slot_1, QMetaData::Public },
	{ "LineEditValuta_returnPressed()", &slot_2, QMetaData::Public },
	{ "PushButtonGet_clicked()", &slot_3, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_4, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_5, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_6, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmDspValuta", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmDspValuta.setMetaObject( metaObj );
    return metaObj;
}

void* frmDspValuta::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmDspValuta" ) ) return (frmDspValuta*)this;
    return QWidget::qt_cast( clname );
}

bool frmDspValuta::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotGetValuta(); break;
    case 2: LineEditValuta_returnPressed(); break;
    case 3: PushButtonGet_clicked(); break;
    case 4: slotDataOnStdout(); break;
    case 5: slotDataOnStderr(); break;
    case 6: slotEndOfProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmDspValuta::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmDspValuta::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
