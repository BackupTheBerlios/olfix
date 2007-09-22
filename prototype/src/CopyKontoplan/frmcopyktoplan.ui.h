/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          CPYKTOW  -  description
                             -------------------
		     version 0.1.1
    begin                	: Lör      3 jan 2004
    modified	: 	: Mån 23 juli 2007
    copyright            : (C) 2003 by Jan Pihlgren
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
/*
KTOADD.c
INPUT:	ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB
    
SQL:	 INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,IB) VALUES
 ("AE","1200","Testkonto","J","1","100","2000","3000","4000","EUBAS97","0.00","0.00") 
*/

/* SELECT KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN
FROM `KTOPLAN` WHERE ARID ='AD' */
/********************************************************************************************************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qdatetime.h>
#include <qstringlist.h> 
#define MAXSTRING 5000
#define MAXPROCESS 500

// SQL
#include <qsqldatabase.h>
#include <qdatatable.h>
#include <qsqlcursor.h>
// Databas
/* Modify the following to match your environment */
#define DRIVER       "QMYSQL3"  /* see the Qt SQL documentation for a list of available drivers */
// #define DATABASE  "test"          /* the name of your database */
#define USER           "olfix"         /* user name with appropriate rights */
#define PASSWORD "olfix"         /* password for USER */
#define HOST           "localhost" /* host on which the database is running */

    QString databas;
    QSqlDatabase * db;
// OLFIX
#define program "CPYKTOW"


    QProcess* process;
    QProcess* proc[200];
    QString inradproc[200];
    QString inrad;
    QString* rad;
    QString errorrad;
    QString hjelpfil;
    bool status=FALSE;
    int procnbr=0;
    bool flag=TRUE;
    
    QString arid;
    QString ktonr;
    QString benamning;
    QString manuell;
    QString momskod;
    QString srunr;
    QString kstalle;
    QString projekt;
    QString subkto;
    QString ktoplan;
    

    QString nybarid;
    QString gammalbarid;
    QString barflag="";
    QStringList kontoplan="";
    QStringList bar ="";

void frmCopyKtoplan::init()
{
    GetDatabas();			/* Ta reda på vilken databas som ska användas, från $HOME/.olfixrc  */
    qDebug("Databas=%s",databas.latin1());
    
    db = QSqlDatabase::addDatabase( DRIVER );
    db->setHostName( HOST );    
    db->setDatabaseName(  databas);
    db->setUserName( USER );
    db->setPassword( PASSWORD );


    if( !db->open() ){
        db->lastError().showMessage( "An error occured. Please read the README file in the sqltable"
                                     "dir for more information.\n\n" );
	qDebug("Error:Kan inte öppna databasen!");
        return;
    }
    check_User();	/* Finns användaren iOLFIX och har vederbörande rättighet att köra detta program */
    getKontoplan();
    lineEditNyttBar->setFocus();
}
    
void frmCopyKtoplan::lineEditNyttBar_returnPressed()
{
    nybarid=lineEditNyttBar->text();
    nybarid=nybarid.upper();
    nybarid=nybarid.stripWhiteSpace();
    lineEditNyttBar->setText((nybarid));
}

void frmCopyKtoplan::lineEditGammaltBar_returnPressed()
{
    gammalbarid=lineEditGammaltBar->text();
    gammalbarid=gammalbarid.upper();
    gammalbarid=gammalbarid.stripWhiteSpace();
    lineEditGammaltBar->setText((gammalbarid));
}

void frmCopyKtoplan::pushButtonKopiera_clicked()
{
    if(nybarid==""){
	QMessageBox::warning( this, "CPYKTOW",
		"Bokföringsåret  måste fyllas i! \n" );
	lineEditNyttBar->setFocus();	
	return;
    }
    if(gammalbarid==""){
	QMessageBox::warning( this, "CPYKTOW",
		"Bokföringsåret  måste fyllas i! \n" );
	lineEditGammaltBar->setFocus();	
	return;
    }
    barflag="NEW";
    frmCopyKtoplan::checkBar(nybarid);
//    qDebug("NEW_Status=%d",status);
    if(status != TRUE){   
  	QMessageBox::warning( this, "CPYKTOW",
		"Felaktigt bokföringsår! \n" );
	lineEditNyttBar->setFocus();	
	return;
    }
   barflag="OLD";
   frmCopyKtoplan::checkBar(gammalbarid);
//   qDebug("OLD_Status=%d",status);
   if(status != TRUE){
       	QMessageBox::warning( this, "CPYKTOW",
		"Felaktigt bokföringsår! \n" );
	lineEditGammaltBar->setFocus();	
	return;
    }
    
    if(status==TRUE){
//	qDebug("createNewKontoplan()");
	createNewKontoplan();		/* Skapa ny kontoplan */
    }else{
	qDebug("status=FALSE");	
    }
}

void  frmCopyKtoplan::checkBar(QString Bar)
{
    QString kto;
    status=FALSE;
    for ( QStringList::Iterator it = kontoplan.begin(); it != kontoplan.end(); ++it ) {
	kto=*it;
//	qDebug("barflag=%s, kto=%s",barflag.latin1(),kto.mid(0,2).latin1());
	if(barflag=="NEW"){
	    if(kto.mid(0,2) != Bar){
		status=TRUE;
//		qDebug("Status_1,NEW=%d",status);
	    }else{
		status=FALSE;
//		qDebug("Status_2,NEW=%d",status);
		return;
	    }
	}
	if(barflag=="OLD"){
	    if(kto.mid(0,2) == Bar){
		status=TRUE;
//		qDebug("Status_1,OLD=%d",status);
		return;
	    }else{
		status=FALSE;
//		qDebug("Status_2,OLD=%d",status);
	    }
	}
    }
//    qDebug("Status=%d",status);
}


void frmCopyKtoplan::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmCopyKtoplan::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmCopyKtoplan::pushBtnHelp_clicked()
{
	inrad="";
	frmCopyKtoplan::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_EKONOMI.html";
	hjelpfil=hjelpfil+"#COPYKTOPLAN";		// Lägg till position

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	lineEditNyttBar->setFocus();
}

void frmCopyKtoplan::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var hjälpfilen finns			               */
    /*****************************************************/

    QStringList lines;
    QString homepath;
    homepath=QDir::homeDirPath();

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
	    hjelpfil=(hjelpfil.right(hjelpfil.length() - 9));
	}
            lines += line;
        }
    }
    f1.close();
}

void frmCopyKtoplan::getKontoplan()
{
/* SELECT KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN
FROM `KTOPLAN` WHERE ARID ='AD' */

	const char *userp = getenv("USER");
                QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTOLST");	// OLFIX funktion
//	process->addArgument(arid);
	frmCopyKtoplan::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmCopyKtoplan::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
                frmCopyKtoplan::connect( process, SIGNAL(processExited() ),this, SLOT(slotKTOLSTEndOfProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "CPYKTOW",
                            "Kan inte starta STYRMAN/KTOLST! \n" );
	    }	
}


void frmCopyKtoplan::slotKTOLSTEndOfProcess()
{
    int i = -1; 
    int j,k,l,m,n;
    QString antal;
    QString rad="";
    QString x;
    
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CPYKTOW",
		"KTOLST ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
	status = -1;
    }else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
//	qDebug("1:: i=%d",i);
	if(i != -1){
	    status = 0;
	}
	i = inrad.find( QRegExp("NR_"), 0 );
//	qDebug("2:: i=%d",i);
	j=inrad.find( QRegExp("_:"), 3 );
//	qDebug("3:: j=%d",j);
	antal=inrad.mid(i+3,j-(i+3));
//	qDebug("antal=%s",antal.latin1());
	k=antal.toInt();
	for (l=0;l<k;l++){
	    for(n=0;n<12;n++){
		m=j;
		j=inrad.find( QRegExp("_:"), m+2 );
//		qDebug("4:: m=%d",m);
		rad=rad+inrad.mid(m+2,j-(m+2));
		rad.append(" ");
		x.setNum(n);
		rad.append(x);
		rad.append(": ");
//		qDebug("rad=%s",rad.latin1());
	    }
	    rad.append("\n");
//	    if(!rad.find( QRegExp(gammalbarid),0 )){
//		qDebug("rad=%s",rad.latin1());
//		kontoplan.append(rad);
//	    }
	    kontoplan.append(rad);   
	    rad="";	    
	}
    }
}

void frmCopyKtoplan::createNewKontoplan()
{
    int i,j;
    QString kto;
    
    const char *userp = getenv("USER");
    QString usr(userp);

    for ( QStringList::Iterator it = kontoplan.begin(); it != kontoplan.end(); ++it ) {
	    kto=*it;
	    if(kto != "" && kto.mid(0,2) == gammalbarid){
//		qDebug("%s kontoplan=%s",kto.mid(0,2).latin1(),kto.latin1());
		arid=nybarid;
//		qDebug("arid=%s",arid.latin1());
		i=kto.find( QRegExp("0:"),0 )+3;
		j=kto.find( QRegExp("1:"),0 );
		ktonr=kto.mid(i,j-i);
//		qDebug("ktonr=%s",ktonr.latin1());
		i=kto.find( QRegExp("1:"),0 )+3;
		j=kto.find( QRegExp("2:"),0 );
		benamning=kto.mid(i,j-i);
//		qDebug("benamning=%s",benamning.latin1());	
		i=kto.find( QRegExp("2:"),0 )+3;
		j=kto.find( QRegExp("3:"),0 );
		manuell=kto.mid(i,j-i);;
//		qDebug("manuell=%s",manuell.latin1());
		i=kto.find( QRegExp("3:"),0 )+3;
		j=kto.find( QRegExp("4:"),0 );
		momskod=kto.mid(i,j-i);;
//		qDebug("momskod=%s",momskod.latin1());
		i=kto.find( QRegExp("4:"),0 )+3;
		j=kto.find( QRegExp("5:"),0 );
		srunr=kto.mid(i,j-i);;
//		qDebug("srunr=%s",srunr.latin1());
		i=kto.find( QRegExp("5:"),0 )+3;
		j=kto.find( QRegExp("6:"),0 );
		kstalle=kto.mid(i,j-i);;
//		qDebug("kstalle=%s",kstalle.latin1());
		i=kto.find( QRegExp("6:"),0 )+3;
		j=kto.find( QRegExp("7:"),0 );
		projekt=kto.mid(i,j-i);;
//		qDebug("projekt=%s",projekt.latin1());
		i=kto.find( QRegExp("7:"),0 )+3;
		j=kto.find( QRegExp("8:"),0 );
		subkto=kto.mid(i,j-i);;
//		qDebug("subkto=%s",subkto.latin1());
		i=kto.find( QRegExp("8:"),0 )+3;
		j=kto.find( QRegExp("9:"),0 );
		ktoplan=kto.mid(i,j-i);;
//		qDebug("ktoplan=%s",ktoplan.latin1());
		addKto();
	}		
        }
}

void frmCopyKtoplan::GetDatabas()
{
   /*****************************************************/
    /*  Läs in .olfixrc filen här			                    */
    /* Plocka fram vilken databas som används		                    */
    /*****************************************************/

    QStringList lines;
    QString homepath;
    homepath=QDir::homeDirPath();

    QFile f1( homepath+"/.olfixrc" );
     if ( f1.open( IO_ReadOnly ) ) {
        QTextStream stream( &f1 );
        QString line;
        int rad = -1;
        while ( !stream.eof() ) {
            line = stream.readLine(); /* line of text excluding '\n'	*/
	rad=line.find( QRegExp("DATABASE="), 0 );
	if(rad == 0){
	    databas=line;
	    databas=(databas.right(databas.length() - 9));
	}
            lines += line;
        }
    }
    f1.close();
}

void frmCopyKtoplan::check_User()
{
                QString quest;      
	QString data;
	const char *userp = getenv("USER");
	QString usr(userp);
	usr=usr.upper();
	quest="select USERID from USR where USERID=";
	quest.append('"');
	quest.append(usr);
	quest.append('"');
//	qDebug("quest=%s",quest.latin1());
	QSqlQuery query(quest,db);
	if(query.isActive()){
	    while(query.next()){
		data = query.value(0).toString();
	    }
//	    qDebug("data=%s",data.latin1());
	    if(data != usr){
	       QMessageBox::warning( this, program,
                            "Användare"+usr+"finns ej!\n"
                            );
	       return;
	   }else{
	       check_Rights();
	}
       }
}

void frmCopyKtoplan::check_Rights()
{
                QString quest="";      
	QString data1="";
	QString data2="";	
	const char *userp = getenv("USER");
	QString usr(userp);
	usr=usr.upper();
	quest="select USERID,TRNSID from RIGHTS where USERID=";
	quest.append('"');
	quest.append(usr);
	quest.append('"');
	quest.append(" and TRNSID = ");
	quest.append('"');
	quest.append(program);
	quest.append('"');
//	qDebug("quest=%s",quest.latin1());
//	qDebug("1: data1=%s data2=%s",data1.latin1(),data2.latin1());
	QSqlQuery query(quest,db);
	if(query.isActive()){
	    while(query.next()){
		data1 = query.value(0).toString();
		data2 = query.value(1).toString();
	    }
//	    qDebug("data1=%s data2=%s",data1.latin1(),data2.latin1());
	    if(data1 != usr and data2 != program){
	       QMessageBox::warning( this, program,
                            "Användare "+usr+" får ej använda "+program+"!\n"
                            );
	       exit(0);
	       return;
	   }
	}
}

void frmCopyKtoplan::addKto()
{
 /*
SQL:	 INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,UB) VALUES
 ("AE","1200","Testkonto","J","1","100","2000","3000","4000","EUBAS97","0.00","0.00") 
*/
    QString quest;
    
    quest="INSERT INTO KTOPLAN(ARID,KTONR,BENAMNING,MANUELL,MOMSKOD,SRUNR,KSTALLE,PROJEKT,SUBKTO,KTOPLAN,IB,UB) VALUES (";
     quest.append('"');
     quest.append(arid);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append(ktonr);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append(benamning);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append(manuell);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append(momskod);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append(srunr);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append(kstalle);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append(projekt);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append(subkto);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append(ktoplan);
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append("0");
     quest.append('"');
     quest.append(", ");
     quest.append('"');     
     quest.append("0");
     quest.append('"');
     quest.append(") ");
     
//     qDebug("quest=%s",quest.latin1());
     QSqlQuery query(quest,db);
     query.exec();

}
