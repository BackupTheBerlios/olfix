/****************************************************************************
** frmLevFakt meta object code from reading C++ file 'frmlevfakt.h'
**
** Created: Mon Aug 18 06:09:32 2003
**      by: The Qt MOC ($Id: moc_frmlevfakt.cpp,v 1.2 2004/02/09 07:18:45 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmlevfakt.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmLevFakt::className() const
{
    return "frmLevFakt";
}

QMetaObject *frmLevFakt::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmLevFakt( "frmLevFakt", &frmLevFakt::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmLevFakt::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmLevFakt", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmLevFakt::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmLevFakt", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmLevFakt::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotlineEditLevNr_returnPressed", 0, 0 };
    static const QUMethod slot_1 = {"slotlineEditLevKundNr_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"slotlineEditRegDatum_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"slotlineEditFaktNr_returnPressed", 0, 0 };
    static const QUMethod slot_4 = {"slotlineEditFakturadatum_returnPressed", 0, 0 };
    static const QUMethod slot_5 = {"slotlineEditBetvilk_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"slotlineEditLevBetDatum_returnPressed", 0, 0 };
    static const QUMethod slot_7 = {"slotlineEditOCRnr_returnPressed", 0, 0 };
    static const QUMethod slot_8 = {"slotlineEditLevFakturaText_returnPressed", 0, 0 };
    static const QUMethod slot_9 = {"slotlineEditBar_returnPressed", 0, 0 };
    static const QUMethod slot_10 = {"slotlineEditLevMomskod_returnPressed", 0, 0 };
    static const QUMethod slot_11 = {"slotlineEditValuta_returnPressed", 0, 0 };
    static const QUMethod slot_12 = {"slotlineEditValutaKurs_returnPressed", 0, 0 };
    static const QUMethod slot_13 = {"slotlineEditFaktBelopp_returnPressed", 0, 0 };
    static const QUMethod slot_14 = {"slotlineEditKreditKontoNr_returnPressed", 0, 0 };
    static const QUMethod slot_15 = {"slotlineEditKreditBelopp_returnPressed", 0, 0 };
    static const QUMethod slot_16 = {"slotlineEditMomsKtoNr_returnPressed", 0, 0 };
    static const QUMethod slot_17 = {"slotlineEditMomsBelopp_returnPressed", 0, 0 };
    static const QUMethod slot_18 = {"slotlineEditDebetKontoNr_returnPressed", 0, 0 };
    static const QUMethod slot_19 = {"slotlineEditDebetBelopp_returnPressed", 0, 0 };
    static const QUMethod slot_20 = {"checkSemafor", 0, 0 };
    static const QUMethod slot_21 = {"slotGetLev", 0, 0 };
    static const QUMethod slot_22 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_23 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_24 = {"slotEndOfGetProcess", 0, 0 };
    static const QUMethod slot_25 = {"slotCheckBar", 0, 0 };
    static const QUMethod slot_26 = {"slotBARCHKEndOfProcess", 0, 0 };
    static const QUParameter param_slot_27[] = {
	{ "ktonr", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_27 = {"slotCheckKontoNr", 1, param_slot_27 };
    static const QUMethod slot_28 = {"slotKTOCHKEndOfProcess", 0, 0 };
    static const QUParameter param_slot_29[] = {
	{ "momskod", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_29 = {"slotGetMoms", 1, param_slot_29 };
    static const QUMethod slot_30 = {"slotFTGDSPEndOfProcess", 0, 0 };
    static const QUMethod slot_31 = {"slotUpdateLevresk", 0, 0 };
    static const QUMethod slot_32 = {"slotLEVRESKEndOfProcess", 0, 0 };
    static const QUMethod slot_33 = {"slotGetNextVernr", 0, 0 };
    static const QUMethod slot_34 = {"slotBARDSPEndOfProcess", 0, 0 };
    static const QUMethod slot_35 = {"slotSaveVerHuvud", 0, 0 };
    static const QUParameter param_slot_36[] = {
	{ "ktonummer", &static_QUType_QString, 0, QUParameter::In },
	{ "belopp", &static_QUType_QString, 0, QUParameter::In },
	{ "radnr", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_36 = {"slotSaveVerRad", 3, param_slot_36 };
    static const QUMethod slot_37 = {"slotWRRECEndOfProcess", 0, 0 };
    static const QUMethod slot_38 = {"slotUppdateraVer", 0, 0 };
    static const QUMethod slot_39 = {"slotVERUPDEndOfProcess", 0, 0 };
    static const QUMethod slot_40 = {"slotVerRemove", 0, 0 };
    static const QUMethod slot_41 = {"slotClearVariabler", 0, 0 };
    static const QUMethod slot_42 = {"slotGetValuta", 0, 0 };
    static const QUMethod slot_43 = {"slotVALDSPEndOfProcess", 0, 0 };
    static const QUParameter param_slot_44[] = {
	{ "betvilkor", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_44 = {"slotGetBetvilkor", 1, param_slot_44 };
    static const QUMethod slot_45 = {"slotBETDSPDataOnStdout", 0, 0 };
    static const QUMethod slot_46 = {"slotBETDSPEndOfProcess", 0, 0 };
    static const QUParameter param_slot_47[] = {
	{ "datum", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_47 = {"slotFindBar", 1, param_slot_47 };
    static const QUMethod slot_48 = {"slotBARFNDDataOnStdout", 0, 0 };
    static const QUMethod slot_49 = {"slotBARFNDEndOfProcess", 0, 0 };
    static const QUMethod slot_50 = {"slotGetMomsKonto", 0, 0 };
    static const QUMethod slot_51 = {"slotGetMomsKtoEndOfProcess", 0, 0 };
    static const QUMethod slot_52 = {"slotGetLevLista", 0, 0 };
    static const QUMethod slot_53 = {"slotGetLevlistaEndOfProcess", 0, 0 };
    static const QUParameter param_slot_54[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_54 = {"slotPickupLevnr", 1, param_slot_54 };
    static const QUMethod slot_55 = {"slotGetKontoLista", 0, 0 };
    static const QUMethod slot_56 = {"slotKTOVIEWEndOfProcess", 0, 0 };
    static const QUParameter param_slot_57[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_57 = {"slotPickupKtonr", 1, param_slot_57 };
    static const QUMethod slot_58 = {"slotGetAutokonto", 0, 0 };
    static const QUMethod slot_59 = {"slotGetAutokontoEndOfProcess", 0, 0 };
    static const QUMethod slot_60 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotlineEditLevNr_returnPressed()", &slot_0, QMetaData::Public },
	{ "slotlineEditLevKundNr_returnPressed()", &slot_1, QMetaData::Public },
	{ "slotlineEditRegDatum_returnPressed()", &slot_2, QMetaData::Public },
	{ "slotlineEditFaktNr_returnPressed()", &slot_3, QMetaData::Public },
	{ "slotlineEditFakturadatum_returnPressed()", &slot_4, QMetaData::Public },
	{ "slotlineEditBetvilk_returnPressed()", &slot_5, QMetaData::Public },
	{ "slotlineEditLevBetDatum_returnPressed()", &slot_6, QMetaData::Public },
	{ "slotlineEditOCRnr_returnPressed()", &slot_7, QMetaData::Public },
	{ "slotlineEditLevFakturaText_returnPressed()", &slot_8, QMetaData::Public },
	{ "slotlineEditBar_returnPressed()", &slot_9, QMetaData::Public },
	{ "slotlineEditLevMomskod_returnPressed()", &slot_10, QMetaData::Public },
	{ "slotlineEditValuta_returnPressed()", &slot_11, QMetaData::Public },
	{ "slotlineEditValutaKurs_returnPressed()", &slot_12, QMetaData::Public },
	{ "slotlineEditFaktBelopp_returnPressed()", &slot_13, QMetaData::Public },
	{ "slotlineEditKreditKontoNr_returnPressed()", &slot_14, QMetaData::Public },
	{ "slotlineEditKreditBelopp_returnPressed()", &slot_15, QMetaData::Public },
	{ "slotlineEditMomsKtoNr_returnPressed()", &slot_16, QMetaData::Public },
	{ "slotlineEditMomsBelopp_returnPressed()", &slot_17, QMetaData::Public },
	{ "slotlineEditDebetKontoNr_returnPressed()", &slot_18, QMetaData::Public },
	{ "slotlineEditDebetBelopp_returnPressed()", &slot_19, QMetaData::Public },
	{ "checkSemafor()", &slot_20, QMetaData::Public },
	{ "slotGetLev()", &slot_21, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_22, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_23, QMetaData::Public },
	{ "slotEndOfGetProcess()", &slot_24, QMetaData::Public },
	{ "slotCheckBar()", &slot_25, QMetaData::Public },
	{ "slotBARCHKEndOfProcess()", &slot_26, QMetaData::Public },
	{ "slotCheckKontoNr(QString)", &slot_27, QMetaData::Public },
	{ "slotKTOCHKEndOfProcess()", &slot_28, QMetaData::Public },
	{ "slotGetMoms(QString)", &slot_29, QMetaData::Public },
	{ "slotFTGDSPEndOfProcess()", &slot_30, QMetaData::Public },
	{ "slotUpdateLevresk()", &slot_31, QMetaData::Public },
	{ "slotLEVRESKEndOfProcess()", &slot_32, QMetaData::Public },
	{ "slotGetNextVernr()", &slot_33, QMetaData::Public },
	{ "slotBARDSPEndOfProcess()", &slot_34, QMetaData::Public },
	{ "slotSaveVerHuvud()", &slot_35, QMetaData::Public },
	{ "slotSaveVerRad(QString,QString,QString)", &slot_36, QMetaData::Public },
	{ "slotWRRECEndOfProcess()", &slot_37, QMetaData::Public },
	{ "slotUppdateraVer()", &slot_38, QMetaData::Public },
	{ "slotVERUPDEndOfProcess()", &slot_39, QMetaData::Public },
	{ "slotVerRemove()", &slot_40, QMetaData::Public },
	{ "slotClearVariabler()", &slot_41, QMetaData::Public },
	{ "slotGetValuta()", &slot_42, QMetaData::Public },
	{ "slotVALDSPEndOfProcess()", &slot_43, QMetaData::Public },
	{ "slotGetBetvilkor(QString)", &slot_44, QMetaData::Public },
	{ "slotBETDSPDataOnStdout()", &slot_45, QMetaData::Public },
	{ "slotBETDSPEndOfProcess()", &slot_46, QMetaData::Public },
	{ "slotFindBar(QString)", &slot_47, QMetaData::Public },
	{ "slotBARFNDDataOnStdout()", &slot_48, QMetaData::Public },
	{ "slotBARFNDEndOfProcess()", &slot_49, QMetaData::Public },
	{ "slotGetMomsKonto()", &slot_50, QMetaData::Public },
	{ "slotGetMomsKtoEndOfProcess()", &slot_51, QMetaData::Public },
	{ "slotGetLevLista()", &slot_52, QMetaData::Public },
	{ "slotGetLevlistaEndOfProcess()", &slot_53, QMetaData::Public },
	{ "slotPickupLevnr(QListViewItem*)", &slot_54, QMetaData::Public },
	{ "slotGetKontoLista()", &slot_55, QMetaData::Public },
	{ "slotKTOVIEWEndOfProcess()", &slot_56, QMetaData::Public },
	{ "slotPickupKtonr(QListViewItem*)", &slot_57, QMetaData::Public },
	{ "slotGetAutokonto()", &slot_58, QMetaData::Public },
	{ "slotGetAutokontoEndOfProcess()", &slot_59, QMetaData::Public },
	{ "languageChange()", &slot_60, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmLevFakt", parentObject,
	slot_tbl, 61,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmLevFakt.setMetaObject( metaObj );
    return metaObj;
}

void* frmLevFakt::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmLevFakt" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmLevFakt::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotlineEditLevNr_returnPressed(); break;
    case 1: slotlineEditLevKundNr_returnPressed(); break;
    case 2: slotlineEditRegDatum_returnPressed(); break;
    case 3: slotlineEditFaktNr_returnPressed(); break;
    case 4: slotlineEditFakturadatum_returnPressed(); break;
    case 5: slotlineEditBetvilk_returnPressed(); break;
    case 6: slotlineEditLevBetDatum_returnPressed(); break;
    case 7: slotlineEditOCRnr_returnPressed(); break;
    case 8: slotlineEditLevFakturaText_returnPressed(); break;
    case 9: slotlineEditBar_returnPressed(); break;
    case 10: slotlineEditLevMomskod_returnPressed(); break;
    case 11: slotlineEditValuta_returnPressed(); break;
    case 12: slotlineEditValutaKurs_returnPressed(); break;
    case 13: slotlineEditFaktBelopp_returnPressed(); break;
    case 14: slotlineEditKreditKontoNr_returnPressed(); break;
    case 15: slotlineEditKreditBelopp_returnPressed(); break;
    case 16: slotlineEditMomsKtoNr_returnPressed(); break;
    case 17: slotlineEditMomsBelopp_returnPressed(); break;
    case 18: slotlineEditDebetKontoNr_returnPressed(); break;
    case 19: slotlineEditDebetBelopp_returnPressed(); break;
    case 20: checkSemafor(); break;
    case 21: slotGetLev(); break;
    case 22: slotDataOnStdout(); break;
    case 23: slotDataOnStderr(); break;
    case 24: slotEndOfGetProcess(); break;
    case 25: slotCheckBar(); break;
    case 26: slotBARCHKEndOfProcess(); break;
    case 27: slotCheckKontoNr((QString)static_QUType_QString.get(_o+1)); break;
    case 28: slotKTOCHKEndOfProcess(); break;
    case 29: slotGetMoms((QString)static_QUType_QString.get(_o+1)); break;
    case 30: slotFTGDSPEndOfProcess(); break;
    case 31: slotUpdateLevresk(); break;
    case 32: slotLEVRESKEndOfProcess(); break;
    case 33: slotGetNextVernr(); break;
    case 34: slotBARDSPEndOfProcess(); break;
    case 35: slotSaveVerHuvud(); break;
    case 36: slotSaveVerRad((QString)static_QUType_QString.get(_o+1),(QString)static_QUType_QString.get(_o+2),(QString)static_QUType_QString.get(_o+3)); break;
    case 37: slotWRRECEndOfProcess(); break;
    case 38: slotUppdateraVer(); break;
    case 39: slotVERUPDEndOfProcess(); break;
    case 40: slotVerRemove(); break;
    case 41: slotClearVariabler(); break;
    case 42: slotGetValuta(); break;
    case 43: slotVALDSPEndOfProcess(); break;
    case 44: slotGetBetvilkor((QString)static_QUType_QString.get(_o+1)); break;
    case 45: slotBETDSPDataOnStdout(); break;
    case 46: slotBETDSPEndOfProcess(); break;
    case 47: slotFindBar((QString)static_QUType_QString.get(_o+1)); break;
    case 48: slotBARFNDDataOnStdout(); break;
    case 49: slotBARFNDEndOfProcess(); break;
    case 50: slotGetMomsKonto(); break;
    case 51: slotGetMomsKtoEndOfProcess(); break;
    case 52: slotGetLevLista(); break;
    case 53: slotGetLevlistaEndOfProcess(); break;
    case 54: slotPickupLevnr((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 55: slotGetKontoLista(); break;
    case 56: slotKTOVIEWEndOfProcess(); break;
    case 57: slotPickupKtonr((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 58: slotGetAutokonto(); break;
    case 59: slotGetAutokontoEndOfProcess(); break;
    case 60: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmLevFakt::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmLevFakt::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmLevFakt::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
