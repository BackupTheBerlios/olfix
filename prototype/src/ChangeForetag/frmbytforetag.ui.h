/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          BYTFTGW  -  description
                             -------------------
		     version 0.4
    begin                   	: Sön   19 okt    2003
    modified:   	: Tisd  12 dec   2005, Rewriten.
    copyright            	: (C) 2003 by Jan Pihlgren
    email                	: jan@pihlgren.se
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
#include <qfont.h>
#include <qlistview.h>
#define MAXSTRING 5000

	QProcess* process;
	QProcess* proc;
	QString inrad;
//	QString inraddb;
	QString errorrad;
	QString* rad;

	QString foretag;
	QString dbnr;
//	QString newforetag;
	QString database;
	QString newdatabase="";
	QString hjelpfil;
//	QString db;
	QString usr;
	QString val;		/* Vilken funktion i programmet DATABASE skall exekveras */
	int flag;
	
//	void which_database();
	// void checkDatabase(QString db,QString usr);
	
void frmBytForetag::init()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    getDatabase();
    val = "3";			// Lista befintliga databaser utom databasen mysql
    frmBytForetag::listDatabaser(val);
    lineEditDatabas->setText(database);
    listViewDatabas->setFocus();
}

void frmBytForetag::pickupDatabas( QListViewItem * item )
{
    char databas[30]="";
//    qDebug("PickupDatabas\n");
    if(!item){
	return;
    }
     listViewDatabas->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }
     strcpy(databas,item->key(0,TRUE));
     newdatabase=databas;
     lineEditNyDatabas->setText((newdatabase));
//    val="4";			/* Finns databasen? */
     frmBytForetag::checkDatabaseExist();
     
//     pushButtonDo->setFocus();
}

void frmBytForetag::checkDatabaseExist()
{
    errorrad="";
    inrad="";	     
    val="4";
    listDatabaser(val);
}

void frmBytForetag::getDatabase()
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
	    int i = line.find( QRegExp("DATABASE="), 0 );    // i == 1
	    if ( i == 0){
	    	int l =line.length();
	    	database = line.mid(9,l);
	    }
            lines += line;
	}
    file.close();
   }
//   qDebug("getDatabase::databas=%s",database.latin1());	
}

void frmBytForetag::setDatabase()
{
    QString command;
    command="sed -e s/DATABASE=";
    command.append(database);
    command.append("/DATABASE=");
    command.append(newdatabase);
    command.append("/ $HOME/.olfixrc > $HOME/olfixtst.tmp");	/* 2005-09-25 */
/*    qDebug("command=%s",command.latin1());			*/
    system(command);
    command="mv $HOME/olfixtst.tmp $HOME/.olfixrc";
/*    qDebug("command=%s",command.latin1());			*/
    system(command);
//    fprintf(stdout,"Databas=%s\n",newdatabase.latin1());	/* 2005-03-03	*/
    val="2";
    listDatabaser(val);			/* Starta om OLFIXW */
    pushButtonOK->setFocus();
}

void frmBytForetag::slotHelp()
{
	inrad="";
	frmBytForetag::readResursFil();			// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_DATABASER.html";
	hjelpfil=hjelpfil+"#DATABASBYT";			// Lägg till position
/*	qDebug("hjelpfil=%s",hjelpfil.latin1());	*/

	proc = new QProcess();
	proc->addArgument( "./OLFIXHLP" );			// OLFIX program
	proc->addArgument(hjelpfil);

	if ( !proc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmBytForetag::readResursFil()
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

void frmBytForetag::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmBytForetag::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmBytForetag::listDatabaser(QString choise)
{
	const char *userp = getenv("USER");
                QString usr(userp);
	inrad="";
	
	process = new QProcess();
//	process->addArgument("./STYRMAN");
//	process->addArgument(usr);			// userid
	process->addArgument( "./DATABASE");	// OLFIX funktion
	process->addArgument(choise);
	process->addArgument(newdatabase);		// Kan vara blank
	
/*	qDebug("choise=%s",choise.latin1());	*/

	frmBytForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmBytForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
                frmBytForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcessList() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "Start av DATABASE ", "Kan inte starta DATABASE!\n");
        }
}

void frmBytForetag::slotEndOfProcessList()
{
    QListViewItem* item;
    listViewDatabas->setSorting(0,TRUE);
    int n,j,k=0;
    int i=-1;
    QString temp1;
    QString temp2;
    QString p;
//    qDebug("val=%s",val.latin1());
//    qDebug("inrad=%s",inrad.latin1());
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "BYTFW",
		"ERROR!\n"+errorrad
	);
	if (val=="4"){
	   lineEditNyDatabas->clear() ;
	   listViewDatabas->setFocus();
	}  
	errorrad="";
	i = -1;
	return;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 if (val == "2"){
	     QMessageBox::information( this, "BYTFW",
				       "Databasbyte genomfört!\n"
				       );
	     pushButtonBreak->setFocus();
	 }
	if (val == "3"){
	    i= -1;
	    i = inrad.find(QRegExp("NR_"),0);
	    if( i != -1){
		int m = inrad.find(QRegExp("_:_"),0);
		n=m-(i+3);
  		p=inrad.mid(i+3,n);
//		qDebug("n=%d  m=%d  p=%s",n,m,p.latin1());
		j=p.toInt();
		n=1;
		while (n <= j){
//		    n++;
		    p.setNum(n);
		    temp1="_:_"+p+"_:_";
//		    qDebug("temp1=%s",temp1.latin1());
		    p.setNum(n+1);
		    if(n != j){			
			temp2="_:_"+p+"_:_";
		    }else{
			temp2="_:_";
		    }			
//		    qDebug("temp2=%s",temp2.latin1());
		    m = inrad.find(QRegExp(temp1),0);
		    if (n == j){
			k = inrad.find(QRegExp(temp2),m+9);
//			qDebug("temp2=%s  k=%d",temp2.latin1(),k);
		    }else{
			k = inrad.find(QRegExp(temp2),0);
		    }
		    i = k - (m+temp1.length());
		    p=inrad.mid(m+temp1.length(),i);
		    if(p != "mysql"){
//			qDebug("p=%s",p.latin1());
			item = new QListViewItem(listViewDatabas,p);
		    }
		    n++;
		}
	    }
	}
  //     qDebug("EndOfProcess():: inrad=%s",inrad.latin1());  
    }
//    fprintf(stderr,"Klart!\n");
}
