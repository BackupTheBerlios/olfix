/****************************************************************************
** frmAddValuta meta object code from reading C++ file 'frmaddvaluta.h'
**
** Created: Fri Jun 6 06:33:24 2003
**      by: The Qt MOC ($Id: moc_frmaddvaluta.cpp,v 1.2 2003/09/28 06:25:24 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddvaluta.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddValuta::className() const
{
    return "frmAddValuta";
}

QMetaObject *frmAddValuta::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddValuta( "frmAddValuta", &frmAddValuta::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmAddValuta::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddValuta", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddValuta::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddValuta", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddValuta::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotAddValuta", 0, 0 };
    static const QUMethod slot_2 = {"slotValuta_lostFocus", 0, 0 };
    static const QUMethod slot_3 = {"slotValutaEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotBeteckning_lostFocus", 0, 0 };
    static const QUMethod slot_5 = {"slotBeteckningEntered", 0, 0 };
    static const QUMethod slot_6 = {"slotLand_lostFocus", 0, 0 };
    static const QUMethod slot_7 = {"slotLandEntered", 0, 0 };
    static const QUMethod slot_8 = {"slotKop_lostFocus", 0, 0 };
    static const QUMethod slot_9 = {"slotKopEntered", 0, 0 };
    static const QUMethod slot_10 = {"slotSalj_lostFocus", 0, 0 };
    static const QUMethod slot_11 = {"slotSaljEntered", 0, 0 };
    static const QUMethod slot_12 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_13 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_14 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_15 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotAddValuta()", &slot_1, QMetaData::Public },
	{ "slotValuta_lostFocus()", &slot_2, QMetaData::Public },
	{ "slotValutaEntered()", &slot_3, QMetaData::Public },
	{ "slotBeteckning_lostFocus()", &slot_4, QMetaData::Public },
	{ "slotBeteckningEntered()", &slot_5, QMetaData::Public },
	{ "slotLand_lostFocus()", &slot_6, QMetaData::Public },
	{ "slotLandEntered()", &slot_7, QMetaData::Public },
	{ "slotKop_lostFocus()", &slot_8, QMetaData::Public },
	{ "slotKopEntered()", &slot_9, QMetaData::Public },
	{ "slotSalj_lostFocus()", &slot_10, QMetaData::Public },
	{ "slotSaljEntered()", &slot_11, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_12, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_13, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_14, QMetaData::Public },
	{ "languageChange()", &slot_15, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddValuta", parentObject,
	slot_tbl, 16,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddValuta.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddValuta::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddValuta" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmAddValuta::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotAddValuta(); break;
    case 2: slotValuta_lostFocus(); break;
    case 3: slotValutaEntered(); break;
    case 4: slotBeteckning_lostFocus(); break;
    case 5: slotBeteckningEntered(); break;
    case 6: slotLand_lostFocus(); break;
    case 7: slotLandEntered(); break;
    case 8: slotKop_lostFocus(); break;
    case 9: slotKopEntered(); break;
    case 10: slotSalj_lostFocus(); break;
    case 11: slotSaljEntered(); break;
    case 12: slotDataOnStdout(); break;
    case 13: slotDataOnStderr(); break;
    case 14: slotEndOfProcess(); break;
    case 15: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddValuta::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddValuta::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmAddValuta::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
