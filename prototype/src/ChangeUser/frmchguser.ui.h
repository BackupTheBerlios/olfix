/****************************************************************/
/**		CHGUSRW					*/
/**		2003-01-21					*/
/**	Ver 0.2    2003-03-23    					*/
/**		Jan Pihlgren	jan@pihlgren.se			*/
/****************************************************************/
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>		
#include <qfile.h>
#include <qregexp.h>

#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString inrad_u;
    QString errorrad;
    QString Userid;
    QString namn="";
    QString avd;
    QString grupp;

    
void frmChgUser::slotGetUser()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	 
	namn="";
	avd="";
	grupp="";
	
    	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "USERDSP");	// OLFIX funktion
	process->addArgument(Userid.latin1());
//	qWarning( "GetUser: Userid=%s \n", Userid.latin1());
	
	frmChgUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotUsrDataOnStdout() ) );
            frmChgUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfUsrProcess() ) );

	if (Userid == ""){
    	    QMessageBox::warning( this, "CHGUSRW",
                      "Userid måste vara ifyllt!\n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/USRCHG!\n");
		QMessageBox::warning( this, "CHGUSRW",
                            "Kan inte starta STYRMAN/USERDSP! \n" );
	    }   
	}
}

void frmChgUser::slotChgUser()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   
//	 frmChgUser::slotUseridEntered();
//	 frmChgUser::slotNameEntered();
//  	 frmChgUser::slotAvdEntered();
//	 frmChgUser::slotGruppEntered();
  
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "USERCHG");	// OLFIX funktion
	process->addArgument(Userid);
	process->addArgument(namn);
	process->addArgument(avd);
	process->addArgument(grupp);
	
	frmChgUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotChgDataOnStdout() ) );
	frmChgUser::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotChgDataOnStderr() ) );
            frmChgUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfChgProcess() ) );
	
//	qWarning( "ChgUser: Userid=%s  Namn=%s  Avd=%s  Grupp=%s\n", Userid.latin1(),namn.latin1() ,avd.latin1(),grupp.latin1());

	if (Userid == "" || namn ==""){
    	    QMessageBox::warning( this, "CHGUSRW",
                      "Userid och/eller Namn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
//		fprintf(stderr,"Problem starta STYRMAN/USRCHG!\n");
		QMessageBox::warning( this, "CHGUSRW",
                            "Kan inte starta STYRMAN/USRCHG! \n" );
	    }   
	}
}

void frmChgUser::slotUseridEntered()
{
    Userid=LineEditUserid->text();
    Userid=Userid.upper();
    LineEditUserid->setText((Userid));
    PushButtonGet->setFocus();
}

void frmChgUser::slotNameEntered()
{
    namn=LineEditNamn->text();
}

void frmChgUser::slotAvdEntered()
{
     avd=LineEditAvd->text();
}

void frmChgUser::slotGruppEntered()
{
    grupp=LineEditGrupp->text();
    PushButtonUpdate->setFocus();
}

void frmChgUser::slotPushButtonGet_clicked()
{
    LineEditNamn->clear();
    LineEditAvd->clear();
    LineEditGrupp->clear();
    namn="";
    avd="";
    grupp="";
    
     frmChgUser::slotGetUser();
}

void frmChgUser::slotPushButtonUpdate_clicked()
{
//  qDebug("PushButtonUpdate clicked Userid=%s",Userid.latin1());    
    frmChgUser::slotChgUser();
}

void frmChgUser::slotUsrDataOnStdout()
{
   while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad_u.append(line);
	inrad_u.append("\n");
//	qWarning( "slotUsrDataOnStdout: Userid=%s \n", inrad_u.latin1() );
    }
}

void frmChgUser::slotEndOfUsrProcess()
{
    int m;
    QString user;
    QString namn;
    QString avd;
    QString grupp;

    int i = inrad_u.find( QRegExp("1:"), 0 );
    int j = inrad_u.find( QRegExp("2:"), 0 );
    int k = inrad_u.find( QRegExp("3:"), 0 );
    int l = inrad_u.find( QRegExp("4:"), 0 );

    m=j-i;
    if (i != -1){
	user=inrad_u.mid(i+2,m-2);
	user=user.stripWhiteSpace();
	LineEditUserid->setText(user);
    }
    m=k-j;
    if ( j != -1){
	namn=inrad_u.mid(j+2,m-2);
	namn=namn.stripWhiteSpace();
	LineEditNamn->setText(namn);
    }
    m=l-k;
    if ( k != -1){
	avd=inrad_u.mid(k+2,m-2);
	avd=avd.stripWhiteSpace();
	LineEditAvd->setText(avd);
    }
    m=inrad_u.length() - l;
    if ( l != -1){
	grupp=inrad_u.mid(l+2,m-2);
	grupp=grupp.stripWhiteSpace();
	LineEditGrupp->setText(grupp);
    }
    LineEditNamn->setFocus();
}


void frmChgUser::slotChgDataOnStdout()
{
   while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
//	qWarning( "slotChgDataOnStdout: inrad=%s \n", inrad.latin1() );
    }
}

void frmChgUser::slotChgDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgUser::slotEndOfChgProcess()
{
    int i ;
//    qDebug("inrad=%s errorrad=%s",inrad.latin1(),errorrad.latin1());    
     i = -1;
     i = errorrad.find( QRegExp("Error: "), 0 );
    
//     qDebug("frmChgUser-inrad=%s i=%d\n",inrad.latin1(),i);
     
     if (i != -1) {
	QMessageBox::critical( this, "CHGUSRW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
//     qDebug("i = %d",i);
     if(i != -1){
	QMessageBox::information( this, "CHGUSRW",
		"Uppdatering OK!\n"
		);
	LineEditUserid->clear();
            LineEditNamn->clear();
	LineEditAvd->clear();
	LineEditGrupp->clear();
	LineEditUserid->setFocus();
	inrad="";
	inrad_u="";
	i = -1;
     }
     else{
	 	QMessageBox::information( this, "CHGUSRW",
		"Ingen uppdatering!\n"
		);
	    }
}
