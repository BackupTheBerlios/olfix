/****************************************************************************
** frmDelRights meta object code from reading C++ file 'frmdelrights.h'
**
** Created: Thu Mar 20 08:10:10 2003
**      by: The Qt MOC ($Id: moc_frmdelrights.cpp,v 1.1 2003/05/08 08:54:41 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmdelrights.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmDelRights::className() const
{
    return "frmDelRights";
}

QMetaObject *frmDelRights::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmDelRights;

#ifndef QT_NO_TRANSLATION
QString frmDelRights::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDelRights", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmDelRights::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmDelRights", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmDelRights::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotUseridEntered", 0, 0 };
    static const QUMethod slot_2 = {"slotTransidEntered", 0, 0 };
    static const QUMethod slot_3 = {"slotGetRights", 0, 0 };
    static const QUMethod slot_4 = {"slotGetDataOnStdout", 0, 0 };
    static const QUMethod slot_5 = {"slotGetDataOnStderr", 0, 0 };
    static const QUMethod slot_6 = {"slotEndOfGetProcess", 0, 0 };
    static const QUMethod slot_7 = {"slotDelRgt", 0, 0 };
    static const QUMethod slot_8 = {"slotDelDataOnStdout", 0, 0 };
    static const QUMethod slot_9 = {"slotDelDataOnStderr", 0, 0 };
    static const QUMethod slot_10 = {"slotEndOfDelProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotUseridEntered()", &slot_1, QMetaData::Public },
	{ "slotTransidEntered()", &slot_2, QMetaData::Public },
	{ "slotGetRights()", &slot_3, QMetaData::Public },
	{ "slotGetDataOnStdout()", &slot_4, QMetaData::Public },
	{ "slotGetDataOnStderr()", &slot_5, QMetaData::Public },
	{ "slotEndOfGetProcess()", &slot_6, QMetaData::Public },
	{ "slotDelRgt()", &slot_7, QMetaData::Public },
	{ "slotDelDataOnStdout()", &slot_8, QMetaData::Public },
	{ "slotDelDataOnStderr()", &slot_9, QMetaData::Public },
	{ "slotEndOfDelProcess()", &slot_10, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmDelRights", parentObject,
	slot_tbl, 11,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmDelRights.setMetaObject( metaObj );
    return metaObj;
}

void* frmDelRights::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmDelRights" ) ) return (frmDelRights*)this;
    return QWidget::qt_cast( clname );
}

bool frmDelRights::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotUseridEntered(); break;
    case 2: slotTransidEntered(); break;
    case 3: slotGetRights(); break;
    case 4: slotGetDataOnStdout(); break;
    case 5: slotGetDataOnStderr(); break;
    case 6: slotEndOfGetProcess(); break;
    case 7: slotDelRgt(); break;
    case 8: slotDelDataOnStdout(); break;
    case 9: slotDelDataOnStderr(); break;
    case 10: slotEndOfDelProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmDelRights::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmDelRights::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
