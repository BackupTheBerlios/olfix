/****************************************************************************
** frmAddLevplats meta object code from reading C++ file 'frmaddlevplats.h'
**
** Created: Wed Sep 10 10:54:34 2003
**      by: The Qt MOC ($Id: moc_frmaddlevplats.cpp,v 1.1 2003/09/28 06:21:29 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddlevplats.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddLevplats::className() const
{
    return "frmAddLevplats";
}

QMetaObject *frmAddLevplats::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddLevplats( "frmAddLevplats", &frmAddLevplats::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmAddLevplats::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddLevplats", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddLevplats::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddLevplats", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddLevplats::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"lineEditKundID_returnPressed", 0, 0 };
    static const QUMethod slot_1 = {"lineEditLevPlatsNr_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"lineEditLevAdress_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"lineEditPostnr_returnPressed", 0, 0 };
    static const QUMethod slot_4 = {"lineEditPostAdress_returnPressed", 0, 0 };
    static const QUMethod slot_5 = {"lineEditLand_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"pushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_7 = {"AddStandardLevPlats", 0, 0 };
    static const QUMethod slot_8 = {"slotPlatsEndOfProcess", 0, 0 };
    static const QUMethod slot_9 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_10 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_11 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "lineEditKundID_returnPressed()", &slot_0, QMetaData::Public },
	{ "lineEditLevPlatsNr_returnPressed()", &slot_1, QMetaData::Public },
	{ "lineEditLevAdress_returnPressed()", &slot_2, QMetaData::Public },
	{ "lineEditPostnr_returnPressed()", &slot_3, QMetaData::Public },
	{ "lineEditPostAdress_returnPressed()", &slot_4, QMetaData::Public },
	{ "lineEditLand_returnPressed()", &slot_5, QMetaData::Public },
	{ "pushButtonOK_clicked()", &slot_6, QMetaData::Public },
	{ "AddStandardLevPlats()", &slot_7, QMetaData::Public },
	{ "slotPlatsEndOfProcess()", &slot_8, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_9, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_10, QMetaData::Public },
	{ "languageChange()", &slot_11, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddLevplats", parentObject,
	slot_tbl, 12,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddLevplats.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddLevplats::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddLevplats" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmAddLevplats::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: lineEditKundID_returnPressed(); break;
    case 1: lineEditLevPlatsNr_returnPressed(); break;
    case 2: lineEditLevAdress_returnPressed(); break;
    case 3: lineEditPostnr_returnPressed(); break;
    case 4: lineEditPostAdress_returnPressed(); break;
    case 5: lineEditLand_returnPressed(); break;
    case 6: pushButtonOK_clicked(); break;
    case 7: AddStandardLevPlats(); break;
    case 8: slotPlatsEndOfProcess(); break;
    case 9: slotDataOnStdout(); break;
    case 10: slotDataOnStderr(); break;
    case 11: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddLevplats::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddLevplats::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmAddLevplats::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
