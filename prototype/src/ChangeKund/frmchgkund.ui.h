/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          CHGKUW  -  description
                             -------------------
		     version 0.5
    begin    	: Tors    9 okt  2003
    modified	: Tors  13 april 2006
    copyright            : (C) 2003 by Jan Pihlgren
    email                    : jan@pihlgren.se
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
#include <qvalidator.h> 		// 2003-10-27
#include <qlistview.h>		// 2006-02-01
#define MAXSTRING 5000


    QProcess* process;
    QString inrad;
    QString* rad;
    QString errorrad;
    QString hjelpfil;

    QString kundid;
    QString kundnamn;
    QString kundorgnr;
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
    QString prislista;
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

    QString kreditdagar;
    QString kreditkod;
    QString exportkod;
    QString skattekod;
    QString rabattkod;
    QString samfaktura;
    QString skuld;
    QString kravdatum;
    QString orderstock;
//    QString prislista;
    
    QString kunddata;		// Alla ovanst�ende
    
    QRegExp rx1( "[A-Za-z0-9������]\\w{1,9}" );
    QRegExp rx2( "[0-9]\\d{2}" );
    QRegExp rx3( "[A-Za-z0-9������ ]{1,29}" );
    QRegExp rx4( "[1-9]\\d{4}" );
    QRegExp rx5( "[0-9+\\- ]{1,14}" );
    QRegExp rx6( "[A-Za-z0-9������@\\.]{1,29}" );
    QRegExp rx7( "[A-Za-z0-9������]{3}" );
    QRegExp rx8( "[0-9]{1,3}" );
    QRegExp rx9( "[A-Z���]{3}" );
    QRegExp rx10( "[A-Za-z0-9������]{1,3}" );
    QRegExp rx11( "[J,N]");
    QRegExp rx12( "[0-9.,]{1,10}" );
    QRegExp rx13( "[A-Za-z0-9������ ]{1,99}" );

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
    
void frmChgKund::init()
{
    lineEditKundNr->setValidator(&validator1);
    lineEditKundNamn->setValidator(&validator3);
    lineEditKundAdress->setValidator(&validator3);
//    lineEditKundPostnr->setValidator(&validator4);	/* 2006-02-01 */
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
    lineEditKreditDagar->setValidator(&validator8);
//    lineEditKreditKod->setValidator(&validator2);
    lineEditExportkod->setValidator(&validator2);
    lineEditSkattekod->setValidator(&validator2);
    lineEditRabattKod->setValidator(&validator2);
    lineEditDrojRenta->setValidator(&validator11);
    lineEditDrojFaktura->setValidator(&validator11);
    lineEditSamFaktura->setValidator(&validator11);
    lineEditFriText->setValidator(&validator13);
    ListKund();
   listViewKund->setFocus();
}

void frmChgKund::lineEditKundNr_returnPressed()
{
    kundid=lineEditKundNr->text();
    if (kundid == "" ){
    	    QMessageBox::warning( this, "CHGKUW",
                      "KundID m�ste fyllas i! \n" );
	    lineEditKundNr->setFocus();
    }else{
	    GetKund();
    }
}
/* ================================================*/
void frmChgKund::listViewKund_clicked( QListViewItem * )
{
      QListViewItem *item = listViewKund->currentItem();
      if ( !item )
        return;
    item->setSelected( TRUE );
    QString temp0=item->text(0);	// kundnr
    lineEditKundNr->setText(temp0);
}
/* ================================================*/
void frmChgKund::lineEditKundNamn_returnPressed()
{
    kundnamn=lineEditKundNamn->text();
    if (kundnamn == "" ){
    	    QMessageBox::warning( this, "CHGKUW",
                      "Kundnamn m�ste fyllas i! \n" );
	    lineEditKundNamn->setFocus();
	}else{
	    lineEditKundOrgnr->setFocus();
	}
}

    
void frmChgKund::lineEditKundOrgnr_returnPressed()
{
    kundorgnr=lineEditKundOrgnr->text();
    lineEditKundAdress->setFocus();
}

void frmChgKund::lineEditKundAdress_returnPressed()
{
    kundadress=lineEditKundAdress->text();
    lineEditKundPostnr->setFocus();
}

void frmChgKund::lineEditKundPostnr_returnPressed()
{
    QString temp;
    postnr=lineEditKundPostnr->text();
    temp=postnr.mid(0,3);
    temp.append(" ");
    temp.append(postnr.mid(3,2));
    postnr=temp;
//	qDebug("postnr=%s\n",postnr.latin1());
    lineEditKundPostnr->setText(postnr);
    
    lineEditKundPostAdress->setFocus();
}

void frmChgKund::lineEditKundPostAdress_returnPressed()
{
    postadr=lineEditKundPostAdress->text();
    lineEditKundLand->setFocus();
}

void frmChgKund::lineEditKundLand_returnPressed()
{
    land=lineEditKundLand->text();
    if (land == "" ){
	land="Sverige";
	lineEditKundLand->setText((land));
    }
    lineEditKundTftnNr->setFocus();
}

void frmChgKund::lineEditKundTftnNr_returnPressed()
{
    tfnnr=lineEditKundTftnNr->text();
    lineEditKundFaxNr->setFocus();
}

void frmChgKund::lineEditKundFaxNr_returnPressed()
{
    faxnr=lineEditKundFaxNr->text();
    lineEditKundEmail->setFocus();
}

void frmChgKund::lineEditKundEmail_returnPressed()
{
    email=lineEditKundEmail->text();
    lineEditKundErRef->setFocus();
}

void frmChgKund::lineEditKundErRef_returnPressed()
{
    erref=lineEditKundErRef->text();
    lineEditErRefTfnNr->setFocus();
}

void frmChgKund::lineEditErRefTfnNr_returnPressed()
{
    erreftfnnr=lineEditErRefTfnNr->text();
    lineEditKundErRefEmail->setFocus();
}

void frmChgKund::lineEditKundErRefEmail_returnPressed()
{
    errefemail=lineEditKundErRefEmail->text();
    lineEditKundSeljare->setFocus();
}

void frmChgKund::lineEditKundSeljare_returnPressed()
{
    seljare=lineEditKundSeljare->text();
    lineEditKundDistrikt->setFocus();
}

void frmChgKund::lineEditKundDistrikt_returnPressed()
{
    distrikt=lineEditKundDistrikt->text();
    lineEditKundKategori->setFocus();
}

void frmChgKund::lineEditKundKategori_returnPressed()
{
    kundkat=lineEditKundKategori->text();
   lineEditKundPrislista->setFocus();
}

void frmChgKund::lineEditKundPrislista_returnPressed()
{
    prislista=lineEditKundPrislista->text();
    lineEditKundStdLevplats->setFocus();
}

void frmChgKund::lineEditKundStdLevplats_returnPressed()
{
    // Vid leveransplats annat �n 001 eller blankt kommer en widget f�r registrering av leveransadress upp!
    levplats=lineEditKundStdLevplats->text();
    if (levplats == "001" || levplats == ""){
	lineEditKundLevvilk->setFocus();
    }else{
	createStandardLevPlats();
    }
}

void frmChgKund::lineEditKundLevvilk_returnPressed()
{
    levvillkor=lineEditKundLevvilk->text();
    lineEditKundLevsett->setFocus();
}

void frmChgKund::lineEditKundLevsett_returnPressed()
{
    levsett=lineEditKundLevsett->text();
    // Kontrollera om betalningsvillkor finns!
    lineEditKundBetvilk->setFocus();
}

void frmChgKund::lineEditKundBetvilk_returnPressed()
{
    betvillkor=lineEditKundBetvilk->text();
    lineEditValuta->setFocus();
}

void frmChgKund::lineEditValuta_returnPressed()
{
    valuta=lineEditValuta->text();
    valuta=valuta.upper();
    if (valuta == "" ){
	valuta="SEK";
	lineEditValuta->setText((valuta));
    }    
    lineEditSprakkod->setFocus();
}


void frmChgKund::lineEditSprakkod_returnPressed()
{
    sprakkod=lineEditSprakkod->text();
    if (sprakkod == "" ){
	sprakkod="sv";
	lineEditSprakkod->setText((sprakkod));
    }
    lineEditOrdererk->setFocus();
}

void frmChgKund::lineEditOrdererk_returnPressed()
{
    ordererk=lineEditOrdererk->text();
    ordererk=ordererk.upper();
    lineEditOrdererk->setText((ordererk));
    lineEditPlocklista->setFocus();
}

void frmChgKund::lineEditPlocklista_returnPressed()
{
    plocklista=lineEditPlocklista->text();
    plocklista=plocklista.upper();
    lineEditPlocklista->setText((plocklista));
    lineEditFoljesedel->setFocus();
}

void frmChgKund::lineEditFoljesedel_returnPressed()
{
    foljesedel=lineEditFoljesedel->text();
    foljesedel=foljesedel.upper();
    lineEditFoljesedel->setText((foljesedel));
    lineEditExpAvgift->setFocus();
}


void frmChgKund::lineEditExpAvgift_returnPressed()
{
    expavg=lineEditExpAvgift->text();    
    expavg=expavg.upper();
    lineEditExpAvgift->setText((expavg));        
    lineEditFraktAvgift->setFocus();
}

void frmChgKund::lineEditFraktAvgift_returnPressed()
{
    fraktavg=lineEditFraktAvgift->text();    
    fraktavg=fraktavg.upper();
    lineEditFraktAvgift->setText((fraktavg));        
    lineEditKravbrev->setFocus();
}

void frmChgKund::lineEditKravbrev_returnPressed()
{
    kravbrev=lineEditKravbrev->text();
    kravbrev=kravbrev.upper();
    lineEditKravbrev->setText((kravbrev));    
    lineEditKreditlimit->setFocus();
}


void frmChgKund::lineEditKreditlimit_returnPressed()
{
    int i;
    kreditlimit=lineEditKreditlimit->text();
        
    i = -1;
    i = kreditlimit.find( QRegExp(","), 0 );
    if (i != -1){
	 kreditlimit.replace( QChar(','), "." );
     }
    lineEditKreditlimit->setText(kreditlimit);

    lineEditKreditDagar->setFocus();
}

void frmChgKund::lineEditDrojRenta_returnPressed()
{
    drojmalsrenta=lineEditDrojRenta->text();
    drojmalsrenta=drojmalsrenta.upper();
    lineEditDrojRenta->setText((drojmalsrenta));
    lineEditDrojFaktura->setFocus();
}

void frmChgKund::lineEditDrojFaktura_returnPressed()
{
    drofmalsfakt=lineEditDrojFaktura->text();
    drofmalsfakt=drofmalsfakt.upper();
    lineEditDrojFaktura->setText((drofmalsfakt));
    lineEditSamFaktura->setFocus();
}

void frmChgKund::lineEditFriText_returnPressed()
{
    fritext=lineEditFriText->text();
    pushButtonOK->setFocus();
}

void frmChgKund::lineEditKreditDagar_returnPressed()
{
    kreditdagar=lineEditKreditDagar->text();
    lineEditKreditKod->setFocus();
}

void frmChgKund::lineEditKreditKod_returnPressed()
{
    kreditkod=lineEditKreditKod->text();
    lineEditExportkod->setFocus();
}

void frmChgKund::lineEditExportkod_returnPressed()
{
    exportkod=lineEditExportkod->text();
    lineEditSkattekod->setFocus();
}

void frmChgKund::lineEditSkattekod_returnPressed()
{
    skattekod=lineEditSkattekod->text();
    lineEditRabattKod->setFocus();
}

void frmChgKund::lineEditRabattKod_returnPressed()
{
    rabattkod=lineEditRabattKod->text();
    lineEditDrojRenta->setFocus();
}

void frmChgKund::lineEditSamFaktura_returnPressed()
{
    samfaktura=lineEditSamFaktura->text();
    lineEditFriText->setFocus();
}

void frmChgKund::pushButtonHelp_clicked()
{
    inrad="";				// t�m inputbuffer
    frmChgKund::readResursFil();		// H�mta path till hj�lpfilen
    int i1 = hjelpfil.find( QRegExp(".html"), 0 );
    hjelpfil=hjelpfil.left(i1);
    hjelpfil=hjelpfil+"_KUNDORDER.html";
    hjelpfil=hjelpfil+"#KUNDER";		// L�gg till position

    process = new QProcess();
    process->addArgument( "./OLFIXHLP");	// OLFIX funktion
    process->addArgument(hjelpfil);
	
    frmChgKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmChgKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
    frmChgKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
    if ( !process->start() ) {
	// error handling
    QMessageBox::warning( this, "Start av CHGKUW ", "Kan inte starta OLFIXHLP!\n" );
   }
    lineEditKundNr->setFocus();
}

void frmChgKund::pushButtonOK_clicked()
{
    QString skilj;
    skilj="_:_";
    kunddata=skilj;
    kunddata.append(kundid);		// 10
    kunddata.append(skilj);
    kunddata.append(kundnamn);	// 11
    kunddata.append(skilj);
    kunddata.append(kundadress);	// 12
    kunddata.append(skilj);
    kunddata.append(postnr);		// 13
    kunddata.append(skilj);
    kunddata.append(postadr);	// 14
    kunddata.append(skilj);
    kunddata.append( land);		// 15
    kunddata.append(skilj);
    kunddata.append(tfnnr);		// 16
    kunddata.append(skilj);
    kunddata.append(faxnr);		// 17
    kunddata.append(skilj);
    kunddata.append(email);		// 18
    kunddata.append(skilj);
    kunddata.append(erref);		// 19
    kunddata.append(skilj);
    kunddata.append(erreftfnnr);	// 20
    kunddata.append(skilj);
    kunddata.append( errefemail);	// 21
    kunddata.append(skilj);    		
    kunddata.append(seljare);		// 22
    kunddata.append(skilj);		
    kunddata.append(distrikt);		// 23
    kunddata.append(skilj);    
    kunddata.append(kundkat);	// 24
    kunddata.append(skilj);
    kunddata.append(levplats);	// 25
    kunddata.append(skilj);
    kunddata.append(levvillkor);	// 26
    kunddata.append(skilj);
    kunddata.append(levsett);		// 27
    kunddata.append(skilj);
    kunddata.append(betvillkor);	// 28
    kunddata.append(skilj);    
    kunddata.append(valuta);		// 29
    kunddata.append(skilj);
    kunddata.append(sprakkod);	// 30
    kunddata.append(skilj);
    kunddata.append(ordererk);	// 31
    kunddata.append(skilj);
    kunddata.append(plocklista);	// 32
    kunddata.append(skilj);
    kunddata.append(foljesedel);	// 33
    kunddata.append(skilj);
    kunddata.append(expavg);		// 34
    kunddata.append(skilj);    
    kunddata.append(fraktavg);	// 35
    kunddata.append(skilj);
    kunddata.append(kravbrev);	// 36
    kunddata.append(skilj);
    kunddata.append(kreditlimit);	// 37
    kunddata.append(skilj);
    kunddata.append(drojmalsrenta);	// 38
    kunddata.append(skilj);
    kunddata.append(drofmalsfakt);	// 39
    kunddata.append(skilj);
    kunddata.append(fritext);		// 40
    kunddata.append(skilj);
    kunddata.append(kreditdagar);	// 41
    kunddata.append(skilj);
    kunddata.append(kreditkod);	// 42
    kunddata.append(skilj);
    kunddata.append(exportkod);	// 43
    kunddata.append(skilj);
    kunddata.append(skattekod);	// 44
    kunddata.append(skilj);
    kunddata.append(rabattkod);	// 45
    kunddata.append(skilj);
    kunddata.append(samfaktura);	// 46
    kunddata.append(skilj);
    kunddata.append(prislista);	// 47
    kunddata.append(skilj);
    kunddata.append(kundorgnr);	// 48
    kunddata.append(skilj);
 
//    qDebug("pushButtonOK_clicked::kunddata=%s",kunddata.latin1());
    updateKundreg();
}

/* ================================================*/


void frmChgKund::updateKundreg()
{
/************************************************************************/
/*	Uppdatera databasen med de �ndrade uppgifterna.			*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
qDebug("kunddata=%s",kunddata.latin1());
	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("KUCHG");
	process->addArgument(kunddata);
	frmChgKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmChgKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotUpdateEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta KUCHG!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta STYRMAN/KUCHG! \n" );
	}

}

void frmChgKund::slotUpdateEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGKUW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
    }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "CHGKUW",
		"Uppdatering OK!\n"+errorrad);
    }
     lineEditKundNr->setFocus();
     errorrad="";
     inrad="";
}

void frmChgKund::GetKund()
{
/*************************************************************************/
/*	H�mta kunddata						*/
/*************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "./STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("KUDSP");
	process->addArgument( kundid);
	frmChgKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmChgKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta CHGKUW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta CHGKUW/KUDSP! \n" );
	}
}


void frmChgKund::slotGetEndOfProcess()
{
    int i,m,n;
    int offset=5;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "DSPKUW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;

     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int i1 = inrad.find( QRegExp("01:"), 0 );
	 int i2 = inrad.find( QRegExp("02:"), 0 );
	 int i3 = inrad.find( QRegExp("03:"), 0 );
	 int i4 = inrad.find( QRegExp("04:"), 0 );
	 int i5 = inrad.find( QRegExp("05:"), 0 );
	 int i6 = inrad.find( QRegExp("06:"), 0 );
	 int i7 = inrad.find( QRegExp("07:"), 0 );
	 int i8 = inrad.find( QRegExp("08:"), 0 );
	 int i9 = inrad.find( QRegExp("09:"), 0 );
	 int i10 = inrad.find( QRegExp("10:"), 0 );
	 int i11 = inrad.find( QRegExp("11:"), 0 );
	 int i12 = inrad.find( QRegExp("12:"), 0 );
	 int i13 = inrad.find( QRegExp("13:"), 0 );
	 int i14 = inrad.find( QRegExp("14:"), 0 );
	 int i15 = inrad.find( QRegExp("15:"), 0 );
	 int i16 = inrad.find( QRegExp("16:"), 0 );
	 int i17 = inrad.find( QRegExp("17:"), 0 );
	 int i18 = inrad.find( QRegExp("18:"), 0 );
	 int i19 = inrad.find( QRegExp("19:"), 0 );
	 int i20 = inrad.find( QRegExp("20:"), 0 );
	 int i21 = inrad.find( QRegExp("21:"), 0 );
	 int i22 = inrad.find( QRegExp("22:"), 0 );
	 int i23 = inrad.find( QRegExp("23:"), 0 );
	 int i24 = inrad.find( QRegExp("24:"), 0 );
	 int i25 = inrad.find( QRegExp("25:"), 0 );
	 int i26 = inrad.find( QRegExp("26:"), 0 );
	 int i27 = inrad.find( QRegExp("27:"), 0 );
	 int i28 = inrad.find( QRegExp("28:"), 0 );
	 int i29 = inrad.find( QRegExp("29:"), 0 );
	 int i30 = inrad.find( QRegExp("30:"), 0 );
	 int i31 = inrad.find( QRegExp("31:"), 0 );
	 int i32 = inrad.find( QRegExp("32:"), 0 );
	 int i33 = inrad.find( QRegExp("33:"), 0 );
	 int i34 = inrad.find( QRegExp("34:"), 0 );
	 int i35 = inrad.find( QRegExp("35:"), 0 );
	 int i36 = inrad.find( QRegExp("36:"), 0 );
	 int i37 = inrad.find( QRegExp("37:"), 0 );
	 int i38 = inrad.find( QRegExp("38:"), 0 );
	 int i39 = inrad.find( QRegExp("39:"), 0 );
	 int i40 = inrad.find( QRegExp("40:"), 0 );
	 int i41 = inrad.find( QRegExp("41:"), 0 );
	 int i42 = inrad.find( QRegExp("42:"), 0 );	/* 20060201 prislista.*/
	 int i43 = inrad.find( QRegExp("END:"),0);	/* 20060201 prislista.*/
//	 int i44 = inrad.length();
/*	qDebug("inrad=%s",inrad.latin1()); 	*/
	 m=i2-i1;
	 if (i1 != -1){
	     kundid=inrad.mid(i1+3,m-offset);
	     lineEditKundNr->setText(kundid);
	 }

 	 m=i3-i2;
	 if (i2 != -1){
	     kundorgnr=inrad.mid(i2+3,m-offset);
	     lineEditKundOrgnr->setText(kundorgnr);
	 }

	 m=i4-i3;
	 if (i3 != -1){
	     kundnamn=inrad.mid(i3+3,m-offset);
	     lineEditKundNamn->setText(kundnamn);
	 }

	 m=i5-i4;
	 if (i4 != -1){
	     kundadress=inrad.mid(i4+3,m-offset);
	     lineEditKundAdress->setText(kundadress);
	 }

 	 m=i6-i5;
	 if (i5 != -1){
	     postnr=inrad.mid(i5+3,m-offset);
	     lineEditKundPostnr->setText(postnr);
	 }
	 
	 m=i7-i6;
	 if (i6 != -1){
	     postadr=inrad.mid(i6+3,m-offset);
	     lineEditKundPostAdress->setText(postadr);
	 }

 	 m=i8-i7;
	 if (i7 != -1){
	     land=inrad.mid(i7+3,m-offset);
	     lineEditKundLand->setText(land);
	 }

 	 m=i9-i8;
	 if (i8 != -1){
	     tfnnr=inrad.mid(i8+3,m-offset);
	     lineEditKundTftnNr->setText(tfnnr);
	 }
	 
	 m=i10-i9;
	 if (i9 != -1){
	     email=inrad.mid(i9+3,m-offset);
	     lineEditKundEmail->setText(email);
	 }

 	 m=i11-i10;
	 if (i10 != -1){	     
	     faxnr=inrad.mid(i10+3,m-offset);
	     lineEditKundFaxNr->setText(faxnr);	     
	 }
	 
 	 m=i12-i11;
	 if (i11 != -1){
	     erref=inrad.mid(i11+3,m-offset);
	     lineEditKundErRef->setText(erref);
	 }

 	 m=i13-i12;
	 if (i12 != -1){
	     erreftfnnr=inrad.mid(i12+3,m-offset);
	     lineEditErRefTfnNr->setText(erreftfnnr);
	 }
 
 	 m=i14-i13;
	 if (i13 != -1){
	     errefemail=inrad.mid(i13+3,m-offset);
	     lineEditKundErRefEmail->setText(errefemail);
	 }

 	 m=i15-i14;
	 if (i14 != -1){
	     seljare=inrad.mid(i14+3,m-offset);
	     lineEditKundSeljare->setText(seljare);
	 }

	 m=i16-i15;
	 if (i15 != -1){
	    fritext=inrad.mid(i15+3,m-offset);
	    lineEditFriText->setText(fritext);
	 }

 	 m=i17-i16;
	 if (i16 != -1){
	     valuta=inrad.mid(i16+3,m-offset);
	     lineEditValuta->setText(valuta);
	 }
	 
	 m=i18-i17;
	 if (i17 != -1){
	     betvillkor=inrad.mid(i17+3,m-offset);
	     lineEditKundBetvilk->setText(betvillkor);
	 }
	 
	 m=i19-i18;
	 if (i18 != -1){
	     levvillkor=inrad.mid(i18+3,m-offset);
	     lineEditKundLevvilk->setText(levvillkor);
	 }

	 m=i20-i19;
	 if (i19 != -1){
	     levsett=inrad.mid(i19+3,m-offset);
	     lineEditKundLevsett->setText(levsett);
	 }

	 m=i21-i20;
	 if (i20 != -1){
	     distrikt=inrad.mid(i20+3,m-offset);
	     lineEditKundDistrikt->setText(distrikt);
	 }

	 m=i22-i21;
	 if (i21 != -1){
	    kundkat=inrad.mid(i21+3,m-offset);
	    lineEditKundKategori ->setText(kundkat);
	 }
 
	 m=i23-i22;
	 if (i22 != -1){
	    levplats=inrad.mid(i22+3,m-offset);
	    lineEditKundStdLevplats ->setText(levplats);
	 }
	 
	 m=i24-i23;
	 if (i23 != -1){
	     ordererk=inrad.mid(i23+3,m-offset);
	    lineEditOrdererk ->setText(ordererk);
	 }
	 
	 
	 m=i25-i24;
	 if (i24 != -1){
	     plocklista=inrad.mid(i24+3,m-offset);
	    lineEditPlocklista ->setText(plocklista);
	 }
	 
	 m=i26-i25;
	 if (i25 != -1){
	     foljesedel=inrad.mid(i25+3,m-offset);
	    lineEditFoljesedel->setText(foljesedel);
	 }
	 
	 m=i27-i26;
	 if (i26 != -1){
	     kravbrev=inrad.mid(i26+3,m-offset);
	    lineEditKravbrev ->setText(kravbrev);
	 }
	 
	 m=i28-i27;
	 if (i27 != -1){
	     sprakkod=inrad.mid(i27+3,m-offset);
	    lineEditSprakkod->setText(sprakkod);
	 }
	 	 
 	 m=i29-i28;
	 if (i28 != -1){
	     expavg=inrad.mid(i28+3,m-offset);
	    lineEditExpAvgift->setText(expavg);
	 }
	 
	 m=i30-i29;
	 if (i29 != -1){
	     fraktavg=inrad.mid(i29+3,m-offset);
	    lineEditFraktAvgift->setText(fraktavg);
	 }
	 
	 m=i31-i30;
	 if (i30 != -1){
	     kreditlimit=inrad.mid(i30+3,m-offset);
	    lineEditKreditlimit->setText(kreditlimit);
	 }
	 
	 m=i32-i31;
	 if (i31 != -1){
	    kreditdagar=inrad.mid(i31+3,m-offset);
	    lineEditKreditDagar->setText(kreditdagar);
	 }
	 
	 m=i33-i32;
	 if (i32 != -1){
	    kreditkod=inrad.mid(i32+3,m-offset);
	    lineEditKreditKod->setText(kreditkod);
//  	    qDebug("kreditkod=|%s| ",kreditkod.latin1());
	 }
	 
	 m=i34-i33;
	 if (i33 != -1){
	     exportkod=inrad.mid(i33+3,m-offset);
	     n = exportkod.find( QRegExp(NULL), 0 );
	     if (n == 0){
		 exportkod="";
	     }
	    lineEditExportkod->setText(exportkod);
	 }
	 
 	 m=i35-i34;
	 if (i34 != -1){
	    skattekod=inrad.mid(i34+3,m-offset);
	     n = skattekod.find( QRegExp(NULL), 0 );
	     if (n == 0){
		 skattekod="";
	     }	    
	    lineEditSkattekod->setText(skattekod);
	 }

 	 m=i36-i35;
	 if (i35 != -1){
	    rabattkod=inrad.mid(i35+3,m-offset);
	     n = rabattkod.find( QRegExp(NULL), 0 );
	     if (n == 0){
		 rabattkod="";
	     }	    
	    lineEditRabattKod->setText(rabattkod);
	 }

	 m=i37-i36;
	 if (i36 != -1){
	    drojmalsrenta=inrad.mid(i36+3,m-offset);
	    lineEditDrojRenta->setText(drojmalsrenta);
	 }
	 
	 m=i38-i37;
	 if (i37 != -1){
	     drofmalsfakt=inrad.mid(i37+3,m-offset);
	    lineEditDrojFaktura->setText(drofmalsfakt);
	 }
	 
	 m=i39-i38;
	 if (i38 != -1){
	    samfaktura=inrad.mid(i38+3,m-offset);
	    lineEditSamFaktura->setText(samfaktura);
	 }
	 
	 m=i40-i39;
	 if (i39 != -1){
	    kravdatum=inrad.mid(i39+3,m-offset);
	    lineEditKravDatum->setText(kravdatum);
	 }
	 
	 m=i41-i40;
	 if (i40 != -1){
	    skuld=inrad.mid(i40+3,m-offset);
	    lineEditSkuld->setText(skuld);
	 }
	 
	 m=i42-i41;
	 if (i41 != -1){
	    orderstock=inrad.mid(i41+3,m-offset);
	    lineEditOrderstock->setText(orderstock);
	 }
	 
	 m=i43-i42;				/* 20060201 */
	 if (i42 != -1){
	    prislista=inrad.mid(i42+3,m-offset);
//	    qDebug("prislista=|%s|",prislista.latin1());
	    lineEditKundPrislista->setText(prislista);
	 }
	  
	 inrad="";
	errorrad="";
	inrad="";
	i = -1;
     }
     pushButtonOK->setFocus();
}

void frmChgKund::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmChgKund::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
	//	qDebug("slotDataOnStdout::inrad= %s",inrad.latin1());
    }
}

void frmChgKund::createStandardLevPlats()
{
/************************************************************************/
/*	Skapa leveransplats 002, en andra leveransadressen f�r en kund.		*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "./ADDLEVPW");	// OLFIX program
	process->addArgument(kundid);
	process->addArgument(levplats);
	frmChgKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmChgKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotPlatsEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta ADDLEVPW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta ADDLEVPW! \n" );
	}

}

void frmChgKund::slotPlatsEndOfProcess()
{
 // testa om leveransplatsen blev registrerad
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::warning( this, "CHGKUW",
		"Kunde inte l�gga upp leveransadressen. F�r l�ggas upp manuellt\n"+errorrad);
	errorrad="";
    }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
//	QMessageBox::information( this, "CHGKUW","Leveransadressen skapad!\n"+errorrad);
    inrad="";
    }
     lineEditKundLevvilk->setFocus();
}

void frmChgKund::KundLista_clicked()
{
/************************************************************************/
/*	Starta programmet LSTKUW, Lista kunder				*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "./LSTKUW");	// OLFIX program
	frmChgKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
                frmChgKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotKundlistaEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta LSTKUW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta LSTKUW! \n" );
	}
}

void frmChgKund::slotKundlistaEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "CHGKUW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
    }
     lineEditKundNr->setFocus();
     errorrad="";
     inrad="";
}

void frmChgKund::readResursFil()
{
    /*****************************************************/
    /*  L�s in .olfixrc filen h�r			               */
    /* Plocka fram var hj�lpfilen finns			               */
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

void frmChgKund::slotEndOfProcess()
{
}

void frmChgKund::ListKund()	
{
	const char *userp = getenv("USER");
            QString usr(userp);

	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KULST");	// OLFIX funktion
	
//	fprintf(stderr,"Starta STYRMAN/KULST! %s\n",usr);
//	qDebug("Starta STYRMAN/KULST userid! %s\n",usr.latin1());
	
	frmChgKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmChgKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfListProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KULST!\n");
	    QMessageBox::warning( this, "Start av KULST ",
                            "Kan inte starta STYRMAN/KULST!\n"
                            );
        }
}

void frmChgKund::slotEndOfListProcess()
{
   QListViewItem* item;
    int i;
    listViewKund->setSorting(1,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i != -1) {
	QMessageBox::critical( this, "CHGKUW",	"ERROR!\n"+errorrad);
	errorrad="";
	i = -1;
     }	 
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    
    if (i != -1) {
	QMessageBox::information( this, "CHGKUW","Kundregistret inneh�ller inga poster!\n");
	i = -1;
    }else{
	QString listrad;
	rad=&inrad;
	inrad.latin1();
	char *pos1;
	char *pos2;
	char tmp[MAXSTRING];
	char *tmppek;
	int j,k,l,m;
	char antrad[6]="";
	char kundnr[11]="";
	char namn[61]="";

	tmppek=tmp;
	qstrcpy(tmp,inrad);
	pos1=strstr(tmp,"OK: NR_");	// 7 tecken l�ngt
	pos2=strstr(tmp,"_:");
	i=pos2-pos1;
	m=i+2;		// startposition f�r f�rsta kundnr.
    
//    	qDebug("i=%d  m=%d",i,m);
    
	k=0;
	for (j=7;j<i;j++){	// j = f�rsta positionen f�r antal poster,(OK: NR_4_:4377_:Kund AB_:4379_:Sm�kund AB_:4378_:Storkund AB_:4376_:Test AB_:)
	    antrad[k]=tmp[j];
	    k++;
	}
	i=atoi(antrad);		// i = antal poster
    
//    	qDebug("antrad=%s",antrad);
    
	for (k = 1;k <= i; k++){	// g� igenom alla raderna / posterna
	    l=0;
	    for(j = m; j < sizeof(kundnr) + m; j++){
		if (tmp[j] != *("_")){
		    kundnr[l]=tmp[j];
		    l++;
		}else{
		    kundnr[l] = *("\0");
		    j=sizeof(kundnr) + m;
		}
	    }
//	     qDebug("%s  ",kundnr);
	    m=m+l+2;	// position f�r namn
	    l=0;
	    for(j = m; j < sizeof(namn) + m; j++){
		if (tmp[j] != *("_")){
		    namn[l]=tmp[j];
		    l++;
		}else{
		    namn[l] = *("\0");
		    j=sizeof(namn) + m;
		}
	    }
//	     qDebug("%s  ",namn);
	    m=m+l+2;
	    item = new QListViewItem(listViewKund,kundnr,namn);
// 	     rensa kundnr och namn 
	    for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
	    for (l=0;l<sizeof(namn);l++)
		namn[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,80);
         }    
    }	 
}
