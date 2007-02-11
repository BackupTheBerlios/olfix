use olfix;
create table RIGHTS(USERID VARCHAR(20) not null ,TRNSID VARCHAR(8)not null );
alter table RIGHTS ADD PRIMARY KEY(USERID,TRNSID);
load data infile "/opt/olfix/data/RIGHTSdata.txt" replace into table RIGHTS Fields terminated by ',' enclosed by '"';
use olfixtst;
create table RIGHTS(USERID VARCHAR(20) not null ,TRNSID VARCHAR(8)not null );
alter table RIGHTS ADD PRIMARY KEY(USERID,TRNSID);
load data infile "/opt/olfix/data/RIGHTSdata.txt" replace into table RIGHTS Fields terminated by ',' enclosed by '"';



