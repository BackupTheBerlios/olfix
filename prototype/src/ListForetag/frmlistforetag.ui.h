/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTFORW  -  description
                             -------------------
		     version 0.2
    begin                : Ons 10 nov  2004
    modified:         : Ons 14 febr 2007
    copyright            : (C) 2004 by Jan Pihlgren
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
	QProcess* proc;
	QString inrad;
	QString errorrad;
	QString* rad;
	QString newdatabase;
	QString val="3";		/* val=3  = listning*/
	QString hjelpfil;
	

void frmListForetag::init()
{
    PushButtonSluta->setFocus();
    listDatabaser(val);
}	

void frmListForetag::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmListForetag::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
}

void frmListForetag::listDatabaser(QString choise)
{
	const char *userp = getenv("USER");
                QString usr(userp);
	inrad="";
	
	process = new QProcess();
	process->addArgument( "./DATABASE");	// OLFIX funktion
	process->addArgument(choise);
	process->addArgument(newdatabase);		// Kan vara blank
	
	frmListForetag::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListForetag::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
                frmListForetag::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcessList() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "Start av DATABASE ", "Kan inte starta DATABASE!\n");
        }
}

void frmListForetag::slotEndOfProcessList()
{
    QListViewItem* item;
    ListView1->setSorting(0,TRUE);
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
//	   lineEditNyDatabas->clear() ;
	   ListView1->setFocus();
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
	     PushButtonSluta->setFocus();
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
			item = new QListViewItem(ListView1,p);
		    }
		    n++;
		}
	    }
	}
  //     qDebug("EndOfProcess():: inrad=%s",inrad.latin1());  
    }
//    fprintf(stderr,"Klart!\n");
}

void frmListForetag::pushButtonHelp()
{
    Help();
}

void frmListForetag::Help()
{
	inrad="";
	readResursFil();					// Hämta path till hjälpfilen
	
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

void frmListForetag::readResursFil()
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
