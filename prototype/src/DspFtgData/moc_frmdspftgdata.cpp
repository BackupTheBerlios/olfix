/****************************************************************************
** frmDspFtgData meta object code from reading C++ file 'frmdspftgdata.h'
**
** Created: Wed Apr 16 16:20:08 2003
**      by: The Qt MOC ($Id: moc_frmdspftgdata.cpp,v 1.1 2003/05/08 08:55:07 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmdspftgdata.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmDspFtgData::className() const
{
    return "frmDspFtgData";
}

QMetaObject *frmDspFtgData::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmDspFtgData;

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
    static const QUMethod slot_5 = {"slotGetADR1", 0, 0 };
    static const QUMethod slot_6 = {"slotGetADR2", 0, 0 };
    static const QUMethod slot_7 = {"slotGetADR3", 0, 0 };
    static const QUMethod slot_8 = {"slotGetFTGNR", 0, 0 };
    static const QUMethod slot_9 = {"slotGetTFN1", 0, 0 };
    static const QUMethod slot_10 = {"slotGetTFN2", 0, 0 };
    static const QUMethod slot_11 = {"slotGetTFAX", 0, 0 };
    static const QUMethod slot_12 = {"slotGetEML1", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotGetFtgData(QString)", &slot_1, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_2, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_3, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_4, QMetaData::Public },
	{ "slotGetADR1()", &slot_5, QMetaData::Public },
	{ "slotGetADR2()", &slot_6, QMetaData::Public },
	{ "slotGetADR3()", &slot_7, QMetaData::Public },
	{ "slotGetFTGNR()", &slot_8, QMetaData::Public },
	{ "slotGetTFN1()", &slot_9, QMetaData::Public },
	{ "slotGetTFN2()", &slot_10, QMetaData::Public },
	{ "slotGetTFAX()", &slot_11, QMetaData::Public },
	{ "slotGetEML1()", &slot_12, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmDspFtgData", parentObject,
	slot_tbl, 13,
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
    if ( !qstrcmp( clname, "frmDspFtgData" ) ) return (frmDspFtgData*)this;
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
    case 5: slotGetADR1(); break;
    case 6: slotGetADR2(); break;
    case 7: slotGetADR3(); break;
    case 8: slotGetFTGNR(); break;
    case 9: slotGetTFN1(); break;
    case 10: slotGetTFN2(); break;
    case 11: slotGetTFAX(); break;
    case 12: slotGetEML1(); break;
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

bool frmDspFtgData::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
