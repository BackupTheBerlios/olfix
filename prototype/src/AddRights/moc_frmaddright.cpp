/****************************************************************************
** frmAddRight meta object code from reading C++ file 'frmaddright.h'
**
** Created: Tue May 27 06:35:06 2003
**      by: The Qt MOC ($Id: moc_frmaddright.cpp,v 1.2 2003/09/28 06:13:38 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddright.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddRight::className() const
{
    return "frmAddRight";
}

QMetaObject *frmAddRight::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddRight( "frmAddRight", &frmAddRight::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmAddRight::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddRight", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddRight::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddRight", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddRight::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotAddRight", 0, 0 };
    static const QUMethod slot_1 = {"slotUseridEntered", 0, 0 };
    static const QUMethod slot_2 = {"slotRightEntered", 0, 0 };
    static const QUMethod slot_3 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_4 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_5 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_6 = {"slotGetFunc", 0, 0 };
    static const QUMethod slot_7 = {"slotEndOfGetFuncfProcess", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_8 = {"slotPickupFunc", 1, param_slot_8 };
    static const QUMethod slot_9 = {"languageChange", 0, 0 };
    static const QUMethod slot_10 = {"init", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotAddRight()", &slot_0, QMetaData::Public },
	{ "slotUseridEntered()", &slot_1, QMetaData::Public },
	{ "slotRightEntered()", &slot_2, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_3, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_4, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_5, QMetaData::Public },
	{ "slotGetFunc()", &slot_6, QMetaData::Public },
	{ "slotEndOfGetFuncfProcess()", &slot_7, QMetaData::Public },
	{ "slotPickupFunc(QListViewItem*)", &slot_8, QMetaData::Public },
	{ "languageChange()", &slot_9, QMetaData::Protected },
	{ "init()", &slot_10, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddRight", parentObject,
	slot_tbl, 11,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddRight.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddRight::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddRight" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmAddRight::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotAddRight(); break;
    case 1: slotUseridEntered(); break;
    case 2: slotRightEntered(); break;
    case 3: slotDataOnStdout(); break;
    case 4: slotDataOnStderr(); break;
    case 5: slotEndOfProcess(); break;
    case 6: slotGetFunc(); break;
    case 7: slotEndOfGetFuncfProcess(); break;
    case 8: slotPickupFunc((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 9: languageChange(); break;
    case 10: init(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddRight::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddRight::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmAddRight::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
