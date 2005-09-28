/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDFORW  -  description
                             -------------------
		     version 0.2
    begin                 : Tis   9 nov  2004
    Modified          : Ons 28 sept 2005
    copyright          : (C) 2003 by Jan Pihlgren
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
#include <qlistview.h>
#include <qwhatsthis.h> 
#define MAXSTRING 5000
#define VERSION "Version: 0.2\n 2005-09-28"

    QProcess* process;
    QString inrad;
    QString inradmysql;
    QString errorrad;
    QString* rad;
    QString dbnr;
    QString dbnamn;
    QString hjelpfil;
    QString passw;
    int flag;

    
    
void frmAddForetag::init()
{
    LineEditdbnr->clear();
    LineEditdbnamn->clear();
    lineEditPassword->clear();
    listDatabaser();
//    qDebug("dbnr=%s, dbnamn=%s)",dbnr.latin1(),dbnamn.latin1());
/*    slottInformation(); Ej längre giltig information	*/
    LineEditdbnr->setFocus();
}
   
void frmAddForetag::slotdbnrEntered()
{
    errorrad="";
    inrad="";
    dbnr=LineEditdbnr->text();
    slotCheckIfExistDbnr();
}

void frmAddForetag::slotdbnamnEntered()
{
    dbnamn=LineEditdbnamn->text();
    dbnamn=dbnamn.lower();
    slotCheckIfExistDbnamn();
    if (flag==0){
	LineEditdbnamn->setFocus();
    }else{
	LineEditdbnamn->setText(dbnamn);
	lineEditPassword->setFocus();
    }
}

void frmAddForetag::lineEditPassword_Entered()
{
    passw=lineEditPassword->text();
    PushButtonOK->setFocus();
}

void frmAddForetag::pushButtonHelp_clicked()
{
	inrad="";
	frmAddForetag::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_DATABASER.html";
	hjelpfil=hjelpfil+"#DATABASNY";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "ADDFORW","Kan inte starta OLFIXHLP!\n" );
	}
	LineEditdbnr->setFocus();
}

void frmAddForetag::slotAddForetag()
{
/************************************************************************/
/*	Skapa databasen i mysql						*/
/************************************************************************/
    const char *userp = getenv("USER");
    QString usr(userp);
    QString user;
    QString sqlfile="/tmp/CreateOLFIXtemplate.sql";
    QString tmpfile="/tmp/CreateOLFIXtemplate.tmp";
    QString newsqlfile="/tmp/CreateOLFIXnew.sql";		    
    QString kommando;
    user=usr.upper();
    /* Editera sqlfilen som ska användas för att skapa den nya databasen */
    kommando="cp ../sql/CreateOLFIXtemplate.sql "+sqlfile;
    system(kommando);
    kommando="sed 's/olfixtemplate/"+dbnamn+"/' "+sqlfile+" > "+tmpfile;
    system(kommando);
    kommando="sed 's/NEWUSER/"+user+"/' "+tmpfile+" > "+newsqlfile;
    system(kommando);
    kommando="rm "+tmpfile;
    system(kommando);
    kommando="rm "+sqlfile;
    system(kommando);
    kommando="sed 's/h00/"+dbnr+"/' "+newsqlfile+" > "+tmpfile;
    system(kommando);
    kommando="sed 's/newdatabase/"+dbnamn+"/' "+tmpfile+" > "+newsqlfile;
    system(kommando);
    kommando="rm "+tmpfile;
    system(kommando);
    /* Skapa databasen */
    kommando="mysql --password="+passw+" < "+newsqlfile;
    system(kommando);
/************************************************************************/
/*	Uppdatera databasen DATABAS					*/
/************************************************************************/
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "FORADD");	// OLFIX funktion
	process->addArgument(dbnr);
	process->addArgument(dbnamn);
	
	frmAddForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
 
	
	if (dbnr == "" || dbnamn ==""){
    	    QMessageBox::warning( this, "ADDFORW",
                      "Databasnummer och/eller databasnamn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FORADD!\n");
		QMessageBox::warning( this, "ADDFORW",
                            "Kan inte starta STYRMAN/FORADD! \n" );
	    }   
	}
}

void frmAddForetag::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddForetag::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmAddForetag::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDFORW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDFORW",
		"Uppdatering OK!\n"+errorrad
	);
	LineEditdbnr->clear();
	LineEditdbnamn->clear();
	lineEditPassword->clear();
	listView1->clear();
	listDatabaser();
	LineEditdbnr->setFocus();
	inrad="";
	i = -1;
     }
}

void frmAddForetag::slottInformation()
{
	QMessageBox::information( this, "ADDFORW",
                   "Databasen MÅSTE fysiskt finnas upplagd! \n\n Denna fuktion uppdaterar bara databasen så att man vet att det \n nya företaget existerar samt möjliggör för användarna att arbeta \n med olika företag." );
}


void frmAddForetag::slotCheckIfExistDbnr()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "FORCHK");	// OLFIX funktion
	process->addArgument(dbnr);

	frmAddForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotCheckDbnrEndOfProcess() ) );
	
	if (dbnr == ""){
    	    QMessageBox::warning( this, "ADDFORW",
                      "Databasnummer och/eller databasnamn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FORCHK!\n");
		QMessageBox::warning( this, "ADDFORW",
                            "Kan inte starta STYRMAN/FORCHK! \n" );
	    }   
	}
}

void frmAddForetag::slotCheckDbnrEndOfProcess()
{
    int i;
    QString message;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
/*    message=errorrad.mid(14,errorrad.length()-14);	*/
     if (i != -1) {
/*	QMessageBox::critical( this, "ADDFORW",
		"ERROR! \n\n"+message
	);	
*/
	errorrad="";
	i = -1;
	LineEditdbnamn->setFocus();
     }
     i = -1;
     
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::critical( this, "ADDFORW",
		"Databasen finns redan!\n"
	);
	inrad="";
	i = -1;
	LineEditdbnr->clear();
	LineEditdbnr->setFocus();
     }
}

void frmAddForetag::listDatabaser()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr);		// userid
	process->addArgument( "FORLST");	// OLFIX funktion

	frmAddForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcessList() ) );

        if ( !process->start() ) {
            // error handling
	    QMessageBox::warning( this, "Start av FORLST ", "Kan inte starta FORLST!\n");
        }

}

void frmAddForetag::slotEndOfProcessList()
{
    QString listrad;
    QListViewItem* item;
    rad=&inrad;
    inrad.latin1();
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int i,j,k,l,m;
    char antrad[6]="";
    char dbnr[4]="";
    char dbnamn[16]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första userid.
//    fprintf(stdout,"i=%d  m=%d",i,m);
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
//    fprintf(stderr," i = %d\n",i);
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(dbnr) + m; j++){
	    if(tmp[j] != *("_")){
		dbnr[l]=tmp[j];
		l++;
	    }else{
		dbnr[l] = *("\0");
		j=sizeof(dbnr) + m;
	    }
	}
//	fprintf(stdout,"%s  ",dbnr);
	m=m+l+2;	// position för databasnummer
	l=0;
	for(j = m; j < sizeof(dbnamn) + m; j++){
	    if(tmp[j] != *("_")){
		dbnamn[l]=tmp[j];
		l++;
	    }else{
		dbnamn[l] = *("\0");
		j=sizeof(dbnamn) + m;
	    }
	}
//	fprintf(stdout,"%s  ",dbnamn);
	m=m+l+2;	// position för databasnamn
	item = new QListViewItem(listView1,dbnr,dbnamn);
 	/* rensa databasbummer och databasnamn */
   	for (l=0;l<sizeof(dbnr);l++)
		dbnr[l]=*("\0");
	for (l=0;l<sizeof(dbnamn);l++)
		dbnamn[l]=*("\0");
	/* rensa listrad */
	listrad.remove(0,70);
    }
//    fprintf(stderr,"Klart!\n");
}

void frmAddForetag::slotCheckIfExistDbnamn()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	   	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "FORLST");	// OLFIX funktion

	frmAddForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotCheckDbnamnEndOfProcess() ) );
	
	if (dbnr == ""){
    	    QMessageBox::warning( this, "ADDFORW",
                      "Databasnummer och/eller databasnamn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "ADDFORW",
                            "Kan inte starta STYRMAN/FORLST! \n" );
	    }   
	}
}

void frmAddForetag::slotCheckDbnamnEndOfProcess()
{
    int i,j,antal;
    QString ant,tmp;
    dbnamn=LineEditdbnamn->text();
    i =- 1;
    i = inrad.find( QRegExp("NR_"), 0 );
    if (i == 0){
	j = inrad.find(QRegExp("_:"),0 );
	ant = inrad.mid(3,j-3);
	antal = ant.toInt();
//	qDebug("j = %d, antal = %d, ant = %s",j,antal,ant.latin1());
	i = -1;
	i = inrad.find(QRegExp(dbnamn),0 );
//	qDebug("dbnamn=%s, i = %d",dbnamn.latin1(),i); 
	if (i != -1){
    		QMessageBox::critical( this, "ADDFORW",
		    "Databasen/företagsnamnet finns redan!\nVälj ett annat namn!\n" );
		dbnamn="";
		LineEditdbnamn->clear();
		LineEditdbnamn->setFocus();
		flag=0;
	}
	checkDb_mysql();
    }
}

void frmAddForetag::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var hjälpfilen finns			               */
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

void frmAddForetag::checkDb_mysql()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	inradmysql="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// Userid
	process->addArgument( "DBCHK");	// OLFIX funktion

	frmAddForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdoutMysql() ) );
	frmAddForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddForetag::connect( process, SIGNAL(processExited() ),this, SLOT(CheckDbmysqlEndOfProcess()) );
	
	if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "ADDFORW",
                            "Kan inte starta STYRMAN/DBCHK! \n" );
	    }   	
}

void frmAddForetag::CheckDbmysqlEndOfProcess()
{
    int i;
    
    flag=0;
    i =- 1;
//    qDebug("inradmysql=%s",inradmysql.latin1());
    i = inradmysql.find( QRegExp("NR_"), 0 );
//    qDebug("i=%d",i);
    if (i == 0){
	i = inradmysql.find(QRegExp(dbnamn),0 );
//	qDebug("dbnamn=%s i=%d",dbnamn.latin1(),i);
	if (i != -1){
    		QMessageBox::critical( this, "ADDFORW/DBCHK",
		    "Databasen/företagsnamnet finns redan!\nVälj ett annat namn!\n" );
		dbnamn="";
		LineEditdbnamn->clear();
		LineEditdbnamn->setFocus();
		flag=0;
	    }else{
		flag=-1;
		lineEditPassword->setFocus();
	    }
	}
}

void frmAddForetag::slotDataOnStdoutMysql()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inradmysql.append(line);
	inradmysql.append("\n");
    }
}

