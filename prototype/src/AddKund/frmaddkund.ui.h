/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDKUW  -  description
                             -------------------
		     version 0.2
    begin                   : Lör 5 aug 2003
    modified	: Sön 26 okt 2003
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
 *****************************************************************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qvalidator.h> 		// 2003-10-26
#define MAXSTRING 5000


    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;

    QString kundid;
    QString kundnamn;
    QString kundadress;
    QString postnr;
    QString postadr;
    QString land;
    QString tfnnr;
    QString faxnr;
    QString email;
    QString erref;
    QString erreftfnnr;
    QString errefemail;
    QString seljare;
    QString distrikt;
    QString kundkat;
    QString levplats;
    QString levvillkor;
    QString levsett;
    QString betvillkor;
    QString valuta;
    QString sprakkod;
    QString ordererk;
    QString plocklista;
    QString foljesedel;
    QString expavg;
    QString fraktavg;
    QString kravbrev;
    QString kreditlimit;
    QString drojmalsrenta;
    QString drofmalsfakt;
    QString fritext;
    QString kunddata;		// Alla ovanstående

    QRegExp rx1( "[A-Za-z0-9ÅÄÖåäö]\\w{1,9}" );
    QRegExp rx2( "[0-9]\\d{2}" );
    QRegExp rx3( "[A-Za-z0-9ÅÄÖåäö ]{1,29}" );
    QRegExp rx4( "[1-9]\\d{4}" );
    QRegExp rx5( "[0-9+\\- ]{14}" );
    QRegExp rx6( "[A-Za-z0-9ÅÄÖåäö@\\.]{1,29}" );
    QRegExp rx7( "[A-Za-z0-9ÅÄÖåäö]{3}" );
    QRegExp rx8( "[0-9]{1,3}" );
    QRegExp rx9( "[A-ZÅÄÖ]{3}" );
    QRegExp rx10( "[A-Za-z0-9ÅÄÖåäö]{1,3}" );
    QRegExp rx11( "[J,N]");
    QRegExp rx12( "\\d{1,10}" );
    QRegExp rx13( "[A-Za-z0-9ÅÄÖåäö ]{1,99}" );
    
    QRegExpValidator validator1( rx1, 0 );
    QRegExpValidator validator2( rx2, 0 );
    QRegExpValidator validator3( rx3, 0 );
    QRegExpValidator validator4( rx4, 0 );
    QRegExpValidator validator5( rx5, 0 );
    QRegExpValidator validator6( rx6, 0 );
    QRegExpValidator validator7( rx7, 0 );
    QRegExpValidator validator8( rx8, 0 );
    QRegExpValidator validator9( rx9, 0 );
    QRegExpValidator validator10( rx10, 0 );
    QRegExpValidator validator11( rx11, 0 );
    QRegExpValidator validator12( rx12, 0 );
    QRegExpValidator validator13( rx13, 0 );
    
void frmAddKund::init()
{
    lineEditKundNr->setValidator(&validator1);
    lineEditKundNamn->setValidator(&validator3);
    lineEditKundAdress->setValidator(&validator3);
    lineEditKundPostnr->setValidator(&validator4);
    lineEditKundPostAdress->setValidator(&validator3);
    lineEditKundLand->setValidator(&validator3);
    lineEditKundTftnNr->setValidator(&validator5);
    lineEditKundFaxNr->setValidator(&validator5);
    lineEditKundEmail->setValidator(&validator6);
    lineEditKundErRef->setValidator(&validator3);
    lineEditErRefTfnNr->setValidator(&validator5);
    lineEditKundErRefEmail->setValidator(&validator6);
    lineEditKundSeljare->setValidator(&validator3);
    lineEditKundDistrikt->setValidator(&validator7);
    lineEditKundKategori->setValidator(&validator7);
    lineEditKundStdLevplats->setValidator(&validator2);
    lineEditKundLevvilk->setValidator(&validator2);
    lineEditKundLevsett->setValidator(&validator2);
    lineEditKundBetvilk->setValidator(&validator8);
    lineEditValuta->setValidator(&validator9);
    lineEditSprakkod->setValidator(&validator10);
    lineEditOrdererk->setValidator(&validator11);
    lineEditPlocklista->setValidator(&validator11);
    lineEditFoljesedel->setValidator(&validator11);
    lineEditExpAvgift->setValidator(&validator11);
    lineEditFraktAvgift->setValidator(&validator11);
    lineEditKravbrev->setValidator(&validator11);
    lineEditKreditlimit->setValidator(&validator12);
    lineEditDrojRenta->setValidator(&validator11);
    lineEditDrojFaktura->setValidator(&validator11);
    lineEditFriText->setValidator(&validator13);
    
    lineEditKundNr->setFocus();
}

void frmAddKund::lineEditKundNr_returnPressed()
{
    kundid=lineEditKundNr->text();
    if (kundid == "" ){
    	    QMessageBox::warning( this, "ADDKUW",
                      "KundID måste fyllas i! \n" );
	    lineEditKundNr->setFocus();
	}else{
// Kontrollera att kundnummret inte redan finns.	    
	    CheckKundnr();
	    lineEditKundNamn->setFocus();
	}
}

void frmAddKund::lineEditKundNamn_returnPressed()
{
    kundnamn=lineEditKundNamn->text();
    if (kundnamn == "" ){
    	    QMessageBox::warning( this, "ADDKUW",
                      "Kundnamn måste fyllas i! \n" );
	    lineEditKundNamn->setFocus();
	}else{
	    lineEditKundAdress->setFocus();
	}
}
    
void frmAddKund::lineEditKundAdress_returnPressed()
{
    kundadress=lineEditKundAdress->text();
    lineEditKundPostnr->setFocus();
}


void frmAddKund::lineEditKundPostnr_returnPressed()
{
    postnr=lineEditKundPostnr->text();
    lineEditKundPostAdress->setFocus();
}

void frmAddKund::lineEditKundPostAdress_returnPressed()
{
    postadr=lineEditKundPostAdress->text();
    lineEditKundLand->setFocus();
}

void frmAddKund::lineEditKundLand_returnPressed()
{
    land=lineEditKundLand->text();
    if (land == "" ){
	land="Sverige";
	lineEditKundLand->setText((land));
    }
    lineEditKundTftnNr->setFocus();
}

void frmAddKund::lineEditKundTftnNr_returnPressed()
{
    tfnnr=lineEditKundTftnNr->text();
    lineEditKundFaxNr->setFocus();
}

void frmAddKund::lineEditKundFaxNr_returnPressed()
{
    faxnr=lineEditKundFaxNr->text();
    lineEditKundEmail->setFocus();
}

void frmAddKund::lineEditKundEmail_returnPressed()
{
    email=lineEditKundEmail->text();
    lineEditKundErRef->setFocus();
}

void frmAddKund::lineEditKundErRef_returnPressed()
{
    erref=lineEditKundErRef->text();
    lineEditErRefTfnNr->setFocus();
}

void frmAddKund::lineEditErRefTfnNr_returnPressed()
{
    erreftfnnr=lineEditErRefTfnNr->text();
    lineEditKundErRefEmail->setFocus();
}

void frmAddKund::lineEditKundErRefEmail_returnPressed()
{
    errefemail=lineEditKundErRefEmail->text();
    lineEditKundSeljare->setFocus();
}

void frmAddKund::lineEditKundSeljare_returnPressed()
{
    seljare=lineEditKundSeljare->text();
    lineEditKundDistrikt->setFocus();
}

void frmAddKund::lineEditKundDistrikt_returnPressed()
{
    distrikt=lineEditKundDistrikt->text();
    lineEditKundKategori->setFocus();
}

void frmAddKund::lineEditKundKategori_returnPressed()
{
    kundkat=lineEditKundKategori->text();
    lineEditKundStdLevplats->setFocus();
}

void frmAddKund::lineEditKundStdLevplats_returnPressed()
{
    // Vid leveransplats annat än 001 eller blankt kommer en dialog för registrering av leveransadress upp!
    levplats=lineEditKundStdLevplats->text();
    if (levplats == "001" || levplats == ""){
	lineEditKundLevvilk->setFocus();
    }else{
	createStandardLevPlats();
    }
}

void frmAddKund::lineEditKundLevvilk_returnPressed()
{
    levvillkor=lineEditKundLevvilk->text();
    lineEditKundLevsett->setFocus();
}

void frmAddKund::lineEditKundLevsett_returnPressed()
{
    levsett=lineEditKundLevsett->text();
    // Kontrollera om betalningsvillkor finns!
    lineEditKundBetvilk->setFocus();
}

void frmAddKund::lineEditKundBetvilk_returnPressed()
{
    betvillkor=lineEditKundBetvilk->text();
    lineEditValuta->setFocus();
}

void frmAddKund::lineEditValuta_returnPressed()
{
    valuta=lineEditValuta->text();
    valuta=valuta.upper();
    if (valuta == "" ){
	valuta="SEK";
	lineEditValuta->setText((valuta));
    }    
    lineEditSprakkod->setFocus();
}


void frmAddKund::lineEditSprakkod_returnPressed()
{
    sprakkod=lineEditSprakkod->text();
    if (sprakkod == "" ){
	sprakkod="sv";
	lineEditSprakkod->setText((sprakkod));
    }        
    lineEditOrdererk->setFocus();
}

void frmAddKund::lineEditOrdererk_returnPressed()
{
    ordererk=lineEditOrdererk->text();
    ordererk=ordererk.upper();
    lineEditOrdererk->setText((ordererk));
    lineEditPlocklista->setFocus();
}

void frmAddKund::lineEditPlocklista_returnPressed()
{
    plocklista=lineEditPlocklista->text();    
    plocklista=plocklista.upper();
    lineEditPlocklista->setText((plocklista));
    lineEditFoljesedel->setFocus();
}

void frmAddKund::lineEditFoljesedel_returnPressed()
{
    foljesedel=lineEditFoljesedel->text();    
    foljesedel=foljesedel.upper();
    lineEditFoljesedel->setText((foljesedel));    
    lineEditExpAvgift->setFocus();
}


void frmAddKund::lineEditExpAvgift_returnPressed()
{
    expavg=lineEditExpAvgift->text();    
    expavg=expavg.upper();
    lineEditExpAvgift->setText((expavg));        
    lineEditFraktAvgift->setFocus();
}

void frmAddKund::lineEditFraktAvgift_returnPressed()
{
    fraktavg=lineEditFraktAvgift->text();    
    fraktavg=fraktavg.upper();
    lineEditFraktAvgift->setText((fraktavg));        
    lineEditKravbrev->setFocus();
}

void frmAddKund::lineEditKravbrev_returnPressed()
{
    kravbrev=lineEditKravbrev->text();
    kravbrev=kravbrev.upper();
    lineEditKravbrev->setText((kravbrev));    
    lineEditKreditlimit->setFocus();
}


void frmAddKund::lineEditKreditlimit_returnPressed()
{
    kreditlimit=lineEditKreditlimit->text();
    lineEditDrojRenta->setFocus();
}

void frmAddKund::lineEditDrojRenta_returnPressed()
{
    drojmalsrenta=lineEditDrojRenta->text();    
    drojmalsrenta=drojmalsrenta.upper();
    lineEditDrojRenta->setText((drojmalsrenta));        
    lineEditDrojFaktura->setFocus();
}

void frmAddKund::lineEditDrojFaktura_returnPressed()
{
    drofmalsfakt=lineEditDrojFaktura->text();    
    drofmalsfakt=drofmalsfakt.upper();
    lineEditDrojFaktura->setText((drofmalsfakt));        
    lineEditFriText->setFocus();
}

void frmAddKund::lineEditFriText_returnPressed()
{
    fritext=lineEditFriText->text();
    pushButtonOK->setFocus();
}

void frmAddKund::pushButtonOK_clicked()
{
    QString skilj;
    skilj="_:_";
    kunddata=skilj;
    kunddata.append(kundid);
    kunddata.append(skilj);
    kunddata.append(kundnamn);
    kunddata.append(skilj);
    kunddata.append(kundadress);
    kunddata.append(skilj);
    kunddata.append(postnr);
    kunddata.append(skilj);
    kunddata.append(postadr);
    kunddata.append(skilj);
    kunddata.append( land);
    kunddata.append(skilj);    
    kunddata.append(tfnnr);
    kunddata.append(skilj);
    kunddata.append(faxnr);
    kunddata.append(skilj);
    kunddata.append(email);
    kunddata.append(skilj);
    kunddata.append(erref);
    kunddata.append(skilj);
    kunddata.append(erreftfnnr);
    kunddata.append(skilj);
    kunddata.append( errefemail);
    kunddata.append(skilj);    
    kunddata.append(seljare);
    kunddata.append(skilj);
    kunddata.append(distrikt);
    kunddata.append(skilj);    
    kunddata.append(kundkat);
    kunddata.append(skilj);
    kunddata.append(levplats);
    kunddata.append(skilj);
    kunddata.append(levvillkor);
    kunddata.append(skilj);
    kunddata.append(levsett);
    kunddata.append(skilj);
    kunddata.append(betvillkor);
    kunddata.append(skilj);    
    kunddata.append(valuta);
    kunddata.append(skilj);
    kunddata.append(sprakkod);
    kunddata.append(skilj);
    kunddata.append(ordererk);
    kunddata.append(skilj);
    kunddata.append(plocklista);
    kunddata.append(skilj);
    kunddata.append(foljesedel);
    kunddata.append(skilj);
    kunddata.append(expavg);
    kunddata.append(skilj);    
    kunddata.append(fraktavg);
    kunddata.append(skilj);
    kunddata.append(kravbrev);
    kunddata.append(skilj);
    kunddata.append(kreditlimit);
    kunddata.append(skilj);
    kunddata.append(drojmalsrenta);
    kunddata.append(skilj);
    kunddata.append(drofmalsfakt);
    kunddata.append(skilj);
    kunddata.append(fritext);
    kunddata.append(skilj);
    qDebug("kunddata=%s",kunddata.latin1());    
    updateKundreg();
}

void frmAddKund::updateKundreg()
{
/************************************************************************/
/*	Uppdatera databasen med den nya kunden.				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("KUADD");
	process->addArgument(kunddata);
	frmAddKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotUpdateEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta ADDKUW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ADDKUW! \n" );
	}
}

void frmAddKund::slotUpdateEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDKUW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
    }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDKUW",
		"Uppdatering OK!\n"+errorrad
	);
	AddLevplats001();		// Registrering av leveransplats 001
	kunddata="";
	lineEditKundNr->clear();
	lineEditKundNamn->clear();
	lineEditKundAdress->clear();
	lineEditKundPostnr->clear();
	lineEditKundPostAdress->clear();
	lineEditKundLand->clear();
	lineEditKundTftnNr->clear();
	lineEditKundFaxNr->clear();
	lineEditKundEmail->clear();
	lineEditKundErRef->clear();
	lineEditErRefTfnNr->clear();
	lineEditKundErRefEmail->clear();
	lineEditKundSeljare->clear();
	lineEditKundDistrikt->clear();
	lineEditKundKategori->clear();
	lineEditKreditlimit->clear();
	lineEditFriText->clear();
    }
     lineEditKundNr->setFocus();
     errorrad="";
     inrad="";
}

void frmAddKund::CheckKundnr()
{
/************************************************************************/
/*	Kontrollera om kundnr redan finns					*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("KUCHK");
	process->addArgument( kundid);
	frmAddKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotCheckEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta ADDKUW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ADDKUW/KUCHK! \n" );
	}
}

void frmAddKund::slotCheckEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	// Kundnummer finns ej, kan användas!
	lineEditKundNamn->setFocus();
	errorrad="";
    }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::warning( this, "ADDKUW",
		"Kundnummer finns redan\n"+errorrad
	);
    lineEditKundNr->setFocus();
    inrad="";
    }
}

void frmAddKund::createStandardLevPlats()
{
/************************************************************************/
/*	Skapa leveransplats 002, en andra leveransadressen för en kund.		*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "ADDLEVPW");	// OLFIX program
	process->addArgument(kundid);
	process->addArgument(levplats);
	frmAddKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotPlatsEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta ADDLEVPW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ADDLEVPW! \n" );
	}
}


void frmAddKund::slotPlatsEndOfProcess()
{
 // testa om leveransplatsen blev registrerad
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::warning( this, "ADDKUW",
		"Kunde inte lägga upp leveransadressen. Får läggas upp manuellt\n"+errorrad);
	errorrad="";
    }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
//	QMessageBox::information( this, "ADDKUW","Leveransadressen skapad!\n"+errorrad);
    inrad="";
    }
     lineEditKundLevvilk->setFocus();
}

void frmAddKund::AddLevplats001()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "STYRMAN");	// OLFIX funktion
	process->addArgument( usr);
	process->addArgument( "SLPADD");	// OLFIX funktion
	process->addArgument(kundid);
	process->addArgument("001");		// leveransadress nr 001
	process->addArgument(kundadress);
	process->addArgument(postnr);
	process->addArgument(postadr);
	process->addArgument(land);
	frmAddKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmAddKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotPlats001EndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta STYRMAN/SLPADD! \n" );
	}
}

void frmAddKund::slotPlats001EndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::warning( this, "ADDKUW",
		"Kunde inte lägga upp adress 001. Får läggas upp manuellt\n"+errorrad);
	errorrad="";
    }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "ADDKUW","Kundadress nr 001 skapad!\n"+errorrad);
    inrad="";
    }
}

void frmAddKund::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmAddKund::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}
