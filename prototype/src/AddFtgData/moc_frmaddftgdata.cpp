/****************************************************************************
** frmAddFtgData meta object code from reading C++ file 'frmaddftgdata.h'
**
** Created: Sat Aug 16 05:44:41 2003
**      by: The Qt MOC ($Id: moc_frmaddftgdata.cpp,v 1.1 2003/09/28 09:00:14 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddftgdata.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddFtgData::className() const
{
    return "frmAddFtgData";
}

QMetaObject *frmAddFtgData::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddFtgData( "frmAddFtgData", &frmAddFtgData::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmAddFtgData::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddFtgData", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddFtgData::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddFtgData", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddFtgData::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotLineEditFtgNamn_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"slotLineEditFtgNr_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"slotLineEditPostAdress_returnPressed", 0, 0 };
    static const QUMethod slot_4 = {"slotLineEditPostnr1_returnPressed", 0, 0 };
    static const QUMethod slot_5 = {"slotLineEditPostOrt_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"slotLineEditBesoksAdress_returnPressed", 0, 0 };
    static const QUMethod slot_7 = {"slotLineEditPostnr2_returnPressed", 0, 0 };
    static const QUMethod slot_8 = {"slotLineEditBesoksOrt_returnPressed", 0, 0 };
    static const QUMethod slot_9 = {"slotLineEditGodsAdress_returnPressed", 0, 0 };
    static const QUMethod slot_10 = {"slotLineEditPostnr3_returnPressed", 0, 0 };
    static const QUMethod slot_11 = {"slotLineEditGodsOrt_returnPressed", 0, 0 };
    static const QUMethod slot_12 = {"slotLineEditTfnnr_returnPressed", 0, 0 };
    static const QUMethod slot_13 = {"slotLineEditMobilTfn_returnPressed", 0, 0 };
    static const QUMethod slot_14 = {"slotLineEditTelefax_returnPressed", 0, 0 };
    static const QUMethod slot_15 = {"slotLineEditemailadress_returnPressed", 0, 0 };
    static const QUMethod slot_16 = {"slotLineEditTelex_returnPressed", 0, 0 };
    static const QUMethod slot_17 = {"slotLineEditMoms1_returnPressed", 0, 0 };
    static const QUMethod slot_18 = {"slotLineEditMoms2_returnPresse", 0, 0 };
    static const QUMethod slot_19 = {"slotLineEditMoms3_returnPressed", 0, 0 };
    static const QUMethod slot_20 = {"slotLineEditMoms4_returnPressed", 0, 0 };
    static const QUMethod slot_21 = {"slotLineEditMoms5_returnPressed", 0, 0 };
    static const QUMethod slot_22 = {"slotlineEditMomsKtoIng_returnPressed", 0, 0 };
    static const QUMethod slot_23 = {"slotlineEditMomsKtoUtg_returnPressed", 0, 0 };
    static const QUMethod slot_24 = {"slotlineEditAutokonto_returnPressed", 0, 0 };
    static const QUMethod slot_25 = {"slotPushButtonOK_clicked", 0, 0 };
    static const QUParameter param_slot_26[] = {
	{ "posttyp", &static_QUType_QString, 0, QUParameter::In },
	{ "ftgdata", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_26 = {"slotUpdateFtgdata", 2, param_slot_26 };
    static const QUMethod slot_27 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_28 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_29 = {"slotUpdateEndOfProcess", 0, 0 };
    static const QUMethod slot_30 = {"slotGetFtgdata", 0, 0 };
    static const QUMethod slot_31 = {"slotGetEndOfProcess", 0, 0 };
    static const QUMethod slot_32 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotLineEditFtgNamn_returnPressed()", &slot_1, QMetaData::Public },
	{ "slotLineEditFtgNr_returnPressed()", &slot_2, QMetaData::Public },
	{ "slotLineEditPostAdress_returnPressed()", &slot_3, QMetaData::Public },
	{ "slotLineEditPostnr1_returnPressed()", &slot_4, QMetaData::Public },
	{ "slotLineEditPostOrt_returnPressed()", &slot_5, QMetaData::Public },
	{ "slotLineEditBesoksAdress_returnPressed()", &slot_6, QMetaData::Public },
	{ "slotLineEditPostnr2_returnPressed()", &slot_7, QMetaData::Public },
	{ "slotLineEditBesoksOrt_returnPressed()", &slot_8, QMetaData::Public },
	{ "slotLineEditGodsAdress_returnPressed()", &slot_9, QMetaData::Public },
	{ "slotLineEditPostnr3_returnPressed()", &slot_10, QMetaData::Public },
	{ "slotLineEditGodsOrt_returnPressed()", &slot_11, QMetaData::Public },
	{ "slotLineEditTfnnr_returnPressed()", &slot_12, QMetaData::Public },
	{ "slotLineEditMobilTfn_returnPressed()", &slot_13, QMetaData::Public },
	{ "slotLineEditTelefax_returnPressed()", &slot_14, QMetaData::Public },
	{ "slotLineEditemailadress_returnPressed()", &slot_15, QMetaData::Public },
	{ "slotLineEditTelex_returnPressed()", &slot_16, QMetaData::Public },
	{ "slotLineEditMoms1_returnPressed()", &slot_17, QMetaData::Public },
	{ "slotLineEditMoms2_returnPresse()", &slot_18, QMetaData::Public },
	{ "slotLineEditMoms3_returnPressed()", &slot_19, QMetaData::Public },
	{ "slotLineEditMoms4_returnPressed()", &slot_20, QMetaData::Public },
	{ "slotLineEditMoms5_returnPressed()", &slot_21, QMetaData::Public },
	{ "slotlineEditMomsKtoIng_returnPressed()", &slot_22, QMetaData::Public },
	{ "slotlineEditMomsKtoUtg_returnPressed()", &slot_23, QMetaData::Public },
	{ "slotlineEditAutokonto_returnPressed()", &slot_24, QMetaData::Public },
	{ "slotPushButtonOK_clicked()", &slot_25, QMetaData::Public },
	{ "slotUpdateFtgdata(QString,QString)", &slot_26, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_27, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_28, QMetaData::Public },
	{ "slotUpdateEndOfProcess()", &slot_29, QMetaData::Public },
	{ "slotGetFtgdata()", &slot_30, QMetaData::Public },
	{ "slotGetEndOfProcess()", &slot_31, QMetaData::Public },
	{ "languageChange()", &slot_32, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddFtgData", parentObject,
	slot_tbl, 33,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddFtgData.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddFtgData::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddFtgData" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmAddFtgData::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotLineEditFtgNamn_returnPressed(); break;
    case 2: slotLineEditFtgNr_returnPressed(); break;
    case 3: slotLineEditPostAdress_returnPressed(); break;
    case 4: slotLineEditPostnr1_returnPressed(); break;
    case 5: slotLineEditPostOrt_returnPressed(); break;
    case 6: slotLineEditBesoksAdress_returnPressed(); break;
    case 7: slotLineEditPostnr2_returnPressed(); break;
    case 8: slotLineEditBesoksOrt_returnPressed(); break;
    case 9: slotLineEditGodsAdress_returnPressed(); break;
    case 10: slotLineEditPostnr3_returnPressed(); break;
    case 11: slotLineEditGodsOrt_returnPressed(); break;
    case 12: slotLineEditTfnnr_returnPressed(); break;
    case 13: slotLineEditMobilTfn_returnPressed(); break;
    case 14: slotLineEditTelefax_returnPressed(); break;
    case 15: slotLineEditemailadress_returnPressed(); break;
    case 16: slotLineEditTelex_returnPressed(); break;
    case 17: slotLineEditMoms1_returnPressed(); break;
    case 18: slotLineEditMoms2_returnPresse(); break;
    case 19: slotLineEditMoms3_returnPressed(); break;
    case 20: slotLineEditMoms4_returnPressed(); break;
    case 21: slotLineEditMoms5_returnPressed(); break;
    case 22: slotlineEditMomsKtoIng_returnPressed(); break;
    case 23: slotlineEditMomsKtoUtg_returnPressed(); break;
    case 24: slotlineEditAutokonto_returnPressed(); break;
    case 25: slotPushButtonOK_clicked(); break;
    case 26: slotUpdateFtgdata((QString)static_QUType_QString.get(_o+1),(QString)static_QUType_QString.get(_o+2)); break;
    case 27: slotDataOnStdout(); break;
    case 28: slotDataOnStderr(); break;
    case 29: slotUpdateEndOfProcess(); break;
    case 30: slotGetFtgdata(); break;
    case 31: slotGetEndOfProcess(); break;
    case 32: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddFtgData::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddFtgData::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmAddFtgData::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
