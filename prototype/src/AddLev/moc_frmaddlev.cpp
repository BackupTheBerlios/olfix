/****************************************************************************
** frmAddLev meta object code from reading C++ file 'frmaddlev.h'
**
** Created: Fri Aug 15 11:18:14 2003
**      by: The Qt MOC ($Id: moc_frmaddlev.cpp,v 1.1 2003/09/28 06:12:19 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddlev.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddLev::className() const
{
    return "frmAddLev";
}

QMetaObject *frmAddLev::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddLev( "frmAddLev", &frmAddLev::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmAddLev::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddLev", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddLev::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddLev", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddLev::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotLevNr_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"slotLevOrgNr_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"slotLevNamn_returnPressed", 0, 0 };
    static const QUMethod slot_4 = {"slotLevAdress_returnPressed", 0, 0 };
    static const QUMethod slot_5 = {"slotLevPostNr_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"slotLevPostAdress_returnPressed", 0, 0 };
    static const QUMethod slot_7 = {"slotLevLand_returnPressed", 0, 0 };
    static const QUMethod slot_8 = {"slotLevTfnNr_returnPressed", 0, 0 };
    static const QUMethod slot_9 = {"slotLevFaxNr_returnPressed", 0, 0 };
    static const QUMethod slot_10 = {"slotLevTelexNr_returnPressed", 0, 0 };
    static const QUMethod slot_11 = {"slotLevEmail_returnPressed", 0, 0 };
    static const QUMethod slot_12 = {"slotLevRef_returnPressed", 0, 0 };
    static const QUMethod slot_13 = {"slotLevRefTfnNr_returnPressed", 0, 0 };
    static const QUMethod slot_14 = {"slotLevMomskod_returnPressed", 0, 0 };
    static const QUMethod slot_15 = {"slotLevKontoNr_returnPressed", 0, 0 };
    static const QUMethod slot_16 = {"slotLevPgNr_returnPressed", 0, 0 };
    static const QUMethod slot_17 = {"slotLevBgNr_returnPressed", 0, 0 };
    static const QUMethod slot_18 = {"slotLevKundNr_returnPressed", 0, 0 };
    static const QUMethod slot_19 = {"slotLevValuta_returnPressed", 0, 0 };
    static const QUMethod slot_20 = {"slotLevBetvilk_returnPressed", 0, 0 };
    static const QUMethod slot_21 = {"slotBtnOK_clicked", 0, 0 };
    static const QUMethod slot_22 = {"slotAddLev", 0, 0 };
    static const QUMethod slot_23 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_24 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_25 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_26 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotLevNr_returnPressed()", &slot_1, QMetaData::Public },
	{ "slotLevOrgNr_returnPressed()", &slot_2, QMetaData::Public },
	{ "slotLevNamn_returnPressed()", &slot_3, QMetaData::Public },
	{ "slotLevAdress_returnPressed()", &slot_4, QMetaData::Public },
	{ "slotLevPostNr_returnPressed()", &slot_5, QMetaData::Public },
	{ "slotLevPostAdress_returnPressed()", &slot_6, QMetaData::Public },
	{ "slotLevLand_returnPressed()", &slot_7, QMetaData::Public },
	{ "slotLevTfnNr_returnPressed()", &slot_8, QMetaData::Public },
	{ "slotLevFaxNr_returnPressed()", &slot_9, QMetaData::Public },
	{ "slotLevTelexNr_returnPressed()", &slot_10, QMetaData::Public },
	{ "slotLevEmail_returnPressed()", &slot_11, QMetaData::Public },
	{ "slotLevRef_returnPressed()", &slot_12, QMetaData::Public },
	{ "slotLevRefTfnNr_returnPressed()", &slot_13, QMetaData::Public },
	{ "slotLevMomskod_returnPressed()", &slot_14, QMetaData::Public },
	{ "slotLevKontoNr_returnPressed()", &slot_15, QMetaData::Public },
	{ "slotLevPgNr_returnPressed()", &slot_16, QMetaData::Public },
	{ "slotLevBgNr_returnPressed()", &slot_17, QMetaData::Public },
	{ "slotLevKundNr_returnPressed()", &slot_18, QMetaData::Public },
	{ "slotLevValuta_returnPressed()", &slot_19, QMetaData::Public },
	{ "slotLevBetvilk_returnPressed()", &slot_20, QMetaData::Public },
	{ "slotBtnOK_clicked()", &slot_21, QMetaData::Public },
	{ "slotAddLev()", &slot_22, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_23, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_24, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_25, QMetaData::Public },
	{ "languageChange()", &slot_26, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddLev", parentObject,
	slot_tbl, 27,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddLev.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddLev::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddLev" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmAddLev::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotLevNr_returnPressed(); break;
    case 2: slotLevOrgNr_returnPressed(); break;
    case 3: slotLevNamn_returnPressed(); break;
    case 4: slotLevAdress_returnPressed(); break;
    case 5: slotLevPostNr_returnPressed(); break;
    case 6: slotLevPostAdress_returnPressed(); break;
    case 7: slotLevLand_returnPressed(); break;
    case 8: slotLevTfnNr_returnPressed(); break;
    case 9: slotLevFaxNr_returnPressed(); break;
    case 10: slotLevTelexNr_returnPressed(); break;
    case 11: slotLevEmail_returnPressed(); break;
    case 12: slotLevRef_returnPressed(); break;
    case 13: slotLevRefTfnNr_returnPressed(); break;
    case 14: slotLevMomskod_returnPressed(); break;
    case 15: slotLevKontoNr_returnPressed(); break;
    case 16: slotLevPgNr_returnPressed(); break;
    case 17: slotLevBgNr_returnPressed(); break;
    case 18: slotLevKundNr_returnPressed(); break;
    case 19: slotLevValuta_returnPressed(); break;
    case 20: slotLevBetvilk_returnPressed(); break;
    case 21: slotBtnOK_clicked(); break;
    case 22: slotAddLev(); break;
    case 23: slotDataOnStdout(); break;
    case 24: slotDataOnStderr(); break;
    case 25: slotEndOfProcess(); break;
    case 26: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddLev::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddLev::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmAddLev::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
