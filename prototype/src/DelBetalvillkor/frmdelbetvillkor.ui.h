/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DELBETVW  -  description
                             -------------------
		     version 0.1
    begin     	: 	Lör 17 febr 2007
    Modified	: 	
    copyright: 	(C) 2003 by Jan Pihlgren
    email       :	 jan@pihlgren.se
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
#include <qregexp.h>
#include <qlistview.h>

#define MAXSTRING 5000

	QProcess* process;
	QProcess* processlist;
	QString inrad;
	QString inradlista;
	QString errorradlista;
	QString errorrad;
	QString hjelpfil;
	QString inrad_u;
	QString listrad;
                QString betvillk;
	QString dagar;
                QString EndFlag;
	QString nbrrows;
	QString database;
	
    

void frmDelBetvillkor::init()
{
    frmDelBetvillkor::listBetvillkor();
    frmDelBetvillkor::getDatabaseName();
    lineEditDatabas->setText(database);
    listViewBetvillkor->setFocus();
}	

void frmDelBetvillkor::slotbetvillkEntered()
{
    betvillk=LineEditBetvillkor->text();
    betvillk=betvillk.upper();
    LineEditBetvillkor->setText((betvillk));
}


void frmDelBetvillkor::slotPushButtonOK_clicked()
{    
    betvillk=LineEditBetvillkor->text();
//    qDebug("betvillk=%s",betvillk.latin1());
    if (betvillk == ""){
	QMessageBox::warning( this, "OLFIX - DELBETVW",
                            "Betalningsvillkor får inte vara blankt!\n"
                            );
	LineEditBetvillkor->setFocus();

    }else{
	slotDelBetvillkor( betvillk );
    }
}

void frmDelBetvillkor::slotDelBetvillkor( QString villk )
{
    	const char *userp = getenv("USER");
                QString usr(userp);
	    
	 inrad="";
	 errorrad="";
//	qDebug("Start Delete!");
                process = new QProcess();
	process->addArgument("./STYRMAN");
	process->addArgument(usr);	
	process->addArgument( "BETVDEL");	// OLFIX program
	process->addArgument( villk );
	frmDelBetvillkor::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDelBetvillkorOnStdout() ) );
	frmDelBetvillkor::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDelBetvillkorOnStderr() ) );
                frmDelBetvillkor::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfDelBetvillkorProcess() ) );

            if ( !process->start() ) {
                // error handling
	QMessageBox::warning( this, "OLFIX - DELBETVW",
                            "Kan inte starta BETVDEL!\n"
                            );
	}
}

void frmDelBetvillkor::slotDelBetvillkorOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDelBetvillkor::slotDelBetvillkorOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmDelBetvillkor::slotEndOfDelBetvillkorProcess()
{
    int i=-1;
    int j=-1;
//    qDebug("errorrad=%s",errorrad.latin1());
      i = -1;
      i = errorrad.find( QRegExp("Error:"), 0 );
      if (i == 0) {
	QMessageBox::critical( this, "OLFIX - BETVDEL",
		"ERROR!\n"+errorrad
		);
	            inrad="";
		i = -1;
      }
      j = -1;
      j = errorrad.find( QRegExp("Error:"), 0 );
      if(j == 0){
	QMessageBox::information( this, "BETVDEL - Error!",
		"Borttagningen av betalningsvillkor misslyckades\n"
		);
	LineEditBetvillkor->setFocus();
	inrad="";
	j = -1;
	return;
       }
       i = -1;       
       i = inrad.find( QRegExp("OK:"), 0 );
       if(i == 0){
	QMessageBox::information( this, "DELBETVW ",
		"Uppdatering OK!\n" 
		);
    }
       LineEditBetvillkor->clear();
       LineEditDagar->clear();
       LineEditBeskrivning->clear();
       
       frmDelBetvillkor::listBetvillkor();
}

void frmDelBetvillkor::listBetvillkor()	
{
    const char *userp = getenv("USER");
    QString usr(userp);
    listViewBetvillkor->clear();
    inradlista="";
    errorradlista="";
	
    processlist = new QProcess();
    processlist->addArgument("./STYRMAN");	// OLFIX styrprogram
    processlist->addArgument(usr);		// betvillk
    processlist->addArgument( "BETLST");	// OLFIX funktion
		
    frmDelBetvillkor::connect( processlist, SIGNAL(readyReadStdout() ),this, SLOT(slotBetvillkorDataOnStdout() ) );
    frmDelBetvillkor::connect( processlist, SIGNAL(readyReadStderr() ),this, SLOT(slotBetvillkorDataOnStderr() ) );	
    frmDelBetvillkor::connect( processlist, SIGNAL(processExited() ),this, SLOT(slotBetvillkorEndOfProcess() ) );	    
 
    if ( !processlist->start() ) {
    // error handling
    QMessageBox::warning( this, "Start av BETLST ",
	"Kan inte starta STYRMAN/BETLST!\n"
                );
    }
}

void frmDelBetvillkor::slotBetvillkorDataOnStdout()
{
    while (processlist->canReadLineStdout() ) {
	QString line = processlist->readStdout();
	inradlista.append(line);
	inradlista.append("\n");
    }
//    qDebug("inradlista=%s",inradlista.latin1());
}

void frmDelBetvillkor::slotBetvillkorDataOnStderr()
{
    while (processlist->canReadLineStderr() ) {
	QString line = processlist->readStderr();
	errorradlista.append(line);
	errorradlista.append("\n");
    }
}

void frmDelBetvillkor::slotBetvillkorEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewBetvillkor->setSorting(0,TRUE);
    i = -1;
    i = errorradlista.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "DELBETVW",
		"ERROR!\n"+errorradlista
	);
	errorradlista="";
	i = -1;
	return;
     }
	 
    i = inradlista.find( QRegExp("NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "DELBETVW",
		"Det finn inga betalningsvillkor registrerade!\n"
	);
	i = -1;
	return;
     }
//    qDebug("inradlista=%s",inradlista.latin1());	 
    
    inradlista.latin1();
    char *pos1;
    char *pos2;
    char tmp[MAXSTRING];
    char *tmppek;
    int j,k,l,m,n1,n2;
    char antrad[6]="";
    QString betvillk="";	// betalningsvillkor nr, 3 tecken 
    QString dagar="";	// antal dagar, 3 tecken
    QString beskr="";		// beskrivning, 40 tecken
    QString temp2="";
    
    tmppek=tmp;
    qstrcpy(tmp,inradlista);
    pos1=strstr(tmp,"NR_");	// 3  tecken långt
    pos2=strstr(tmp,"_:");	// pos2 = första fältet minus2 tecken
    i=pos2-(pos1+3);
    m=i;			// antal tecken i antal poster
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j = 0; j < i ; j++ ){	 // j = förstapositionen för antal poster
	antrad[k]=tmp[j+7];
	k++;
    };
    i=atoi(antrad);		// i = antal poster
    i=i*3;
//    qDebug("i=%d antrad=%s",i,antrad);
    l=0;
    for (k = 1;k <= i; k++){	// gå igenom alla fält / post. Det finn tre fält per post. Antal fält = 3
	for (m=0; m <=2; m++){
//	    qDebug("m=%d",m);
	    n1 = -1;
	    n1 = inradlista.find( QRegExp("_:"), l );	 // start fält nr 1
//	    qDebug("n1=%d",n1);	
	    n2= -1;
	    n2 = inradlista.find( QRegExp("_:"),n1+2); 	// slut fält nr 1
//	    qDebug("n2=%d",n2);	
	    temp2=inradlista.mid(n1+2,n2-n1-2);
//	    qDebug("temp2=%s",temp2.latin1());
	    if(m==0){
		betvillk=temp2;
	    }
	    if(m==1){
		dagar=temp2;
	    }
	    if(m==2){
		beskr=temp2;
	    }
	    l=n2;
	}
//               qDebug("l=%d betvillkor=%s dagar=%s beskriv=%s",l,betvillk.latin1(),dagar.latin1(),beskr.latin1());
	
	item = new QListViewItem(listViewBetvillkor,betvillk,dagar,beskr);	
	k++;
	k++;
    }
}
    
void frmDelBetvillkor::slotPickupbetvillk( QListViewItem * item)
{
    char villkor[4]="";
    char dag[4]="";
    char beskr[41]="";
//    qDebug("Pickupbetvillk\n");
    if(!item){
	return;
    }
     listViewBetvillkor->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(villkor,item->key(0,TRUE));	// = Betallningsvillkor nr
     betvillk=villkor;
     strcpy(dag,item->key(1,TRUE));
     dagar=dag;
     strcpy(beskr,item->key(2,TRUE));   //= Beskrivning
     
     LineEditBetvillkor->setText(betvillk);
     LineEditDagar->setText(dagar);
     LineEditBeskrivning->setText(beskr);
     LineEditBetvillkor->setFocus();
}

void frmDelBetvillkor::pushBtnHelp_clicked()
{
	inrad="";
	frmDelBetvillkor::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ADMINISTRATION.html";
	hjelpfil=hjelpfil+"#DELBETV";			// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());
	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
//	lineEditArtikelNr->setFocus();
}

void frmDelBetvillkor::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			                     */
    /* Plocka fram var hjälpfilen finns		                     */
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

void frmDelBetvillkor::getDatabaseName()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			                     */
    /* Plocka fram vilken databas som används		                     */
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
	rad=line.find( QRegExp("DATABASE="), 0 );
	if(rad == 0){
	    database=line;
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	    database=(database.right(database.length() - 9));
/*	    qDebug("hjelpfil=%s",hjelpfil.latin1());		*/
	}
            lines += line;
        }
    }
    f1.close();
}
