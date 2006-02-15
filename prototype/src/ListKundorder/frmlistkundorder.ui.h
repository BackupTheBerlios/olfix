/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTORDW  -  description
	          Lista kundorder.
                           -------------------
                           version 0.1
    begin                 : Tis  1 mars 2005
    copyright           : (C) 2003 by Jan Pihlgren
    email                 : jan@pihlgren.se
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
#include <qclipboard.h> 
#define MAXSTRING 5000

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString* rad;
	QString hjelpfil;
	
void frmListKundorder::GetKundorder()	
{
	const char *userp = getenv("USER");
            QString usr(userp);

	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ORDLST2");	// OLFIX funktion,begränsadedata
	
	frmListKundorder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListKundorder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListKundorder::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/LSTORDW!\n");
	    QMessageBox::warning( this, "Start av ORDLST ",
                            "Kan inte starta STYRMAN/ORDLST!\n"
                            );
        }
}

void frmListKundorder::init()
{
//    messages->setColumnAlignment( 1, Qt::AlignRight );
    ListView1->setColumnAlignment(0,Qt::AlignRight);
    ListView1->setColumnAlignment(1,Qt::AlignRight);
    ListView1->setColumnAlignment(2,Qt::AlignHCenter);    
    ListView1->setColumnAlignment(3,Qt::AlignHCenter);
    ListView1->setColumnAlignment(4,Qt::AlignRight);
    PushButtonSluta->setFocus();
    frmListKundorder::GetKundorder();
}	
	
void frmListKundorder::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListKundorder::slotEndOfProcess()
{
    QListViewItem* item;
    int i;
    ListView1->setSorting(0,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTORDW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
    }
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "LSTORDW",
		"Kundorderregistret innehåller inga poster!\n"
		);
	i = -1;
    }
 
    QString listrad;
    rad=&inrad;
    inrad.latin1();
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int j,k,l,m;
//    int antrad;
    char antrad[6]="";
    char ordernr[11]="";
    char kundnr[11]="";
    char levdatum[11]="";
    char orderstatus[2]="";
    char ordersumma[13]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken långt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första Kundordernr.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=7;j<i;j++){	
	antrad[k]=tmp[j];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(ordernr) + m; j++){
	    if(tmp[j] != *("_")){
		ordernr[l]=tmp[j];
		l++;
	    }else{
		ordernr[l] = *("\0");
		j=sizeof(ordernr) + m;
	    }
	}
//	qDebug("%s  ",ordernr);
	m=m+l+2;	// position för kundnr
	l=0;
	for(j = m; j < sizeof(kundnr) + m; j++){
	    if(tmp[j] != *("_")){
		kundnr[l]=tmp[j];
		l++;
	    }else{
		kundnr[l] = *("\0");
		j=sizeof(kundnr) + m;
	    }
	}
//	qDebug("%s  ",kundnr);
	m=m+l+2;	// position för levdatum
	l=0;
	for(j = m; j < sizeof(levdatum) + m; j++){
	    if(tmp[j] != *("_")){
		levdatum[l]=tmp[j];
		l++;
	    }else{
		levdatum[l] = *("\0");
		j=sizeof(levdatum) + m;
	    }
	}
//	qDebug("%s  ",levdatum);
	m=m+l+2;	// position för orderstatus
	l=0;
	for(j = m; j < sizeof(orderstatus) + m; j++){
	    if(tmp[j] != *("_")){
		orderstatus[l]=tmp[j];
		l++;
	    }else{
		orderstatus[l] = *("\0");
		j=sizeof(orderstatus) + m;
	    }
	}
//	qDebug("%s  ",orderstatus);
	m=m+l+2;	// position för ordersumma
	l=0;
	for(j = m; j < sizeof(ordersumma) + m; j++){
	    if(tmp[j] != *("_")){
		ordersumma[l]=tmp[j];
		l++;
	    }else{
		ordersumma[l] = *("\0");
		j=sizeof(ordersumma) + m;
	    }
	}
	
	m=m+l+2;
	item = new QListViewItem(ListView1,ordernr,kundnr,levdatum,orderstatus,ordersumma);
// 	 rensa levnr och namn 
  	for (l=0;l<sizeof(ordernr);l++)
		ordernr[l]=*("\0");
	for (l=0;l<sizeof(ordernr);l++)
		ordernr[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,80);
    }   
}

void frmListKundorder::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
//	qWarning( "slotDataOnErrout: Userid=%s \n", inrad.latin1() );
    }
}

void frmListKundorder::slotReloadLev()
{
    ListView1->clear();
    frmListKundorder::GetKundorder();
}

void frmListKundorder::PushButtonHjelp_clicked()
{
	inrad="";
	frmListKundorder::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_KUNDORDER.html";
	hjelpfil=hjelpfil+"#LISTORDER";		// Lägg till position
	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	PushButtonSluta->setFocus();

}

void frmListKundorder::readResursFil()
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
