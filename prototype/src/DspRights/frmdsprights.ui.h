/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
			  DSPRGTW  -  description
			     -------------------
		     version 0.1
    begin                : Tis    14 dec 2007
    modified	         :     
    copyright        : (C) 2003 by Jan Pihlgren
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
#define MAXSTRING 15000

QProcess* process;
QProcess* proc;
QString inrad;
QString errorrad;
QString* rad;
QString UserID;
QString Funk;
bool flag;
QString hjelpfil;
QString host;


void frmDspRights::init()
{
    getHost();
    lineEditUserID->setFocus();
}

void frmDspRights::slotUserIDEntered()
{
    UserID=lineEditUserID->text();
    UserID=UserID.upper();
    lineEditUserID->setText((UserID));
    if(UserID==""){
	PushButtonQuit->setFocus();
    }else{
//	checkUser(UserID);
	PushButtonOK->setFocus();
    }
}


void frmDspRights::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
	//	qWarning( "slotDataOnStdout: UserID=%s \n", inrad.latin1() );
    }
}

void frmDspRights::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
	//	qWarning( "slotDataOnErrout: UserID=%s \n", inrad.latin1() );
    }
    
}

void frmDspRights::slotGetRights()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    QString bibl;
    
    inrad="";
    errorrad="";
//    qDebug("GetRights");
    process = new QProcess();
    process->addArgument("./STYRMAN");
    process->addArgument(usr);		// userid
    process->addArgument( "RGTLST");		// OLFIX funktion
        
    frmDspRights::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmDspRights::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmDspRights::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfGetRightsProcess() ) );
    
    if ( !process->start() ) {
	// error handling
	qDebug("Problem starta STYRMAN/RGTLST!\n");
	QMessageBox::warning( this, "Start av RGTLST ",
			      "Kan inte starta STYRMAN/RGTLST!\n"
			      );
    }    
}

void frmDspRights::slotEndOfGetRightsProcess() 
{
    
    QString listrad;
    char usr[21];
    rad=&inrad;
    inrad.latin1();
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int j,k,l,m;
    char antrad[6]="";
    char userid[21]="";
    char trnsid[9]="";

    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "DSPRGTW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	return;
    }
//    qDebug("EndOfGetRightsProcess");
    /*                                                   Start                                              */
    QString host="";
    int l1, l2, m1, m2;    
    m1=inrad.find( QRegExp("host="), 0 );
    m2=inrad.find( QRegExp("NR_"), 0 );
    l1=m2-(m1+5);
    l2=m2-m1;
    host=inrad.mid(5,l1);
    inrad=inrad.mid(m2,inrad.length()-m2);    
    /*                                                End                                                */
    
    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"NR_");
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första trnsid.
    //    fprintf(stdout,"i=%d  m=%d",i,m);
    k=0;
    for (j=3;j<i;j++){
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(userid) + m; j++){
	    if(tmp[j] != *("_")){
		userid[l]=tmp[j];
		l++;
	    }else{
		userid[l] = *("\0");
		j=sizeof(userid) + m;
	    }
	}
	//	fprintf(stdout,"%s  ",user);
	m=m+l+2;	// position för userid
	l=0;
	for(j = m; j < sizeof(trnsid) + m; j++){
	    if(tmp[j] != *("_")){
		trnsid[l]=tmp[j];
		l++;
	    }else{
		trnsid[l] = *("\0");
		j=sizeof(trnsid) + m;
	    }
	}
	//	fprintf(stdout,"%s  ",userid);
	m=m+l+2;
	qstrcpy(usr,userid);
//	qDebug("userid=%s UserID=%s",usr,UserID.latin1());
	if(userid==UserID){
	    item = new QListViewItem(listViewBehor,trnsid);
	}
	// 	 rensa trnsid, userid 
	for (l=0;l<sizeof(trnsid);l++)
	    trnsid[l]=*("\0");
	for (l=0;l<sizeof(userid);l++)
	    userid[l]=*("\0");
	//	 rensa listrad
	listrad.remove(0,70);
    }
    PushButtonQuit->setFocus();
}

void frmDspRights::slotEndOfCheckUserProcess(){
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::warning( this, "DSPRGTW",
			       errorrad
			       );
	errorrad="";
	i = -1;
	lineEditUserID->setFocus();
	lineEditUserID->selectAll();
	UserID="";
	return;
    }else{
	return;
    }
}

void frmDspRights::slotHelp()
{
	inrad="";
	readResursFil();			// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ADMINISTRATION.html";
	hjelpfil=hjelpfil+"#BEHORIG";			// Lägg till position
/*	qDebug("hjelpfil=%s",hjelpfil.latin1());	*/

	proc = new QProcess();
	proc->addArgument( "./OLFIXHLP" );			// OLFIX program
	proc->addArgument(hjelpfil);

	if ( !proc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmDspRights::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var hjälpfilen finns		               */
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

void frmDspRights::getHost()
{
  QString rcfil;
  QStringList lines;
  QString homeDir( QDir::homeDirPath() );
   rcfil.append(homeDir);
   rcfil.append("/.olfixrc");	// configfil
// Läs in config filen här
   QFile file(rcfil);
   if ( file.open( IO_ReadOnly ) ) {
	QTextStream stream( &file );
	QString line;
	while ( !stream.eof() ) {
	    line = stream.readLine(); // line of text excluding '\n'
	    int i = line.find( QRegExp("HOST="), 0 );    // i == 1
	    if ( i == 0){
	    	int l =line.length();
	    	host = line.mid(5,l);
	    }
            lines += line;
	}
    file.close();
   }
       /*                                                   Start     2007-12-13                                         */    
    if(host != "127.0.0.1 "){
	 if(host != "localhost "){
	     textLabel1->setText("<u><b>Host</b></u>\n");
	     textLabelHostName->setText(host);
	 }
    }else{
	textLabel1->setText("");
    }
    /*                                                End         2007-12-13                                         */
}
