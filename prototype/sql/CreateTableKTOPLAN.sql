use olfix;
create table KTOPLAN(ARID VARCHAR(2) not null,KTONR VARCHAR(4) not null,BENAMNING VARCHAR(100),MANUELL ENUM('J','N')DEFAULT 'J',MOMSKOD VARCHAR(4),SRUNR INT(3),KSTALLE VARCHAR(4),PROJEKT VARCHAR(4),SUBKTO VARCHAR(4),KTOPLAN VARCHAR(15),IB DECIMAL(10,2),UB DECIMAL(10,2));
alter table KTOPLAN ADD PRIMARY KEY (KTONR,ARID);
load data infile "/usr/local/olfix/data/KTOPLANdata.txt" replace into table KTOPLAN Fields terminated by ',' enclosed by '"';
use olfixtst;
create table KTOPLAN(ARID VARCHAR(2) not null,KTONR VARCHAR(4) not null,BENAMNING VARCHAR(100),MANUELL ENUM('J','N')DEFAULT 'J',MOMSKOD VARCHAR(4),SRUNR INT(3),KSTALLE VARCHAR(4),PROJEKT VARCHAR(4),SUBKTO VARCHAR(4),KTOPLAN VARCHAR(15),IB DECIMAL(10,2),UB DECIMAL(10,2));
alter table KTOPLAN ADD PRIMARY KEY (KTONR,ARID);
load data infile "/usr/local/olfix/data/KTOPLANdata.txt" replace into table KTOPLAN Fields terminated by ',' enclosed by '"';




