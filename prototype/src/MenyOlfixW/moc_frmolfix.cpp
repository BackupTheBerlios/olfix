/****************************************************************************
** frmOlfix meta object code from reading C++ file 'frmolfix.h'
**
** Created: Tue Mar 25 05:38:40 2003
**      by: The Qt MOC ($Id: moc_frmolfix.cpp,v 1.1 2003/05/08 08:55:02 frazze Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "frmolfix.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *frmOlfix::className() const
{
    return "frmOlfix";
}

QMetaObject *frmOlfix::metaObj = 0;
static QMetaObjectCleanUp cleanUp_frmOlfix;

#ifndef QT_NO_TRANSLATION
QString frmOlfix::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmOlfix", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString frmOlfix::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "frmOlfix", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* frmOlfix::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"init", 0, 0 };
    static const QUMethod slot_1 = {"slotGetProgram", 0, 0 };
    static const QUMethod slot_2 = {"slotDataOnStdout", 0, 0 };
    static const QUMethod slot_3 = {"slotDataOnStderr", 0, 0 };
    static const QUMethod slot_4 = {"slotEndOfProcess", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_5 = {"ListView1_clicked", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "prg", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"slotRunProgram", 1, param_slot_6 };
    static const QUMethod slot_7 = {"slotDataOnPrgStderr", 0, 0 };
    static const QUMethod slot_8 = {"slotEndOfPrgProcess", 0, 0 };
    static const QUParameter param_slot_9[] = {
	{ "prog", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"CheckBehor", 1, param_slot_9 };
    static const QUMethod slot_10 = {"slotEndOfCheckProcess", 0, 0 };
    static const QUMethod slot_11 = {"slotDataOnCheckStdout", 0, 0 };
    static const QUMethod slot_12 = {"slotDataOnCheckStderr", 0, 0 };
    static const QUMethod slot_13 = {"slotOmOlfix", 0, 0 };
    static const QUMethod slot_14 = {"slotLicensvillkor", 0, 0 };
    static const QUMethod slot_15 = {"slotHelp", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "init()", &slot_0, QMetaData::Public },
	{ "slotGetProgram()", &slot_1, QMetaData::Public },
	{ "slotDataOnStdout()", &slot_2, QMetaData::Public },
	{ "slotDataOnStderr()", &slot_3, QMetaData::Public },
	{ "slotEndOfProcess()", &slot_4, QMetaData::Public },
	{ "ListView1_clicked(QListViewItem*)", &slot_5, QMetaData::Public },
	{ "slotRunProgram(QString)", &slot_6, QMetaData::Public },
	{ "slotDataOnPrgStderr()", &slot_7, QMetaData::Public },
	{ "slotEndOfPrgProcess()", &slot_8, QMetaData::Public },
	{ "CheckBehor(QString)", &slot_9, QMetaData::Public },
	{ "slotEndOfCheckProcess()", &slot_10, QMetaData::Public },
	{ "slotDataOnCheckStdout()", &slot_11, QMetaData::Public },
	{ "slotDataOnCheckStderr()", &slot_12, QMetaData::Public },
	{ "slotOmOlfix()", &slot_13, QMetaData::Public },
	{ "slotLicensvillkor()", &slot_14, QMetaData::Public },
	{ "slotHelp()", &slot_15, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"frmOlfix", parentObject,
	slot_tbl, 16,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_frmOlfix.setMetaObject( metaObj );
    return metaObj;
}

void* frmOlfix::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "frmOlfix" ) ) return (frmOlfix*)this;
    return QWidget::qt_cast( clname );
}

bool frmOlfix::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: init(); break;
    case 1: slotGetProgram(); break;
    case 2: slotDataOnStdout(); break;
    case 3: slotDataOnStderr(); break;
    case 4: slotEndOfProcess(); break;
    case 5: ListView1_clicked((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 6: slotRunProgram((QString)static_QUType_QString.get(_o+1)); break;
    case 7: slotDataOnPrgStderr(); break;
    case 8: slotEndOfPrgProcess(); break;
    case 9: CheckBehor((QString)static_QUType_QString.get(_o+1)); break;
    case 10: slotEndOfCheckProcess(); break;
    case 11: slotDataOnCheckStdout(); break;
    case 12: slotDataOnCheckStderr(); break;
    case 13: slotOmOlfix(); break;
    case 14: slotLicensvillkor(); break;
    case 15: slotHelp(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool frmOlfix::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool frmOlfix::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
