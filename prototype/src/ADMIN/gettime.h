/********************************************************/
/*		gettime.h				*/
/*		2002-12-19	Jan Pihlgren		*/
/********************************************************/

#define FORMAT_STR "%Y-%m-%d"    /* YYYY-MM-DD */
#define MAXSIZE 20

char tid[21]="";

int getTime()
{
  time_t t;
  struct tm *tm_t;
  char str[MAXSIZE +1];

  t = time(NULL);
  tm_t = localtime(&t);

//  str = malloc(MAXSIZE + 1);
  strftime(str, MAXSIZE, FORMAT_STR, tm_t);
  strcpy(tid,str);
//  free(str);
  return 0;
}
