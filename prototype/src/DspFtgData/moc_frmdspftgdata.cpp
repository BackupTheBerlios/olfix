/****************************************************************************
** frmDspFtgData meta object code from reading C++ file 'frmdspftgdata.h'
**
** Created: Fri Aug 15 11:09:32 2003
**      by: The Qt MOC ($Id: moc_frmdspftgdata.cpp,v 1.2 2003/09/28 07:49:24 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmdspftgdata.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmDspFtgData::className() const
{
    return "frmDspFtgData";
}

QMetaObject *frmDspFtgData::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmDspFtgData( "frmDspFtgData", &frmDspFtgData::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmDspFtgData::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspFtgData", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmDspFtgData::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspFtgData", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmDspFtgData::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "posttyp", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"slotGetFtgData", 1, param_slot_1 };
    static const QUMethod slot_2 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_3 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_4 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_5 = {"slotGetFNAMN", 0, 0 };
    static const QUMethod slot_6 = {"slotGetADR1", 0, 0 };
    static const QUMethod slot_7 = {"slotGetADR2", 0, 0 };
    static const QUMethod slot_8 = {"slotGetADR3", 0, 0 };
    static const QUMethod slot_9 = {"slotGetADR4", 0, 0 };
    static const QUMethod slot_10 = {"slotGetADR5", 0, 0 };
    static const QUMethod slot_11 = {"slotGetADR6", 0, 0 };
    static const QUMethod slot_12 = {"slotGetADR7", 0, 0 };
    static const QUMethod slot_13 = {"slotGetADR8", 0, 0 };
    static const QUMethod slot_14 = {"slotGetADR9", 0, 0 };
    static const QUMethod slot_15 = {"slotGetFTGNR", 0, 0 };
    static const QUMethod slot_16 = {"slotGetTFN1", 0, 0 };
    static const QUMethod slot_17 = {"slotGetTFN2", 0, 0 };
    static const QUMethod slot_18 = {"slotGetTFAX", 0, 0 };
    static const QUMethod slot_19 = {"slotGetEML1", 0, 0 };
    static const QUMethod slot_20 = {"slotGetMOMS1", 0, 0 };
    static const QUMethod slot_21 = {"slotGetMOMS2", 0, 0 };
    static const QUMethod slot_22 = {"slotGetMOMS3", 0, 0 };
    static const QUMethod slot_23 = {"slotGetMOMS4", 0, 0 };
    static const QUMethod slot_24 = {"slotGetMOMS5", 0, 0 };
    static const QUMethod slot_25 = {"slotGetMOMSI", 0, 0 };
    static const QUMethod slot_26 = {"slotGetMOMSU", 0, 0 };
    static const QUMethod slot_27 = {"slotGetAUTOK", 0, 0 };
    static const QUMethod slot_28 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotGetFtgData(QString)", &slot_1, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_2, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_3, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_4, QMetaData::Public },
	{ "slotGetFNAMN()", &slot_5, QMetaData::Public },
	{ "slotGetADR1()", &slot_6, QMetaData::Public },
	{ "slotGetADR2()", &slot_7, QMetaData::Public },
	{ "slotGetADR3()", &slot_8, QMetaData::Public },
	{ "slotGetADR4()", &slot_9, QMetaData::Public },
	{ "slotGetADR5()", &slot_10, QMetaData::Public },
	{ "slotGetADR6()", &slot_11, QMetaData::Public },
	{ "slotGetADR7()", &slot_12, QMetaData::Public },
	{ "slotGetADR8()", &slot_13, QMetaData::Public },
	{ "slotGetADR9()", &slot_14, QMetaData::Public },
	{ "slotGetFTGNR()", &slot_15, QMetaData::Public },
	{ "slotGetTFN1()", &slot_16, QMetaData::Public },
	{ "slotGetTFN2()", &slot_17, QMetaData::Public },
	{ "slotGetTFAX()", &slot_18, QMetaData::Public },
	{ "slotGetEML1()", &slot_19, QMetaData::Public },
	{ "slotGetMOMS1()", &slot_20, QMetaData::Public },
	{ "slotGetMOMS2()", &slot_21, QMetaData::Public },
	{ "slotGetMOMS3()", &slot_22, QMetaData::Public },
	{ "slotGetMOMS4()", &slot_23, QMetaData::Public },
	{ "slotGetMOMS5()", &slot_24, QMetaData::Public },
	{ "slotGetMOMSI()", &slot_25, QMetaData::Public },
	{ "slotGetMOMSU()", &slot_26, QMetaData::Public },
	{ "slotGetAUTOK()", &slot_27, QMetaData::Public },
	{ "languageChange()", &slot_28, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmDspFtgData", parentObject,
	slot_tbl, 29,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmDspFtgData.setMetaObject( metaObj );
    return metaObj;
}

void* frmDspFtgData::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmDspFtgData" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmDspFtgData::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotGetFtgData((QString)static_QUType_QString.get(_o+1)); break;
    case 2: slotDataOnStdout(); break;
    case 3: slotDataOnStderr(); break;
    case 4: slotEndOfProcess(); break;
    case 5: slotGetFNAMN(); break;
    case 6: slotGetADR1(); break;
    case 7: slotGetADR2(); break;
    case 8: slotGetADR3(); break;
    case 9: slotGetADR4(); break;
    case 10: slotGetADR5(); break;
    case 11: slotGetADR6(); break;
    case 12: slotGetADR7(); break;
    case 13: slotGetADR8(); break;
    case 14: slotGetADR9(); break;
    case 15: slotGetFTGNR(); break;
    case 16: slotGetTFN1(); break;
    case 17: slotGetTFN2(); break;
    case 18: slotGetTFAX(); break;
    case 19: slotGetEML1(); break;
    case 20: slotGetMOMS1(); break;
    case 21: slotGetMOMS2(); break;
    case 22: slotGetMOMS3(); break;
    case 23: slotGetMOMS4(); break;
    case 24: slotGetMOMS5(); break;
    case 25: slotGetMOMSI(); break;
    case 26: slotGetMOMSU(); break;
    case 27: slotGetAUTOK(); break;
    case 28: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmDspFtgData::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmDspFtgData::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmDspFtgData::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
