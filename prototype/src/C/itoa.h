
/***************************************************************************
                          itoa.h  -  description
                             -------------------
    begin                : fre 15 nov
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
 ***************************************************************************/
void reverse(char s[]);

void itoa(int n,char s[])
{
//omvandla n till tecken i s
	int i,sign;
	if ((sign = n)< 0)	/* spara tecken */
		n = -n;		/* gör n positivt */
	i = 0;
	do {			/* generera siffror i omvänd ordning */
		s[i++] = n % 10 +'0';  /* hämta nästa siffra */
	}
	while ((n /= 10) > 0);	/* ta bort den */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
//	fprintf(stderr,"itoa=%s",s);
}

void reverse(char s[])
{
// vänder ordningen i sträng s
	int c,i,j;
	for (i = 0, j = strlen(s) - 1 ;i < j; i++, j-- ){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
