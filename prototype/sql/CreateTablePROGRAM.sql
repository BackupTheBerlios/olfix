use olfix;
create table PROGRAM(PRGNR VARCHAR(3) not null primary key,MENYAVD VARCHAR(20),MENYGRP VARCHAR(30), MENYTXT VARCHAR(30),PROGRAM VARCHAR(8));
load data infile "/usr/local/olfix/data/PROGRAMdata.txt" replace into table PROGRAM Fields terminated by ',' enclosed by '"';




