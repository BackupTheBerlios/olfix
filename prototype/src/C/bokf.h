/***************************************************************************
                          bokf.h  -  description
                             -------------------
    begin                : ons 6 nov 2002
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

/*	Alla fält av typ char skall göras 1 tecken längre           */
/*	än behovet för att ge plats åt det avslutande \x00-tecknet. */

typedef struct {
	char posttyp[3];	/*  2 tecken 		pos  1- 2 */
	char filler1[4];	/*  3 tecken  ";" 	pos  3- 5 */
	char vernr[11];		/* 10 tecken 		pos  6-15 */
	char filler2[4];	/*  3 tecken  ";" 	pos 16-18 */
	char userid[9];		/*  8 tecken 		pos 19-26 */
	char filler3[4];	/*  3 tecken  ";" 	pos 27-29 */
	char trnsid[9];		/*  8 tecken 		pos 30-37 */
	char filler4[4];	/*  3 tecken  ";" 	pos 38-40 */
	char belopp[13];	/* 12 tecken 		pos 41-52 */
	char filler5[4];	/*  3 tecken  ";" 	pos 53-55 */
	char datum[11];		/* 10 tecken 		pos 56-65 */
	char filler6[4];	/*  3 tecken  ";" 	pos 66-68 */
	char vertext[56];	/* 53 tecken 		pos 69-123*/
	char filler7[2];	/*  1 tecken  "   	pos 124 */
} VERHPOST;						/* 124 tecken */

typedef struct {
	char posttyp[3];	/*  2 tecken 		pos  1- 2 */
	char filler1[4];	/*  3 tecken  ";" 	pos  3- 5 */
	char vernr[11];		/* 10 tecken 		pos  6-15 */
	char filler2[4];	/*  3 tecken  ";" 	pos 16-18 */
	char userid[9];		/*  8 tecken 		pos 19-26 */
	char filler3[4];	/*  3 tecken  ";" 	pos 27-29 */
	char trnsid[9];		/*  8 tecken 		pos 30-37 */
	char filler4[4];	/*  3 tecken  ";" 	pos 38-40 */
	char belopp[13];	/* 12 tecken 		pos 41-52 */
	char filler5[4];	/*  3 tecken  ";" 	pos 53-55 */
	char radnr[7];		/*  6 tecken 		pos 56-61 */
	char filler6[4];	/*  3 tecken  ";" 	pos 62-64 */
	char kontonr[5];	/*  4 tecken 		pos 65-68 */
	char filler7[4];	/*  3 tecken  ";" 	pos 69-71 */
	char dk[2];		/*  1 tecken 		pos 72    */
	char filler8[4];	/*  3 tecken  ";" 	pos 73-75 */
	char filler9[49];	/* 48 tecken  space	pos 76-123 */
	char filler10[2];	/*  1 tecken  " 	pos 124   */
} VERDPOST;						/* 124 tecken */

extern VERHPOST *verh_pek;
extern VERDPOST *verd_pek;
