/****************************************************************************
** frmBokfstd meta object code from reading C++ file 'Bokfstd.h'
**
** Created: Wed Aug 13 08:41:46 2003
**      by: The Qt MOC ($Id: moc_Bokfstd.cpp,v 1.2 2003/09/28 06:37:16 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "Bokfstd.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmBokfstd::className() const
{
    return "frmBokfstd";
}

QMetaObject *frmBokfstd::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmBokfstd( "frmBokfstd", &frmBokfstd::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmBokfstd::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmBokfstd", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmBokfstd::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmBokfstd", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmBokfstd::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotLineEditBar_lostFocus", 0, 0 };
    static const QUMethod slot_1 = {"slotLineEditBar_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"slotLineEditVerText_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"slotLineEditKtonr_textChanged", 0, 0 };
    static const QUMethod slot_4 = {"slotLineEditKtonr_lostFocus", 0, 0 };
    static const QUMethod slot_5 = {"slotLineEditKtonr_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"slotLineEditDK_lostFocus", 0, 0 };
    static const QUMethod slot_7 = {"slotLineEditDK_returnPressed", 0, 0 };
    static const QUMethod slot_8 = {"slotLineEditBelopp_returnPressed", 0, 0 };
    static const QUMethod slot_9 = {"slotLineEditKst_returnPressed", 0, 0 };
    static const QUMethod slot_10 = {"slotLineEditSubKto_returnPressed", 0, 0 };
    static const QUMethod slot_11 = {"slotRadOK", 0, 0 };
    static const QUMethod slot_12 = {"slotUpdateRadnr", 0, 0 };
    static const QUParameter param_slot_13[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_13 = {"slotPickupKtonr", 1, param_slot_13 };
    static const QUMethod slot_14 = {"slotGetKontoLista", 0, 0 };
    static const QUMethod slot_15 = {"slotKTOVIEWDataOnStdout", 0, 0 };
    static const QUMethod slot_16 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_17 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_18 = {"slotBARCHKEndOfProcess", 0, 0 };
    static const QUMethod slot_19 = {"slotCheckBar", 0, 0 };
    static const QUMethod slot_20 = {"slotGetNextVernr", 0, 0 };
    static const QUMethod slot_21 = {"slotBARDSPEndOfProcess", 0, 0 };
    static const QUMethod slot_22 = {"slotKTOVIEWEndOfProcess", 0, 0 };
    static const QUMethod slot_23 = {"slotCheckKstalle", 0, 0 };
    static const QUMethod slot_24 = {"slotKSTCHKEndOfProcess", 0, 0 };
    static const QUMethod slot_25 = {"slotCheckKonto", 0, 0 };
    static const QUMethod slot_26 = {"slotKTOCHKEndOfProcess", 0, 0 };
    static const QUMethod slot_27 = {"slotSaveVerHuvud", 0, 0 };
    static const QUMethod slot_28 = {"slotSaveVerRad", 0, 0 };
    static const QUMethod slot_29 = {"slotWRRECEndOfProcess", 0, 0 };
    static const QUMethod slot_30 = {"slotVerOK", 0, 0 };
    static const QUMethod slot_31 = {"slotVerRemove", 0, 0 };
    static const QUMethod slot_32 = {"slotVERUPDEndOfProcess", 0, 0 };
    static const QUMethod slot_33 = {"slotCleanUp", 0, 0 };
    static const QUMethod slot_34 = {"languageChange", 0, 0 };
    static const QUMethod slot_35 = {"init", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotLineEditBar_lostFocus()", &slot_0, QMetaData::Public },
	{ "slotLineEditBar_returnPressed()", &slot_1, QMetaData::Public },
	{ "slotLineEditVerText_returnPressed()", &slot_2, QMetaData::Public },
	{ "slotLineEditKtonr_textChanged()", &slot_3, QMetaData::Public },
	{ "slotLineEditKtonr_lostFocus()", &slot_4, QMetaData::Public },
	{ "slotLineEditKtonr_returnPressed()", &slot_5, QMetaData::Public },
	{ "slotLineEditDK_lostFocus()", &slot_6, QMetaData::Public },
	{ "slotLineEditDK_returnPressed()", &slot_7, QMetaData::Public },
	{ "slotLineEditBelopp_returnPressed()", &slot_8, QMetaData::Public },
	{ "slotLineEditKst_returnPressed()", &slot_9, QMetaData::Public },
	{ "slotLineEditSubKto_returnPressed()", &slot_10, QMetaData::Public },
	{ "slotRadOK()", &slot_11, QMetaData::Public },
	{ "slotUpdateRadnr()", &slot_12, QMetaData::Public },
	{ "slotPickupKtonr(QListViewItem*)", &slot_13, QMetaData::Public },
	{ "slotGetKontoLista()", &slot_14, QMetaData::Public },
	{ "slotKTOVIEWDataOnStdout()", &slot_15, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_16, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_17, QMetaData::Public },
	{ "slotBARCHKEndOfProcess()", &slot_18, QMetaData::Public },
	{ "slotCheckBar()", &slot_19, QMetaData::Public },
	{ "slotGetNextVernr()", &slot_20, QMetaData::Public },
	{ "slotBARDSPEndOfProcess()", &slot_21, QMetaData::Public },
	{ "slotKTOVIEWEndOfProcess()", &slot_22, QMetaData::Public },
	{ "slotCheckKstalle()", &slot_23, QMetaData::Public },
	{ "slotKSTCHKEndOfProcess()", &slot_24, QMetaData::Public },
	{ "slotCheckKonto()", &slot_25, QMetaData::Public },
	{ "slotKTOCHKEndOfProcess()", &slot_26, QMetaData::Public },
	{ "slotSaveVerHuvud()", &slot_27, QMetaData::Public },
	{ "slotSaveVerRad()", &slot_28, QMetaData::Public },
	{ "slotWRRECEndOfProcess()", &slot_29, QMetaData::Public },
	{ "slotVerOK()", &slot_30, QMetaData::Public },
	{ "slotVerRemove()", &slot_31, QMetaData::Public },
	{ "slotVERUPDEndOfProcess()", &slot_32, QMetaData::Public },
	{ "slotCleanUp()", &slot_33, QMetaData::Public },
	{ "languageChange()", &slot_34, QMetaData::Protected },
	{ "init()", &slot_35, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmBokfstd", parentObject,
	slot_tbl, 36,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmBokfstd.setMetaObject( metaObj );
    return metaObj;
}

void* frmBokfstd::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmBokfstd" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmBokfstd::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotLineEditBar_lostFocus(); break;
    case 1: slotLineEditBar_returnPressed(); break;
    case 2: slotLineEditVerText_returnPressed(); break;
    case 3: slotLineEditKtonr_textChanged(); break;
    case 4: slotLineEditKtonr_lostFocus(); break;
    case 5: slotLineEditKtonr_returnPressed(); break;
    case 6: slotLineEditDK_lostFocus(); break;
    case 7: slotLineEditDK_returnPressed(); break;
    case 8: slotLineEditBelopp_returnPressed(); break;
    case 9: slotLineEditKst_returnPressed(); break;
    case 10: slotLineEditSubKto_returnPressed(); break;
    case 11: slotRadOK(); break;
    case 12: slotUpdateRadnr(); break;
    case 13: slotPickupKtonr((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 14: slotGetKontoLista(); break;
    case 15: slotKTOVIEWDataOnStdout(); break;
    case 16: slotDataOnStdout(); break;
    case 17: slotDataOnStderr(); break;
    case 18: slotBARCHKEndOfProcess(); break;
    case 19: slotCheckBar(); break;
    case 20: slotGetNextVernr(); break;
    case 21: slotBARDSPEndOfProcess(); break;
    case 22: slotKTOVIEWEndOfProcess(); break;
    case 23: slotCheckKstalle(); break;
    case 24: slotKSTCHKEndOfProcess(); break;
    case 25: slotCheckKonto(); break;
    case 26: slotKTOCHKEndOfProcess(); break;
    case 27: slotSaveVerHuvud(); break;
    case 28: slotSaveVerRad(); break;
    case 29: slotWRRECEndOfProcess(); break;
    case 30: slotVerOK(); break;
    case 31: slotVerRemove(); break;
    case 32: slotVERUPDEndOfProcess(); break;
    case 33: slotCleanUp(); break;
    case 34: languageChange(); break;
    case 35: init(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmBokfstd::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmBokfstd::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmBokfstd::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
