use olfix;
create table VERHUVUD(VERNR INT not null ,ARID VARCHAR(2) not null ,VERDATUM DATE,REGDAT DATE, DEBET DECIMAL(10,2),KREDIT DECIMAL(10,2),VERTEXT VARCHAR(60),KORRIGERAR INT,KORRIGERAD INT,USERID VARCHAR(8));
alter table VERHUVUD ADD PRIMARY KEY (VERNR,ARID);
use olfixtst;
create table VERHUVUD(VERNR INT not null ,ARID VARCHAR(2) not null ,VERDATUM DATE,REGDAT DATE, DEBET DECIMAL(10,2),KREDIT DECIMAL(10,2),VERTEXT VARCHAR(60),KORRIGERAR INT,KORRIGERAD INT,USERID VARCHAR(8));
alter table VERHUVUD ADD PRIMARY KEY (VERNR,ARID);




