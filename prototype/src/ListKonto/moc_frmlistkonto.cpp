/****************************************************************************
** frmListKonto meta object code from reading C++ file 'frmlistkonto.h'
**
** Created: Thu Mar 20 08:23:14 2003
**      by: The Qt MOC ($Id: moc_frmlistkonto.cpp,v 1.2 2003/09/28 08:24:46 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmlistkonto.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmListKonto::className() const
{
    return "frmListKonto";
}

QMetaObject *frmListKonto::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmListKonto;

#ifndef QT_NO_TRANSLATION
QString frmListKonto::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListKonto", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmListKonto::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmListKonto", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmListKonto::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"PushButtonLista_clicked", 0, 0 };
    static const QUMethod slot_1 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_2 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_3 = {"slotLineEditBarEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_5 = {"slotReloadKonto", 0, 0 };
    static const QUMethod slot_6 = {"init", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "PushButtonLista_clicked()", &slot_0, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_1, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_2, QMetaData::Public },
	{ "slotLineEditBarEntered()", &slot_3, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_4, QMetaData::Public },
	{ "slotReloadKonto()", &slot_5, QMetaData::Public },
	{ "init()", &slot_6, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmListKonto", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmListKonto.setMetaObject( metaObj );
    return metaObj;
}

void* frmListKonto::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmListKonto" ) ) return (frmListKonto*)this;
    return QWidget::qt_cast( clname );
}

bool frmListKonto::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: PushButtonLista_clicked(); break;
    case 1: slotDataOnStdout(); break;
    case 2: slotEndOfProcess(); break;
    case 3: slotLineEditBarEntered(); break;
    case 4: slotDataOnStderr(); break;
    case 5: slotReloadKonto(); break;
    case 6: init(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmListKonto::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmListKonto::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
