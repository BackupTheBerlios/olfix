/****************************************************************************
** frmAddKund meta object code from reading C++ file 'frmaddkund.h'
**
** Created: Thu Sep 11 04:33:41 2003
**      by: The Qt MOC ($Id: moc_frmaddkund.cpp,v 1.1 2003/09/28 06:06:24 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddkund.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddKund::className() const
{
    return "frmAddKund";
}

QMetaObject *frmAddKund::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddKund( "frmAddKund", &frmAddKund::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmAddKund::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddKund", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddKund::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddKund", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddKund::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"lineEditKundNr_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"lineEditKundNamn_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"lineEditKundAdress_returnPressed", 0, 0 };
    static const QUMethod slot_4 = {"lineEditKundPostnr_returnPressed", 0, 0 };
    static const QUMethod slot_5 = {"lineEditKundPostAdress_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"lineEditKundLand_returnPressed", 0, 0 };
    static const QUMethod slot_7 = {"lineEditKundTftnNr_returnPressed", 0, 0 };
    static const QUMethod slot_8 = {"lineEditKundFaxNr_returnPressed", 0, 0 };
    static const QUMethod slot_9 = {"lineEditKundEmail_returnPressed", 0, 0 };
    static const QUMethod slot_10 = {"lineEditKundErRef_returnPressed", 0, 0 };
    static const QUMethod slot_11 = {"lineEditErRefTfnNr_returnPressed", 0, 0 };
    static const QUMethod slot_12 = {"lineEditKundErRefEmail_returnPressed", 0, 0 };
    static const QUMethod slot_13 = {"lineEditKundSeljare_returnPressed", 0, 0 };
    static const QUMethod slot_14 = {"lineEditKundDistrikt_returnPressed", 0, 0 };
    static const QUMethod slot_15 = {"lineEditKundKategori_returnPressed", 0, 0 };
    static const QUMethod slot_16 = {"lineEditKundStdLevplats_returnPressed", 0, 0 };
    static const QUMethod slot_17 = {"lineEditKundLevvilk_returnPressed", 0, 0 };
    static const QUMethod slot_18 = {"lineEditKundLevsett_returnPressed", 0, 0 };
    static const QUMethod slot_19 = {"lineEditKundBetvilk_returnPressed", 0, 0 };
    static const QUMethod slot_20 = {"lineEditValuta_returnPressed", 0, 0 };
    static const QUMethod slot_21 = {"lineEditSprakkod_returnPressed", 0, 0 };
    static const QUMethod slot_22 = {"lineEditOrdererk_returnPressed", 0, 0 };
    static const QUMethod slot_23 = {"lineEditPlocklista_returnPressed", 0, 0 };
    static const QUMethod slot_24 = {"lineEditFoljesedel_returnPressed", 0, 0 };
    static const QUMethod slot_25 = {"lineEditExpAvgift_returnPressed", 0, 0 };
    static const QUMethod slot_26 = {"lineEditFraktAvgift_returnPressed", 0, 0 };
    static const QUMethod slot_27 = {"lineEditKravbrev_returnPressed", 0, 0 };
    static const QUMethod slot_28 = {"lineEditKreditlimit_returnPressed", 0, 0 };
    static const QUMethod slot_29 = {"lineEditDrojRenta_returnPressed", 0, 0 };
    static const QUMethod slot_30 = {"lineEditDrojFaktura_returnPressed", 0, 0 };
    static const QUMethod slot_31 = {"lineEditFriText_returnPressed", 0, 0 };
    static const QUMethod slot_32 = {"pushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_33 = {"updateKundreg", 0, 0 };
    static const QUMethod slot_34 = {"slotUpdateEndOfProcess", 0, 0 };
    static const QUMethod slot_35 = {"CheckKundnr", 0, 0 };
    static const QUMethod slot_36 = {"slotCheckEndOfProcess", 0, 0 };
    static const QUMethod slot_37 = {"createStandardLevPlats", 0, 0 };
    static const QUMethod slot_38 = {"slotPlatsEndOfProcess", 0, 0 };
    static const QUMethod slot_39 = {"AddLevplats001", 0, 0 };
    static const QUMethod slot_40 = {"slotPlats001EndOfProcess", 0, 0 };
    static const QUMethod slot_41 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_42 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_43 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "lineEditKundNr_returnPressed()", &slot_1, QMetaData::Public },
	{ "lineEditKundNamn_returnPressed()", &slot_2, QMetaData::Public },
	{ "lineEditKundAdress_returnPressed()", &slot_3, QMetaData::Public },
	{ "lineEditKundPostnr_returnPressed()", &slot_4, QMetaData::Public },
	{ "lineEditKundPostAdress_returnPressed()", &slot_5, QMetaData::Public },
	{ "lineEditKundLand_returnPressed()", &slot_6, QMetaData::Public },
	{ "lineEditKundTftnNr_returnPressed()", &slot_7, QMetaData::Public },
	{ "lineEditKundFaxNr_returnPressed()", &slot_8, QMetaData::Public },
	{ "lineEditKundEmail_returnPressed()", &slot_9, QMetaData::Public },
	{ "lineEditKundErRef_returnPressed()", &slot_10, QMetaData::Public },
	{ "lineEditErRefTfnNr_returnPressed()", &slot_11, QMetaData::Public },
	{ "lineEditKundErRefEmail_returnPressed()", &slot_12, QMetaData::Public },
	{ "lineEditKundSeljare_returnPressed()", &slot_13, QMetaData::Public },
	{ "lineEditKundDistrikt_returnPressed()", &slot_14, QMetaData::Public },
	{ "lineEditKundKategori_returnPressed()", &slot_15, QMetaData::Public },
	{ "lineEditKundStdLevplats_returnPressed()", &slot_16, QMetaData::Public },
	{ "lineEditKundLevvilk_returnPressed()", &slot_17, QMetaData::Public },
	{ "lineEditKundLevsett_returnPressed()", &slot_18, QMetaData::Public },
	{ "lineEditKundBetvilk_returnPressed()", &slot_19, QMetaData::Public },
	{ "lineEditValuta_returnPressed()", &slot_20, QMetaData::Public },
	{ "lineEditSprakkod_returnPressed()", &slot_21, QMetaData::Public },
	{ "lineEditOrdererk_returnPressed()", &slot_22, QMetaData::Public },
	{ "lineEditPlocklista_returnPressed()", &slot_23, QMetaData::Public },
	{ "lineEditFoljesedel_returnPressed()", &slot_24, QMetaData::Public },
	{ "lineEditExpAvgift_returnPressed()", &slot_25, QMetaData::Public },
	{ "lineEditFraktAvgift_returnPressed()", &slot_26, QMetaData::Public },
	{ "lineEditKravbrev_returnPressed()", &slot_27, QMetaData::Public },
	{ "lineEditKreditlimit_returnPressed()", &slot_28, QMetaData::Public },
	{ "lineEditDrojRenta_returnPressed()", &slot_29, QMetaData::Public },
	{ "lineEditDrojFaktura_returnPressed()", &slot_30, QMetaData::Public },
	{ "lineEditFriText_returnPressed()", &slot_31, QMetaData::Public },
	{ "pushButtonOK_clicked()", &slot_32, QMetaData::Public },
	{ "updateKundreg()", &slot_33, QMetaData::Public },
	{ "slotUpdateEndOfProcess()", &slot_34, QMetaData::Public },
	{ "CheckKundnr()", &slot_35, QMetaData::Public },
	{ "slotCheckEndOfProcess()", &slot_36, QMetaData::Public },
	{ "createStandardLevPlats()", &slot_37, QMetaData::Public },
	{ "slotPlatsEndOfProcess()", &slot_38, QMetaData::Public },
	{ "AddLevplats001()", &slot_39, QMetaData::Public },
	{ "slotPlats001EndOfProcess()", &slot_40, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_41, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_42, QMetaData::Public },
	{ "languageChange()", &slot_43, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddKund", parentObject,
	slot_tbl, 44,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddKund.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddKund::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddKund" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmAddKund::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: lineEditKundNr_returnPressed(); break;
    case 2: lineEditKundNamn_returnPressed(); break;
    case 3: lineEditKundAdress_returnPressed(); break;
    case 4: lineEditKundPostnr_returnPressed(); break;
    case 5: lineEditKundPostAdress_returnPressed(); break;
    case 6: lineEditKundLand_returnPressed(); break;
    case 7: lineEditKundTftnNr_returnPressed(); break;
    case 8: lineEditKundFaxNr_returnPressed(); break;
    case 9: lineEditKundEmail_returnPressed(); break;
    case 10: lineEditKundErRef_returnPressed(); break;
    case 11: lineEditErRefTfnNr_returnPressed(); break;
    case 12: lineEditKundErRefEmail_returnPressed(); break;
    case 13: lineEditKundSeljare_returnPressed(); break;
    case 14: lineEditKundDistrikt_returnPressed(); break;
    case 15: lineEditKundKategori_returnPressed(); break;
    case 16: lineEditKundStdLevplats_returnPressed(); break;
    case 17: lineEditKundLevvilk_returnPressed(); break;
    case 18: lineEditKundLevsett_returnPressed(); break;
    case 19: lineEditKundBetvilk_returnPressed(); break;
    case 20: lineEditValuta_returnPressed(); break;
    case 21: lineEditSprakkod_returnPressed(); break;
    case 22: lineEditOrdererk_returnPressed(); break;
    case 23: lineEditPlocklista_returnPressed(); break;
    case 24: lineEditFoljesedel_returnPressed(); break;
    case 25: lineEditExpAvgift_returnPressed(); break;
    case 26: lineEditFraktAvgift_returnPressed(); break;
    case 27: lineEditKravbrev_returnPressed(); break;
    case 28: lineEditKreditlimit_returnPressed(); break;
    case 29: lineEditDrojRenta_returnPressed(); break;
    case 30: lineEditDrojFaktura_returnPressed(); break;
    case 31: lineEditFriText_returnPressed(); break;
    case 32: pushButtonOK_clicked(); break;
    case 33: updateKundreg(); break;
    case 34: slotUpdateEndOfProcess(); break;
    case 35: CheckKundnr(); break;
    case 36: slotCheckEndOfProcess(); break;
    case 37: createStandardLevPlats(); break;
    case 38: slotPlatsEndOfProcess(); break;
    case 39: AddLevplats001(); break;
    case 40: slotPlats001EndOfProcess(); break;
    case 41: slotDataOnStderr(); break;
    case 42: slotDataOnStdout(); break;
    case 43: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddKund::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddKund::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmAddKund::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
