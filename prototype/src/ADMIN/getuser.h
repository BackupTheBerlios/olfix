/********************************************************/
/*		getuser.cpp				*/
/*		2002-12-22	Jan Pihlgren		*/
/********************************************************/
#include <stdio.h>
#include <string.h>

char user[10]="";

void getUser(char **envp)
{
	int i;
	int j,l;
	int storlek;
	char usr[10]="";

	for (i=0; envp[i] !=NULL;i++){
		if(strncmp(envp[i],"USER=",5)==0){
			storlek=strlen(envp[i]);
			strncpy(user,envp[i],storlek+1);
			l=0;
			for (j=5;j < storlek;j++){
				usr[l]=user[j];
				l++;
			}
			strcat(usr,"\0");
		}
	}
	strcpy(user,usr);
}

