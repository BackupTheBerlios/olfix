/****************************************************************************
** frmKtoRapport meta object code from reading C++ file 'ktorapport.h'
**
** Created: Fri May 16 08:47:42 2003
**      by: The Qt MOC ($Id: moc_ktorapport.cpp,v 1.3 2003/09/28 08:00:35 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "ktorapport.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmKtoRapport::className() const
{
    return "frmKtoRapport";
}

QMetaObject *frmKtoRapport::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmKtoRapport;

#ifndef QT_NO_TRANSLATION
QString frmKtoRapport::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmKtoRapport", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmKtoRapport::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmKtoRapport", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmKtoRapport::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotLineEditBar_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"slotGetVerrader", 0, 0 };
    static const QUMethod slot_3 = {"slotCheckBar", 0, 0 };
    static const QUMethod slot_4 = {"slotBARCHKEndOfProcess", 0, 0 };
    static const QUMethod slot_5 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_6 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_7 = {"slotKTORPTEndOfProcess", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotLineEditBar_returnPressed()", &slot_1, QMetaData::Public },
	{ "slotGetVerrader()", &slot_2, QMetaData::Public },
	{ "slotCheckBar()", &slot_3, QMetaData::Public },
	{ "slotBARCHKEndOfProcess()", &slot_4, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_5, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_6, QMetaData::Public },
	{ "slotKTORPTEndOfProcess()", &slot_7, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmKtoRapport", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmKtoRapport.setMetaObject( metaObj );
    return metaObj;
}

void* frmKtoRapport::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmKtoRapport" ) ) return (frmKtoRapport*)this;
    return QWidget::qt_cast( clname );
}

bool frmKtoRapport::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotLineEditBar_returnPressed(); break;
    case 2: slotGetVerrader(); break;
    case 3: slotCheckBar(); break;
    case 4: slotBARCHKEndOfProcess(); break;
    case 5: slotDataOnStdout(); break;
    case 6: slotDataOnStderr(); break;
    case 7: slotKTORPTEndOfProcess(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmKtoRapport::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmKtoRapport::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
