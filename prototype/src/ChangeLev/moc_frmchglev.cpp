/****************************************************************************
** frmChgLev meta object code from reading C++ file 'frmchglev.h'
**
** Created: Fri Aug 15 11:21:43 2003
**      by: The Qt MOC ($Id: moc_frmchglev.cpp,v 1.1 2003/09/28 06:48:00 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmchglev.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmChgLev::className() const
{
    return "frmChgLev";
}

QMetaObject *frmChgLev::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmChgLev( "frmChgLev", &frmChgLev::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmChgLev::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgLev", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmChgLev::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgLev", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmChgLev::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotLevNr_returnPressed", 0, 0 };
    static const QUMethod slot_1 = {"slotGetLev", 0, 0 };
    static const QUMethod slot_2 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_3 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_4 = {"slotEndOfGetProcess", 0, 0 };
    static const QUMethod slot_5 = {"slotLevOrgNr_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"slotLevNamn_returnPressed", 0, 0 };
    static const QUMethod slot_7 = {"slotLevAdress_returnPressed", 0, 0 };
    static const QUMethod slot_8 = {"slotLevPostNr_returnPressed", 0, 0 };
    static const QUMethod slot_9 = {"slotLevPostAdress_returnPressed", 0, 0 };
    static const QUMethod slot_10 = {"slotLevLand_returnPressed", 0, 0 };
    static const QUMethod slot_11 = {"slotLevTfnNr_returnPressed", 0, 0 };
    static const QUMethod slot_12 = {"slotLevFaxNr_returnPressed", 0, 0 };
    static const QUMethod slot_13 = {"slotLevTelexNr_returnPressed", 0, 0 };
    static const QUMethod slot_14 = {"slotLevEmail_returnPressed", 0, 0 };
    static const QUMethod slot_15 = {"slotLevRef_returnPressed", 0, 0 };
    static const QUMethod slot_16 = {"slotLevRefTfnNr_returnPressed", 0, 0 };
    static const QUMethod slot_17 = {"slotLevMomskod_returnPressed", 0, 0 };
    static const QUMethod slot_18 = {"slotLevKontoNr_returnPressed", 0, 0 };
    static const QUMethod slot_19 = {"slotLevPgNr_returnPressed", 0, 0 };
    static const QUMethod slot_20 = {"slotLevBgNr_returnPressed", 0, 0 };
    static const QUMethod slot_21 = {"slotLevKundNr_returnPressed", 0, 0 };
    static const QUMethod slot_22 = {"slotValuta_returnPressed", 0, 0 };
    static const QUMethod slot_23 = {"slotBetvillkor_returnPressed", 0, 0 };
    static const QUMethod slot_24 = {"slotUpdateLev", 0, 0 };
    static const QUMethod slot_25 = {"slotEndOfUpdateProcess", 0, 0 };
    static const QUMethod slot_26 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotLevNr_returnPressed()", &slot_0, QMetaData::Public },
	{ "slotGetLev()", &slot_1, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_2, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_3, QMetaData::Public },
	{ "slotEndOfGetProcess()", &slot_4, QMetaData::Public },
	{ "slotLevOrgNr_returnPressed()", &slot_5, QMetaData::Public },
	{ "slotLevNamn_returnPressed()", &slot_6, QMetaData::Public },
	{ "slotLevAdress_returnPressed()", &slot_7, QMetaData::Public },
	{ "slotLevPostNr_returnPressed()", &slot_8, QMetaData::Public },
	{ "slotLevPostAdress_returnPressed()", &slot_9, QMetaData::Public },
	{ "slotLevLand_returnPressed()", &slot_10, QMetaData::Public },
	{ "slotLevTfnNr_returnPressed()", &slot_11, QMetaData::Public },
	{ "slotLevFaxNr_returnPressed()", &slot_12, QMetaData::Public },
	{ "slotLevTelexNr_returnPressed()", &slot_13, QMetaData::Public },
	{ "slotLevEmail_returnPressed()", &slot_14, QMetaData::Public },
	{ "slotLevRef_returnPressed()", &slot_15, QMetaData::Public },
	{ "slotLevRefTfnNr_returnPressed()", &slot_16, QMetaData::Public },
	{ "slotLevMomskod_returnPressed()", &slot_17, QMetaData::Public },
	{ "slotLevKontoNr_returnPressed()", &slot_18, QMetaData::Public },
	{ "slotLevPgNr_returnPressed()", &slot_19, QMetaData::Public },
	{ "slotLevBgNr_returnPressed()", &slot_20, QMetaData::Public },
	{ "slotLevKundNr_returnPressed()", &slot_21, QMetaData::Public },
	{ "slotValuta_returnPressed()", &slot_22, QMetaData::Public },
	{ "slotBetvillkor_returnPressed()", &slot_23, QMetaData::Public },
	{ "slotUpdateLev()", &slot_24, QMetaData::Public },
	{ "slotEndOfUpdateProcess()", &slot_25, QMetaData::Public },
	{ "languageChange()", &slot_26, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmChgLev", parentObject,
	slot_tbl, 27,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmChgLev.setMetaObject( metaObj );
    return metaObj;
}

void* frmChgLev::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmChgLev" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmChgLev::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotLevNr_returnPressed(); break;
    case 1: slotGetLev(); break;
    case 2: slotDataOnStdout(); break;
    case 3: slotDataOnStderr(); break;
    case 4: slotEndOfGetProcess(); break;
    case 5: slotLevOrgNr_returnPressed(); break;
    case 6: slotLevNamn_returnPressed(); break;
    case 7: slotLevAdress_returnPressed(); break;
    case 8: slotLevPostNr_returnPressed(); break;
    case 9: slotLevPostAdress_returnPressed(); break;
    case 10: slotLevLand_returnPressed(); break;
    case 11: slotLevTfnNr_returnPressed(); break;
    case 12: slotLevFaxNr_returnPressed(); break;
    case 13: slotLevTelexNr_returnPressed(); break;
    case 14: slotLevEmail_returnPressed(); break;
    case 15: slotLevRef_returnPressed(); break;
    case 16: slotLevRefTfnNr_returnPressed(); break;
    case 17: slotLevMomskod_returnPressed(); break;
    case 18: slotLevKontoNr_returnPressed(); break;
    case 19: slotLevPgNr_returnPressed(); break;
    case 20: slotLevBgNr_returnPressed(); break;
    case 21: slotLevKundNr_returnPressed(); break;
    case 22: slotValuta_returnPressed(); break;
    case 23: slotBetvillkor_returnPressed(); break;
    case 24: slotUpdateLev(); break;
    case 25: slotEndOfUpdateProcess(); break;
    case 26: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmChgLev::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmChgLev::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmChgLev::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
