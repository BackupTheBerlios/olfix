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
		     version 0.2
    begin                : Tors 9 okt 2003
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

    QString kreditdagar;
    QString kreditkod;
    QString exportkod;
    QString skattekod;
    QString rabattkod;
    QString samfaktura;
    QString skuld;
    QString kravdatum;
    QString orderstock;
    
    QString kunddata;		// Alla ovanstående
    
void frmChgKund::init()
{
    lineEditKundNr->setFocus();
}

void frmChgKund::lineEditKundNr_returnPressed()
{
    kundid=lineEditKundNr->text();
    if (kundid == "" ){
    	    QMessageBox::warning( this, "ADDKUW",
                      "KundID måste fyllas i! \n" );
	    lineEditKundNr->setFocus();
    }else{
	    GetKund();
    }
}

/* ================================================*/
void frmChgKund::lineEditKundNamn_returnPressed()
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
    
void frmChgKund::lineEditKundAdress_returnPressed()
{
    kundadress=lineEditKundAdress->text();
    lineEditKundPostnr->setFocus();
}


void frmChgKund::lineEditKundPostnr_returnPressed()
{
    postnr=lineEditKundPostnr->text();
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
    lineEditKundStdLevplats->setFocus();
}

void frmChgKund::lineEditKundStdLevplats_returnPressed()
{
    // Vid leveransplats annat än 001 eller blankt kommer en widget för registrering av leveransadress upp!
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
    kreditlimit=lineEditKreditlimit->text();
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

void frmChgKund::pushButtonOK_clicked()
{
    QString skilj;
    skilj="_:_";
    kunddata=skilj;
    kunddata.append(kundid);		// 10
    kunddata.append(skilj);
    kunddata.append(kundnamn);		// 11
    kunddata.append(skilj);
    kunddata.append(kundadress);		// 12
    kunddata.append(skilj);
    kunddata.append(postnr);		// 13
    kunddata.append(skilj);
    kunddata.append(postadr);		// 14
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
    kunddata.append(erreftfnnr);		// 20
    kunddata.append(skilj);
    kunddata.append( errefemail);		// 21
    kunddata.append(skilj);    		
    kunddata.append(seljare);		// 22
    kunddata.append(skilj);		
    kunddata.append(distrikt);		// 23
    kunddata.append(skilj);    
    kunddata.append(kundkat);		// 24
    kunddata.append(skilj);
    kunddata.append(levplats);		// 25
    kunddata.append(skilj);
    kunddata.append(levvillkor);		// 26
    kunddata.append(skilj);
    kunddata.append(levsett);		// 27
    kunddata.append(skilj);
    kunddata.append(betvillkor);		// 28
    kunddata.append(skilj);    
    kunddata.append(valuta);		// 29
    kunddata.append(skilj);
    kunddata.append(sprakkod);		// 30
    kunddata.append(skilj);
    kunddata.append(ordererk);		// 31
    kunddata.append(skilj);
    kunddata.append(plocklista);		// 32
    kunddata.append(skilj);
    kunddata.append(foljesedel);		// 33
    kunddata.append(skilj);
    kunddata.append(expavg);		// 34
    kunddata.append(skilj);    
    kunddata.append(fraktavg);		// 35
    kunddata.append(skilj);
    kunddata.append(kravbrev);		// 36
    kunddata.append(skilj);
    kunddata.append(kreditlimit);		// 37
    kunddata.append(skilj);
    kunddata.append(drojmalsrenta);	// 38
    kunddata.append(skilj);
    kunddata.append(drofmalsfakt);		// 39
    kunddata.append(skilj);
    kunddata.append(fritext);		// 40
    kunddata.append(skilj);
    kunddata.append(kreditdagar);		// 41
    kunddata.append(skilj);
    kunddata.append(kreditkod);		// 42
    kunddata.append(skilj);
    kunddata.append(exportkod);		// 43
    kunddata.append(skilj);
    kunddata.append(skattekod);		// 44
    kunddata.append(skilj);
    kunddata.append(rabattkod);		// 45
    kunddata.append(skilj);
    kunddata.append(samfaktura);		// 46
    kunddata.append(skilj);
    
//    qDebug("pushButtonOK_clicked::kunddata=%s",kunddata.latin1());
    updateKundreg();
}

/* ================================================*/


void frmChgKund::updateKundreg()
{
/************************************************************************/
/*	Uppdatera databasen med de ändrade uppgifterna.			*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "STYRMAN");	// OLFIX funktion
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
/************************************************************************/
/*	Hämta kunddata							*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "STYRMAN");	// OLFIX funktion
	process->addArgument(usr);
	process->addArgument("KUDSP");
	process->addArgument( kundid);
	frmChgKund::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmChgKund::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmChgKund::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetEndOfProcess() ) );

	if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta DSPKUW!\n");
		QMessageBox::warning( this, "",
                            "Kan inte starta DSPKUW/KUDSP! \n" );
	}
}


void frmChgKund::slotGetEndOfProcess()
{
    int i,m;
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
	 int i42 = inrad.length();
		 
	 m=i2-i1;
	 if (i1 != -1){
	     kundid=inrad.mid(i1+3,m-offset);
	     lineEditKundNr->setText(kundid);
	 }

 	 m=i3-i2;
	 if (i2 != -1){
//	     kundorgnr=inrad.mid(i2+2,m-offset);
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
	 }
	 
	 m=i34-i33;
	 if (i33 != -1){
	     exportkod=inrad.mid(i33+3,m-offset);
	    lineEditExportkod->setText(exportkod);
	 }
	 
 	 m=i35-i34;
	 if (i34 != -1){
	    skattekod=inrad.mid(i34+3,m-offset);
	    lineEditSkattekod->setText(skattekod);
	 }

 	 m=i36-i35;
	 if (i35 != -1){
	    rabattkod=inrad.mid(i35+3,m-offset);
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
/*	Skapa leveransplats 002, en andra leveransadressen för en kund.		*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument( "ADDLEVPW");	// OLFIX program
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
		"Kunde inte lägga upp leveransadressen. Får läggas upp manuellt\n"+errorrad);
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
	process->addArgument( "LSTKUW");	// OLFIX program
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
