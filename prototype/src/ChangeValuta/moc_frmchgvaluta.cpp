/****************************************************************************
** frmChgValuta meta object code from reading C++ file 'frmchgvaluta.h'
**
** Created: Thu Mar 20 08:08:04 2003
**      by: The Qt MOC ($Id: moc_frmchgvaluta.cpp,v 1.2 2003/09/28 06:51:02 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmchgvaluta.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmChgValuta::className() const
{
    return "frmChgValuta";
}

QMetaObject *frmChgValuta::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmChgValuta;

#ifndef QT_NO_TRANSLATION
QString frmChgValuta::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgValuta", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmChgValuta::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmChgValuta", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmChgValuta::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotGetValuta", 0, 0 };
    static const QUMethod slot_2 = {"slotChgValuta", 0, 0 };
    static const QUMethod slot_3 = {"slotValutaEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotBeteckningEntered", 0, 0 };
    static const QUMethod slot_5 = {"slotLandEntered", 0, 0 };
    static const QUMethod slot_6 = {"slotKopEntered", 0, 0 };
    static const QUMethod slot_7 = {"slotSaljEntered", 0, 0 };
    static const QUMethod slot_8 = {"slotPushButtonGet_clicked", 0, 0 };
    static const QUMethod slot_9 = {"slotValDataOnStdout", 0, 0 };
    static const QUMethod slot_10 = {"slotValDataOnStderr", 0, 0 };
    static const QUMethod slot_11 = {"slotEndOfValProcess", 0, 0 };
    static const QUMethod slot_12 = {"slotChgDataOnStdout", 0, 0 };
    static const QUMethod slot_13 = {"slotChgDataOnStderr", 0, 0 };
    static const QUMethod slot_14 = {"slotEndOfChgProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotGetValuta()", &slot_1, QMetaData::Public },
	{ "slotChgValuta()", &slot_2, QMetaData::Public },
	{ "slotValutaEntered()", &slot_3, QMetaData::Public },
	{ "slotBeteckningEntered()", &slot_4, QMetaData::Public },
	{ "slotLandEntered()", &slot_5, QMetaData::Public },
	{ "slotKopEntered()", &slot_6, QMetaData::Public },
	{ "slotSaljEntered()", &slot_7, QMetaData::Public },
	{ "slotPushButtonGet_clicked()", &slot_8, QMetaData::Public },
	{ "slotValDataOnStdout()", &slot_9, QMetaData::Public },
	{ "slotValDataOnStderr()", &slot_10, QMetaData::Public },
	{ "slotEndOfValProcess()", &slot_11, QMetaData::Public },
	{ "slotChgDataOnStdout()", &slot_12, QMetaData::Public },
	{ "slotChgDataOnStderr()", &slot_13, QMetaData::Public },
	{ "slotEndOfChgProcess()", &slot_14, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmChgValuta", parentObject,
	slot_tbl, 15,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmChgValuta.setMetaObject( metaObj );
    return metaObj;
}

void* frmChgValuta::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmChgValuta" ) ) return (frmChgValuta*)this;
    return QWidget::qt_cast( clname );
}

bool frmChgValuta::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotGetValuta(); break;
    case 2: slotChgValuta(); break;
    case 3: slotValutaEntered(); break;
    case 4: slotBeteckningEntered(); break;
    case 5: slotLandEntered(); break;
    case 6: slotKopEntered(); break;
    case 7: slotSaljEntered(); break;
    case 8: slotPushButtonGet_clicked(); break;
    case 9: slotValDataOnStdout(); break;
    case 10: slotValDataOnStderr(); break;
    case 11: slotEndOfValProcess(); break;
    case 12: slotChgDataOnStdout(); break;
    case 13: slotChgDataOnStderr(); break;
    case 14: slotEndOfChgProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmChgValuta::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmChgValuta::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
