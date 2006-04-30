/****************************************************************/
/**		CHGBARW					*/
/**		2003-06-06				*/
/**		Version: 0.4.3				*/
/**		Modifierad: 2006-04-30			*/
/**		Jan Pihlgren	jan@pihlgren.se		*/
/****************************************************************/
/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *********************************************** *****************/
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>		
#include <qfile.h>
#include <qregexp.h> 
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString arid;
    QString benamn;
    QString arstart;
    QString arslut;
    QString arlast;		// Låst bokföringsår, default N
    QString beskattar;
    QString senverdat;
    QString vernr;		// Nästa verifikationsnummer, default 1
    QString ktoplan;

    QString hjelpfil;
    
void frmChgBar::init()
{
    LineEditBar->clear();
    LineEditBar->setFocus();
}
 
void frmChgBar::LineEditBar_returnPressed()
{
    arid="";
    arid=LineEditBar->text();
    arid=arid.stripWhiteSpace();
    arid=arid.upper();
    LineEditBar->setText((arid));
    if(arid != ""){
	frmChgBar::slotGetBar();
    }else{
	LineEditBar->setFocus();
    }
}
    
void frmChgBar::slotChgBar()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);
	 arlast.append("N");
	 
//	 qDebug("Utgående data\n %s\n %s\n %s\n %s\n %s\n %s\n %s\n %s\n %s\n",arid.latin1(),benamn.latin1(),arstart.latin1(),arslut.latin1(),arlast.latin1(),beskattar.latin1(),senverdat.latin1(),vernr.latin1(),ktoplan.latin1());
		    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARCHG");	// OLFIX funktion
	process->addArgument(arid);
	process->addArgument(benamn);
	process->addArgument(arstart);
	process->addArgument(arslut);
	process->addArgument(arlast);
	process->addArgument(beskattar);
	process->addArgument(senverdat);
	process->addArgument(vernr);
	process->addArgument(ktoplan);
	
	frmChgBar::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgBar::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgBar::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	   

	if (vernr == ""){
	    vernr.append("1");
	}

	if (arid == "" ){
    	    QMessageBox::warning( this, "CHGBARW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BARCHG!\n");
		QMessageBox::warning( this, "CHGBARW",
                            "Kan inte starta STYRMAN/BARCHG! \n" );
	    }
	}
}


void frmChgBar::LineEditBenamn_returnPressed()
{
    benamn=LineEditBenamn->text();
    LineEditStartdatum->setFocus();
}

void frmChgBar::LineEditStartdatum_returnPressed()
{
    arstart=LineEditStartdatum->text();
    if (arstart == ""){
	QMessageBox::warning( this, "CHGBARW",
                      "Startdatum måste fyllas i! \n" );
	LineEditStartdatum->setFocus();
     }
    LineEditSlutdatum->setFocus();
}

void frmChgBar::LineEditSlutdatum_returnPressed()
{
    arslut=LineEditSlutdatum->text();
    if (arslut==""){
	QMessageBox::warning( this, "CHGBARW",
                      "Slutdatum måste fyllas i! \n" );
	LineEditSlutdatum->setFocus();
	    }
    LineEditBeskattAr->setFocus();
}

void frmChgBar::LineEditBeskattAr_returnPressed()
{
    beskattar=LineEditBeskattAr->text();
    if (beskattar==""){
	QMessageBox::warning( this, "CHGBARW",
                      "Beskattningsår måste fyllas i! \n" );
	LineEditBeskattAr->setFocus();
	    }
    LineEditNestaVerNr->setFocus();
}

void frmChgBar::LineEditNestaVerNr_returnPressed()
{
    vernr=LineEditNestaVerNr->text();
    if (vernr==""){
	vernr.append("1");
    }
    LineEditKontoplan->setFocus();
}


void frmChgBar::LineEditKontoplan_returnPressed()
{
    ktoplan=LineEditKontoplan->text();
   if (ktoplan==""){
	QMessageBox::warning( this, "CHGBARW",
                      "Kontoplan måste fyllas i! \n" );
	LineEditKontoplan->setFocus();
	    }
   PushButtonOK->setFocus();
}

void frmChgBar::PushButtonOK_clicked()
{
//    arlast.append("N");
    frmChgBar::slotChgBar();
}


void frmChgBar::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgBar::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmChgBar::slotEndOfProcess()
{
    int i=-1;
    int j=-1;
    
//    qDebug("inrad=%s",inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
//	qDebug("frmChgBar-inrad=%s i=%d\n",errorrad.latin1(),i);
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - BARCHG",
		"ERROR!\n"+errorrad 
	);
	errorrad="";
	i = -1;
    }
    j = -1;
    j = errorrad.find( QRegExp("BARCHG INSERT error:"), 0 );
    if(j == 0){
	QMessageBox::information( this, "BARCHG - Error!",
		"Felaktigt  bokföringsår \n" 
	);
	errorrad="";
	j = -1;
    }
    i = -1;
    i = inrad.find( QRegExp("OK:"), 0 );  
    if(i == 0){
	QMessageBox::information( this, "BARCHG",
		"Uppdatering OK!\n" 
	);
    LineEditBar->clear();
    LineEditBenamn->clear();
    LineEditStartdatum->clear();
    LineEditSlutdatum->clear();
    LineEditBeskattAr->clear();
//	    LineEditNestaVerNr->clear();
    LineEditKontoplan->clear();
    arlast=("");
    inrad="";
    i = -1;
   }
    PushButtonQuit->setFocus();
}


void frmChgBar::slotGetBar()
{
	const char *userp = getenv("USER");
                QString usr(userp);
	inrad=""; 		    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "BARDSP");	// OLFIX funktion
	process->addArgument(arid);
	
	frmChgBar::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotGetDataOnStderr() ) );
	frmChgBar::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotGetDataOnStdout() ) );
                frmChgBar::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetEndOfProcess() ) );	   
	    
	if (arid == "" ){
    	    QMessageBox::warning( this, "CHGBARW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/BARDSP!\n");
		QMessageBox::warning( this, "CHGBARW",
                            "Kan inte starta STYRMAN/BARDSP! \n" );
	    }
	}    
}

void frmChgBar::slotGetDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgBar::slotGetDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmChgBar::slotGetEndOfProcess()
{
    int i=-1;
    int j1,j2;   
//    qDebug("inrad=%s",inrad.latin1());
     i = errorrad.find( QRegExp("Error:"), 0 );
//    qDebug("frmChgBar-inrad=%s i=%d\n",inrad.latin1(),i);
     if (i == 0) {
		QMessageBox::critical( this, "OLFIX - BARDSP",
			"ERROR!\n"+errorrad 
		);
	            errorrad="";
		i = -1;
		LineEditBar->setFocus();
     }
     i = inrad.find(QRegExp("OK:"),0);
     if (i == 0){
	 arid="";
	 benamn="";
	 j1 = inrad.find(QRegExp("ARID:"),0);
	 j2 = inrad.find(QRegExp("BENAMN:"),0);
//	 qDebug("BARDSP=%s\n",inrad.mid(i+5,2).latin1());
	 arid=inrad.mid(j1+5,j2-j1-7);
             LineEditBar->setText((arid));
	 j1 = inrad.find(QRegExp("BENAMN:"),0);
 	 j2 = inrad.find(QRegExp("ARSTART:"),0);
	 benamn=inrad.mid(j1+7,j2-j1-9);
	 LineEditBenamn->setText(benamn);
	 j1 = inrad.find(QRegExp("ARSTART:"),0);
	 j2 = inrad.find(QRegExp("ARSLUT:"),0);
	 arstart=inrad.mid(j1+8,j2-j1-10);
	 LineEditStartdatum->setText(arstart);
 	 j1 = inrad.find(QRegExp("ARSLUT:"),0);
 	 j2 = inrad.find(QRegExp("ARLAST:"),0);
	 arslut=inrad.mid(j1+7,j2-j1-9);
	 LineEditSlutdatum->setText(arslut);
	 j1 = inrad.find(QRegExp("SVERDAT:"),0);
	 j2 = inrad.find(QRegExp("VERNR:"),0);	 
	 senverdat=inrad.mid(j1+8,j2-j1-10);
	 LineEditSenVerDat->setText(senverdat);
	 j1 = inrad.find(QRegExp("VERNR:"),0);
	 j2 = inrad.find(QRegExp("KTOPLAN:"),0);
	 vernr=inrad.mid(j1+6,j2-j1-8);
	 LineEditNestaVerNr->setText(vernr);
	 j1 = inrad.find(QRegExp("KTOPLAN:"),0);
	 j2 = inrad.find(QRegExp("BESKATT:"),0);	 
	 ktoplan=inrad.mid(j1+8,j2-j1-10);
	 LineEditKontoplan->setText(ktoplan);
	 j1 = inrad.find(QRegExp("BESKATT:"),0);
	 beskattar=inrad.mid(j1+8,4);
	 LineEditBeskattAr->setText(beskattar);
	 }
}


void frmChgBar::pushBtnHelp_clicked()
{
	inrad="";
	frmChgBar::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_EKONOMI.html";
	hjelpfil=hjelpfil+"#ENDRABAR";		// Lägg till position
	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	LineEditBar->setFocus();
}

void frmChgBar::readResursFil()
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

