/***************************************************************************
                          konto.h  -  description
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



	struct konto	 {		/* strukturmall för konto */

	char arid[3];			// Bokföringsår
	char ktonr[5];			// Kontonummer
	char benamning[101];		// Benämning på kontot
	char manuell[2];		// Flagga, J elle N
	char momskod[5];		// Momskod
	char srunr[4];			// SRUnr, 100-999, för deklaration
	char kstalle[5];		// Kostnadsställe
	char projekt[5];		// Projekt
	char subkto[5];			// Subkonto
	char ktoplan[3];		// Kontoplan
	char ib[13];			// Ingående balans (xxxxxxxxxx.xx)
	char ub[13];			// Utgående balans (xxxxxxxxxx.xx)
	};
