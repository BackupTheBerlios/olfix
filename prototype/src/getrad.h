/********************************************************/
/*		getrad.h				*/
/*							*/
/*           Tors 7 nov 2002				*/
/*    copyright            : (C) 2002 by Jan Pihlgren	*/
/*    email                : jan@pihlgren.se		*/
/********************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *********************************************** ****************************/


#include <stdio.h>

char getrad(s, lim)
char s[]; int lim;
{
	int c=0;
	int i;

	for (i = 0; i < lim - 1 && (c = getc(stdin)) != '\n'; i++){
		if (c == EOF)
			return(c);
		else
			s[i] = c;
	}
	s[i] = 0x00;
	return(i);
}
