-- MySQL dump 9.07
--
-- Host: localhost    Database: olfix
---------------------------------------------------------
-- Server version	4.0.11a-gamma

--
-- Current Database: olfix
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ olfix;

USE olfix;

--
-- Table structure for table 'ARTIKELREG'
--

DROP TABLE IF EXISTS ARTIKELREG;
CREATE TABLE ARTIKELREG (
  ARTIKELNR varchar(30) NOT NULL default '',
  ARBENEMNING1 varchar(30) NOT NULL default '',
  ARBENEMNING2 varchar(30) default NULL,
  ARENHET varchar(5) default NULL,
  ARFPRIS decimal(10,2) default NULL,
  ARLEDTID char(3) default NULL,
  ARPRODKLASS varchar(5) default NULL,
  ARPRODKTO varchar(5) default NULL,
  ARLEVNR1 varchar(10) default NULL,
  ARLEVNR2 varchar(10) default NULL,
  ARLEVNR3 varchar(10) default NULL,
  ARNETTOVIKT decimal(10,2) default NULL,
  ARARTTYP enum('0','1','2','3','4') default '0',
  ARSTRUKT enum('','B','I','T','F') default '',
  ARURBENEMNING varchar(30) default NULL,
  ARURLAND varchar(30) default NULL,
  ARURARTNR varchar(30) default NULL,
  ARTULLTAX varchar(10) default NULL,
  ARVOLYM decimal(4,3) default NULL,
  AROMRFAKTOR int(11) NOT NULL default '1',
  PRIMARY KEY  (ARTIKELNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'ARTIKELREG'
--


--
-- Table structure for table 'BETVILKOR'
--

DROP TABLE IF EXISTS BETVILKOR;
CREATE TABLE BETVILKOR (
  BETVILKOR char(3) NOT NULL default '',
  DAGAR char(3) default NULL,
  BESKRIVNING varchar(40) NOT NULL default '',
  PRIMARY KEY  (BETVILKOR)
) TYPE=MyISAM;

--
-- Dumping data for table 'BETVILKOR'
--

INSERT INTO BETVILKOR VALUES ('1','30','30 dagar netto');
INSERT INTO BETVILKOR VALUES ('2','20','20 dagar netto');
INSERT INTO BETVILKOR VALUES ('3','10','10 dagar netto');
INSERT INTO BETVILKOR VALUES ('4','0','Kontantköp');
INSERT INTO BETVILKOR VALUES ('5','15','Postförskott');

--
-- Table structure for table 'BOKFAR'
--

DROP TABLE IF EXISTS BOKFAR;
CREATE TABLE BOKFAR (
  ARID char(2) NOT NULL default '',
  BENAMNING varchar(25) default NULL,
  ARSTART date default NULL,
  ARSLUT date default NULL,
  ARLAST enum('J','N') default 'N',
  SENVERDAT date default NULL,
  VERNR int(11) default NULL,
  KONTOPLAN varchar(15) default NULL,
  BESKATTNINGSAR varchar(4) default NULL,
  PRIMARY KEY  (ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'BOKFAR'
--

INSERT INTO BOKFAR VALUES ('XX','2003-01-01--2003-12-31','2003-01-01','2003-12-31','N','2003-09-11',26,'EUBAS97','2003');

--
-- Table structure for table 'DATABAS'
--

DROP TABLE IF EXISTS DATABAS;
CREATE TABLE DATABAS (
  DATABASNR char(3) NOT NULL default '',
  DATABASTEXT varchar(15) NOT NULL default '',
  PRIMARY KEY  (DATABASNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'DATABAS'
--

INSERT INTO DATABAS VALUES ('01','olfix');
INSERT INTO DATABAS VALUES ('99','olfixtst');

--
-- Table structure for table 'FTGDATA'
--

DROP TABLE IF EXISTS FTGDATA;
CREATE TABLE FTGDATA (
  POSTTYP varchar(5) NOT NULL default '',
  POSTBESKR varchar(60) default NULL,
  FDATA text,
  PRIMARY KEY  (POSTTYP)
) TYPE=MyISAM;

--
-- Dumping data for table 'FTGDATA'
--

INSERT INTO FTGDATA VALUES ('FNAMN','Företagsnamn','PROGRAM AB');
INSERT INTO FTGDATA VALUES ('FTGNR','Företagsnummer','991199-1991');
INSERT INTO FTGDATA VALUES ('ADR1','Postadress','Box 70');
INSERT INTO FTGDATA VALUES ('ADR2','Postnummer till Postadress','199 98');
INSERT INTO FTGDATA VALUES ('ADR3','Ort till Postadress','PROGSTAD');
INSERT INTO FTGDATA VALUES ('ADR4','Besöksadress','Syntaxvägen 99');
INSERT INTO FTGDATA VALUES ('ADR5','Postnr till Besöksadress','199 98');
INSERT INTO FTGDATA VALUES ('ADR6','Ort till Besöksadress','PROGSTAD');
INSERT INTO FTGDATA VALUES ('ADR7','Godsadress','Verktygsgatan 11');
INSERT INTO FTGDATA VALUES ('ADR8','Postnr till Godsadress','199 97');
INSERT INTO FTGDATA VALUES ('ADR9','Ort till Godsadress','PROGSTAD');
INSERT INTO FTGDATA VALUES ('TFNVX','Telefonnummer till vx','09-199300');
INSERT INTO FTGDATA VALUES ('TFN1','Telefonnummer','09-199300');
INSERT INTO FTGDATA VALUES ('TFN2','Mobiltelefonnummer','070-98765411');
INSERT INTO FTGDATA VALUES ('TFNMB','Mobiltelefonnummer','070-98765411');
INSERT INTO FTGDATA VALUES ('TFAX','Telefaxnummer','09-199397');
INSERT INTO FTGDATA VALUES ('TELEX','Telexnummer','12345');
INSERT INTO FTGDATA VALUES ('EML1','E-mailadress','pelle@program.se');
INSERT INTO FTGDATA VALUES ('MOMSI','Momskonto, ingående moms','2641');
INSERT INTO FTGDATA VALUES ('MOMSU','Momskonto, utgående moms','2611');
INSERT INTO FTGDATA VALUES ('MOMS1','Momssats 1','25');
INSERT INTO FTGDATA VALUES ('MOMS2','Momssats 2','12');
INSERT INTO FTGDATA VALUES ('MOMS3','Momssats 3','6');
INSERT INTO FTGDATA VALUES ('MOMS4','Momssats 4',' ');
INSERT INTO FTGDATA VALUES ('MOMS5','Momssats 5',' ');
INSERT INTO FTGDATA VALUES ('AUTOK','Automatkontering J/N','N');
INSERT INTO FTGDATA VALUES ('KORNR','Senast använda kundordernr','0');
INSERT INTO FTGDATA VALUES ('BF1','Bokföringsperiod 1','Januari');
INSERT INTO FTGDATA VALUES ('BF2','Bokföringsperiod 2','Februari');
INSERT INTO FTGDATA VALUES ('BF3','Bokföringsperiod 3','Mars');
INSERT INTO FTGDATA VALUES ('BF4','Bokföringsperiod 4','April');
INSERT INTO FTGDATA VALUES ('BF5','Bokföringsperiod 5','Maj');
INSERT INTO FTGDATA VALUES ('BF6','Bokföringsperiod 6','Juni');
INSERT INTO FTGDATA VALUES ('BF7','Bokföringsperiod 7','Juli');
INSERT INTO FTGDATA VALUES ('BF8','Bokföringsperiod 8','Augusti');
INSERT INTO FTGDATA VALUES ('BF9','Bokföringsperiod 9','September');
INSERT INTO FTGDATA VALUES ('BF10','Bokföringsperiod 10','Oktober');
INSERT INTO FTGDATA VALUES ('BF11','Bokföringsperiod 11','Novemper');
INSERT INTO FTGDATA VALUES ('BF12','Bokföringsperiod 12','December');
INSERT INTO FTGDATA VALUES ('BF13','Bokföringsperiod 13','Januari');
INSERT INTO FTGDATA VALUES ('INKNR','Senast använda inköpsordernr','28');
INSERT INTO FTGDATA VALUES ('SNIKD','Branschtillhörighet','82301');
INSERT INTO FTGDATA VALUES ('WKUNR','Senaste använda webbkundnummer','4379');
INSERT INTO FTGDATA VALUES ('FAKNR','Senaste fakturanr på kundorder','0');
INSERT INTO FTGDATA VALUES ('FKNR2','Senaste fakturanr på kundorder,serie 2','0');
INSERT INTO FTGDATA VALUES ('FKNRS','Antal fakturanrserier, default = 1','0');
--
-- Table structure for table 'INKRADREG'
--

DROP TABLE IF EXISTS INKRADREG;
CREATE TABLE INKRADREG (
  INKORDNR varchar(10) NOT NULL default '',
  INKORDRADNR int(4) NOT NULL default '0',
  ARTIKELNR varchar(30) default NULL,
  BENEMNING varchar(30) default NULL,
  LEVARTIKELNR varchar(30) default NULL,
  LEVBENEMNING varchar(30) default NULL,
  ENHET varchar(5) default NULL,
  BESTANTAL decimal(10,2) default NULL,
  LEVERERAT decimal(10,2) default NULL,
  RESTNOTERAT decimal(10,2) default NULL,
  INKPRIS decimal(10,2) default NULL,
  LEVVECKA varchar(5) default NULL,
  TORDNR int(6) default NULL,
  OPNR int(6) default NULL,
  PRIMARY KEY  (INKORDNR,INKORDRADNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'INKRADREG'
--


--
-- Table structure for table 'INKREG'
--

DROP TABLE IF EXISTS INKREG;
CREATE TABLE INKREG (
  INKORDNR varchar(10) NOT NULL default '',
  BESTTYP enum('N','D','I','L','A') default NULL,
  ORDERDATUM date default NULL,
  LEVNR varchar(10) default NULL,
  LEVNAMN varchar(30) default NULL,
  LEVADRESS varchar(30) default NULL,
  LEVPOSTNR varchar(6) default NULL,
  LEVPOSTADR varchar(30) default NULL,
  LEVLAND varchar(30) default NULL,
  LEVVALUTA char(3) default NULL,
  LEVBETVILLKOR varchar(50) default NULL,
  LEVVILLKOR varchar(150) default NULL,
  LEVSETT varchar(150) default NULL,
  GODSMERKE varchar(30) default NULL,
  KOMMENTAR varchar(250) default NULL,
  BESTTEXT text,
  VARREF varchar(30) default NULL,
  VARREFTFN varchar(15) default NULL,
  VARREFFAX varchar(15) default NULL,
  ERREF varchar(20) default NULL,
  LEVDATUM date default NULL,
  KUNDNR varchar(30) default NULL,
  FTGNAMN varchar(30) default NULL,
  FTGADR varchar(30) default NULL,
  FTGPOSTNR varchar(6) default NULL,
  FTGPOSTADR varchar(30) default NULL,
  SPRAKKOD char(3) default 'sv',
  BEKREFTKOD enum('H','D','E') default 'E',
  ORDERSTATUS enum('N','F','B','M') default 'N',
  UTSKRIFTSKOD enum('J','N') default 'J',
  ORDERSUMMA decimal(10,2) default NULL,
  PRIMARY KEY  (INKORDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'INKREG'
--


--
-- Table structure for table 'KSTALLE'
--

DROP TABLE IF EXISTS KSTALLE;
CREATE TABLE KSTALLE (
  ARID char(2) NOT NULL default '',
  KSTALLE varchar(4) NOT NULL default '',
  BENAMNING varchar(100) default NULL,
  PRIMARY KEY  (ARID,KSTALLE)
) TYPE=MyISAM;

--
-- Dumping data for table 'KSTALLE'
--


--
-- Table structure for table 'KTOPLAN'
--

DROP TABLE IF EXISTS KTOPLAN;
CREATE TABLE KTOPLAN (
  ARID char(2) NOT NULL default '',
  KTONR varchar(4) NOT NULL default '',
  BENAMNING varchar(100) default NULL,
  MANUELL enum('J','N') default 'J',
  MOMSKOD varchar(4) default NULL,
  SRUNR int(3) default NULL,
  KSTALLE varchar(4) default NULL,
  PROJEKT varchar(4) default NULL,
  SUBKTO varchar(4) default NULL,
  KTOPLAN varchar(15) default NULL,
  IB decimal(10,2) default NULL,
  UB decimal(10,2) default NULL,
  PRIMARY KEY  (KTONR,ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'KTOPLAN'
--


--
-- Table structure for table 'KUNDKATEGORI'
--

DROP TABLE IF EXISTS KUNDKATEGORI;
CREATE TABLE KUNDKATEGORI (
  KATEGORINR char(3) NOT NULL default '',
  BESKRIVNING varchar(40) NOT NULL default '',
  PRIMARY KEY  (KATEGORINR)
) TYPE=MyISAM;

--
-- Dumping data for table 'KUNDKATEGORI'
--


--
-- Table structure for table 'KUNDREG'
--

DROP TABLE IF EXISTS KUNDREG;
CREATE TABLE KUNDREG (
  KUNDNR varchar(10) NOT NULL default '',
  KUNDORGNR varchar(12) default NULL,
  NAMN varchar(60) NOT NULL default '',
  ADRESS varchar(30) default NULL,
  POSTNR varchar(6) default NULL,
  POSTADR varchar(30) default NULL,
  LAND varchar(30) default NULL,
  TFNNR varchar(15) default NULL,
  EMAILADR varchar(30) default NULL,
  FAXNR varchar(15) default NULL,
  ERREFERENT varchar(30) default NULL,
  ERREFTFNNR varchar(15) default NULL,
  ERREFEMAIL varchar(60) default NULL,
  SELJARE varchar(20) default NULL,
  FRITEXT varchar(100) default NULL,
  VALUTA char(3) default NULL,
  BETALVILLKOR char(3) default NULL,
  LEVVILLKOR char(3) default NULL,
  LEVSETT char(3) default NULL,
  DISTRIKT char(3) default NULL,
  KUNDKATEGORI char(3) default NULL,
  STDLEVPLATS char(3) default '001',
  ORDERERKENNANDE enum('J','N') default 'J',
  PLOCKLISTA enum('J','N') default 'J',
  FOLJESEDEL enum('J','N') default 'J',
  KRAVBREV enum('J','N') default 'J',
  SPRAKKOD char(3) default NULL,
  EXPAVGIFT enum('J','N') default 'J',
  FRAKTAVG enum('J','N') default 'J',
  KREDITLIMIT decimal(10,2) default NULL,
  KREDITDAGAR int(11) default NULL,
  KREDITKOD char(3) default NULL,
  EXPORTKOD char(3) default NULL,
  SKATTEKOD char(3) default NULL,
  RABATTKOD char(3) default NULL,
  DROJMALSRTA enum('J','N') default 'J',
  DROJMALSFAKTURA enum('J','N') default 'J',
  SAMLINGSFAKT enum('J','N') default 'J',
  SENASTEKRAVDATUM date default NULL,
  SKULD decimal(10,2) default NULL,
  ORDERSTOCK decimal(10,2) default NULL,
  PRIMARY KEY  (KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'KUNDREG'
--


--
-- Table structure for table 'LAGERSTELLEREG'
--

DROP TABLE IF EXISTS LAGERSTELLEREG;
CREATE TABLE LAGERSTELLEREG (
  ARLAGST char(1) NOT NULL default '',
  ARTIKELNR varchar(30) NOT NULL default '',
  ARLAGHYLLA varchar(10) default NULL,
  ARLAGSALDO decimal(10,2) default NULL,
  ARINVGRP char(3) default NULL,
  ARABC char(2) default NULL,
  ARVALUTA char(3) default NULL,
  ARIPRIS decimal(10,2) default '0.00',
  ARIKVANT0 decimal(10,2) default '0.00',
  ARIKVANT1 decimal(10,2) default '0.00',
  ARIKVANT2 decimal(10,2) default '0.00',
  ARKALKPRIS decimal(10,2) default '0.00',
  ARPLANKPRIS decimal(10,2) default '0.00',
  ARFRYSTKPRIS decimal(10,2) default '0.00',
  ARBESTKVANT decimal(10,2) default '0.00',
  ARBESTPUNKT decimal(10,2) default '0.00',
  AROMKOST decimal(10,2) default '0.00',
  RESERVERAT decimal(10,2) default NULL,
  PRIMARY KEY  (ARTIKELNR,ARLAGST)
) TYPE=MyISAM;

--
-- Dumping data for table 'LAGERSTELLEREG'
--


--
-- Table structure for table 'LEVREG'
--

DROP TABLE IF EXISTS LEVREG;
CREATE TABLE LEVREG (
  LEVNR varchar(10) NOT NULL default '',
  LEVORGNR varchar(12) default NULL,
  LEVNAMN varchar(30) NOT NULL default '',
  LEVADRESS varchar(30) default NULL,
  LEVPOSTNR varchar(6) default NULL,
  LEVPOSTADR varchar(30) default NULL,
  LEVLAND varchar(30) default NULL,
  LEVTFNNR varchar(15) default NULL,
  LEVFAXNR varchar(15) default NULL,
  LEVTELEX varchar(10) default NULL,
  LEVEMAIL varchar(30) default NULL,
  LEVPOSTGIRONR varchar(10) default NULL,
  LEVBANKGIRONR varchar(10) default NULL,
  LEVREFERENT varchar(20) default NULL,
  LEVREFTFN varchar(15) default NULL,
  LEVMOMSKOD char(1) default '1',
  LEVSKULD decimal(10,2) default NULL,
  LEVKONTO varchar(4) default NULL,
  LEVKUNDNR varchar(30) default NULL,
  LEVVALUTA char(3) default NULL,
  BETALVILKOR char(3) default NULL,
  PRIMARY KEY  (LEVNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVREG'
--


--
-- Table structure for table 'LEVRESK'
--

DROP TABLE IF EXISTS LEVRESK;
CREATE TABLE LEVRESK (
  LEVNR varchar(10) NOT NULL default '',
  FAKTURANR varchar(20) NOT NULL default '',
  REGDATUM date default NULL,
  FAKTDATUM date default NULL,
  EXPIREDATUM date default NULL,
  FAKTTEXT varchar(100) default NULL,
  BAR char(2) default NULL,
  MOMSPROCENT decimal(3,2) default NULL,
  VALUTA char(3) default NULL,
  VALUTAKURS decimal(3,2) default NULL,
  VALUTABELOPP decimal(10,2) default NULL,
  LEVKTONR varchar(4) default NULL,
  FAKTBELOPP decimal(10,2) default NULL,
  MOMSKTONR varchar(4) default NULL,
  MOMSBELOPP decimal(10,2) default NULL,
  DEBETKONTONR varchar(4) default NULL,
  DEBETBELOPP decimal(10,2) default NULL,
  USERID varchar(8) default NULL,
  VERNR int(11) default NULL,
  BETALD enum('J','N') default 'N',
  BETALDDATUM date default NULL,
  OCRNR varchar(20) default NULL,
  PRIMARY KEY  (LEVNR,FAKTURANR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVRESK'
--


--
-- Table structure for table 'LEVSETT'
--

DROP TABLE IF EXISTS LEVSETT;
CREATE TABLE LEVSETT (
  LEVSETTNR char(3) NOT NULL default '',
  LEVSETTTEXT varchar(150) NOT NULL default '',
  PRIMARY KEY  (LEVSETTNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVSETT'
--


--
-- Table structure for table 'LEVVILLKOR'
--

DROP TABLE IF EXISTS LEVVILLKOR;
CREATE TABLE LEVVILLKOR (
  VILLKORSNR char(3) NOT NULL default '',
  VILLKORSTEXT varchar(150) NOT NULL default '',
  PRIMARY KEY  (VILLKORSNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVVILLKOR'
--


--
-- Table structure for table 'ORDERRADREG'
--

DROP TABLE IF EXISTS ORDERRADREG;
CREATE TABLE ORDERRADREG (
  ORDERNR varchar(10) NOT NULL default '',
  ORDERRAD int(4) NOT NULL default '0',
  KUNDNR varchar(10) NOT NULL default '',
  RADORDERTYP enum('N','D') default 'N',
  ARTIKELNR varchar(30) NOT NULL default '',
  BENEMNING varchar(60) default NULL,
  LEVERANSVECKA varchar(5) default NULL,
  BESTELLT decimal(10,2) NOT NULL default '0.00',
  APRIS decimal(10,2) NOT NULL default '0.00',
  SUMMA decimal(10,2) NOT NULL default '0.00',
  MOMSKR decimal(10,2) NOT NULL default '0.00',
  LEVERERAT decimal(10,2) default NULL,
  RESTNOTERAT decimal(10,2) default NULL,
  RADRABATT decimal(2,1) default NULL,
  KALKYLPRIS decimal(10,2) default NULL,
  LEVDATUM date default NULL,
  ENHET varchar(4) default 'ST',
  PRIMARY KEY  (ORDERNR,ORDERRAD)
) TYPE=MyISAM;

--
-- Dumping data for table 'ORDERRADREG'
--


--
-- Table structure for table 'ORDERREG'
--

DROP TABLE IF EXISTS ORDERREG;
CREATE TABLE ORDERREG (
  ORDERNR varchar(10) NOT NULL default '',
  KUNDNR varchar(10) NOT NULL default '',
  ORDERTYP enum('N','D','E','F') default 'N',
  ORDERSTATUS enum('A','N','F','B') default 'A',
  ORDERDATUM date default NULL,
  LEVDATUM date default NULL,
  KUNDNAMN varchar(60) default NULL,
  KUNDADRESS varchar(30) default NULL,
  KUNDPOSTNR varchar(6) default NULL,
  KUNDPOSTADR varchar(30) default NULL,
  KUNDLAND varchar(30) default NULL,
  ERREF varchar(20) default NULL,
  LEVADRESS varchar(30) default NULL,
  LEVPOSTNR varchar(6) default NULL,
  LEVPOSTADR varchar(30) default NULL,
  LEVLAND varchar(30) default NULL,
  VARREF varchar(20) default NULL,
  SELJARE varchar(20) default NULL,
  GODSMERKE varchar(100) default NULL,
  BETVILLKTYP enum('F','P','K') NOT NULL default 'F',
  BETVILLKOR char(3) default '001',
  LEVVILLKOR char(3) default '001',
  LEVSETT char(3) default '001',
  PLOCKLISTA enum('J','N') default 'J',
  FOLJESEDEL enum('J','N') default 'J',
  FRAKTAVG enum('J','N') default 'J',
  SKATTEKOD char(3) NOT NULL default '001',
  MOMS decimal(3,2) default NULL,
  VALUTA char(3) default 'SEK',
  EXPORTKOD char(3) default '001',
  SPRAKKOD char(3) default 'sv',
  ORDERSUMMA decimal(10,2) default NULL,
  FRAKTSUMMA decimal(10,2) default NULL,
  FRAKTMOMSKR decimal(10,2) default NULL,
  ORDERMOMS decimal(10,2) default NULL,
  ORDERTOTAL decimal(10,2) default NULL,
  PRIMARY KEY  (ORDERNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'ORDERREG'
--


--
-- Table structure for table 'PASSW'
--

DROP TABLE IF EXISTS PASSW;
CREATE TABLE PASSW (
  KUNDNR varchar(10) NOT NULL default '',
  PASSW varchar(16) NOT NULL default '',
  PRIMARY KEY  (KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'PASSW'
--


--
-- Table structure for table 'PLOCKLISTEREG'
--

DROP TABLE IF EXISTS PLOCKLISTEREG;
CREATE TABLE PLOCKLISTEREG (
  PLOCKNR int(11) NOT NULL auto_increment,
  ORDERNR varchar(10) NOT NULL default '',
  ORDERRAD int(4) NOT NULL default '0',
  KUNDNR varchar(10) NOT NULL default '',
  ARTIKELNR varchar(30) NOT NULL default '',
  BENEMNING varchar(60) default NULL,
  LEVERANSVECKA varchar(5) default NULL,
  BESTELLT decimal(10,2) NOT NULL default '0.00',
  ATTLEVERERA decimal(10,2) NOT NULL default '0.00',
  LEVERERAT decimal(10,2) NOT NULL default '0.00',
  PLOCKAT decimal(10,2) NOT NULL default '0.00',
  RESTNOTERAT decimal(10,2) NOT NULL default '0.00',
  LEVDATUM date default NULL,
  ENHET varchar(4) default NULL,
  PLOCKSTATUS enum('P','U','B') default 'P',
  PLOCKDATUM date NOT NULL default '0000-00-00',
  PRIMARY KEY  (PLOCKNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'PLOCKLISTEREG'
--


--
-- Table structure for table 'PRODUKTGRUPP'
--

DROP TABLE IF EXISTS PRODUKTGRUPP;
CREATE TABLE PRODUKTGRUPP (
  PRODKLASS varchar(5) NOT NULL default '',
  BESKRIVNING varchar(30) default NULL,
  MOMSKOD varchar(5) default NULL,
  PRIMARY KEY  (PRODKLASS)
) TYPE=MyISAM;

--
-- Dumping data for table 'PRODUKTGRUPP'
--


--
-- Table structure for table 'PROGRAM'
--

DROP TABLE IF EXISTS PROGRAM;
CREATE TABLE PROGRAM (
  PRGNR char(3) NOT NULL default '',
  MENYAVD varchar(20) default NULL,
  MENYGRP varchar(30) default NULL,
  MENYTXT varchar(30) default NULL,
  PROGRAM varchar(8) default NULL,
  PRIMARY KEY  (PRGNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'PROGRAM'
--

INSERT INTO PROGRAM VALUES ('026','Ekonomi','Valutaadministration','Ändra valuta','CHGVALW');
INSERT INTO PROGRAM VALUES ('025','Ekonomi','Valutaadministration','Ny valuta','ADDVALW');
INSERT INTO PROGRAM VALUES ('024','Ekonomi','Kostnadställeadministration','Lista kostnadsställen','LSTKSTW');
INSERT INTO PROGRAM VALUES ('023','Ekonomi','Kostnadställeadministration','Visa ett kostnadsställe','DSPKSTW');
INSERT INTO PROGRAM VALUES ('022','Ekonomi','Kostnadställeadministration','Ta bort kostnadställe','');
INSERT INTO PROGRAM VALUES ('021','Ekonomi','Kostnadställeadministration','Ändra kostnadställe','');
INSERT INTO PROGRAM VALUES ('020','Ekonomi','Kostnadställeadministration','Nytt kostnadställe','ADDKSTW');
INSERT INTO PROGRAM VALUES ('019','Ekonomi','Kontoadministration','Lista konton','LSTKTOW');
INSERT INTO PROGRAM VALUES ('018','Ekonomi','Kontoadministration','Visa konto','DSPKTOW');
INSERT INTO PROGRAM VALUES ('017','Ekonomi','Kontoadministration','Ta bort konto','');
INSERT INTO PROGRAM VALUES ('016','Ekonomi','Kontoadministration','Ändra konto','CHGKTOW');
INSERT INTO PROGRAM VALUES ('015','Ekonomi','Kontoadministration','Nytt konto','ADDKTOW');
INSERT INTO PROGRAM VALUES ('013','Ekonomi','Bokföring','Registrera verifikation','');
INSERT INTO PROGRAM VALUES ('012','Administration','Funktionsadministration','Lista funktioner','LSTFNCW');
INSERT INTO PROGRAM VALUES ('011','Administration','Funktionsadministration','Ny funktion','ADDFNCW');
INSERT INTO PROGRAM VALUES ('010','Administration','Behörighetsadministration','Lista behörigheter','LSTRGTW');
INSERT INTO PROGRAM VALUES ('009','Administration','Behörighetsadministration','Visa behörighet','');
INSERT INTO PROGRAM VALUES ('007','Administration','Behörighetsadministration','Ändra behörighet','');
INSERT INTO PROGRAM VALUES ('006','Administration','Behörighetsadministration','Ny behörighet','ADDRGTW');
INSERT INTO PROGRAM VALUES ('003','Administration','Användaradministration','Ta bort användare','DELUSRW');
INSERT INTO PROGRAM VALUES ('005','Administration','Användaradministration','Lista användare','LSTUSRW');
INSERT INTO PROGRAM VALUES ('002','Administration','Användaradministration','Ändra användarinfo','CHGUSRW');
INSERT INTO PROGRAM VALUES ('014','Ekonomi','Bokföring','Registrera ver. standard','BOKFORSW');
INSERT INTO PROGRAM VALUES ('008','Administration','Behörighetsadministration','Ta bort behörighet','DELRGTW');
INSERT INTO PROGRAM VALUES ('004','Administration','Användaradministration','Visa en användare','DSPUSRW');
INSERT INTO PROGRAM VALUES ('001','Administration','Användaradministration','Ny användare','ADDUSRW');
INSERT INTO PROGRAM VALUES ('027','Ekonomi','Valutaadministration','Ta bort valuta','DELVALW');
INSERT INTO PROGRAM VALUES ('028','Ekonomi','Valutaadministration','Visa valuta','DSPVALW');
INSERT INTO PROGRAM VALUES ('029','Ekonomi','Valutaadministration','Lista valutor','LSTVALW');
INSERT INTO PROGRAM VALUES ('030','Ekonomi','Rapporter','Kontorapport','RPTKTOW');
INSERT INTO PROGRAM VALUES ('031','Ekonomi','Rapporter','Rapportgenerator','RPTGENW');
INSERT INTO PROGRAM VALUES ('032','Ekonomi','Räkenskapsår','Nytt bokföringsår','ADDBARW');
INSERT INTO PROGRAM VALUES ('033','Ekonomi','Räkenskapsår','Ändra bokföringsårsdata','CHGBARW');
INSERT INTO PROGRAM VALUES ('034','Administration','Företagsdata','Ny post','ADDFTGW');
INSERT INTO PROGRAM VALUES ('035','Administration','Företagsdata','Ändra post','CHGFTGW');
INSERT INTO PROGRAM VALUES ('036','Administration','Företagsdata','Visa företagsdata','DSPFTGW');
INSERT INTO PROGRAM VALUES ('037','Försäljning','Kunddata','Ny kund','ADDKUW');
INSERT INTO PROGRAM VALUES ('038','Försäljning','Kunddata','Ny leveransadress för kund','ADDLEVPW');
INSERT INTO PROGRAM VALUES ('039','Inköp','Leverantörsdata','Ny leverantör','ADDLEVW');
INSERT INTO PROGRAM VALUES ('040','Inköp','Leverantörsdata','Visa en leverantör','DSPLEVW');
INSERT INTO PROGRAM VALUES ('041','Inköp','Leverantörsdata','Ändra leverantörsdata','CHGLEVW');
INSERT INTO PROGRAM VALUES ('042','Ekonomi','Bokföring','Reg. leverantörsfaktura','LEVFAKTW');
INSERT INTO PROGRAM VALUES ('043','Ekonomi','Rapporter','Leverantörsreskontra','LEVRESKW');
INSERT INTO PROGRAM VALUES ('054','Administration','Betalningsvillkor','Lista betalningsvillkor','LSTBETVW');
INSERT INTO PROGRAM VALUES ('044','Ekonomi','Rapporter','Förfallna levfakturor','ATTBETW');
INSERT INTO PROGRAM VALUES ('045','Ekonomi','Rapporter','Saldolista','SDOLISW');
INSERT INTO PROGRAM VALUES ('046','Försäljning','Kunddata','Visa kunddata','DSPKUW');
INSERT INTO PROGRAM VALUES ('047','Försäljning','Kunddata','Ändra kunddata','CHGKUW');
INSERT INTO PROGRAM VALUES ('048','Försäljning','Kunddata','Lista kunder','LSTKUW');
INSERT INTO PROGRAM VALUES ('049','Administration','Företagsdata','Byta företag','BYTFTGW');
INSERT INTO PROGRAM VALUES ('050','Materialhantering','Artikeldata','Ny artikel','ADDARW');
INSERT INTO PROGRAM VALUES ('051','Materialhantering','Artikeldata','Visa grunddata för en artikel','DSPARW');
INSERT INTO PROGRAM VALUES ('052','Materialhantering','Artikeldata','Visa en artikels ekonomidata','DSPAREW');
INSERT INTO PROGRAM VALUES ('053','Materialhantering','Artikeldata','Ändra artikeldata','CHGARW');
INSERT INTO PROGRAM VALUES ('055','Administration','Betalningsvillkor','Nya betalningsvillkor','ADDBETVW');
INSERT INTO PROGRAM VALUES ('056','Materialhantering','Artikeldata','Lista artiklar','LSTARW');
INSERT INTO PROGRAM VALUES ('057','Administration','Betalningsvillkor','Ändra betalningsvillkor','CHGBETVW');
INSERT INTO PROGRAM VALUES ('058','Inköp','Beställningar','Registrera inköpsorder','ADDINKW');
INSERT INTO PROGRAM VALUES ('059','Inköp','Beställningar','(Ändra beställning)','CHGINKW');
INSERT INTO PROGRAM VALUES ('060','Inköp','Beställningar','(Annulera beställning)','DELINKW');
INSERT INTO PROGRAM VALUES ('061','Inköp','Beställningar','Visa beställning','DSPINKW');
INSERT INTO PROGRAM VALUES ('062','Inköp','Beställningar','Beställningsstock','LSTINKW');
INSERT INTO PROGRAM VALUES ('063','Inköp','Beställningar','Skriv ut beställning','PRTINKW');
INSERT INTO PROGRAM VALUES ('064','Inköp','Beställningar','(Avprickning följesedel)','UPDINKW');
INSERT INTO PROGRAM VALUES ('065','Försäljning','Kundorder','Registrera kundorder','ADDORDW');
INSERT INTO PROGRAM VALUES ('066','Försäljning','Kundorder','(Ändra kundorder)','CHGORDW');
INSERT INTO PROGRAM VALUES ('067','Försäljning','Kundorder','(Makulera kundorder)','DELORDW');
INSERT INTO PROGRAM VALUES ('068','Försäljning','Kundorder','Visa en kundorder','DSPORDW');
INSERT INTO PROGRAM VALUES ('069','Försäljning','Kundorder','Lista kundorder','LSTORDW');
INSERT INTO PROGRAM VALUES ('070','Försäljning','Kundorder','Skriva ut plocklista','PLORDW');
INSERT INTO PROGRAM VALUES ('071','Försäljning','Kundorder','(Skriva ut följesedel)','FSORDW');
INSERT INTO PROGRAM VALUES ('072','Försäljning','Kundorder','(Skriva ut faktura)','FAKTORDW');
INSERT INTO PROGRAM VALUES ('074','Administration','Företagsdata','Ny text i textregistret','ADDTXTW');
INSERT INTO PROGRAM VALUES ('073','Inköp','Leverantörsdata','Lista leverantörer','LSTLEVW');
INSERT INTO PROGRAM VALUES ('076','Administration','Leveransvillkor','Nya leveransvillkor','ADDLEVVW');
INSERT INTO PROGRAM VALUES ('075','Administration','Företagsdata','Radera post i textregistret','DELTXTW');
INSERT INTO PROGRAM VALUES ('077','Administration','Leveransvillkor','Lista leveransvillkor','LSTLEVVW');
INSERT INTO PROGRAM VALUES ('078','Administration','Leveranssätt','Nya leveranssätt','ADDLEVSW');
INSERT INTO PROGRAM VALUES ('079','Administration','Leveranssätt','Lista leveranssätt','LSTLEVSW');
INSERT INTO PROGRAM VALUES ('080','Ekonomi','Rapporter','Balansräkning','BALRPTW');
INSERT INTO PROGRAM VALUES ('081','Ekonomi','Rapporter','Huvudbok','HUVBOKW');
INSERT INTO PROGRAM VALUES ('082','Ekonomi','Rapporter','Dagbok','DAGBOKW');
INSERT INTO PROGRAM VALUES ('083','Försäljning','Kunddata','Lista kunders leveransplatser','LSTLEVPW');
INSERT INTO PROGRAM VALUES ('084','Administration','Företagsdata','Ny databasregistrering','ADDFORW');
INSERT INTO PROGRAM VALUES ('085','Administration','Företagsdata','Lista databaser','LSTFORW');
INSERT INTO PROGRAM VALUES ('086','Materialhantering','Artikeladmin.','Ny produktklass/produktgrupp','ADDPKDW');
INSERT INTO PROGRAM VALUES ('087','Materialhantering','Artikeladmin.','Lista produktklass/produktgrup','LSTPKDW');
INSERT INTO PROGRAM VALUES ('088','Ekonomi','Räkenskapsår','Visa bokföringsår','DSPBARW');
INSERT INTO PROGRAM VALUES ('089','Administration','Företagsdata','Lista företagsdata','LSTFTGW');
INSERT INTO PROGRAM VALUES ('090','Ekonomi','Rapporter','Resultatrapport','RESRPTW');
INSERT INTO PROGRAM VALUES ('091','Ekonomi','Räkenskapsår','Lista alla räkenskapsår','LSTBARW');
INSERT INTO PROGRAM VALUES ('092','Försäljning','Kunddata','Söka kunder','SRCHKUW');
INSERT INTO PROGRAM VALUES ('093','Ekonomi','Rapporter','Skapa SIE-fil','RPTSIEW');
INSERT INTO PROGRAM VALUES ('094','Försäljning','Kundorder','Pricka av plocklista','PLCHGW');

--
-- Table structure for table 'RIGHTS'
--

DROP TABLE IF EXISTS RIGHTS;
CREATE TABLE RIGHTS (
  USERID varchar(8) NOT NULL default '',
  TRNSID varchar(8) NOT NULL default '',
  PRIMARY KEY  (USERID,TRNSID)
) TYPE=MyISAM;

--
-- Dumping data for table 'RIGHTS'
--

INSERT INTO RIGHTS VALUES ('ADMIN','BYTFTGW');
INSERT INTO RIGHTS VALUES ('ADMIN','PRGLST');
INSERT INTO RIGHTS VALUES ('OLFIX','ADDRGTW');
INSERT INTO RIGHTS VALUES ('OLFIX','ARICHK');
INSERT INTO RIGHTS VALUES ('OLFIX','BARDSP');
INSERT INTO RIGHTS VALUES ('OLFIX','KTOCHK');
INSERT INTO RIGHTS VALUES ('OLFIX','KTOLST');
INSERT INTO RIGHTS VALUES ('OLFIX','KTOVIEW');
INSERT INTO RIGHTS VALUES ('OLFIX','PRGLST');
INSERT INTO RIGHTS VALUES ('OLFIX','RGTADD');
INSERT INTO RIGHTS VALUES ('OLFIX','RGTCHK');
INSERT INTO RIGHTS VALUES ('OLFIX','RGTDEL');
INSERT INTO RIGHTS VALUES ('OLFIX','RGTLST');
INSERT INTO RIGHTS VALUES ('OLFIX','TRHDADD');
INSERT INTO RIGHTS VALUES ('OLFIX','TRNSADD');
INSERT INTO RIGHTS VALUES ('OLFIX','TRNSDEL');
INSERT INTO RIGHTS VALUES ('OLFIX','USERADD');
INSERT INTO RIGHTS VALUES ('OLFIX','USERLST');
INSERT INTO RIGHTS VALUES ('OLFIX','VERUPD');
INSERT INTO RIGHTS VALUES ('TESTARE','LSTUSRW');
INSERT INTO RIGHTS VALUES ('TESTARE','PRGLST');
INSERT INTO RIGHTS VALUES ('TESTARE','RGTCHK');
INSERT INTO RIGHTS VALUES ('TESTARE','USERADD');
INSERT INTO RIGHTS VALUES ('TESTARE','USERDSP');
INSERT INTO RIGHTS VALUES ('TESTARE','USERLST');

--
-- Table structure for table 'STDLEVPLATS'
--

DROP TABLE IF EXISTS STDLEVPLATS;
CREATE TABLE STDLEVPLATS (
  STDLEVPLATS char(3) NOT NULL default '',
  KUNDNR varchar(10) NOT NULL default '',
  ADRESS varchar(30) NOT NULL default '',
  POSTNR varchar(6) NOT NULL default '',
  POSTADR varchar(30) NOT NULL default '',
  LAND varchar(30) default NULL,
  PRIMARY KEY  (STDLEVPLATS,KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'STDLEVPLATS'
--


--
-- Table structure for table 'TEXTREG'
--

DROP TABLE IF EXISTS TEXTREG;
CREATE TABLE TEXTREG (
  TEXTNR char(3) NOT NULL default '',
  TXT text,
  PRIMARY KEY  (TEXTNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'TEXTREG'
--


--
-- Table structure for table 'TRANSID'
--

DROP TABLE IF EXISTS TRANSID;
CREATE TABLE TRANSID (
  TRNSID varchar(8) NOT NULL default '',
  TRNSTXT varchar(60) default NULL,
  PRIMARY KEY  (TRNSID)
) TYPE=MyISAM;

--
-- Dumping data for table 'TRANSID'
--

INSERT INTO TRANSID VALUES ('ARICHK','Kontrollera om visst bokföringsår finns');
INSERT INTO TRANSID VALUES ('BARDSP','Hämta data för angivet bokföringsår');
INSERT INTO TRANSID VALUES ('BARCHK','Kontrollera om visst bokföringsår finns');
INSERT INTO TRANSID VALUES ('BOKF','Bokföringsprogram');
INSERT INTO TRANSID VALUES ('FORDSP','Visa info om databas nr x');
INSERT INTO TRANSID VALUES ('FTGUPD','Uppdatera företagsdata');
INSERT INTO TRANSID VALUES ('KSTADD','Nyupplägg av kostnadsställe');
INSERT INTO TRANSID VALUES ('KSTCHK','Kontrollera om visst kostnadställe finns');
INSERT INTO TRANSID VALUES ('KSTDSP','Visa info för ett kostnadställe');
INSERT INTO TRANSID VALUES ('KSTLST','Lista kostnadsställen på skärm');
INSERT INTO TRANSID VALUES ('KTOADD','Lägga till en ny post i konto');
INSERT INTO TRANSID VALUES ('KTOCHG','Ändra info för ett kontonr');
INSERT INTO TRANSID VALUES ('KTOCHK','Kontrollera om visst konto finns');
INSERT INTO TRANSID VALUES ('KTODEL','Ta bort post i konto (endast utan transaktioner)');
INSERT INTO TRANSID VALUES ('KTODSP','Visa info på ett konto');
INSERT INTO TRANSID VALUES ('KTOLST','Lista alla konton, nr och text');
INSERT INTO TRANSID VALUES ('KTORPT','Lista alla poster i tabellen VERRAD');
INSERT INTO TRANSID VALUES ('KTOUPD','Uppdatera konto med antingen debet eller kredit');
INSERT INTO TRANSID VALUES ('KTOVIEW','Visa kontonr och benämning på skärm');
INSERT INTO TRANSID VALUES ('PRGLST','Lista program');
INSERT INTO TRANSID VALUES ('RGTADD','Lägga till behörighet till transaktioner');
INSERT INTO TRANSID VALUES ('RGTCHK','Kontrolera användares behörighet');
INSERT INTO TRANSID VALUES ('RGTDEL','Ta bort behörighet till transaktioner');
INSERT INTO TRANSID VALUES ('RGTDSP','Visa behörigheter för en användare');
INSERT INTO TRANSID VALUES ('RGTLST','Lista alla behörigheter');
INSERT INTO TRANSID VALUES ('TRHDADD','Lägga till ny loggpost i TRHD');
INSERT INTO TRANSID VALUES ('TRNSADD','Ny post i TRANSID');
INSERT INTO TRANSID VALUES ('TRNSCHG','Ändra post i TRANSID');
INSERT INTO TRANSID VALUES ('TRNSDEL','Ta bort post i TRANSID');
INSERT INTO TRANSID VALUES ('TRNSDSP','Visa enstaka TRANSID');
INSERT INTO TRANSID VALUES ('TRNSLST','Lista alla TRANSID');
INSERT INTO TRANSID VALUES ('USERADD','Ny post i USER');
INSERT INTO TRANSID VALUES ('USERCHG','Ändra post i USER');
INSERT INTO TRANSID VALUES ('USERDEL','Ta bort post i USER');
INSERT INTO TRANSID VALUES ('USERDSP','Visa en användare');
INSERT INTO TRANSID VALUES ('USERLST','Lista alla användare');
INSERT INTO TRANSID VALUES ('VALLST','Lista valutor');
INSERT INTO TRANSID VALUES ('VALADD','Lägga upp en ny valuta');
INSERT INTO TRANSID VALUES ('VALCHG','Ändra valutainformation');
INSERT INTO TRANSID VALUES ('VALDEL','Ta bort en valuta');
INSERT INTO TRANSID VALUES ('VALDSP','Visa en valuta');
INSERT INTO TRANSID VALUES ('VERUPD','Nyuppläggning av verifikat');
INSERT INTO TRANSID VALUES ('VERDSP','Visa enstaka verifikation');
INSERT INTO TRANSID VALUES ('VRDADD','Ny detaljpost för verifikation till VERD');
INSERT INTO TRANSID VALUES ('VRHADD','Ny huvudpost för verifikation till VERH');
INSERT INTO TRANSID VALUES ('WRREC','Skriva post till tempfilen /tmp/vernr.txt');
INSERT INTO TRANSID VALUES ('ATTBET','Lista leverantörsfakturor att betala');
INSERT INTO TRANSID VALUES ('BARADD','Lägga upp nytt bokföringsår');
INSERT INTO TRANSID VALUES ('BARCHG','Ändra data för angivet bokföringsår');
INSERT INTO TRANSID VALUES ('BARFND','Hitta bokföringsår för angivet datum');
INSERT INTO TRANSID VALUES ('BETDSP','Visa ett betalningsvillkor');
INSERT INTO TRANSID VALUES ('FTGADD','Lägga upp en ny företagspost');
INSERT INTO TRANSID VALUES ('FTGDSP','Visa företagsdata');
INSERT INTO TRANSID VALUES ('FTGLST','Lista posttyper för företagsdata');
INSERT INTO TRANSID VALUES ('FTGLIS','Lista företagsdata');
INSERT INTO TRANSID VALUES ('KUADD','Registrera nya kunder');
INSERT INTO TRANSID VALUES ('KUCHG','Ändra kunddata');
INSERT INTO TRANSID VALUES ('KUCHK','Kontrollera om kundnr finns');
INSERT INTO TRANSID VALUES ('KUDSP','Visa kunddata');
INSERT INTO TRANSID VALUES ('KULST','Lista kunder, kundnr och namn');
INSERT INTO TRANSID VALUES ('LEVADD','Lägga upp en ny leverantör');
INSERT INTO TRANSID VALUES ('LEVCHG','Ändra leverantörsdata');
INSERT INTO TRANSID VALUES ('LEVDSP','Visa en leverantör');
INSERT INTO TRANSID VALUES ('LEVLST','Lista leverantörer,nr och namn');
INSERT INTO TRANSID VALUES ('LRESRPT','Lista alla obetalda poster i tabellen LEVRESK');
INSERT INTO TRANSID VALUES ('LRESADD','Ny post i leverantörsreskontran');
INSERT INTO TRANSID VALUES ('RPTCRE','Rapportgenerator. Skapa rapporter');
INSERT INTO TRANSID VALUES ('SLPADD','Standardleveransplats');
INSERT INTO TRANSID VALUES ('TRNTST','Detta är en testfunktion');
INSERT INTO TRANSID VALUES ('ARCHK','Kontrollera om artikelnummer finns');
INSERT INTO TRANSID VALUES ('ARADD','Lägga upp en ny artikel');
INSERT INTO TRANSID VALUES ('AR2ADD','Lägga upp ny artikel i lagerställeregister.');
INSERT INTO TRANSID VALUES ('ARDSP','Visa grunddata för en artikel');
INSERT INTO TRANSID VALUES ('ARDSPL','Visa lagerdata för en artikel');
INSERT INTO TRANSID VALUES ('ARCHG','Ändra grunddata för en artikel');
INSERT INTO TRANSID VALUES ('ARCHGL','Ändra lagerställedata för en artikel');
INSERT INTO TRANSID VALUES ('BETLST','Lista betalningsvillkor');
INSERT INTO TRANSID VALUES ('BETADD','Lägga upp ett nytt betalningsvillkor');
INSERT INTO TRANSID VALUES ('ARLST','Lista artiklar(artikelnr,benämn1,benämn2)');
INSERT INTO TRANSID VALUES ('BETCHG','Ändra data för betalningsvillkor');
INSERT INTO TRANSID VALUES ('TXTDSP','Visa texter ur TEXTREG');
INSERT INTO TRANSID VALUES ('TXTADD','Lägg upp en ny post i TEXTREG');
INSERT INTO TRANSID VALUES ('INKADD','Lägga upp en ny inköpsorder');
INSERT INTO TRANSID VALUES ('INKRADD','Lägga upp en ny inköpsorderrad');
INSERT INTO TRANSID VALUES ('TXTDEL','Radera post i TEXTREG');
INSERT INTO TRANSID VALUES ('INKRLST','Lista alla rader på angiven inköpsorder');
INSERT INTO TRANSID VALUES ('INKHDSP','Visa orderhuvud för angiven inköpsorder');
INSERT INTO TRANSID VALUES ('INKLST','Beställningsstock');
INSERT INTO TRANSID VALUES ('LEVVDSP','Visa ett leveransvillkor');
INSERT INTO TRANSID VALUES ('LEVSDSP','Visa ett leveranssätt');
INSERT INTO TRANSID VALUES ('LEVVADD','Lägga upp ett nytt leveransvillkor');
INSERT INTO TRANSID VALUES ('LEVSADD','Lägga upp ett nytt leveranssätt');
INSERT INTO TRANSID VALUES ('LEVVLST','Lista leveransvillkor');
INSERT INTO TRANSID VALUES ('LEVSLST','Lista leveranssätt');
INSERT INTO TRANSID VALUES ('VERHDSP','Hämta mindatum och maxdatum för angivet bokf.år');
INSERT INTO TRANSID VALUES ('VERHLST','Lista verifikationers huvudposter för önskat bokföringsår');
INSERT INTO TRANSID VALUES ('HBOKRPT','Huvudboksrapport');
INSERT INTO TRANSID VALUES ('DBOKRPT','Dagboksrapport');
INSERT INTO TRANSID VALUES ('PRTAPI','Utskriftsinterface');
INSERT INTO TRANSID VALUES ('LEVPLST','Lista kunders leveransadresser');
INSERT INTO TRANSID VALUES ('FORCHK','Kontr. om databas finns i tabell DATABAS');
INSERT INTO TRANSID VALUES ('FORADD','Ny databas i tabellen DATABAS');
INSERT INTO TRANSID VALUES ('FORLST','Lista databaser i tabell DATABAS');
INSERT INTO TRANSID VALUES ('PKDADD','Ny produktgrupp/produktkod/produktklass');
INSERT INTO TRANSID VALUES ('PKDLST','Lista produktgrupper/produktkoder/produktklasser');
INSERT INTO TRANSID VALUES ('WKUDSP','Visa begränsade kunddata för webbkund');
INSERT INTO TRANSID VALUES ('ARLSTL','Lista artiklar med lagersaldo');
INSERT INTO TRANSID VALUES ('ARLIS','Lista artiklaf för angiven produktklass');
INSERT INTO TRANSID VALUES ('ARLSPK','Lista artiklar för angiven produktkod');
INSERT INTO TRANSID VALUES ('AR2UPD','Uppdatera artikelpost i LAGERSTELLEREG');
INSERT INTO TRANSID VALUES ('BARLST','Lista bokföringsår');
INSERT INTO TRANSID VALUES ('KUSRCH','Söka kunder på namn, postnr, tfnnr eller postadr');
INSERT INTO TRANSID VALUES ('LEVPDSP','Visa en standardleveransplats');
INSERT INTO TRANSID VALUES ('ORDADD','Nyupplägg av kundorderhuvud');
INSERT INTO TRANSID VALUES ('ORDCHK','Kontrollera diverse uppgifter på kundorder');
INSERT INTO TRANSID VALUES ('ORDDSP','Visa en kundorders huvudpost');
INSERT INTO TRANSID VALUES ('ORDRDSP','Visa en kundorders orderrader');
INSERT INTO TRANSID VALUES ('PKDDSP','Visa en produktgrupp/produktkod/produktklass');
INSERT INTO TRANSID VALUES ('SIEEXPK','SIE-export av kontoplan');
INSERT INTO TRANSID VALUES ('SIEEXPR','SIE-export av resultat');
INSERT INTO TRANSID VALUES ('SIEEXPV','SIE-export av verifikat');
INSERT INTO TRANSID VALUES ('DBCHK','Lista databaser registrerade i databasen mysql');
INSERT INTO TRANSID VALUES ('ORDLST2','Lista kundorder med begränsad information');
INSERT INTO TRANSID VALUES ('ORDLST','Lista kundorder');
INSERT INTO TRANSID VALUES ('PICKADD','Nytt plock av kundorderrad');
INSERT INTO TRANSID VALUES ('PICKDSP','Visa plockade men ej utskrivna plock');
INSERT INTO TRANSID VALUES ('PICKLST','Lista avprickade kundorderrader');

--
-- Table structure for table 'TRHD'
--

DROP TABLE IF EXISTS TRHD;
CREATE TABLE TRHD (
  TRNSNR int(11) NOT NULL auto_increment,
  TRNSID varchar(8) NOT NULL default '',
  TID varchar(20) NOT NULL default '',
  USERID varchar(8) NOT NULL default '',
  TRNSDATA varchar(255) default NULL,
  PRIMARY KEY  (TRNSNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'TRHD'
--


--
-- Table structure for table 'USR'
--

DROP TABLE IF EXISTS USR;
CREATE TABLE USR (
  USERID varchar(8) NOT NULL default '',
  NAMN varchar(30) default NULL,
  AVD varchar(10) default NULL,
  GRUPP varchar(10) default NULL,
  PRIMARY KEY  (USERID)
) TYPE=MyISAM;

--
-- Dumping data for table 'USR'
--

INSERT INTO USR VALUES ('OLFIX','Olfix Superuser','IT','Stab');
INSERT INTO USR VALUES ('TESTARE','Testare Test','Prov','Utv');
INSERT INTO USR VALUES ('ADMIN','Admin Adminstratör','IT','Stab');

--
-- Table structure for table 'VALUTA'
--

DROP TABLE IF EXISTS VALUTA;
CREATE TABLE VALUTA (
  VALUTAID char(3) NOT NULL default '',
  LAND varchar(15) default NULL,
  SALJ decimal(3,2) default NULL,
  KOP decimal(3,2) default NULL,
  BETECKNING varchar(15) default NULL,
  PRIMARY KEY  (VALUTAID)
) TYPE=MyISAM;

--
-- Dumping data for table 'VALUTA'
--

INSERT INTO VALUTA VALUES ('DKK','Danmark',1.22,1.22,'Kronor');
INSERT INTO VALUTA VALUES ('NOK','Norge',1.23,1.23,'Kronor');
INSERT INTO VALUTA VALUES ('NYZ','Nya Zeeland',4.45,4.45,'Dollar');
INSERT INTO VALUTA VALUES ('SAR','Saudiarabien',2.40,2.40,'Riyal');
INSERT INTO VALUTA VALUES ('HKD','Honkong',0.00,0.00,'Dollar');
INSERT INTO VALUTA VALUES ('MYR','Malaysia',2.36,2.36,'Ringgit');
INSERT INTO VALUTA VALUES ('SGD','Singapore',5.08,5.08,'Dollar');
INSERT INTO VALUTA VALUES ('CAD','Kanada',5.66,5.66,'Dollar');
INSERT INTO VALUTA VALUES ('AUD','Australien',5.03,5.03,'Dollar');
INSERT INTO VALUTA VALUES ('USD','USA',8.97,8.97,'Dollar');
INSERT INTO VALUTA VALUES ('JPY','Japan',7.38,7.38,'Yen');
INSERT INTO VALUTA VALUES ('GBP','Storbritanien',14.26,14.26,'Pund');
INSERT INTO VALUTA VALUES ('EUR','Europa',9.08,9.08,'Euro');
INSERT INTO VALUTA VALUES ('CHF','Schweiz',0.00,0.00,'France');
INSERT INTO VALUTA VALUES ('SEK','Sverige',0.99,0.99,'Kronor');
INSERT INTO VALUTA VALUES ('EEK','Estland',0.59,0.57,'Kronor');

--
-- Table structure for table 'VERHUVUD'
--

DROP TABLE IF EXISTS VERHUVUD;
CREATE TABLE VERHUVUD (
  VERNR int(11) NOT NULL default '0',
  ARID char(2) NOT NULL default '',
  VERDATUM date default NULL,
  REGDAT date default NULL,
  DEBET decimal(10,2) default NULL,
  KREDIT decimal(10,2) default NULL,
  VERTEXT varchar(60) default NULL,
  KORRIGERAR int(11) default NULL,
  KORRIGERAD int(11) default NULL,
  USERID varchar(8) default NULL,
  PRIMARY KEY  (VERNR,ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'VERHUVUD'
--


--
-- Table structure for table 'VERRAD'
--

DROP TABLE IF EXISTS VERRAD;
CREATE TABLE VERRAD (
  VERNR int(11) NOT NULL default '0',
  RADNR smallint(6) NOT NULL default '0',
  ARID char(2) NOT NULL default '',
  KTONR varchar(4) default NULL,
  BELOPP decimal(10,2) default NULL,
  DK enum('D','K') default NULL,
  KSTALLE varchar(4) default NULL,
  PROJEKT varchar(4) default NULL,
  SUBKTO varchar(4) default NULL,
  DEFINITIV enum('J','N') default 'N',
  STRUKEN enum('J','N') default 'N',
  PRIMARY KEY  (VERNR,RADNR,ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'VERRAD'
--


--
-- Table structure for table 'WEBBKUND'
--

DROP TABLE IF EXISTS WEBBKUND;
CREATE TABLE WEBBKUND (
  KUNDNR varchar(10) NOT NULL default '',
  NAMN varchar(60) NOT NULL default '',
  ADRESS varchar(30) default NULL,
  POSTNR varchar(6) default NULL,
  POSTADR varchar(30) default NULL,
  LAND varchar(30) default NULL,
  ADRESS2 varchar(30) default NULL,
  POSTNR2 varchar(6) default NULL,
  POSTADR2 varchar(30) default NULL,
  LAND2 varchar(30) default NULL,
  TFNNR varchar(15) default NULL,
  EMAILADR varchar(30) default NULL,
  BETALVILLKOR char(3) default NULL,
  LEVVILLKOR char(3) default NULL,
  LEVSETT char(3) default NULL,
  ORDERERKENNANDE enum('J','N') default 'J',
  PLOCKLISTA enum('J','N') default 'J',
  FOLJESEDEL enum('J','N') default 'J',
  KRAVBREV enum('J','N') default 'J',
  EXPAVGIFT enum('J','N') default 'J',
  FRAKTAVG enum('J','N') default 'J',
  KREDITLIMIT decimal(10,2) default NULL,
  KREDITDAGAR int(11) default NULL,
  DROJMALSRTA enum('J','N') default 'J',
  DROJMALSFAKTURA enum('J','N') default 'J',
  SENASTEKRAVDATUM date default NULL,
  SKULD decimal(10,2) default NULL,
  ORDERSTOCK decimal(10,2) default NULL,
  PASSWORD varchar(16) NOT NULL default '',
  PRIMARY KEY  (KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'WEBBKUND'
--


--
-- Current Database: olfixtst
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ olfixtst;

USE olfixtst;

--
-- Table structure for table 'ARTIKELREG'
--

DROP TABLE IF EXISTS ARTIKELREG;
CREATE TABLE ARTIKELREG (
  ARTIKELNR varchar(30) NOT NULL default '',
  ARBENEMNING1 varchar(60) NOT NULL default '',
  ARBENEMNING2 varchar(60) default NULL,
  ARENHET varchar(5) default NULL,
  ARFPRIS decimal(10,2) default NULL,
  ARLEDTID char(3) default NULL,
  ARPRODKLASS varchar(5) default NULL,
  ARPRODKTO varchar(5) default NULL,
  ARLEVNR1 varchar(10) default NULL,
  ARLEVNR2 varchar(10) default NULL,
  ARLEVNR3 varchar(10) default NULL,
  ARNETTOVIKT decimal(10,2) default NULL,
  ARARTTYP enum('0','1','2','3','4') default '0',
  ARSTRUKT enum('','B','I','T','F') default '',
  ARURBENEMNING varchar(60) default NULL,
  ARURLAND varchar(30) default NULL,
  ARURARTNR varchar(30) default NULL,
  ARTULLTAX varchar(10) default NULL,
  ARVOLYM decimal(4,3) default NULL,
  AROMRFAKTOR int(11) NOT NULL default '1',
  PRIMARY KEY  (ARTIKELNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'ARTIKELREG'
--

INSERT INTO ARTIKELREG VALUES ('1000-1001','Att använda GNU/LINUX','Linus Walleij','ST',117.00,'7','1000','','100','200','300',0.00,'2','','Att använda GNU/LINUX','Sverige','ISBN 91-44-03400-8','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1002','Linux MAGNUM','Jack Tacket,Jr och Steven Burn','ST',117.00,'7','1000','','100','200','300',0.00,'2','','Linux MAGNUM','Sverige','ISBN 0-7645-2508-5','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1003','Linux På egen hand','Steve Oualline och Eric Foster','ST',117.00,'7','1000','','100','200','300',0.00,'2','','Linux På egen hand','Sverige','ISBN 013-019716-5','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1004','C++ programmering','Stephen Prata','ST',117.00,'7','1001','','100','200','300',0.00,'2','','Linux På egen hand','Sverige','ISBN 91-86201-34-4','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1005','Programming with Qt','Matthias Kalle Dalheimer','ST',117.00,'7','1002','','100','200','300',0.00,'2','','Programming with Qt','Sverige','ISBN 0-596-00064-2','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1006','The C Programming language','Brian W Kernighan och Dennis M','ST',117.00,'7','1003','','100','200','300',0.00,'2','','The C Programming language','USA','ISBN 91-970296-45','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1007','The C Programming lang.Facit','Clovis Tondo,Scott Gimpel','ST',117.00,'7','1003','','100','200','300',0.00,'2','','The C Programming lang.Facit','USA','ISBN 91-970296-88','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1008','Vägen till C','Ulf Bilting,Jan Skansholm','ST',117.00,'7','1003','','100','200','300',0.00,'2','','Vägen till C','Sverige','ISBN 91-44-26732-0','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1009','Arbeta med C','J A Illik','ST',117.00,'7','1003','','100','200','300',0.00,'2','','Arbeta med C','Sverige','ISBN 91-86200-40-2','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1010','Nyckeln till C','Alan C Plantz','ST',117.00,'7','1003','','100','200','300',0.00,'2','','Nyckeln till C','Sverige','ISBN 91-86200-75-5','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1011','Professional Linux Programming','Neil Mattew and Richard Stones','ST',117.00,'7','1000','','100','200','300',0.00,'2','','Professional Linux Programming','USA','ISBN 1861003013','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1012','Qt Programming in 24 Hours','Daniel Solin','ST',117.00,'7','1002','','100','200','300',0.00,'2','','Qt Programming in 24 Hours','USA','ISBN 0-672-31869-5','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1013','C++ GUI Programming with Qt 3','Jasmine Blanchette, Mark Summerfield','ST',117.00,'7','1002','','100','200','300',0.00,'2','','C++ GUI programming with Qt 3','USA','ISBN 0-13-124072-2','',0.000,1);
INSERT INTO ARTIKELREG VALUES ('1000-1014','Practical Qt','Mattias Kalle Dalheimer,Jesper Pedersen','ST',117.00,'7','1002','','100','200','300',0.00,'2','','Practical Qt','Tyskland','ISBN 3-89864-260-1','',0.000,1);

--
-- Table structure for table 'BETVILKOR'
--

DROP TABLE IF EXISTS BETVILKOR;
CREATE TABLE BETVILKOR (
  BETVILKOR char(3) NOT NULL default '',
  DAGAR char(3) default NULL,
  BESKRIVNING varchar(40) NOT NULL default '',
  PRIMARY KEY  (BETVILKOR)
) TYPE=MyISAM;

--
-- Dumping data for table 'BETVILKOR'
--

INSERT INTO BETVILKOR VALUES ('1','30','30 dagar netto');
INSERT INTO BETVILKOR VALUES ('2','20','20 dagar netto');
INSERT INTO BETVILKOR VALUES ('3','10','10 dagar netto');
INSERT INTO BETVILKOR VALUES ('4','0','Kontantköp');
INSERT INTO BETVILKOR VALUES ('5','30','Postförskott');
INSERT INTO BETVILKOR VALUES ('6','60','60 dagar netto');
INSERT INTO BETVILKOR VALUES ('001','30','30 dagar netto');
INSERT INTO BETVILKOR VALUES ('002','20','20 dagar netto');
INSERT INTO BETVILKOR VALUES ('003','10','10 dagar netto');
INSERT INTO BETVILKOR VALUES ('004','0','Kontantköp');
INSERT INTO BETVILKOR VALUES ('005','30','Postförskott');
INSERT INTO BETVILKOR VALUES ('006','60','60 dagar netto');

--
-- Table structure for table 'BOKFAR'
--

DROP TABLE IF EXISTS BOKFAR;
CREATE TABLE BOKFAR (
  ARID char(2) NOT NULL default '',
  BENAMNING varchar(25) default NULL,
  ARSTART date default NULL,
  ARSLUT date default NULL,
  ARLAST enum('J','N') default 'N',
  SENVERDAT date default NULL,
  VERNR int(11) default NULL,
  KONTOPLAN varchar(15) default NULL,
  BESKATTNINGSAR varchar(4) default NULL,
  PRIMARY KEY  (ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'BOKFAR'
--

INSERT INTO BOKFAR VALUES ('SS','2003-01-01--2003-12-31','2003-01-01','2003-12-31','N','0000-00-00',987124,'EUBAS2003','2003');
INSERT INTO BOKFAR VALUES ('ST','2003-01-01--2003-12-31','2003-01-01','2003-12-31','N','0000-00-00',987124,'EUBAS2003','2003');
INSERT INTO BOKFAR VALUES ('AD','2003-01-01--2003-12-31','2003-01-01','2003-12-31','N','2004-01-02',101,'EUBAS97','2003');
INSERT INTO BOKFAR VALUES ('AE','2005-01-01--2005-12-31','2005-01-01','2005-12-31','N','0000-00-00',1,'EUBAS2003','2005');

--
-- Table structure for table 'DATABAS'
--

DROP TABLE IF EXISTS DATABAS;
CREATE TABLE DATABAS (
  DATABASNR char(3) NOT NULL default '',
  DATABASTEXT varchar(15) NOT NULL default '',
  PRIMARY KEY  (DATABASNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'DATABAS'
--

INSERT INTO DATABAS VALUES ('99','olfixtst');
INSERT INTO DATABAS VALUES ('01','olfix');
INSERT INTO DATABAS VALUES ('02','olfixweb');

--
-- Table structure for table 'FTGDATA'
--

DROP TABLE IF EXISTS FTGDATA;
CREATE TABLE FTGDATA (
  POSTTYP varchar(5) NOT NULL default '',
  POSTBESKR varchar(60) default NULL,
  FDATA text,
  PRIMARY KEY  (POSTTYP)
) TYPE=MyISAM;

--
-- Dumping data for table 'FTGDATA'
--

INSERT INTO FTGDATA VALUES ('FNAMN','Företagsnamn','PROGRAM AB');
INSERT INTO FTGDATA VALUES ('FTGNR','Företagsnummer','991199-1991');
INSERT INTO FTGDATA VALUES ('ADR1','Postadress','Box 70');
INSERT INTO FTGDATA VALUES ('ADR2','Postnummer till Postadress','199 98');
INSERT INTO FTGDATA VALUES ('ADR3','Ort till Postadress','PROGSTAD');
INSERT INTO FTGDATA VALUES ('ADR4','Besöksadress','Syntaxvägen 99');
INSERT INTO FTGDATA VALUES ('ADR5','Postnr till Besöksadress','199 98');
INSERT INTO FTGDATA VALUES ('ADR6','Ort till Besöksadress','PROGSTAD');
INSERT INTO FTGDATA VALUES ('ADR7','Godsadress','Verktygsgatan 11');
INSERT INTO FTGDATA VALUES ('ADR8','Postnr till Godsadress','199 97');
INSERT INTO FTGDATA VALUES ('ADR9','Ort till Godsadress','PROGSTAD');
INSERT INTO FTGDATA VALUES ('TFNVX','Telefonnummer till vx','09-199300');
INSERT INTO FTGDATA VALUES ('TFN1','Telefonnummer','09-199300');
INSERT INTO FTGDATA VALUES ('TFN2','Mobiltelefonnummer','070-98765411');
INSERT INTO FTGDATA VALUES ('TFNMB','Mobiltelefonnummer','070-98765411');
INSERT INTO FTGDATA VALUES ('TFAX','Telefaxnummer','09-199397');
INSERT INTO FTGDATA VALUES ('TELEX','Telexnummer','12345');
INSERT INTO FTGDATA VALUES ('EML1','E-mailadress','info@program.se');
INSERT INTO FTGDATA VALUES ('MOMSI','Momskonto, ingående moms','2641');
INSERT INTO FTGDATA VALUES ('MOMSU','Momskonto, utgående moms','2611');
INSERT INTO FTGDATA VALUES ('MOMS1','Momssats 1','25');
INSERT INTO FTGDATA VALUES ('MOMS2','Momssats 2','12');
INSERT INTO FTGDATA VALUES ('MOMS3','Momssats 3','6');
INSERT INTO FTGDATA VALUES ('MOMS4','Momssats 4',' ');
INSERT INTO FTGDATA VALUES ('MOMS5','Momssats 5',' ');
INSERT INTO FTGDATA VALUES ('AUTOK','Automatkontering J/N','N');
INSERT INTO FTGDATA VALUES ('KORNR','Senast använda kundordernr','0');
INSERT INTO FTGDATA VALUES ('BF1','Bokföringsperiod 1','Januari');
INSERT INTO FTGDATA VALUES ('BF2','Bokföringsperiod 2','Februari');
INSERT INTO FTGDATA VALUES ('BF3','Bokföringsperiod 3','Mars');
INSERT INTO FTGDATA VALUES ('BF4','Bokföringsperiod 4','April');
INSERT INTO FTGDATA VALUES ('BF5','Bokföringsperiod 5','Maj');
INSERT INTO FTGDATA VALUES ('BF6','Bokföringsperiod 6','Juni');
INSERT INTO FTGDATA VALUES ('BF7','Bokföringsperiod 7','Juli');
INSERT INTO FTGDATA VALUES ('BF8','Bokföringsperiod 8','Augusti');
INSERT INTO FTGDATA VALUES ('BF9','Bokföringsperiod 9','September');
INSERT INTO FTGDATA VALUES ('BF10','Bokföringsperiod 10','Oktober');
INSERT INTO FTGDATA VALUES ('BF11','Bokföringsperiod 11','Novemper');
INSERT INTO FTGDATA VALUES ('BF12','Bokföringsperiod 12','December');
INSERT INTO FTGDATA VALUES ('BF13','Bokföringsperiod 13','Januari');
INSERT INTO FTGDATA VALUES ('INKNR','Senast använda inköpsordernr','28');
INSERT INTO FTGDATA VALUES ('SNIKD','Branschtillhörighet','82301');
INSERT INTO FTGDATA VALUES ('WKUNR','Senaste använda webbkundnummer','4379');
INSERT INTO FTGDATA VALUES ('FAKNR','Senaste fakturanr på kundorder','0');
INSERT INTO FTGDATA VALUES ('FKNR2','Senaste fakturanr på kundorder,serie 2','0');
INSERT INTO FTGDATA VALUES ('FKNRS','Antal fakturanrserier, default = 1','0');
--
-- Table structure for table 'INKRADREG'
--

DROP TABLE IF EXISTS INKRADREG;
CREATE TABLE INKRADREG (

  INKORDNR varchar(10) NOT NULL default '',
  INKORDRADNR int(4) NOT NULL default '0',
  ARTIKELNR varchar(30) default NULL,
  BENEMNING varchar(30) default NULL,
  LEVARTIKELNR varchar(30) default NULL,
  LEVBENEMNING varchar(30) default NULL,
  ENHET varchar(5) default NULL,
  BESTANTAL decimal(10,2) default NULL,
  LEVERERAT decimal(10,2) default NULL,
  RESTNOTERAT decimal(10,2) default NULL,
  INKPRIS decimal(10,2) default NULL,
  LEVVECKA varchar(5) default NULL,
  TORDNR int(6) default NULL,
  OPNR int(6) default NULL,
  PRIMARY KEY  (INKORDNR,INKORDRADNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'INKRADREG'
--

INSERT INTO INKRADREG VALUES ('6712',10,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','D/A Omvandlare 12-bit','ST',25.00,0.00,25.00,95.00,'351',0,0);
INSERT INTO INKRADREG VALUES ('23',10,'1173-1175','Spänningsregulator positiv',NULL,NULL,'uA78H',0.00,0.00,100.00,0.00,'100',30,4084);
INSERT INTO INKRADREG VALUES ('19',40,'1173-7513','Microprocessor','SY6502','','ST',20.00,5.00,15.00,63.00,'402',0,0);
INSERT INTO INKRADREG VALUES ('19',30,'1173-7300','1024x1 bit static RAM','21022DC','','ST',20.00,0.00,20.00,10.05,'402',0,0);
INSERT INTO INKRADREG VALUES ('19',20,'1173-7300','1024x1 bit static RAM','21022DC','','ST',20.00,10.00,10.00,10.05,'401',0,0);
INSERT INTO INKRADREG VALUES ('19',10,'1173-7206','Dual Monostable Multivibrator','SN74LS123N','','ST',20.00,0.00,20.00,4.75,'402',0,0);
INSERT INTO INKRADREG VALUES ('18',10,'1173-0911','Spänningsregulator positiv','uA7805AWC','','ST',10.00,0.00,10.00,1.50,'402',0,0);
INSERT INTO INKRADREG VALUES ('18',30,'1173-1175','Spänningsregulator positiv','uA78H05ASC','Voltage regulator 5V','ST',10.00,0.00,10.00,30.00,'402',0,0);
INSERT INTO INKRADREG VALUES ('18',50,'1173-1447','Timerkrets','ICM7555','Timer','ST',10.00,0.00,10.00,5.45,'402',0,0);
INSERT INTO INKRADREG VALUES ('18',20,'1173-0963','Spänningsregulator negativ','uA79M05AUC','','ST',10.00,10.00,0.00,5.50,'402',0,0);
INSERT INTO INKRADREG VALUES ('18',40,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','D/A Omvandlare 12-bit','ST',10.00,0.00,10.00,95.00,'402',0,0);
INSERT INTO INKRADREG VALUES ('18',60,'1173-6910','Quadruple 2input NAND gate','SN74LS00N','Quadruple 2input NAND gate','ST',10.00,0.00,10.00,1.45,'402',0,0);
INSERT INTO INKRADREG VALUES ('27',10,'1173-1175','Spänningsregulator positiv','uA78H05ASC','Voltage regulator 5V','',100.00,0.00,100.00,30.00,'4093',0,0);
INSERT INTO INKRADREG VALUES ('26',20,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','','',100.00,0.00,100.00,95.00,'4074',0,0);
INSERT INTO INKRADREG VALUES ('26',10,'1173-1175','Spänningsregulator positiv','uA78H05ASC','Voltage regulator 5V','',100.00,0.00,100.00,30.00,'4074',0,0);
INSERT INTO INKRADREG VALUES ('25',10,'1173-1175','Spänningsregulator positiv','uA78H05ASC','Voltage regulator 5V','',100.00,0.00,100.00,30.00,'4074',0,0);
INSERT INTO INKRADREG VALUES ('25',20,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','','',100.00,0.00,100.00,95.00,'4074',0,0);
INSERT INTO INKRADREG VALUES ('27',20,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','','',100.00,0.00,100.00,95.00,'4093',0,0);
INSERT INTO INKRADREG VALUES ('27',30,'1173-1447','Timerkrets','ICM7555','Timer','',100.00,0.00,100.00,5.45,'4093',0,0);
INSERT INTO INKRADREG VALUES ('28',10,'1173-7300','1024x1 bit statiskt RAM','2102 2DC','','',100.00,0.00,100.00,10.05,'4094',0,0);
INSERT INTO INKRADREG VALUES ('28',20,'1173-7701','Quad 2-input NOR Gate','MC14000BCP','','',100.00,0.00,100.00,1.45,'4101',0,0);
INSERT INTO INKRADREG VALUES ('28',30,'1173-7802','4-Bit Aritmetic Logic Unit','MC14581BCP','','',100.00,0.00,100.00,20.00,'4101',0,0);

--
-- Table structure for table 'INKREG'
--

DROP TABLE IF EXISTS INKREG;
CREATE TABLE INKREG (
  INKORDNR varchar(10) NOT NULL default '',
  BESTTYP enum('N','D','I','L','A') default NULL,
  ORDERDATUM date default NULL,
  LEVNR varchar(10) default NULL,
  LEVNAMN varchar(30) default NULL,
  LEVADRESS varchar(30) default NULL,
  LEVPOSTNR varchar(6) default NULL,
  LEVPOSTADR varchar(30) default NULL,
  LEVLAND varchar(30) default NULL,
  LEVVALUTA char(3) default NULL,
  LEVBETVILLKOR varchar(50) default NULL,
  LEVVILLKOR varchar(150) default NULL,
  LEVSETT varchar(150) default NULL,
  GODSMERKE varchar(30) default NULL,
  KOMMENTAR varchar(250) default NULL,
  BESTTEXT text,
  VARREF varchar(30) default NULL,
  VARREFTFN varchar(15) default NULL,
  VARREFFAX varchar(15) default NULL,
  ERREF varchar(20) default NULL,
  LEVDATUM date default NULL,
  KUNDNR varchar(30) default NULL,
  FTGNAMN varchar(30) default NULL,
  FTGADR varchar(30) default NULL,
  FTGPOSTNR varchar(6) default NULL,
  FTGPOSTADR varchar(30) default NULL,
  SPRAKKOD char(3) default 'sv',
  BEKREFTKOD enum('H','D','E') default 'E',
  ORDERSTATUS enum('N','F','B','M') default 'N',
  UTSKRIFTSKOD enum('J','N') default 'J',
  ORDERSUMMA decimal(10,2) default NULL,
  PRIMARY KEY  (INKORDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'INKREG'
--

INSERT INTO INKREG VALUES ('6712','N','2003-12-13','9999','Testleverantör AB','Delivery Street 1C','199 99','LEVSTAD','Sverige','SEK','60 dagar netto','EXW','ASG kundnr:99901111','Godsmäre','Kommentar','Endast komplett order får levereras\nLevereras med ASG','Pelle Pehrzon','09-199311','09-199312','Caroline Seljare','2003-12-15','98765','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J',NULL);
INSERT INTO INKREG VALUES ('18','N','2003-12-24','9999','Testleverantör AB','Delivery Street 1C','199 99','LEVSTAD','Sverige','SEK','30 dagar netto','EXW','ASG kundnr:99901111','P-order','Kommentar','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.','Pelle Pehrzon','09-199321','09-199322','Caroline Seljare','2004-01-10','98765','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J',1389.00);
INSERT INTO INKREG VALUES ('19','N','2003-12-24','9999','Testleverantör AB','Delivery Street 1C','199 99','LEVSTAD','Sverige','SEK','20 dagar netto','QWOUTA','ASG','Godsmärke','Kommentar','Beställningseftertext','Pelle Pehrzon','09-199341','09-199342','Caroline Seljare','2004-01-10','98765','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J',1757.00);
INSERT INTO INKREG VALUES ('27','N','2004-02-05','126','Dataspecialisten AB','Storgatan 1','199 11','STORSTAD','Sverige','SEK',' 30 dagar netto',' EXW',' Schenker kundnr:11105232','PELLE','Direkt','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.\n  \n\n\n\n','Pelle Pehrzon','09-112233','09112239','Ola Norman','2004-02-25','567891','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J',13045.00);
INSERT INTO INKREG VALUES ('26','N','2004-02-05','123','Leverantör AB','Postgatan 33','199 99','DATABY','SVERIGE','SEK',' 20 dagar netto',' EXW',' Schenker kundnr:11105232','KALLE PALL 26','Detta är en kommentar','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.\n  \n\n\n\n','Pelle Pehrzon','09-59112666','09-112233','Per Josefsson','2004-02-15','12345678','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J',12500.00);
INSERT INTO INKREG VALUES ('25','N','2004-02-05','124','Distributör AB','Brevgatan 1A','199 99','DATABY','SVERIGE','EUR',' 30 dagar netto','','','','','','Pelle Pehrzon','','','Lena Bertils','2004-02-05','12345678','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J',12500.00);
INSERT INTO INKREG VALUES ('28','N','2004-02-16','124','Distributör AB','Brevgatan 1A','199 99','DATABY','SVERIGE','EUR',' 30 dagar netto',' EXW',' Schenker kundnr:11105232','Godsmärke för beställning nr 2','','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.\n  \n\n\n\n','Pelle Pehrzon','','','Lena Bertils','2004-02-26','12345678','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J',3150.00);

--
-- Table structure for table 'KSTALLE'
--

DROP TABLE IF EXISTS KSTALLE;
CREATE TABLE KSTALLE (
  ARID char(2) NOT NULL default '',
  KSTALLE varchar(4) NOT NULL default '',
  BENAMNING varchar(100) default NULL,
  PRIMARY KEY  (ARID,KSTALLE)
) TYPE=MyISAM;

--
-- Dumping data for table 'KSTALLE'
--

INSERT INTO KSTALLE VALUES ('SS','9999','Project Mercury');

--
-- Table structure for table 'KTOPLAN'
--

DROP TABLE IF EXISTS KTOPLAN;
CREATE TABLE KTOPLAN (
  ARID char(2) NOT NULL default '',
  KTONR varchar(4) NOT NULL default '',
  BENAMNING varchar(100) default NULL,
  MANUELL enum('J','N') default 'J',
  MOMSKOD varchar(4) default NULL,
  SRUNR int(3) default NULL,
  KSTALLE varchar(4) default NULL,
  PROJEKT varchar(4) default NULL,
  SUBKTO varchar(4) default NULL,
  KTOPLAN varchar(15) default NULL,
  IB decimal(10,2) default NULL,
  UB decimal(10,2) default NULL,
  PRIMARY KEY  (KTONR,ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'KTOPLAN'
--

INSERT INTO KTOPLAN VALUES ('AC','1010','Kassa','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1020','Postgiro','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1040','Checkkonto','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1050','Bank','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1120','Aktier och andelar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1210','Kundfodringar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1230','Belånade kundfodringar (factoring)','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1310','Förutbetalda hyreskostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1330','Förutbetalda försäkringskostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1350','Upplupna hyresintäkter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1360','Upplupna ränteintäkter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1410','Fordringar hos anställda','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1430','Fordringar hos leverantörer','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1450','Skattefordringar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1470','Ingåendemervardesskatt (moms)','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1510','Lager','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1530','Produkter i arbete (PIA)','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1560','Förnödenheter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1580','Förskott till leverantörer','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1620','Aktier och andelar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1710','Patent','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1730','Goodwill','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1810','Arbetsmaskiner','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1819','Värdeminskning inventarier','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1820','Inventarier','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1840','Bilar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1849','Värdeminskning bilar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1910','Byggnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','1919','Värdeminskning byggnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2010','Skulder under indrivning','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2110','Leverantörsskulder','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2210','Skatteskulder','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2250','Skuld preliminärskatt','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2310','Upplupna löner','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2320','Upplupna semesterlöner','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2330','Upplupna sociala avgifter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2340','Upplupna räntekostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2410','Utgående mervärdesskatt (moms)','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2480','Mervärdesskatt, redovisningskonto','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2510','Personalens källskatt','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2530','Införsel','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2560','Fackföreningsavgifter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2590','Övriga löneavdrag','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2610','Förskott från kunder','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2620','Skulder till personal','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2630','Avräkning, factoring','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2640','Låneskulder','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2720','Checkkredit','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2790','Övriga långfristiga skulder','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2810','Lagerreserv','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2880','Obeskattade intäkter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','2910','Eget kapital','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','3010','Försäljning','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','3082','Bonus','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','3512','Försäljning skrot','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','3610','Fakturerat emballage','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','3640','Faktureringskostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','3770','Återvunna kundförluster','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','3780','Öresutjämning','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','3810','Hyresintäkter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','3910','Erhållna statliga bidrag','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','4010','Inköp av varor och material','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','4610','Legoarbeten','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','4910','Förändring lager','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','4930','Förändring av material i produktion (PIA)','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5010','Löner till personal','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5310','Löner till företagsledare','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5220','Löner till tjänstemän','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5340','Erssättning för måltidskostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5450','Kostnader för bil','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5520','Traktamenten vid tjänsteresa','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5530','Bilersättningar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5610','Lagstadgade arbetsgivaravgifter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5620','Egenavgifter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5630','Löneskatt','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5710','Pensionsförsäkringsavgifter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','5810','Utbildning','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6010','Lokalhyra','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6050','Elektricitet','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6070','Städning av lokaler','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6110','Hyra arbetsmaskiner','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6210','Elektricitet','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6230','Eldningsolja','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6260','Bensin mm','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6410','Förbrukningsinventarier','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6460','Förbrukningsmateriel','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6510','Kontorsmateriel','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6730','Redovisningskostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6740','ADB-tjänster','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6750','Konsultarvoden för speciella utredningar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6780','Advokatkostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6810','Telefon och telegram','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6830','Datakommunikation','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6850','Porto','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6911','Personbilar,drivmedel','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6912','Personbilar,försäkring och skatt','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6913','Personbilar,reparationer','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6915','Personbilar,leasing','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','6919','Personbilar,övrigt','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7010','Frakter,transporter mm','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7050','Resekostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7150','Försäljningsprovisioner','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7210','Annonsering','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7310','Företagsförsäkringar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7350','Kundförluster','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7410','Styrelsearvoden','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7620','Patentkostnader för egna patent','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7670','Tidningar,tidskrifter,facklitteratur','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7710','Vatten och avlopp','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7720','Bränsle','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7810','Resultat vid avyttring av maskiner och inventarier','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7815','Bokfört värde på maskiner och inventarier','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7911','Avskrivning av maskiner','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7912','Avskrivning av inventarier','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','7914','Avskrivning av bilar mm','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','8010','Utdelning på aktier och andelar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','8020','Ränteintäkter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','8050','Ränteintäkter på kundfodringar','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','8120','Räntekostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','8150','Räntekostnader för leverantörsskulder','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','8170','Bankkostnader','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','8910','Årets skattekostnad','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','8980','Egenavgifter','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AC','8999','Redovisat resultat','J','',0,'','','','BAS90',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1210','Maskiner','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1219','Ack avskrivningar maskiner','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1220','Inventarier','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1229','Ack avskrivningar inventarier','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1409','Beräknad förändring lager','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1510','Kundfordringar','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1613','Övriga förskott anställda','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1650','Momsfordran','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1710','Förutbetalda hyresutgifter','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1790','Övriga internfordringar','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1910','Kassa','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','1920','Postgiro','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2081','Aktiekapital','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2330','Checkräkningskredit','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2350','Banklån','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2440','Leverantörsskulder','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2611','Utgående moms','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2615','Utgående moms EU-förvärv','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2641','Ingående moms','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2645','Ingående moms utland','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2710','Källskatt (A-skatt)','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2920','Upplupna semesterlöner','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','2941','Upplupna arbetsgivaravgifter','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','3041','Försäljning Jonaid','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','3051','Försäljning Zuhaib','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','3960','Kursvinst rörelsen','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','3990','Övriga intäkter','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','4010','Materialkostnad','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','4056','Varuinköp EU','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','5010','Lokalhyra','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','5090','Övriga lokalkostnader','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','5830','Kost och logi','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','5900','Reklam och PR','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','6071','Representation, avdragsgill','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','6110','Kontorsmateriel','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','6200','Telefon och Post','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','6310','Företagsförsäkringar','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','6970','Tidningar, facklitteratur','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','6992','Övriga kostnader, ej avdragsgilla','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7010','Löner anställda','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7082','Semesterlön','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7221','Lön Yasar','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7231','Lön Anila','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7321','Skattefria traktamenten','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7331','Skattefri bilersättning','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7384','Arbetskläder','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7510','Arbetsgivaravgifter','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7570','AMF','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7620','Sjuk- och hälsovård','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7690','Övriga personalkostnader','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7831','Avskrivningar maskiner','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7832','Avskrivningar inventarier','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','7960','Kursförlust rörelsen','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','8400','Räntekostnader','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('AD','8490','Övriga finansiella kostnader','J','',0,'','','','EUBAS97',0.00,0.00);
INSERT INTO KTOPLAN VALUES ('SS','9999','Testkonto3','J','1',100,'2000','3000','4000','EUBAS97',0.00,0.00);

--
-- Table structure for table 'KUNDKATEGORI'
--

DROP TABLE IF EXISTS KUNDKATEGORI;
CREATE TABLE KUNDKATEGORI (
  KATEGORINR char(3) NOT NULL default '',
  BESKRIVNING varchar(40) NOT NULL default '',
  PRIMARY KEY  (KATEGORINR)
) TYPE=MyISAM;

--
-- Dumping data for table 'KUNDKATEGORI'
--

INSERT INTO KUNDKATEGORI VALUES ('003','Webbkund');
INSERT INTO KUNDKATEGORI VALUES ('001','Normalkund');

--
-- Table structure for table 'KUNDREG'
--

DROP TABLE IF EXISTS KUNDREG;
CREATE TABLE KUNDREG (
  KUNDNR varchar(10) NOT NULL default '',
  KUNDORGNR varchar(12) default NULL,
  NAMN varchar(60) NOT NULL default '',
  ADRESS varchar(30) default NULL,
  POSTNR varchar(6) default NULL,
  POSTADR varchar(30) default NULL,
  LAND varchar(30) default NULL,
  TFNNR varchar(15) default NULL,
  EMAILADR varchar(30) default NULL,
  FAXNR varchar(15) default NULL,
  ERREFERENT varchar(30) default NULL,
  ERREFTFNNR varchar(15) default NULL,
  ERREFEMAIL varchar(60) default NULL,
  SELJARE varchar(20) default NULL,
  FRITEXT varchar(100) default NULL,
  VALUTA char(3) default NULL,
  BETALVILLKOR char(3) default NULL,
  LEVVILLKOR char(3) default NULL,
  LEVSETT char(3) default NULL,
  DISTRIKT char(3) default NULL,
  KUNDKATEGORI char(3) default NULL,
  STDLEVPLATS char(3) default '001',
  ORDERERKENNANDE enum('J','N') default 'J',
  PLOCKLISTA enum('J','N') default 'J',
  FOLJESEDEL enum('J','N') default 'J',
  KRAVBREV enum('J','N') default 'J',
  SPRAKKOD char(3) default NULL,
  EXPAVGIFT enum('J','N') default 'J',
  FRAKTAVG enum('J','N') default 'J',
  KREDITLIMIT decimal(10,2) default NULL,
  KREDITDAGAR int(11) default NULL,
  KREDITKOD char(3) default NULL,
  EXPORTKOD char(3) default NULL,
  SKATTEKOD char(3) default NULL,
  RABATTKOD char(3) default NULL,
  DROJMALSRTA enum('J','N') default 'J',
  DROJMALSFAKTURA enum('J','N') default 'J',
  SAMLINGSFAKT enum('J','N') default 'J',
  SENASTEKRAVDATUM date default NULL,
  SKULD decimal(10,2) default NULL,
  ORDERSTOCK decimal(10,2) default NULL,
  PRIMARY KEY  (KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'KUNDREG'
--

INSERT INTO KUNDREG VALUES ('4376','[NULL]','Nya Test AB','Provgatan 2','199 99','LILLEBY','Sverige','09-999990','info@test.se','09-999999','Karl Andersson','09-999991','karl.a@test.se','Caroline Seljare','Fritt textfält','SEK','1','001','001','Kal','Sof','002','J','J','J','J','sv','J','J',2000.00,0,'[NU','[NU','[NU','[NU','J','J','J','0000-00-00',0.00,0.00);
INSERT INTO KUNDREG VALUES ('4377','[NULL]','Nya Kund AB','Provgatan 23','199 97','LILLEBY','Sverige','09-999190','info@kund.se','09-999199','Per Karlsson','09-999191','per.k@kund.se','Josef Seljare','Vår nya kund','SEK','1','001','001','Öre','Sof','001','J','J','J','J','sv','J','J',2000.00,0,'','011','001','001','J','J','J','0000-00-00',0.00,0.00);
INSERT INTO KUNDREG VALUES ('4378','[NULL]','Nya Storkund AB','Fina gatan 2','100 01','LYXBY','Sverige','09-109990','info@storkund.se','09-109999','Carl von Petersen','09-109991','c.p@storkund.se','Carolina Seljare','Detta är en stor kund','sv','SEK','001','1','LYX','001','001','J','J','J','N','J','J','J',0.00,45,'001','001','001','001','J','J','J','0000-00-00',0.00,0.00);
INSERT INTO KUNDREG VALUES ('4379','[NULL]','Nya Småkund AB','Myrstigen 32','199 02','SMÅSTAD','Sverige','09-129990','info@smakund.se','09-129999','Lillemor Andrén','09-129991','lillemor.a@smakund.se','Caroline Seljare','Den lilla kunden','SEK','1','001','001','Öre','Sft','002','J','J','J','J','sv','J','J',5000.00,30,'001','001','001','001','J','J','J','0000-00-00',0.00,0.00);
INSERT INTO KUNDREG VALUES ('4375',NULL,'Lilla Kunden Eftr AB','Bakgatan 1C','199 09','SMÅSTAD','Sverige','09-390000','info@lillakundeneftr.se','09-390009','Lillemor Andrén','09-390001','lillemor@lillakundeneftr.se','Lilleman Karlsson','Byte av företagsnamn Testföretaget','SEK','1','001','001','003','003','002','J','J','J','J','sv','J','J',13500.00,0,'001','001','001','001','J','J','J',NULL,NULL,NULL);

--
-- Table structure for table 'LAGERSTELLEREG'
--

DROP TABLE IF EXISTS LAGERSTELLEREG;
CREATE TABLE LAGERSTELLEREG (
  ARLAGST char(1) NOT NULL default '',
  ARTIKELNR varchar(30) NOT NULL default '',
  ARLAGHYLLA varchar(10) default NULL,
  ARLAGSALDO decimal(10,2) default NULL,
  ARINVGRP char(3) default NULL,
  ARABC char(2) default NULL,
  ARVALUTA char(3) default NULL,
  ARIPRIS decimal(10,2) default '0.00',
  ARIKVANT0 decimal(10,2) default '0.00',
  ARIKVANT1 decimal(10,2) default '0.00',
  ARIKVANT2 decimal(10,2) default '0.00',
  ARKALKPRIS decimal(10,2) default '0.00',
  ARPLANKPRIS decimal(10,2) default '0.00',
  ARFRYSTKPRIS decimal(10,2) default '0.00',
  ARBESTKVANT decimal(10,2) default '0.00',
  ARBESTPUNKT decimal(10,2) default '0.00',
  AROMKOST decimal(10,2) default '0.00',
  RESERVERAT decimal(10,2) default NULL,
  PRIMARY KEY  (ARTIKELNR,ARLAGST)
) TYPE=MyISAM;

--
-- Dumping data for table 'LAGERSTELLEREG'
--

INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1001','ABC002',103.00,'001','A','SEK',125.50,60.00,75.00,50.00,160.00,202.50,160.00,62.00,125.00,34.50,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1002','AAA001',126.00,'1','A','SEK',30.00,0.00,0.00,0.00,35.00,0.00,0.00,0.00,100.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1003','AAA001',75.00,'1','A','SEK',1.50,0.00,0.00,0.00,1.60,0.00,0.00,0.00,100.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1004','AAA001',10.00,'1','A','SEK',5.50,0.00,0.00,0.00,6.65,0.00,0.00,0.00,50.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1005','AAA002',27.00,'1','A','SEK',95.00,0.00,0.00,0.00,100.00,0.00,0.00,0.00,25.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1006','AAA002',536.00,'2','A','SEK',5.45,0.00,0.00,0.00,6.85,0.00,0.00,0.00,150.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1007','AAA003',243.00,'2','A','SEK',1.45,0.00,0.00,0.00,1.65,0.00,0.00,0.00,200.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1008','AAA003',263.00,'2','A','SEK',4.75,0.00,0.00,0.00,5.15,0.00,0.00,0.00,100.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1009','AAB001',458.00,'2','A','SEK',10.05,0.00,0.00,0.00,11.65,0.00,0.00,0.00,350.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1010','AAB001',27.00,'1','A','SEK',45.45,0.00,0.00,0.00,50.35,0.00,0.00,0.00,30.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1011','AAC001',11.00,'1','A','SEK',98.00,0.00,0.00,0.00,103.00,0.00,0.00,0.00,65.00,5.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1012','AAA004',34.00,'1','A','SEK',1.45,0.00,0.00,0.00,2.05,0.00,0.00,0.00,50.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1013','AAA005',32.00,'1','A','SEK',20.00,0.00,0.00,0.00,23.00,0.00,0.00,0.00,30.00,0.00,NULL);
INSERT INTO LAGERSTELLEREG VALUES ('1','1000-1014','AAB001',6.00,'2','A','SEK',55.00,0.00,0.00,0.00,70.00,0.00,0.00,0.00,10.00,0.00,NULL);

--
-- Table structure for table 'LEVREG'
--

DROP TABLE IF EXISTS LEVREG;
CREATE TABLE LEVREG (
  LEVNR varchar(10) NOT NULL default '',
  LEVORGNR varchar(12) default NULL,
  LEVNAMN varchar(30) NOT NULL default '',
  LEVADRESS varchar(30) default NULL,
  LEVPOSTNR varchar(6) default NULL,
  LEVPOSTADR varchar(30) default NULL,
  LEVLAND varchar(30) default NULL,
  LEVTFNNR varchar(15) default NULL,
  LEVFAXNR varchar(15) default NULL,
  LEVTELEX varchar(10) default NULL,
  LEVEMAIL varchar(30) default NULL,
  LEVPOSTGIRONR varchar(10) default NULL,
  LEVBANKGIRONR varchar(10) default NULL,
  LEVREFERENT varchar(20) default NULL,
  LEVREFTFN varchar(15) default NULL,
  LEVMOMSKOD char(1) default '1',
  LEVSKULD decimal(10,2) default NULL,
  LEVKONTO varchar(4) default NULL,
  LEVKUNDNR varchar(30) default NULL,
  LEVVALUTA char(3) default NULL,
  BETALVILKOR char(3) default NULL,
  PRIMARY KEY  (LEVNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVREG'
--

INSERT INTO LEVREG VALUES ('9999','666667-9997','Testleverantör AB','Delivery Street 1C','199 99','LEVSTAD','Sverige','09-919191','09-919192','88888','kundtj@testlev.se','5559998-8','5998-9998','Lars Andersson','09-919193','1',0.00,'2121','98765','SEK','1');
INSERT INTO LEVREG VALUES ('1000','','ICA Stjärnköp','','','MÄRSTA','','020-833333','','',' kundkontakt@ica.se','','','','','1',0.00,'','','SEK','1');
INSERT INTO LEVREG VALUES ('2001','','Carlsberg','','','','Sverige','020-788020','','','','','','','','1',0.00,'','','SEK','1');
INSERT INTO LEVREG VALUES ('123','559999-9999','Leverantör AB','Postgatan 33','199 99','DATABY','SVERIGE','09-999999','09-999998','99999','kundtj@leverantor.se','4559999-9','5999-9999','Per Josefsson','09-999997','1',0.00,'2440','12345678','SEK','2');
INSERT INTO LEVREG VALUES ('124','559988-9999','Distributör AB','Brevgatan 1A','199 99','DATABY','SVERIGE','09-999199','09-999198','19999','kundtj@distributor.se','4559988-9','5988-9999','Lena Bertils','09-999997','1',0.00,'2440','12345678','EUR','1');
INSERT INTO LEVREG VALUES ('125','559955-5599','Försäljning AB','Säljgatan 3','199 11','BY','Sverige','09-119910','09-119919','11119','info@forsaljning.se','454511-1','4545-1111','Karl Säljare','09-119915','1',0.00,'2110','98765','SEK','1');
INSERT INTO LEVREG VALUES ('126','550101-5555','Dataspecialisten AB','Storgatan 1','199 11','STORSTAD','Sverige','09-112250','09-112259','22229','info@dataspecialisten.se','4512323-3','4512-5566','Ola Norman','09-112255','1',0.00,'2110','567891','SEK','1');
INSERT INTO LEVREG VALUES ('100','559901-9991','Bokförlag AB','Bokgatan 1','198 01','BOKBY','Sverige','09-909090','09-909010','99991','kundtj@bokforlag.se','5599999-9','5900-2222','Linda Bokman','09-909011','1',0.00,'2110','33331','SEK','1');
INSERT INTO LEVREG VALUES ('200','559902-9992','Stora Bokförlaget AB','Förlagsgatan 11','198 02','FÖRLAGSSTAD','Sverige','09-919190','09-919111','22222','kundtj@storaforlag.se','559998-2','5900-3333','Philip King','09-919196','1',0.00,'2110','44440','SEK','1');
INSERT INTO LEVREG VALUES ('300','559899-5559','Lilla Förlaget HB','Bokgränd 23','198 03','BOKBY','Sverige','09-808080','09-808081','89992','Kundtj@lillaforlaget.se','558800-8','5900-4444','Kerstin Bokare','09-808089','1',0.00,'2110','55550','SEK','1');

--
-- Table structure for table 'LEVRESK'
--

DROP TABLE IF EXISTS LEVRESK;
CREATE TABLE LEVRESK (
  LEVNR varchar(10) NOT NULL default '',
  FAKTURANR varchar(20) NOT NULL default '',
  REGDATUM date default NULL,
  FAKTDATUM date default NULL,
  EXPIREDATUM date default NULL,
  FAKTTEXT varchar(100) default NULL,
  BAR char(2) default NULL,
  MOMSPROCENT decimal(3,2) default NULL,
  VALUTA char(3) default NULL,
  VALUTAKURS decimal(3,2) default NULL,
  VALUTABELOPP decimal(10,2) default NULL,
  LEVKTONR varchar(4) default NULL,
  FAKTBELOPP decimal(10,2) default NULL,
  MOMSKTONR varchar(4) default NULL,
  MOMSBELOPP decimal(10,2) default NULL,
  DEBETKONTONR varchar(4) default NULL,
  DEBETBELOPP decimal(10,2) default NULL,
  USERID varchar(8) default NULL,
  VERNR int(11) default NULL,
  BETALD enum('J','N') default 'N',
  BETALDDATUM date default NULL,
  OCRNR varchar(20) default NULL,
  PRIMARY KEY  (LEVNR,FAKTURANR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVRESK'
--

INSERT INTO LEVRESK VALUES ('123','1238866','2003-11-07','2003-11-04','2003-12-07','Inköp av bokhylla','AC',25.00,'SEK',1.00,1100.00,'2110',1100.00,'1470',275.00,'1810',825.00,'ADMIN',22,'N',NULL,'76598234');

--
-- Table structure for table 'LEVSETT'
--

DROP TABLE IF EXISTS LEVSETT;
CREATE TABLE LEVSETT (
  LEVSETTNR char(3) NOT NULL default '',
  LEVSETTTEXT varchar(150) NOT NULL default '',
  PRIMARY KEY  (LEVSETTNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVSETT'
--

INSERT INTO LEVSETT VALUES ('001','Schenker kundnr:11105232');
INSERT INTO LEVSETT VALUES ('002','ASG. Kundnr 111111');
INSERT INTO LEVSETT VALUES ('003','Post');

--
-- Table structure for table 'LEVVILLKOR'
--

DROP TABLE IF EXISTS LEVVILLKOR;
CREATE TABLE LEVVILLKOR (
  VILLKORSNR char(3) NOT NULL default '',
  VILLKORSTEXT varchar(150) NOT NULL default '',
  PRIMARY KEY  (VILLKORSNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'LEVVILLKOR'
--

INSERT INTO LEVVILLKOR VALUES ('001','EXW');
INSERT INTO LEVVILLKOR VALUES ('002','EYW');
INSERT INTO LEVVILLKOR VALUES ('003','');

--
-- Table structure for table 'ORDERRADREG'
--

DROP TABLE IF EXISTS ORDERRADREG;
CREATE TABLE ORDERRADREG (
  ORDERNR varchar(10) NOT NULL default '',
  ORDERRAD int(4) NOT NULL default '0',
  KUNDNR varchar(10) NOT NULL default '',
  RADORDERTYP enum('N','D') default 'N',
  ARTIKELNR varchar(30) NOT NULL default '',
  BENEMNING varchar(60) default NULL,
  LEVERANSVECKA varchar(5) default NULL,
  BESTELLT decimal(10,2) NOT NULL default '0.00',
  APRIS decimal(10,2) NOT NULL default '0.00',
  SUMMA decimal(10,2) NOT NULL default '0.00',
  MOMSKR decimal(10,2) NOT NULL default '0.00',
  LEVERERAT decimal(10,2) default NULL,
  RESTNOTERAT decimal(10,2) default NULL,
  RADRABATT decimal(2,1) default NULL,
  KALKYLPRIS decimal(10,2) default NULL,
  LEVDATUM date default NULL,
  ENHET varchar(4) default 'ST',
  PRIMARY KEY  (ORDERNR,ORDERRAD)
) TYPE=MyISAM;

--
-- Dumping data for table 'ORDERRADREG'
--


--
-- Table structure for table 'ORDERREG'
--

DROP TABLE IF EXISTS ORDERREG;
CREATE TABLE ORDERREG (
  ORDERNR varchar(10) NOT NULL default '',
  KUNDNR varchar(10) NOT NULL default '',
  ORDERTYP enum('N','D','E','F') default 'N',
  ORDERSTATUS enum('A','N','F','B') default 'A',
  ORDERDATUM date default NULL,
  LEVDATUM date default NULL,
  KUNDNAMN varchar(60) default NULL,
  KUNDADRESS varchar(30) default NULL,
  KUNDPOSTNR varchar(6) default NULL,
  KUNDPOSTADR varchar(30) default NULL,
  KUNDLAND varchar(30) default NULL,
  ERREF varchar(20) default NULL,
  LEVADRESS varchar(30) default NULL,
  LEVPOSTNR varchar(6) default NULL,
  LEVPOSTADR varchar(30) default NULL,
  LEVLAND varchar(30) default NULL,
  VARREF varchar(20) default NULL,
  SELJARE varchar(20) default NULL,
  GODSMERKE varchar(100) default NULL,
  BETVILLKTYP enum('F','P','K') NOT NULL default 'F',
  BETVILLKOR char(3) default '001',
  LEVVILLKOR char(3) default '001',
  LEVSETT char(3) default '001',
  PLOCKLISTA enum('J','N') default 'J',
  FOLJESEDEL enum('J','N') default 'J',
  FRAKTAVG enum('J','N') default 'J',
  SKATTEKOD char(3) NOT NULL default '001',
  MOMS decimal(3,2) default NULL,
  VALUTA char(3) default 'SEK',
  EXPORTKOD char(3) default '001',
  SPRAKKOD char(3) default 'sv',
  ORDERSUMMA decimal(10,2) default NULL,
  FRAKTSUMMA decimal(10,2) default NULL,
  FRAKTMOMSKR decimal(10,2) default NULL,
  ORDERMOMS decimal(10,2) default NULL,
  ORDERTOTAL decimal(10,2) default NULL,
  PRIMARY KEY  (ORDERNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'ORDERREG'
--


--
-- Table structure for table 'PASSW'
--

DROP TABLE IF EXISTS PASSW;
CREATE TABLE PASSW (
  KUNDNR varchar(10) NOT NULL default '',
  PASSW varchar(16) NOT NULL default '',
  PRIMARY KEY  (KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'PASSW'
--

INSERT INTO PASSW VALUES ('4376','webbson');
INSERT INTO PASSW VALUES ('4375','webbman');

--
-- Table structure for table 'PLOCKLISTEREG'
--

DROP TABLE IF EXISTS PLOCKLISTEREG;
CREATE TABLE PLOCKLISTEREG (
  PLOCKNR int(11) NOT NULL auto_increment,
  ORDERNR varchar(10) NOT NULL default '',
  ORDERRAD int(4) NOT NULL default '0',
  KUNDNR varchar(10) NOT NULL default '',
  ARTIKELNR varchar(30) NOT NULL default '',
  BENEMNING varchar(60) default NULL,
  LEVERANSVECKA varchar(5) default NULL,
  BESTELLT decimal(10,2) NOT NULL default '0.00',
  ATTLEVERERA decimal(10,2) NOT NULL default '0.00',
  LEVERERAT decimal(10,2) NOT NULL default '0.00',
  PLOCKAT decimal(10,2) NOT NULL default '0.00',
  RESTNOTERAT decimal(10,2) NOT NULL default '0.00',
  LEVDATUM date default NULL,
  ENHET varchar(4) default NULL,
  PLOCKSTATUS enum('P','B') default 'P',
  PLOCKDATUM date NOT NULL default '0000-00-00',
  PRIMARY KEY  (PLOCKNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'PLOCKLISTEREG'
--


--
-- Table structure for table 'PRODUKTGRUPP'
--

DROP TABLE IF EXISTS PRODUKTGRUPP;
CREATE TABLE PRODUKTGRUPP (
  PRODKLASS varchar(5) NOT NULL default '',
  BESKRIVNING varchar(30) default NULL,
  MOMSKOD varchar(5) default NULL,
  PRIMARY KEY  (PRODKLASS)
) TYPE=MyISAM;

--
-- Dumping data for table 'PRODUKTGRUPP'
--

INSERT INTO PRODUKTGRUPP VALUES ('2200','Hårddiskar','MOMS1');
INSERT INTO PRODUKTGRUPP VALUES ('2500','Bildskärmar','MOMS1');
INSERT INTO PRODUKTGRUPP VALUES ('2300','Tangentbord','MOMS1');
INSERT INTO PRODUKTGRUPP VALUES ('2400','Routers','MOMS1');
INSERT INTO PRODUKTGRUPP VALUES ('2100','Switchar','MOMS1');
INSERT INTO PRODUKTGRUPP VALUES ('1001','C++-programmering','MOMS3');
INSERT INTO PRODUKTGRUPP VALUES ('1002','Qt-böcker','MOMS3');
INSERT INTO PRODUKTGRUPP VALUES ('1003','C-programmering','MOMS3');

--
-- Table structure for table 'PROGRAM'
--

DROP TABLE IF EXISTS PROGRAM;
CREATE TABLE PROGRAM (
  PRGNR char(3) NOT NULL default '',
  MENYAVD varchar(20) default NULL,
  MENYGRP varchar(30) default NULL,
  MENYTXT varchar(30) default NULL,
  PROGRAM varchar(8) default NULL,
  PRIMARY KEY  (PRGNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'PROGRAM'
--

INSERT INTO PROGRAM VALUES ('001','Administration','Användaradministration','Ny användare','ADDUSRW');
INSERT INTO PROGRAM VALUES ('002','Administration','Användaradministration','Ändra användarinfo','CHGUSRW');
INSERT INTO PROGRAM VALUES ('003','Administration','Användaradministration','Ta bort användare','DELUSRW');
INSERT INTO PROGRAM VALUES ('004','Administration','Användaradministration','Visa en användare','DSPUSRW');
INSERT INTO PROGRAM VALUES ('005','Administration','Användaradministration','Lista användare','LSTUSRW');
INSERT INTO PROGRAM VALUES ('006','Administration','Behörighetsadministration','Ny behörighet','ADDRGTW');
INSERT INTO PROGRAM VALUES ('007','Administration','Behörighetsadministration','Ändra behörighet','');
INSERT INTO PROGRAM VALUES ('008','Administration','Behörighetsadministration','Ta bort behörighet','DELRGTW');
INSERT INTO PROGRAM VALUES ('009','Administration','Behörighetsadministration','Visa behörighet','');
INSERT INTO PROGRAM VALUES ('010','Administration','Behörighetsadministration','Lista behörigheter','LSTRGTW');
INSERT INTO PROGRAM VALUES ('011','Administration','Funktionsadministration','Ny funktion','ADDFNCW');
INSERT INTO PROGRAM VALUES ('012','Administration','Funktionsadministration','Lista funktioner','LSTFNCW');
INSERT INTO PROGRAM VALUES ('013','Ekonomi','Bokföring','Registrera verifikation','');
INSERT INTO PROGRAM VALUES ('014','Ekonomi','Bokföring','Registrera ver. standard','BOKFORSW');
INSERT INTO PROGRAM VALUES ('015','Ekonomi','Kontoadministration','Nytt konto','ADDKTOW');
INSERT INTO PROGRAM VALUES ('016','Ekonomi','Kontoadministration','Ändra konto','CHGKTOW');
INSERT INTO PROGRAM VALUES ('017','Ekonomi','Kontoadministration','Ta bort konto','');
INSERT INTO PROGRAM VALUES ('018','Ekonomi','Kontoadministration','Visa konto','DSPKTOW');
INSERT INTO PROGRAM VALUES ('019','Ekonomi','Kontoadministration','Lista konton','LSTKTOW');
INSERT INTO PROGRAM VALUES ('020','Ekonomi','Kostnadställeadministration','Nytt kostnadställe','ADDKSTW');
INSERT INTO PROGRAM VALUES ('021','Ekonomi','Kostnadställeadministration','Ändra kostnadställe','');
INSERT INTO PROGRAM VALUES ('022','Ekonomi','Kostnadställeadministration','Ta bort kostnadställe','');
INSERT INTO PROGRAM VALUES ('023','Ekonomi','Kostnadställeadministration','Visa ett kostnadsställe','DSPKSTW');
INSERT INTO PROGRAM VALUES ('024','Ekonomi','Kostnadställeadministration','Lista kostnadsställen','LSTKSTW');
INSERT INTO PROGRAM VALUES ('025','Ekonomi','Valutaadministration','Ny valuta','ADDVALW');
INSERT INTO PROGRAM VALUES ('026','Ekonomi','Valutaadministration','Ändra valuta','CHGVALW');
INSERT INTO PROGRAM VALUES ('027','Ekonomi','Valutaadministration','Ta bort valuta','DELVALW');
INSERT INTO PROGRAM VALUES ('028','Ekonomi','Valutaadministration','Visa valuta','DSPVALW');
INSERT INTO PROGRAM VALUES ('029','Ekonomi','Valutaadministration','Lista valutor','LSTVALW');
INSERT INTO PROGRAM VALUES ('030','Ekonomi','Rapporter','Kontorapport','RPTKTOW');
INSERT INTO PROGRAM VALUES ('031','Ekonomi','Rapporter','Rapportgenerator','RPTGENW');
INSERT INTO PROGRAM VALUES ('032','Ekonomi','Räkenskapsår','Nytt bokföringsår','ADDBARW');
INSERT INTO PROGRAM VALUES ('033','Ekonomi','Räkenskapsår','Ändra bokföringsårsdata','CHGBARW');
INSERT INTO PROGRAM VALUES ('034','Administration','Företagsdata','Ny post','ADDFTGW');
INSERT INTO PROGRAM VALUES ('035','Administration','Företagsdata','Ändra post','CHGFTGW');
INSERT INTO PROGRAM VALUES ('036','Administration','Företagsdata','Visa företagsdata','DSPFTGW');
INSERT INTO PROGRAM VALUES ('037','Försäljning','Kunddata','Ny kund','ADDKUW');
INSERT INTO PROGRAM VALUES ('038','Försäljning','Kunddata','Ny leveransadress för kund','ADDLEVPW');
INSERT INTO PROGRAM VALUES ('039','Inköp','Leverantörsdata','Ny leverantör','ADDLEVW');
INSERT INTO PROGRAM VALUES ('040','Inköp','Leverantörsdata','Visa en leverantör','DSPLEVW');
INSERT INTO PROGRAM VALUES ('041','Inköp','Leverantörsdata','Ändra leverantörsdata','CHGLEVW');
INSERT INTO PROGRAM VALUES ('042','Ekonomi','Bokföring','Reg. leverantörsfaktura','LEVFAKTW');
INSERT INTO PROGRAM VALUES ('043','Ekonomi','Rapporter','Leverantörsreskontra','LEVRESKW');
INSERT INTO PROGRAM VALUES ('044','Ekonomi','Rapporter','Förfallna levfakturor','ATTBETW');
INSERT INTO PROGRAM VALUES ('045','Ekonomi','Rapporter','Saldolista','SDOLISW');
INSERT INTO PROGRAM VALUES ('046','Försäljning','Kunddata','Visa kunddata','DSPKUW');
INSERT INTO PROGRAM VALUES ('047','Försäljning','Kunddata','Ändra kunddata','CHGKUW');
INSERT INTO PROGRAM VALUES ('048','Försäljning','Kunddata','Lista kunder','LSTKUW');
INSERT INTO PROGRAM VALUES ('049','Administration','Företagsdata','Byta företag','BYTFTGW');
INSERT INTO PROGRAM VALUES ('050','Materialhantering','Artikeldata','Ny artikel','ADDARW');
INSERT INTO PROGRAM VALUES ('051','Materialhantering','Artikeldata','Visa grunddata för en artikel','DSPARW');
INSERT INTO PROGRAM VALUES ('052','Materialhantering','Artikeldata','Visa en artikels ekonomidata','DSPAREW');
INSERT INTO PROGRAM VALUES ('053','Materialhantering','Artikeldata','Ändra artikeldata','CHGARW');
INSERT INTO PROGRAM VALUES ('054','Administration','Betalningsvillkor','Lista betalningsvillkor','LSTBETVW');
INSERT INTO PROGRAM VALUES ('055','Administration','Betalningsvillkor','Nya betalningsvillkor','ADDBETVW');
INSERT INTO PROGRAM VALUES ('056','Materialhantering','Artikeldata','Lista artiklar','LSTARW');
INSERT INTO PROGRAM VALUES ('057','Administration','Betalningsvillkor','Ändra betalningsvillkor','CHGBETVW');
INSERT INTO PROGRAM VALUES ('058','Inköp','Beställningar','Registrera inköpsorder','ADDINKW');
INSERT INTO PROGRAM VALUES ('059','Inköp','Beställningar','(Ändra beställning)','CHGINKW');
INSERT INTO PROGRAM VALUES ('060','Inköp','Beställningar','(Annulera beställning)','DELINKW');
INSERT INTO PROGRAM VALUES ('061','Inköp','Beställningar','Visa beställning','DSPINKW');
INSERT INTO PROGRAM VALUES ('062','Inköp','Beställningar','Beställningsstock','LSTINKW');
INSERT INTO PROGRAM VALUES ('063','Inköp','Beställningar','Skriv ut beställning','PRTINKW');
INSERT INTO PROGRAM VALUES ('064','Inköp','Beställningar','(Avprickning följesedel)','UPDINKW');
INSERT INTO PROGRAM VALUES ('065','Försäljning','Kundorder','Registrera kundorder','ADDORDW');
INSERT INTO PROGRAM VALUES ('066','Försäljning','Kundorder','(Ändra kundorder)','CHGORDW');
INSERT INTO PROGRAM VALUES ('067','Försäljning','Kundorder','(Makulera kundorder)','DELORDW');
INSERT INTO PROGRAM VALUES ('068','Försäljning','Kundorder','Visa en kundorder','DSPORDW');
INSERT INTO PROGRAM VALUES ('069','Försäljning','Kundorder','Lista kundorder','LSTORDW');
INSERT INTO PROGRAM VALUES ('070','Försäljning','Kundorder','Skriva ut plocklista','PLORDW');
INSERT INTO PROGRAM VALUES ('071','Försäljning','Kundorder','(Skriva ut följesedel)','FSORDW');
INSERT INTO PROGRAM VALUES ('072','Försäljning','Kundorder','(Skriva ut faktura)','FAKTORDW');
INSERT INTO PROGRAM VALUES ('074','Administration','Företagsdata','Ny text i textregistret','ADDTXTW');
INSERT INTO PROGRAM VALUES ('073','Inköp','Leverantörsdata','Lista leverantörer','LSTLEVW');
INSERT INTO PROGRAM VALUES ('076','Administration','Leveransvillkor','Nya leveransvillkor','ADDLEVVW');
INSERT INTO PROGRAM VALUES ('075','Administration','Företagsdata','Radera post i textregistret','DELTXTW');
INSERT INTO PROGRAM VALUES ('077','Administration','Leveransvillkor','Lista leveransvillkor','LSTLEVVW');
INSERT INTO PROGRAM VALUES ('078','Administration','Leveranssätt','Nya leveranssätt','ADDLEVSW');
INSERT INTO PROGRAM VALUES ('079','Administration','Leveranssätt','Lista leveranssätt','LSTLEVSW');
INSERT INTO PROGRAM VALUES ('080','Ekonomi','Rapporter','Balansräkning','BALRPTW');
INSERT INTO PROGRAM VALUES ('081','Ekonomi','Rapporter','Huvudbok','HUVBOKW');
INSERT INTO PROGRAM VALUES ('082','Ekonomi','Rapporter','Dagbok','DAGBOKW');
INSERT INTO PROGRAM VALUES ('083','Försäljning','Kunddata','Lista kunders leveransplatser','LSTLEVPW');
INSERT INTO PROGRAM VALUES ('084','Administration','Företagsdata','Ny databasregistrering','ADDFORW');
INSERT INTO PROGRAM VALUES ('085','Administration','Företagsdata','Lista databaser','LSTFORW');
INSERT INTO PROGRAM VALUES ('086','Materialhantering','Artikeladmin.','Ny produktklass/produktgrupp','ADDPKDW');
INSERT INTO PROGRAM VALUES ('087','Materialhantering','Artikeladmin.','Lista produktklass/produktgrup','LSTPKDW');
INSERT INTO PROGRAM VALUES ('088','Ekonomi','Räkenskapsår','Visa bokföringsår','DSPBARW');
INSERT INTO PROGRAM VALUES ('089','Administration','Företagsdata','Lista företagsdata','LSTFTGW');
INSERT INTO PROGRAM VALUES ('090','Ekonomi','Rapporter','Resultatrapport','RESRPTW');
INSERT INTO PROGRAM VALUES ('091','Ekonomi','Räkenskapsår','Lista alla räkenskapsår','LSTBARW');
INSERT INTO PROGRAM VALUES ('092','Försäljning','Kunddata','Söka kunder','SRCHKUW');
INSERT INTO PROGRAM VALUES ('093','Ekonomi','Rapporter','Skapa SIE-fil','RPTSIEW');
INSERT INTO PROGRAM VALUES ('094','Försäljning','Kundorder','Pricka av plocklista','PLCHGW');

--
-- Table structure for table 'RIGHTS'
--

DROP TABLE IF EXISTS RIGHTS;
CREATE TABLE RIGHTS (
  USERID varchar(8) NOT NULL default '',
  TRNSID varchar(8) NOT NULL default '',
  PRIMARY KEY  (USERID,TRNSID)
) TYPE=MyISAM;

--
-- Dumping data for table 'RIGHTS'
--

INSERT INTO RIGHTS VALUES ('GUEST','ARLIS');
INSERT INTO RIGHTS VALUES ('GUEST','ARLSPK');
INSERT INTO RIGHTS VALUES ('GUEST','ARLST');
INSERT INTO RIGHTS VALUES ('GUEST','ARLSTL');
INSERT INTO RIGHTS VALUES ('GUEST','VALDSP');
INSERT INTO RIGHTS VALUES ('GUEST','VALLST');
INSERT INTO RIGHTS VALUES ('GUEST','WKUDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDARW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDBARW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDBETVW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDFNCW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDFORW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDFTGW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDINKW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDKSTW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDKTOW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDKUW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDLEVPW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDLEVSW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDLEVVW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDLEVW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDORDW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDPKDW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDRGTW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDTXTW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDUSRW');
INSERT INTO RIGHTS VALUES ('ADMIN','ADDVALW');
INSERT INTO RIGHTS VALUES ('ADMIN','AR2ADD');
INSERT INTO RIGHTS VALUES ('ADMIN','ARADD');
INSERT INTO RIGHTS VALUES ('ADMIN','ARCHG');
INSERT INTO RIGHTS VALUES ('ADMIN','ARCHGL');
INSERT INTO RIGHTS VALUES ('ADMIN','ARCHK');
INSERT INTO RIGHTS VALUES ('ADMIN','ARDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','ARDSPL');
INSERT INTO RIGHTS VALUES ('ADMIN','ARLST');
INSERT INTO RIGHTS VALUES ('ADMIN','ATTBET');
INSERT INTO RIGHTS VALUES ('ADMIN','ATTBETW');
INSERT INTO RIGHTS VALUES ('ADMIN','BALRPTW');
INSERT INTO RIGHTS VALUES ('ADMIN','BARADD');
INSERT INTO RIGHTS VALUES ('ADMIN','BARCHG');
INSERT INTO RIGHTS VALUES ('ADMIN','BARCHK');
INSERT INTO RIGHTS VALUES ('ADMIN','BARDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','BARFND');
INSERT INTO RIGHTS VALUES ('ADMIN','BETADD');
INSERT INTO RIGHTS VALUES ('ADMIN','BETCHG');
INSERT INTO RIGHTS VALUES ('ADMIN','BETDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','BETLST');
INSERT INTO RIGHTS VALUES ('ADMIN','BOKF');
INSERT INTO RIGHTS VALUES ('ADMIN','BOKFORSW');
INSERT INTO RIGHTS VALUES ('ADMIN','BOKFORW');
INSERT INTO RIGHTS VALUES ('ADMIN','BYTFTGW');
INSERT INTO RIGHTS VALUES ('ADMIN','CHGARW');
INSERT INTO RIGHTS VALUES ('ADMIN','CHGBARW');
INSERT INTO RIGHTS VALUES ('ADMIN','CHGBETVW');
INSERT INTO RIGHTS VALUES ('ADMIN','CHGFTGW');
INSERT INTO RIGHTS VALUES ('ADMIN','CHGKUW');
INSERT INTO RIGHTS VALUES ('ADMIN','CHGLEVW');
INSERT INTO RIGHTS VALUES ('ADMIN','CHGUSRW');
INSERT INTO RIGHTS VALUES ('ADMIN','CHGVALW');
INSERT INTO RIGHTS VALUES ('ADMIN','DAGBOKW');
INSERT INTO RIGHTS VALUES ('ADMIN','DBCHK');
INSERT INTO RIGHTS VALUES ('ADMIN','DBOKRPT');
INSERT INTO RIGHTS VALUES ('ADMIN','DELRGTW');
INSERT INTO RIGHTS VALUES ('ADMIN','DELTXTW');
INSERT INTO RIGHTS VALUES ('ADMIN','DELUSRW');
INSERT INTO RIGHTS VALUES ('ADMIN','DELVALW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPAREW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPARW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPBARW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPFTGW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPINKW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPKSTW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPKTOW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPKUW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPLEVVW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPLEVW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPUSRW');
INSERT INTO RIGHTS VALUES ('ADMIN','DSPVALW');
INSERT INTO RIGHTS VALUES ('ADMIN','FORADD');
INSERT INTO RIGHTS VALUES ('ADMIN','FORCHK');
INSERT INTO RIGHTS VALUES ('ADMIN','FORDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','FORLST');
INSERT INTO RIGHTS VALUES ('ADMIN','FTGDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','FTGLIS');
INSERT INTO RIGHTS VALUES ('ADMIN','FTGLST');
INSERT INTO RIGHTS VALUES ('ADMIN','FTGUPD');
INSERT INTO RIGHTS VALUES ('ADMIN','HBOKRPT');
INSERT INTO RIGHTS VALUES ('ADMIN','HUVBOKW');
INSERT INTO RIGHTS VALUES ('ADMIN','INKADD');
INSERT INTO RIGHTS VALUES ('ADMIN','INKHDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','INKLST');
INSERT INTO RIGHTS VALUES ('ADMIN','INKRADD');
INSERT INTO RIGHTS VALUES ('ADMIN','INKRLST');
INSERT INTO RIGHTS VALUES ('ADMIN','KSTADD');
INSERT INTO RIGHTS VALUES ('ADMIN','KSTCHK');
INSERT INTO RIGHTS VALUES ('ADMIN','KSTDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','KSTLST');
INSERT INTO RIGHTS VALUES ('ADMIN','KTOADD');
INSERT INTO RIGHTS VALUES ('ADMIN','KTOCHG');
INSERT INTO RIGHTS VALUES ('ADMIN','KTOCHK');
INSERT INTO RIGHTS VALUES ('ADMIN','KTODSP');
INSERT INTO RIGHTS VALUES ('ADMIN','KTORPT');
INSERT INTO RIGHTS VALUES ('ADMIN','KTORPT2');
INSERT INTO RIGHTS VALUES ('ADMIN','KTOVIEW');
INSERT INTO RIGHTS VALUES ('ADMIN','KUADD');
INSERT INTO RIGHTS VALUES ('ADMIN','KUCHG');
INSERT INTO RIGHTS VALUES ('ADMIN','KUCHK');
INSERT INTO RIGHTS VALUES ('ADMIN','KUDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','KULST');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVADD');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVCHG');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVFAKTW');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVLST');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVPLST');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVRESKW');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVSADD');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVSDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVSLST');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVVADD');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVVDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','LEVVLST');
INSERT INTO RIGHTS VALUES ('ADMIN','LRESADD');
INSERT INTO RIGHTS VALUES ('ADMIN','LRESRPT');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTARW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTBETVW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTFNCW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTFORW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTFTGW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTINKW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTKSTW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTKTOW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTKUW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTLEVPW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTLEVSW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTLEVVW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTLEVW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTORDW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTPKDW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTRGTW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTUSRW');
INSERT INTO RIGHTS VALUES ('ADMIN','LSTVALW');
INSERT INTO RIGHTS VALUES ('ADMIN','ORDLST2');
INSERT INTO RIGHTS VALUES ('ADMIN','PKDADD');
INSERT INTO RIGHTS VALUES ('ADMIN','PKDLST');
INSERT INTO RIGHTS VALUES ('ADMIN','PRGLST');
INSERT INTO RIGHTS VALUES ('ADMIN','PRTINKW');
INSERT INTO RIGHTS VALUES ('ADMIN','RESRPTW');
INSERT INTO RIGHTS VALUES ('ADMIN','RGTADD');
INSERT INTO RIGHTS VALUES ('ADMIN','RGTCHK');
INSERT INTO RIGHTS VALUES ('ADMIN','RGTDEL');
INSERT INTO RIGHTS VALUES ('ADMIN','RGTDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','RGTLST');
INSERT INTO RIGHTS VALUES ('ADMIN','RPTCRE');
INSERT INTO RIGHTS VALUES ('ADMIN','RPTGENW');
INSERT INTO RIGHTS VALUES ('ADMIN','RPTKTOW');
INSERT INTO RIGHTS VALUES ('ADMIN','SDOLISW');
INSERT INTO RIGHTS VALUES ('ADMIN','SLPADD');
INSERT INTO RIGHTS VALUES ('ADMIN','TRNSADD');
INSERT INTO RIGHTS VALUES ('ADMIN','TRNSLST');
INSERT INTO RIGHTS VALUES ('ADMIN','TXTADD');
INSERT INTO RIGHTS VALUES ('ADMIN','TXTDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','USERADD');
INSERT INTO RIGHTS VALUES ('ADMIN','USERCHG');
INSERT INTO RIGHTS VALUES ('ADMIN','USERDEL');
INSERT INTO RIGHTS VALUES ('ADMIN','USERDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','USERLST');
INSERT INTO RIGHTS VALUES ('ADMIN','VALADD');
INSERT INTO RIGHTS VALUES ('ADMIN','VALCHG');
INSERT INTO RIGHTS VALUES ('ADMIN','VALDEL');
INSERT INTO RIGHTS VALUES ('ADMIN','VALDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','VALLST');
INSERT INTO RIGHTS VALUES ('ADMIN','VERHDSP');
INSERT INTO RIGHTS VALUES ('ADMIN','VERHLST');
INSERT INTO RIGHTS VALUES ('ADMIN','VERUPD');
INSERT INTO RIGHTS VALUES ('JAPI','TSTFNC');
INSERT INTO RIGHTS VALUES ('OLFIX','ADDRGTW');
INSERT INTO RIGHTS VALUES ('OLFIX','ARICHK');
INSERT INTO RIGHTS VALUES ('OLFIX','BARDSP');
INSERT INTO RIGHTS VALUES ('OLFIX','KTOCHK');
INSERT INTO RIGHTS VALUES ('OLFIX','KTOLST');
INSERT INTO RIGHTS VALUES ('OLFIX','KTOVIEW');
INSERT INTO RIGHTS VALUES ('OLFIX','PRGLST');
INSERT INTO RIGHTS VALUES ('OLFIX','RGTADD');
INSERT INTO RIGHTS VALUES ('OLFIX','RGTCHK');
INSERT INTO RIGHTS VALUES ('OLFIX','RGTDEL');
INSERT INTO RIGHTS VALUES ('OLFIX','RGTLST');
INSERT INTO RIGHTS VALUES ('OLFIX','TRHDADD');
INSERT INTO RIGHTS VALUES ('OLFIX','TRNSADD');
INSERT INTO RIGHTS VALUES ('OLFIX','TRNSDEL');
INSERT INTO RIGHTS VALUES ('OLFIX','USERADD');
INSERT INTO RIGHTS VALUES ('OLFIX','USERLST');
INSERT INTO RIGHTS VALUES ('OLFIX','VERUPD');
INSERT INTO RIGHTS VALUES ('TESTARE','KUCHK');
INSERT INTO RIGHTS VALUES ('TESTARE','LSTUSRW');
INSERT INTO RIGHTS VALUES ('TESTARE','PRGLST');
INSERT INTO RIGHTS VALUES ('TESTARE','RGTCHK');
INSERT INTO RIGHTS VALUES ('TESTARE','USERADD');
INSERT INTO RIGHTS VALUES ('TESTARE','USERDSP');
INSERT INTO RIGHTS VALUES ('TESTARE','USERLST');

--
-- Table structure for table 'STDLEVPLATS'
--

DROP TABLE IF EXISTS STDLEVPLATS;
CREATE TABLE STDLEVPLATS (
  STDLEVPLATS char(3) NOT NULL default '',
  KUNDNR varchar(10) NOT NULL default '',
  ADRESS varchar(30) NOT NULL default '',
  POSTNR varchar(6) NOT NULL default '',
  POSTADR varchar(30) NOT NULL default '',
  LAND varchar(30) default NULL,
  PRIMARY KEY  (STDLEVPLATS,KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'STDLEVPLATS'
--

INSERT INTO STDLEVPLATS VALUES ('002','4375','Bakgatan 1D','199 09','SMÅSTAD','-');
INSERT INTO STDLEVPLATS VALUES ('001','4375','Bakgatan 1C','199 09','SMÅSTAD','Sverige');
INSERT INTO STDLEVPLATS VALUES ('555','4375','Testgatan 3','199 02','PROVSTAD','Sverige');
INSERT INTO STDLEVPLATS VALUES ('001','4376','Industrigatan 13','199 21','LILLEBY','Sverige');
INSERT INTO STDLEVPLATS VALUES ('002','4376','Bokhållargatan 3','199 19','LILLEBY','Sverige');

--
-- Table structure for table 'TEXTREG'
--

DROP TABLE IF EXISTS TEXTREG;
CREATE TABLE TEXTREG (
  TEXTNR char(3) NOT NULL default '',
  TXT text,
  PRIMARY KEY  (TEXTNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'TEXTREG'
--

INSERT INTO TEXTREG VALUES ('002','Endast komplett order får levereras.\nLeverans ska ske med Danzas/ASG.\nVårt kundnr hos Danzas/ASG är 991145.');
INSERT INTO TEXTREG VALUES ('003','Detta är ytterligare ett test med textregistret.\nMed radnr 2.\nOch med rad nr 3.\n');
INSERT INTO TEXTREG VALUES ('001','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.\n');

--
-- Table structure for table 'TRANSID'
--

DROP TABLE IF EXISTS TRANSID;
CREATE TABLE TRANSID (
  TRNSID varchar(8) NOT NULL default '',
  TRNSTXT varchar(60) default NULL,
  PRIMARY KEY  (TRNSID)
) TYPE=MyISAM;

--
-- Dumping data for table 'TRANSID'
--

INSERT INTO TRANSID VALUES ('ARICHK','Kontrollera om visst bokföringsår finns');
INSERT INTO TRANSID VALUES ('BARDSP','Hämta data för angivet bokföringsår');
INSERT INTO TRANSID VALUES ('BARCHK','Kontrollera om visst bokföringsår finns');
INSERT INTO TRANSID VALUES ('BOKF','Bokföringsprogram');
INSERT INTO TRANSID VALUES ('FORDSP','Visa info om databas nr x');
INSERT INTO TRANSID VALUES ('FTGUPD','Uppdatera företagsdata');
INSERT INTO TRANSID VALUES ('KSTADD','Nyupplägg av kostnadsställe');
INSERT INTO TRANSID VALUES ('KSTCHK','Kontrollera om visst kostnadställe finns');
INSERT INTO TRANSID VALUES ('KSTDSP','Visa info för ett kostnadställe');
INSERT INTO TRANSID VALUES ('KSTLST','Lista kostnadsställen på skärm');
INSERT INTO TRANSID VALUES ('KTOADD','Lägga till en ny post i konto');
INSERT INTO TRANSID VALUES ('KTOCHG','Ändra info för ett kontonr');
INSERT INTO TRANSID VALUES ('KTOCHK','Kontrollera om visst konto finns');
INSERT INTO TRANSID VALUES ('KTODEL','Ta bort post i konto (endast utan transaktioner)');
INSERT INTO TRANSID VALUES ('KTODSP','Visa info på ett konto');
INSERT INTO TRANSID VALUES ('KTOLST','Lista alla konton, nr och text');
INSERT INTO TRANSID VALUES ('KTORPT','Lista alla poster i tabellen VERRAD');
INSERT INTO TRANSID VALUES ('KTOUPD','Uppdatera konto med antingen debet eller kredit');
INSERT INTO TRANSID VALUES ('KTOVIEW','Visa kontonr och benämning på skärm');
INSERT INTO TRANSID VALUES ('PRGLST','Lista program');
INSERT INTO TRANSID VALUES ('RGTADD','Lägga till behörighet till transaktioner');
INSERT INTO TRANSID VALUES ('RGTCHK','Kontrolera användares behörighet');
INSERT INTO TRANSID VALUES ('RGTDEL','Ta bort behörighet till transaktioner');
INSERT INTO TRANSID VALUES ('RGTDSP','Visa behörigheter för en användare');
INSERT INTO TRANSID VALUES ('RGTLST','Lista alla behörigheter');
INSERT INTO TRANSID VALUES ('TRHDADD','Lägga till ny loggpost i TRHD');
INSERT INTO TRANSID VALUES ('TRNSADD','Ny post i TRANSID');
INSERT INTO TRANSID VALUES ('TRNSCHG','Ändra post i TRANSID');
INSERT INTO TRANSID VALUES ('TRNSDEL','Ta bort post i TRANSID');
INSERT INTO TRANSID VALUES ('TRNSDSP','Visa enstaka TRANSID');
INSERT INTO TRANSID VALUES ('TRNSLST','Lista alla TRANSID');
INSERT INTO TRANSID VALUES ('USERADD','Ny post i USER');
INSERT INTO TRANSID VALUES ('USERCHG','Ändra post i USER');
INSERT INTO TRANSID VALUES ('USERDEL','Ta bort post i USER');
INSERT INTO TRANSID VALUES ('USERDSP','Visa en användare');
INSERT INTO TRANSID VALUES ('USERLST','Lista alla användare');
INSERT INTO TRANSID VALUES ('VALLST','Lista valutor');
INSERT INTO TRANSID VALUES ('VALADD','Lägga upp en ny valuta');
INSERT INTO TRANSID VALUES ('VALCHG','Ändra valutainformation');
INSERT INTO TRANSID VALUES ('VALDEL','Ta bort en valuta');
INSERT INTO TRANSID VALUES ('VALDSP','Visa en valuta');
INSERT INTO TRANSID VALUES ('VERUPD','Nyuppläggning av verifikat');
INSERT INTO TRANSID VALUES ('VERDSP','Visa enstaka verifikation');
INSERT INTO TRANSID VALUES ('VRDADD','Ny detaljpost för verifikation till VERD');
INSERT INTO TRANSID VALUES ('VRHADD','Ny huvudpost för verifikation till VERH');
INSERT INTO TRANSID VALUES ('WRREC','Skriva post till tempfilen /tmp/vernr.txt');
INSERT INTO TRANSID VALUES ('ATTBET','Lista leverantörsfakturor att betala');
INSERT INTO TRANSID VALUES ('BARADD','Lägga upp nytt bokföringsår');
INSERT INTO TRANSID VALUES ('BARCHG','Ändra data för angivet bokföringsår');
INSERT INTO TRANSID VALUES ('BARFND','Hitta bokföringsår för angivet datum');
INSERT INTO TRANSID VALUES ('BETDSP','Visa ett betalningsvillkor');
INSERT INTO TRANSID VALUES ('FTGADD','Lägga upp en ny företagspost');
INSERT INTO TRANSID VALUES ('FTGDSP','Visa företagsdata');
INSERT INTO TRANSID VALUES ('FTGLST','Lista posttyper för företagsdata');
INSERT INTO TRANSID VALUES ('FTGLIS','Lista företagsdata');
INSERT INTO TRANSID VALUES ('KUADD','Registrera nya kunder');
INSERT INTO TRANSID VALUES ('KUCHG','Ändra kunddata');
INSERT INTO TRANSID VALUES ('KUCHK','Kontrollera om kundnr finns');
INSERT INTO TRANSID VALUES ('KUDSP','Visa kunddata');
INSERT INTO TRANSID VALUES ('KULST','Lista kunder, kundnr och namn');
INSERT INTO TRANSID VALUES ('LEVADD','Lägga upp en ny leverantör');
INSERT INTO TRANSID VALUES ('LEVCHG','Ändra leverantörsdata');
INSERT INTO TRANSID VALUES ('LEVDSP','Visa en leverantör');
INSERT INTO TRANSID VALUES ('LEVLST','Lista leverantörer,nr och namn');
INSERT INTO TRANSID VALUES ('LRESRPT','Lista alla obetalda poster i tabellen LEVRESK');
INSERT INTO TRANSID VALUES ('LRESADD','Ny post i leverantörsreskontran');
INSERT INTO TRANSID VALUES ('RPTCRE','Rapportgenerator. Skapa rapporter');
INSERT INTO TRANSID VALUES ('SLPADD','Standardleveransplats');
INSERT INTO TRANSID VALUES ('TRNTST','Detta är en testfunktion');
INSERT INTO TRANSID VALUES ('ARCHK','Kontrollera om artikelnummer finns');
INSERT INTO TRANSID VALUES ('ARADD','Lägga upp en ny artikel');
INSERT INTO TRANSID VALUES ('AR2ADD','Lägga upp ny artikel i lagerställeregister.');
INSERT INTO TRANSID VALUES ('ARDSP','Visa grunddata för en artikel');
INSERT INTO TRANSID VALUES ('ARDSPL','Visa lagerdata för en artikel');
INSERT INTO TRANSID VALUES ('ARCHG','Ändra grunddata för en artikel');
INSERT INTO TRANSID VALUES ('ARCHGL','Ändra lagerställedata för en artikel');
INSERT INTO TRANSID VALUES ('BETLST','Lista betalningsvillkor');
INSERT INTO TRANSID VALUES ('BETADD','Lägga upp ett nytt betalningsvillkor');
INSERT INTO TRANSID VALUES ('ARLST','Lista artiklar(artikelnr,benämn1,benämn2)');
INSERT INTO TRANSID VALUES ('BETCHG','Ändra data för betalningsvillkor');
INSERT INTO TRANSID VALUES ('TXTDSP','Visa texter ur TEXTREG');
INSERT INTO TRANSID VALUES ('TXTADD','Lägg upp en ny post i TEXTREG');
INSERT INTO TRANSID VALUES ('INKADD','Lägga upp en ny inköpsorder');
INSERT INTO TRANSID VALUES ('INKRADD','Lägga upp en ny inköpsorderrad');
INSERT INTO TRANSID VALUES ('TXTDEL','Radera post i TEXTREG');
INSERT INTO TRANSID VALUES ('INKRLST','Lista alla rader på angiven inköpsorder');
INSERT INTO TRANSID VALUES ('INKHDSP','Visa orderhuvud för angiven inköpsorder');
INSERT INTO TRANSID VALUES ('INKLST','Beställningsstock');
INSERT INTO TRANSID VALUES ('LEVVDSP','Visa ett leveransvillkor');
INSERT INTO TRANSID VALUES ('LEVSDSP','Visa ett leveranssätt');
INSERT INTO TRANSID VALUES ('LEVVADD','Lägga upp ett nytt leveransvillkor');
INSERT INTO TRANSID VALUES ('LEVSADD','Lägga upp ett nytt leveranssätt');
INSERT INTO TRANSID VALUES ('LEVVLST','Lista leveransvillkor');
INSERT INTO TRANSID VALUES ('LEVSLST','Lista leveranssätt');
INSERT INTO TRANSID VALUES ('VERHDSP','Hämta mindatum och maxdatum för angivet bokf.år');
INSERT INTO TRANSID VALUES ('VERHLST','Lista verifikationers huvudposter för önskat bokföringsår');
INSERT INTO TRANSID VALUES ('HBOKRPT','Huvudboksrapport');
INSERT INTO TRANSID VALUES ('DBOKRPT','Dagboksrapport');
INSERT INTO TRANSID VALUES ('PRTAPI','Utskriftsinterface');
INSERT INTO TRANSID VALUES ('LEVPLST','Lista kunders leveransadresser');
INSERT INTO TRANSID VALUES ('FORCHK','Kontr. om databas finns i tabell DATABAS');
INSERT INTO TRANSID VALUES ('FORADD','Ny databas i tabellen DATABAS');
INSERT INTO TRANSID VALUES ('FORLST','Lista databaser i tabell DATABAS');
INSERT INTO TRANSID VALUES ('PKDADD','Ny produktgrupp/produktkod/produktklass');
INSERT INTO TRANSID VALUES ('PKDLST','Lista produktgrupper/produktkoder/produktklasser');
INSERT INTO TRANSID VALUES ('WKUDSP','Visa begränsade kunddata för webbkund');
INSERT INTO TRANSID VALUES ('ARLSTL','Lista artiklar med lagersaldo');
INSERT INTO TRANSID VALUES ('ARLIS','Lista artiklaf för angiven produktklass');
INSERT INTO TRANSID VALUES ('ARLSPK','Lista artiklar för angiven produktkod');
INSERT INTO TRANSID VALUES ('AR2UPD','Uppdatera artikelpost i LAGERSTELLEREG');
INSERT INTO TRANSID VALUES ('BARLST','Lista bokföringsår');
INSERT INTO TRANSID VALUES ('KUSRCH','Söka kunder på namn, postnr, tfnnr eller postadr');
INSERT INTO TRANSID VALUES ('LEVPDSP','Visa en standardleveransplats');
INSERT INTO TRANSID VALUES ('ORDADD','Nyupplägg av kundorderhuvud');
INSERT INTO TRANSID VALUES ('ORDCHK','Kontrollera diverse uppgifter på kundorder');
INSERT INTO TRANSID VALUES ('ORDDSP','Visa en kundorders huvudpost');
INSERT INTO TRANSID VALUES ('ORDRDSP','Visa en kundorders orderrader');
INSERT INTO TRANSID VALUES ('PKDDSP','Visa en produktgrupp/produktkod/produktklass');
INSERT INTO TRANSID VALUES ('SIEEXPK','SIE-export av kontoplan');
INSERT INTO TRANSID VALUES ('SIEEXPR','SIE-export av resultat');
INSERT INTO TRANSID VALUES ('SIEEXPV','SIE-export av verifikat');
INSERT INTO TRANSID VALUES ('DBCHK','Lista databaser registrerade i databasen mysql');
INSERT INTO TRANSID VALUES ('ORDLST2','Lista kundorder med begränsad information');
INSERT INTO TRANSID VALUES ('ORDLST','Lista kundorder');
INSERT INTO TRANSID VALUES ('PICKADD','Nytt plock av kundorderrad');
INSERT INTO TRANSID VALUES ('PICKDSP','Visa plockade men ej utskrivna plock');
INSERT INTO TRANSID VALUES ('PICKLST','Lista avprickade kundorderrader');

--
-- Table structure for table 'TRHD'
--

DROP TABLE IF EXISTS TRHD;
CREATE TABLE TRHD (
  TRNSNR int(11) NOT NULL auto_increment,
  TRNSID varchar(8) NOT NULL default '',
  TID varchar(20) NOT NULL default '',
  USERID varchar(8) NOT NULL default '',
  TRNSDATA varchar(255) default NULL,
  PRIMARY KEY  (TRNSNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'TRHD'
--

INSERT INTO TRHD VALUES (1,'VERADD','2003-1','JAPI','1120 -:- K -:- 1980');
INSERT INTO TRHD VALUES (2,'VERADD','2003-1','JAPI','1120 -:- K -:- 1980');
INSERT INTO TRHD VALUES (3,'VERADD','2003-1','JAPI','1120 -:- K -:- 1980');
INSERT INTO TRHD VALUES (4,'VERADD','2003-11-09_08:34:45','JAPI','1120 -:- K -:- 1980');
INSERT INTO TRHD VALUES (5,'VERADD','2003-11-09_08:34:45','JAPI','1120 -:- K -:- 1980');
INSERT INTO TRHD VALUES (6,'VERADD','2003-11-09_08:48:45','ADMIN','1120 -:- K -:- 1980');
INSERT INTO TRHD VALUES (7,'ARCHGW','2003-11-18_07:05:41','ADMIN','_:_1_:_Test1_:_ABC002_:_100_:_001_:_A_:_SEK_:_125.50_:_50_:_75_:_50_:_198.00_:_202.50_:_195.00_:_62_:_125_:_26.50_:_');
INSERT INTO TRHD VALUES (8,'ARCHGL','2003-11-18_07:10:49','ADMIN','_:_1_:_Test1_:_ABC002_:_100_:_001_:_A_:_SEK_:_125.50_:_50_:_75_:_50_:_198.00_:_202.50_:_195.00_:_62_:_125_:_27.50_:_');
INSERT INTO TRHD VALUES (9,'CHGARW','2003-11-18_07:34:25','ADMIN','_:_1_:_Test1_:_ABC002_:_100.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_155.00_:_202.50_:_155.00_:_62.00_:_125.00_:_27.50_:_');
INSERT INTO TRHD VALUES (10,'CHGARW','2003-11-18_07:38:32','ADMIN','_:_1_:_Test1_:_ABC002_:_100.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_27.5_:_');
INSERT INTO TRHD VALUES (11,'CHGARW','2003-11-18_07:51:01','ADMIN','_:_1_:_Test1_:_ABC002_:_100.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_');
INSERT INTO TRHD VALUES (12,'CHGARW','2003-11-18_12:00:34','ADMIN','_:_1_:_Test1_:_ABC002_:_101.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_');
INSERT INTO TRHD VALUES (13,'CHGARW','2003-11-18_12:04:40','ADMIN','_:_1_:_Test1_:_ABC002_:_102.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_');
INSERT INTO TRHD VALUES (14,'CHGARW','2003-11-18_12:08:29','ADMIN','_:_1_:_Test1_:_ABC002_:_102.00_:_001_:_A_:_SEK_:_125.50_:_60.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_');
INSERT INTO TRHD VALUES (15,'CHGARW','2003-11-18_12:12:36','ADMIN','_:_1_:_Test1_:_ABC002_:_103.00_:_001_:_A_:_SEK_:_125.50_:_60.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_');
INSERT INTO TRHD VALUES (16,'CHGARW','2003-11-24_05:45:08','ADMIN','_:_1_:_1173-7540_:_AAC001_:_11.00_:_1_:_A_:_SEK_:_98.00_:_0.00_:_0.00_:_0.00_:_103.00_:_0.00_:_103.00_:_0.00_:_65.00_:_5.00_:_');
INSERT INTO TRHD VALUES (17,'CHGARW','2003-11-24_06:39:57','ADMIN','_:_1_:_1173-7540_:_AAC001_:_11.00_:_1_:_A_:_SEK_:_98.00_:_0.00_:_0.00_:_0.00_:_103.00_:_0.00_:_103.00_:_0.00_:_65.00_:_5.00_:_');
INSERT INTO TRHD VALUES (18,'CHGARW','2003-11-24_06:52:13','ADMIN','_:_1_:_1173-7540_:_AAC001_:_11.00_:_1_:_A_:_SEK_:_98.00_:_0.00_:_0.00_:_0.00_:_103.00_:_0.00_:_103.00_:_0.00_:_65.00_:_5.00_:_');
INSERT INTO TRHD VALUES (19,'CHGARW','2003-11-24_07:00:22','ADMIN','_:_1_:_1173-7540_:_AAC001_:_11.00_:_1_:_A_:_SEK_:_98.00_:_0.00_:_0.00_:_0.00_:_103.00_:_0.00_:_0.00_:_0.00_:_65.00_:_5.00_:_');
INSERT INTO TRHD VALUES (20,'CHGARW','2003-11-24_07:01:10','ADMIN','_:_1_:_1173-1445_:_AAA002_:_27.00_:_1_:_A_:_SEK_:_95.00_:_0.00_:_0.00_:_0.00_:_100.00_:_0.00_:_0.00_:_0.00_:_25.00_:_0.00_:_');
INSERT INTO TRHD VALUES (21,'CHGARW','2003-12-07_04:40:48','ADMIN','_:_1_:_7310070059208_:_1_:_2.00_:_1_:_A_:_SEK_:_10.90_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_');
INSERT INTO TRHD VALUES (22,'CHGARW','2003-12-07_04:53:24','ADMIN','_:_1_:_7310070125002_:_1_:_3.00_:_1_:_A_:_SEK_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_');
INSERT INTO TRHD VALUES (23,'BOKFOR','2004-01-02_13:26:43','ADMIN','H AD 00000100 001 2440 D     10000.00           2004-01-02 jan      test nr 100                                                                                                  \n');
INSERT INTO TRHD VALUES (24,'BOKFOR','2004-01-02_13:26:43','ADMIN','D AD 00000100 002 2611 K      2500.00                                                                                                                              l             \n');
INSERT INTO TRHD VALUES (25,'BOKFOR','2004-01-02_13:26:43','ADMIN','D AD 00000100 003 4010 K      7500.00                                                                                                                              l             \n');

--
-- Table structure for table 'USR'
--

DROP TABLE IF EXISTS USR;
CREATE TABLE USR (
  USERID varchar(8) NOT NULL default '',
  NAMN varchar(30) default NULL,
  AVD varchar(10) default NULL,
  GRUPP varchar(10) default NULL,
  PRIMARY KEY  (USERID)
) TYPE=MyISAM;

--
-- Dumping data for table 'USR'
--

INSERT INTO USR VALUES ('OLFIX','Olfix Superuser','IT','Stab');
INSERT INTO USR VALUES ('TESTARE','Testare Test','IT','Stab');
INSERT INTO USR VALUES ('CARRO','Caroline Inköpare','Inköp','Prod');
INSERT INTO USR VALUES ('ADMIN','Administratör av OLFIX','IT','Stab');
INSERT INTO USR VALUES ('GUEST','Guest Apache','Apache','Webb');

--
-- Table structure for table 'VALUTA'
--

DROP TABLE IF EXISTS VALUTA;
CREATE TABLE VALUTA (
  VALUTAID char(3) NOT NULL default '',
  LAND varchar(15) default NULL,
  SALJ decimal(3,2) default NULL,
  KOP decimal(3,2) default NULL,
  BETECKNING varchar(15) default NULL,
  PRIMARY KEY  (VALUTAID)
) TYPE=MyISAM;

--
-- Dumping data for table 'VALUTA'
--

INSERT INTO VALUTA VALUES ('DKK','Danmark',1.22,1.22,'Kronor');
INSERT INTO VALUTA VALUES ('NOK','Norge',1.23,1.23,'Kronor');
INSERT INTO VALUTA VALUES ('NYZ','Nya Zeeland',4.45,4.45,'Dollar');
INSERT INTO VALUTA VALUES ('SAR','Saudiarabien',2.40,2.40,'Riyal');
INSERT INTO VALUTA VALUES ('HKD','Honkong',0.00,0.00,'Dollar');
INSERT INTO VALUTA VALUES ('MYR','Malaysia',2.36,2.36,'Ringgit');
INSERT INTO VALUTA VALUES ('SGD','Singapore',5.08,5.08,'Dollar');
INSERT INTO VALUTA VALUES ('CAD','Kanada',5.66,5.66,'Dollar');
INSERT INTO VALUTA VALUES ('AUD','Australien',5.03,5.03,'Dollar');
INSERT INTO VALUTA VALUES ('USD','USA',8.97,8.97,'Dollar');
INSERT INTO VALUTA VALUES ('JPY','Japan',7.38,7.38,'Yen');
INSERT INTO VALUTA VALUES ('GBP','Storbritanien',14.26,14.26,'Pund');
INSERT INTO VALUTA VALUES ('EUR','Europa',9.08,9.08,'Euro');
INSERT INTO VALUTA VALUES ('CHF','Schweiz',0.00,0.00,'France');
INSERT INTO VALUTA VALUES ('SEK','Sverige',1.00,1.00,'Kronor');
INSERT INTO VALUTA VALUES ('SEC','TestSverige',1.99,1.98,'Kroner');

--
-- Table structure for table 'VERHUVUD'
--

DROP TABLE IF EXISTS VERHUVUD;
CREATE TABLE VERHUVUD (
  VERNR int(11) NOT NULL default '0',
  ARID char(2) NOT NULL default '',
  VERDATUM date default NULL,
  REGDAT date default NULL,
  DEBET decimal(10,2) default NULL,
  KREDIT decimal(10,2) default NULL,
  VERTEXT varchar(60) default NULL,
  KORRIGERAR int(11) default NULL,
  KORRIGERAD int(11) default NULL,
  USERID varchar(8) default NULL,
  PRIMARY KEY  (VERNR,ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'VERHUVUD'
--

INSERT INTO VERHUVUD VALUES (8,'AC','2003-06-27','2003-06-27',3000.00,0.00,'Test av hela LEVFAKTW',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (4,'AC','2003-06-03','2003-06-03',2000.00,0.00,'Inköp av skrivbord',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (7,'AC','2003-06-26','2003-06-26',10000.00,0.00,'test WRREC',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (3,'AC','2003-05-20','2003-05-20',10000.00,0.00,'Bokhylla',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (2,'AC','2003-05-20','2003-05-20',1000.00,0.00,'test nr 2',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (1,'AC','2003-05-20','2003-05-20',1000.00,0.00,'Test av sortering och DK +-',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (9,'AC','2003-06-27','2003-06-27',5000.00,0.00,'totaltest nr 2 av LEVFAKTW',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (10,'AC','2003-06-27','2003-06-27',5800.00,0.00,'Soffgrupp',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (11,'AC','2003-07-01','2003-07-01',0.00,0.00,'',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (12,'AC','2003-07-01','2003-07-01',100.00,0.00,'test',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (13,'AC','2003-07-02','2003-07-02',4540.00,0.00,'test valuta',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (14,'AC','2003-07-02','2003-07-02',1500.00,0.00,'Inköp av möbler',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (15,'AC','2003-07-02','2003-07-02',4540.00,0.00,'inköp material',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (16,'AC','2003-07-02','2003-07-02',3632.00,0.00,'Inköp av material',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (17,'AC','2003-07-03','2003-07-03',3139.50,0.00,'test',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (18,'AC','2003-07-09','2003-07-09',1000.00,0.00,'test ocrnummer',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (19,'AC','2003-07-09','2003-07-09',3000.00,0.00,'test nr 2 av OCR',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (20,'AC','2003-07-09','2003-07-09',36320.00,0.00,'Inköp av stålbalk',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (21,'AC','2003-07-10','2003-07-10',5000.00,0.00,'Test av vernr',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (22,'AC','2003-07-10','2003-07-10',1000.00,0.00,'test',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (23,'AC','2003-07-09','2003-07-09',2000.00,0.00,'test',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (24,'AC','2003-07-10','2003-07-10',9080.00,0.00,'test av OCR',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (1,'AD','2003-07-30','2003-07-30',300000.00,0.00,'Lån eget kapital',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (2,'AD','2003-07-30','2003-07-30',499450.00,0.00,'Insättning checkräkningskredit',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (3,'AD','2003-07-30','2003-07-30',0.00,60000.00,'Lokalhyra 1.a kv 2003',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (7,'AD','2003-08-01','2003-08-01',0.00,2000.00,'Mässingplåt. 1 mm. 0,5 m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (8,'AD','2003-08-02','2003-08-02',0.00,2000.00,'Al-plåt. 1 mm. 1 m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (9,'AD','2003-08-03','2003-08-03',0.00,3000.00,'Järnplåt. 1 mm. 1 m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (10,'AD','2003-08-04','2003-08-04',0.00,3000.00,'Järnplåt. 0,6 mm. 1,5 m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (11,'AD','2003-08-05','2003-08-05',0.00,3000.00,'Järnplåt. 0,3 mm. 3 m3.',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (12,'AD','2003-08-06','2003-08-06',0.00,3000.00,'Al-plåt 0,75 mm. 2 m3.',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (13,'AD','2003-08-07','2003-08-07',0.00,1000.00,'Alplåt 0,5 mm 1m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (14,'AD','2003-08-08','2003-08-08',0.00,1000.00,'Al-plåt 1 m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (15,'AD','2003-08-09','2003-08-09',0.00,36320.00,'U-balk. Al. 5 m.',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (16,'AD','2003-08-10','2003-08-10',0.00,1000.00,'Järnplåt. 0,3 mm. 1 m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (17,'AD','2003-08-11','2003-08-11',0.00,5000.00,'I-balk',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (18,'AD','2003-08-11','2003-08-11',0.00,2500.00,'Järnplåt. 1 mm. 1 m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (19,'AD','2003-08-12','2003-08-12',0.00,50000.00,'U-balk aluminium. 7 m.',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (20,'AD','2003-08-12','2003-08-12',0.00,2000.00,'Järnplåt. 0,6mm. 1 m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (21,'AD','2003-08-13','2003-08-13',0.00,1000.00,'Aluminiumplåt. 1 m3',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (22,'AD','2003-08-13','2003-08-13',0.00,4000.00,'Printerpapper',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (23,'AD','2003-08-13','2003-08-13',0.00,5000.00,'Pärmar,Kollegieblock,Kopieringspapper',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (25,'AC','2003-08-13','2003-08-13',0.00,54480.00,'test',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (24,'AD','2003-08-16','2003-08-16',0.00,25000.00,'Bokhyllor',0,0,'ADMIN');
INSERT INTO VERHUVUD VALUES (25,'AD','2003-09-11','2003-09-11',0.00,40860.00,'Aluminiumprofil U',0,0,'ADMIN');

--
-- Table structure for table 'VERRAD'
--

DROP TABLE IF EXISTS VERRAD;
CREATE TABLE VERRAD (
  VERNR int(11) NOT NULL default '0',
  RADNR smallint(6) NOT NULL default '0',
  ARID char(2) NOT NULL default '',
  KTONR varchar(4) default NULL,
  BELOPP decimal(10,2) default NULL,
  DK enum('D','K') default NULL,
  KSTALLE varchar(4) default NULL,
  PROJEKT varchar(4) default NULL,
  SUBKTO varchar(4) default NULL,
  DEFINITIV enum('J','N') default 'N',
  STRUKEN enum('J','N') default 'N',
  PRIMARY KEY  (VERNR,RADNR,ARID)
) TYPE=MyISAM;

--
-- Dumping data for table 'VERRAD'
--

INSERT INTO VERRAD VALUES (4,3,'AC','1820',1500.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (7,1,'AC','2110',10000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (7,2,'AC','1470',1200.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (4,2,'AC','1470',500.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (4,1,'AC','2110',2000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (3,3,'AC','1820',7500.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (3,2,'AC','1470',2500.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (3,1,'AC','2110',10000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (2,3,'AC','1470',250.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (2,2,'AC','1510',750.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (2,1,'AC','2110',1000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (1,1,'AC','1510',1000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (1,2,'AC','1470',250.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (1,3,'AC','1510',750.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (7,3,'AC','1810',8800.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (8,1,'AC','2110',3000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (8,2,'AC','1470',750.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (8,3,'AC','1810',2250.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (9,1,'AC','2110',5000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (9,2,'AC','1470',1250.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (9,3,'AC','1810',3750.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (10,1,'AC','2110',5800.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (10,2,'AC','1470',1450.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (10,3,'AC','1810',4350.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (11,1,'AC','2110',0.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (11,2,'AC','1470',0.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (11,3,'AC','1810',0.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (12,1,'AC','2110',100.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (12,2,'AC','1470',25.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (12,3,'AC','4010',75.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (13,1,'AC','2110',4540.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (13,2,'AC','1470',1135.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (13,3,'AC','4010',3405.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (14,1,'AC','2110',1500.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (14,2,'AC','1470',375.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (14,3,'AC','1810',1125.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (15,1,'AC','2110',4540.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (15,2,'AC','1470',1135.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (15,3,'AC','4010',3405.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (16,1,'AC','2110',3632.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (16,2,'AC','1470',908.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (16,3,'AC','4010',2724.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (17,1,'AC','2110',3139.50,'D','','','','N','N');
INSERT INTO VERRAD VALUES (17,3,'AC','4010',2354.62,'K','','','','N','N');
INSERT INTO VERRAD VALUES (17,2,'AC','1470',784.88,'K','','','','N','N');
INSERT INTO VERRAD VALUES (18,1,'AC','2110',1000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (18,2,'AC','1470',250.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (18,3,'AC','4010',750.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (19,1,'AC','2110',3000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (19,2,'AC','1470',750.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (19,3,'AC','4010',2250.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (20,1,'AC','2110',36320.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (20,2,'AC','1470',9080.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (20,3,'AC','4010',27240.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (21,1,'AC','2110',5000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (21,2,'AC','1470',1250.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (21,3,'AC','4010',3750.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (22,1,'AC','2110',1000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (22,2,'AC','1470',250.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (22,3,'AC','4010',750.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (23,1,'AC','2110',2000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (23,2,'AC','1470',500.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (23,3,'AC','4010',1500.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (24,1,'AC','2110',9080.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (24,2,'AC','1470',2270.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (24,3,'AC','4010',6810.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (1,2,'AD','2081',300000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (1,1,'AD','2330',300000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (2,1,'AD','2330',499450.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (2,2,'AD','2350',500000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (2,3,'AD','8490',550.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (3,1,'AD','2330',60000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (3,2,'AD','2641',12000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (3,3,'AD','5010',48000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (7,2,'AD','2641',500.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (7,1,'AD','2440',2000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (8,1,'AD','2440',2000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (7,3,'AD','4010',1500.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (8,2,'AD','2641',500.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (8,3,'AD','4010',1500.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (9,1,'AD','2440',3000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (9,2,'AD','2641',750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (9,3,'AD','4010',2250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (10,1,'AD','2440',3000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (10,2,'AD','2641',750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (10,3,'AD','4010',2250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (11,1,'AD','2440',3000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (11,2,'AD','2641',750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (11,3,'AD','4010',2250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (12,1,'AD','2440',3000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (12,2,'AD','2641',750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (12,3,'AD','4010',2250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (13,1,'AD','2440',1000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (13,2,'AD','2641',250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (13,3,'AD','4010',750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (14,1,'AD','2440',1000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (14,2,'AD','2641',250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (14,3,'AD','4010',750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (15,1,'AD','2440',36320.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (15,2,'AD','2641',9080.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (15,3,'AD','4010',27240.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (16,1,'AD','2440',1000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (16,2,'AD','2641',250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (16,3,'AD','4010',750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (17,1,'AD','2440',5000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (17,2,'AD','2641',1250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (17,3,'AD','4010',3750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (18,1,'AD','2440',2500.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (18,2,'AD','2641',625.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (18,3,'AD','4010',1875.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (19,1,'AD','2440',50000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (19,2,'AD','2641',12500.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (19,3,'AD','4010',37500.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (20,1,'AD','2440',2000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (20,2,'AD','2641',500.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (20,3,'AD','4010',1500.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (21,1,'AD','2440',1000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (21,2,'AD','2641',250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (21,3,'AD','4010',750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (22,1,'AD','2440',4000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (22,2,'AD','2641',1000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (22,3,'AD','6110',3000.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (23,1,'AD','2440',5000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (23,2,'AD','2641',1250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (23,3,'AD','6110',3750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (25,1,'AC','2110',54480.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (25,2,'AC','1470',13620.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (25,3,'AC','4010',40860.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (24,1,'AD','2440',25000.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (24,2,'AD','2641',6250.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (24,3,'AD','1220',18750.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (25,1,'AD','2440',40860.00,'K','','','','N','N');
INSERT INTO VERRAD VALUES (25,2,'AD','2611',10215.00,'D','','','','N','N');
INSERT INTO VERRAD VALUES (25,3,'AD','4010',30645.00,'D','','','','N','N');

--
-- Table structure for table 'WEBBKUND'
--

DROP TABLE IF EXISTS WEBBKUND;
CREATE TABLE WEBBKUND (
  KUNDNR varchar(10) NOT NULL default '',
  NAMN varchar(60) NOT NULL default '',
  ADRESS varchar(30) default NULL,
  POSTNR varchar(6) default NULL,
  POSTADR varchar(30) default NULL,
  LAND varchar(30) default NULL,
  ADRESS2 varchar(30) default NULL,
  POSTNR2 varchar(6) default NULL,
  POSTADR2 varchar(30) default NULL,
  LAND2 varchar(30) default NULL,
  TFNNR varchar(15) default NULL,
  EMAILADR varchar(30) default NULL,
  BETALVILLKOR char(3) default NULL,
  LEVVILLKOR char(3) default NULL,
  LEVSETT char(3) default NULL,
  ORDERERKENNANDE enum('J','N') default 'J',
  PLOCKLISTA enum('J','N') default 'J',
  FOLJESEDEL enum('J','N') default 'J',
  KRAVBREV enum('J','N') default 'J',
  EXPAVGIFT enum('J','N') default 'J',
  FRAKTAVG enum('J','N') default 'J',
  KREDITLIMIT decimal(10,2) default NULL,
  KREDITDAGAR int(11) default NULL,
  DROJMALSRTA enum('J','N') default 'J',
  DROJMALSFAKTURA enum('J','N') default 'J',
  SENASTEKRAVDATUM date default NULL,
  SKULD decimal(10,2) default NULL,
  ORDERSTOCK decimal(10,2) default NULL,
  PASSWORD varchar(16) NOT NULL default '',
  PRIMARY KEY  (KUNDNR)
) TYPE=MyISAM;

--
-- Dumping data for table 'WEBBKUND'
--

INSERT INTO WEBBKUND VALUES ('100001','Karl-Oskar Webbsson','Box 99','199 99','AVLIDEN',NULL,'Itgatan 31','199 97','AVLIDEN',NULL,'09-990011','ko.webbsson@prog.net','5','001','003','J','J','J','J','J','J',5000.00,30,'J','J',NULL,0.00,0.00,'webbsson');

use mysql;
INSERT INTO user
(
Host,
User,
Password,
Select_priv,
Insert_priv,
Update_priv,
Delete_priv,
Create_priv,
Drop_priv,
Reload_priv,
Shutdown_priv,
Process_priv,
File_priv,
Grant_priv,
References_priv,
Index_priv,
Alter_priv
)
VALUES
(
"localhost",
"olfix",
PASSWORD("olfix"),
"Y",
"Y",
"Y",
"Y",
"Y",
"Y",
"Y",
"Y",
"Y",
"Y",
"Y",
"Y",
"Y",
"Y"
);
FLUSH PRIVILEGES;
