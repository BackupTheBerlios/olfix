/****************************************************************************
** frmSaldolista meta object code from reading C++ file 'frmsaldolista.h'
**
** Created: Sat Aug 23 09:52:16 2003
**      by: The Qt MOC ($Id: moc_frmsaldolista.cpp,v 1.1 2003/09/28 08:39:42 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmsaldolista.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmSaldolista::className() const
{
    return "frmSaldolista";
}

QMetaObject *frmSaldolista::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmSaldolista( "frmSaldolista", &frmSaldolista::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmSaldolista::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmSaldolista", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmSaldolista::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmSaldolista", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmSaldolista::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotlineEditBar_returnPressed", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"radioButtonCSV_toggled", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"radioButtonPrint_toggled", 1, param_slot_2 };
    static const QUMethod slot_3 = {"slotpushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_4 = {"slotGetData", 0, 0 };
    static const QUMethod slot_5 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_6 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_7 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_8 = {"slotCreateHeader", 0, 0 };
    static const QUParameter param_slot_9[] = {
	{ "filnamn", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"slotFileRemove", 1, param_slot_9 };
    static const QUMethod slot_10 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotlineEditBar_returnPressed()", &slot_0, QMetaData::Public },
	{ "radioButtonCSV_toggled(bool)", &slot_1, QMetaData::Public },
	{ "radioButtonPrint_toggled(bool)", &slot_2, QMetaData::Public },
	{ "slotpushButtonOK_clicked()", &slot_3, QMetaData::Public },
	{ "slotGetData()", &slot_4, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_5, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_6, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_7, QMetaData::Public },
	{ "slotCreateHeader()", &slot_8, QMetaData::Public },
	{ "slotFileRemove(QString)", &slot_9, QMetaData::Public },
	{ "languageChange()", &slot_10, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmSaldolista", parentObject,
	slot_tbl, 11,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmSaldolista.setMetaObject( metaObj );
    return metaObj;
}

void* frmSaldolista::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmSaldolista" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmSaldolista::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotlineEditBar_returnPressed(); break;
    case 1: radioButtonCSV_toggled((bool)static_QUType_bool.get(_o+1)); break;
    case 2: radioButtonPrint_toggled((bool)static_QUType_bool.get(_o+1)); break;
    case 3: slotpushButtonOK_clicked(); break;
    case 4: slotGetData(); break;
    case 5: slotDataOnStdout(); break;
    case 6: slotDataOnStderr(); break;
    case 7: slotEndOfProcess(); break;
    case 8: slotCreateHeader(); break;
    case 9: slotFileRemove((QString)static_QUType_QString.get(_o+1)); break;
    case 10: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmSaldolista::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmSaldolista::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmSaldolista::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
