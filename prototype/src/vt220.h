	/* =====================================================*/
	/*	 		VT220.H				*/
	/*							*/
	/*		 Styrkommandon för en vt220-skärm.	*/
	/*							*/
	/*			94-07-17			*/
	/*			Jan Pihlgren			*/
	/*	Modifierad 94-12-10	cls()			*/
	/* -----------------------------------------------------*/
/***************************************************************************
                         VT220.h  -  description
                             -------------------
    begin                : Tis 12  nov	2002
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


void cls(void)
{
	printf("\x1B\x5B\x32\x4A");	/* Rensa skärmen. */
	printf("\x1B\x5B%d;%d\x48",1,1);/* Övre högra hörnet */
}

void bell(void)				/* Ctrl-G */
{
	printf("\x07");
}

void radera_rad(void)
{
	printf("\x1B\x5B\x4B");	/*radera till slutet av raden */
}

void locate(int row,int col)
{
	printf("\x1B\x5B%d;%d\x48",row,col);
}

void rensa_yta(int row,int AntRad) /* Från rad, antal rader */
{
	int i = 0;
	locate(row,1);
	while (i < AntRad)
		{
		radera_rad();
		printf("\n");
		i++;
		}
	locate(row,1);
}

void fel_tecken(void)
{
	bell();
	printf("\b \b");
}

void sov(int tid)
{
	int i,j;

	for(i=0;i <= tid;i++){
		for(j=0;j <= 1000;j++){
			locate(24,40);
			fprintf(stdout,"%d",j);
		};
	};
}

void wait(void)
{
	int i,j;

	for(i=0;i <= 2;i++){
		for(j=0;j <= 1000;j++){
		};
	};
}

