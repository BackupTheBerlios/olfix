/****************************************************************************
** frmAddKonto meta object code from reading C++ file 'frmaddkonto.h'
**
** Created: Thu Mar 20 07:51:55 2003
**      by: The Qt MOC ($Id: moc_frmaddkonto.cpp,v 1.1 2003/05/08 08:54:19 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddkonto.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddKonto::className() const
{
    return "frmAddKonto";
}

QMetaObject *frmAddKonto::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddKonto;

#ifndef QT_NO_TRANSLATION
QString frmAddKonto::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddKonto", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddKonto::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddKonto", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddKonto::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotAddKonto", 0, 0 };
    static const QUMethod slot_1 = {"LineEditBar_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"LineEditKontoNr_returnPressed", 0, 0 };
    static const QUMethod slot_3 = {"LineEditBenamn_returnPressed", 0, 0 };
    static const QUMethod slot_4 = {"LineEditManuell_returnPressed", 0, 0 };
    static const QUMethod slot_5 = {"LineEditMomskod_returnPressed", 0, 0 };
    static const QUMethod slot_6 = {"LineEditSRU_returnPressed", 0, 0 };
    static const QUMethod slot_7 = {"LineEditKst_returnPressed", 0, 0 };
    static const QUMethod slot_8 = {"LineEditProjekt_returnPressed", 0, 0 };
    static const QUMethod slot_9 = {"LineEditSubkonto_returnPressed", 0, 0 };
    static const QUMethod slot_10 = {"LineEditKontoplan_returnPressed", 0, 0 };
    static const QUMethod slot_11 = {"PushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_12 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_13 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_14 = {"slotEndOfProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotAddKonto()", &slot_0, QMetaData::Public },
	{ "LineEditBar_returnPressed()", &slot_1, QMetaData::Public },
	{ "LineEditKontoNr_returnPressed()", &slot_2, QMetaData::Public },
	{ "LineEditBenamn_returnPressed()", &slot_3, QMetaData::Public },
	{ "LineEditManuell_returnPressed()", &slot_4, QMetaData::Public },
	{ "LineEditMomskod_returnPressed()", &slot_5, QMetaData::Public },
	{ "LineEditSRU_returnPressed()", &slot_6, QMetaData::Public },
	{ "LineEditKst_returnPressed()", &slot_7, QMetaData::Public },
	{ "LineEditProjekt_returnPressed()", &slot_8, QMetaData::Public },
	{ "LineEditSubkonto_returnPressed()", &slot_9, QMetaData::Public },
	{ "LineEditKontoplan_returnPressed()", &slot_10, QMetaData::Public },
	{ "PushButtonOK_clicked()", &slot_11, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_12, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_13, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_14, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddKonto", parentObject,
	slot_tbl, 15,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddKonto.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddKonto::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddKonto" ) ) return (frmAddKonto*)this;
    return QWidget::qt_cast( clname );
}

bool frmAddKonto::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotAddKonto(); break;
    case 1: LineEditBar_returnPressed(); break;
    case 2: LineEditKontoNr_returnPressed(); break;
    case 3: LineEditBenamn_returnPressed(); break;
    case 4: LineEditManuell_returnPressed(); break;
    case 5: LineEditMomskod_returnPressed(); break;
    case 6: LineEditSRU_returnPressed(); break;
    case 7: LineEditKst_returnPressed(); break;
    case 8: LineEditProjekt_returnPressed(); break;
    case 9: LineEditSubkonto_returnPressed(); break;
    case 10: LineEditKontoplan_returnPressed(); break;
    case 11: PushButtonOK_clicked(); break;
    case 12: slotDataOnStderr(); break;
    case 13: slotDataOnStdout(); break;
    case 14: slotEndOfProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddKonto::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddKonto::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
