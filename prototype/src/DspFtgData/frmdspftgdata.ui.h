/****************************************************************/
/**		DSPFTGW					*/
/**		Version: 0.5 					*/
/**		20003-08-14					*/
/**		Modifierad: 2004-11-18				*/
/**		Jan Pihlgren	jan@pihlgren.se			*/
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
    QString* rad;
    QString flag;
    QString ptyp;	/* posttyp */

void frmDspFtgData::init()
{
    PushButtonOK->setFocus();
    slotGetFtgData("FNAMN");
}


void frmDspFtgData::slotGetFtgData(QString posttyp)
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "FTGDSP");	// OLFIX funktion
	process->addArgument(posttyp);
	
	frmDspFtgData::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmDspFtgData::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmDspFtgData::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	 if ( !process->start() ) {
		// error handling
		fprintf(stderr,"Problem starta STYRMAN/FTGDSP!\n");
		QMessageBox::warning( this, "DSPFTGW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	    }

}


void frmDspFtgData::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmDspFtgData::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmDspFtgData::slotEndOfProcess()
{
    int h,i,j,k,m;
   QString posttyp;
//    qDebug("frmDspFtgData-inrad=%s",inrad.latin1());
    h= -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
    if (h != -1) {
	QMessageBox::critical( this, "DSPFTGW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	h = -1;
     }
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);

//    qDebug("posttyp=%s",posttyp.latin1());   
    i = -1;
    i = posttyp.find( QRegExp("FNAMN"), 0 );
    if (i != -1){
	slotGetFNAMN();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR1"), 0 );
    if (i != -1){
	slotGetADR1();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR2"), 0 );
    if (i != -1){
	slotGetADR2();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR3"), 0 );
    if (i != -1){
	slotGetADR3();
    }
        i = -1;
    i = posttyp.find( QRegExp("ADR4"), 0 );
    if (i != -1){
	slotGetADR4();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR5"), 0 );
    if (i != -1){
	slotGetADR5();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR6"), 0 );
    if (i != -1){
	slotGetADR6();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR7"), 0 );
    if (i != -1){
	slotGetADR7();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR8"), 0 );
    if (i != -1){
	slotGetADR8();
    }
    i = -1;
    i = posttyp.find( QRegExp("ADR9"), 0 );
    if (i != -1){
	slotGetADR9();
    }
    i = -1;
    i = posttyp.find( QRegExp("FTGNR"), 0 );
    if (i != -1){
	slotGetFTGNR();
    }
    i = -1;
    i = posttyp.find( QRegExp("TFN1"), 0 );
    if (i != -1){
	slotGetTFN1();
    }
    i = -1;
    i = posttyp.find( QRegExp("TFN2"), 0 );
    if (i != -1){
	slotGetTFN2();
    }
    i = -1;
    i = posttyp.find( QRegExp("TFAX"), 0 );
    if (i != -1){
	slotGetTFAX();
    }
    i = -1;
    i = posttyp.find( QRegExp("EML1"), 0 );
    if (i != -1){
	slotGetEML1();
    }    
    i = -1;
    i = posttyp.find( QRegExp("MOMS1"), 0 );
    if (i != -1){
	slotGetMOMS1();
    }    
    i = -1;
    i = posttyp.find( QRegExp("MOMS2"), 0 );
    if (i != -1){
	slotGetMOMS2();
    }    
    i = -1;
    i = posttyp.find( QRegExp("MOMS3"), 0 );
    if (i != -1){
	slotGetMOMS3();
    }    
    i = -1;
    i = posttyp.find( QRegExp("MOMS4"), 0 );
    if (i != -1){
	slotGetMOMS4();
    }    
    i = -1;
    i = posttyp.find( QRegExp("MOMS5"), 0 );
    if (i != -1){
	slotGetMOMS5();
    } 
        i = -1;
    i = posttyp.find( QRegExp("MOMSI"), 0 );
    if (i != -1){
	slotGetMOMSI();
    } 
    i = -1;
    i = posttyp.find( QRegExp("MOMSU"), 0 );
    if (i != -1){
	slotGetMOMSU();
    } 
    i = -1;
    i = posttyp.find( QRegExp("AUTOK"), 0 );
    if (i != -1){
	slotGetAUTOK();
    } 
    i = posttyp.find( QRegExp("SNIKD"), 0 );
    if (i != -1){
	slotGetSNIKD();
    } 

    
}

void frmDspFtgData::slotGetFNAMN()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString fnamn;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    fnamn = inrad.mid(k+2,m-2);
//    qDebug("moms5=%s",moms5.latin1());
    LineEditFtgNamn->setText(fnamn);
    
    inrad="";
    slotGetFtgData("ADR1");
}

void frmDspFtgData::slotGetADR1()
{
    //	Postadressen
   int i,j,k,m;
   QString posttyp;
   QString postadr; 
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    postadr = inrad.mid(k+2,m-2);
    LineEditPostAdress->setText(postadr);
        
    inrad="";
    slotGetFtgData("ADR2");
}

void frmDspFtgData::slotGetADR2()
{
   //	Postnummer
   int i,j,k,m;
   QString posttyp;
   QString postnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();;
    postnr = inrad.mid(k+2,m-2);
    LineEditPostnr1->setText(postnr);
    
    inrad="";
    slotGetFtgData("ADR3");
}

void frmDspFtgData::slotGetADR3()
{
    //	Ort
   int i,j,k,m;
   QString posttyp;
   QString ort;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    ort = inrad.mid(k+2,m-2);
    LineEditPostOrt->setText(ort);
    
    inrad="";
    slotGetFtgData("ADR4");
}

void frmDspFtgData::slotGetADR4()
{
    //	Besöksadressen
   int i,j,k,m;
   QString posttyp;
   QString postadr; 
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    postadr = inrad.mid(k+2,m-2);
    LineEditBesoksAdress->setText(postadr);
        
    inrad="";
    slotGetFtgData("ADR5");
}

void frmDspFtgData::slotGetADR5()
{
   //	Postnummer
   int i,j,k,m;
   QString posttyp;
   QString postnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();;
    postnr = inrad.mid(k+2,m-2);
    LineEditPostnr2->setText(postnr);
    
    inrad="";
    slotGetFtgData("ADR6");
}

void frmDspFtgData::slotGetADR6()
{
    //	Ort
   int i,j,k,m;
   QString posttyp;
   QString ort;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    ort = inrad.mid(k+2,m-2);
    LineEditBesoksOrt->setText(ort);
    
    inrad="";
    slotGetFtgData("ADR7");
}

void frmDspFtgData::slotGetADR7()
{
    //	Godsdressen
   int i,j,k,m;
   QString posttyp;
   QString postadr; 
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    postadr = inrad.mid(k+2,m-2);
    LineEditGodsAdress->setText(postadr);
        
    inrad="";
    slotGetFtgData("ADR8");
}

void frmDspFtgData::slotGetADR8()
{
   //	Postnummer
   int i,j,k,m;
   QString posttyp;
   QString postnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();;
    postnr = inrad.mid(k+2,m-2);
    LineEditPostnr3->setText(postnr);
    
    inrad="";
    slotGetFtgData("ADR9");
}

void frmDspFtgData::slotGetADR9()
{
    //	Ort
   int i,j,k,m;
   QString posttyp;
   QString ort;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = inrad.length();
    ort = inrad.mid(k+2,m-2);
    LineEditGodsOrt->setText(ort);
    
    inrad="";
    slotGetFtgData("FTGNR");
}


void frmDspFtgData::slotGetFTGNR()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString ftgnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    ftgnr = inrad.mid(k+2,m-2);
//    qDebug("ftgnr=%s",ftgnr.latin1());
    LineEditFtgNr->setText(ftgnr);
    
    inrad="";
    slotGetFtgData("TFN1");
}


void frmDspFtgData::slotGetTFN1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString tfnnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    tfnnr = inrad.mid(k+2,m-2);
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditTfnnr->setText(tfnnr);
    
    inrad="";
    slotGetFtgData("TFN2");
}


void frmDspFtgData::slotGetTFN2()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString tfnnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    tfnnr = inrad.mid(k+2,m-2);
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditMobilTfn->setText(tfnnr);
    
    inrad="";
    slotGetFtgData("TFAX");
}


void frmDspFtgData::slotGetTFAX()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString telefax;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    telefax = inrad.mid(k+2,m-2);
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditTelefax->setText(telefax);
    
    inrad="";
    slotGetFtgData("EML1");
}


void frmDspFtgData::slotGetEML1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString mailadr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    mailadr = inrad.mid(k+2,m-2);
//    qDebug("tfnnr=%s",mailadr.latin1());
    LineEditemailadress->setText(mailadr);
    
    inrad="";
    slotGetFtgData("MOMS1");
}


void frmDspFtgData::slotGetMOMS1()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString moms1;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    moms1 = inrad.mid(k+2,m-2);
//    qDebug("moms1=%s",moms1.latin1());
    LineEditMoms1->setText(moms1);
    
    inrad="";
    slotGetFtgData("MOMS2");
}

void frmDspFtgData::slotGetMOMS2()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString moms2;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    moms2 = inrad.mid(k+2,m-2);
//    qDebug("moms2=%s",moms2.latin1());
    LineEditMoms2->setText(moms2);
    
    inrad="";
    slotGetFtgData("MOMS3");
}

void frmDspFtgData::slotGetMOMS3()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString moms3;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    moms3 = inrad.mid(k+2,m-2);
//    qDebug("moms3=%s",moms3.latin1());
    LineEditMoms3->setText(moms3);
    
    inrad="";
    slotGetFtgData("MOMS4");
}

void frmDspFtgData::slotGetMOMS4()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString moms4;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    moms4 = inrad.mid(k+2,m-2);
//    qDebug("moms4=%s",moms4.latin1());
    LineEditMoms4->setText(moms4);
    
    inrad="";
    slotGetFtgData("MOMS5");
}

void frmDspFtgData::slotGetMOMS5()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString moms5;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    moms5 = inrad.mid(k+2,m-2);
//    qDebug("moms5=%s",moms5.latin1());
    LineEditMoms5->setText(moms5);
    
    inrad="";
    slotGetFtgData("MOMSI");
}

void frmDspFtgData::slotGetMOMSI()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString momsi;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    momsi = inrad.mid(k+2,m-2);
//    qDebug("momsi=%s",momsi.latin1());
    lineEditMomktoIng->setText(momsi);
    
    inrad="";
    slotGetFtgData("MOMSU");
}

void frmDspFtgData::slotGetMOMSU()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString momsu;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    momsu = inrad.mid(k+2,m-2);
//    qDebug("momsu=%s",momsu.latin1());
    lineEditMomktoUtg->setText(momsu);   
    inrad="";
    slotGetFtgData("AUTOK");
}

void frmDspFtgData::slotGetAUTOK()
{
//	Automatkontering J/N    
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString autok;	
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    autok = inrad.mid(k+2,m-2);
//    qDebug("autok=%s",autok.latin1());
    lineEditAutokont->setText(autok);   
    inrad="";
    slotGetFtgData("SNIKD");
}

void frmDspFtgData::slotGetSNIKD()
{
//	Branschkod
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString snikd;	
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    snikd = inrad.mid(k+2,m-2);
//    qDebug("autok=%s",autok.latin1());
    LineEditBranschkod->setText(snikd);   
    inrad="";
 //   slotGetFtgData("SNIKD");
}
