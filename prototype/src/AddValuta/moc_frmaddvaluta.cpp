/****************************************************************************
** frmAddValuta meta object code from reading C++ file 'frmaddvaluta.h'
**
** Created: Thu Mar 20 07:58:38 2003
**      by: The Qt MOC ($Id: moc_frmaddvaluta.cpp,v 1.1 2003/05/08 08:54:26 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddvaluta.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddValuta::className() const
{
    return "frmAddValuta";
}

QMetaObject *frmAddValuta::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddValuta;

#ifndef QT_NO_TRANSLATION
QString frmAddValuta::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddValuta", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddValuta::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddValuta", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddValuta::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotAddValuta", 0, 0 };
    static const QUMethod slot_2 = {"slotValutaEntered", 0, 0 };
    static const QUMethod slot_3 = {"slotBeteckningEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotLandEntered", 0, 0 };
    static const QUMethod slot_5 = {"slotKopEntered", 0, 0 };
    static const QUMethod slot_6 = {"slotSaljEntered", 0, 0 };
    static const QUMethod slot_7 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_8 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_9 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_10 = {"slotPushButtonOK_clicked", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotAddValuta()", &slot_1, QMetaData::Public },
	{ "slotValutaEntered()", &slot_2, QMetaData::Public },
	{ "slotBeteckningEntered()", &slot_3, QMetaData::Public },
	{ "slotLandEntered()", &slot_4, QMetaData::Public },
	{ "slotKopEntered()", &slot_5, QMetaData::Public },
	{ "slotSaljEntered()", &slot_6, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_7, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_8, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_9, QMetaData::Public },
	{ "slotPushButtonOK_clicked()", &slot_10, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddValuta", parentObject,
	slot_tbl, 11,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddValuta.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddValuta::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddValuta" ) ) return (frmAddValuta*)this;
    return QWidget::qt_cast( clname );
}

bool frmAddValuta::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotAddValuta(); break;
    case 2: slotValutaEntered(); break;
    case 3: slotBeteckningEntered(); break;
    case 4: slotLandEntered(); break;
    case 5: slotKopEntered(); break;
    case 6: slotSaljEntered(); break;
    case 7: slotDataOnStdout(); break;
    case 8: slotDataOnStderr(); break;
    case 9: slotEndOfProcess(); break;
    case 10: slotPushButtonOK_clicked(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddValuta::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddValuta::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
