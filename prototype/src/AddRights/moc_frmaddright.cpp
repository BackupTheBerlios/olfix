/****************************************************************************
** frmAddRight meta object code from reading C++ file 'frmaddright.h'
**
** Created: Tue Mar 25 16:09:50 2003
**      by: The Qt MOC ($Id: moc_frmaddright.cpp,v 1.1 2003/05/08 08:54:22 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddright.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddRight::className() const
{
    return "frmAddRight";
}

QMetaObject *frmAddRight::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddRight;

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
    static const QUMethod slot_6 = {"init", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotAddRight()", &slot_0, QMetaData::Public },
	{ "slotUseridEntered()", &slot_1, QMetaData::Public },
	{ "slotRightEntered()", &slot_2, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_3, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_4, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_5, QMetaData::Public },
	{ "init()", &slot_6, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddRight", parentObject,
	slot_tbl, 7,
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
    if ( !qstrcmp( clname, "frmAddRight" ) ) return (frmAddRight*)this;
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
    case 6: init(); break;
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

bool frmAddRight::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
