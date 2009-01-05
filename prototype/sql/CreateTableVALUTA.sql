use olfix;
create table VALUTA(VALUTAID VARCHAR(3) not null primary key,LAND VARCHAR(15),SALJ DECIMAL(5,2),KOP DECIMAL(5,2),BETECKNING VARCHAR(15));
load data infile "/usr/local/olfix/data/VALUTAdata.txt" replace into table VALUTA Fields terminated by ',' enclosed by '"';
use olfixtst;
create table VALUTA(VALUTAID VARCHAR(3) not null primary key,LAND VARCHAR(15),SALJ DECIMAL(5,2),KOP DECIMAL(5,2),BETECKNING VARCHAR(15));
load data infile "/usr/local/olfix/data/VALUTAdata.txt" replace into table VALUTA Fields terminated by ',' enclosed by '"';







