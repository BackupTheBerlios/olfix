/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDUSRW  -  description
                             -------------------
		     version 0.2x
    begin                : Fre  21 febr 2003
    modified	         : Ons 28 nov  2007
    copyright         : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *********************************************** *****************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>		
#include <qfile.h>
#include <qregexp.h>
#define MAXSTRING 5000

    QProcess* process;
    QString Userid;
    QString Namn="";
    QString Avd;
    QString Grupp;
    QString inrad;
    QString errorrad;
    QString* rad;
    QString hjelpfil;

    
    void frmAddUser::init()
{
	frmAddUser::checkHost();
}


void frmAddUser::slotAddUser()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	   
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "USERADD");	// OLFIX funktion
	process->addArgument(Userid);
	process->addArgument(Namn);
	process->addArgument(Avd);
	process->addArgument(Grupp);
	
	frmAddUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddUser::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	// qWarning( "AddUser: Userid=%s  Namn=%s  Avd=%s  Grupp=%s\n", Userid.latin1(),Namn.latin1() ,Avd.latin1(),Grupp.latin1());

	if (Userid == "" || Namn ==""){
    	    QMessageBox::warning( this, "ADDUSRW",
                      "USERID och/eller Namn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/USRADD!\n");
		QMessageBox::warning( this, "ADDUSRW",
                            "Kan inte starta STYRMAN/USRADD! \n" );
	    }   
	}
}

void frmAddUser::slotUserIdEntered()
{
    Userid=LineEditUserId->text();
    Userid=Userid.upper();
    LineEditUserId->setText((Userid));
}

void frmAddUser::slotNameEntered()
{
    Namn=LineEditName->text();
}

void frmAddUser::slotAvdEntered()
{
     Avd=LineEditAvd->text();
}

void frmAddUser::slotGruppEntered()
{
    Grupp=LineEditGrupp->text();
}

void frmAddUser::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddUser::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddUser::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OLFIX - ADDUSRW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "OLFIX - ADDUSRW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditUserId->clear();
	LineEditName->clear();
	LineEditAvd->clear();
	LineEditGrupp->clear();
	LineEditUserId->setFocus();
	inrad="";
	i = -1;
     }
}

void frmAddUser::pushBtnHelp_clicked()
{
	inrad="";
	frmAddUser::readResursFil();		// Hämta path till hj�lpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ADMINISTRATION.html";
	hjelpfil=hjelpfil+"#NYUSER";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	LineEditUserId->setFocus();

}

void frmAddUser::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               	*/
    /* Plocka fram var hjälpfilen finns			 */
    /*****************************************************/

    QStringList lines;
    QString homepath;
    homepath=QDir::homeDirPath();
/*    qDebug("Home Path=%s",homepath.latin1());		*/

    QFile f1( homepath+"/.olfixrc" );
   if ( f1.open( IO_ReadOnly ) ) {
        QTextStream stream( &f1 );
        QString line;
        int rad = -1;
        while ( !stream.eof() ) {
            line = stream.readLine(); /* line of text excluding '\n'	*/
	rad=line.find( QRegExp("HELPFILE="), 0 );
	if(rad == 0){
	    hjelpfil=line;
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	    hjelpfil=(hjelpfil.right(hjelpfil.length() - 9));
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	}
            lines += line;
        }
    }
    f1.close();
}

void frmAddUser::checkHost()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "HOSTCHK");	// OLFIX funktion

    frmAddUser::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddUser::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddUser::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfHostProcess() ) );

    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/HOSTCHK!\n");
	QMessageBox::warning( this, "ADDUSRW",
                           "Kan inte starta STYRMAN/HOSTCHK! \n" );
    }   
}

void frmAddUser::slotEndOfHostProcess()
{
    int i;
    QString host;
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "OLFIX - ADDUSRW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
    }
    i = -1;
   /*                                                   Start     2007-11-28                                         */
    int   m2, l1, l2;
    
    int m1=inrad.find( QRegExp("host="), 0 );
//    qDebug("inrad=%s längd=%d",inrad.latin1(),inrad.length());
    m2=inrad.length();
    l1=m2-(m1+5);
    l2=m2-m1;
    host=inrad.mid(5,l1);
//    inrad=inrad.mid(m2,inrad.length()-m2);
    
  qDebug("host=%s m1=%d m2=%d l1=%d l2=%d\n",host.latin1(),m1,m2,l1,l2);
    if(host != "127.0.0.1 "){
	 if(host != "localhost "){
	     textLabel1->setText("<u><b>Host</b></u>");
	     textLabelHostName->setText(host);
	 }
    }else{
	textLabel1->setText("");
    }
    /*                                                End         2007-11-28                                         */  
}
