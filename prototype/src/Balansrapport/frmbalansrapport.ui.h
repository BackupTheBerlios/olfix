/****************************************************************/
/**		BALRPTW					*/
/**		Ver 0.2                                                                                    */
/**		Created    2004-03-19				*/
/**		Modified: 2005-01-09				*/
/**   Copyright	Jan Pihlgren	jan@pihlgren.se			*/
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
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qdatetime.h>
#define VERSION "0.1"
#define MAXSTRING 5000

    QProcess* process;
    QString inrad;
    QString errorrad;
    QString inradPeriod;
    QString errorradPeriod;
    
    QString bar;		// Bokföringsår
    QString csvflag;
    QString delsumflag;
    QString datum;
    QString fromdate;
    QString tomdate;
    QString period;    
    QString ftgnamn;
    
    QString reportpath;
    QString tmppath;
    QString kugarversion;
    QString kommando;
    
void frmBalansrapport::init()
{
    csvflag="N";		/*  Ska det vara en kommaseparerad rapport för Kspread. N=Nej 	*/
			/*  N = Gör en Kugarrapport 					*/
                                    /*  J = Gör en Kspreadrapport  				*/
    delsumflag="1";	/* På vilken nivå ska delsummor göras. Default = nivå 1  	*/
    
    QDateTime dt = QDateTime::currentDateTime();
    datum=dt.toString("yyyy-MM-dd");
    textLabelDatum->setText(datum);
    frmBalansrapport::KugarVersion();
    frmBalansrapport::GetReportDir();
    frmBalansrapport::GetTmpDir();
    frmBalansrapport::getFortetagsnamn();
}

void frmBalansrapport::slotlineEditBar_returnPressed()
{
    bar=lineEditBar->text();
    bar=bar.upper();
    lineEditBar->setText((bar));
    if (bar==""){
	QMessageBox::warning( this, "BALRPTW",
                      "Bokföringsår måste fyllas i! \n" );
	lineEditBar->setFocus();
    }else{  
	pushButtonOK->setFocus();
    }
    frmBalansrapport::GetBokfPeriod();	// Hämta fromdate och tomdate( datum för första och sista verifikationen)
//    qDebug("fromdate=%s, tomdate=%s",fromdate.latin1(),tomdate.latin1());
//    period=fromdate+" -- "+tomdate;
//    qDebug("period=%s",period.latin1());
}

void frmBalansrapport::radioButtonKto1_toggled( bool )
{
    delsumflag="1";
}

void frmBalansrapport::radioButtonKto2_toggled( bool )
{
    delsumflag="2";
}

void frmBalansrapport::radioButtonKto3_toggled( bool )
{
    delsumflag="3";
}

void frmBalansrapport::radioButtonKto4_toggled( bool )
{
    delsumflag="4";
}

void frmBalansrapport::radioButtonCSV_toggled( bool )
{
    csvflag="J";
}

void frmBalansrapport::radioButtonPrint_toggled( bool )
{
    csvflag="N";
}

void frmBalansrapport::slotpushButtonOK_clicked()
{
    if (csvflag != "J"){
	slotFileRemove("Balansrapport.kud");		// tag bort gammal datafil
	slotCreateHeader();
    }else{
	slotFileRemove("Balansrapport.txt");		// tag bort gammal datafil	
    }
    slotGetData();
    pushButtonAvbryt->setFocus();
}

void frmBalansrapport::slotGetData()
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "KTORPT");	// OLFIX funktion
	process->addArgument(bar);		// Bokföringsår
	process->addArgument(fromdate);		// Från och med datum
	process->addArgument(tomdate);		// Till och med datum

	frmBalansrapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmBalansrapport::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmBalansrapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );


	if (bar == "" ){
    	    QMessageBox::warning( this, "BALRPTW",
                      "Bokföringsår måste vara ifyllt!" );
	}
	else {
	    if ( !process->start() ) {
		// error handling
		QMessageBox::warning( this, "BALRPTW",
                            "Kan inte starta STYRMAN/KTORPT! \n" );
	    }
	}
}

void frmBalansrapport::slotEndOfProcess()
{
    int i,j,m,n;
    int ant;
    int klassflag=0;

    QString antal;
    QString ktonr;
    QString ktonamn;
    QString dk;
    QString belopp;
    QString vernr;
    
    QString rubrik;
    QString ktotemp;
    QString ktonamntemp;
    int klasstemp=0;

//	Summa per konto    
    QString debetsum;		// Summa Debet
    QString kreditsum;		// Summa Kredit
    QString utgsaldo;		// Utgående saldo
    double debet=0;
    double kredit=0;
    double usaldo=0;
    
//	Summa per kontoklass    
    QString delsumdebet;
    QString delsumkredit;
    QString delsumutgsaldo;
    double deldebet=0;
    double delkredit=0;
    double delusaldo=0;
    
    QString fil;
    QString rapportrad;
    QString rubrikrad;
        
    if (csvflag == "J"){
	fil=tmppath+"Balansrapport.txt";
    }else{
	fil=tmppath+"Balansrapport.kud";
    }
    
    QFile filnamn( fil );
    utgsaldo="0.00";
//    qDebug("slotEndOfProcess() 1::inrad=%s",inrad.latin1());
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - BALRPTW",
		"ERROR!\n"+errorrad
		);
	errorrad="";
    }else{
	filnamn.open( IO_WriteOnly | IO_Append );
	QTextStream stream(&filnamn);
	
	i = -1;
	i = inrad.find( QRegExp("NR_"), 0 );
	if (i != -1) {
	    j =  inrad.find( QRegExp("_:"), i );
	    m = j - (i + 3);
	    antal = inrad.mid(i +3,m);
	    ant=antal.toInt();		/* Antal verifikationsrader	*/
//	    qDebug("slotEndOfProcess() 2 ::antal=%s ant=%d",antal.latin1(),ant);	    
	    ktotemp="";	 
	    for (n=0;n<=ant;n++){
		i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 ktonr = inrad.mid(i+2,m);	
		 qDebug("ktonr=%s",ktonr.latin1());
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 ktonamn = inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 dk = inrad.mid(i+2,m);		//dk = D  = Debet, dk =  K = Kredit 
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 belopp = inrad.mid(i+2,m);
		 i = j;
		 j = inrad.find(QRegExp("_:"),i+2);
		 m = j - (i+2);
		 vernr = inrad.mid(i+2,m);
		 
		 qDebug("ktonr=%s, ktotemp=%s, rubrik=%s, klassflag=%d, klasstemp=%d",ktonr.latin1(),ktotemp.latin1(),rubrik.latin1(),klassflag,klasstemp); 
//		 qDebug("ktonr.mid(0,1)=%s",ktonr.mid(0,1).latin1());
		 if ((ktonr.mid(0,1).toInt()<3) &&(ktonr != ktotemp)){
		     debetsum.setNum(debet,'f',2);
		     kreditsum.setNum(kredit,'f',2);
		     utgsaldo.setNum(usaldo,'f',2);
//		     qDebug("slotEndOfProcess()  3b ::cvsflag=%s",csvflag.latin1());
		     if (csvflag =="J"){			// Skapa rapportrad för Kspread
			 rapportrad=(ktotemp);
			 rapportrad.append(",");
			 rapportrad.append(ktonamntemp);
			 rapportrad.append(",");			 
			 rapportrad.append(debetsum);
			 rapportrad.append(",");
			 rapportrad.append(kreditsum);
			 rapportrad.append(",");			 
			 rapportrad.append(utgsaldo);
			 rapportrad.append("\n");
//			 qDebug("slotEndOfProcess()::rapportrad=%s",rapportrad.latin1());
			 if (ktotemp != ""){
			     stream << rapportrad;
			 }
		     }else{		 		// Skapa raportrad för Kugar
//			 qDebug("ktonr=%s, klassflag=%d, klasstemp=%d",ktonr.latin1(),klassflag,klasstemp);
			 if (ktotemp==""){
			     rapportrad="<Rubrik1 level=\"1\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("1");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append("TILLGÅNGAR");
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=1000;			  
			 }
			 
// 			 if ((klasstemp < 2000) && (ktonr.mid(0,1).toInt()==2 )){
			  if ((klasstemp >=1999) && (klasstemp <= 2001 )){
			     rapportrad="<Rubrik1 level=\"1\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("2");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append("EGET OCH FRÄMMANDE KAPITAL");
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2000;
			     rubrik="EGET OCH FRÄMMANDE KAPITAL";			     
			 }

			 if (ktotemp.mid(0,2).toInt()==10){
//			    frmBalansrapport::Rubrik("10","ANLÄGGNINGSTILLGÅNGAR", 1000);
			     rubrik="ANLÄGGNINGSTILLGÅNGAR";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("10");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=1000;
			     
			 }
			 if (ktotemp.mid(0,2).toInt()==11){
			     rubrik="BYGGNADER OCH MARK";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("11");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=1100;
			 }			 
			 if (ktotemp.mid(0,2).toInt()==12){
//			     frmBalansrapport::Rubrik("12","AMASKINER OCH INVENTARIER", 1200);
			     rubrik="MASKINER OCH INVENTARIER";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("12");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=1200;	     
			 }
			 if (ktotemp.mid(0,2).toInt()==13){
			     rubrik="FINANSIELLA ANLÄGGNINGSTILLGÅNGAR";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("13");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=1300;
			 }
			 if (ktotemp.mid(0,2).toInt()==14){
			     rubrik="LAGER OCH PÅGÅENDE ARBETEN";
			     rubrikrad="<Rubrik2 level=\"2\" ";
			     rubrikrad.append("klass1=\"");
			     rubrikrad.append("14");
			     rubrikrad.append("\" klassnamn=\"");
			     rubrikrad.append(rubrik);
			     rubrikrad.append("\"/>\n");
			     stream << rubrikrad;
			     klassflag=1400;
			 }
//			 if (ktonr.mid(0,2).toInt()==15){
 			 if (ktotemp.mid(0,2).toInt()==15){
			     rubrik="KUNDFORDRINGAR";
			     rubrikrad="<Rubrik2 level=\"2\" ";
			     rubrikrad.append("klass1=\"");
			     rubrikrad.append("15");
			     rubrikrad.append("\" klassnamn=\"");
			     rubrikrad.append(rubrik);
			     rubrikrad.append("\"/>\n");
			     stream << rubrikrad;
			     klassflag=1500;
			 }
			 if (ktotemp.mid(0,2).toInt()==16){
			     rubrik="ÖVRIGA KORTFRISTIGA FORDRINGAR";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("16");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=1600;
			 }
			 if (ktotemp.mid(0,2).toInt()==17){
			     rubrik="FÖRUTBETALDA KOSTNADER";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("17");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=1700;
			 }
			 if (ktotemp.mid(0,2).toInt()==18){
			     rubrik="KORTFRISTIGA PLACERINGAR";
			     rubrikrad="<Rubrik2 level=\"2\" ";
			     rubrikrad.append("klass1=\"");
			     rubrikrad.append("18");
			     rubrikrad.append("\" klassnamn=\"");
			     rubrikrad.append(rubrik);
			     rubrikrad.append("\"/>\n");
			     stream << rubrikrad;
			     klassflag=1800;
			 }
			 if (ktotemp.mid(0,2).toInt()==19){
			     rubrik="KASSA OCH BANK";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("19");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=1900;
			 }
//			 if (ktonr.mid(0,2).toInt()==20 && ktotemp.mid(0,2).toInt()==20){
//			 if (klassflag >=2000 && klassflag <=2099){
			 if (ktotemp.mid(0,2).toInt()==20){
			     rubrik="EGET KAPITAL";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("20");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2000;
			 }
			 if (ktotemp.mid(0,2).toInt()==21){
			     rubrik="OBESKATTADE RESERVER";
			     rubrikrad="<Rubrik2 level=\"2\" ";
			     rubrikrad.append("klass1=\"");
			     rubrikrad.append("21");
			     rubrikrad.append("\" klassnamn=\"");
			     rubrikrad.append(rubrik);
			     rubrikrad.append("\"/>\n");
			     stream << rubrikrad;
			     klassflag=2100;
			 }
			 if (ktotemp.mid(0,2).toInt()==22){
			     rubrik="AVSÄTTNINGAR";			     
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("22");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2200;
			 }
			 if (ktotemp.mid(0,2).toInt()==23){
			     rubrik="LÅNGFRISTIGA SKULDER";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("23");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2300;
			 }
			 if (ktotemp.mid(0,2).toInt()==24){
			     rubrik="KORTFISTIGA SKULDER, KUNDER, LEVERANTÖRER";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("24");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2400;
			 }
			 if (ktotemp.mid(0,2).toInt()==25){
			     rubrik="SKATTESKULDER";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("25");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2500;
			 }
			 if (ktotemp.mid(0,2).toInt()==26){
			     rubrik="MOMS";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("26");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2600;
			 }
			 if (ktotemp.mid(0,2).toInt()==27){
			     rubrik="PERSONALENS KÄLLSKATT MM";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("27");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2700;
			 }
			 if (ktotemp.mid(0,2).toInt()==28){
			     rubrik="ÖVRIGA KORTFRISTIGA SKULDER";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("28");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2800;
			 }
			 if (ktotemp.mid(0,2).toInt()==29){
			     rubrik="UPPLUPNA KOSTNADER MM";
			     rapportrad="<Rubrik2 level=\"2\" ";
			     rapportrad.append("klass1=\"");
			     rapportrad.append("29");
			     rapportrad.append("\" klassnamn=\"");
			     rapportrad.append(rubrik);
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     klassflag=2900;
			 }
			 			 
			 rapportrad="<Row level=\"3\" ";
			 rapportrad.append(" kontonr=\"");
			 rapportrad.append(ktotemp);
			 rapportrad.append("\" kontonamn=\"");
			 ktonamntemp="  "+ktonamntemp;
			 rapportrad.append(ktonamntemp);
			 rapportrad.append("\" debet=\"");
			 rapportrad.append(debetsum);
			 rapportrad.append("\" kredit=\"");
			 rapportrad.append(kreditsum);
			 rapportrad.append("\" utgsaldo=\"");
			 rapportrad.append(utgsaldo);
			  rapportrad.append("\"/>\n");
			  
//			 qDebug("slotEndOfProcess() 3d ::rapportrad=%s klassflag=%d, klasstemp=%d",rapportrad.latin1(),klassflag,klasstemp);
			 if (ktotemp != ""){			  
//			  if  (ktotemp < ktonr && ktotemp != ""){
			     stream << rapportrad;
			     qDebug("Streaming rapportrad");
			 }		    
			 
//	  	   	 qDebug("ktotemp=%s mid=%s",ktotemp.latin1(),ktotemp.mid(0,1).latin1());
			 if (ktonr.mid(0,1) != ktotemp.mid(0,1) && ktotemp !=""){
			     delsumdebet.setNum(deldebet,'f',2);
			     delsumkredit.setNum(delkredit,'f',2);
			     delsumutgsaldo.setNum(delusaldo,'f',2);			
			 
			     rapportrad="<Delsumma level=\"4\" ";
			     rapportrad.append(" delsumdebet=\"");
			     rapportrad.append(delsumdebet);
			     rapportrad.append("\" delsumkredit=\"");
			     rapportrad.append(delsumkredit);
			     rapportrad.append("\" delsumutgsaldo=\"");
			     rapportrad.append(delsumutgsaldo);
//			     qDebug("%s, %s, %s",delsumdebet.latin1(),delsumkredit.latin1(),delsumutgsaldo.latin1());
			     rapportrad.append("\"/>\n");
			     stream << rapportrad;
			     deldebet=0;
			     delkredit=0;
			     delusaldo=0;
			 }
		      }
     		     ktotemp=ktonr;
		     ktonamntemp=ktonamn;
		     klasstemp=klassflag;
		     debet=0;
		     kredit=0;
		     usaldo=0;	     
		 }
		 if (ktonr.mid(0,1).toInt()<3){
		 if (dk == "D"){
		     debet=debet+belopp.toDouble();
		     deldebet=deldebet+belopp.toDouble();
		 }
		 if (dk == "K"){
		     kredit=kredit+belopp.toDouble();
		     delkredit=delkredit+belopp.toDouble();
		 }
		 usaldo=debet -kredit;
		 delusaldo=deldebet-delkredit;
	     }
	     }
	} 
	if (csvflag != "J"){
	    rapportrad="</KugarData>";
	    stream << rapportrad;
	}
    }
    filnamn.close();
    QMessageBox::information( this, "BALRPTW","Rapport skapad!\n");
    if (csvflag == "J"){
	frmBalansrapport::slotRunPrinting("Balansrapport.txt","" );
    }else{
	frmBalansrapport::slotRunPrinting("Balansrapport.kud","Balansrapport.kut" );
    }    
    errorrad="";
     inrad="";
}

void frmBalansrapport::slotCreateHeader()
{
    int i;
    int antrad=55;
    QString rad[antrad];
    QString rapportrad;

    QFile filnamn(tmppath+"Balansrapport.kud");
    QTextStream stream(&filnamn);

    slotFileRemove(tmppath+"Balansrapport.kud");	// radera gammal fil. Ändra till .kud

    rad[1]="<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    rad[2]="<!DOCTYPE KugarData [\n";
    rad[3]="   <!ELEMENT KugarData (Rowhead* )>\n";
    rad[4]="   <!ATTLIST KugarData\n";
    rad[5]="      Template CDATA #REQUIRED>\n\n";
    rad[6]="   <!ELEMENT Rowhead EMPTY>\n";
    rad[7]="   <!ATTLIST Rowhead\n";
    rad[8]="      level CDATA #REQUIRED\n";
    rad[9]="      ftgnamn CDATA #REQUIRED\n";
    rad[10]="      period CDATA #REQUIRED\n";
    rad[11]="      datum CDATA #REQUIRED\n";
    rad[12]=">\n";
    rad[13]="   <!ELEMENT KugarData (Rubrik1* )>\n";
    rad[14]="   <!ATTLIST KugarData\n";
    rad[15]="      Template CDATA #REQUIRED>\n\n";
    rad[16]="   <!ELEMENT Rubrik1 EMPTY>\n";
    rad[17]="   <!ATTLIST Rubrik1\n";
    rad[18]="      level CDATA #REQUIRED\n";
    rad[19]="      klass1 CDATA #REQUIRED\n";
    rad[20]="      klassnamn CDATA #REQUIRED\n";
    rad[21]=">\n";
    rad[22]="   <!ELEMENT KugarData (Rubrik2* )>\n";
    rad[23]="   <!ATTLIST KugarData\n";
    rad[24]="      Template CDATA #REQUIRED>\n\n";
    rad[25]="   <!ELEMENT Rubrik2 EMPTY>\n";
    rad[26]="   <!ATTLIST Rubrik2\n";
    rad[27]="      level CDATA #REQUIRED\n";
    rad[28]="      klass1 CDATA #REQUIRED\n";
    rad[29]="      klassnamn CDATA #REQUIRED\n";
    rad[30]=">\n";

    rad[31]="   <!ELEMENT KugarData (Row* )>\n";
    rad[32]="   <!ATTLIST KugarData\n";
    rad[33]="      Template CDATA #REQUIRED>\n\n";
    rad[34]="   <!ELEMENT Row EMPTY>\n";
    rad[35]="   <!ATTLIST Row\n";
    rad[36]="      level CDATA #REQUIRED\n";
    rad[37]="      kontonr CDATA #REQUIRED\n";
    rad[38]="      kontonamn CDATA #REQUIRED\n";
    rad[39]="      debet CDATA #REQUIRED\n";
    rad[40]="      kredit CDATA #REQUIRED\n";
    rad[41]="      utgsaldo CDATA #REQUIRED";
    rad[42]=">\n";
    rad[43]="   <!ELEMENT KugarData (Delsumma* )>\n";
    rad[44]="   <!ATTLIST KugarData\n";
    rad[45]="      Template CDATA #REQUIRED>\n\n";
    rad[46]="   <!ELEMENT Delsumma EMPTY>\n";
    rad[47]="   <!ATTLIST Delsumma\n";
    rad[48]="      level CDATA #REQUIRED\n";
    rad[49]="      delsumdebet CDATA #REQUIRED\n";
    rad[50]="      delsumkredit CDATA #REQUIRED\n";
    rad[51]="      delsumutgsaldo CDATA #REQUIRED\n";    
    rad[52]=">\n";       
    rad[53]="]>\n\n";
    rad[54]="<KugarData Template=\"";
    rad[54].append(reportpath);
    rad[54].append("Balansrapport.kut\">\n");	// ange rätt template, absolut path

//    qDebug("slotCreateHeader::rapportrad = \n%s",rapportrad.latin1());
    rapportrad=rad[1];
    for (i=2;i<(antrad);i++){
	rapportrad.append(rad[i]);
    }
    rapportrad.append("<Rowhead level=\"0");
    rapportrad.append("\" ftgnamn=\"");
    rapportrad.append(ftgnamn);
    rapportrad.append("\" period=\"");
    rapportrad.append(period);
    rapportrad.append("\" datum=\"");
    rapportrad.append(datum);
    rapportrad.append("\"/>\n");    

//    qDebug("slotCreateHeader::rapportrad = \n%s",rapportrad.latin1());
    
    filnamn.open( IO_WriteOnly | IO_Append );
    stream << rapportrad;
}

void frmBalansrapport::slotFileRemove(QString filnamn)
{
//  Ta bort temporärfilen /tmp/Balansrapport.kud eller filen /tmp/Balansrapport.txt
    bool status;
    QDir d = QDir::root();                   // "/"
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }
    status=d.remove(filnamn,FALSE);
}

void frmBalansrapport::KugarVersion()
{
//  Hämta aktuell version av kugar
//  Anrop av kugar skiljer sig mellan version 1.2.1 och version 1.2.92 ->
    bool status;
    int i = -1;

    QString filename;

    system("kugar -v >/tmp/kugarversion.txt");
    filename="/tmp/kugarversion.txt";
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
   frmBalansrapport::slotFileRemove("kugarversion.txt");
}

void frmBalansrapport::GetReportDir()
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
	    reportpath=inrad.mid(7,inrad.length()-7);
	    i= -1;
	}
    }
    file.close ();
//    qDebug("reportpath=  %s",reportpath.latin1());
}

void frmBalansrapport::GetTmpDir()
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
	i = inrad.find( QRegExp("VTMP="), 0 );
	if(i == 0){
	    tmppath=inrad.mid(5,inrad.length()-5);
	    i= -1;
	}
    }
    file.close ();
//    qDebug("tmppath=%s",tmppath.latin1());
}

void frmBalansrapport::getFortetagsnamn()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	errorrad="";
	inrad="";
	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument("FNAMN");	// Företagsnamn

	frmBalansrapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
	frmBalansrapport::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
            frmBalansrapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotFtgnamnEndOfProcess() ) );


	if ( !process->start() ) {
		QMessageBox::warning( this, "BALRPTW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	}
}

void frmBalansrapport::slotFtgnamnEndOfProcess()
{
    int i,j,m;
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - BALRPTW",
		"ERROR!\n"+errorrad
		);
	errorrad="";
    }else{	
	i = -1;
	i = inrad.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    j =  inrad.find( QRegExp("2:"), 0 );
	    m=inrad.length()-j;
	    ftgnamn = inrad.mid(j+2,m-4);
	}
    }
//	qDebug("inrad=%s ",inrad.latin1());
//	qDebug("ftgnamn=%s, j=%d, m=%d, lengd=%d",ftgnamn.latin1(),j,m,inrad.length());
}

QString frmBalansrapport::CheckDatum( QString datumet )
{
    /*      Kontrollera och formatera datum enligt 20ÅÅ-MM-DD */
    int i;
    int j,k;
    QString tempdatum;
    QString millenium;
//    QString tmp;

    i = datumet.length();
    k = datumet.find( QRegExp("-"), 0 );
    j = datumet.find( QRegExp("-"), k+1 );
    millenium=datum.mid(0,2);

//    qDebug("millenium=%s, datumet=%s, datumetlängd=%d, datumet 1:a - =%d, datumet 2:a - %d",millenium.latin1(),datumet.latin1(),i,k,j);

    tempdatum=datumet;
    if (i < 7 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(0,2)+"-"+datumet.mid(2,2)+"-"+datumet.mid(4,2);
    }
    if (i == 7 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(1,2)+"-"+datumet.mid(3,2)+"-"+datumet.mid(5,2);
    }
    if (i == 8 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(2,2)+"-"+datumet.mid(4,2)+"-"+datumet.mid(6,2);
    }
    if (i == 9 && k < 0 && j < 0){
	tempdatum = millenium+datumet.mid(3,2)+"-"+datumet.mid(5,2)+"-"+datumet.mid(7,2);
    }
    if (i < 10 && k > 0 ){
	if (k > 0 && k <5){
	    if ( j < 0){
		tempdatum =datumet.mid(0,k+1)+datumet.mid(k+1,2)+"-"+datumet.mid(k+3,2);
	    }
	    if (j > 0){
		tempdatum ="20"+datumet.mid(0,k+1)+datumet.mid(k+1,2)+datumet.mid(j,3);
	    }
	}
	if (k > 4 && k <7){
	    if ( j < 0){
		tempdatum =datumet.mid(0,4)+"-"+datumet.mid(4,2)+"-"+datumet.mid(k+1,2);
	    }
	    if (j > 0){
		tempdatum =datumet.mid(0,4)+"-"+datumet.mid(4,2)+datumet.mid(j,3);
	    }
	}
    }
//    qDebug("tempdatum=%s, ",tempdatum.latin1());
        return tempdatum;
}

void frmBalansrapport::GetBokfPeriod()
{
	const char *userp = getenv("USER");
            QString usr(userp);
	errorrad="";
	inrad="";

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "VERHDSP");	// OLFIX funktion
	process->addArgument(bar);		// Bokföringsår

	frmBalansrapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotPeriodDataOnStderr() ) );
	frmBalansrapport::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotPeriodDataOnStdout() ) );
            frmBalansrapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotGetBokfPeriodEndOfProcess() ) );


	if ( !process->start() ) {
		QMessageBox::warning( this, "SDOLISW",
                            "Kan inte starta STYRMAN/VERHDSP! \n" );
	}
}

void frmBalansrapport::slotGetBokfPeriodEndOfProcess()
{
    QString mindate;
    QString maxdate;
    int i,j,m;
    i = -1;
    i = errorradPeriod.find( QRegExp("Error:"), 0 );
    if (i == 0) {
	QMessageBox::critical( this, "OLFIX - SDOLISW",
		"ERROR!\n"+errorradPeriod
		);
	errorradPeriod="";
    }else{
	i = -1;
	i = inradPeriod.find( QRegExp("OK:"), 0 );
	if (i != -1) {
	    j =  inradPeriod.find( QRegExp("01:"), 0 );
	    m=10;
	    mindate = inradPeriod.mid(j+3,m);
	    j =  inradPeriod.find( QRegExp("02:"), 0 );
	    m=10;
	    maxdate = inradPeriod.mid(j+3,m);
	}
	period=mindate+" -- "+maxdate;
    }
    fromdate=mindate;
    tomdate=maxdate;
//   qDebug("period=%s|,m=%d",period.latin1(),m);
//    qDebug("fromdate=%s, tomdate=%s",fromdate.latin1(),tomdate.latin1());
}

void frmBalansrapport::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmBalansrapport::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmBalansrapport::slotPeriodDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inradPeriod.append(line);
	inradPeriod.append("\n");
    }
}

void frmBalansrapport::slotPeriodDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorradPeriod.append(line);
	errorradPeriod.append("\n");
    }
}

void frmBalansrapport::slotRunPrinting(QString rptfile,QString rpttemplate )
{
	inrad="";
	errorrad="";

	process = new QProcess();
	process->addArgument("./PRTAPI" );		// OLFIX program
	process->addArgument(csvflag);
	process->addArgument(rptfile);
	process->addArgument(rpttemplate);
//	qDebug("csvflag=%s, rptfile=%s, rpttemplate=%s",csvflag.latin1(),rptfile.latin1(),rpttemplate.latin1());
	frmBalansrapport::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnPrtStderr() ) );
	frmBalansrapport::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfPrtProcess() ) );

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta PRTAPI!\n" );
	}
    }

void frmBalansrapport::slotDataOnPrtStderr()
{
   while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmBalansrapport::slotEndOfPrtProcess()
{
    int i;
    i = -1;
    i = inrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "OLFIXW",
		"ERROR!\n"+inrad
	);
	inrad="";
	i = -1;
     }
}

/*
void frmBalansrapport::Rubrik(QString klass1,QString klassnamn, int klass)
{
     rapportrad="<Rubrik2 level=\"2\" ";
     rapportrad.append("klass1=\"");
     rapportrad.append(klass1);
     rapportrad.append("\" klassnamn=\"");
     rapportrad.append(klassnamn);
     rapportrad.append("\"/>\n");
     stream << rapportrad;
     klassflag=klass;
}
*/
