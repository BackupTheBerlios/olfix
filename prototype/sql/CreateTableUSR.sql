use olfix;
create table USR(USERID VARCHAR(8) not null primary key,NAMN VARCHAR(30),AVD VARCHAR(10),GRUPP VARCHAR(10));
load data infile "/usr/local/olfix/data/USRdata.txt" replace into table USR Fields terminated by ',' enclosed by '"';






