/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
/***************************************************************************
                          LSTTXTW  -  description
	          Lista texter i textregistret TEXTREG.
                           -------------------
                           version 0.1
    begin                 : Tis  23 nov 2005
    copyright           : (C) 2003 by Jan Pihlgren
    email                 : jan@pihlgren.se
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
#include <qfont.h>
#include <qlistview.h>
#include <qclipboard.h> 
#define MAXSTRING 5000

	QProcess* process;
	QString inrad;
	QString errorrad;
	QString hjelpfil;
	
void frmListTextReg::init()
{
//    messages->setColumnAlignment( 1, Qt::AlignRight );
    ListView1->setColumnAlignment(0,Qt::AlignLeft);
    ListView1->setColumnAlignment(1,Qt::AlignLeft);
    PushButtonSluta->setFocus();
    frmListTextReg::GetTexter();
}	
	
void frmListTextReg::GetTexter()	
{
	const char *userp = getenv("USER");
            QString usr(userp);

	
	process = new QProcess();
	process->addArgument("./STYRMAN");	// OLFIX styrprogram
	process->addArgument(usr);		// userid
	process->addArgument( "TXTLST");	// OLFIX funktion,begränsadedata
	
	frmListTextReg::connect( process, SIGNAL(readyReadStdout() ),this, SLOT(slotDataOnStdout() ) );
	frmListTextReg::connect( process, SIGNAL(readyReadStderr() ),this, SLOT(slotDataOnStderr() ) );	
	frmListTextReg::connect( process, SIGNAL(processExited() ),this, SLOT(slotEndOfProcess() ) );	    
 
	if ( !process->start() ) {
                // error handling
	    fprintf(stderr,"Problem starta STYRMAN/LSTTXTW!\n");
	    QMessageBox::warning( this, "Start av TXTLST ",
                            "Kan inte starta STYRMAN/TXTLST!\n"
                            );
        }
}
	
void frmListTextReg::slotDataOnStdout()
{
    while (process->canReadLineStdout() ) {
	QString line = process->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmListTextReg::slotEndOfProcess()
{
    QListViewItem* item;
    int i,k,m;
    int i1,i2;
    int antrad;
    
    QString antal;
    QString textnr;
    QString text;
    
    ListView1->setSorting(0,TRUE);
    
    i = -1;
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "LSTTXTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
    }
    i = inrad.find( QRegExp("OK: NR_0_"), 0 );
    if (i != -1) {
	QMessageBox::information( this, "LSTTXTW",
		"Textregistret innehåller inga poster!\n"
		);
	i = -1;
    }else{
	i = -1;
	i1 = inrad.find( QRegExp("OK: NR_"), 0 );
	i2 = inrad.find( QRegExp("_:"), 0 );
	m=i2-(i1+7);
//	qDebug("i1=%d i2=%d m=%d",i1,i2,m);
	
	antal=inrad.mid(i1+7,m);
	antrad=antal.toInt();
       
//	qDebug("antal=%s antrad=%d",antal.latin1(),antrad);
	i1=i2+2;
	for (k = 0;k < antrad;k++){
	    i2 = inrad.find( QRegExp("_:_"), i1+1 );
	    m=i2-i1;	    
	    textnr=inrad.mid(i1,m);
//	    qDebug("i1=%d i2=%d m=%d  textnr=%s",i1,i2,m,textnr.latin1());
	    i1=i2+3;
	    i2 = inrad.find( QRegExp("_:_"), i1+1 );
	    m=i2-i1;	    
	    QString tmp=inrad.mid(i1,m);
	    text=tmp.stripWhiteSpace();
//	    qDebug("i1=%d i2=%d m=%d  text=%s",i1,i2,m,text.latin1());
	    text.replace(QRegExp("\n"),"_");
//	    qDebug("textnr=%s  text=%s",textnr.latin1(),text.latin1());
	    item = new QListViewItem(ListView1,textnr,text);
	    i1=i2+3;
	}
    }  
}

void frmListTextReg::slotDataOnStderr()
{
    while (process->canReadLineStderr() ) {
	QString line = process->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }
}

void frmListTextReg::slotReloadText()
{
    ListView1->clear();
    frmListTextReg::GetTexter();
}

void frmListTextReg::PushButtonHjelp_clicked()
{
	inrad="";
	frmListTextReg::readResursFil();		// Hämta path till hjälpfilen

	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ADMIN.html";
	hjelpfil=hjelpfil+"#LISTTEXTER";		// Lägg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	process = new QProcess();
	process->addArgument( "OLFIXHLP" );	// OLFIX program
	process->addArgument(hjelpfil);

	if ( !process->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	PushButtonSluta->setFocus();

}

void frmListTextReg::readResursFil()
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
