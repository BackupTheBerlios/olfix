/****************************************************************************
** frmChgFtgData meta object code from reading C++ file 'frmchgftgdata.h'
**
** Created: Thu Aug 14 09:36:54 2003
**      by: The Qt MOC ($Id: moc_frmchgftgdata.cpp,v 1.2 2003/09/28 06:40:16 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmchgftgdata.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmChgFtgData::className() const
{
    return "frmChgFtgData";
}

QMetaObject *frmChgFtgData::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmChgFtgData( "frmChgFtgData", &frmChgFtgData::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmChgFtgData::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgFtgData", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmChgFtgData::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgFtgData", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmChgFtgData::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotGetPosttyp", 0, 0 };
    static const QUMethod slot_2 = {"PushButtonGet_clicked", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ "posttyp", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"slotGetFtgData", 1, param_slot_3 };
    static const QUMethod slot_4 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_5 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_6 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_7 = {"slotGetADR1", 0, 0 };
    static const QUMethod slot_8 = {"slotLineEditAdr1_FtgNamn_returnPressed", 0, 0 };
    static const QUMethod slot_9 = {"slotLineEditAdr1_PostAdr_returnPressed", 0, 0 };
    static const QUMethod slot_10 = {"slotLineEditAdr1_PostNr_returnPressed", 0, 0 };
    static const QUMethod slot_11 = {"slotLineEditAdr1_Ort_returnPressed", 0, 0 };
    static const QUMethod slot_12 = {"slotGetADR4", 0, 0 };
    static const QUMethod slot_13 = {"slotLineEditAdr2_BesokAdr_returnPressed", 0, 0 };
    static const QUMethod slot_14 = {"slotLineEditAdr2_PostNr_returnPressed", 0, 0 };
    static const QUMethod slot_15 = {"slotLineEditAdr2_Ort_returnPressed", 0, 0 };
    static const QUMethod slot_16 = {"slotGetADR7", 0, 0 };
    static const QUMethod slot_17 = {"slotLineEditAdr3_GodsAdr_returnPressed", 0, 0 };
    static const QUMethod slot_18 = {"slotLineEditAdr3_PostNr_returnPressed", 0, 0 };
    static const QUMethod slot_19 = {"slotLineEditAdr3_Ort_returnPressed", 0, 0 };
    static const QUMethod slot_20 = {"slotGetFNAMN", 0, 0 };
    static const QUMethod slot_21 = {"slotLineEditFnamn_returnPressed", 0, 0 };
    static const QUMethod slot_22 = {"slotGetFTGNR", 0, 0 };
    static const QUMethod slot_23 = {"slotLineEditFtgnr_returnPressed", 0, 0 };
    static const QUMethod slot_24 = {"slotGetTFN1", 0, 0 };
    static const QUMethod slot_25 = {"slotLineEditTfnnr1_returnPressed", 0, 0 };
    static const QUMethod slot_26 = {"slotGetTFN2", 0, 0 };
    static const QUMethod slot_27 = {"slotLineEditTfnnr2_returnPressed", 0, 0 };
    static const QUMethod slot_28 = {"slotGetTFAX", 0, 0 };
    static const QUMethod slot_29 = {"slotLineEditTelefax_returnPressed", 0, 0 };
    static const QUMethod slot_30 = {"slotGetEML1", 0, 0 };
    static const QUMethod slot_31 = {"slotLineEditEmail_returnPressed", 0, 0 };
    static const QUMethod slot_32 = {"slotGetMOMS1", 0, 0 };
    static const QUMethod slot_33 = {"slotLineEditMoms1_returnPressed", 0, 0 };
    static const QUMethod slot_34 = {"slotGetMOMS2", 0, 0 };
    static const QUMethod slot_35 = {"slotLineEditMoms2_returnPressed", 0, 0 };
    static const QUMethod slot_36 = {"slotGetMOMS3", 0, 0 };
    static const QUMethod slot_37 = {"slotLineEditMoms3_returnPressed", 0, 0 };
    static const QUMethod slot_38 = {"slotGetBVLK1", 0, 0 };
    static const QUMethod slot_39 = {"slotLineEditBetvilk1_returnPressed", 0, 0 };
    static const QUMethod slot_40 = {"slotGetBVLK2", 0, 0 };
    static const QUMethod slot_41 = {"slotLineEditBetvilk2_returnPressed", 0, 0 };
    static const QUMethod slot_42 = {"slotGetBVLK3", 0, 0 };
    static const QUMethod slot_43 = {"slotLineEditBetvilk3_returnPressed", 0, 0 };
    static const QUMethod slot_44 = {"slotGetPosttyper", 0, 0 };
    static const QUMethod slot_45 = {"slotGetPostEndOfProcess", 0, 0 };
    static const QUParameter param_slot_46[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_46 = {"ListView1_clicked", 1, param_slot_46 };
    static const QUParameter param_slot_47[] = {
	{ "posttyp", &static_QUType_QString, 0, QUParameter::In },
	{ "ftgdata", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_47 = {"slotUpdFtgData", 2, param_slot_47 };
    static const QUMethod slot_48 = {"slotUpdateEndOfProcess", 0, 0 };
    static const QUMethod slot_49 = {"PushButtonUpdate_clicked", 0, 0 };
    static const QUMethod slot_50 = {"slotGetAUTOK", 0, 0 };
    static const QUMethod slot_51 = {"slotLineEditAutokonto_returnPressed", 0, 0 };
    static const QUMethod slot_52 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotGetPosttyp()", &slot_1, QMetaData::Public },
	{ "PushButtonGet_clicked()", &slot_2, QMetaData::Public },
	{ "slotGetFtgData(QString)", &slot_3, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_4, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_5, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_6, QMetaData::Public },
	{ "slotGetADR1()", &slot_7, QMetaData::Public },
	{ "slotLineEditAdr1_FtgNamn_returnPressed()", &slot_8, QMetaData::Public },
	{ "slotLineEditAdr1_PostAdr_returnPressed()", &slot_9, QMetaData::Public },
	{ "slotLineEditAdr1_PostNr_returnPressed()", &slot_10, QMetaData::Public },
	{ "slotLineEditAdr1_Ort_returnPressed()", &slot_11, QMetaData::Public },
	{ "slotGetADR4()", &slot_12, QMetaData::Public },
	{ "slotLineEditAdr2_BesokAdr_returnPressed()", &slot_13, QMetaData::Public },
	{ "slotLineEditAdr2_PostNr_returnPressed()", &slot_14, QMetaData::Public },
	{ "slotLineEditAdr2_Ort_returnPressed()", &slot_15, QMetaData::Public },
	{ "slotGetADR7()", &slot_16, QMetaData::Public },
	{ "slotLineEditAdr3_GodsAdr_returnPressed()", &slot_17, QMetaData::Public },
	{ "slotLineEditAdr3_PostNr_returnPressed()", &slot_18, QMetaData::Public },
	{ "slotLineEditAdr3_Ort_returnPressed()", &slot_19, QMetaData::Public },
	{ "slotGetFNAMN()", &slot_20, QMetaData::Public },
	{ "slotLineEditFnamn_returnPressed()", &slot_21, QMetaData::Public },
	{ "slotGetFTGNR()", &slot_22, QMetaData::Public },
	{ "slotLineEditFtgnr_returnPressed()", &slot_23, QMetaData::Public },
	{ "slotGetTFN1()", &slot_24, QMetaData::Public },
	{ "slotLineEditTfnnr1_returnPressed()", &slot_25, QMetaData::Public },
	{ "slotGetTFN2()", &slot_26, QMetaData::Public },
	{ "slotLineEditTfnnr2_returnPressed()", &slot_27, QMetaData::Public },
	{ "slotGetTFAX()", &slot_28, QMetaData::Public },
	{ "slotLineEditTelefax_returnPressed()", &slot_29, QMetaData::Public },
	{ "slotGetEML1()", &slot_30, QMetaData::Public },
	{ "slotLineEditEmail_returnPressed()", &slot_31, QMetaData::Public },
	{ "slotGetMOMS1()", &slot_32, QMetaData::Public },
	{ "slotLineEditMoms1_returnPressed()", &slot_33, QMetaData::Public },
	{ "slotGetMOMS2()", &slot_34, QMetaData::Public },
	{ "slotLineEditMoms2_returnPressed()", &slot_35, QMetaData::Public },
	{ "slotGetMOMS3()", &slot_36, QMetaData::Public },
	{ "slotLineEditMoms3_returnPressed()", &slot_37, QMetaData::Public },
	{ "slotGetBVLK1()", &slot_38, QMetaData::Public },
	{ "slotLineEditBetvilk1_returnPressed()", &slot_39, QMetaData::Public },
	{ "slotGetBVLK2()", &slot_40, QMetaData::Public },
	{ "slotLineEditBetvilk2_returnPressed()", &slot_41, QMetaData::Public },
	{ "slotGetBVLK3()", &slot_42, QMetaData::Public },
	{ "slotLineEditBetvilk3_returnPressed()", &slot_43, QMetaData::Public },
	{ "slotGetPosttyper()", &slot_44, QMetaData::Public },
	{ "slotGetPostEndOfProcess()", &slot_45, QMetaData::Public },
	{ "ListView1_clicked(QListViewItem*)", &slot_46, QMetaData::Public },
	{ "slotUpdFtgData(QString,QString)", &slot_47, QMetaData::Public },
	{ "slotUpdateEndOfProcess()", &slot_48, QMetaData::Public },
	{ "PushButtonUpdate_clicked()", &slot_49, QMetaData::Public },
	{ "slotGetAUTOK()", &slot_50, QMetaData::Public },
	{ "slotLineEditAutokonto_returnPressed()", &slot_51, QMetaData::Public },
	{ "languageChange()", &slot_52, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmChgFtgData", parentObject,
	slot_tbl, 53,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmChgFtgData.setMetaObject( metaObj );
    return metaObj;
}

void* frmChgFtgData::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmChgFtgData" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmChgFtgData::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotGetPosttyp(); break;
    case 2: PushButtonGet_clicked(); break;
    case 3: slotGetFtgData((QString)static_QUType_QString.get(_o+1)); break;
    case 4: slotDataOnStdout(); break;
    case 5: slotDataOnStderr(); break;
    case 6: slotEndOfProcess(); break;
    case 7: slotGetADR1(); break;
    case 8: slotLineEditAdr1_FtgNamn_returnPressed(); break;
    case 9: slotLineEditAdr1_PostAdr_returnPressed(); break;
    case 10: slotLineEditAdr1_PostNr_returnPressed(); break;
    case 11: slotLineEditAdr1_Ort_returnPressed(); break;
    case 12: slotGetADR4(); break;
    case 13: slotLineEditAdr2_BesokAdr_returnPressed(); break;
    case 14: slotLineEditAdr2_PostNr_returnPressed(); break;
    case 15: slotLineEditAdr2_Ort_returnPressed(); break;
    case 16: slotGetADR7(); break;
    case 17: slotLineEditAdr3_GodsAdr_returnPressed(); break;
    case 18: slotLineEditAdr3_PostNr_returnPressed(); break;
    case 19: slotLineEditAdr3_Ort_returnPressed(); break;
    case 20: slotGetFNAMN(); break;
    case 21: slotLineEditFnamn_returnPressed(); break;
    case 22: slotGetFTGNR(); break;
    case 23: slotLineEditFtgnr_returnPressed(); break;
    case 24: slotGetTFN1(); break;
    case 25: slotLineEditTfnnr1_returnPressed(); break;
    case 26: slotGetTFN2(); break;
    case 27: slotLineEditTfnnr2_returnPressed(); break;
    case 28: slotGetTFAX(); break;
    case 29: slotLineEditTelefax_returnPressed(); break;
    case 30: slotGetEML1(); break;
    case 31: slotLineEditEmail_returnPressed(); break;
    case 32: slotGetMOMS1(); break;
    case 33: slotLineEditMoms1_returnPressed(); break;
    case 34: slotGetMOMS2(); break;
    case 35: slotLineEditMoms2_returnPressed(); break;
    case 36: slotGetMOMS3(); break;
    case 37: slotLineEditMoms3_returnPressed(); break;
    case 38: slotGetBVLK1(); break;
    case 39: slotLineEditBetvilk1_returnPressed(); break;
    case 40: slotGetBVLK2(); break;
    case 41: slotLineEditBetvilk2_returnPressed(); break;
    case 42: slotGetBVLK3(); break;
    case 43: slotLineEditBetvilk3_returnPressed(); break;
    case 44: slotGetPosttyper(); break;
    case 45: slotGetPostEndOfProcess(); break;
    case 46: ListView1_clicked((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 47: slotUpdFtgData((QString)static_QUType_QString.get(_o+1),(QString)static_QUType_QString.get(_o+2)); break;
    case 48: slotUpdateEndOfProcess(); break;
    case 49: PushButtonUpdate_clicked(); break;
    case 50: slotGetAUTOK(); break;
    case 51: slotLineEditAutokonto_returnPressed(); break;
    case 52: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmChgFtgData::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmChgFtgData::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmChgFtgData::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
