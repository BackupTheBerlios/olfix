/****************************************************************************
** frmDspKstalle meta object code from reading C++ file 'frmdspkstalle.h'
**
** Created: Thu Mar 20 08:17:24 2003
**      by: The Qt MOC ($Id: moc_frmdspkstalle.cpp,v 1.2 2003/09/28 07:50:42 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmdspkstalle.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmDspKstalle::className() const
{
    return "frmDspKstalle";
}

QMetaObject *frmDspKstalle::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmDspKstalle;

#ifndef QT_NO_TRANSLATION
QString frmDspKstalle::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspKstalle", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmDspKstalle::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspKstalle", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmDspKstalle::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"LineEditBar_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"LineEditKstalle_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"slotGetKstalle", 0, 0 };
    static const QUMethod slot_4 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_5 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_6 = {"slotEndOfProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "LineEditBar_returnPressed()", &slot_1, QMetaData::Public },
	{ "LineEditKstalle_returnPressed()", &slot_2, QMetaData::Public },
	{ "slotGetKstalle()", &slot_3, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_4, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_5, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_6, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmDspKstalle", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmDspKstalle.setMetaObject( metaObj );
    return metaObj;
}

void* frmDspKstalle::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmDspKstalle" ) ) return (frmDspKstalle*)this;
    return QWidget::qt_cast( clname );
}

bool frmDspKstalle::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: LineEditBar_returnPressed(); break;
    case 2: LineEditKstalle_returnPressed(); break;
    case 3: slotGetKstalle(); break;
    case 4: slotDataOnStdout(); break;
    case 5: slotDataOnStderr(); break;
    case 6: slotEndOfProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmDspKstalle::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmDspKstalle::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
