/****************************************************************************
** frmAddKstalle meta object code from reading C++ file 'frmaddkstalle.h'
**
** Created: Thu Mar 20 07:53:53 2003
**      by: The Qt MOC ($Id: moc_frmaddkstalle.cpp,v 1.1 2003/05/08 08:54:20 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmaddkstalle.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmAddKstalle::className() const
{
    return "frmAddKstalle";
}

QMetaObject *frmAddKstalle::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmAddKstalle;

#ifndef QT_NO_TRANSLATION
QString frmAddKstalle::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddKstalle", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmAddKstalle::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmAddKstalle", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmAddKstalle::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotBarEntered", 0, 0 };
    static const QUMethod slot_2 = {"slotKstalleEntered", 0, 0 };
    static const QUMethod slot_3 = {"slotBenamnEntered", 0, 0 };
    static const QUMethod slot_4 = {"slotPushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_5 = {"slotAddKstalle", 0, 0 };
    static const QUMethod slot_6 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_7 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_8 = {"slotEndOfProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotBarEntered()", &slot_1, QMetaData::Public },
	{ "slotKstalleEntered()", &slot_2, QMetaData::Public },
	{ "slotBenamnEntered()", &slot_3, QMetaData::Public },
	{ "slotPushButtonOK_clicked()", &slot_4, QMetaData::Public },
	{ "slotAddKstalle()", &slot_5, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_6, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_7, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_8, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmAddKstalle", parentObject,
	slot_tbl, 9,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmAddKstalle.setMetaObject( metaObj );
    return metaObj;
}

void* frmAddKstalle::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmAddKstalle" ) ) return (frmAddKstalle*)this;
    return QWidget::qt_cast( clname );
}

bool frmAddKstalle::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotBarEntered(); break;
    case 2: slotKstalleEntered(); break;
    case 3: slotBenamnEntered(); break;
    case 4: slotPushButtonOK_clicked(); break;
    case 5: slotAddKstalle(); break;
    case 6: slotDataOnStdout(); break;
    case 7: slotDataOnStderr(); break;
    case 8: slotEndOfProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmAddKstalle::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmAddKstalle::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
