/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          DSPORDW  -  description
	         Visa kundorder
                             -------------------
		     version 0.1
    begin   	: Sön     27 mars    2005
    Updated	: 
    copyright	: (C) 2005 by Jan Pihlgren
    email     	: jan@pihlgren.se
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

    QString orderdatum;
    QString ordernr;
    QString orderkundnr;
    QString orderkundnamn;
    QString orderkundadress;
    QString orderkundpostnr;
    QString orderkundpostadr;
    QString orderkundland;
    
    QString orderkundref;
    QString orderkundlevadress;
    QString orderkundlevpostnr;
    QString orderkundlevpostadr;
    QString orderkundlevland;
    
    
    QString ordertfnnr;
    QString orderfaxnr;
    QString ordertelexnr;
    QString orderemail;
    QString orderref;
    QString orderreftfnnr;
    QString ordermomskod;
    QString ordermoms;
    QString orderkontonr;
    QString orderpgnr;
    QString orderbgnr;
    QString seljare;
    QString godsmarke;
    QString orderleveranstid;
    QString ordervaluta;
    QString orderbetvillkor;
    QString orderlevvillkor;
    QString orderlevplats;
    QString orderstatus;
    QString orderhuvuddata;       
    
    
    /* Order 	*/
    QString orderdel;		/*  Del av ordern, H=orderhuvud, R=orderrad */
    QString ordersumma;
    QString momssumma;		/*  Total moms på ordern */
    QString fraktbelopp;
    QString fraktmomskr;
    QString ordertotal;
    bool nykundflag=FALSE;
//    QString kunddata="";			/* för nyregistrering av kund */
    
void frmDspOrder::init()
{
    int vecka;
    int year;
    int dag;
    QString dagnummer;
    QString veckonr;
    QString artal;
//    QDateTime dt = QDateTime::currentDateTime();
    dag= QDate::currentDate().dayOfWeek();
//    orderdatum=dt.toString("yyyy-MM-dd");
//    textLabelOrderdatum->setText(orderdatum);    
//    orderleveranstid=orderdatum;
    
    vecka= QDate::currentDate().weekNumber(&year);
    veckonr=QString::number(vecka,10);
    dagnummer=QString::number(dag,10);
    if (veckonr.length() < 2){
	veckonr.prepend("0");
    }
    artal=QString::number(year,10);
    
    frmDspOrder::listViewRader_format();
    frmDspOrder::getOrderLista();
    lineEditOrderNbr->setFocus();
}


void frmDspOrder::slotPickupOrdernr( QListViewItem * item)
{
    char ordernummer[11]="";
//    qDebug("PickupOrdernr\n");
    if(!item){
	return;
    }
     listViewOrder->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(ordernummer,item->key(0,TRUE));
     ordernr=ordernummer;
     lineEditOrderNbr->setText((ordernr));
     lineEditOrderNbr->setFocus();
}

void frmDspOrder::lineEditOrderNbr_returnPressed()
{
    
    ordernr=lineEditOrderNbr->text();
    listViewRader->clear();
    frmDspOrder::getOrderhuvud();
}

void frmDspOrder::getOrderLista()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	 inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ORDLST2");	// OLFIX funktion

	frmDspOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDspOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotOrderListaEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av ORDLST2 ",
                            "Kan inte starta STYRMAN/ORDLST2!\n"
                            );
        }
}

void frmDspOrder::slotOrderListaEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewOrder->setSorting(1,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "DSPORDW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }

    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "DSPORDW",
		"Orderregistret innehåller inga poster!\n"
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
    char ordnr[11]="";
    char kundnr[11]="";
    char levdatum[11]="";
    char orderstatus[2]="";
    char ordertotal[14]="";

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
	for(j = m; j < sizeof(ordnr) + m; j++){
	    if(tmp[j] != *("_")){
		ordnr[l]=tmp[j];
		l++;
	    }else{
		ordnr[l] = *("\0");
		j=sizeof(ordnr) + m;
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
	m=m+l+2;	// position för ordertotal
	l=0;
	for(j = m; j < sizeof(ordertotal) + m; j++){
	    if(tmp[j] != *("_")){
		ordertotal[l]=tmp[j];
		l++;
	    }else{
		ordertotal[l] = *("\0");
		j=sizeof(ordertotal) + m;
	    }
	}
	
	m=m+l+2;
	item = new QListViewItem(listViewOrder,ordnr,kundnr,levdatum,orderstatus,ordertotal);
// 	 rensa 
	
  	for (l=0;l<sizeof(ordnr);l++)
		ordnr[l]=*("\0");
  	for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
	for (l=0;l<sizeof(levdatum);l++)
		levdatum[l]=*("\0");
	for (l=0;l<sizeof(orderstatus);l++)
		orderstatus[l]=*("\0");		
	for (l=0;l<sizeof(ordertotal);l++)
		ordertotal[l]=*("\0");	
//	 rensa listrad 
	listrad.remove(0,80);
    }
}

void frmDspOrder::getOrderhuvud()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	    inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ORDDSP");	// OLFIX funktion
	process->addArgument(ordernr);

	frmDspOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmDspOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotOrderhuvudEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av ORDDSP ",
                            "Kan inte starta STYRMAN/ORDDSP!\n"
                            );
        }
}

void frmDspOrder::slotOrderhuvudEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "DSPORDW",
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
//	 int i25 = inrad.find( QRegExp("25:"), 0 );
//	 int i26 = inrad.find( QRegExp("26:"), 0 );
//	 int i27 = inrad.find( QRegExp("27:"), 0 );
	 int i28 = inrad.find( QRegExp("28:"), 0 );
	 int i29 = inrad.find( QRegExp("29:"), 0 );
	 int i30 = inrad.find( QRegExp("30:"), 0 );
//	 int i31 = inrad.find( QRegExp("31:"), 0 );
	 int i32 = inrad.find( QRegExp("32:"), 0 );
	 int i33 = inrad.find( QRegExp("33:"), 0 );	
	 int i34 = inrad.find( QRegExp("34:"), 0 );
	 int i35 = inrad.find( QRegExp("35:"), 0 );
	 int i36 = inrad.find( QRegExp("36:"), 0 );
	 int i37 = inrad.find( QRegExp("END"), 0 );
/*	 int i38 = inrad.find( QRegExp("38:"), 0 );
	 int i39 = inrad.find( QRegExp("39:"), 0 );
	 int i40 = inrad.find( QRegExp("40:"), 0 );
	 int i41 = inrad.find( QRegExp("41:"), 0 );
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
	     orderkundnr=inrad.mid(i2+3,m-4);
	     lineEditOrderKundNr->setText(orderkundnr);
	 }
/*
	 m=i4-i3;
	 if (i3 != -1){					// Ordertyp 
	     orderkundnamn=inrad.mid(i3+3,m-4);
	     lineEditKundNamn->setText(orderkundnamn);
	 }
*/
	 m=i5-i4;					// Orderstatus
	 if (i4 != -1){
	     orderstatus=inrad.mid(i4+3,m-4);
	     lineEditOrderStatus->setText(orderstatus);
	 }

 	 m=i6-i5;
	 if (i5 != -1){					// Orderdatum
	     orderdatum=inrad.mid(i5+3,m-4);
	     textLabelOrderdatum->setText(orderdatum);
	 }

	 m=i7-i6;
	 if (i6 != -1){					// Leveransdatum
	     orderleveranstid=inrad.mid(i6+3,m-4);
	     lineOrderLeveranstid->setText(orderleveranstid);
	 }

 	 m=i8-i7;
	 if (i7 != -1){					// Kundnamn
	     orderkundnamn=inrad.mid(i7+3,m-4);
	     lineEditKundNamn->setText(orderkundnamn);
	 }

 	 m=i9-i8;
	 if (i8 != -1){					// Kundadress
	     orderkundadress=inrad.mid(i8+3,m-4);
	     lineEditKundAdress->setText(orderkundadress);
	 }

	 m=i10-i9;
	 if (i9 != -1){					// Kundpostnummer
	     orderkundpostnr=inrad.mid(i9+3,m-4);
	     lineEditKundPostnr->setText(orderkundpostnr);
	 }

 	 m=i11-i10;
	 if (i10 != -1){					// Kundpostadress
	     orderkundpostadr=inrad.mid(i10+3,m-4);
	     lineEditKundPostAdress->setText(orderkundpostadr);
	 }

 	 m=i12-i11;
	 if (i11 != -1){					// Land
	     orderkundland=inrad.mid(i11+3,m-4);
	     lineEditKundLand->setText(orderkundland);
	 }

 	 m=i13-i12;
	 if (i12 != -1){					// Kundens referens
	     orderkundref=inrad.mid(i12+3,m-4);
	     lineEditKundRef->setText(orderkundref);
	 }

 	 m=i14-i13;
	 if (i13 != -1){					// Leveransadress
	     orderkundlevadress=inrad.mid(i13+3,m-4);
	     lineEditKundLevAdress->setText(orderkundlevadress);
	 }

 	 m=i15-i14;
	 if (i14 != -1){					// Leveranspostnr
	     orderkundlevpostnr=inrad.mid(i14+3,m-4);	
	     lineEditKundLevPostnr->setText(orderkundlevpostnr);
	 }

	 m=i16-i15;
	 if (i15 != -1){					// Leveranspostadress
	    orderkundlevpostadr=inrad.mid(i15+3,m-4);
	    lineEditKundLevPostAdress->setText(orderkundlevpostadr);
	 }

 	 m=i17-i16;
	 if (i16 != -1){					// Leveransland
	     orderkundlevland=inrad.mid(i16+3,m-5);
	     lineEditKundLevLand->setText(orderkundlevland);
	 }

	 m=i18-i17;
/*	 if (i17 != -1){					// Vår referent
	     orderbetvillkor=inrad.mid(i17+3,m-4);
	     lineEditBetvilk->setText(orderbetvillkor);
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
/*	     orderbetvillkortyp=inrad.mid(i20+3,m-4);
	     lineEditBetvilk->setText(orderbetvillkortyp);
*/	 }

	 m=i22-i21;
	 if (i21 != -1){					// Betalningsvillkor
	     orderbetvillkor=inrad.mid(i21+3,m-4);
	     lineEditBetvilk->setText(orderbetvillkor);
	 }

	 m=i23-i22;
	 if (i22 != -1){					// Leveransvillkor
	    orderlevvillkor=inrad.mid(i22+3,m-4);
	    lineEditLevvillkor ->setText(orderlevvillkor);
	 }

	 m=i24-i23;
	 if (i23 != -1){					// Leveransplats /LEVSETT)
	    orderlevplats=inrad.mid(i23+3,m-4);
	    lineEditLevplats ->setText(orderlevplats);
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
	    ordermoms=inrad.mid(i28+3,m-4);
	    lineEditMomskod->setText(ordermoms);
	 }

	 m=i30-i29;
	 if (i29 != -1){					// Valuta
	    ordervaluta=inrad.mid(i29+3,m-4);
	    lineEditValuta->setText(ordervaluta);
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
	 if (i32 != -1){					// Ordersumma exklusive moms
	    ordersumma=inrad.mid(i32+3,m-4);
	    lineEditOrderSumma->setText(ordersumma);
	 }

	 m=i34-i33;
	 if (i33 != -1){					// Fraktavgift i kronor exklusive moms
	    fraktbelopp=inrad.mid(i33+3,m-4);
	    lineEditOrderFrakt->setText(fraktbelopp);
	 }

 	 m=i35-i34;
	 if (i34 != -1){
	    fraktmomskr=inrad.mid(i34+3,m-4);		// = Moms i kr på fraktbeloppet
	    lineEditFraktmoms->setText(fraktmomskr);
	 }

 	 m=i36-i35;
	 if (i35 != -1){
	    momssumma=inrad.mid(i35+3,m-4);		// Total moms på ordern i kronor
	    lineEditOrderMomsKr->setText(momssumma);
	 }

	 m=i37-i36;
	 if (i36 != -1){					// Total ordersumma inklusive moms
	    ordertotal=inrad.mid(i36+3,m-4);
	    lineEditOrderTotal->setText(ordertotal);
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
	    orderstock=inrad.mid(i41+3,m-4);
	    lineEditOrderstock->setText(orderstock);
	 }
*/
	 inrad="";
	errorrad="";
	inrad="";
	i = -1;
     }
     pushButtonAvbryt->setFocus();
     frmDspOrder::getOrderrader();
}

void frmDspOrder::listViewRader_format()
{
    listViewRader->setColumnWidth(0,44);		// Radnr
    listViewRader->setColumnWidth(1,180);		// Artikelnr
    listViewRader->setColumnWidth(2,295);		// Benämning
    listViewRader->setColumnWidth(3,86);		// Leveransvecka
    listViewRader->setColumnWidth(4,65);		// Antal
    listViewRader->setColumnWidth(5,66);		// Pris
    listViewRader->setColumnWidth(6,86);		// Summa
    listViewRader->setColumnWidth(7,86);		// Moms
}

void frmDspOrder::pushBtnHelp_clicked()
{
	inrad="";
	frmDspOrder::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_KUNDORDER.html";
	hjelpfil=hjelpfil+"#FORSALJ1";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmDspOrder::readResursFil()
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


void frmDspOrder::clearKundInfo()
{
     	     lineEditOrderKundNr->clear();
//	     lineEditOrderNbr->clear();
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
	     lineEditOrderSumma->clear();
	     lineEditOrderFrakt->setEnabled("TRUE");
	     lineEditOrderFrakt->clear();
	     lineEditOrderMomsKr->clear();
	     lineEditOrderTotal->clear();
/*	    -----------------				*/	     
	     ordernr="0";
	     orderkundnr="";
	     orderkundnamn="";
	     orderkundadress="";
	     orderkundpostnr="";
	     orderkundpostadr="";
	     orderkundland="";
 
	     orderkundref="";
	     orderkundlevadress="";
	     orderkundlevpostnr="";
	     orderkundlevpostadr="";
	     orderkundlevland="";
    
	     ordertfnnr="";
	     orderfaxnr="";
	    ordertelexnr="";
	    orderemail="";
	    orderref="";
	    orderreftfnnr="";
	    ordermomskod="";
	    ordermoms="25";
	    orderkontonr="";
	    orderpgnr="";
	    orderbgnr="";
	    seljare="";
	    godsmarke="";
	    orderleveranstid="";
	    ordervaluta="SEK";
	    orderbetvillkor="001";
	    orderlevvillkor="001";
	    orderlevplats="000";
	    orderhuvuddata="";       
}

void frmDspOrder::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }   
}

void frmDspOrder::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmDspOrder::getOrderrader()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	 inrad4="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ORDRDSP");	// OLFIX funktion
	process->addArgument(ordernr );	

	frmDspOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotOrderRadDataOnStdout() ) );
	frmDspOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotOrderRadDataOnStderr() ) );
	frmDspOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotOrderRaderEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av ORDRDSP ",
                            "Kan inte starta STYRMAN/ORDRDSP!\n"
                            );
        }
}

void frmDspOrder::slotOrderRaderEndOfProcess()
{
    /*  Orderradrad	 */	
 //   bool radnrflag=FALSE;
    QString orderradnr="010";    
    QString oldradnr;
    QString orderartikelnr;
    QString prodklass;
    QString orderbenamn;
    QString radleveransvecka;
    QString orderantal;
    QString orderradpris;
    QString radbelopp;
    QString radmoms;		/*  Moms på radbelopp */
//    QString orderraddata;	    
    
//    qDebug("inrad4=%s",inrad4.latin1());
    int i,m,n;
    QString tmp;
    QListViewItem * item;

    i = -1;
    i = errorrad4.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "DSPORDW",
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
	     int i2 = inrad4.find( QRegExp("02_:"), m1 );		// radnr
	     int i3 = inrad4.find( QRegExp("03_:"), m1 );		// kundnr
	     int i4 = inrad4.find( QRegExp("04_:"), m1 );		// radtyp
	     int i5 = inrad4.find( QRegExp("05_:"), m1 );		// artikelnr
	     int i6 = inrad4.find( QRegExp("06_:"), m1 );		// benämning
	     int i7 = inrad4.find( QRegExp("07_:"), m1 );		// leveransvecka
	     int i8 = inrad4.find( QRegExp("08_:"), m1 );		// antal
	     int i9 = inrad4.find( QRegExp("09_:"), m1 );		// apris
	     int i10 = inrad4.find( QRegExp("_:_10_:_"), m1 );		// summa rad, belopp exklusive moms
//	     qDebug("i10=%d",i10);
	     int i11 = inrad4.find( QRegExp("_:_11_:_"), m1 );
	     int i12 = inrad4.find( QRegExp("12_:"), m1 );
	     int i13 = inrad4.find( QRegExp("13_:"), m1 );	
	     int i14 = inrad4.find( QRegExp("14_:"), m1 );
	     int i15 = inrad4.find( QRegExp("_:_15_:_"), m1 );	
	     int i16 = inrad4.find( QRegExp("_:_16_:_"), m1 );
	     int i17 = inrad4.find( QRegExp("_:_17_:_"), m1 );
	     int i18 = inrad4.find( QRegExp("_:_NEXT_:_"), m1 );
//	     int i19 = inrad4.find( QRegExp("END"), 0 );    
	     m1=m1+i18+10;
	     m=(i3-3)-(i2+5);
	     orderradnr=inrad4.mid(i2+5,m);
//	     qDebug("i2=%d I3=%d m=%d  m1=%d",i2,i3,m,m1);
//	     qDebug("orderradnr=%s ",orderradnr.latin1());	     
	     m=(i4-3)-(i3+5);
	     tmp=inrad4.mid(i3+5,m);
//	     qDebug("kundnr=%s ",tmp.latin1());
	     m=(i5-3)-(i4+5);
	     tmp=inrad4.mid(i4+5,m);
//	     qDebug("radordertyp=%s ",tmp.latin1());
	     m=(i6-3)-(i5+5);
	     orderartikelnr=inrad4.mid(i5+5,m);
//	     qDebug("orderartikelnr=%s ",orderartikelnr.latin1());
	     m=(i7-3)-(i6+5);
	     orderbenamn=inrad4.mid(i6+5,m);
//	     qDebug("benämning=%s",orderbenamn.latin1());
	     m=(i8-3)-(i7+5);
	     radleveransvecka=inrad4.mid(i7+5,m);
//	     qDebug("radleveransvecka=%s",radleveransvecka.latin1());
	     m=(i9-3)-(i8+5);
	     orderantal=inrad4.mid(i8+5,m);				// antal
//	     qDebug("orderantal=%s",orderantal.latin1());
	     m=(i10)-(i9+5);
	     orderradpris=inrad4.mid(i9+5,m);			// apris
//	     qDebug("orderradpris=%s",orderradpris.latin1());
	     m=(i11)-(i10 + 8);
	     radbelopp=inrad4.mid(i10 + 8,m);			// summa exklusive moms
//	     qDebug("radbelopp=%s",radbelopp.latin1());
	     m=(i12 - 3)-(i11 + 8);
	     radmoms=inrad4.mid(i11 + 8,m);			// moms i kronor
//	     qDebug("radmoms=%s",radmoms.latin1());
	     m=(i13 - 3)-(i12 + 5);
	     tmp=inrad4.mid(i12 + 5,m);				// levererat antal
//	     qDebug("levererat antal=%s",tmp.latin1());
	     m=(i14 - 3)-(i13 + 5);					// restnoterat
	     tmp=inrad4.mid(i13 + 5,m);				
//	     qDebug("restnoterat antal=%s",tmp.latin1());		
	     m=(i15 )-(i14 + 5);					// radrabatt
	     tmp=inrad4.mid(i14 + 5,m);
//	     qDebug("radrabatt=%s",tmp.latin1());		
	     m=(i16)-(i15 + 8);					// kalkylpris
	     tmp=inrad4.mid(i15 + 8,m);
//	     qDebug("kalkylpris=%s",tmp.latin1());
	     m=(i17)-(i16 + 8);					// leveransdatum för orderrad
	     tmp=inrad4.mid(i16 + 8,m);
//	     qDebug("leveransdatum=%s",tmp.latin1());		
	     m=(i18 - 3)-(i17 +8);					// enhet
	     tmp=inrad4.mid(i17 + 8,m);
//	     qDebug("enhet=%s",tmp.latin1());
	     item = new QListViewItem(listViewRader,orderradnr,orderartikelnr,orderbenamn,radleveransvecka,orderantal,orderradpris,radbelopp,radmoms);
	 } 
      }
     pushButtonAvbryt->setFocus();
}

void frmDspOrder::slotOrderRadDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad4.append(line);
	inrad4.append("\n");
    }   
}

void frmDspOrder::slotOrderRadDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad4.append(line);
	errorrad4.append("\n");
    }  
}
