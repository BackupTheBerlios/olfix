/****************************************************************************
** frmAddBar meta object code from reading C++ file 'frmaddbar.h'
**
** Created: Wed May 28 05:28:45 2003
**      by: The Qt MOC ($Id: moc_frmaddbar.cpp,v 1.2 2003/09/28 05:45:57 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddbar.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddBar::className() const
{
    return "frmAddBar";
}

QMetaObject *frmAddBar::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddBar( "frmAddBar", &frmAddBar::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmAddBar::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddBar", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddBar::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddBar", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddBar::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotAddBar", 0, 0 };
    static const QUMethod slot_1 = {"LineEditBar_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"LineEditBenamn_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"LineEditStartdatum_returnPressed", 0, 0 };
    static const QUMethod slot_4 = {"LineEditSlutdatum_returnPressed", 0, 0 };
    static const QUMethod slot_5 = {"LineEditBeskattAr_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"LineEditNestaVerNr_returnPressed", 0, 0 };
    static const QUMethod slot_7 = {"LineEditKontoplan_returnPressed", 0, 0 };
    static const QUMethod slot_8 = {"PushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_9 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_10 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_11 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_12 = {"slotAbout", 0, 0 };
    static const QUMethod slot_13 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotAddBar()", &slot_0, QMetaData::Public },
	{ "LineEditBar_returnPressed()", &slot_1, QMetaData::Public },
	{ "LineEditBenamn_returnPressed()", &slot_2, QMetaData::Public },
	{ "LineEditStartdatum_returnPressed()", &slot_3, QMetaData::Public },
	{ "LineEditSlutdatum_returnPressed()", &slot_4, QMetaData::Public },
	{ "LineEditBeskattAr_returnPressed()", &slot_5, QMetaData::Public },
	{ "LineEditNestaVerNr_returnPressed()", &slot_6, QMetaData::Public },
	{ "LineEditKontoplan_returnPressed()", &slot_7, QMetaData::Public },
	{ "PushButtonOK_clicked()", &slot_8, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_9, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_10, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_11, QMetaData::Public },
	{ "slotAbout()", &slot_12, QMetaData::Public },
	{ "languageChange()", &slot_13, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddBar", parentObject,
	slot_tbl, 14,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddBar.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddBar::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddBar" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmAddBar::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotAddBar(); break;
    case 1: LineEditBar_returnPressed(); break;
    case 2: LineEditBenamn_returnPressed(); break;
    case 3: LineEditStartdatum_returnPressed(); break;
    case 4: LineEditSlutdatum_returnPressed(); break;
    case 5: LineEditBeskattAr_returnPressed(); break;
    case 6: LineEditNestaVerNr_returnPressed(); break;
    case 7: LineEditKontoplan_returnPressed(); break;
    case 8: PushButtonOK_clicked(); break;
    case 9: slotDataOnStderr(); break;
    case 10: slotDataOnStdout(); break;
    case 11: slotEndOfProcess(); break;
    case 12: slotAbout(); break;
    case 13: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddBar::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddBar::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmAddBar::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
