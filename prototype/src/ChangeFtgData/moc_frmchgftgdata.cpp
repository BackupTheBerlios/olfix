/****************************************************************************
** frmChgFtgData meta object code from reading C++ file 'frmchgftgdata.h'
**
** Created: Tue Apr 22 07:09:13 2003
**      by: The Qt MOC ($Id: moc_frmchgftgdata.cpp,v 1.1 2003/05/08 08:55:04 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmchgftgdata.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmChgFtgData::className() const
{
    return "frmChgFtgData";
}

QMetaObject *frmChgFtgData::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmChgFtgData;

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
    static const QUMethod slot_8 = {"slotGetADR2", 0, 0 };
    static const QUMethod slot_9 = {"slotGetADR3", 0, 0 };
    static const QUMethod slot_10 = {"slotGetFTGNR", 0, 0 };
    static const QUMethod slot_11 = {"slotGetTFN1", 0, 0 };
    static const QUMethod slot_12 = {"slotGetTFN2", 0, 0 };
    static const QUMethod slot_13 = {"slotGetTFAX", 0, 0 };
    static const QUMethod slot_14 = {"slotGetEML1", 0, 0 };
    static const QUMethod slot_15 = {"slotGetMOMS1", 0, 0 };
    static const QUMethod slot_16 = {"slotLineEditMoms1_returnPressed", 0, 0 };
    static const QUMethod slot_17 = {"slotGetPosttyper", 0, 0 };
    static const QUMethod slot_18 = {"slotGetPostEndOfProcess", 0, 0 };
    static const QUParameter param_slot_19[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_19 = {"ListView1_clicked", 1, param_slot_19 };
    static const QUParameter param_slot_20[] = {
	{ "posttyp", &static_QUType_QString, 0, QUParameter::In },
	{ "ftgdata", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_20 = {"slotUpdFtgData", 2, param_slot_20 };
    static const QUMethod slot_21 = {"slotUpdateEndOfProcess", 0, 0 };
    static const QUMethod slot_22 = {"PushButtonUpdate_clicked", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotGetPosttyp()", &slot_1, QMetaData::Public },
	{ "PushButtonGet_clicked()", &slot_2, QMetaData::Public },
	{ "slotGetFtgData(QString)", &slot_3, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_4, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_5, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_6, QMetaData::Public },
	{ "slotGetADR1()", &slot_7, QMetaData::Public },
	{ "slotGetADR2()", &slot_8, QMetaData::Public },
	{ "slotGetADR3()", &slot_9, QMetaData::Public },
	{ "slotGetFTGNR()", &slot_10, QMetaData::Public },
	{ "slotGetTFN1()", &slot_11, QMetaData::Public },
	{ "slotGetTFN2()", &slot_12, QMetaData::Public },
	{ "slotGetTFAX()", &slot_13, QMetaData::Public },
	{ "slotGetEML1()", &slot_14, QMetaData::Public },
	{ "slotGetMOMS1()", &slot_15, QMetaData::Public },
	{ "slotLineEditMoms1_returnPressed()", &slot_16, QMetaData::Public },
	{ "slotGetPosttyper()", &slot_17, QMetaData::Public },
	{ "slotGetPostEndOfProcess()", &slot_18, QMetaData::Public },
	{ "ListView1_clicked(QListViewItem*)", &slot_19, QMetaData::Public },
	{ "slotUpdFtgData(QString,QString)", &slot_20, QMetaData::Public },
	{ "slotUpdateEndOfProcess()", &slot_21, QMetaData::Public },
	{ "PushButtonUpdate_clicked()", &slot_22, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmChgFtgData", parentObject,
	slot_tbl, 23,
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
    if ( !qstrcmp( clname, "frmChgFtgData" ) ) return (frmChgFtgData*)this;
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
    case 8: slotGetADR2(); break;
    case 9: slotGetADR3(); break;
    case 10: slotGetFTGNR(); break;
    case 11: slotGetTFN1(); break;
    case 12: slotGetTFN2(); break;
    case 13: slotGetTFAX(); break;
    case 14: slotGetEML1(); break;
    case 15: slotGetMOMS1(); break;
    case 16: slotLineEditMoms1_returnPressed(); break;
    case 17: slotGetPosttyper(); break;
    case 18: slotGetPostEndOfProcess(); break;
    case 19: ListView1_clicked((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 20: slotUpdFtgData((QString)static_QUType_QString.get(_o+1),(QString)static_QUType_QString.get(_o+2)); break;
    case 21: slotUpdateEndOfProcess(); break;
    case 22: PushButtonUpdate_clicked(); break;
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

bool frmChgFtgData::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
