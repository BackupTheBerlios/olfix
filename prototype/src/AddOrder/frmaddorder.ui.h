/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDORDW  -  description
	         Kundorder
                             -------------------
		     version 0.3
    begin   	: Sö  12 okt   2003
    Updated	: Mån  7 mars 2005
    copyright	: (C) 2003 by Jan Pihlgren
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
    QString* rad;
    QString errorrad;

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
    QString ordervaluta;
    QString orderbetvillkor;
    QString orderlevvillkor;
    QString orderlevplats;
       
    /*  Orderradrad	 */	
    bool radnrflag=FALSE;
    QString orderradnr="010";    
    QString oldradnr;
    QString orderartikelnr;
    QString orderbenamn;
    QString orderantal;
    QString orderradpris;
    QString radbelopp;
	    
    /* Order 	*/
    QString ordersumma;
    QString momssumma;
    QString fraktbelopp;
    
void frmAddOrder::init()
{
//    int vecka;
//    int year;
    int dag;
    QString dagnummer;
    QString veckonr;
    QString artal;
    QDateTime dt = QDateTime::currentDateTime();
    dag= QDate::currentDate().dayOfWeek();
    orderdatum=dt.toString("yyyy-MM-dd");
    
    textLabelOrderdatum->setText(orderdatum);
    frmAddOrder::listViewRader_format();
    frmAddOrder::getKundLista();
    lineEditOrderKundNr->setFocus();
}

void frmAddOrder::slotKundNr_returnPressed()
{
    orderkundnr=lineEditOrderKundNr->text();
    frmAddOrder::getKundData();
    lineEditArtikelNr->setFocus();
}

void frmAddOrder::slotPickupKundnr( QListViewItem * item)
{
    char kundnummer[11]="";
//    qDebug("PickupKundnr\n");
    if(!item){
	return;
    }
     listViewKund->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(kundnummer,item->key(0,TRUE));
     orderkundnr=kundnummer;
     lineEditOrderKundNr->setText((orderkundnr));
     lineEditOrderKundNr->setFocus();
}

void frmAddOrder::slotOrderNr_returnPressed()
{
    ordernr=lineEditOrderNbr->text();
    lineEditKundNamn->setFocus();
}

void frmAddOrder::slotKundNamn_returnPressed()
{
    orderkundnamn=lineEditKundNamn->text();
    lineEditKundAdress->setFocus();
}


void frmAddOrder::slotOrderAdress_returnPressed()
{
    orderkundadress=lineEditKundAdress->text();
    lineEditKundPostnr->setFocus();
}

void frmAddOrder::slotOrderPostNr_returnPressed()
{
    orderkundpostnr=lineEditKundPostnr->text();
    lineEditKundPostAdress->setFocus();
}

void frmAddOrder::slotOrderPostAdress_returnPressed()
{
    orderkundpostadr=lineEditKundPostAdress->text();
    lineEditKundLand->setFocus();
}

void frmAddOrder::slotOrderLand_returnPressed()
{
    orderkundland=lineEditKundLand->text();
    lineEditValuta->setFocus();
}
/*
   QString orderkundref;
    QString orderkundlevadress;
    QString orderkundlevpostnr;
    QString orderkundlevpostadr;
    QString orderkundlevland;
  
*/
void frmAddOrder::lineEditKundRef_returPressed()
{
    orderkundref=lineEditKundRef->text();
    lineEditKundRef->setText(orderkundref);
    lineEditArtikelNr->setFocus();
}

void frmAddOrder::lineEditKundLevAdress_returnPressed()
{
    orderkundlevadress=lineEditKundLevAdress->text();
    lineEditKundLevAdress->setText(orderkundlevadress);
    lineEditArtikelNr->setFocus();
}

void frmAddOrder::lineEditKundLevPostnr_returnPressed()
{
    orderkundlevpostnr=lineEditKundLevPostnr->text();
    lineEditKundLevPostnr->setText(orderkundlevpostnr);
    lineEditArtikelNr->setFocus();
}

void frmAddOrder::lineEditKundLevLand_return_pressed()
{
    orderkundlevland=lineEditKundLevLand->text();
    lineEditKundLevLand->setText(orderkundlevland);
    lineEditArtikelNr->setFocus();
}

void frmAddOrder::lineEditKundLevPostAdress_returnPressed()
{
    orderkundlevpostadr=lineEditKundLevPostAdress->text();
    lineEditKundLevPostAdress->setText(orderkundlevpostadr);
    lineEditArtikelNr->setFocus();
}

void frmAddOrder::slotOrderValuta_returnPressed()
{
    ordervaluta=lineEditValuta->text();
    lineEditBetvilk->setFocus();
}	

void frmAddOrder::slotOrderBetvilk_returnPressed()
{
    orderbetvillkor=lineEditBetvilk->text();
    pushButtonOK->setFocus();
}


void frmAddOrder::lineEditLevvillkor_returnPressed()
{

}

void frmAddOrder::lineEditLevplats_returnPressed()
{
    orderlevplats=lineEditLevplats->text();
    frmAddOrder::getStdLevplats( orderlevplats );
    lineEditArtikelNr->setFocus();
}

/************************************************************************/
/*		Orderradrad	Start					*/
/************************************************************************/

void frmAddOrder::lineEditArtikelNr_returnPressed()
{
    orderartikelnr=lineEditArtikelNr->text();
    if (orderartikelnr==""){
	QMessageBox::warning( this, "ADDORDW",
			      "Artikelnummer måste anges!\n" );
	lineEditArtikelNr->setFocus();
    }else{
	frmAddOrder::getArtikeldata();
	lineEditBenamn->setFocus();
    }
}

void frmAddOrder::lineEditBenamn_returnPressed()
{
    orderbenamn=lineEditBenamn->text();
    lineEditAntal->setFocus();
}

void frmAddOrder::lineEditAntal_returnPressed()
{
    int i;
    double antal;
    orderantal=lineEditAntal->text();
    antal=orderantal.toDouble();
    if ( antal==0){
	QMessageBox::warning( this, "ADDORDW",
			      "Antal måste anges!\n" );
	lineEditAntal->clear();
	lineEditAntal->setFocus();
    }else{
	i = -1;
	i =orderantal.find( QRegExp(","), 0 );
	if (i != -1){
	    orderantal.replace( QChar(','), "." );
	    lineEditAntal->setText(orderantal);
	}
	lineEditAPris->setFocus();
    }
}

void frmAddOrder::lineEditAPris_returnPressed()
{
    int i;
    double pris,antal,summa;
    orderradpris=lineEditAPris->text();
    i = -1;
    i =orderradpris.find( QRegExp(","), 0 );
    if (i != -1){
	orderradpris.replace( QChar(','), "." );
	lineEditAPris->setText(orderradpris);
    }
    pris=orderradpris.toDouble();
    antal=orderantal.toDouble();
    summa=pris*antal;
    radbelopp=radbelopp.setNum(summa,'f',2);
    lineEditRadSumma->setText(radbelopp);
    pushBtnOKRad->setFocus();
}

void frmAddOrder::pushBtnOKRad_clicked()
{
    double summa ,belopp, moms, momsbelopp;
    QListViewItem * item;
    int i;
    item = new QListViewItem(listViewRader,orderradnr,orderartikelnr,orderbenamn,orderantal,orderradpris,radbelopp);
    item->setText(8,orderbenamn);
    if (radnrflag == FALSE){
	i = orderradnr.toInt();
	i = i+10;
	orderradnr=QString::number(i,10);
	if (orderradnr.length() <3){
	    orderradnr="0"+orderradnr;
	}
    }else{
	orderradnr=oldradnr;
	radnrflag=FALSE;
    }
    /* Beräkna ordersumma	*/
    summa=ordersumma.toDouble();
    belopp=radbelopp.toDouble();
    summa=summa+belopp;
    ordersumma=ordersumma.setNum(summa,'f',2);
    lineEditOrderSumma->setText(ordersumma);
    /*  Beräkna momsen	*/  
    moms=ordermoms.toDouble();
    moms=moms/100;
    momsbelopp=summa*moms;
    momssumma=momssumma.setNum(momsbelopp,'f',2);
    lineEditOrderMomsKr->setText(momssumma);
    /* Nästa orderrad 	*/
    lineEditRadnr->setText(orderradnr);
    lineEditArtikelNr->clear();
    lineEditBenamn->clear();
    lineEditAntal->clear();
    lineEditAPris->clear();
    lineEditRadSumma->clear();
    orderartikelnr="";
    orderbenamn="";
    orderantal="";
    orderradpris="";
    radbelopp="";
    lineEditArtikelNr->setFocus();
}

void frmAddOrder::pushBtnRadNej_clicked()
{
    lineEditRadnr->setText(orderradnr);
    lineEditArtikelNr->clear();
    lineEditBenamn->clear();
    lineEditAntal->clear();
    lineEditAPris->clear();
    lineEditRadSumma->clear();
    orderartikelnr="";
    orderbenamn="";
    orderantal="";
    orderradpris="";
    radbelopp="";
    lineEditArtikelNr->setFocus();
}

void frmAddOrder::listViewRader_clicked( QListViewItem * )
{
    double radsumma ,tmpordersumma;
    radnrflag=TRUE;
    oldradnr=orderradnr;
    QListViewItem *item =  listViewRader->currentItem();
    if ( !item )
	return;
    item->setSelected( TRUE );
    QString temp0=item->text(0);	// radnr
    QString temp1=item->text(1);	// artikelnr
    QString temp2=item->text(2);	// artikelbenämning
    QString temp3=item->text(3);	// antal
    QString temp4=item->text(4);	// pris/st
    QString temp5=item->text(5);	// radsumma
    //    qDebug("temp=%s, %s, %s, %s, %s, %s",temp0.latin1(),temp1.latin1(),temp2.latin1(),temp3.latin1(),temp4.latin1(),temp5.latin1());
    // --------------------------------------------------------------
    lineEditRadnr->setText(temp0);
    orderradnr=temp0;
    lineEditArtikelNr->setText(temp1);
    lineEditBenamn->setText(temp2);
    lineEditAntal->setText(temp3);
    lineEditAPris->setText(temp4);
    lineEditRadSumma->setText(temp5);
    radsumma=temp5.toDouble();
    tmpordersumma=ordersumma.toDouble();
    tmpordersumma=tmpordersumma-radsumma;
    ordersumma=ordersumma.setNum(tmpordersumma,'f',2);
    lineEditOrderSumma->setText(ordersumma);
    lineEditArtikelNr->setFocus();
    delete listViewRader->currentItem();
}



/************************************************************************/
/*		Orderradrad	Slut					*/
/************************************************************************/

void frmAddOrder::lineEditOrderFrakt_returnPressed()
{
    double summa ,totalsumma,fraktsumma,moms,momsbelopp;
    totalsumma=0;
       /*	Fraktkostnad	   */
    summa=ordersumma.toDouble();
    fraktbelopp=lineEditOrderFrakt->text();
    fraktsumma=fraktbelopp.toDouble(); 
    lineEditOrderFrakt->setText(fraktbelopp);
	    
       /*  Beräkna momsen	*/  
    moms=ordermoms.toDouble();
    moms=moms/100;
    momsbelopp=(summa+fraktsumma)*moms;
    momssumma=momssumma.setNum(momsbelopp,'f',2);
    lineEditOrderMomsKr->setText(momssumma);
    
       /* Order total 	*/
    totalsumma=totalsumma+summa+fraktsumma+momsbelopp;
    ordersumma=ordersumma.setNum(totalsumma,'f',2);
    lineEditOrderTotal->setText(ordersumma);

}

void frmAddOrder::pushBtnOrderKlar_clicked()
{
    pushButtonOK->setFocus();
}

void frmAddOrder::slotBtnOK_clicked()
{
    slotAddOrder();
}


void frmAddOrder::slotAddOrder()
{
/************************************************************************/
/*	Uppdatera databasen						*/
/************************************************************************/
	const char *userp = getenv("USER");
            QString usr(userp);
	    
	if (ordermomskod == ""){
	    ordermomskod = "1";
	 }
	if (orderbetvillkor == ""){
	    orderbetvillkor ="1";
	}
	
//	qDebug("ordernr=%s",ordernr.latin1());
//	qDebug("ordernamn=%s",ordernamn.latin1());
	    
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "ORDADD");	// OLFIX funktion
	process->addArgument(ordernr);
	process->addArgument(orderkundnr);
	process->addArgument(orderkundnamn);
	process->addArgument(orderkundadress);
	process->addArgument(orderkundpostnr);
	process->addArgument(orderkundpostadr);
	process->addArgument(orderkundland);
	process->addArgument(ordertfnnr);
	process->addArgument(orderfaxnr);
	process->addArgument(ordertelexnr);
	process->addArgument(orderemail);
	process->addArgument(orderpgnr);
	process->addArgument(orderbgnr);
	process->addArgument(orderref);
	process->addArgument(orderreftfnnr);
	process->addArgument(ordermomskod);
	process->addArgument(orderkontonr);
	process->addArgument(ordervaluta);
	process->addArgument(orderbetvillkor);
	
	frmAddOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmAddOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	    
	if (ordernr == "" || orderkundnamn ==""){
    	    QMessageBox::warning( this, "ADDORDW",
                      "Leverantörsnummer och/eller ordererantörsnamn saknas \n" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/ORDADD!\n");
		QMessageBox::warning( this, "ADDORDW",
                            "Kan inte starta STYRMAN/ORDADD! \n" );
	    }
	}
}

void frmAddOrder::slotDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }   
}

void frmAddOrder::slotDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmAddOrder::slotEndOfProcess()
{
    int i;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
//   qDebug("Error:%s",errorrad.latin1());
//   qDebug("Inrad:%s",inrad.latin1());
     if (i != -1) {
	QMessageBox::critical( this, "ADDORDW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
	return;
     }else{
	 i = -1;
	 i = inrad.find( QRegExp("OK:"), 0 );
	 if (i != -1) {
	     QMessageBox::information( this, "ADDORDW",
		"Uppdatering OK!\n"+errorrad
		);
	     lineEditOrderNbr->clear();
	     lineEditKundNamn->clear();
	     lineEditKundAdress->clear();
	     lineEditKundPostnr->clear();
	     lineEditKundPostAdress->clear();
	     lineEditKundLand->clear();
	     lineEditOrderKundNr->clear();
	     lineEditOrderNbr->setFocus();
	     ordermomskod="1";

	     inrad="";
	     i = -1;
	 } 
     }
}

void frmAddOrder::getKundLista()
{
	const char *userp = getenv("USER");
            QString usr(userp);


	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KULST");	// OLFIX funktion

	frmAddOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotKundListaEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KULST!\n");
	    QMessageBox::warning( this, "Start av KULST ",
                            "Kan inte starta STYRMAN/KULST!\n"
                            );
        }
}

void frmAddOrder::slotKundListaEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewKund->setSorting(1,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDORDW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }

    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "ADORDW",
		"Kundregistret innehåller inga poster!\n"
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
    char kundnr[11]="";
    char namn[61]="";

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
    };
    i=atoi(antrad);		// i = antal poster
    
//    qDebug("antrad=%s",antrad);
    
    for (k = 1;k <= i; k++){	// gå igenom alla raderna / posterna
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
	m=m+l+2;	// position för namn
	l=0;
	for(j = m; j < sizeof(namn) + m; j++){
	    if(tmp[j] != *("_")){
		namn[l]=tmp[j];
		l++;
	    }else{
		namn[l] = *("\0");
		j=sizeof(namn) + m;
	    }
	}
//	qDebug("%s  ",namn);
	m=m+l+2;
	item = new QListViewItem(listViewKund,kundnr,namn);
// 	 rensa kundnr och namn
  	for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
	for (l=0;l<sizeof(namn);l++)
		namn[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,80);
    }
    	frmAddOrder::getOrdernr();
}


void frmAddOrder::getKundData()
{
	const char *userp = getenv("USER");
            QString usr(userp);


	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KUDSP");	// OLFIX funktion
	process->addArgument(orderkundnr);

	frmAddOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotKundDataEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/KUDSP!\n");
	    QMessageBox::warning( this, "Start av KUDSP ",
                            "Kan inte starta STYRMAN/KUDSP!\n"
                            );
        }
}


void frmAddOrder::slotKundDataEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad);
         if (i != -1) {
	QMessageBox::critical( this, "ADDORDW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;

     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
/*	 int i1 = inrad.find( QRegExp("01:"), 0 );
	 int i2 = inrad.find( QRegExp("02:"), 0 );	*/
	 int i3 = inrad.find( QRegExp("03:"), 0 );
	 int i4 = inrad.find( QRegExp("04:"), 0 );
	 int i5 = inrad.find( QRegExp("05:"), 0 );
	 int i6 = inrad.find( QRegExp("06:"), 0 );
	 int i7 = inrad.find( QRegExp("07:"), 0 );
	 int i8 = inrad.find( QRegExp("08:"), 0 );
/*	 int i9 = inrad.find( QRegExp("09:"), 0 );
	 int i10 = inrad.find( QRegExp("10:"), 0 );
*/	 int i11 = inrad.find( QRegExp("11:"), 0 );
	 int i12 = inrad.find( QRegExp("12:"), 0 );
/*	 int i13 = inrad.find( QRegExp("13:"), 0 );
	 int i14 = inrad.find( QRegExp("14:"), 0 );
	 int i15 = inrad.find( QRegExp("15:"), 0 );	*/
	 int i16 = inrad.find( QRegExp("16:"), 0 );
	 int i17 = inrad.find( QRegExp("17:"), 0 );
	 int i18 = inrad.find( QRegExp("18:"), 0 );
	 int i19 = inrad.find( QRegExp("19:"), 0 );
/*	 int i20 = inrad.find( QRegExp("20:"), 0 );
	 int i21 = inrad.find( QRegExp("21:"), 0 );	*/
	 int i22 = inrad.find( QRegExp("22:"), 0 );	
	 int i23 = inrad.find( QRegExp("23:"), 0 );
/*	 int i24 = inrad.find( QRegExp("24:"), 0 );
	 int i25 = inrad.find( QRegExp("25:"), 0 );
	 int i26 = inrad.find( QRegExp("26:"), 0 );
	 int i27 = inrad.find( QRegExp("27:"), 0 );
	 int i28 = inrad.find( QRegExp("28:"), 0 );
	 int i29 = inrad.find( QRegExp("29:"), 0 );
	 int i30 = inrad.find( QRegExp("30:"), 0 );
	 int i31 = inrad.find( QRegExp("31:"), 0 );
	 int i32 = inrad.find( QRegExp("32:"), 0 );
	 int i33 = inrad.find( QRegExp("33:"), 0 );	*/
	 int i34 = inrad.find( QRegExp("34:"), 0 );
	 int i35 = inrad.find( QRegExp("35:"), 0 );
/*	 int i36 = inrad.find( QRegExp("36:"), 0 );
	 int i37 = inrad.find( QRegExp("37:"), 0 );
	 int i38 = inrad.find( QRegExp("38:"), 0 );
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

 	 m=i3-i2;
	 if (i2 != -1){
//	     kundorgnr=inrad.mid(i2+2,m-4);
	 }
*/
	 m=i4-i3;
	 if (i3 != -1){
	     orderkundnamn=inrad.mid(i3+3,m-4);
	     lineEditKundNamn->setText(orderkundnamn);
	 }

	 m=i5-i4;
	 if (i4 != -1){
	     orderkundadress=inrad.mid(i4+3,m-4);
	     lineEditKundAdress->setText(orderkundadress);
	 }

 	 m=i6-i5;
	 if (i5 != -1){
	     orderkundpostnr=inrad.mid(i5+3,m-4);
	     lineEditKundPostnr->setText(orderkundpostnr);
	 }

	 m=i7-i6;
	 if (i6 != -1){
	     orderkundpostadr=inrad.mid(i6+3,m-4);
	     lineEditKundPostAdress->setText(orderkundpostadr);
	 }

 	 m=i8-i7;
	 if (i7 != -1){
	     orderkundland=inrad.mid(i7+3,m-4);
	     lineEditKundLand->setText(orderkundland);
	 }
/*
 	 m=i9-i8;
	 if (i8 != -1){
	     tfnnr=inrad.mid(i8+3,m-4);
	     lineEditKundTftnNr->setText(tfnnr);
	 }

	 m=i10-i9;
	 if (i9 != -1){
	     email=inrad.mid(i9+3,m-4);
	     lineEditKundEmail->setText(email);
	 }

 	 m=i11-i10;
	 if (i10 != -1){
	     faxnr=inrad.mid(i10+3,m-4);
	     lineEditKundFaxNr->setText(faxnr);
	 }
*/
 	 m=i12-i11;
	 if (i11 != -1){
	     orderkundref=inrad.mid(i11+3,m-4);
	     lineEditKundRef->setText(orderkundref);
	 }
/*
 	 m=i13-i12;
	 if (i12 != -1){
	     erreftfnnr=inrad.mid(i12+3,m-4);
	     lineEditErRefTfnNr->setText(erreftfnnr);
	 }

 	 m=i14-i13;
	 if (i13 != -1){
	     errefemail=inrad.mid(i13+3,m-4);
	     lineEditKundErRefEmail->setText(errefemail);
	 }

 	 m=i15-i14;
	 if (i14 != -1){
	     seljare=inrad.mid(i14+3,m-4);
	     lineEditKundSeljare->setText(seljare);
	 }

	 m=i16-i15;
	 if (i15 != -1){
	    fritext=inrad.mid(i15+3,m-4);
	    lineEditFriText->setText(fritext);
	 }
*/
 	 m=i17-i16;
	 if (i16 != -1){
	     ordervaluta=inrad.mid(i16+3,m-5);
	     lineEditValuta->setText(ordervaluta);
	 }

	 m=i18-i17;
	 if (i17 != -1){
	     orderbetvillkor=inrad.mid(i17+3,m-4);
	     lineEditBetvilk->setText(orderbetvillkor);
	 }

	 m=i19-i18;
	 if (i18 != -1){
	     orderlevvillkor=inrad.mid(i18+3,m-4);
	     lineEditLevvillkor->setText(orderlevvillkor);
	 }
/*
	 m=i20-i19;
	 if (i19 != -1){
	     levsett=inrad.mid(i19+3,m-4);
	     lineEditKundLevsett->setText(levsett);
	 }

	 m=i21-i20;
	 if (i20 != -1){
	     distrikt=inrad.mid(i20+3,m-4);
	     lineEditKundDistrikt->setText(distrikt);
	 }

	 m=i22-i21;
	 if (i21 != -1){
	    kundkat=inrad.mid(i21+3,m-4);
	    lineEditKundKategori ->setText(kundkat);
	 }
*/
	 m=i23-i22;
	 if (i22 != -1){
	    orderlevplats=inrad.mid(i22+3,m-4);
	    lineEditLevplats ->setText(orderlevplats);
	 }
/*
	 m=i24-i23;
	 if (i23 != -1){
	     ordererk=inrad.mid(i23+3,m-4);
	    lineEditOrdererk ->setText(ordererk);
	 }


	 m=i25-i24;
	 if (i24 != -1){
	     plocklista=inrad.mid(i24+3,m-4);
	    lineEditPlocklista ->setText(plocklista);
	 }

	 m=i26-i25;
	 if (i25 != -1){
	     foljesedel=inrad.mid(i25+3,m-4);
	    lineEditFoljesedel->setText(foljesedel);
	 }

	 m=i27-i26;
	 if (i26 != -1){
	     kravbrev=inrad.mid(i26+3,m-4);
	    lineEditKravbrev ->setText(kravbrev);
	 }

	 m=i28-i27;
	 if (i27 != -1){
	     sprakkod=inrad.mid(i27+3,m-4);
	    lineEditSprakkod->setText(sprakkod);
	 }

 	 m=i29-i28;
	 if (i28 != -1){
	     expavg=inrad.mid(i28+3,m-4);
	    lineEditExpAvgift->setText(expavg);
	 }

	 m=i30-i29;
	 if (i29 != -1){
	     fraktavg=inrad.mid(i29+3,m-4);
	    lineEditFraktAvgift->setText(fraktavg);
	 }

	 m=i31-i30;
	 if (i30 != -1){
	     kreditlimit=inrad.mid(i30+3,m-4);
	    lineEditKreditlimit->setText(kreditlimit);
	 }

	 m=i32-i31;
	 if (i31 != -1){
	     kreditdagar=inrad.mid(i31+3,m-4);
	    lineEditKreditDagar->setText(kreditdagar);
	 }

	 m=i33-i32;
	 if (i32 != -1){
	     kreditkod=inrad.mid(i32+3,m-4);
	    lineEditKreditKod->setText(kreditkod);
	 }

	 m=i34-i33;
	 if (i33 != -1){
	     exportkod=inrad.mid(i33+3,m-4);
	    lineEditExportkod->setText(exportkod);
	 }
*/
 	 m=i35-i34;
	 if (i34 != -1){
	    ordermomskod=inrad.mid(i34+3,m-4);		// = Skattekod
//	    lineEditMomskod->setText(ordermomskod);
	 }
/*
 	 m=i36-i35;
	 if (i35 != -1){
	    rabattkod=inrad.mid(i35+3,m-4);
	    lineEditRabattKod->setText(rabattkod);
	 }

	 m=i37-i36;
	 if (i36 != -1){
	    drojmalsrenta=inrad.mid(i36+3,m-4);
	    lineEditDrojRenta->setText(drojmalsrenta);
	 }

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
     frmAddOrder::getStdLevplats( orderlevplats );
}

void frmAddOrder::getOrdernr()
{
	const char *userp = getenv("USER");
            QString usr(userp);


	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument("KORNR");	// Senas använda kundordernummer

	frmAddOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetOrdernrEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGDSP ",
                            "Kan inte starta STYRMAN/FTGDSP!\n"
                            );
        }
}

void frmAddOrder::slotgetOrdernrEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDORDW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int i1 = inrad.find( QRegExp("1:"), 0 );
	 int i2 = inrad.find( QRegExp("2:"), 0 );	
	 int i3 = inrad.length();
	 m=i2-i1;
	 m=i3-i2;
	 if (i2 != -1){
	     ordernr=inrad.mid(i2+2,m-4);
//	     qDebug("m=%d  ordernr=%s  i3=%d",m,ordernr.latin1(), i3);
	 }
	 bool ok;
	 int ornr = ordernr.toInt( &ok, 10 ); 
	 ornr++;
	 ordernr = QString::number( ornr, 10 );
	 lineEditOrderNbr->setText(ordernr);
	inrad="";
	errorrad="";
	inrad="";
	i = -1;
    }
   frmAddOrder::getMoms();
}

void frmAddOrder::getMoms()
{
	const char *userp = getenv("USER");
            QString usr(userp);


	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument("MOMS1");	// Senas använda kundordernummer

	frmAddOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmAddOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmAddOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotgetMomsEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGDSP ",
                            "Kan inte starta STYRMAN/FTGDSP!\n"
                            );
        }

}

void frmAddOrder::slotgetMomsEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "ADDORDW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int i1 = inrad.find( QRegExp("1:MOMS1"), 0 );
	 int i2 = inrad.find( QRegExp("2:"), 0 );	
	 int i3 = inrad.length();
	 m=i2-i1;
	 m=i3-i2;
	 if (i2 != -1){
	     ordermoms=inrad.mid(i2+2,m-4);
//	     qDebug("m=%d  moms=%s  i3=%d",m,ordermoms.latin1(), i3);
	 }
	 lineEditMomskod->setText(ordermoms+"%");
	inrad="";
	errorrad="";
	inrad="";
	i = -1;
    }
}

void frmAddOrder::listViewRader_format()
{
    listViewRader->setColumnWidth(0,44);		// Radnr
    listViewRader->setColumnWidth(1,236);		// Artikelnr
    listViewRader->setColumnWidth(2,292);		// Benämning
//    listViewRader->setColumnWidth(3,55);		// Lev.vecka
    listViewRader->setColumnWidth(3,86);		// Antal
    listViewRader->setColumnWidth(4,71);		// Pris
    listViewRader->setColumnWidth(5,86);		// Summa
}

void frmAddOrder::getArtikeldata()
{
    const char *userp = getenv("USER");
    QString usr(userp);

    inrad="";
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "ARDSP");	// OLFIX funktion
    process->addArgument(orderartikelnr);

    frmAddOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotArdataEndOfProcess() ) );

    if ( !process->start() ) {
	// error handling
	fprintf(stderr,"Problem starta STYRMAN/ARDSP!\n");
	QMessageBox::warning( this, "Start av ARDSP",
			      "Kan inte starta STYRMAN/ARDSP!\n"
			      );
    }
}

void frmAddOrder::slotArdataEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    //   qDebug("Error:",errorrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDORDW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	orderartikelnr="";
	lineEditArtikelNr->clear();
	lineEditArtikelNr->setFocus();
    }else{
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    //	    int i1 = inrad.find( QRegExp("01:"), 0 );	//	artikelnr
	    int i2 = inrad.find( QRegExp("02:"), 0 );		//	benämning 1
	    int i3 = inrad.find( QRegExp("03:"), 0 );		//	benämning 2
	    //	    int i4 = inrad.find( QRegExp("04:"), 0 );	//	enhet
    	    int i5 = inrad.find( QRegExp("05:"), 0 );		//	försäljningspris
	    int i6 = inrad.find( QRegExp("06:"), 0 );		//	ledtid
//	    int i7 = inrad.find( QRegExp("07:"), 0 );		//	prodklass
//	    int i15= inrad.find(QRegExp("15:"),0);		//	leverantörens artbenämning
//	    int i16= inrad.find(QRegExp("16:"),0);
//	    int i17= inrad.find(QRegExp("17:"),0);		//	leverantörens artnr
//	    int i18= inrad.find(QRegExp("18:"),0);
	    m=i3-i2;
	    if (i2 != -1){
		orderbenamn=inrad.mid(i2+3,m-4);
		lineEditBenamn->setText(orderbenamn);
	    }
   	    m=i6-i5;
	    if (i5 != -1){
		orderradpris=inrad.mid(i5+3,m-4);
		lineEditAPris->setText(orderradpris);
	    }	    
 
/*	    
	    m=i7-i6;
	    if (i6 != -1){
		arledtid=inrad.mid(i6+3,m-4);
	    }
*/
/*	    
	    m=i16-i15;
	    if (i15 != -1){
		orderbenamn=inrad.mid(i15+3,m-4);
	    }
*/	    
/*	    m=i18-i17;
	    if (i17 != -1){
		orderartikelnr=inrad.mid(i17+3,m-4);
	    }
*/	    
//	    frmAddBest::getArtikelEkonomidata();
	}
    }
}

void frmAddOrder::getStdLevplats( QString platsnr )
{
    const char *userp = getenv("USER");
    QString usr(userp);
    platsnr=platsnr.left(3);
    inrad="";
   
    process = new QProcess();
    process->addArgument("./STYRMAN");	// OLFIX styrprogram
    process->addArgument(usr);		// userid
    process->addArgument( "LEVPDSP");	// OLFIX funktion
    process->addArgument(orderkundnr);
    process->addArgument(platsnr);
// qDebug("kundnr=%s standardlevplats=%s",orderkundnr.latin1(),platsnr.latin1());
    frmAddOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
    frmAddOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
    frmAddOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotLevPEndOfProcess() ) );

    if ( !process->start() ) {
	// error handling
	QMessageBox::warning( this, "Start av LEVPDSP",
			      "Kan inte starta STYRMAN/LEVPDSP!\n"
			      );
    }
}

void frmAddOrder::slotLevPEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
// qDebug("Error: %s",errorrad.latin1());
// qDebug("Inrad=%s",inrad);
    if (i != -1) {
	QMessageBox::critical( this, "ADDORDW",
			       "ERROR!\n"+errorrad
			       );
	errorrad="";
	i = -1;
	lineEditLevplats->setFocus();
    }else{
/*
   QString orderkundref;
    QString orderkundlevadress;
    QString orderkundlevpostnr;
    QString orderkundlevpostadr;
    QString orderkundlevland;
  
*/
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
//	    int i1 = inrad.find( QRegExp("01:"), 0 );	           //	standardleveransplatsnrnr
//	    int i2 = inrad.find( QRegExp("02:"), 0 );		//	kundnr
	    int i3 = inrad.find( QRegExp("03:"), 0 );		//	adress
	    int i4 = inrad.find( QRegExp("04:"), 0 );		//	postnr
    	    int i5 = inrad.find( QRegExp("05:"), 0 );		//	postadress
	    int i6 = inrad.find( QRegExp("06:"), 0 );		//	land
	    m=i4-i3;
	    if (i3 != -1){
		orderkundlevadress=inrad.mid(i3+3,m-4);
		lineEditKundLevAdress->setText(orderkundlevadress);
	    }
	    m=i5-i4;
	    if (i4 != -1){
		orderkundlevpostnr=inrad.mid(i4+3,m-4);
		lineEditKundLevPostnr->setText(orderkundlevpostnr);
	    }
	    m=i6-i5;
	    if (i5 != -1){
		orderkundlevpostadr=inrad.mid(i5+3,m-4);
		lineEditKundLevPostAdress->setText(orderkundlevpostadr);
	    }
	    m=i6-i5;
	    if (i6 != -1){
		orderkundlevland=inrad.mid(i6+3,m-4);
		lineEditKundLevLand->setText(orderkundlevland);
	    }	    
	}
    }
}
