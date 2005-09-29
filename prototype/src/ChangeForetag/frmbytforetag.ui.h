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
    begin                   : Sön   19 okt    2003
    modified:	: Tors 29 sept  2005
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
	QString inrad;
	QString inraddb;
	QString errorrad;
	QString* rad;

	QString foretag;
	QString dbnr;
	QString newforetag;
	QString database;
	QString newdatabase;
	QString hjelpfil;
	QString db;
	QString usr;
	int flag;
	
void which_database();
// void checkDatabase(QString db,QString usr);
	
void frmBytForetag::init()
{
    const char *userp = getenv("USER");
    QString tmp(userp);
    usr=tmp;

    getDatabase();
    lineEditForetag->setText(foretag);
    lineEditDatabas->setText(database);
    lineEditNyttForetag->setFocus();
}

void frmBytForetag::lineEditNyttForetag_returnPressed()
{
    newforetag=lineEditNyttForetag->text();
    db=newforetag;
    checkDatabase(newforetag,usr);
    if (flag == -1){
	db=newforetag;
    }else{
	lineEditNyttForetag->setFocus();
    }
//    qDebug("1.flag=%d",flag);  
/*    qDebug("newdatabase= %s        newforetag=%s",newdatabase.latin1(),newforetag.latin1());	*/
    pushButtonDo->setFocus();
}

void frmBytForetag::pushButtonDo_clicked()
{
 
    lineEditForetag->setText(newforetag);
    lineEditDatabas->setText(newdatabase);
    setDatabase();
    pushButtonOK->setFocus();
}

void frmBytForetag::slotButtonHelp_clicked()
{
    frmBytForetag::slotHelp();
    lineEditNyttForetag->setFocus();
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
/*   qDebug("getDatabase::databas=%s",database.latin1());	*/
   if (database=="olfix"){
       foretag="01";
   }
   if (database=="olfixtst"){
       foretag="99";
   }
   if (database != "olfix" and database != "olfixtst"){
       foretag = database.right(2);
   }
   listDatabaser();
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
}

void frmBytForetag::slotHelp()
{
	inrad="";
//	errorrad="";

	frmBytForetag::readResursFil();			// Hämta path till hjälpfilen
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_DATABASER.html";
	hjelpfil=hjelpfil+"#DATABASBYT";			// Lägg till position

//	hjelpfil=hjelpfil+"#BYTAFORETAG";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "OLFIXHLP" );		// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	lineEditNyttForetag->setFocus();
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

void frmBytForetag::checkDatabase(QString db,QString usr)
{
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FORCHK");	// OLFIX funktion
	process->addArgument(db);


	frmBytForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmBytForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmBytForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	if (db == "" ){
    	    QMessageBox::warning( this, "BYTFTGW/FORCHK",
                      "Företag saknas! \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
/*		fprintf(stderr,"Problem starta STYRMAN/FORCHCK!\n");		*/
		QMessageBox::warning( this, "BYTFTGW",
                            "Kan inte starta STYRMAN/FORCHK! \n" );
	    }
	}	
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

void frmBytForetag::slotEndOfProcess()
{
    int h;
    h = -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
//   qDebug("errorrad=%s",errorrad.latin1());	
         if (h != -1) {
	QMessageBox::critical( this, "BYTFTGW",
		"ERROR!\n"+errorrad
	);
	flag=h;
	errorrad="";
	h = -1;
    }else{
//	qDebug("slotEndOfProcess::inrad=%s",inrad.latin1());
	flag=-1;
	
	getDatabasename();
    }	
}

void frmBytForetag::getDatabasename()
{
//             qDebug("getDatabasename()::db=%s",db.latin1());
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FORDSP");	// OLFIX funktion
	process->addArgument(db);


	frmBytForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdoutDbnamn() ) );
	frmBytForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderrDbnamn() ) );
            frmBytForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcessDbnamn() ) );

	if (db == "" ){
    	    QMessageBox::warning( this, "BYTFTGW/FORDSP",
                      "Företag saknas \n" );
	}

	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FORDSP!\n");
		QMessageBox::warning( this, "BYTFTGW",
                            "Kan inte starta STYRMAN/FORDSP! \n" );
	    }
}	

void frmBytForetag::slotDataOnStdoutDbnamn()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inraddb.append(line);
	inraddb.append("\n");
    }
}

void frmBytForetag::slotDataOnStderrDbnamn()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmBytForetag::slotEndOfProcessDbnamn()
{
    int h,tmp;
    h = -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
//   qDebug("%s",errorrad.latin1());
         if (h != -1) {
	QMessageBox::critical( this, "BYTFTGW/FORDSP",
		"ERROR!\n"+errorrad
	);
	flag=h;
	errorrad="";
	h = -1;
    }else{
	 tmp=inraddb.find(QRegExp("_:"),6);
//	 qDebug("inraddb=%s  tmp=%d  length=%d",inraddb.latin1(),tmp,tmp2);
	 newdatabase=inraddb.mid(6,tmp-6);
	 lineEditNyDatabas->setText(newdatabase);
//	 qDebug("newdatabase=%s",newdatabase.latin1());
     }
    inraddb="";
}

void frmBytForetag::listDatabaser()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr);		// userid
	process->addArgument( "FORLST");	// OLFIX funktion

	frmBytForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmBytForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcessList() ) );

        if ( !process->start() ) {
            // error handling
	    QMessageBox::warning( this, "Start av FORLST ", "Kan inte starta FORLST!\n");
        }

}

void frmBytForetag::slotEndOfProcessList()
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

void frmBytForetag::slotPickupDbnr( QListViewItem * item)
{
    char dbnum[9]="";
    if(!item){
	return;
    }
     listView1->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(dbnum,item->key(0,TRUE));
     dbnr=dbnum;
     lineEditNyttForetag->setText((dbnr));
     db=dbnr;
     getDatabasename();
     lineEditNyDatabas->setText(newdatabase);
    pushButtonDo->setFocus();
}
