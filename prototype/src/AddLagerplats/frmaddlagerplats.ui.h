/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
/***************************************************************************
                          ADDLPLW  -  description
                             -------------------
		     version 0.1
    begin                : Tors 30 okt 2003
    copyright            : (C) 2003 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/
/*****************************************************************
 *					                                                 *
 *   This program is free software; you can redistribute it and/or modify 	 *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or     	 *
 *   (at your option) any later version.                                   		 *
 *                                                                         				 *
 *****************************************************************/

#include <qmessagebox.h>
#include <qprocess.h>
#include <qdir.h>
#include <stdlib.h>
#include <qstring.h>
#include <qfile.h>
#include <qregexp.h>
#include <qvalidator.h>
#define MAXSTRING 5000


    QProcess* process;
    QString inrad;
    QString errorrad;

    QString artikelnr;
    QString lagerplats;
    
    QRegExp rx1( "[A-Za-z0-9ÅÄÖåäö]\\w{1,29}" );
    QRegExp rx2( "[1-9]{1}" );
    
    QRegExpValidator validator1( rx1, 0 );
    QRegExpValidator validator2( rx2, 0 );
    


void frmAddLagerplats::init()
{
    lineEditLagerplats->setValidator(&validator2);
    lineEditArtikelNr->setValidator(&validator1);
}
