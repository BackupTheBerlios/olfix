/***************************************************************************/
/*                          unpad.h  -  description			   */
/*                             -------------------			   */
/*			     version 0.01				   */
/*    begin                : Ons 21 nov 2002				   */
/*    copyright            : (C) 2002 by Jan Pihlgren			   */
/*    email                : jan@pihlgren.se				   */
/****************************************************************************/

/***************************************************************************/
/*                                                                         */
/*   This program is free software; you can redistribute it and/or modify  */
/*   it under the terms of the GNU General Public License as published by  */
/*   the Free Software Foundation; either version 2 of the License, or     */
/*   (at your option) any later version.                                   */
/*                                                                         */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unpad( char *data)
{
	int i,j;
	char *pek;
	char tmp[500];

	pek=data;
	j=0;
	for (i=0;i<strlen(data);i++){
		if (i==0 && data[i] == 0x20)
			i++;
		if (data[i] == 0x20 && data[i+1] == 0x20){
			i++;
		}
		else{
			tmp[j]=data[i];
			j++;
		}
	}
	tmp[j]=0x00;
	if (tmp[j-1] == 0x20)
		tmp[j-1] = 0x00;
	i=j;
	for(j=0;j<i;j++){
		*(pek+j)=tmp[j];
	}
}
