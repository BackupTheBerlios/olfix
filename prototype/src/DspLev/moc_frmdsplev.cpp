/****************************************************************************
** frmDspLev meta object code from reading C++ file 'frmdsplev.h'
**
** Created: Fri Aug 15 11:15:58 2003
**      by: The Qt MOC ($Id: moc_frmdsplev.cpp,v 1.1 2003/09/28 07:57:07 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmdsplev.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmDspLev::className() const
{
    return "frmDspLev";
}

QMetaObject *frmDspLev::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmDspLev( "frmDspLev", &frmDspLev::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmDspLev::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspLev", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmDspLev::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDspLev", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmDspLev::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotLevNr_returnPressed", 0, 0 };
    static const QUMethod slot_1 = {"slotGetLev", 0, 0 };
    static const QUMethod slot_2 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_3 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_4 = {"slotEndOfProcess", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ "posttyp", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"slotGetFtgData", 1, param_slot_5 };
    static const QUMethod slot_6 = {"slotFtgEndOfProcess", 0, 0 };
    static const QUMethod slot_7 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotLevNr_returnPressed()", &slot_0, QMetaData::Public },
	{ "slotGetLev()", &slot_1, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_2, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_3, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_4, QMetaData::Public },
	{ "slotGetFtgData(QString)", &slot_5, QMetaData::Public },
	{ "slotFtgEndOfProcess()", &slot_6, QMetaData::Public },
	{ "languageChange()", &slot_7, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmDspLev", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmDspLev.setMetaObject( metaObj );
    return metaObj;
}

void* frmDspLev::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmDspLev" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmDspLev::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotLevNr_returnPressed(); break;
    case 1: slotGetLev(); break;
    case 2: slotDataOnStdout(); break;
    case 3: slotDataOnStderr(); break;
    case 4: slotEndOfProcess(); break;
    case 5: slotGetFtgData((QString)static_QUType_QString.get(_o+1)); break;
    case 6: slotFtgEndOfProcess(); break;
    case 7: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmDspLev::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmDspLev::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmDspLev::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
