/****************************************************************************
** frmChgBar meta object code from reading C++ file 'frmchgbar.h'
**
** Created: Fri Jun 6 06:44:20 2003
**      by: The Qt MOC ($Id: moc_frmchgbar.cpp,v 1.2 2003/09/28 06:38:37 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmchgbar.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmChgBar::className() const
{
    return "frmChgBar";
}

QMetaObject *frmChgBar::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmChgBar( "frmChgBar", &frmChgBar::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmChgBar::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgBar", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmChgBar::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgBar", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmChgBar::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"LineEditBar_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"slotChgBar", 0, 0 };
    static const QUMethod slot_3 = {"LineEditBenamn_returnPressed", 0, 0 };
    static const QUMethod slot_4 = {"LineEditStartdatum_returnPressed", 0, 0 };
    static const QUMethod slot_5 = {"LineEditSlutdatum_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"LineEditBeskattAr_returnPressed", 0, 0 };
    static const QUMethod slot_7 = {"LineEditNestaVerNr_returnPressed", 0, 0 };
    static const QUMethod slot_8 = {"LineEditKontoplan_returnPressed", 0, 0 };
    static const QUMethod slot_9 = {"PushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_10 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_11 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_12 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_13 = {"slotGetBar", 0, 0 };
    static const QUMethod slot_14 = {"slotGetDataOnStderr", 0, 0 };
    static const QUMethod slot_15 = {"slotGetDataOnStdout", 0, 0 };
    static const QUMethod slot_16 = {"slotGetEndOfProcess", 0, 0 };
    static const QUMethod slot_17 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "LineEditBar_returnPressed()", &slot_1, QMetaData::Public },
	{ "slotChgBar()", &slot_2, QMetaData::Public },
	{ "LineEditBenamn_returnPressed()", &slot_3, QMetaData::Public },
	{ "LineEditStartdatum_returnPressed()", &slot_4, QMetaData::Public },
	{ "LineEditSlutdatum_returnPressed()", &slot_5, QMetaData::Public },
	{ "LineEditBeskattAr_returnPressed()", &slot_6, QMetaData::Public },
	{ "LineEditNestaVerNr_returnPressed()", &slot_7, QMetaData::Public },
	{ "LineEditKontoplan_returnPressed()", &slot_8, QMetaData::Public },
	{ "PushButtonOK_clicked()", &slot_9, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_10, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_11, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_12, QMetaData::Public },
	{ "slotGetBar()", &slot_13, QMetaData::Public },
	{ "slotGetDataOnStderr()", &slot_14, QMetaData::Public },
	{ "slotGetDataOnStdout()", &slot_15, QMetaData::Public },
	{ "slotGetEndOfProcess()", &slot_16, QMetaData::Public },
	{ "languageChange()", &slot_17, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmChgBar", parentObject,
	slot_tbl, 18,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmChgBar.setMetaObject( metaObj );
    return metaObj;
}

void* frmChgBar::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmChgBar" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmChgBar::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: LineEditBar_returnPressed(); break;
    case 2: slotChgBar(); break;
    case 3: LineEditBenamn_returnPressed(); break;
    case 4: LineEditStartdatum_returnPressed(); break;
    case 5: LineEditSlutdatum_returnPressed(); break;
    case 6: LineEditBeskattAr_returnPressed(); break;
    case 7: LineEditNestaVerNr_returnPressed(); break;
    case 8: LineEditKontoplan_returnPressed(); break;
    case 9: PushButtonOK_clicked(); break;
    case 10: slotDataOnStderr(); break;
    case 11: slotDataOnStdout(); break;
    case 12: slotEndOfProcess(); break;
    case 13: slotGetBar(); break;
    case 14: slotGetDataOnStderr(); break;
    case 15: slotGetDataOnStdout(); break;
    case 16: slotGetEndOfProcess(); break;
    case 17: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmChgBar::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmChgBar::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmChgBar::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
