use olfix;
create table BOKFAR(ARID VARCHAR(2) not null primary key,BENAMNING VARCHAR(25),ARSTART DATE ,ARSLUT DATE,ARLAST ENUM('J','N')DEFAULT 'N',SENVERDAT DATE,VERNR INT(11),KONTOPLAN VARCHAR(15),BESKATTNINGSAR VARCHAR(4));
use olfixtst;
create table BOKFAR(ARID VARCHAR(2) not null primary key,BENAMNING VARCHAR(25),ARSTART DATE ,ARSLUT DATE,ARLAST ENUM('J','N')DEFAULT 'N',SENVERDAT DATE,VERNR INT(11),KONTOPLAN VARCHAR(15),BESKATTNINGSAR VARCHAR(4));






