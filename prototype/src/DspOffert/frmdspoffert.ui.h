/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPOFFW  -  description
	         Visa offert
                             -------------------
		     version 0.4.3.
    begin   	:	 Tors     27 april    2006
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


    QProcess* process;
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
    QString offertstatus;
    QString offerthuvuddata;       
    
    
    /* offert 	*/
    QString offertdel;		/*  Del av offertn, H=offerthuvud, R=offertrad */
    QString offertsumma;
    QString momssumma;		/*  Total moms p� offertn */
    QString fraktbelopp;
    QString fraktmomskr;
    QString offerttotal;
    bool nykundflag=FALSE;
//    QString kunddata="";			/* f�r nyregistrering av kund */
    
void frmDspOffert::init()
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
    
    frmDspOffert::listViewRader_format();
    frmDspOffert::getOffertLista();
    listViewOffert->setFocus();
//    lineEditOffertNbr->setFocus();
}


void frmDspOffert::slotPickupoffertnr( QListViewItem * item)
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

void frmDspOffert::lineEditOffertNbr_returnPressed()
{
    
    offertnr=lineEditOffertNbr->text();
    listViewRader->clear();
    frmDspOffert::getOfferthuvud();
}

void frmDspOffert::getOffertLista()
{
	const char *userp = getenv("USER");
	QString usr(userp);
	 inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "OFFLST");	// OLFIX funktion

	frmDspOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDspOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotOffertListaEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFLST ",
                            "Kan inte starta STYRMAN/OFFLST!\n"
                            );
        }
}

void frmDspOffert::slotOffertListaEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewOffert->setSorting(1,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "DSPOFFW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }

    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "DSPOFFW",
		"Offertregistret inneh�ller inga poster!\n"
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
    pos1=strstr(tmp,"OK: NR_");	// 7 tecken l�ngt
    pos2=strstr(tmp,"_:");
    i=pos2-pos1;
    m=i+2;		// startposition f�r f�rsta kundnr.
    
//    qDebug("i=%d  m=%d",i,m);
    
    k=0;
    for (j=7;j<i;j++){	// j = f�rsta positionen f�r antal poster,(OK: NR_4_:4377_:Kund AB_:4379_:Sm�kund AB_:4378_:Storkund AB_:4376_:Test AB_:)
	antrad[k]=tmp[j];
	k++;
    }
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// g� igenom alla raderna / posterna
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
	m=m+l+2;	// position f�r kundnr
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
	m=m+l+2;	// position f�r levdatum	
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
	m=m+l+2;	// position f�r offertstatus
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
	m=m+l+2;	// position f�r offerttotal
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

void frmDspOffert::getOfferthuvud()
{
	const char *userp = getenv("USER");
	QString usr(userp);
	inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "OFFDSP");	// OLFIX funktion
	process->addArgument(offertnr);

	frmDspOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDspOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotofferthuvudEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFDSP ",
                            "Kan inte starta STYRMAN/OFFDSP!\n"
                            );
        }
}

void frmDspOffert::slotofferthuvudEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "DSPOFFW",
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
/*	 if (i17 != -1){					// V�r referent
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
	 if (i19 != -1){					// Godsm�rke
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
	 if (i25 != -1){					// F�ljesedel
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
	 if (i31 != -1){					//  Spr�kkod
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
	    fraktmomskr=inrad.mid(i34+3,m-4);			// = Moms i kr p� fraktbeloppet
	    lineEditFraktmoms->setText(fraktmomskr);
	 }

 	 m=i36-i35;
	 if (i35 != -1){
	    momssumma=inrad.mid(i35+3,m-4);		// Total moms p� offertn i kronor
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
     frmDspOffert::getoffertrader();
}

void frmDspOffert::listViewRader_format()
{
    listViewRader->setColumnWidth(0,44);		// Radnr
    listViewRader->setColumnWidth(1,180);		// Artikelnr
    listViewRader->setColumnWidth(2,290);		// Ben�mning
    listViewRader->setColumnWidth(3,86);		// Leveransvecka
    listViewRader->setColumnWidth(4,65);		// Antal
    listViewRader->setColumnWidth(5,66);		// Pris
    listViewRader->setColumnWidth(6,86);		// Summa
    listViewRader->setColumnWidth(7,86);		// Moms
}

void frmDspOffert::pushBtnHelp_clicked()
{
	inrad="";
	frmDspOffert::readResursFil();		// H�mta path till hj�lpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_OFFERT.html";
	hjelpfil=hjelpfil+"#OFFERT_DSP";		// L�gg till position
/*	qDebug("hjelpfil=%s",hjelpfil.latin1());	*/

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmDspOffert::readResursFil()
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


void frmDspOffert::clearKundInfo()
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

void frmDspOffert::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }   
}

void frmDspOffert::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmDspOffert::getoffertrader()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	 inrad4="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "OFFRDSP");	// OLFIX funktion
	process->addArgument(offertnr );	

	frmDspOffert::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotoffertRadDataOnStdout() ) );
	frmDspOffert::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotoffertRadDataOnStderr() ) );
	frmDspOffert::connect( process, SIGNAL(processExited() ),this, SLOT(slotoffertRaderEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFRDSP ",
                            "Kan inte starta STYRMAN/OFFRDSP!\n"
                            );
        }
}

void frmDspOffert::slotoffertRaderEndOfProcess()
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
    QString radmoms;		/*  Moms p� radbelopp */
//    QString offertraddata;	    
    
//    qDebug("inrad4=%s",inrad4.latin1());
    int i,m,n;
    QString tmp;
    QListViewItem * item;

    i = -1;
    i = errorrad4.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "DSPOFFW",
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
	     int i6 = inrad4.find( QRegExp("_:_07_:_"), m1 );		// ben�mning
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
//	     qDebug("ben�mning=%s",offertbenamn.latin1());
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
	     m=(i17)-(i16 + 8);					// leveransdatum f�r offertrad
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

void frmDspOffert::slotoffertRadDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad4.append(line);
	inrad4.append("\n");
    }   
}

void frmDspOffert::slotoffertRadDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad4.append(line);
	errorrad4.append("\n");
    }  
}
