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
                          TOTRGTW  -  description
	         Ge en anv�ndare r�ttigheter att k�ra alla program/funktioner
                             -------------------
		     version 0.1
    begin   	: 	Tis    5 dec    2006
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

QProcess* process[5];
int nbr=0;
QProcess* proc;
QString inrad;
QString errorrad;
QString val;		/* Val av funktion inne i TOTADD */
QString userid;
QString hjelpfil;
QString tmppath;		/* S�kv�g till tempor�rkatalog */
QString programrecord;	/* Post i olfixprg.tmp */
QString sqlkommando;
QString use_database="";

void frmTotalRights::init()
{
    QString tmpfile="/olfixprg.tmp";
    QString datafile="/olfixprg.dat";
    val="3";			/* Lista �ver befintliga databaser */
    frmTotalRights::createTempFile();	
    frmTotalRights::GetTmpDir();
    frmTotalRights::FileRemove(datafile);
//    frmTotalRights::FileRemove(tmpfile);
    listViewDatabas->setFocus();
}

void frmTotalRights::pickupDatabas( QListViewItem * item )
{
    char databas[30]="";
//    qDebug("PickupDatabas\n");
    if(!item){
	return;
    }
     listViewDatabas->setCurrentItem(item);
     if(!item->key(0,TRUE)){
	 return;
     }

     strcpy(databas,item->key(0,TRUE));
     use_database=databas;
     lineEditDatabas->setText((use_database));
     val="4";			/* Finns databasen? */
     frmTotalRights::createTempFile();
     lineEditDatabas->setFocus();
}

void frmTotalRights::lineEditDatabas_returnPressed()
{
    use_database=lineEditDatabas->text();
}

void frmTotalRights::lineEditUserID_returnPressed()
{
    userid=lineEditUserID->text();
    userid=userid.upper();
    lineEditUserID->setText(userid);
}

void frmTotalRights::pushBtnCreate_clicked()
{
    int status,n;
    QString inrecord;
    QString tmpfile="/olfixprg.tmp";
    QString datafile="/olfixprg.dat";
    QString olfixprgfile=tmppath+tmpfile;	/* tmppath = katalog f�r /tmp */
    QString tempfile=tmpfile;
    
    val="1";			/* val=1 skapar filenolixprg.tmp, lista �ver filer i /path/olfix/bin */
    frmTotalRights::createTempFile();	/* Lista alla program i olfix/bin med kommando ls */
    
   QFile file(olfixprgfile);
    status=file.open(IO_ReadOnly);
    QTextStream stream( &file );
    n=0;
    while ( !stream.eof() ) {
	inrecord = stream.readLine();
	if (inrecord == "TOTADD" or inrecord == "TOTRGTW" or inrecord=="ADDRGTW"){
//	    qDebug("inrecord=%s",inrecord.latin1());
	}else{
	    programrecord=inrecord;	   
	    n++;

//	qDebug("n[%d] programrecord=%s",n,programrecord.latin1());
	    frmTotalRights::createSqlData(programrecord, userid);
	}
    }
    file.close ();
    val="2";			/* val=2 uppdaterar tabellen RIGHTS */
    frmTotalRights::createTempFile();	
 }

void frmTotalRights::createTempFile()
{
//   qDebug("createTempFile::Start");
    const char *userp = getenv("USER");
    QString usr(userp);
    
    inrad="";   
    
    nbr=val.toInt();
    process[nbr] = new QProcess();
    process[nbr]->addArgument("./STYRMAN");	// OLFIX styrprogram
    process[nbr]->addArgument(usr);		// userid
    process[nbr]->addArgument( "TOTADD");	// OLFIX funktion
    process[nbr]->addArgument( val);		// funktion inne i TOTADD
    process[nbr]->addArgument(use_database);	// databas som ska uppdateras
    
//    qDebug("process[%d]",nbr);
    
    frmTotalRights::connect(process[nbr], SIGNAL(readyReadStdout() ),this, SLOT(DataOnStdout() ) );
    frmTotalRights::connect( process[nbr], SIGNAL(readyReadStderr() ),this, SLOT(DataOnStderr() ) );
    frmTotalRights::connect( process[nbr], SIGNAL(processExited() ),this, SLOT(EndOfProcess() ) );

	if ( !process[nbr]->start() ) {
                // error handling
	    QMessageBox::warning( this, "Start av TOTADD",
                            "Kan inte starta TOTADD!\n"
                            );
        }
}

void frmTotalRights::pushBtnHelp_clicked()
{
	inrad="";
	frmTotalRights::readResursFil();		// H�mta path till hj�lpfilen
	
	int i1 = hjelpfil.find( QRegExp(".html"), 0 );
//	int i2 = hjelpfil.length();
	hjelpfil=hjelpfil.left(i1);
	hjelpfil=hjelpfil+"_ADMINISTRATION.html";
	hjelpfil=hjelpfil+"#TOTAL_RIGHT";		// L�gg till position
//	qDebug("hjelpfil=%s",hjelpfil.latin1());

	proc = new QProcess();
	proc->addArgument( "./OLFIXHLP" );		// OLFIX program
	proc->addArgument(hjelpfil);

	if ( !proc->start() ) {
	    // error handling
	    QMessageBox::warning( this, "OLFIX","Kan inte starta OLFIXHLP!\n" );
	}
	lineEditUserID->setFocus();
}

void frmTotalRights::readResursFil()
{
    /*****************************************************/
    /*  L�s in .olfixrc filen h�r			                     */
    /* Plocka fram var hj�lpfilen finns			*/
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

void frmTotalRights::GetTmpDir()
{
    /*****************************************************/
    /*  L�s in .olfixrc filen h�r			               */
    /* Plocka fram var mappen tmp finns		               */
    /*****************************************************/

    QString hemkatalog;
    QString olfixrcfile;	// filen $HOME/.olfixrc

    bool status;
    int i = -1;
    //	H�mta s�kv�gen till kugar template. Default /usr/local/olfix/report
    //	H�mtas fr�n .olfixrc
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

void frmTotalRights::DataOnStdout()
{
     while (process[nbr]->canReadLineStdout() ) {
	QString line = process[nbr]->readStdout();
	inrad.append(line);
	inrad.append("\n");
    }
}

void frmTotalRights::DataOnStderr()
{
      while (process[nbr]->canReadLineStderr() ) {
	QString line = process[nbr]->readStderr();
	errorrad.append(line);
	errorrad.append("\n");
    }  
}

void frmTotalRights::EndOfProcess()
{
    QListViewItem* item;
    listViewDatabas->setSorting(0,TRUE);
    int n,j,k=0;
    int i=-1;
    QString temp1;
    QString temp2;
    QString p;
    
    i = errorrad.find( QRegExp("Error:"), 0 );
         if (i != -1) {
	QMessageBox::critical( this, "TOTRGTW",
		"ERROR!\n"+errorrad
	);
	errorrad="";
	i = -1;
	return;
     }
     i = -1;
     i = inrad.find( QRegExp("OK:"), 0 );
     if (i != -1) {
	 if (val == "2"){
	     QMessageBox::information( this, "TOTRGTW",
				       "Uppdatering genomf�rd!!\n"+inrad
				       );
	     pushBtnAvbryt->setFocus();
               }
	if (val=="3"){
	    i= -1;
	    i = inrad.find(QRegExp("NR_"),0);
	    if( i != -1){
		int m = inrad.find(QRegExp("_:_"),0);
		n=m-(i+3);
  		p=inrad.mid(i+3,n);
//		qDebug("n=%d  m=%d  p=%s",n,m,p.latin1());
		j=p.toInt();
		n=1;
		while (n <= j){
//		    n++;
		    p.setNum(n);
		    temp1="_:_"+p+"_:_";
//		    qDebug("temp1=%s",temp1.latin1());
		    p.setNum(n+1);
		    if(n != j){			
			temp2="_:_"+p+"_:_";
		    }else{
			temp2="_:_";
		    }			
//		    qDebug("temp2=%s",temp2.latin1());
		    m = inrad.find(QRegExp(temp1),0);
		    if (n == j){
			k = inrad.find(QRegExp(temp2),m+9);
//			qDebug("temp2=%s  k=%d",temp2.latin1(),k);
		    }else{
			k = inrad.find(QRegExp(temp2),0);
		    }
		    i = k - (m+temp1.length());
		    p=inrad.mid(m+temp1.length(),i);
		    if(p != "mysql"){
//			qDebug("p=%s",p.latin1());
			item = new QListViewItem(listViewDatabas,p);
		    }
		    n++;
		}
	    }
	}
    }
  //     qDebug("EndOfProcess():: inrad=%s",inrad.latin1());
}

/******************************************************************/
/*	Skapa en textfil med data f�r att kunna ladda med  sql-kommandot load */
/******************************************************************/

void frmTotalRights::createSqlData(QString function, QString usr)
{
   
    QString filnamn="/olfixprg.dat";
    filnamn=tmppath+filnamn;
    QFile file(filnamn);
    QTextStream stream(&file);

    QString record;
    QString citat="\"";
    QString komma=",";
    QString newline="\n";
    
    record=citat;
    record.append(usr);
    record.append(citat);
    record.append(komma);
    record.append(citat);
    record.append(function);
    record.append(citat);
    record.append(komma);
    record.append(newline);
  
//    qDebug("record till update=%s",record.latin1());
    
    file.open( IO_WriteOnly | IO_Append );
    stream << record;
    file.close();
 }

void frmTotalRights::FileRemove(QString filnamn)
{
//  Ta bort tempor�rfilen 
    bool status;
    QDir d = QDir::root();                   // "/    root "
    if ( !d.cd("tmp") ) {                       // "/tmp"
        qWarning( "Cannot find the \"/tmp\" directory" );
    }
//    qDebug("filnamn=%s",filnamn.latin1());
    status=d.remove(filnamn,FALSE);
}
