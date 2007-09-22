/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DELLEVSW  -  description
                             -------------------
		     version 0.1
    begin                : Fre  12 juli 2007
    modified           : 
    copyright         : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                            *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       	 *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 	 *
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
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;
    QString hjelpfil;
    QString levsettnr;
    QString levsettext;

void frmDelLevsett::init()
{
    getLevsett();			/* Lista befintliga leveranssätt */
    lineEditLevsett->setFocus();
}

void frmDelLevsett::slotLevsett_Entered()
{
    levsettnr=lineEditLevsett->text();
    lineEditLevsett->setText(levsettnr);
//    getRecord();			/* Hämta beskrivning */
    qDebug("Levsettnr=%s  Beskrivning=%s",levsettnr.latin1(),levsettext.latin1());
}

/*
void frmDelLevsett::slotLevsettText_Entered()
{
    levsettext=lineEditText->text();
    lineEditText->setText(levsettext);
//    PushButtonGet->setFocus();
}
*/

void frmDelLevsett::slotGetDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDelLevsett::slotGetDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDelLevsett::slotEndOfGetProcess()
{
       int i=-1;
       i = inrad.find( QRegExp("OK:"), 0 );
       if(i == 0){
//	QMessageBox::information( this, " RGTDEL",
//		"Uppdatering OK!\n" 
//		);
	pushBtnOK->setFocus();
       }

      i = -1;
      i = errorrad.find( QRegExp("Error:"), 0 );
      if (i == 0) {
	QMessageBox::critical( this, "OLFIX - DELLEVSW",
		"ERROR!\n"+errorrad
		);
	errorrad="";
	i = -1;
	lineEditLevsett->setFocus();
	levsettnr="";
      }
}
/*
void frmDelLevsett::slotPushButtonOK_clicked()
{

}
*/
void frmDelLevsett::slotDelLevsett( )
{
	const char *userp = getenv("USER");
                QString usr(userp);
	
	inrad="";
	errorrad="";
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVSDEL");	// OLFIX funktion
	process->addArgument(levsettnr);

	frmDelLevsett::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDelDataOnStdout() ) );
	frmDelLevsett::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDelDataOnStderr() ) );
                frmDelLevsett::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfDelProcess() ) );

	if (levsettnr == ""){
    	    QMessageBox::warning( this, "DELLEVSW",
                      "Leveranssättsnummer saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/LEVSDEL!\n");
		QMessageBox::warning( this, "DELLEVSW",
                            "Kan inte starta STYRMAN/LEVSDEL! \n" );
	    }   
	}
}

void frmDelLevsett::slotDelDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDelLevsett::slotDelDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDelLevsett::slotEndOfDelProcess()
{
       int i=-1;
       i = inrad.find( QRegExp("OK:"), 0 );
       qDebug("i=%d, Inrad =%s",i,inrad.latin1());
       if(i != -1){
	QMessageBox::information( this, " DELLEVSW",
		"Leveranssätt "+levsettnr+" är nu raderat!\n" 
		);
	lineEditLevsett->clear();
	lineEditText->clear();
	levsettnr="";
	inrad="";
	errorrad="";
	getLevsett();	/* Uppdatera listan med leveranssätt */
//	lineEditLevsett->setFocus();
       }

      i = -1;
      i = errorrad.find( QRegExp("Error:"), 0 );
      if (i == 0) {
	QMessageBox::critical( this, "OLFIX - LEVSDEL",
		"ERROR!\n"+errorrad
		);
	errorrad="";
	i = -1;
	lineEditLevsett->setFocus();
	levsettnr="";
    }
}

void frmDelLevsett::PickupLevsett( QListViewItem * item)
{
    lineEditLevsett->clear();
    lineEditText->clear();
    
    if(!item){
	return;
    }
     listViewLevsett->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }
     qDebug("Pickup!");
     lineEditLevsett->setText( item->text( 0 ) );
     lineEditText->setText( item->text( 1 ) );
     levsettnr=lineEditLevsett->text();
     levsettext=lineEditText->text();
     qDebug("levsettnr=%s",levsettnr.latin1());     
     lineEditLevsett->setFocus();
}

void frmDelLevsett::getLevsett()	
{
	const char *userp = getenv("USER");
	QString usr(userp);
	
	listViewLevsett->clear();
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "LEVSLST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/BETLST! %s\n",user);
	
	frmDelLevsett::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDelLevsett::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmDelLevsett::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av LEVSLST ",
                            "Kan inte starta STYRMAN/LEVSLST!\n"
                            );
        }
}

	
void frmDelLevsett::slotEndOfProcess()
{
    QString listrad;
//	rad=&inrad;
//	inrad.latin1();
  char *pos1;
  char *pos2;
  char tmp[MAXSTRING];
  char *tmppek;
  int j,k,l,m;
  char antrad[6]="";
  char levsett[4]="";
  char beskrivning[41]="";

//   qDebug("inrad=%s",inrad.latin1());
    QListViewItem* item;
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "DELLEVSW","ERROR!\n"+errorrad);
	errorrad="";
	i = -1;
    }
	 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "DELLEVSW","Leveranssättsregistret innehåller inga poster!\n");
	i = -1;
    }else{	 
	tmppek=tmp;
	qstrcpy(tmp,inrad);
	pos1=strstr(tmp,"OK: NR_");
	pos2=strstr(tmp,"_:");
	i=pos2-pos1;
	m=i+2;		// startposition för betalningsvillkor
	k=0;
	for (j=7;j<i;j++){
	    antrad[k]=tmp[j];
	    k++;
	};
	i=atoi(antrad);				// i = antal poster
	//    qDebug("antalrader=%d",i);
    
	for (k = 1;k <= i; k++){			// gå igenom alla raderna / posterna
	    l=0;
	    for(j = m; j < sizeof(levsett) + m; j++){
		if(tmp[j] != *("_")){
		    levsett[l]=tmp[j];
		    l++;
		}else{
		    levsett[l] = *("\0");
		    j=sizeof(levsett) + m;
		}
	    }
	    m=m+l+2;			// position för beskrivning
	    l=0;
	    for(j = m; j < sizeof(beskrivning) + m; j++){
		if(tmp[j] != *("_")){
		    beskrivning[l]=tmp[j];
		    l++;
		}else{
		    beskrivning[l] = *("\0");
		    j=sizeof(beskrivning) + m;
		}
	    }
	    m=m+l+2;
	    item = new QListViewItem(listViewLevsett,levsett,beskrivning);
// 	 	rensa betalvilkor,  dagar  och beskrivning
	    for (l=0;l<sizeof(levsett);l++)
		levsett[l]=*("\0");
	    for (l=0;l<sizeof(beskrivning);l++)
		beskrivning[l]=*("\0");	
//	 	rensa listrad 
	}
    }
	    listrad.remove(0,70);   
}

void frmDelLevsett::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmDelLevsett::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmDelLevsett::pushBtnHelp_clicked()
{
	inrad="";
	frmDelLevsett::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ADMINISTRATION.html";
	hjelpfil=hjelpfil+"#DELLEVSETT";		// Lägg till position

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );		// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	lineEditLevsett->setFocus();
}

void frmDelLevsett::readResursFil()
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
