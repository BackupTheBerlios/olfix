/****************************************************************************
** frmDelValuta meta object code from reading C++ file 'frmdelvaluta.h'
**
** Created: Thu Mar 20 08:13:44 2003
**      by: The Qt MOC ($Id: moc_frmdelvaluta.cpp,v 1.2 2003/09/28 07:47:33 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmdelvaluta.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmDelValuta::className() const
{
    return "frmDelValuta";
}

QMetaObject *frmDelValuta::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmDelValuta;

#ifndef QT_NO_TRANSLATION
QString frmDelValuta::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDelValuta", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmDelValuta::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDelValuta", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmDelValuta::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotPushButtonGet_clicked", 0, 0 };
    static const QUMethod slot_2 = {"slotGetValuta", 0, 0 };
    static const QUMethod slot_3 = {"slotValutaEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotGetDataOnStdout", 0, 0 };
    static const QUMethod slot_5 = {"slotGetDataOnStderr", 0, 0 };
    static const QUMethod slot_6 = {"slotEndOfGetProcess", 0, 0 };
    static const QUMethod slot_7 = {"slotPushButtonOK_clicked", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ "mynt", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"slotDelValData", 1, param_slot_8 };
    static const QUMethod slot_9 = {"slotEndOfDelProcess", 0, 0 };
    static const QUMethod slot_10 = {"slotDelDataOnStderr", 0, 0 };
    static const QUMethod slot_11 = {"slotDelDataOnStdout", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotPushButtonGet_clicked()", &slot_1, QMetaData::Public },
	{ "slotGetValuta()", &slot_2, QMetaData::Public },
	{ "slotValutaEntered()", &slot_3, QMetaData::Public },
	{ "slotGetDataOnStdout()", &slot_4, QMetaData::Public },
	{ "slotGetDataOnStderr()", &slot_5, QMetaData::Public },
	{ "slotEndOfGetProcess()", &slot_6, QMetaData::Public },
	{ "slotPushButtonOK_clicked()", &slot_7, QMetaData::Public },
	{ "slotDelValData(QString)", &slot_8, QMetaData::Public },
	{ "slotEndOfDelProcess()", &slot_9, QMetaData::Public },
	{ "slotDelDataOnStderr()", &slot_10, QMetaData::Public },
	{ "slotDelDataOnStdout()", &slot_11, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmDelValuta", parentObject,
	slot_tbl, 12,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmDelValuta.setMetaObject( metaObj );
    return metaObj;
}

void* frmDelValuta::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmDelValuta" ) ) return (frmDelValuta*)this;
    return QWidget::qt_cast( clname );
}

bool frmDelValuta::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotPushButtonGet_clicked(); break;
    case 2: slotGetValuta(); break;
    case 3: slotValutaEntered(); break;
    case 4: slotGetDataOnStdout(); break;
    case 5: slotGetDataOnStderr(); break;
    case 6: slotEndOfGetProcess(); break;
    case 7: slotPushButtonOK_clicked(); break;
    case 8: slotDelValData((QString)static_QUType_QString.get(_o+1)); break;
    case 9: slotEndOfDelProcess(); break;
    case 10: slotDelDataOnStderr(); break;
    case 11: slotDelDataOnStdout(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmDelValuta::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmDelValuta::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
