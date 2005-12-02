/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          SCRHARW  -  description
                             -------------------
		     version 0.2
    begin    	: Sön 28 nov 2005
    modified	: 
    copyright 	: (C) 2005 by Jan Pihlgren
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
#include <qclipboard.h> 			
#include <qapplication.h>		
#define MAXSTRING 5000

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString* rad;
	QString begrepp="1";
	QString soekord;
	QString hjelpfil;
	

void frmSoekArtikel::init()
{
    lineEditSoek->setFocus();
//    frmSoekArtikel::GetArtikel();
}	
	
void frmSoekArtikel::GetArtikel()	
{
	const char *userp = getenv("USER");
            QString usr(userp);
	    inrad="";				// töm inputbuffer
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX huvudprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ARSRCH");	// OLFIX funktion
	process->addArgument(begrepp);
	process->addArgument(soekord);
		
	frmSoekArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmSoekArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmSoekArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if (soekord==""){
	    QMessageBox::warning( this, "SRCHARW ", "Sökordet saknas!\n");
	    lineEditSoek->setFocus();
	}else{
	    if ( !process->start() ) {
                // error handling
		QMessageBox::warning( this, "Start av ARSRCH ", "Kan inte starta STYRMAN/ARSRCH!\n" );
	    }
	}
}
	
void frmSoekArtikel::slotEndOfProcess()
{
  char *pos1;
  char *pos2;
  char tmp[MAXSTRING];
  char *tmppek;
  int j,k,m;
  char antrad[6]="";
  QString ord;
  QString mening;
  QString artikelnr;
  QString benemn1;
  QString benemn2;
  QListViewItem* item;
   int i;
   
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "SRCHARW","ERROR!\n"+errorrad);
	errorrad="";
	i = -1;
    }
//	qDebug("inrad=%s",inrad.latin1()); 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	if (begrepp=="1"){
	    mening=" Artikelregistret innehåller inga poster\n vars artikelnummer innehåller \n";
	}
	if (begrepp=="2"){
	   mening=" Artikelregistret innehåller inga poster\n vars benämning 1 innehåller \n";
	}
	if (begrepp=="3"){
	   mening=" Artikelregistret innehåller inga poster\n vars benämning 2 innehåller \n"; 
	}
	if (begrepp=="4"){
	   mening=" Artikelregistret innehåller inga poster\n vars ursprungsbenämning innehåller \n"; 
	}
	ord="                \"";
	ord.append(soekord);
//	ord=ord.upper();
	mening.append(ord.latin1());
	mening.append("\"");
	QMessageBox::information( this, "SRCHARW",mening); 	
	i = -1;
	lineEditSoek->setFocus();
//	exit(-1);
    }else{	 
	tmppek=tmp;
	qstrcpy(tmp,inrad);
	pos1=strstr(tmp,"OK: NR_");
	pos2=strstr(tmp,"_:");
	i=pos2-pos1;
	m=i+2;		// startposition för artikelnr
	k=0;
	for (j=7;j<i;j++){
	    antrad[k]=tmp[j];
	    k++;
	};
	i=atoi(antrad);				// i = antal poster
	int ant=i;
//	qDebug("antalrader=%d",i);
	j =  inrad.find( QRegExp("_:"), 0); 
//	qDebug("j=%d",j);
	for (k = 0;k < ant; k++){			// gå igenom alla raderna / posterna
	    i = j;
	    j = inrad.find(QRegExp("_:"),i+2);
	    if (j < i){
		k=ant;
	    }
	    m = j - (i+2);
	    artikelnr=inrad.mid(i+2,m);   
//	    qDebug("artikelnr=%s",artikelnr.latin1());
	    i = j;
	    j = inrad.find(QRegExp("_:"),i+2);
	    m = j - (i+2);
	    benemn1=inrad.mid(i+2,m);   
//	    qDebug("benemn1=%s",benemn1.latin1());
	    i = j;
	    j = inrad.find(QRegExp("_:"),i+2);
	    m = j - (i+2);
	    benemn2=inrad.mid(i+2,m);   
//	    qDebug("benemn2=%s",benemn2.latin1());
	    item = new QListViewItem(ListView1,artikelnr,benemn1,benemn2);	    
	}
    }
}

void frmSoekArtikel::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmSoekArtikel::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmSoekArtikel::slotReloadArtikel()
{
    ListView1->clear();
    inrad="";
    frmSoekArtikel::GetArtikel();
}

void frmSoekArtikel::PickupArtikelnr(QListViewItem * item)
{
    QString artikelnr;
    char artikelnummer[31]="";
//    qDebug("PickupArtikelnr\n");
    if(!item){
	return;
    }
     ListView1->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(artikelnummer,item->key(0,TRUE));
     artikelnr=artikelnummer;
//     qDebug("artikelnr=%s",artikelnr.latin1());
     QClipboard *cb = QApplication::clipboard();     
     cb->setText( artikelnr);
}

void frmSoekArtikel::lineEditSoek_returnPressed()
{
    ListView1->clear();
    soekord=lineEditSoek->text();
//    qDebug("soekord=%s",soekord.latin1());
    PushButtonSoek->setFocus();
}

void frmSoekArtikel::radioButton1_selected()
{
    begrepp="1";
    lineEditSoek->clear();
    lineEditSoek->setFocus();
//    qDebug("begrepp=%s",begrepp.latin1());
}

void frmSoekArtikel::radioButton2_selected()
{
    begrepp="2";
    lineEditSoek->clear();
    lineEditSoek->setFocus();
//    qDebug("begrepp=%s",begrepp.latin1());
}

void frmSoekArtikel::radioButton3_selected()
{
    begrepp="3";
    lineEditSoek->clear();
    lineEditSoek->setFocus();
//    qDebug("begrepp=%s",begrepp.latin1());
}

void frmSoekArtikel::radioButton4_selected()
{
    begrepp="4";
    lineEditSoek->clear();
    lineEditSoek->setFocus();
//    qDebug("begrepp=%s",begrepp.latin1());
}


void frmSoekArtikel::ListView1_clicked(QListViewItem * )
{
    QListViewItem *item =  ListView1->currentItem();
    if ( !item )
	return;
    item->setSelected( TRUE );
    soekord=item->text(0);
    lineEditSoek->setText(soekord);
   radioButton1->setChecked(TRUE);
   begrepp="1";
}

void frmSoekArtikel::PushButtonSoek_clicked()
{
    ListView1->clear();
   frmSoekArtikel::GetArtikel();
}

void frmSoekArtikel::pushButtonGetData_clicked()
{
    if (begrepp=="1"){
	const char *userp = getenv("USER");
            QString usr(userp);
	inrad="";				// töm inputbuffer
	
	process = new QProcess();
	process->addArgument( "./DSPARW");	// OLFIX funktion
	process->addArgument(soekord);
	
	frmSoekArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmSoekArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmSoekArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if (soekord==""){
	    QMessageBox::warning( this, "SRCHARW ", "Artikelnummer får inte vara blankt!\n");
	    lineEditSoek->setFocus();
	}else{
	    if ( !process->start() ) {
                // error handling
		QMessageBox::warning( this, "Start av DSPARW ", "Kan inte starta DSPARW!\n" );
	    }
	}
    }else{
	QString mening="Måste vara ett artikelnummer!\n";
	QMessageBox::information( this, "SRCHARW",mening); 
    }
}

void frmSoekArtikel::pushButtonHelp_clicked()
{
	inrad="";				// töm inputbuffer
	frmSoekArtikel::readResursFil();		// Hämta path till hjälpfilen
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ARTIKLAR.html";
	hjelpfil=hjelpfil+"#ARTIKELSOEK";		// Lägg till position

	process = new QProcess();
	process->addArgument( "OLFIXHLP");	// OLFIX funktion
	process->addArgument(hjelpfil);
	
	frmSoekArtikel::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmSoekArtikel::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmSoekArtikel::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av DSPARW ", "Kan inte starta OLFIXHLP!\n" );
	}
	lineEditSoek->setFocus();
}

void frmSoekArtikel::readResursFil()
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

