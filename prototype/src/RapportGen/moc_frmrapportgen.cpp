/****************************************************************************
** frmRapportGen meta object code from reading C++ file 'frmrapportgen.h'
**
** Created: Wed Aug 27 09:54:18 2003
**      by: The Qt MOC ($Id: moc_frmrapportgen.cpp,v 1.1 2003/09/28 08:35:04 janpihlgren Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmrapportgen.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmRapportGen::className() const
{
    return "frmRapportGen";
}

QMetaObject *frmRapportGen::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmRapportGen( "frmRapportGen", &frmRapportGen::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString frmRapportGen::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmRapportGen", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmRapportGen::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmRapportGen", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmRapportGen::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slottextEditSQL_returnPressed", 0, 0 };
    static const QUMethod slot_2 = {"slottextEditSQL_TextChanged", 0, 0 };
    static const QUMethod slot_3 = {"slotpushButtonOK_clicked", 0, 0 };
    static const QUMethod slot_4 = {"slotCreateTmpFile", 0, 0 };
    static const QUMethod slot_5 = {"slotEndOfProcess", 0, 0 };
    static const QUMethod slot_6 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_7 = {"slotDataOnStderr", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ "filnamn", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"slotFileRemove", 1, param_slot_8 };
    static const QUMethod slot_9 = {"GetFileDialog", 0, 0 };
    static const QUMethod slot_10 = {"slotGetQueryFile", 0, 0 };
    static const QUMethod slot_11 = {"SaveFileDialog", 0, 0 };
    static const QUMethod slot_12 = {"slotClearSqlQuery", 0, 0 };
    static const QUMethod slot_13 = {"slotHelp", 0, 0 };
    static const QUMethod slot_14 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slottextEditSQL_returnPressed()", &slot_1, QMetaData::Public },
	{ "slottextEditSQL_TextChanged()", &slot_2, QMetaData::Public },
	{ "slotpushButtonOK_clicked()", &slot_3, QMetaData::Public },
	{ "slotCreateTmpFile()", &slot_4, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_5, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_6, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_7, QMetaData::Public },
	{ "slotFileRemove(QString)", &slot_8, QMetaData::Public },
	{ "GetFileDialog()", &slot_9, QMetaData::Public },
	{ "slotGetQueryFile()", &slot_10, QMetaData::Public },
	{ "SaveFileDialog()", &slot_11, QMetaData::Public },
	{ "slotClearSqlQuery()", &slot_12, QMetaData::Public },
	{ "slotHelp()", &slot_13, QMetaData::Public },
	{ "languageChange()", &slot_14, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmRapportGen", parentObject,
	slot_tbl, 15,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmRapportGen.setMetaObject( metaObj );
    return metaObj;
}

void* frmRapportGen::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmRapportGen" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool frmRapportGen::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slottextEditSQL_returnPressed(); break;
    case 2: slottextEditSQL_TextChanged(); break;
    case 3: slotpushButtonOK_clicked(); break;
    case 4: slotCreateTmpFile(); break;
    case 5: slotEndOfProcess(); break;
    case 6: slotDataOnStdout(); break;
    case 7: slotDataOnStderr(); break;
    case 8: slotFileRemove((QString)static_QUType_QString.get(_o+1)); break;
    case 9: GetFileDialog(); break;
    case 10: slotGetQueryFile(); break;
    case 11: SaveFileDialog(); break;
    case 12: slotClearSqlQuery(); break;
    case 13: slotHelp(); break;
    case 14: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmRapportGen::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmRapportGen::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool frmRapportGen::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
