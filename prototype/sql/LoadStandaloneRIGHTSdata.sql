use olfix;
load data infile "/usr/local/olfix/data/temprightdata.txt" replace into table RIGHTS Fields terminated by ',' enclosed by '"';
use olfixtst;
load data infile "/usr/local/olfix/data/temprightdata.txt" replace into table RIGHTS Fields terminated by ',' enclosed by '"';



