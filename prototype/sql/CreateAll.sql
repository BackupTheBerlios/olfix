use mysql;
CREATE DATABASE olfix;
use olfix;
create table BOKFAR(ARID VARCHAR(2) not null primary key,BENAMNING VARCHAR(25),ARSTART DATE ,ARSLUT DATE,ARLAST ENUM('J','N')DEFAULT 'N',SENVERDAT DATE,VERNR INT(11),KONTOPLAN VARCHAR(15),BESKATTNINGSAR VARCHAR(4));
use olfix;
create table FTGDATA(POSTTYP VARCHAR(5) not null PRIMARY KEY,POSTBESKR VARCHAR(60),FDATA TEXT);
use olfix;
create table KTOPLAN(ARID VARCHAR(2) not null,KTONR VARCHAR(4) not null,BENAMNING VARCHAR(100),MANUELL ENUM('J','N')DEFAULT 'J',MOMSKOD VARCHAR(4),SRUNR INT(3),KSTALLE VARCHAR(4),PROJEKT VARCHAR(4),SUBKTO VARCHAR(4),KTOPLAN VARCHAR(15),IB DECIMAL(10,2),UB DECIMAL(10,2));
alter table KTOPLAN ADD PRIMARY KEY (KTONR,ARID);
use olfix;
create table KSTALLE(ARID VARCHAR(2) not null,KSTALLE VARCHAR(4)not null ,BENAMNING VARCHAR(100));
alter table KSTALLE ADD PRIMARY KEY (ARID,KSTALLE);
use olfix;
create table LEVREG (
LEVNR VARCHAR(10) not null,
LEVORGNR VARCHAR(12),
LEVNAMN VARCHAR(30) not null,
LEVADRESS VARCHAR(30),
LEVPOSTNR VARCHAR(6),
LEVPOSTADR VARCHAR(30),
LEVLAND VARCHAR(30),
LEVTFNNR VARCHAR(15),
LEVFAXNR VARCHAR(15),
LEVTELEX VARCHAR(10),
LEVEMAIL VARCHAR(30),
LEVPOSTGIRONR VARCHAR(10),
LEVBANKGIRONR VARCHAR(10),
LEVREFERENT VARCHAR(20),
LEVREFTFN VARCHAR(15),
LEVMOMSKOD VARCHAR(1) DEFAULT '1',
LEVSKULD DECIMAL(10,2),
LEVKONTO VARCHAR(4),
LEVKUNDNR VARCHAR(30),
LEVVALUTA CHAR(3),
BETALVILKOR VARCHAR(3)
);
alter table LEVREG ADD PRIMARY KEY (LEVNR);
use olfix;
create table LEVRESK (
LEVNR VARCHAR(10) not null,
FAKTURANR VARCHAR(20) not null,
REGDATUM DATE,
FAKTDATUM DATE,
EXPIREDATUM DATE,
FAKTTEXT VARCHAR(100),
BAR VARCHAR(2),
MOMSPROCENT DECIMAL(2,2),
VALUTA CHAR(3),
VALUTAKURS DECIMAL(3,2),
VALUTABELOPP DECIMAL(10,2),
LEVKTONR VARCHAR(4),
FAKTBELOPP DECIMAL(10,2),
MOMSKTONR VARCHAR(4),
MOMSBELOPP DECIMAL(10,2),
DEBETKONTONR VARCHAR(4),
DEBETBELOPP DECIMAL(10,2),
USERID VARCHAR(8),
VERNR INT,
BETALD ENUM('J','N')DEFAULT 'N',
BETALDDATUM DATE,
OCRNR VARCHAR(20)
);
alter table LEVRESK ADD PRIMARY KEY (LEVNR,FAKTURANR);
use olfix;
create table RIGHTS(USERID VARCHAR(8) not null ,TRNSID VARCHAR(8)not null );
alter table RIGHTS ADD PRIMARY KEY(USERID,TRNSID);
use olfix;
create table TRANSID(TRNSID VARCHAR(8) not null primary key,TRNSTXT VARCHAR(60));
use olfix;
create table TRHD(TRNSNR INT not null auto_increment PRIMARY KEY,TRNSID VARCHAR(8) not null ,TID VARCHAR(20) not null ,USERID VARCHAR(8) not null,TRNSDATA VARCHAR(255));
use olfix;
create table USR(USERID VARCHAR(8) not null primary key,NAMN VARCHAR(30),AVD VARCHAR(10),GRUPP VARCHAR(10));
use olfix;
create table VALUTA(VALUTAID VARCHAR(3) not null primary key,LAND VARCHAR(15),SALJ DECIMAL(3,2),KOP DECIMAL(3,2),BETECKNING VARCHAR(15));
use olfix;
create table VERHUVUD(VERNR INT not null ,ARID VARCHAR(2) not null ,VERDATUM DATE,REGDAT DATE, DEBET DECIMAL(10,2),KREDIT DECIMAL(10,2),VERTEXT VARCHAR(60),KORRIGERAR INT,KORRIGERAD INT,USERID VARCHAR(8));
alter table VERHUVUD ADD PRIMARY KEY (VERNR,ARID);
use olfix;
create table VERRAD(VERNR INT not null ,RADNR SMALLINT not null,ARID VARCHAR(2) not null ,KTONR VARCHAR(4),BELOPP DECIMAL(10,2),DK ENUM('D','K'),KSTALLE VARCHAR(4),PROJEKT VARCHAR(4),SUBKTO VARCHAR(4),DEFINITIV ENUM('J','N')DEFAULT 'N',STRUKEN ENUM('J','N')DEFAULT 'N');
alter table VERRAD ADD PRIMARY KEY (VERNR,RADNR,ARID);
use olfix;
create table PROGRAM(PRGNR VARCHAR(3) not null primary key,MENYAVD VARCHAR(20),MENYGRP VARCHAR(30), MENYTXT VARCHAR(30),PROGRAM VARCHAR(8));
use olfix;
create table TEXTREG(TEXTNR VARCHAR(3) not null primary key,TXT TEXT);
use olfix;
create table INKREG(
INKORDNR VARCHAR(10) not null,
BESTTYP ENUM('N','D','I','L'),
ORDERDATUM DATE,
LEVNR VARCHAR(10),
LEVNAMN VARCHAR (30),
LEVADRESS VARCHAR(30),
LEVPOSTNR VARCHAR(6),
LEVPOSTADR VARCHAR(30),
LEVLAND VARCHAR(30),
LEVVALUTA VARCHAR(3),
LEVBETVILLKOR VARCHAR(3),
GODSMERKE VARCHAR(30),
BESTTEXT VARCHAR(3),
VARREF VARCHAR (30),
LEVDATUM DATE,
KUNDNR VARCHAR(30),
FTGNAMN VARCHAR(30),
FTGADR VARCHAR(30),
FTGPOSTNR VARCHAR(6),
FTGPOSTADR VARCHAR(30),
SPRAKKOD VARCHAR(3) DEFAULT 'sv',
BEKREFTKOD ENUM('H','D','E')DEFAULT 'E',
ORDERSTATUS ENUM('N','F','B','M')DEFAULT 'N',
UTSKRIFTSKOD ENUM('J','N')DEFAULT 'J'
);
alter table INKREG ADD PRIMARY KEY (INKORDNR);
