/***************************************************************************
                          tempfil.h  -  description
                             -------------------
			     version 0.01
    begin                : Tors 5 dec 2002
    copyright            : (C) 2002 by Jan Pihlgren
    email                : jan@pihlgren.se
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *********************************************** ****************************/


	struct verfil_h			/* strukturmall för verifikationens huvudpost */
	{
	char posttyp[2];		// Huvudpost,Ska sättas till "H"
	char vernr[13];			// Verifikationsnummer
	char arid[3];			// Bokföringsår
	char verdatum[11];		// Verifikationsdatum,(YYYY-MM-DD)
	char regdatum[11];		// Registreringsdatum,(YYYY-MM-DD)
	char debet[13];			// Debetbelopp,(xxxxxxxxxx.xx)
	char kredit[13];		// Kreditbelopp,(xxxxxxxxxx.xx)
	char vertext[60];		// Verifikationstext
	char korrigerar[13];		// Korrigerar vernr
	char korrigerad[13];		// Korrigerad av vernr
	char userid[9];			// Användaridentitet (161 tecken)
	};

	struct verfil_d {		/* strukturmall för verifikationens radpost */

	char posttyp[2];		// Radpost. Ska sättas till "D", (Detaljrad)
	char vernr[13];			// Verifikationsnummer
	char radnr[4];			// Radnummer
	char arid[3];			// Bokföringsår
	char ktonr[5];			// Kontonummer
	char dk[2];			// D/K, Debet eller Kredit
	char belopp[13];		// Radbelopp,(xxxxxxxxxx.xx)
	char kstalle[5];		// Kostnadsställe
	char projekt[5];		// Projekt
	char subkto[5];			// Subkonto
	char definitiv[2];		// Flagga
	char struken[2];		// Flagga
	char filler[100];		// Utfyllnad   (161 tecken)
	};
