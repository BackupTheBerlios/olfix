/****************************************************************************
** frmBokfstd meta object code from reading C++ file 'Bokfstd.h'
**
** Created: Thu Mar 20 08:01:59 2003
**      by: The Qt MOC ($Id: moc_Bokfstd.cpp,v 1.1 2003/05/08 08:54:32 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "Bokfstd.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmBokfstd::className() const
{
    return "frmBokfstd";
}

QMetaObject *frmBokfstd::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmBokfstd;

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
    static const QUMethod slot_0 = {"slotLineEditBar_returnPressed", 0, 0 };
    static const QUMethod slot_1 = {"slotLineEditVerText_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"slotLineEditKtonr_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"slotLineEditDK_returnPressed", 0, 0 };
    static const QUMethod slot_4 = {"slotLineEditBelopp_returnPressed", 0, 0 };
    static const QUMethod slot_5 = {"slotLineEditKst_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"slotLineEditSubKto_returnPressed", 0, 0 };
    static const QUMethod slot_7 = {"slotRadOK", 0, 0 };
    static const QUMethod slot_8 = {"slotUpdateRadnr", 0, 0 };
    static const QUParameter param_slot_9[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_9 = {"slotPickupKtonr", 1, param_slot_9 };
    static const QUMethod slot_10 = {"slotGetKontoLista", 0, 0 };
    static const QUMethod slot_11 = {"slotKTOVIEWDataOnStdout", 0, 0 };
    static const QUMethod slot_12 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_13 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_14 = {"slotBARCHKEndOfProcess", 0, 0 };
    static const QUMethod slot_15 = {"slotCheckBar", 0, 0 };
    static const QUMethod slot_16 = {"slotGetNextVernr", 0, 0 };
    static const QUMethod slot_17 = {"slotBARDSPEndOfProcess", 0, 0 };
    static const QUMethod slot_18 = {"slotKTOVIEWEndOfProcess", 0, 0 };
    static const QUMethod slot_19 = {"slotCheckKstalle", 0, 0 };
    static const QUMethod slot_20 = {"slotKSTCHKEndOfProcess", 0, 0 };
    static const QUMethod slot_21 = {"slotCheckKonto", 0, 0 };
    static const QUMethod slot_22 = {"slotKTOCHKEndOfProcess", 0, 0 };
    static const QUMethod slot_23 = {"slotSaveVerHuvud", 0, 0 };
    static const QUMethod slot_24 = {"slotSaveVerRad", 0, 0 };
    static const QUMethod slot_25 = {"slotWRRECEndOfProcess", 0, 0 };
    static const QUMethod slot_26 = {"slotVerOK", 0, 0 };
    static const QUMethod slot_27 = {"slotVerRemove", 0, 0 };
    static const QUMethod slot_28 = {"slotVERUPDEndOfProcess", 0, 0 };
    static const QUMethod slot_29 = {"slotCleanUp", 0, 0 };
    static const QUMethod slot_30 = {"init", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotLineEditBar_returnPressed()", &slot_0, QMetaData::Public },
	{ "slotLineEditVerText_returnPressed()", &slot_1, QMetaData::Public },
	{ "slotLineEditKtonr_returnPressed()", &slot_2, QMetaData::Public },
	{ "slotLineEditDK_returnPressed()", &slot_3, QMetaData::Public },
	{ "slotLineEditBelopp_returnPressed()", &slot_4, QMetaData::Public },
	{ "slotLineEditKst_returnPressed()", &slot_5, QMetaData::Public },
	{ "slotLineEditSubKto_returnPressed()", &slot_6, QMetaData::Public },
	{ "slotRadOK()", &slot_7, QMetaData::Public },
	{ "slotUpdateRadnr()", &slot_8, QMetaData::Public },
	{ "slotPickupKtonr(QListViewItem*)", &slot_9, QMetaData::Public },
	{ "slotGetKontoLista()", &slot_10, QMetaData::Public },
	{ "slotKTOVIEWDataOnStdout()", &slot_11, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_12, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_13, QMetaData::Public },
	{ "slotBARCHKEndOfProcess()", &slot_14, QMetaData::Public },
	{ "slotCheckBar()", &slot_15, QMetaData::Public },
	{ "slotGetNextVernr()", &slot_16, QMetaData::Public },
	{ "slotBARDSPEndOfProcess()", &slot_17, QMetaData::Public },
	{ "slotKTOVIEWEndOfProcess()", &slot_18, QMetaData::Public },
	{ "slotCheckKstalle()", &slot_19, QMetaData::Public },
	{ "slotKSTCHKEndOfProcess()", &slot_20, QMetaData::Public },
	{ "slotCheckKonto()", &slot_21, QMetaData::Public },
	{ "slotKTOCHKEndOfProcess()", &slot_22, QMetaData::Public },
	{ "slotSaveVerHuvud()", &slot_23, QMetaData::Public },
	{ "slotSaveVerRad()", &slot_24, QMetaData::Public },
	{ "slotWRRECEndOfProcess()", &slot_25, QMetaData::Public },
	{ "slotVerOK()", &slot_26, QMetaData::Public },
	{ "slotVerRemove()", &slot_27, QMetaData::Public },
	{ "slotVERUPDEndOfProcess()", &slot_28, QMetaData::Public },
	{ "slotCleanUp()", &slot_29, QMetaData::Public },
	{ "init()", &slot_30, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmBokfstd", parentObject,
	slot_tbl, 31,
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
    if ( !qstrcmp( clname, "frmBokfstd" ) ) return (frmBokfstd*)this;
    return QWidget::qt_cast( clname );
}

bool frmBokfstd::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotLineEditBar_returnPressed(); break;
    case 1: slotLineEditVerText_returnPressed(); break;
    case 2: slotLineEditKtonr_returnPressed(); break;
    case 3: slotLineEditDK_returnPressed(); break;
    case 4: slotLineEditBelopp_returnPressed(); break;
    case 5: slotLineEditKst_returnPressed(); break;
    case 6: slotLineEditSubKto_returnPressed(); break;
    case 7: slotRadOK(); break;
    case 8: slotUpdateRadnr(); break;
    case 9: slotPickupKtonr((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 10: slotGetKontoLista(); break;
    case 11: slotKTOVIEWDataOnStdout(); break;
    case 12: slotDataOnStdout(); break;
    case 13: slotDataOnStderr(); break;
    case 14: slotBARCHKEndOfProcess(); break;
    case 15: slotCheckBar(); break;
    case 16: slotGetNextVernr(); break;
    case 17: slotBARDSPEndOfProcess(); break;
    case 18: slotKTOVIEWEndOfProcess(); break;
    case 19: slotCheckKstalle(); break;
    case 20: slotKSTCHKEndOfProcess(); break;
    case 21: slotCheckKonto(); break;
    case 22: slotKTOCHKEndOfProcess(); break;
    case 23: slotSaveVerHuvud(); break;
    case 24: slotSaveVerRad(); break;
    case 25: slotWRRECEndOfProcess(); break;
    case 26: slotVerOK(); break;
    case 27: slotVerRemove(); break;
    case 28: slotVERUPDEndOfProcess(); break;
    case 29: slotCleanUp(); break;
    case 30: init(); break;
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

bool frmBokfstd::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
