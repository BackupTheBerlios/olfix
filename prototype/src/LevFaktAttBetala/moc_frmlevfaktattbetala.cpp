/****************************************************************************
** frmLevFaktAttBetala meta object code from reading C++ file 'frmlevfaktattbetala.h'
**
** Created: Wed Aug 20 21:36:26 2003
**      by: The Qt MOC ($Id: moc_frmlevfaktattbetala.cpp,v 1.1 2003/09/28 08:09:37 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmlevfaktattbetala.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmLevFaktAttBetala::className() const
{
    return "frmLevFaktAttBetala";
}

QMetaObject *frmLevFaktAttBetala::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmLevFaktAttBetala( "frmLevFaktAttBetala", &frmLevFaktAttBetala::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmLevFaktAttBetala::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmLevFaktAttBetala", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmLevFaktAttBetala::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmLevFaktAttBetala", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmLevFaktAttBetala::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotlineEditExpireDate_returnPressed", 0, 0 };
    static const QUMethod slot_1 = {"slotpushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_2 = {"slotSkapRapportfil", 0, 0 };
    static const QUMethod slot_3 = {"slotEndOfProcess", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ "filnamn", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"slotFileRemove", 1, param_slot_4 };
    static const QUMethod slot_5 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_6 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_7 = {"slotCreateHeader", 0, 0 };
    static const QUMethod slot_8 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotlineEditExpireDate_returnPressed()", &slot_0, QMetaData::Public },
	{ "slotpushButtonOK_clicked()", &slot_1, QMetaData::Public },
	{ "slotSkapRapportfil()", &slot_2, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_3, QMetaData::Public },
	{ "slotFileRemove(QString)", &slot_4, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_5, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_6, QMetaData::Public },
	{ "slotCreateHeader()", &slot_7, QMetaData::Public },
	{ "languageChange()", &slot_8, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmLevFaktAttBetala", parentObject,
	slot_tbl, 9,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmLevFaktAttBetala.setMetaObject( metaObj );
    return metaObj;
}

void* frmLevFaktAttBetala::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmLevFaktAttBetala" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool frmLevFaktAttBetala::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotlineEditExpireDate_returnPressed(); break;
    case 1: slotpushButtonOK_clicked(); break;
    case 2: slotSkapRapportfil(); break;
    case 3: slotEndOfProcess(); break;
    case 4: slotFileRemove((QString)static_QUType_QString.get(_o+1)); break;
    case 5: slotDataOnStdout(); break;
    case 6: slotDataOnStderr(); break;
    case 7: slotCreateHeader(); break;
    case 8: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmLevFaktAttBetala::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmLevFaktAttBetala::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool frmLevFaktAttBetala::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
