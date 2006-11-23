/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          PRTOFFW  -  description
	         Skriva ut en offert
                             -------------------
		     version 0.5.
    begin   	:	 Ons    22 Nov    2006
    Updated	: 
    copyright:	 (C) 2006 by Jan Pihlgren
    email     	: 	jan@pihlgren.se
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
#define MAXSTRING 5000

    QString printpath;
    QString tmppath;
    QString kugarversion;
    QString kommando;
    QString printfil="Offert.kud";

    QProcess* process;
    QProcess* process4;
    QString inrad;
    QString inrad2;
    QString inrad3;    
    QString inrad4;     
    QString* rad;
    QString errorrad;
    QString errorrad2;
    QString errorrad3;
    QString errorrad4;    
    QString hjelpfil;    

    QString offertdatum;
    QString offertnr;
    QString offertkundnr;
    QString offertkundnamn;
    QString offertkundadress;
    QString offertkundpostnr;
    QString offertkundpostadr;
    QString offertkundland;
    
    QString offertkundref;
    QString offertkundlevadress;
    QString offertkundlevpostnr;
    QString offertkundlevpostadr;
    QString offertkundlevland;
    
    
    QString offerttfnnr;
    QString offertfaxnr;
    QString offerttelexnr;
    QString offertemail;
    QString offertref;
    QString offertreftfnnr;
    QString offertmomskod;
    QString offertmoms;
    QString offertkontonr;
    QString offertpgnr;
    QString offertbgnr;
    QString seljare;
    QString godsmarke;
    QString offertleveranstid;
    QString offertvaluta;
    QString offertbetvillkor;
    QString offertlevvillkor;
    QString offertlevplats;
    QString offertlevsett;
    QString offertstatus;
    QString offerthuvuddata;       
    
    QString ftgnamn;		// 23
    QString ftgadr;		// 24
    QString ftgpostnr;	// 25
    QString ftgpostadr;	// 26
    QString ftgtfn;
    
    /* offert 	*/
    QString offertdel;		/*  Del av offertn, H=offerthuvud, R=offertrad */
    QString offertsumma;
    QString momssumma;	/*  Total moms på offerten */
    QString fraktbelopp;
    QString fraktmomskr;
    QString offerttotal;
//    bool nykundflag=FALSE;
    
void frmPrtOffert::init()
{
    int vecka;
    int year;
    int dag;
    QString dagnummer;
    QString veckonr;
    QString artal;
//    QDateTime dt = QDateTime::currentDateTime();
    dag= QDate::currentDate().dayOfWeek();
//    offertdatum=dt.toString("yyyy-MM-dd");
//    textLabeloffertdatum->setText(offertdatum);    
//    offertleveranstid=offertdatum;
    
    vecka= QDate::currentDate().weekNumber(&year);
    veckonr=QString::number(vecka,10);
    dagnummer=QString::number(dag,10);
    if (veckonr.length() < 2){
	veckonr.prepend("0");
    }
    artal=QString::number(year,10);
      
    frmPrtOffert::listViewRader_format();
    frmPrtOffert::getOffertLista();
    frmPrtOffert::getForetagsdata("FNAMN");
    listViewOffert->setFocus();
//    lineEditOffertNbr->setFocus();

}


void frmPrtOffert::slotPickupoffertnr( QListViewItem * item)
{
    char offertnummer[11]="";
//    qDebug("Pickupoffertnr\n");
    if(!item){
	return;
    }
     listViewOffert->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(offertnummer,item->key(0,TRUE));
     offertnr=offertnummer;
     lineEditOffertNbr->setText((offertnr));
     lineEditOffertNbr->setFocus();
}

void frmPrtOffert::lineEditOffertNbr_returnPressed()
{
    
    offertnr=lineEditOffertNbr->text();
    listViewRader->clear();
    frmPrtOffert::getOfferthuvud();
}

void frmPrtOffert::getOffertLista()
{
	const char *userp = getenv("USER");
	QString usr(userp);
	 inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "OFFLST");	// OLFIX funktion

	frmPrtOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmPrtOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmPrtOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotOffertListaEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFLST ",
                            "Kan inte starta STYRMAN/OFFLST!\n"
                            );
        }
}

void frmPrtOffert::slotOffertListaEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewOffert->setSorting(1,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "PRTOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }

    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "PRTOFFW",
		"Offertregistret innehåller inga poster!\n"
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
    char offertnr[11]="";
    char kundnr[11]="";
    char levdatum[11]="";
    char offertstatus[2]="";
    char offerttotal[14]="";

    tmppek=tmp;
    qstrcpy(tmp,inrad);
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken långt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition för första kundnr.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=7;j<i;j++){	// j = första positionen för antal poster,(OK: NR_4_:4377_:Kund AB_:4379_:Småkund AB_:4378_:Storkund AB_:4376_:Test AB_:)
	antrad[k]=tmp[j];
	k++;
    }
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
	l=0;
	for(j = m; j < sizeof(offertnr) + m; j++){
	    if(tmp[j] != *("_")){
		offertnr[l]=tmp[j];
		l++;
	    }else{
		offertnr[l] = *("\0");
		j=sizeof(offertnr) + m;
	    }
	}
//	qDebug("%s  ",ordnr);
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
	m=m+l+2;	// position för offertstatus
	l=0;
	for(j = m; j < sizeof(offertstatus) + m; j++){
	    if(tmp[j] != *("_")){
		offertstatus[l]=tmp[j];
		l++;
	    }else{
		offertstatus[l] = *("\0");
		j=sizeof(offertstatus) + m;
	    }
	}
	m=m+l+2;	// position för offerttotal
	l=0;
	for(j = m; j < sizeof(offerttotal) + m; j++){
	    if(tmp[j] != *("_")){
		offerttotal[l]=tmp[j];
		l++;
	    }else{
		offerttotal[l] = *("\0");
		j=sizeof(offerttotal) + m;
	    }
	}
	
	m=m+l+2;
	item = new QListViewItem(listViewOffert,offertnr,kundnr,levdatum,offertstatus,offerttotal);
// 	 rensa 
	
  	for (l=0;l<sizeof(offertnr);l++)
		offertnr[l]=*("\0");
  	for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
	for (l=0;l<sizeof(levdatum);l++)
		levdatum[l]=*("\0");
	for (l=0;l<sizeof(offertstatus);l++)
		offertstatus[l]=*("\0");		
	for (l=0;l<sizeof(offerttotal);l++)
		offerttotal[l]=*("\0");	
//	 rensa listrad 
	listrad.remove(0,80);
    }
}

void frmPrtOffert::getOfferthuvud()
{
	const char *userp = getenv("USER");
	QString usr(userp);
	inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "OFFDSP");	// OLFIX funktion
	process->addArgument(offertnr);

	frmPrtOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmPrtOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmPrtOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotofferthuvudEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFDSP ",
                            "Kan inte starta STYRMAN/OFFDSP!\n"
                            );
        }
}

void frmPrtOffert::slotofferthuvudEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "PRTOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;

     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
//	 qDebug("inrad=%s",inrad.latin1());
	 
//	 int i1 = inrad.find( QRegExp("01:"), 0 );
	 int i2 = inrad.find( QRegExp("03:"), 0 );	
	 int i3 = inrad.find( QRegExp("04:"), 0 );
	 int i4 = inrad.find( QRegExp("05:"), 0 );
	 int i5 = inrad.find( QRegExp("06:"), 0 );
	 int i6 = inrad.find( QRegExp("07:"), 0 );
	 int i7 = inrad.find( QRegExp("08:"), 0 );
	 int i8 = inrad.find( QRegExp("09:"), 0 );
	 int i9 = inrad.find( QRegExp("10:"), 0 );
	 int i10 = inrad.find( QRegExp("11:"), 0 );
	 int i11 = inrad.find( QRegExp("12:"), 0 );
	 int i12 = inrad.find( QRegExp("13:"), 0 );
	 int i13 = inrad.find( QRegExp("14:"), 0 );	
	 int i14 = inrad.find( QRegExp("15:"), 0 );
	 int i15 = inrad.find( QRegExp("16:"), 0 );	
	 int i16 = inrad.find( QRegExp("17:"), 0 );
	 int i17 = inrad.find( QRegExp("18:"), 0 );
	 int i18 = inrad.find( QRegExp("19:"), 0 );
	 int i19 = inrad.find( QRegExp("20:"), 0 );
	 int i20 = inrad.find( QRegExp("21:"), 0 );
	 int i21 = inrad.find( QRegExp("22:"), 0 );	
	 int i22 = inrad.find( QRegExp("23:"), 0 );	
	 int i23 = inrad.find( QRegExp("24:"), 0 );
	 int i24 = inrad.find( QRegExp("25:"), 0 );
//	 int i25 = inrad.find( QRegExp("26:"), 0 );
//	 int i26 = inrad.find( QRegExp("27:"), 0 );
//	 int i27 = inrad.find( QRegExp("28:"), 0 );
	 int i28 = inrad.find( QRegExp("29:"), 0 );
	 int i29 = inrad.find( QRegExp("30:"), 0 );
	 int i30 = inrad.find( QRegExp("31:"), 0 );
//	 int i31 = inrad.find( QRegExp("32:"), 0 );
	 int i32 = inrad.find( QRegExp("33:"), 0 );
	 int i33 = inrad.find( QRegExp("34:"), 0 );	
	 int i34 = inrad.find( QRegExp("35:"), 0 );
	 int i35 = inrad.find( QRegExp("36:"), 0 );
	 int i36 = inrad.find( QRegExp("37:"), 0 );
	 int i37 = inrad.find( QRegExp("38:"), 0 );
	 int i38 = inrad.find( QRegExp("END"), 0 );
/*	 int i38 = inrad.find( QRegExp("39:"), 0 );
	 int i39 = inrad.find( QRegExp("40:"), 0 );
	 int i40 = inrad.find( QRegExp("41:"), 0 );
	 int i41 = inrad.find( QRegExp("42:"), 0 );
	 int i42 = inrad.length();			*/
/*
	 m=i2-i1;
	 if (i1 != -1){
	     kundid=inrad.mid(i1+3,m-4);
	     lineEditKundNr->setText(kundid);
	 }
*/
 	 m=i3-i2;
	 if (i2 != -1){
	     offertkundnr=inrad.mid(i2+3,m-4);
	     lineEditOffertKundNr->setText(offertkundnr);
	 }
/*
	 m=i4-i3;
	 if (i3 != -1){				// offerttyp 
	     offertkundnamn=inrad.mid(i3+3,m-4);
	     lineEditKundNamn->setText(offertkundnamn);
	 }
*/
	 m=i5-i4;					// offertstatus
	 if (i4 != -1){
	     offertstatus=inrad.mid(i4+3,m-4);
	     lineEditOffertStatus->setText(offertstatus);
	 }

 	 m=i6-i5;
	 if (i5 != -1){					// offertdatum
	     offertdatum=inrad.mid(i5+3,m-4);
	     textLabelOffertdatum->setText(offertdatum);
	 }

	 m=i7-i6;
	 if (i6 != -1){					// Leveransdatum
	     offertleveranstid=inrad.mid(i6+3,m-4);
	     lineOffertLeveranstid->setText(offertleveranstid);
	 }

 	 m=i8-i7;
	 if (i7 != -1){					// Kundnamn
	     offertkundnamn=inrad.mid(i7+3,m-4);
	     lineEditKundNamn->setText(offertkundnamn);
	 }

 	 m=i9-i8;
	 if (i8 != -1){					// Kundadress
	     offertkundadress=inrad.mid(i8+3,m-4);
	     lineEditKundAdress->setText(offertkundadress);
	 }

	 m=i10-i9;
	 if (i9 != -1){					// Kundpostnummer
	     offertkundpostnr=inrad.mid(i9+3,m-4);
	     lineEditKundPostnr->setText(offertkundpostnr);
	 }

 	 m=i11-i10;
	 if (i10 != -1){					// Kundpostadress
	     offertkundpostadr=inrad.mid(i10+3,m-4);
	     lineEditKundPostAdress->setText(offertkundpostadr);
	 }

 	 m=i12-i11;
	 if (i11 != -1){					// Land
	     offertkundland=inrad.mid(i11+3,m-4);
	     lineEditKundLand->setText(offertkundland);
	 }

 	 m=i13-i12;
	 if (i12 != -1){					// Kundens referens
	     offertkundref=inrad.mid(i12+3,m-4);
	     lineEditKundRef->setText(offertkundref);
	 }

 	 m=i14-i13;
	 if (i13 != -1){					// Leveransadress
	     offertkundlevadress=inrad.mid(i13+3,m-4);
	     lineEditKundLevAdress->setText(offertkundlevadress);
	 }

 	 m=i15-i14;
	 if (i14 != -1){					// Leveranspostnr
	     offertkundlevpostnr=inrad.mid(i14+3,m-4);	
	     lineEditKundLevPostnr->setText(offertkundlevpostnr);
	 }

	 m=i16-i15;
	 if (i15 != -1){					// Leveranspostadress
	    offertkundlevpostadr=inrad.mid(i15+3,m-4);
	    lineEditKundLevPostAdress->setText(offertkundlevpostadr);
	 }

 	 m=i17-i16;
	 if (i16 != -1){					// Leveransland
	     offertkundlevland=inrad.mid(i16+3,m-5);
	     lineEditKundLevLand->setText(offertkundlevland);
	 }

	 m=i18-i17;
/*	 if (i17 != -1){					// Vår referent
	     offertbetvillkor=inrad.mid(i17+3,m-4);
	     lineEditBetvilk->setText(offertbetvillkor);
	 }
*/
	 m=i19-i18;
	 if (i18 != -1){					// Seljare
	     seljare=inrad.mid(i18+3,m-4);
	     lineEditSeljare->setText(seljare);
	 }

	 m=i20-i19;
	 if (i19 != -1){					// Godsmärke
	     godsmarke=inrad.mid(i19+3,m-4);
	     lineEditGodsmarke->setText(godsmarke);
	 }

	 m=i21-i20;
	 if (i20 != -1){					// Betalningsvillkorstyp
/*	     offertbetvillkortyp=inrad.mid(i20+3,m-4);
	     lineEditBetvilk->setText(offertbetvillkortyp);
*/	 }

	 m=i22-i21;
	 if (i21 != -1){					// Betalningsvillkor
	     offertbetvillkor=inrad.mid(i21+3,m-4);
	     lineEditBetvilk->setText(offertbetvillkor);
	 }

	 m=i23-i22;
	 if (i22 != -1){					// Leveransvillkor
	    offertlevvillkor=inrad.mid(i22+3,m-4);
	    lineEditLevvillkor ->setText(offertlevvillkor);
	 }

	 m=i24-i23;
	 if (i23 != -1){					// Leveransplats /LEVSETT)
	    offertlevplats=inrad.mid(i23+3,m-4);
	    lineEditLevplats ->setText(offertlevplats);
	 }
/*
	 m=i25-i24;
	 if (i24 != -1){					// Plocklista
	     plocklista=inrad.mid(i24+3,m-4);
	    lineEditPlocklista ->setText(plocklista);
	 }

	 m=i26-i25;
	 if (i25 != -1){					// Följesedel
	     foljesedel=inrad.mid(i25+3,m-4);
	    lineEditFoljesedel->setText(foljesedel);
	 }

	 m=i27-i26;
	 if (i26 != -1){					// Fraktavgift	
	     kravbrev=inrad.mid(i26+3,m-4);
	    lineEditKravbrev ->setText(kravbrev);
	 }

	 m=i28-i27;
	 if (i27 != -1){					// Skattekod
	     sprakkod=inrad.mid(i27+3,m-4);
	    lineEditSprakkod->setText(sprakkod);
	 }
*/
 	 m=i29-i28;
	 if (i28 != -1){					// Moms i %
	    offertmoms=inrad.mid(i28+3,m-4);
	    lineEditMomskod->setText(offertmoms);
	 }

	 m=i30-i29;
	 if (i29 != -1){					// Valuta
	    offertvaluta=inrad.mid(i29+3,m-4);
	    lineEditValuta->setText(offertvaluta);
	 }
/*
	 m=i31-i30;
	 if (i30 != -1){					// Exportkod
	     kreditlimit=inrad.mid(i30+3,m-4);
	    lineEditKreditlimit->setText(kreditlimit);
	 }

	 m=i32-i31;
	 if (i31 != -1){					//  Språkkod
	     kreditdagar=inrad.mid(i31+3,m-4);
	    lineEditKreditDagar->setText(kreditdagar);
	 }
*/
	 m=i33-i32;
	 if (i32 != -1){					// offertsumma exklusive moms
	    offertsumma=inrad.mid(i32+3,m-4);
	    lineEditOffertSumma->setText(offertsumma);
	 }

	 m=i34-i33;
	 if (i33 != -1){					// Fraktavgift i kronor exklusive moms
	    fraktbelopp=inrad.mid(i33+3,m-4);
	    lineEditOffertFrakt->setText(fraktbelopp);
	 }

 	 m=i35-i34;
	 if (i34 != -1){
	    fraktmomskr=inrad.mid(i34+3,m-4);			// = Moms i kr på fraktbeloppet
	    lineEditFraktmoms->setText(fraktmomskr);
	 }

 	 m=i36-i35;
	 if (i35 != -1){
	    momssumma=inrad.mid(i35+3,m-4);		// Total moms på offertn i kronor
	    lineEditOffertMomsKr->setText(momssumma);
	 }

	 m=i37-i36;
	 if (i36 != -1){					// Total offertsumma inklusive moms
	    offerttotal=inrad.mid(i36+3,m-4);
	    lineEditOffertTotal->setText(offerttotal);
	 }
/*
	 m=i38-i37;
	 if (i37 != -1){
	     drofmalsfakt=inrad.mid(i37+3,m-4);
	    lineEditDrojFaktura->setText(drofmalsfakt);
	 }

	 m=i39-i38;
	 if (i38 != -1){
	    samfaktura=inrad.mid(i38+3,m-4);
	    lineEditSamFaktura->setText(samfaktura);
	 }

	 m=i40-i39;
	 if (i39 != -1){
	    kravdatum=inrad.mid(i39+3,m-4);
	    lineEditKravDatum->setText(kravdatum);
	 }

	 m=i41-i40;
	 if (i40 != -1){
	    skuld=inrad.mid(i40+3,m-4);
	    lineEditSkuld->setText(skuld);
	 }

	 m=i42-i41;
	 if (i41 != -1){
	    offertstock=inrad.mid(i41+3,m-4);
	    lineEditoffertstock->setText(offertstock);
	 }
*/
	 inrad="";
	errorrad="";
	inrad="";
	i = -1;
     }
     pushButtonAvbryt->setFocus();
     frmPrtOffert::getoffertrader();
}

void frmPrtOffert::listViewRader_format()
{
    listViewRader->setColumnWidth(0,44);		// Radnr
    listViewRader->setColumnWidth(1,180);		// Artikelnr
    listViewRader->setColumnWidth(2,290);		// Benämning
    listViewRader->setColumnWidth(3,86);		// Leveransvecka
    listViewRader->setColumnWidth(4,65);		// Antal
    listViewRader->setColumnWidth(5,66);		// Pris
    listViewRader->setColumnWidth(6,86);		// Summa
    listViewRader->setColumnWidth(7,86);		// Moms
}

void frmPrtOffert::pushBtnHelp_clicked()
{
	inrad="";
	frmPrtOffert::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_OFFERT.html";
	hjelpfil=hjelpfil+"#OFFERT_PRT";		// Lägg till position
/*	qDebug("hjelpfil=%s",hjelpfil.latin1());	*/

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmPrtOffert::readResursFil()
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


void frmPrtOffert::clearKundInfo()
{
     	     lineEditOffertKundNr->clear();
//	     lineEditOffertNbr->clear();
	     lineEditKundNamn->clear();
	     lineEditKundAdress->clear();
	     lineEditKundPostnr->clear();
	     lineEditKundPostAdress->clear();
	     lineEditKundLand->clear();
/*	      ----------------				*/	     
	     lineEditKundRef->clear();
	     lineEditKundLevAdress->clear();
	     lineEditKundLevPostnr->clear();
	     lineEditKundLevPostAdress->clear();
	     lineEditKundLevLand->clear();
	     lineEditLevplats->clear();
	     lineEditLevvillkor->clear();
	     lineEditBetvilk->clear();
	     lineEditValuta->clear();
	     lineEditMomskod->clear();
/*	    -----------------				*/	     
	     lineEditOffertSumma->clear();
	     lineEditOffertFrakt->setEnabled("TRUE");
	     lineEditOffertFrakt->clear();
	     lineEditOffertMomsKr->clear();
	     lineEditOffertTotal->clear();
/*	    -----------------				*/	     
	     offertnr="0";
	     offertkundnr="";
	     offertkundnamn="";
	     offertkundadress="";
	     offertkundpostnr="";
	     offertkundpostadr="";
	     offertkundland="";
 
	     offertkundref="";
	     offertkundlevadress="";
	     offertkundlevpostnr="";
	     offertkundlevpostadr="";
	     offertkundlevland="";
    
	     offerttfnnr="";
	     offertfaxnr="";
	    offerttelexnr="";
	    offertemail="";
	    offertref="";
	    offertreftfnnr="";
	    offertmomskod="";
	    offertmoms="25";
	    offertkontonr="";
	    offertpgnr="";
	    offertbgnr="";
	    seljare="";
	    godsmarke="";
	    offertleveranstid="";
	    offertvaluta="SEK";
	    offertbetvillkor="001";
	    offertlevvillkor="001";
	    offertlevplats="000";
	    offerthuvuddata="";       
}

void frmPrtOffert::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }   
}

void frmPrtOffert::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmPrtOffert::getoffertrader()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	 inrad4="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "OFFRDSP");	// OLFIX funktion
	process->addArgument(offertnr );	

	frmPrtOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotoffertRadDataOnStdout() ) );
	frmPrtOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotoffertRadDataOnStderr() ) );
	frmPrtOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotoffertRaderEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFRDSP ",
                            "Kan inte starta STYRMAN/OFFRDSP!\n"
                            );
        }
}

void frmPrtOffert::slotoffertRaderEndOfProcess()
{
    /*  offertradrad	 */	
 //   bool radnrflag=FALSE;
    QString offertradnr="010";    
    QString oldradnr;
    QString offertartikelnr;
    QString prodklass;
    QString offertbenamn;
    QString radleveransvecka;
    QString offertantal;
    QString offertradpris;
    QString radbelopp;
    QString radmoms;		/*  Moms på radbelopp */
//    QString offertraddata;	    
    
//    qDebug("inrad4=%s",inrad4.latin1());
    int i,m,n;
    QString tmp;
    QListViewItem * item;

    i = -1;
    i = errorrad4.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "PRTOFFW",
		"ERROR!\n"+errorrad4
	);
	errorrad4="";
	i = -1;
     }
     i = -1;

     i = inrad4.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int p1 = inrad4.find( QRegExp("OK:"), 0 );
	 int p2 = inrad4.find( QRegExp("_:_"), 0 );
	 int n1=(p2)-(p1+3);
	 tmp=inrad4.mid(p1+3,n1);
	 int n2=tmp.toInt();
	 int m1=0;
//	 qDebug("p1=%d p2=%d n1=%d tmp=%s n2=%d",p1,p2,n1,tmp.latin1(),n2);
	 for (n=1;n<=n2;n++){
	     int i2 = inrad4.find( QRegExp("_:_03_:_"), m1 );		// radnr
	     int i3 = inrad4.find( QRegExp("_:_04_:_"), m1 );		// kundnr
	     int i4 = inrad4.find( QRegExp("_:_05_:_"), m1 );		// radtyp
	     int i5 = inrad4.find( QRegExp("_:_06_:_"), m1 );		// artikelnr
	     int i6 = inrad4.find( QRegExp("_:_07_:_"), m1 );		// benämning
	     int i7 = inrad4.find( QRegExp("_:_08_:_"), m1 );		// leveransvecka
	     int i8 = inrad4.find( QRegExp("_:_09_:_"), m1 );		// antal
	     int i9 = inrad4.find( QRegExp("_:_10_:_"), m1 );		// apris
	     int i10 = inrad4.find( QRegExp("_:_11_:_"), m1 );	// summa rad, belopp exklusive moms
//	     qDebug("i10=%d",i10);
	     int i11 = inrad4.find( QRegExp("_:_12_:_"), m1 );
	     int i12 = inrad4.find( QRegExp("_:_13_:_"), m1 );
	     int i13 = inrad4.find( QRegExp("_:_14_:_"), m1 );	
	     int i14 = inrad4.find( QRegExp("_:_15_:_"), m1 );
	     int i15 = inrad4.find( QRegExp("_:_16_:_"), m1 );	
	     int i16 = inrad4.find( QRegExp("_:_17_:_"), m1 );
	     int i17 = inrad4.find( QRegExp("_:_18_:_"), m1 );
	     int i18 = inrad4.find( QRegExp("_:_19_:_"), m1 );
	     int i19 = inrad4.find( QRegExp("_:_NEXT_:_"), m1 );
	     
	     m1=m1+i19+10;
	     m=(i3)-(i2+8);
	     offertradnr=inrad4.mid(i2+8,m);
//	     qDebug("i2=%d I3=%d m=%d  m1=%d",i2,i3,m,m1);
//	     qDebug("offertradnr=%s ",offertradnr.latin1());	     
	     m=(i4-3)-(i3+8);
	     tmp=inrad4.mid(i3+8,m);
//	     qDebug("kundnr=%s ",tmp.latin1());
	     m=(i5-3)-(i4+8);
	     tmp=inrad4.mid(i4+8,m);
//	     qDebug("radofferttyp=%s ",tmp.latin1());
	     m=(i6)-(i5+8);
	     offertartikelnr=inrad4.mid(i5+8,m);
//	     qDebug("offertartikelnr=%s ",offertartikelnr.latin1());
	     m=(i7)-(i6+8);
	     offertbenamn=inrad4.mid(i6+8,m);
//	     qDebug("benämning=%s",offertbenamn.latin1());
	     m=(i8)-(i7+8);
	     radleveransvecka=inrad4.mid(i7+8,m);
//	     qDebug("radleveransvecka=%s",radleveransvecka.latin1());
	     m=(i9-3)-(i8+8);
	     offertantal=inrad4.mid(i8+8,m);				// antal
//	     qDebug("offertantal=%s",offertantal.latin1());
	     m=(i10)-(i9+8);
	     offertradpris=inrad4.mid(i9+8,m);				// apris
//	     qDebug("offertradpris=%s",offertradpris.latin1());
	     m=(i11)-(i10 + 8);
	     radbelopp=inrad4.mid(i10 + 8,m);				// summa exklusive moms
//	     qDebug("radbelopp=%s",radbelopp.latin1());
	     m=(i12)-(i11 + 8);
	     radmoms=inrad4.mid(i11 + 8,m);				// moms i kronor
//	     qDebug("radmoms=%s",radmoms.latin1());
	     m=(i13 - 3)-(i12 + 8);
	     tmp=inrad4.mid(i12 + 8,m);				// levererat antal
//	     qDebug("levererat antal=%s",tmp.latin1());
	     m=(i14 - 3)-(i13 + 8);					// restnoterat
	     tmp=inrad4.mid(i13 + 8,m);				
//	     qDebug("restnoterat antal=%s",tmp.latin1());		
	     m=(i15 )-(i14 + 8);					// radrabatt
	     tmp=inrad4.mid(i14 + 8,m);
//	     qDebug("radrabatt=%s",tmp.latin1());		
	     m=(i16)-(i15 + 8);					// kalkylpris
	     tmp=inrad4.mid(i15 + 8,m);
//	     qDebug("kalkylpris=%s",tmp.latin1());
	     m=(i17)-(i16 + 8);					// leveransdatum för offertrad
	     tmp=inrad4.mid(i16 + 8,m);
//	     qDebug("leveransdatum=%s",tmp.latin1());		
	     m=(i18 - 3)-(i17 +8);					// enhet
	     tmp=inrad4.mid(i17 + 8,m);
//	     qDebug("enhet=%s",tmp.latin1());
	     item = new QListViewItem(listViewRader,offertradnr,offertartikelnr,offertbenamn,radleveransvecka,offertantal,offertradpris,radbelopp,radmoms);
	 } 
      }
     pushButtonAvbryt->setFocus();
}

void frmPrtOffert::slotoffertRadDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad4.append(line);
	inrad4.append("\n");
    }   
}

void frmPrtOffert::slotoffertRadDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad4.append(line);
	errorrad4.append("\n");
    }  
}

/* ******************************************************* */
/*	UTSKRIFTsprocessen  börjar här.                                                    */
/* ******************************************************* */
void frmPrtOffert::pushButtonSkrivUt_clicked()
{
    //      	Hämta företagsnamn
    frmPrtOffert::getForetagsdata("FNAMN");
    
    //	Hämta sökvägen till kugar template. Default /usr/local/olfix/report
    frmPrtOffert::GetReportDir();
    frmPrtOffert::GetTmpDir();
    frmPrtOffert::KugarVersion();    
    frmPrtOffert::CreatePrintout();
    
}

/* ******************************************************* */
/*	SKAPA utskriftsdokumentet         .                                                     */
/* ******************************************************* */
void frmPrtOffert::CreatePrintout()
{
    int i;
    QString rad[70];
    QString rapportrad;

    QFile filnamn(tmppath+printfil);
    QTextStream stream(&filnamn);
    
    FileRemove(printfil);		// radera gammal fil.
        rad[1]="<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    rad[2]="<!DOCTYPE KugarData [\n";
    rad[3]="   <!ELEMENT KugarData (namn* )>\n";
    rad[4]="   <!ATTLIST KugarData\n";
    rad[5]="      Template CDATA #REQUIRED>\n\n";
    rad[6]="   <!ELEMENT namn EMPTY>\n";
    rad[7]="   <!ATTLIST namn\n";
    rad[8]="      level CDATA #REQUIRED\n";
    rad[9]="      ftgnamn CDATA #REQUIRED\n";
    rad[10]="      datum CDATA #REQUIRED\n";
    rad[11]="      ordernr CDATA #REQUIRED\n";
    rad[12]="      sida CDATA #REQUIRED\n";
    rad[13]="      kundnr CDATA #REQUIRED\n";
    rad[14]="      kundnamn CDATA #REQUIRED\n";
    rad[15]="      kundadr CDATA #REQUIRED\n";
    rad[16]="      kundpostnr CDATA #REQUIRED\n";
    rad[17]="      kundpostadr CDATA #REQUIRED\n";
    rad[18]="      kundland CDATA #REQUIRED\n";
    rad[19]="      levkundnamn CDATA #REQUIRED\n";
    rad[20]="      kundlevadr CDATA #REQUIRED\n";
    rad[21]="      levpostnr CDATA #REQUIRED\n";
    rad[22]="      leveranspostadr CDATA #REQUIRED\n";
    rad[23]="      leveransland CDATA #REQUIRED\n";
    rad[24]="      seljare CDATA #REQUIRED\n";
    rad[25]="      betvillkor CDATA #REQUIRED\n";
    rad[28]="      levvillkor CDATA #REQUIRED\n";
    rad[29]="      valuta CDATA #REQUIRED\n";
    rad[30]="      levsett CDATA #REQUIRED\n";
    rad[31]="      erref CDATA #REQUIRED\n";
    rad[32]="      godsmerke CDATA #REQUIRED\n";
    rad[33]="      offerttotal CDATA #REQUIRED\n";
    rad[34]="      foretagsnamn CDATA #REQUIRED\n";
    rad[35]="      adress1 CDATA #REQUIRED\n"; 
    rad[36]="      adress2 CDATA #REQUIRED\n";
    rad[37]="      adress3 CDATA #REQUIRED\n";
    rad[38]="      telefon CDATA #REQUIRED\n";
    rad[39]=">\n";
    rad[40]="  <!ELEMENT KugarData (Rad*)>\n";
    rad[41]="  <!ATTLIST KugarData\n";
    rad[42]="      Template CDATA #REQUIRED>\n\n";
    rad[43]="  <!ELEMENT Rad EMPTY>\n";
    rad[44]="  <!ATTLIST Rad\n";
    rad[45]="      level CDATA #REQUIRED\n";
    rad[46]="      pos CDATA #REQUIRED\n";
    rad[47]="      vartnr CDATA #REQUIRED\n";
    rad[48]="      antal CDATA #REQUIRED\n";
    rad[49]="      apris CDATA #REQUIRED\n";
    rad[50]="      summa CDATA #REQUIRED\n";
    rad[51]=">\n";
    rad[52]="]>\n\n";
    rad[53]="<KugarData Template=\"";
    rad[53].append(printpath);
    rad[53].append("Offert.kut\">\n");	// ange rätt template, absolut path
    rapportrad=rad[1];
    for (i=2;i<54;i++){
	rapportrad.append(rad[i]);
    }
//    qDebug("CreateHeader::rapportrad = \n%s",rapportrad.latin1());
    rapportrad.append("<namn level=\"0");
    rapportrad.append("\" ftgnamn=\"");
    rapportrad.append(ftgnamn);
    rapportrad.append("\" datum=\"");
    rapportrad.append(offertdatum);
    rapportrad.append("\" ordernr=\"");
    rapportrad.append(offertnr);
    rapportrad.append("\" sida=\"");
    rapportrad.append(" 1");
    rapportrad.append("\" kundnr=\"");
    rapportrad.append(offertkundnr);
    rapportrad.append("\" kundnamn=\"");
    rapportrad.append(offertkundnamn);
    rapportrad.append("\" kundadr=\"");
    rapportrad.append(offertkundadress);
    rapportrad.append("\" kundpostnr=\"");
    rapportrad.append(offertkundpostnr);
    rapportrad.append("\" kundpostadr=\"");
    rapportrad.append(offertkundpostadr);
    rapportrad.append("\" kundland=\"");
    rapportrad.append(offertkundland);
    rapportrad.append("\" levkundnamn=\"");
    rapportrad.append(offertkundnamn);
    rapportrad.append("\" kundlevadr=\"");
    rapportrad.append(offertkundlevadress);
    rapportrad.append("\" levpostnr=\"");
    rapportrad.append(offertkundlevpostnr);
    rapportrad.append("\" leveranspostadr=\"");
    rapportrad.append(offertkundlevpostadr);
    rapportrad.append("\" leveransland=\"");
    rapportrad.append(offertkundlevland);
    rapportrad.append("\" betvillkor=\"");
    rapportrad.append(offertbetvillkor);
    rapportrad.append("\" levvillkor=\"");
    rapportrad.append(offertlevvillkor);
    rapportrad.append("\" valuta=\"");
    rapportrad.append(offertvaluta);
    rapportrad.append("\" levsett=\"");
    rapportrad.append(offertlevsett);
    rapportrad.append("\" erref=\"");
    rapportrad.append(offertref);
    rapportrad.append("\" seljare=\"");
    rapportrad.append(seljare);
    rapportrad.append("\" godsmerke=\"");
    rapportrad.append(godsmarke);
    rapportrad.append("\" offerttotal=\"");
    rapportrad.append(offerttotal);

    
    rapportrad.append("\" foretagsnamn=\"");
    rapportrad.append(ftgnamn);
    rapportrad.append("\" adress1=\"");
    rapportrad.append(ftgadr);
    rapportrad.append("\" adress2=\"");
    rapportrad.append(ftgpostnr);
    rapportrad.append("\" adress3=\"");
    rapportrad.append(ftgpostadr);
    rapportrad.append("\" telefon=\"");
    rapportrad.append(ftgtfn);
    rapportrad.append("\"/>\n");
    
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
//    qDebug("CreateHeader::ordernr=  %s",ordernr.latin1());
    filnamn.close();
//    frmPrtOffert::CallKugar();
    frmPrtOffert::PickOffertRader();
}

void frmPrtOffert::PickOffertRader()
{
    // listViewRader
    int i=0;    
    QListViewItemIterator it( listViewRader);
    QString rnr;
    listViewRader->firstChild ();
    for ( ; it.current(); ++it ){
	i++;
	QString temp0=it.current()->text(0);	// radnr
	QString temp1=it.current()->text(1);	// artikelnr
	QString temp2=it.current()->text(2);	// artikelbenämning
	QString temp3=it.current()->text(4);	// antal
	QString temp4=it.current()->text(5);	// pris/st
	QString temp5=it.current()->text(6);	// radsumma
     qDebug("i=%d  temp=%s, %s, %s, %s, %s, %s",i,temp0.latin1(),temp1.latin1(),temp2.latin1(),temp3.latin1(),temp4.latin1(),temp5.latin1());
	frmPrtOffert::CreateOffertRad(temp0,temp1,temp2,temp3, temp4,temp5);
    }
      frmPrtOffert::CreateReportFot();

//    listViewRader->clear();
}

void frmPrtOffert::CreateOffertRad(QString tmp0,QString tmp1,QString tmp2,QString tmp3, QString tmp4,QString tmp5)
{
    QString fil;
    fil=tmppath+printfil;
    QFile filnamn(fil);
//    qDebug("fil=%s",fil.latin1());
    QTextStream stream(&filnamn);
    
    QString offertraddata="";
    QString skilj;
    skilj="_:_";
    offertraddata="<Rad level=\"1\" ";
    offertraddata.append(" pos=\"");
    offertraddata.append(tmp0);	// offertradnr    
    offertraddata.append("\" vartnr=\"");
    offertraddata.append(tmp1);	// artikelnr
    offertraddata.append("\n");
    offertraddata.append(tmp2);	//benämning
    offertraddata.append("\" antal=\"");
    offertraddata.append(tmp3);	// antal
    offertraddata.append("\" apris=\"");
    offertraddata.append(tmp4);	// a'-pris
    offertraddata.append("\" summa=\"");
    offertraddata.append(tmp5);	// Summa
    offertraddata.append("\"/>\n");    
    // ------------------------------------------------------------        
    
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << offertraddata;
    filnamn.close();
}




void frmPrtOffert::CreateReportFot()
{
    QString fil;
    fil=tmppath+printfil;
    QFile filnamn(fil);
//    qDebug("fil=%s",fil.latin1());
    QTextStream stream(&filnamn);
    QString footrad;	// rapportfot

    filnamn.open( IO_WriteOnly | IO_Append );
    
// ------------------------------------------------------------    
//   Pagefoot    
// ------------------------------------------------------------        
    footrad=("<foot level=\"1");
    footrad.append("\" foretagsnamn=\"");
    footrad.append(ftgnamn);
    footrad.append("\" adress1=\"");
    footrad.append(ftgadr);
    footrad.append("\" adress2=\"");
    footrad.append(ftgpostnr);
    footrad.append("\" adress3=\"");
    footrad.append(ftgpostadr);
    footrad.append("\" telefon=\"");
    footrad.append("09-999999");
// ------------------------------------------------------------        
    footrad.append("\"/>\n");
//    footrad.append("</PageFooter>\n");
    footrad.append("</KugarData>\n");
    
    stream << footrad;
    filnamn.close();
    frmPrtOffert::CallKugar();
}


void frmPrtOffert::FileRemove(QString filnamn)
{
//  Ta bort temporärfilen /tmp/Offert.kud 
    bool status;
    QDir d = QDir::root();                   // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }
//    qDebug("filnamn=%s",filnamn.latin1());
    status=d.remove(filnamn,FALSE);
}

void frmPrtOffert::GetTmpDir()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var mappen tmp finns		               */
    /*****************************************************/

    QString hemkatalog;
    QString olfixrcfile;	// filen $HOME/.olfixrc

    bool status;
    int i = -1;
    //	Hämta sökvägen till kugar template. Default /usr/local/olfix/report
    //	Hämtas från .olfixrc
    hemkatalog=QDir::homeDirPath ();
    olfixrcfile=hemkatalog+"/.olfixrc";
    QFile file(olfixrcfile);
    status=file.open(IO_ReadOnly);
    QTextStream stream( &file );
    while ( !stream.eof() ) {
	inrad = stream.readLine();
	i = inrad.find( QRegExp("VTMP="), 0 );
	if(i == 0){
	    tmppath=inrad.mid(5,inrad.length()-5);
	    i= -1;
	}
    }
    file.close ();
//    qDebug("tmppath=%s",tmppath.latin1());
}

void frmPrtOffert::KugarVersion()
{
//  Hämta aktuell version av kugar
//  Anrop av kugar skiljer sig mellan version 1.2.1 och version 1.2.92 ->    
    bool status;
    int i = -1;

    QString filename;
    
    system("kugar -v >/tmp/kugarversion.txt");
    filename=tmppath+"kugarversion.txt";
    QFile file(filename);
    status=file.open(IO_ReadOnly);
    QTextStream stream( &file );
    while ( !stream.eof() ) {
	inrad = stream.readLine();
	i = inrad.find( QRegExp("Kugar:"), 0 );
	if(i == 0){
	    kugarversion=inrad.mid(7,inrad.length()-7);
	    i= -1;
	}
    }   
    file.close ();
//   qDebug("kugarversion=%s",kugarversion.latin1());
   frmPrtOffert::FileRemove("kugarversion.txt");
}

void frmPrtOffert::GetReportDir()
{
    QString hemkatalog;
    QString olfixrcfile;	// filen $HOME/.olfixrc

    bool status;
    int i = -1;
    //	Hämta sökvägen till kugar template. Default /usr/local/olfix/report
    //	Hämtas från .olfixrc
    hemkatalog=QDir::homeDirPath ();
    olfixrcfile=hemkatalog+"/.olfixrc";
    QFile file(olfixrcfile);
    status=file.open(IO_ReadOnly);
    QTextStream stream( &file );
    while ( !stream.eof() ) {
	inrad = stream.readLine();
	i = inrad.find( QRegExp("REPORT="), 0 );
	if(i == 0){
	    printpath=inrad.mid(7,inrad.length()-7);
//	    qDebug("reportpath=%s",reportpath.latin1());
	    i= -1;
	}
    }   
    file.close ();
//    qDebug("reportpath=  %s",reportpath.latin1());
}

void frmPrtOffert::getForetagsdata(QString posttyp)
{
/************************************************************************/
/*	Hämta företagsdata, FTGDATA	 				*/
/************************************************************************/
	const char *userp = getenv("USER");
	QString usr(userp);
//	qDebug("posttyp=%s",posttyp.latin1());
	inrad4="";
	errorrad4="";
	process4 = new QProcess();
	process4->addArgument("./STYRMAN");	// OLFIX styrprogram
	process4->addArgument(usr);		// userid
	process4->addArgument( "FTGDSP");	// OLFIX funktion
	process4->addArgument(posttyp);

	frmPrtOffert::connect( process4, SIGNAL(readyReadStdout() ),this, SLOT(FtgDataOnStdout() ) );
	frmPrtOffert::connect( process4, SIGNAL(readyReadStderr() ),this, SLOT(FtgDataOnStderr() ) );
	frmPrtOffert::connect( process4, SIGNAL(processExited() ),this, SLOT(ForetagsdataEndOfProcess() ) );
	    
	if ( !process4->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FTGDSP!\n");
		QMessageBox::warning( this, "PRTOFFW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	}
}

void frmPrtOffert::FtgDataOnStdout()
{
     while (process4->canReadLineStdout() ) {
	QString line = process4->readStdout();
	inrad4.append(line);
	inrad4.append("\n");
    }   
}

void frmPrtOffert::FtgDataOnStderr()
{
      while (process4->canReadLineStderr() ) {
	QString line = process4->readStderr();
	errorrad4.append(line);
	errorrad4.append("\n");
    }  
}

void frmPrtOffert::ForetagsdataEndOfProcess()
{
//    qDebug("inrad4=%s",inrad4.latin1());
    int i,m;
    QString posttyp="";
    i = -1;
    i = errorrad4.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "PRTOFFW",
		"ERROR!\n"+errorrad4
	);
    }else{
	i = -1;
	i = inrad4.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    int i1 = inrad4.find( QRegExp("1:"), 0 );		// posttyp
	    int i2 = inrad4.find( QRegExp("2:"), 0 );		// ftgdata
//	    int i3 = inrad4.find(QRegExp("END:"),0);			// postslut
	    int i3 = inrad.length();
//	    qDebug("inrad4.length=%d",i3);
	    m=i2-i1;
	    if (i1 != -1){
		posttyp=inrad4.mid(i1+2,m-4);
	    }

	    m=i3-i2;
	    if (i2 != -1){
		if(posttyp=="FNAMN"){
//		    qDebug("m=%d",m);
		    ftgnamn=inrad4.mid(i2+2,m-2);
//		    qDebug("ftgnamn=%s len ftgnamn=%d",ftgnamn.latin1(),ftgnamn.length());
		    ftgnamn=ftgnamn.left(ftgnamn.length()-2); // plocka bort en radretur
//		    qDebug("ftgnamn=%s| len ftgnamn=%d",ftgnamn.latin1(),ftgnamn.length());
		    frmPrtOffert::getForetagsdata("ADR1"); // Boxadress
		}
		if(posttyp=="ADR1"){
		    ftgadr=inrad4.mid(i2+2,m-2);
		    ftgadr=ftgadr.left(ftgadr.length()-2);
		    frmPrtOffert::getForetagsdata("ADR2"); // Postnr
		}
		if(posttyp=="ADR2"){
		    ftgpostnr=inrad4.mid(i2+2,m-2);
		    ftgpostnr=ftgpostnr.left(ftgpostnr.length()-2);
		    frmPrtOffert::getForetagsdata("ADR3"); //Postadress
		}
		if(posttyp=="ADR3"){
		    ftgpostadr=inrad4.mid(i2+2,m-2);
		    ftgpostadr=ftgpostadr.left(ftgpostadr.length()-2);
		    frmPrtOffert::getForetagsdata("TFN1");
		}		
		if(posttyp=="TFN1"){
		    ftgtfn=inrad4.mid(i2+2,m-2);
		    ftgtfn=ftgtfn.left(ftgtfn.length()-2);
		}				
	    }
	}
    }
//    qDebug("posttyp=%s",posttyp.latin1());
//    qDebug("ftgnamn5=%s",ftgnamn.latin1());
}





void frmPrtOffert::CallKugar()
{
    if (kugarversion<"1.2.92"){
	kommando="kugar -d ";
	kommando.append(tmppath);
	kommando.append(printfil);
	kommando.append(" -r ");
	kommando.append(printpath);
	kommando.append("Offert.kut");
//	qDebug("kommando=%s",kommando.latin1());
	system(kommando);
    }else{
	kommando="kugar ";
	kommando.append(tmppath);
	kommando.append(printfil);
	system(kommando);
    }
    pushButtonAvbryt->setFocus();
}


/* 	Iakta status före avslut av programmet */
void frmPrtOffert::test_and_debug()
{
    qDebug("test_and_debug:ftgnamn=%s",ftgnamn.latin1());
    close();
}
