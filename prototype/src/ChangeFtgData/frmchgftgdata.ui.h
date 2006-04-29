/****************************************************************/
/**		CHGFTGW					*/
/**		Version: 0.4.3				*/
/**		2005-12-05				*/
/**		Modifierad:  2006-04-24 			*/
/**		Jan Pihlgren	jan@pihlgren.se		*/
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

    int processnr=0;
    QProcess* process[25];
    QString inrad;
    QString errorrad;
    QString* rad;
    QString flag;
    QString ptyp;	/* posttyp */
    QString hjelpfil;


void frmChgFtgData::init()
{
    textLabel2_2->hide();
    lineEditFKNR2->hide();
    PushButtonOK->setFocus();
    slotGetFtgData("FNAMN");
}

void frmChgFtgData::PushButtonUpdate_clicked()
{
    frmChgFtgData::changeFtgData();
}

void frmChgFtgData::slotGetFtgData(QString posttyp)
{
	const char *userp = getenv("USER");
            QString usr(userp);

	process[processnr] = new QProcess();
	process[processnr] ->addArgument("./STYRMAN");	// OLFIX styrprogram
	process[processnr] ->addArgument(usr);		// userid
	process[processnr] ->addArgument( "FTGDSP");	// OLFIX funktion
	process[processnr] ->addArgument(posttyp);
	
	frmChgFtgData::connect( process[processnr] , SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgFtgData::connect( process[processnr] , SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
            frmChgFtgData::connect( process[processnr] , SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	 if ( !process[processnr] ->start() ) {
		// error handling
		QMessageBox::warning( this, "CHGFTGW",
                            "Kan inte starta STYRMAN/FTGDSP! \n" );
	    }
}


void frmChgFtgData::slotDataOnStdout()
{
    while (process[processnr] ->canReadLineStdout() ) {
	QString line = process[processnr] ->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}


void frmChgFtgData::slotDataOnStderr()
{
    while (process[processnr] ->canReadLineStderr() ) {
	QString line = process[processnr] ->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}


void frmChgFtgData::slotEndOfProcess()
{
    int h,i,j,k,m;
   QString posttyp;
//    qDebug("frmDspFtgData-inrad=%s",inrad.latin1());
    h= -1;
    h = errorrad.find( QRegExp("Error:"), 0 );
    if (h != -1) {
	QMessageBox::critical( this, "CHGFTGW",
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
    i = posttyp.find( QRegExp("TELEX"), 0 );
    if (i != -1){
	slotGetTELEX();
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
    i = posttyp.find( QRegExp("FAKNR"), 0 );
    if (i != -1){
	slotGetFAKNR();
    } 
    i = posttyp.find( QRegExp("FKNR2"), 0 );
    if (i != -1){
	slotGetFKNR2();
    } 
    i = posttyp.find( QRegExp("FKNRS"), 0 );
    if (i != -1){
	slotGetFKNRS();
    } 
    i = posttyp.find( QRegExp("INKNR"), 0 );
    if (i != -1){
	slotGetINKNR();
    } 
    i = posttyp.find( QRegExp("KORNR"), 0 );
    if (i != -1){
	slotGetKORNR();
    } 
    i = posttyp.find( QRegExp("SKUNR"), 0 );
    if (i != -1){
	slotGetSKUNR();
    } 
    i = posttyp.find( QRegExp("KFKTO"), 0 );
    if (i != -1){
	slotGetKFKTO();
    } 
    i = posttyp.find( QRegExp("INKTO"), 0 );
    if (i != -1){
	slotGetINKTO();
    } 
    i = posttyp.find( QRegExp("OFFNR"), 0 );
    if (i != -1){
	slotGetOFFNR();
    } 
    i = posttyp.find( QRegExp("BGNR"), 0 );
    if (i != -1){
	slotGetBGNR();
    } 
    i = posttyp.find( QRegExp("PGNR"), 0 );
    if (i != -1){
	slotGetPGNR();
    } 
}

void frmChgFtgData::slotGetFNAMN()
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

void frmChgFtgData::slotGetADR1()
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

void frmChgFtgData::slotGetADR2()
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

void frmChgFtgData::slotGetADR3()
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

void frmChgFtgData::slotGetADR4()
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

void frmChgFtgData::slotGetADR5()
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

void frmChgFtgData::slotGetADR6()
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

void frmChgFtgData::slotGetADR7()
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

void frmChgFtgData::slotGetADR8()
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

void frmChgFtgData::slotGetADR9()
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


void frmChgFtgData::slotGetFTGNR()
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


void frmChgFtgData::slotGetTFN1()
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
    tfnnr=tfnnr.stripWhiteSpace();
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditTfnnr->setText(tfnnr);
    
    inrad="";
    slotGetFtgData("TFN2");
}


void frmChgFtgData::slotGetTFN2()
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
    tfnnr=tfnnr.stripWhiteSpace();
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditMobilTfn->setText(tfnnr);
    
    inrad="";
    slotGetFtgData("TFAX");
}


void frmChgFtgData::slotGetTFAX()
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
    telefax=telefax.stripWhiteSpace();
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEditTelefax->setText(telefax);
    
    inrad="";
    slotGetFtgData("TELEX");
}

void frmChgFtgData::slotGetTELEX()
{
    int i,j,k,m;
   QString posttyp;
   QString adr;
   QString telex;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    telex = inrad.mid(k+2,m-2);
    telex=telex.stripWhiteSpace();
//    qDebug("tfnnr=%s",tfnnr.latin1());
    LineEdit1Telex->setText(telex);
    
    inrad="";
    slotGetFtgData("EML1");

}

void frmChgFtgData::slotGetEML1()
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
    mailadr=mailadr.stripWhiteSpace();
//    qDebug("tfnnr=%s",mailadr.latin1());
    LineEditemailadress->setText(mailadr);
    
    inrad="";
    slotGetFtgData("MOMS1");
}


void frmChgFtgData::slotGetMOMS1()
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
    moms1=moms1.stripWhiteSpace();
//    qDebug("moms1=%s",moms1.latin1());
    LineEditMoms1->setText(moms1);
    
    inrad="";
    slotGetFtgData("MOMS2");
}

void frmChgFtgData::slotGetMOMS2()
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
    moms2=moms2.stripWhiteSpace();
//    qDebug("moms2=%s",moms2.latin1());
    LineEditMoms2->setText(moms2);
    
    inrad="";
    slotGetFtgData("MOMS3");
}

void frmChgFtgData::slotGetMOMS3()
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
    moms3=moms3.stripWhiteSpace();
//    qDebug("moms3=%s",moms3.latin1());
    LineEditMoms3->setText(moms3);
    
    inrad="";
    slotGetFtgData("MOMS4");
}

void frmChgFtgData::slotGetMOMS4()
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
    moms4=moms4.stripWhiteSpace();
//    qDebug("moms4=%s",moms4.latin1());
    LineEditMoms4->setText(moms4);
    
    inrad="";
    slotGetFtgData("MOMS5");
}

void frmChgFtgData::slotGetMOMS5()
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
    moms5=moms5.stripWhiteSpace();
//    qDebug("moms5=%s",moms5.latin1());
    LineEditMoms5->setText(moms5);
    
    inrad="";
    slotGetFtgData("MOMSI");
}

void frmChgFtgData::slotGetMOMSI()
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
    momsi=momsi.stripWhiteSpace();
//    qDebug("momsi=%s",momsi.latin1());
    lineEditMomktoIng->setText(momsi);
    
    inrad="";
    slotGetFtgData("MOMSU");
}

void frmChgFtgData::slotGetMOMSU()
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
    momsu=momsu.stripWhiteSpace();
//    qDebug("momsu=%s",momsu.latin1());
    lineEditMomktoUtg->setText(momsu);   
    inrad="";
    slotGetFtgData("AUTOK");
}

void frmChgFtgData::slotGetAUTOK()
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
    autok=autok.stripWhiteSpace();
//    qDebug("autok=%s",autok.latin1());
    lineEditAutokont->setText(autok);   
    inrad="";
    slotGetFtgData("SNIKD");
}

void frmChgFtgData::slotGetSNIKD()
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
    snikd=snikd.stripWhiteSpace();
//    qDebug("autok=%s",autok.latin1());
    LineEditBranschkod->setText(snikd);   
    inrad="";
    slotGetFtgData("FKNRS");
}

void frmChgFtgData::slotGetFKNRS()
{
//	Senaste fakturanr
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString fknrs;	
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    fknrs = inrad.mid(k+2,m-2);
    fknrs=fknrs.stripWhiteSpace();
    lineEditFKNRS->setText(fknrs); 
    if (fknrs != "1"){
	textLabel2_2->show();
	lineEditFKNR2->show();
    }else{
	textLabel2_2->hide();
	lineEditFKNR2->hide();
    }
    inrad="";
    slotGetFtgData("FAKNR");
}

void frmChgFtgData::slotGetFAKNR()
{
//	Senaste fakturanr
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString faknr;	
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    faknr = inrad.mid(k+2,m-2);
    faknr=faknr.stripWhiteSpace();
    lineEditFAKNR->setText(faknr);   
    inrad="";
    slotGetFtgData("FKNR2");
}

void frmChgFtgData::slotGetFKNR2()
{
//	Senaste fakturanr
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString fknr2;	
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    fknr2 = inrad.mid(k+2,m-2);
    fknr2=fknr2.stripWhiteSpace();
    lineEditFKNR2->setText(fknr2);   
    inrad="";
    slotGetFtgData("INKNR");    
}

void frmChgFtgData::slotGetINKNR()
{
//	Senaste fakturanr
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString inknr;	
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    inknr = inrad.mid(k+2,m-2);
    inknr=inknr.stripWhiteSpace();
    lineEditINKNR->setText(inknr);   
    inrad="";
    slotGetFtgData("SKUNR");    
}

void frmChgFtgData::slotGetSKUNR()
{
//	Senaste fakturanr
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString skunr;	
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    skunr = inrad.mid(k+2,m-2);
    skunr=skunr.stripWhiteSpace();
    lineEditSKUNR->setText(skunr);   
    inrad="";
    slotGetFtgData("KORNR");    
}

void frmChgFtgData::slotGetKORNR()
{
//	Senaste fakturanr
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString kornr;	
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
    m = inrad.length();
    kornr = inrad.mid(k+2,m-2);
    kornr=kornr.stripWhiteSpace();
    lineEditKORNR->setText(kornr);   
    inrad="";
    slotGetFtgData("KFKTO");    
}

void frmChgFtgData::slotGetKFKTO()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString kfkto;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    kfkto = inrad.mid(k+2,m-2);
//    qDebug("moms5=%s",moms5.latin1());
    lineEditKtonrKundfordr->setText(kfkto);
    inrad="";
    slotGetFtgData("INKTO");
}

void frmChgFtgData::slotGetINKTO()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString inkto;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    inkto = inrad.mid(k+2,m-2);
//    qDebug("moms5=%s",moms5.latin1());
    lineEditKtonrInbet->setText(inkto);    
    inrad="";
    slotGetFtgData("OFFNR");
}

void frmChgFtgData::slotGetOFFNR()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString offnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    offnr = inrad.mid(k+2,m-2);
    lineEditOFFERTNR->setText(offnr);    
    inrad="";
    slotGetFtgData("BGNR");
}

void frmChgFtgData::slotGetBGNR()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString bgnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    bgnr = inrad.mid(k+2,m-2);
    LineEditBankgiro->setText(bgnr);    
    inrad="";
    slotGetFtgData("PGNR");
}

void frmChgFtgData::slotGetPGNR()
{
   int i,j,k,m;
   QString posttyp;
   QString adr;
   QString pgnr;
   
    i = inrad.find( QRegExp("OK:"), 0 );
    j = inrad.find(QRegExp("1:"),0);
    k = inrad.find( QRegExp("2:"), 0 );
    m = k - j;
    posttyp = inrad.mid(j+2,m-2);
//    qDebug("posttyp=%s",posttyp.latin1());   
    m = inrad.length();
    pgnr = inrad.mid(k+2,m-2);
//    qDebug("moms5=%s",moms5.latin1());
    LineEditPostgiro->setText(pgnr);    
    inrad="";
//    slotGetFtgData("PGNR");
}

void frmChgFtgData::changeFtgData()
{
    QString ftgnamn=LineEditFtgNamn->text();			// FNAMN
    if ( LineEditFtgNamn->edited() ) {
	frmChgFtgData::updateFtgData( "FNAMN", ftgnamn );
    }
    QString ftgnr=LineEditFtgNr->text();				// FTGNR
    if ( LineEditFtgNr->edited() ) {
	frmChgFtgData::updateFtgData( "FTGNR", ftgnr );
    }
    QString branchkod=LineEditBranschkod->text();		// SNIKD
    if ( LineEditBranschkod->edited() ) {
	frmChgFtgData::updateFtgData( "SNIKD", branchkod );
    }
    QString postadr=LineEditPostAdress->text();			// ADR1
    if ( LineEditPostAdress->edited() ) {
	frmChgFtgData::updateFtgData( "ADR1", postadr );
    }
    QString postnr1=LineEditPostnr1->text();			// ADR2
    if ( LineEditPostnr1->edited() ) {
	frmChgFtgData::updateFtgData( "ADR2", postnr1 );
    }
    QString postort=LineEditPostOrt->text();			// ADR3
    if ( LineEditPostOrt->edited() ) {
	frmChgFtgData::updateFtgData( "ADR3", postort );
    }
    QString besoksadr=LineEditBesoksAdress->text();		// ADR4
    if ( LineEditBesoksAdress->edited() ) {
	frmChgFtgData::updateFtgData( "ADR4", besoksadr );
    }
    QString postnr2=LineEditPostnr2->text();			// ADR5
    if ( LineEditPostnr2->edited() ) {
	frmChgFtgData::updateFtgData( "ADR5", postnr2 );
    }
    QString besoksort=LineEditBesoksOrt->text();			// ADR6
    if ( LineEditBesoksOrt->edited() ) {
	frmChgFtgData::updateFtgData( "ADR6", besoksort );
    }
    QString godsadr=LineEditGodsAdress->text();			// ADR7
    if ( LineEditGodsAdress->edited() ) {
	frmChgFtgData::updateFtgData( "ADR7", godsadr );
    }
    QString postnr3=LineEditPostnr3->text();			// ADR8
    if ( LineEditPostnr3->edited() ) {
	frmChgFtgData::updateFtgData( "ADR8", postnr3 );
    }
    QString godsort=LineEditGodsOrt->text();			// ADR9
    if ( LineEditGodsOrt->edited() ) {
	frmChgFtgData::updateFtgData( "ADR9", godsort );
    }
    QString tfnnr=LineEditTfnnr->text();				// TFN1
    tfnnr=tfnnr.stripWhiteSpace();
    if ( LineEditTfnnr->edited() ) {
	frmChgFtgData::updateFtgData( "TFN1", tfnnr );
    }
    QString mobiltfn=LineEditMobilTfn->text();			// TFNMB
    mobiltfn=mobiltfn.stripWhiteSpace();
    if ( LineEditMobilTfn->edited() ) {
	frmChgFtgData::updateFtgData( "TFNMB", mobiltfn );
    }
    QString telefax=LineEditTelefax->text();			// TFAX
    telefax=telefax.stripWhiteSpace();
    if ( LineEditTelefax->edited() ) {
	frmChgFtgData::updateFtgData( "TFAX", telefax );
    }
    QString email=LineEditemailadress->text();			// EML1
    email=email.stripWhiteSpace();
    if ( LineEditemailadress->edited() ) {
	frmChgFtgData::updateFtgData( "EML1", email );
    }
    QString telex=LineEdit1Telex->text();			// TELEX
    telex=telex.stripWhiteSpace();
    if ( LineEdit1Telex->edited() ) {
	frmChgFtgData::updateFtgData( "TELEX", telex );
    }
    QString moms1=LineEditMoms1->text();			// MOMS1
    moms1=moms1.stripWhiteSpace();
    if ( LineEditMoms1->edited() ) {
	frmChgFtgData::updateFtgData( "MOMS1", moms1 );
    }
    QString moms2=LineEditMoms2->text();			// MOMS2
    moms2=moms2.stripWhiteSpace();
    if ( LineEditMoms2->edited() ) {
	frmChgFtgData::updateFtgData( "MOMS2", moms2 );
    }
    QString moms3=LineEditMoms3->text();			// MOMS3
    moms3=moms3.stripWhiteSpace();
    if ( LineEditMoms3->edited() ) {
	frmChgFtgData::updateFtgData( "MOMS3", moms3 );
    }
    QString moms4=LineEditMoms4->text();			// MOMS4
    moms4=moms4.stripWhiteSpace();
    if ( LineEditMoms4->edited() ) {
	frmChgFtgData::updateFtgData( "MOMS4", moms4 );
    }
    QString moms5=LineEditMoms5->text();			// MOMS5
    moms5=moms5.stripWhiteSpace();
    if ( LineEditMoms5->edited() ) {
	frmChgFtgData::updateFtgData( "MOMS5", moms5 );
    }
    QString inmoms=lineEditMomktoIng->text();			// MOMSI
    inmoms=inmoms.stripWhiteSpace();
    if ( lineEditMomktoIng->edited() ) {
	frmChgFtgData::updateFtgData( "MOMSI", inmoms );
    }
    QString utmoms=lineEditMomktoUtg->text();			// MOMSU
    utmoms=utmoms.stripWhiteSpace();
    if ( lineEditMomktoUtg->edited() ) {
	frmChgFtgData::updateFtgData( "MOMSU", utmoms );
    }
    QString autokont=lineEditAutokont->text();			// AUTOK
    autokont=autokont.stripWhiteSpace();
    if ( lineEditAutokont->edited() ) {
	frmChgFtgData::updateFtgData( "AUTOK", autokont );
    }
    QString fknrs=lineEditFKNRS->text();				// FKNRS
    if ( lineEditFKNRS->edited() ) {
	fknrs=fknrs.stripWhiteSpace();
	frmChgFtgData::updateFtgData( "FKNRS", fknrs );
    }
    QString faknr=lineEditFAKNR->text();				// FAKNR
    faknr=faknr.stripWhiteSpace();
    if ( lineEditFAKNR->edited() ) {
	frmChgFtgData::updateFtgData( "FAKNR", faknr );
    }
    if (fknrs != "1"){
	QString fknr2=lineEditFKNR2->text();			// FKNR2
	fknr2=fknr2.stripWhiteSpace();
	if ( lineEditFKNR2->edited() ) {
	    frmChgFtgData::updateFtgData( "FKNR2", fknr2 );
	}
    }
    QString inknr=lineEditINKNR->text();				// INKNR
    inknr=inknr.stripWhiteSpace();
    if ( lineEditINKNR->edited() ) {
	frmChgFtgData::updateFtgData( "INKNR", inknr );
    }
    QString skunr=lineEditSKUNR->text();			// SKUNR
    skunr=skunr.stripWhiteSpace();
    if ( lineEditSKUNR->edited() ) {
	frmChgFtgData::updateFtgData( "SKUNR", skunr );
    }
    QString kornr=lineEditKORNR->text();			// KORNR
    kornr=kornr.stripWhiteSpace();
    if ( lineEditKORNR->edited() ) {
	frmChgFtgData::updateFtgData( "KORNR",kornr );
    }
    QString kfkto=lineEditKtonrKundfordr->text();			// KFKTO
    kfkto=kfkto.stripWhiteSpace();
    if ( lineEditKtonrKundfordr->edited() ) {
	frmChgFtgData::updateFtgData( "KFKTO",kfkto );
    }
    QString inbetkto=lineEditKtonrInbet->text();			// INKTO
    inbetkto=inbetkto.stripWhiteSpace();
    if ( lineEditKtonrInbet->edited() ) {
	frmChgFtgData::updateFtgData( "INKTO",inbetkto );
    }
    QString offnr=lineEditOFFERTNR->text();			// OFFNR
    offnr=offnr.stripWhiteSpace();
    if ( lineEditOFFERTNR->edited() ) {
	frmChgFtgData::updateFtgData( "OFFNR",offnr );
    }
    QString bgnr=LineEditBankgiro->text();			// OFFNR
    bgnr=bgnr.stripWhiteSpace();
    if ( LineEditBankgiro->edited() ) {
	frmChgFtgData::updateFtgData( "BGNR",bgnr );
    }
    QString pgnr=LineEditPostgiro->text();			// OFFNR
    pgnr=pgnr.stripWhiteSpace();
    if ( LineEditPostgiro->edited() ) {
	frmChgFtgData::updateFtgData( "PGNR",bgnr );
    }
    slotGetFtgData("FNAMN");					// läs in data igen, från början(FNAMN) .
    PushButtonOK->setFocus(); 
    QMessageBox::information( this, "CHGFTGW","Företagsdata uppdaterat! \n" );
}

void frmChgFtgData::updateFtgData( QString posttyp,QString data )
{
	const char *userp = getenv("USER");
	QString usr(userp);
	processnr++;
	process[processnr]  = new QProcess();
	process[processnr] ->addArgument("./STYRMAN");	// OLFIX styrprogram
	process[processnr] ->addArgument(usr);		// userid
	process[processnr] ->addArgument( "FTGUPD");		// OLFIX funktion
	process[processnr] ->addArgument(posttyp);
	process[processnr] ->addArgument(data);
	
	frmChgFtgData::connect( process[processnr] , SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmChgFtgData::connect( process[processnr] , SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );
                frmChgFtgData::connect( process[processnr] , SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );

	 if ( !process[processnr] ->start() ) {
		// error handling
		QMessageBox::warning( this, "CHGFTGW",
                            "Kan inte starta STYRMAN/FTGUPD! \n" );
	    }
}

void frmChgFtgData::pushBtnHelp_clicked()
{
    inrad="";
    frmChgFtgData::readResursFil();		// Hämta path till hjälpfilen

    int i1 = hjelpfil.find( QRegExp(".html"), 0 );
    hjelpfil=hjelpfil.left(i1);
    hjelpfil=hjelpfil+"_FTGADMIN.html";
    hjelpfil=hjelpfil+"#CHGFTGDATA";		// Lägg till position
    //	qDebug("hjelpfil=%s",hjelpfil.latin1());

    process[processnr] = new QProcess();
    process[processnr]->addArgument( "OLFIXHLP" );		// OLFIX program
    process[processnr]->addArgument(hjelpfil);

    if ( !process[processnr]->start() ) {
	// error handling
	QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
    }
    LineEditFtgNamn->setFocus();
}

void frmChgFtgData::readResursFil()
{
    /*****************************************************/
    /*  Läs in .olfixrc filen här			                     */
    /* Plocka fram var hjälpfilen finns			*/
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
	    line = stream.readLine(); 			/* line of text excluding '\n'	*/
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
