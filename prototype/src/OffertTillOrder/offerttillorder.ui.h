/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
/***************************************************************************
                              OFF2ORDW  -  description
	         Skapa en order från en offert.
                             -------------------
		     version 0.1
    begin   	: 	Tors    29 nov    2006
    Updated	: 	
    copyright:	 (C) 2006 by Jan Pihlgren
    email     	:	 jan@pihlgren.se
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
#define MAXPROCESS 200

    QProcess* process;
    QProcess* process0;
    QProcess* process1;
    QProcess* process2;
    QProcess* process3;
    QProcess* process4[200];		// till för sparade av orderrader
    int processnbr=0;
    QString inrad;
    QString inrad0;
    QString inrad1;
    QString inrad2;
    QString inrad3;
    QString inrad4;			// till för sparade av orderrader
    QString errorrad;
    QString errorrad0;
    QString errorrad1;
    QString errorrad2;
    QString errorrad3;
    QString errorrad4;		// till för sparade av orderrader
    QString rad;
    QString hjelpfil;    
    
    QString offertnr;
    QString ordernr;			// För den nya ordern

    QString orderdatum;		// För den nya ordern
    QString offertdatum;    
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
    
    QString seljare;
    QString godsmarke;
    QString offertleveranstid;
    QString offertvaluta;
    QString offertbetvillkor;
    QString offertlevvillkor;
    QString offertlevplats;
    QString offertstatus;
    QString offerthuvuddata;       
    QString offertmoms;
    QString offertsumma;
    QString fraktbelopp;
    QString fraktmomskr;
    QString momssumma;		/*  Total moms på offertn */
    QString offerttotal;
    
void frmOffertTillOrder::init()
{
    QDateTime dt = QDateTime::currentDateTime();
    orderdatum=dt.toString("yyyy-MM-dd");
     
    frmOffertTillOrder::listViewOfferter_format();
    getOffertLista();
    listViewOfferter->setFocus();
}

void frmOffertTillOrder::lineEditOffertNr_returnPressed()
{
    pushButtonAvbryt->setFocus();
}

void frmOffertTillOrder::pushButtonCreateOrder_clicked()
{
    frmOffertTillOrder::getOrderNr();
    frmOffertTillOrder::getOffertHuvud();		// och spara orderhuvud,saveOrderHuvud()
//    frmOffertTillOrder::saveOrderHuvud();
//    frmOffertTillOrder::getOffertRader();		// och spara orderrader,  saveOrderRader()
    
    pushButtonAvbryt->setFocus();
}

void frmOffertTillOrder::Pickupoffertnr( QListViewItem * item)
{
    char offertnummer[11]="";
//    qDebug("Pickupoffertnr\n");
    if(!item){
	return;
    }
     listViewOfferter->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(offertnummer,item->key(0,TRUE));
     offertnr=offertnummer;
     lineEditOffertNr->setText((offertnr));
     lineEditOffertNr->setFocus();
}

void frmOffertTillOrder::listViewOfferter_format()
{
    listViewOfferter->setColumnWidth(0,60);		// Offertnr
    listViewOfferter->setColumnWidth(1,60);		// Kundnr
}


void frmOffertTillOrder::getOffertLista()
{
	const char *userp = getenv("USER");
	QString usr(userp);
	 inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "OFFLST");	// OLFIX funktion

	frmOffertTillOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
	frmOffertTillOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
	frmOffertTillOrder::connect( process, SIGNAL(processExited() ),this, SLOT(OffertListaEndOfProcess() ) );

	if ( !process->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFLST ",
                            "Kan inte starta STYRMAN/OFFLST!\n"
                            );
        }
}

void frmOffertTillOrder::DataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }   
}

void frmOffertTillOrder::DataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmOffertTillOrder::OffertListaEndOfProcess()
{
    QListViewItem* item;
    int i;
    listViewOfferter->setSorting(0,TRUE);
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OFF2ORDW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }

    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
         if (i != -1) {
	QMessageBox::information( this, "OFF2ORDW",
		"Offertregistret innehåller inga poster!\n"
	);
	i = -1;
	

     }

    QString listrad;
    rad=inrad;
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
	item = new QListViewItem(listViewOfferter,offertnr,kundnr);
// 	 rensa 
	
  	for (l=0;l<sizeof(offertnr);l++)
		offertnr[l]=*("\0");
  	for (l=0;l<sizeof(kundnr);l++)
		kundnr[l]=*("\0");
//	 rensa listrad 
	listrad.remove(0,80);
    }
}

void frmOffertTillOrder::pushButtonHelp_clicked()
{
	inrad="";
	frmOffertTillOrder::readResursFil();		// Hämta path till hjälpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_OFFERT.html";
	hjelpfil=hjelpfil+"#OFFERT2ORDER";		// Lägg till position
/*	qDebug("hjelpfil=%s",hjelpfil.latin1());	*/

	process = new QProcess();
	process->addArgument( "./OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
}

void frmOffertTillOrder::readResursFil()
{
    /**************************************************/
    /*  Läs in .olfixrc filen här			               */
    /* Plocka fram var hjälpfilen finns		               */
    /**************************************************/

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

void frmOffertTillOrder::getOrderNr()
{
	const char *userp = getenv("USER");
	QString usr(userp);


	process0 = new QProcess();
	process0->addArgument("./STYRMAN");	// OLFIX styrprogram
	process0->addArgument(usr);		// userid
	process0->addArgument( "FTGDSP");	// OLFIX funktion
	process0->addArgument("KORNR");	// Senas använda kundordernummer

	frmOffertTillOrder::connect( process0, SIGNAL(readyReadStdout() ),this, SLOT(OrdernrDataOnStdout() ) );
	frmOffertTillOrder::connect( process0, SIGNAL(readyReadStderr() ),this, SLOT(OrdernrDataOnStderr() ) );
	frmOffertTillOrder::connect( process0, SIGNAL(processExited() ),this, SLOT(slotgetOrdernrEndOfProcess() ) );

	if ( !process0->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av FTGDSP ",
                            "Kan inte starta STYRMAN/FTGDSP!\n"
                            );
        }

}

void frmOffertTillOrder::slotgetOrdernrEndOfProcess()
{
    int i,m;
    i = -1;
    i = errorrad0.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OFF2ORDW",
		"ERROR!\n"+errorrad
	);
	errorrad0="";
	i = -1;
     }
     i = -1;
     i = inrad0.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int i1 = inrad0.find( QRegExp("1:"), 0 );
	 int i2 = inrad0.find( QRegExp("2:"), 0 );	
	 int i3 = inrad0.length();
	 m=i2-i1;
	 m=i3-i2;
	 if (i2 != -1){
	     ordernr=inrad0.mid(i2+2,m-4);
//	     qDebug("m=%d  ordernr=%s  i3=%d",m,ordernr.latin1(), i3);
	 }
	 bool ok;
	 int ornr = ordernr.toInt( &ok, 10 ); 
	 ornr++;
	 ordernr = QString::number( ornr, 10 );
	 qDebug("ordernr = %s",ordernr.latin1());	 

	inrad0="";
	errorrad0="";
	i = -1;
    }
//   frmOffertTillOrder::getMoms("MOMS1","H");		
}

void frmOffertTillOrder::UpdateKundOrderNr()
{
/*   Uppdatera ordernummer i FTGDATA, posttyp KORNR=senast använda kundordernr
      Använd funktion FTGUPD KORNR "ordernr+1"
*/
    const char *userp = getenv("USER");
    QString usr(userp);
	
//	qDebug("ordernr=%s",ordernr.latin1());
	inrad="";
	errorrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGUPD");	// OLFIX funktion		
	process->addArgument("KORNR");
	process->addArgument(ordernr);
	
	frmOffertTillOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(kornrDataOnStdout() ) );
	frmOffertTillOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(kornrDataOnStderr() ) );
	frmOffertTillOrder::connect( process, SIGNAL(processExited() ),this, SLOT(slotUpdateOrdernrEndOfProcess() ) );
	    
	if (ordernr == ""){
    	    QMessageBox::warning( this, "OFF2ORDW",
                      "Ordernummer saknas \n" );
	}else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "OFF2ORDW",
                            "Kan inte starta STYRMAN/FTGUPD \n" );
	    }
	}
}

void frmOffertTillOrder::slotUpdateOrdernrEndOfProcess()
{
//    frmOffertTillOrder::SaveOrderRader();
}

/**************************************************************************/
/*		  Hämta offert och skapa order 				*/
/**************************************************************************/

void frmOffertTillOrder::getOffertHuvud()
{
    	const char *userp = getenv("USER");
	QString usr(userp);
	inrad="";

	process1 = new QProcess();
	process1->addArgument("./STYRMAN");		// OLFIX styrprogram
	process1->addArgument(usr);		// userid
	process1->addArgument( "OFFDSP");		// OLFIX funktion
	process1->addArgument(offertnr);

	frmOffertTillOrder::connect( process1, SIGNAL(readyReadStdout() ),this, SLOT(getOffertDataOnStdout() ) );
	frmOffertTillOrder::connect( process1, SIGNAL(readyReadStderr() ),this, SLOT(getOffertDataOnStderr() ) );
	frmOffertTillOrder::connect( process1, SIGNAL(processExited() ),this, SLOT(getOfferthuvudEndOfProcess() ) );

	if ( !process1->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFDSP ",
                            "Kan inte starta STYRMAN/OFFDSP!\n"
                            );
        }
    
/*    frmOffertTillOrder::saveOrderHuvud();	    Ligger i  getOfferthuvudEndOfProcess() */
}

void frmOffertTillOrder::saveOrderHuvud()
{
    QString skilj="_:_";
    offerthuvuddata=skilj;
    
    offerthuvuddata.append(ordernr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(orderdatum);		//Datum då offerten görs till order.
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundnr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundnamn);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundadress);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundpostnr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundpostadr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundland);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundref);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundlevadress);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundlevpostnr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundlevpostadr);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertkundlevland);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(seljare);
    offerthuvuddata.append(skilj);    
    offerthuvuddata.append(offertleveranstid);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertmoms);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertvaluta);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertbetvillkor);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertlevvillkor);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertlevplats);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(godsmarke);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offertsumma);	/* Summa exkl moms */
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(fraktbelopp);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(fraktmomskr);
    offerthuvuddata.append(skilj);        
    offerthuvuddata.append(momssumma);
    offerthuvuddata.append(skilj);
    offerthuvuddata.append(offerttotal);		/* Summa inkl moms */
    offerthuvuddata.append(skilj);
    offerthuvuddata.append("END");
//   qDebug("offerthuvuddata=%s",offerthuvuddata.latin1());
   getOffertRader();
/*************************************************************************/
/*	Uppdatera databasen						*/
/*************************************************************************/
   const char *userp = getenv("USER");
   QString usr(userp);
	    
	process2 = new QProcess();
	process2->addArgument("./STYRMAN");		// OLFIX styrprogram
	process2->addArgument(usr);		// userid
	process2->addArgument( "ORDADD");		// OLFIX funktion		Orderhuvud till ORDERREG
	process2->addArgument(offerthuvuddata);
	
	frmOffertTillOrder::connect( process2, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmOffertTillOrder::connect( process2, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
                frmOffertTillOrder::connect( process2, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );
	    
	if (offerthuvuddata == "" ){
    	    QMessageBox::warning( this, "OFF2ORDW",
                      "Data saknas till offerthuvud! \n" );
	}else {
	    if ( !process2->start() ) {
		// error handling
		QMessageBox::warning( this, "OFF2ORDW",
                            "Kan inte starta STYRMAN/ORDADD! \n" );
	    }	
	}
}


void frmOffertTillOrder::getOffertRader()
{
//    qDebug("getOffertRader() start! Offertnr=%s",offertnr.latin1());
	const char *userp = getenv("USER");
	QString usr(userp);
	 inrad3="";

	process3 = new QProcess();
	process3->addArgument("./STYRMAN");		// OLFIX styrprogram
	process3->addArgument(usr);		// userid
	process3->addArgument( "OFFRDSP");		// OLFIX funktion
	process3->addArgument(offertnr );	

	frmOffertTillOrder::connect( process3, SIGNAL(readyReadStdout() ),this, SLOT(OffertRadDataOnStdout() ) );
	frmOffertTillOrder::connect( process3, SIGNAL(readyReadStderr() ),this, SLOT(OffertRadDataOnStderr() ) );
	frmOffertTillOrder::connect( process3, SIGNAL(processExited() ),this, SLOT(OffertRaderEndOfProcess() ) );

	if ( !process3->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av OFFRDSP ",
                            "Kan inte starta STYRMAN/OFFRDSP!\n"
                            );
        }    
//   frmOffertTillOrder::saveOrderRader(); 
}

void frmOffertTillOrder::saveOrderRader()
{

    
    
}

void frmOffertTillOrder::getOfferthuvudEndOfProcess()
{
    int i,m;

    i = -1;
    i = errorrad1.find( QRegExp("Error:"), 0 );
 //   qDebug("Error:",errorrad1);
         if (i != -1) {
	QMessageBox::critical( this, "OFF2ORDW",
		"ERROR!\n"+errorrad1
	);
	errorrad1="";
	i = -1;
     }
     i = -1;

     i = inrad1.find( QRegExp("OK:"), 0 );
     if (i != -1) {
//	 qDebug("inrad1=%s",inrad.latin1());
	 
//	 int i1 = inrad1.find( QRegExp("01:"), 0 );
	 int i2 = inrad1.find( QRegExp("03:"), 0 );	
	 int i3 = inrad1.find( QRegExp("04:"), 0 );
	 int i4 = inrad1.find( QRegExp("05:"), 0 );
	 int i5 = inrad1.find( QRegExp("06:"), 0 );
	 int i6 = inrad1.find( QRegExp("07:"), 0 );
	 int i7 = inrad1.find( QRegExp("08:"), 0 );
	 int i8 = inrad1.find( QRegExp("09:"), 0 );
	 int i9 = inrad1.find( QRegExp("10:"), 0 );
	 int i10 = inrad1.find( QRegExp("11:"), 0 );
	 int i11 = inrad1.find( QRegExp("12:"), 0 );
	 int i12 = inrad1.find( QRegExp("13:"), 0 );
	 int i13 = inrad1.find( QRegExp("14:"), 0 );	
	 int i14 = inrad1.find( QRegExp("15:"), 0 );
	 int i15 = inrad1.find( QRegExp("16:"), 0 );	
	 int i16 = inrad1.find( QRegExp("17:"), 0 );
	 int i17 = inrad1.find( QRegExp("18:"), 0 );
	 int i18 = inrad1.find( QRegExp("19:"), 0 );
	 int i19 = inrad1.find( QRegExp("20:"), 0 );
	 int i20 = inrad1.find( QRegExp("21:"), 0 );
	 int i21 = inrad1.find( QRegExp("22:"), 0 );	
	 int i22 = inrad1.find( QRegExp("23:"), 0 );	
	 int i23 = inrad1.find( QRegExp("24:"), 0 );
	 int i24 = inrad1.find( QRegExp("25:"), 0 );
//	 int i25 = inrad1.find( QRegExp("26:"), 0 );
//	 int i26 = inrad1.find( QRegExp("27:"), 0 );
//	 int i27 = inrad1.find( QRegExp("28:"), 0 );
	 int i28 = inrad1.find( QRegExp("29:"), 0 );
	 int i29 = inrad1.find( QRegExp("30:"), 0 );
	 int i30 = inrad1.find( QRegExp("31:"), 0 );
//	 int i31 = inrad1.find( QRegExp("32:"), 0 );
	 int i32 = inrad1.find( QRegExp("33:"), 0 );
	 int i33 = inrad1.find( QRegExp("34:"), 0 );	
	 int i34 = inrad1.find( QRegExp("35:"), 0 );
	 int i35 = inrad1.find( QRegExp("36:"), 0 );
	 int i36 = inrad1.find( QRegExp("37:"), 0 );
	 int i37 = inrad1.find( QRegExp("38:"), 0 );
	 int i38 = inrad1.find( QRegExp("END"), 0 );
/*	 int i38 = inrad1.find( QRegExp("39:"), 0 );
	 int i39 = inrad1.find( QRegExp("40:"), 0 );
	 int i40 = inrad1.find( QRegExp("41:"), 0 );
	 int i41 = inrad1.find( QRegExp("42:"), 0 );
	 int i42 = inrad1.length();			*/
/*
	 m=i2-i1;
	 if (i1 != -1){
	     kundid=inrad1.mid(i1+3,m-4);
	 }
*/
 	 m=i3-i2;
	 if (i2 != -1){
	     offertkundnr=inrad1.mid(i2+3,m-4);
	 }
/*
	 m=i4-i3;
	 if (i3 != -1){					// offerttyp 
	     offertkundnamn=inrad1.mid(i3+3,m-4);
	 }
*/
	 m=i5-i4;						// offertstatus
	 if (i4 != -1){
	     offertstatus=inrad1.mid(i4+3,m-4);
	 }

 	 m=i6-i5;
	 if (i5 != -1){					// offertdatum
	     offertdatum=inrad1.mid(i5+3,m-4);
	 }

	 m=i7-i6;
	 if (i6 != -1){					// Leveransdatum
	     offertleveranstid=inrad1.mid(i6+3,m-4);
	 }

 	 m=i8-i7;
	 if (i7 != -1){					// Kundnamn
	     offertkundnamn=inrad1.mid(i7+3,m-4);
	 }

 	 m=i9-i8;
	 if (i8 != -1){					// Kundadress
	     offertkundadress=inrad1.mid(i8+3,m-4);
	 }

	 m=i10-i9;
	 if (i9 != -1){					// Kundpostnummer
	     offertkundpostnr=inrad1.mid(i9+3,m-4);
	 }

 	 m=i11-i10;
	 if (i10 != -1){					// Kundpostadress
	     offertkundpostadr=inrad1.mid(i10+3,m-4);
	 }

 	 m=i12-i11;
	 if (i11 != -1){					// Land
	     offertkundland=inrad1.mid(i11+3,m-4);
	 }

 	 m=i13-i12;
	 if (i12 != -1){					// Kundens referens
	     offertkundref=inrad1.mid(i12+3,m-4);
	 }

 	 m=i14-i13;
	 if (i13 != -1){					// Leveransadress
	     offertkundlevadress=inrad1.mid(i13+3,m-4);
	 }

 	 m=i15-i14;
	 if (i14 != -1){					// Leveranspostnr
	     offertkundlevpostnr=inrad1.mid(i14+3,m-4);	
	 }

	 m=i16-i15;
	 if (i15 != -1){					// Leveranspostadress
	    offertkundlevpostadr=inrad1.mid(i15+3,m-4);
	 }

 	 m=i17-i16;
	 if (i16 != -1){					// Leveransland
	     offertkundlevland=inrad1.mid(i16+3,m-5);
	 }

	 m=i18-i17;
/*	 if (i17 != -1){					// Vår referent
	     offertbetvillkor=inrad1.mid(i17+3,m-4);
	 }
*/
	 m=i19-i18;
	 if (i18 != -1){					// Seljare
	     seljare=inrad1.mid(i18+3,m-4);
	 }

	 m=i20-i19;
	 if (i19 != -1){					// Godsmärke
	     godsmarke=inrad1.mid(i19+3,m-4);
	 }

	 m=i21-i20;
	 if (i20 != -1){					// Betalningsvillkorstyp
/*	     offertbetvillkortyp=inrad1.mid(i20+3,m-4);
*/	 }

	 m=i22-i21;
	 if (i21 != -1){					// Betalningsvillkor
	     offertbetvillkor=inrad1.mid(i21+3,m-4);
	 }

	 m=i23-i22;
	 if (i22 != -1){					// Leveransvillkor
	    offertlevvillkor=inrad1.mid(i22+3,m-4);
	 }

	 m=i24-i23;
	 if (i23 != -1){					// Leveransplats /LEVSETT)
	    offertlevplats=inrad1.mid(i23+3,m-4);
	 }
/*
	 m=i25-i24;
	 if (i24 != -1){					// Plocklista
	     plocklista=inrad1.mid(i24+3,m-4);
	 }

	 m=i26-i25;
	 if (i25 != -1){					// Följesedel
	     foljesedel=inrad1.mid(i25+3,m-4);
	 }

	 m=i27-i26;
	 if (i26 != -1){					// Fraktavgift	
	     kravbrev=inrad1.mid(i26+3,m-4);
	 }

	 m=i28-i27;
	 if (i27 != -1){					// Skattekod
	     sprakkod=inrad1.mid(i27+3,m-4);
	 }
*/
 	 m=i29-i28;
	 if (i28 != -1){					// Moms i %
	    offertmoms=inrad1.mid(i28+3,m-4);
	 }

	 m=i30-i29;
	 if (i29 != -1){					// Valuta
	    offertvaluta=inrad1.mid(i29+3,m-4);
	 }
/*
	 m=i31-i30;
	 if (i30 != -1){					// Exportkod
	     kreditlimit=inrad1.mid(i30+3,m-4);
	 }

	 m=i32-i31;
	 if (i31 != -1){					//  Språkkod
	     kreditdagar=inrad1.mid(i31+3,m-4);
	 }
*/
	 m=i33-i32;
	 if (i32 != -1){					// offertsumma exklusive moms
	    offertsumma=inrad1.mid(i32+3,m-4);
	 }

	 m=i34-i33;
	 if (i33 != -1){					// Fraktavgift i kronor exklusive moms
	    fraktbelopp=inrad1.mid(i33+3,m-4);
	 }

 	 m=i35-i34;
	 if (i34 != -1){
	    fraktmomskr=inrad1.mid(i34+3,m-4);			// = Moms i kr på fraktbeloppet
	 }

 	 m=i36-i35;
	 if (i35 != -1){
	    momssumma=inrad1.mid(i35+3,m-4);		// Total moms på offertn i kronor
	 }

	 m=i37-i36;
	 if (i36 != -1){					// Total offertsumma inklusive moms
	    offerttotal=inrad1.mid(i36+3,m-4);
	 }
/*
	 m=i38-i37;
	 if (i37 != -1){
	     drofmalsfakt=inrad1.mid(i37+3,m-4);
	 }

	 m=i39-i38;
	 if (i38 != -1){
	    samfaktura=inrad1.mid(i38+3,m-4);
	 }

	 m=i40-i39;
	 if (i39 != -1){
	    kravdatum=inrad1.mid(i39+3,m-4);
	 }

	 m=i41-i40;
	 if (i40 != -1){
	    skuld=inrad1.mid(i40+3,m-4);
	 }

	 m=i42-i41;
	 if (i41 != -1){
	    offertstock=inrad1.mid(i41+3,m-4);
	 }
*/
	 inrad1="";
	errorrad1="";
	i = -1;
     }
      frmOffertTillOrder::saveOrderHuvud();		/* Ligger här för att säkerställa att alldata har hämtats */
}

void frmOffertTillOrder::OffertRaderEndOfProcess()
{
//    qDebug("OffertRaderEndOfProcess()::Hämta offertrad! Offertnr=%s",offertnr.latin1());
    /*  Orderradrad	 */
    QString orderkundnr=offertkundnr;
    QString orderradnr;
    QString oldradnr;
    QString radtyp;
    QString orderartikelnr;
    QString prodklass;
    QString orderbenamn;
    QString radleveransvecka;
    QString orderantal;
    QString orderradpris;
    QString radbelopp;
    QString radmoms;		/*  Moms på radbelopp (11) */
    QString levantal;			/* Levererart antal    (12)*/
    QString restantal;		/* Resterande antal   (13)*/
    QString radrabatt;		/*                                   (14)*/
    QString kalkylpris;		/*                                   (15)*/
    QString levdatum;		/* Leveransdatum      (16)*/
    QString enhet;			/* Enhet (st, liter, m)  (17)*/ 
    QString faktantal;		/* Fakturerat antal   (18)*/
//    qDebug("OffertRaderEndOfProcess()::inrad3=%s.  errorrad3=%s",inrad3.latin1(),errorrad3.latin1());
    int i,m,n;
    QString tmp;

    i = -1;
    i = errorrad3.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OFF2ORDW",
		"ERROR!\n"+errorrad3
	);
	errorrad3="";
	i = -1;
     }
     i = -1;

     i = inrad3.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 int p1 = inrad3.find( QRegExp("OK:"), 0 );
	 int p2 = inrad3.find( QRegExp("_:_"), 0 );
	 int n1=(p2)-(p1+3);
	 tmp=inrad3.mid(p1+3,n1);
	 int n2=tmp.toInt();
	 int m1=0;
//	 qDebug("inrad=%s",inrad3.latin1());
//	 qDebug("p1=%d p2=%d n1=%d tmp=%s n2=%d",p1,p2,n1,tmp.latin1(),n2);
	 for (n=1;n<=n2;n++){
     	     int i2 = inrad3.find( QRegExp("_:_02_:_"), m1 );	// ordernr, kommande
	     int i3 = inrad3.find( QRegExp("_:_03_:_"), m1 );	// radnr
	     int i4 = inrad3.find( QRegExp("_:_04_:_"), m1 );	// kundnr
	     int i5 = inrad3.find( QRegExp("_:_05_:_"), m1 );		// radtyp
	     int i6 = inrad3.find( QRegExp("_:_06_:_"), m1 );	// artikelnr
	     int i7 = inrad3.find( QRegExp("_:_07_:_"), m1 );	// benämning
	     int i8 = inrad3.find( QRegExp("_:_08_:_"), m1 );	// leveransvecka
	     int i9 = inrad3.find( QRegExp("_:_09_:_"), m1 );	// antal
	     int i10 = inrad3.find( QRegExp("_:_10_:_"), m1 );	// apris
	     int i11 = inrad3.find( QRegExp("_:_11_:_"), m1 );	// summa rad, belopp inklusive moms
	     int i12 = inrad3.find( QRegExp("_:_12_:_"), m1 );	// Moms i kr
	     int i13 = inrad3.find( QRegExp("_:_13_:"), m1 );	// Levererat antal
	     int i14 = inrad3.find( QRegExp("_:_14_:"), m1 );	// Restnoterat antal
	     int i15 = inrad3.find( QRegExp("_:_15_:"), m1 );	// Radrabatt
	     int i16 = inrad3.find( QRegExp("_:_16_:_"), m1 );	// Kalkylpris
	     int i17 = inrad3.find( QRegExp("_:_17_:_"), m1 );	// Leveransdatum
	     int i18 = inrad3.find( QRegExp("_:_18_:_"), m1 );	// Enhet (st, liter ...)
	     int i19 = inrad3.find( QRegExp("_:__:_NEXT_:_"), m1 );
	     m1=m1+i19+13; /* 10 ? */
	     m=i3 - i2 - 8;
	     
	     m=i4 - i3 - 8;
	     orderradnr=inrad3.mid(i3+8,m);
//	     qDebug("orderradnr=%s",orderradnr.latin1());
	     m=i6 - i5 - 8;
	     radtyp=inrad3.mid(i5+8,m);
	     radtyp=radtyp.stripWhiteSpace();
//	     qDebug("radordertyp=%s ",radtyp.latin1());
	     m=i7 - i6 - 8;
	     orderartikelnr=inrad3.mid(i6+8,m);
	     orderartikelnr=orderartikelnr.stripWhiteSpace();
//	     qDebug("orderartikelnr=%s m=%d",orderartikelnr.latin1(),m);
	     m=i8 - i7 - 8;
	     orderbenamn=inrad3.mid(i7+8,m);
	     orderbenamn=orderbenamn.stripWhiteSpace();
//	     qDebug("benämning=%s",orderbenamn.latin1());
	     m=i9 - i8 - 8;
	     radleveransvecka=inrad3.mid(i8+8,m);
	     radleveransvecka=radleveransvecka.stripWhiteSpace();
//	     qDebug("radleveransvecka=%s",radleveransvecka.latin1());
	     m=i10 - i9 - 8;
	     orderantal=inrad3.mid(i9+8,m);			// antal
	     orderantal=orderantal.stripWhiteSpace();
//	     qDebug("orderantal=%s",orderantal.latin1());
	     m=i11 - i10 - 8;
	     orderradpris=inrad3.mid(i10+8,m);			// apris
	     orderradpris=orderradpris.stripWhiteSpace();
//	     qDebug("orderradpris=%s",orderradpris.latin1());
	     m=i12 - i11 - 8;
	     radbelopp=inrad3.mid(i11 + 8,m);			// summa exklusive moms
	     radbelopp=radbelopp.stripWhiteSpace();
//	     qDebug("radbelopp=%s",radbelopp.latin1());
	     m=i13 - i12 - 8;
	     radmoms=inrad3.mid(i12 + 8,m);			// moms i kronor
	     radmoms=radmoms.stripWhiteSpace();
//	     qDebug("radmoms=%s",radmoms.latin1());
	     m=i14 - i13 - 8;
	     levantal=inrad3.mid(i13 + 8,m);			// levererat antal
	     levantal=levantal.stripWhiteSpace();
//	     qDebug("levererat antal=%s",levantal.latin1());
	     m=i15 - i14 - 8;					// restnoterat
	     restantal=inrad3.mid(i14 + 8,m);	
	     restantal=restantal.stripWhiteSpace();
//	     qDebug("restnoterat antal=%s",restantal.latin1());		
	     m=i16 - i15 - 8;					// radrabatt
	     radrabatt=inrad3.mid(i15 + 8,m);
	     radrabatt=radrabatt.stripWhiteSpace();
//	     qDebug("radrabatt=%s",radrabatt.latin1());		
	     m=i17 - i16 - 8;					// kalkylpris
	     kalkylpris=inrad3.mid(i16 + 8,m);
	     kalkylpris=kalkylpris.stripWhiteSpace();
//	     qDebug("kalkylpris=%s",kalkylpris.latin1());
	     m=i18 - i17 - 8;					// leveransdatum för orderrad
	     levdatum=inrad3.mid(i17 + 8,m);
	     levdatum=levdatum.stripWhiteSpace();
//	     qDebug("leveransdatum=%s",levdatum.latin1());		
	     m=i19 - i18 - 8;					// enhet			
	     enhet=inrad3.mid(i18 + 8,m);
	     enhet=enhet.stripWhiteSpace();
//	     qDebug("enhet=%s",enhet.latin1());
       	     faktantal="0";
	     faktantal=faktantal.stripWhiteSpace();
//	     qDebug("fakturerat=%s",faktantal.latin1());
	     	     
/**************************************************************************/
/*	     Här skapas en orderrad för varje offertrad för sig. 			*/
/**************************************************************************/
	     QString orderraddata="";
	     QString skilj;
//	     qDebug("ordernr=%s",ordernr.latin1());
	     skilj="_:_";
	     orderraddata=skilj;
	     orderraddata.append(ordernr);	// ordernr
	     orderraddata.append(skilj);
	     orderraddata.append(orderradnr);	// radnr
	     orderraddata.append(skilj);    
	     orderraddata.append(orderkundnr);	// kundnummer
	     orderraddata.append(skilj);
/*	     orderraddata.append(radtyp);		// radtyp	
	     orderraddata.append(skilj);    	*/
	     orderraddata.append(orderartikelnr);	// artikelnr
	     orderraddata.append(skilj);
	     orderraddata.append(orderbenamn);	//benämning
	     orderraddata.append(skilj);
	     orderraddata.append(radleveransvecka);	// leveransvecka
	     orderraddata.append(skilj);    
	     orderraddata.append(orderantal);	// antal
	     orderraddata.append(skilj);
	     orderraddata.append(orderradpris);	// a'-pris
	     orderraddata.append(skilj);
	     orderraddata.append(radbelopp);	// summa exkl moms.
	     orderraddata.append(skilj);    
	     orderraddata.append(radmoms);	// momskr.
	     orderraddata.append(skilj);    
	     orderraddata.append(levantal);	// levantal
	     orderraddata.append(skilj);    
	     orderraddata.append(restantal);	// restantal
	     orderraddata.append(skilj);
	     orderraddata.append(radrabatt);	// radrabatt
	     orderraddata.append(skilj);    
	     orderraddata.append(kalkylpris);	// kalkylpris
	     orderraddata.append(skilj);    
	     orderraddata.append(levdatum);	// levdatum
	     orderraddata.append(skilj);    
	     orderraddata.append(enhet);	// enhet
	     orderraddata.append(skilj);    
	     orderraddata.append(faktantal);	// faktantal
	     orderraddata.append(skilj);    
	     orderraddata.append("END");	
	     
//	     qDebug("orderraddat=%s",orderraddata.latin1());
	     //    frmChgOrder::ChangeOrderRad();		
	     //    frmChgOrder::updateReserveratAntal(tmp1,tmp4);  	// parallell bearbetning
	     	     
/**************************************************************************/
/*	     Här sparas varje rad för sig. 					*/
/**************************************************************************/
	     processnbr=processnbr+1;			// Nytt processnbr för varje ny orderrad
	     if (processnbr > 195){
		 processnbr=1;
	     }
//	     qDebug("processnummer=%d",processnbr);
	     
	     const char *userp = getenv("USER");
	     QString usr(userp);
	     inrad4="";
	     errorrad4="",
	     
	     process4[processnbr] = new QProcess();
	     process4[processnbr]->addArgument("./STYRMAN");		// OLFIX styrprogram
	     process4[processnbr]->addArgument(usr);			// userid
	     process4[processnbr]->addArgument( "ORDRADD");		// OLFIX funktion
	     process4[processnbr]->addArgument(orderraddata);	

	     frmOffertTillOrder::connect( process4[processnbr], SIGNAL(readyReadStdout() ),this, SLOT(OffertRadDataOnStdout() ) );
	     frmOffertTillOrder::connect( process4[processnbr], SIGNAL(readyReadStderr() ),this, SLOT(OffertRadDataOnStderr() ) );
	     frmOffertTillOrder::connect( process4[processnbr], SIGNAL(processExited() ),this, SLOT(OffertRaderEndOfProcess4() ) );
	     
	     if ( !process4[processnbr]->start() ) {
		 // error handling
		 QMessageBox::warning( this, "Start av ORDRADD ",
				       "Kan inte starta STYRMAN/ORDRADD!\n"
				       );
	     }    
	 }
     }
     UpdateKundOrderNr();						// Uppdateraordernr i tabellen FTGDATA		
     pushButtonAvbryt->setFocus();
}

void frmOffertTillOrder::deleteOffert()
{
    const char *userp = getenv("USER");
    QString usr(userp);
    inrad="";
    errorrad="",
	     
    process = new QProcess();
    process->addArgument("./STYRMAN");		// OLFIX styrprogram
    process->addArgument(usr);			// userid
    process->addArgument( "OFFDEL");		// OLFIX funktion
    process->addArgument(offertnr);	

     frmOffertTillOrder::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
     frmOffertTillOrder::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
     frmOffertTillOrder::connect( process, SIGNAL(processExited() ),this, SLOT(OffertDeleteEndOfProcess() ) );
	     
     if ( !process4[processnbr]->start() ) {
	 // error handling
	 QMessageBox::warning( this, "Start av OFFDEL",
			       "Kan inte starta STYRMAN/OFFDEL!\n"
			       );
     }    
}

void frmOffertTillOrder::OffertDeleteEndOfProcess()
{
    int i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OFF2ORDW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
     }
     i = -1;

     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	QMessageBox::information( this, "OFF2ORDW",
		"Ny order nr %s skapad av offert!\n",ordernr
	);
    }
}

void frmOffertTillOrder::getOffertDataOnStdout()
{
     while (process1->canReadLineStdout() ) {
	QString line = process1->readStdout();
	inrad1.append(line);
	inrad1.append("\n");   
    }
}

void frmOffertTillOrder::getOffertDataOnStderr()
{
      while (process1->canReadLineStderr() ) {
	QString line = process1->readStderr();
	errorrad1.append(line);
	errorrad1.append("\n");
    }  
}

void frmOffertTillOrder::OrdernrDataOnStdout()
{
     while (process0->canReadLineStdout() ) {
	QString line = process0->readStdout();
	inrad0.append(line);
	inrad0.append("\n");   
    }
}

void frmOffertTillOrder::OrdernrDataOnStderr()
{
      while (process0->canReadLineStderr() ) {
	QString line = process0->readStderr();
	errorrad0.append(line);
	errorrad0.append("\n");
    }  
}

void frmOffertTillOrder::OffertRadDataOnStdout()
{
     while (process3->canReadLineStdout() ) {
	QString line = process3->readStdout();
	inrad3.append(line);
	inrad3.append("\n");   
    }
//     qDebug("OffertRadDataOnStdout()::inrad3=%s",inrad3.latin1());
}

void frmOffertTillOrder::OffertRadDataOnStderr()
{
      while (process3->canReadLineStderr() ) {
	QString line = process3->readStderr();
	errorrad3.append(line);
	errorrad3.append("\n");
    }  
}

void frmOffertTillOrder::slotDataOnStdout()
{
     while (process2->canReadLineStdout() ) {
	QString line = process2->readStdout();
	inrad2.append(line);
	inrad2.append("\n");   
    }
}

void frmOffertTillOrder::slotDataOnStderr()
{
      while (process2->canReadLineStderr() ) {
	QString line = process2->readStderr();
	errorrad2.append(line);
	errorrad2.append("\n");
    }  
}

void frmOffertTillOrder::kornrDataOnStdout()
{
     while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");   
    }
}

void frmOffertTillOrder::kornrDataOnStderr()
{
      while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmOffertTillOrder::slotEndOfProcess() 
{
    getOffertRader();
}

void frmOffertTillOrder::OffertRaderEndOfProcess4()
{
    int i;
    i = -1;
    i = errorrad4.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OFF2ORDW",
		"ERROR!\n"+errorrad4
	);
	errorrad4="";
	i = -1;
     }
     i = -1;

     i = inrad4.find( QRegExp("OK:"), 0 );
}



