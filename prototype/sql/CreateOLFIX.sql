-- MySQL dump 10.9
--
-- Host: localhost    Database: olfix
-- ------------------------------------------------------
-- Server version	4.1.12

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `olfix`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `olfix` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `olfix`;

--
-- Table structure for table `ARTIKELREG`
--

DROP TABLE IF EXISTS `ARTIKELREG`;
CREATE TABLE `ARTIKELREG` (
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `ARBENEMNING1` varchar(30) NOT NULL default '',
  `ARBENEMNING2` varchar(30) default NULL,
  `ARENHET` varchar(5) default NULL,
  `ARFPRIS` decimal(10,2) default NULL,
  `ARLEDTID` char(3) default NULL,
  `ARPRODKLASS` varchar(5) default NULL,
  `ARPRODKTO` varchar(5) default NULL,
  `ARLEVNR1` varchar(10) default NULL,
  `ARLEVNR2` varchar(10) default NULL,
  `ARLEVNR3` varchar(10) default NULL,
  `ARNETTOVIKT` decimal(10,2) default NULL,
  `ARARTTYP` enum('0','1','2','3','4') default '0',
  `ARSTRUKT` enum('','B','I','T','F') default '',
  `ARURBENEMNING` varchar(30) default NULL,
  `ARURLAND` varchar(30) default NULL,
  `ARURARTNR` varchar(30) default NULL,
  `ARTULLTAX` varchar(10) default NULL,
  `ARVOLYM` decimal(4,3) default NULL,
  `AROMRFAKTOR` int(11) NOT NULL default '1',
  PRIMARY KEY  (`ARTIKELNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ARTIKELREG`
--


/*!40000 ALTER TABLE `ARTIKELREG` DISABLE KEYS */;
LOCK TABLES `ARTIKELREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `ARTIKELREG` ENABLE KEYS */;

--
-- Table structure for table `BETVILKOR`
--

DROP TABLE IF EXISTS `BETVILKOR`;
CREATE TABLE `BETVILKOR` (
  `BETVILKOR` char(3) NOT NULL default '',
  `DAGAR` char(3) default NULL,
  `BESKRIVNING` varchar(40) NOT NULL default '',
  PRIMARY KEY  (`BETVILKOR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `BETVILKOR`
--


/*!40000 ALTER TABLE `BETVILKOR` DISABLE KEYS */;
LOCK TABLES `BETVILKOR` WRITE;
INSERT INTO `BETVILKOR` (`BETVILKOR`, `DAGAR`, `BESKRIVNING`) VALUES ('1','30','30 dagar netto'),('2','20','20 dagar netto'),('3','10','10 dagar netto'),('4','0','Kontantköp'),('5','15','Postförskott');
UNLOCK TABLES;
/*!40000 ALTER TABLE `BETVILKOR` ENABLE KEYS */;

--
-- Table structure for table `BOKFAR`
--

DROP TABLE IF EXISTS `BOKFAR`;
CREATE TABLE `BOKFAR` (
  `ARID` char(2) NOT NULL default '',
  `BENAMNING` varchar(25) default NULL,
  `ARSTART` date default NULL,
  `ARSLUT` date default NULL,
  `ARLAST` enum('J','N') default 'N',
  `SENVERDAT` date default NULL,
  `VERNR` int(11) default NULL,
  `KONTOPLAN` varchar(15) default NULL,
  `BESKATTNINGSAR` varchar(4) default NULL,
  PRIMARY KEY  (`ARID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `BOKFAR`
--


/*!40000 ALTER TABLE `BOKFAR` DISABLE KEYS */;
LOCK TABLES `BOKFAR` WRITE;
INSERT INTO `BOKFAR` (`ARID`, `BENAMNING`, `ARSTART`, `ARSLUT`, `ARLAST`, `SENVERDAT`, `VERNR`, `KONTOPLAN`, `BESKATTNINGSAR`) VALUES ('XX','2003-01-01--2003-12-31','2003-01-01','2003-12-31','N','2003-09-11',26,'EUBAS97','2003');
UNLOCK TABLES;
/*!40000 ALTER TABLE `BOKFAR` ENABLE KEYS */;

--
-- Table structure for table `FTGDATA`
--

DROP TABLE IF EXISTS `FTGDATA`;
CREATE TABLE `FTGDATA` (
  `POSTTYP` varchar(5) NOT NULL default '',
  `POSTBESKR` varchar(60) default NULL,
  `FDATA` text,
  PRIMARY KEY  (`POSTTYP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `FTGDATA`
--


/*!40000 ALTER TABLE `FTGDATA` DISABLE KEYS */;
LOCK TABLES `FTGDATA` WRITE;
INSERT INTO `FTGDATA` (`POSTTYP`, `POSTBESKR`, `FDATA`) VALUES ('FNAMN','Företagsnamn',NULL),('FTGNR','Företagsnummer',NULL),('ADR1','Postadress',NULL),('ADR2','Postnummer till Postadress',NULL),('ADR3','Ort till Postadress',NULL),('ADR4','Besöksadress',NULL),('ADR5','Postnr till Besöksadress',NULL),('ADR6','Ort till Besöksadress',NULL),('ADR7','Godsadress',NULL),('ADR8','Postnr till Godsadress',NULL),('ADR9','Ort till Godsadress',NULL),('TFNVX','Telefonnummer till vx',NULL),('TFN1','Telefonnummer',NULL),('TFN2','Mobiltelefonnummer',NULL),('TFNMB','Mobiltelefonnummer',NULL),('TFAX','Telefaxnummer',NULL),('TELEX','Telexnummer',NULL),('EML1','E-mailadress',NULL),('MOMSI','Momskonto, ingående moms',NULL),('MOMSU','Momskonto, utgående moms',NULL),('MOMS1','Momssats 1',NULL),('MOMS2','Momssats 2',NULL),('MOMS3','Momssats 3',NULL),('MOMS4','Momssats 4',NULL),('MOMS5','Momssats 5',NULL),('AUTOK','Automatkontering J/N?\n\"BGNR','Bankgironummer'),('KORNR','Senast använda kundordernr',NULL),('BF1','Bokföringsperiod 1',NULL),('BF2','Bokföringsperiod 2',NULL),('BF3','Bokföringsperiod 3',NULL),('BF4','Bokföringsperiod 4',NULL),('BF5','Bokföringsperiod 5',NULL),('BF6','Bokföringsperiod 6',NULL),('BF7','Bokföringsperiod 7',NULL),('BF8','Bokföringsperiod 8',NULL),('BF9','Bokföringsperiod 9',NULL),('BF10','Bokföringsperiod 10',NULL),('BF11','Bokföringsperiod 11',NULL),('BF12','Bokföringsperiod 12',NULL),('BF13','Bokföringsperiod 13',NULL),('INKNR','Senast använda inköpsordernr',NULL),('SNIKD','Branschtillhörighet',NULL),('OFFNR','Senast använda offertnummer',NULL),('FAKNR','Senaste fakturanr på kundorder',NULL),('FKNR2','Senaste fakturanr p kundorder,serie 2',NULL),('FKNRS','Antal fakturanummerserier,default = 1',NULL),('KFKTO','Konto för kundfordringar',NULL),('INKTO','Konto för inbetalningar',NULL),('SKUNR','Senast använda kundnummer',NULL),('WKUNR','Senast använda webbkundnummer',NULL),('PGNR','Postgironummer',NULL),('MNR','Momsnummer',NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `FTGDATA` ENABLE KEYS */;

--
-- Table structure for table `INKRADREG`
--

DROP TABLE IF EXISTS `INKRADREG`;
CREATE TABLE `INKRADREG` (
  `INKORDNR` varchar(10) NOT NULL default '',
  `INKORDRADNR` int(4) NOT NULL default '0',
  `ARTIKELNR` varchar(30) default NULL,
  `BENEMNING` varchar(30) default NULL,
  `LEVARTIKELNR` varchar(30) default NULL,
  `LEVBENEMNING` varchar(30) default NULL,
  `ENHET` varchar(5) default NULL,
  `BESTANTAL` decimal(10,2) default NULL,
  `LEVERERAT` decimal(10,2) default NULL,
  `RESTNOTERAT` decimal(10,2) default NULL,
  `INKPRIS` decimal(10,2) default NULL,
  `LEVVECKA` varchar(5) default NULL,
  `TORDNR` int(6) default NULL,
  `OPNR` int(6) default NULL,
  PRIMARY KEY  (`INKORDNR`,`INKORDRADNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `INKRADREG`
--


/*!40000 ALTER TABLE `INKRADREG` DISABLE KEYS */;
LOCK TABLES `INKRADREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `INKRADREG` ENABLE KEYS */;

--
-- Table structure for table `INKREG`
--

DROP TABLE IF EXISTS `INKREG`;
CREATE TABLE `INKREG` (
  `INKORDNR` varchar(10) NOT NULL default '',
  `BESTTYP` enum('N','D','I','L','A') default NULL,
  `ORDERDATUM` date default NULL,
  `LEVNR` varchar(10) default NULL,
  `LEVNAMN` varchar(30) default NULL,
  `LEVADRESS` varchar(30) default NULL,
  `LEVPOSTNR` varchar(6) default NULL,
  `LEVPOSTADR` varchar(30) default NULL,
  `LEVLAND` varchar(30) default NULL,
  `LEVVALUTA` char(3) default NULL,
  `LEVBETVILLKOR` varchar(50) default NULL,
  `LEVVILLKOR` varchar(150) default NULL,
  `LEVSETT` varchar(150) default NULL,
  `GODSMERKE` varchar(30) default NULL,
  `KOMMENTAR` varchar(250) default NULL,
  `BESTTEXT` text,
  `VARREF` varchar(30) default NULL,
  `VARREFTFN` varchar(15) default NULL,
  `VARREFFAX` varchar(15) default NULL,
  `ERREF` varchar(20) default NULL,
  `LEVDATUM` date default NULL,
  `KUNDNR` varchar(30) default NULL,
  `FTGNAMN` varchar(30) default NULL,
  `FTGADR` varchar(30) default NULL,
  `FTGPOSTNR` varchar(6) default NULL,
  `FTGPOSTADR` varchar(30) default NULL,
  `SPRAKKOD` char(3) default 'sv',
  `BEKREFTKOD` enum('H','D','E') default 'E',
  `ORDERSTATUS` enum('N','F','B','M') default 'N',
  `UTSKRIFTSKOD` enum('J','N') default 'J',
  `ORDERSUMMA` decimal(10,2) default NULL,
  PRIMARY KEY  (`INKORDNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `INKREG`
--


/*!40000 ALTER TABLE `INKREG` DISABLE KEYS */;
LOCK TABLES `INKREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `INKREG` ENABLE KEYS */;

--
-- Table structure for table `KSTALLE`
--

DROP TABLE IF EXISTS `KSTALLE`;
CREATE TABLE `KSTALLE` (
  `ARID` char(2) NOT NULL default '',
  `KSTALLE` varchar(4) NOT NULL default '',
  `BENAMNING` varchar(100) default NULL,
  PRIMARY KEY  (`ARID`,`KSTALLE`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KSTALLE`
--


/*!40000 ALTER TABLE `KSTALLE` DISABLE KEYS */;
LOCK TABLES `KSTALLE` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `KSTALLE` ENABLE KEYS */;

--
-- Table structure for table `KTOPLAN`
--

DROP TABLE IF EXISTS `KTOPLAN`;
CREATE TABLE `KTOPLAN` (
  `ARID` char(2) NOT NULL default '',
  `KTONR` varchar(4) NOT NULL default '',
  `BENAMNING` varchar(100) default NULL,
  `MANUELL` enum('J','N') default 'J',
  `MOMSKOD` varchar(4) default NULL,
  `SRUNR` int(3) default NULL,
  `KSTALLE` varchar(4) default NULL,
  `PROJEKT` varchar(4) default NULL,
  `SUBKTO` varchar(4) default NULL,
  `KTOPLAN` varchar(15) default NULL,
  `IB` decimal(10,2) default NULL,
  `UB` decimal(10,2) default NULL,
  PRIMARY KEY  (`KTONR`,`ARID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KTOPLAN`
--


/*!40000 ALTER TABLE `KTOPLAN` DISABLE KEYS */;
LOCK TABLES `KTOPLAN` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `KTOPLAN` ENABLE KEYS */;

--
-- Table structure for table `KUNDKATEGORI`
--

DROP TABLE IF EXISTS `KUNDKATEGORI`;
CREATE TABLE `KUNDKATEGORI` (
  `KATEGORINR` char(3) NOT NULL default '',
  `BESKRIVNING` varchar(40) NOT NULL default '',
  PRIMARY KEY  (`KATEGORINR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KUNDKATEGORI`
--


/*!40000 ALTER TABLE `KUNDKATEGORI` DISABLE KEYS */;
LOCK TABLES `KUNDKATEGORI` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `KUNDKATEGORI` ENABLE KEYS */;

--
-- Table structure for table `KUNDREG`
--

DROP TABLE IF EXISTS `KUNDREG`;
CREATE TABLE `KUNDREG` (
  `KUNDNR` varchar(10) NOT NULL default '',
  `KUNDORGNR` varchar(12) default NULL,
  `NAMN` varchar(60) NOT NULL default '',
  `ADRESS` varchar(30) default NULL,
  `POSTNR` varchar(10) default NULL,
  `POSTADR` varchar(30) default NULL,
  `LAND` varchar(30) default NULL,
  `TFNNR` varchar(15) default NULL,
  `EMAILADR` varchar(30) default NULL,
  `FAXNR` varchar(15) default NULL,
  `ERREFERENT` varchar(30) default NULL,
  `ERREFTFNNR` varchar(15) default NULL,
  `ERREFEMAIL` varchar(60) default NULL,
  `SELJARE` varchar(20) default NULL,
  `FRITEXT` varchar(100) default NULL,
  `VALUTA` char(3) default NULL,
  `BETALVILLKOR` char(3) default NULL,
  `LEVVILLKOR` char(3) default NULL,
  `LEVSETT` char(3) default NULL,
  `DISTRIKT` char(3) default NULL,
  `KUNDKATEGORI` char(3) default NULL,
  `STDLEVPLATS` char(3) default '001',
  `ORDERERKENNANDE` enum('J','N') default 'J',
  `PLOCKLISTA` enum('J','N') default 'J',
  `FOLJESEDEL` enum('J','N') default 'J',
  `KRAVBREV` enum('J','N') default 'J',
  `SPRAKKOD` char(3) default NULL,
  `EXPAVGIFT` enum('J','N') default 'J',
  `FRAKTAVG` enum('J','N') default 'J',
  `KREDITLIMIT` decimal(10,2) default NULL,
  `KREDITDAGAR` int(11) default NULL,
  `KREDITKOD` char(3) default NULL,
  `EXPORTKOD` char(3) default NULL,
  `SKATTEKOD` char(3) default NULL,
  `RABATTKOD` char(3) default NULL,
  `DROJMALSRTA` enum('J','N') default 'J',
  `DROJMALSFAKTURA` enum('J','N') default 'J',
  `SAMLINGSFAKT` enum('J','N') default 'J',
  `SENASTEKRAVDATUM` date default NULL,
  `SKULD` decimal(10,2) default NULL,
  `ORDERSTOCK` decimal(10,2) default NULL,
  `PRISLISTA` int(11) default NULL,
  PRIMARY KEY  (`KUNDNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KUNDREG`
--


/*!40000 ALTER TABLE `KUNDREG` DISABLE KEYS */;
LOCK TABLES `KUNDREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `KUNDREG` ENABLE KEYS */;

--
-- Table structure for table `KURESK`
--

DROP TABLE IF EXISTS `KURESK`;
CREATE TABLE `KURESK` (
  `ORDERNR` varchar(10) NOT NULL default '',
  `FAKTURANR` varchar(20) NOT NULL default '',
  `KUNDNR` varchar(10) NOT NULL default '',
  `FAKTURADATUM` date default NULL,
  `EXPIREDATUM` date default NULL,
  `NETTOBELOPP` decimal(10,2) default NULL,
  `MOMSBELOPP` decimal(10,2) default NULL,
  `FAKTURABELOPP` decimal(10,2) default NULL,
  `BETALD` enum('J','N') NOT NULL default 'N',
  `BETALDATUM` date default NULL,
  `USERID` varchar(20) default NULL,
  `VALUTA` char(3) default 'SEK',
  `VALUTAKURS` decimal(10,2) NOT NULL default '1.00',
  `VALUTABELOPP` decimal(10,2) default '0.00',
  `BAR` char(2) default NULL,
  `VERNR` int(11) default NULL,
  `MOMSKTONR` varchar(4) default NULL,
  `KTONR` varchar(4) default NULL,
  `DEBETBELOPP` decimal(10,2) default NULL,
  PRIMARY KEY  (`ORDERNR`,`FAKTURANR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KURESK`
--


/*!40000 ALTER TABLE `KURESK` DISABLE KEYS */;
LOCK TABLES `KURESK` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `KURESK` ENABLE KEYS */;

--
-- Table structure for table `LAGERSTELLEREG`
--

DROP TABLE IF EXISTS `LAGERSTELLEREG`;
CREATE TABLE `LAGERSTELLEREG` (
  `ARLAGST` char(1) NOT NULL default '',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `ARLAGHYLLA` varchar(10) default NULL,
  `ARLAGSALDO` decimal(10,2) default NULL,
  `ARINVGRP` char(3) default NULL,
  `ARABC` char(2) default NULL,
  `ARVALUTA` char(3) default NULL,
  `ARIPRIS` decimal(10,2) default '0.00',
  `ARIKVANT0` decimal(10,2) default '0.00',
  `ARIKVANT1` decimal(10,2) default '0.00',
  `ARIKVANT2` decimal(10,2) default '0.00',
  `ARKALKPRIS` decimal(10,2) default '0.00',
  `ARPLANKPRIS` decimal(10,2) default '0.00',
  `ARFRYSTKPRIS` decimal(10,2) default '0.00',
  `ARBESTKVANT` decimal(10,2) default '0.00',
  `ARBESTPUNKT` decimal(10,2) default '0.00',
  `AROMKOST` decimal(10,2) default '0.00',
  `RESERVERAT` decimal(10,2) default NULL,
  PRIMARY KEY  (`ARTIKELNR`,`ARLAGST`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LAGERSTELLEREG`
--


/*!40000 ALTER TABLE `LAGERSTELLEREG` DISABLE KEYS */;
LOCK TABLES `LAGERSTELLEREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `LAGERSTELLEREG` ENABLE KEYS */;

--
-- Table structure for table `LEVPRISER`
--

DROP TABLE IF EXISTS `LEVPRISER`;
CREATE TABLE `LEVPRISER` (
  `KUNDNR` varchar(10) NOT NULL default '',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `BENEMNING` varchar(60) default '0',
  `PRIS` decimal(10,2) default '0.00',
  `MATERIALKLASS` varchar(5) default '0',
  `ENHET` varchar(5) default '0',
  `XREF` varchar(30) default '0',
  PRIMARY KEY  (`KUNDNR`,`ARTIKELNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVPRISER`
--


/*!40000 ALTER TABLE `LEVPRISER` DISABLE KEYS */;
LOCK TABLES `LEVPRISER` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVPRISER` ENABLE KEYS */;

--
-- Table structure for table `LEVREG`
--

DROP TABLE IF EXISTS `LEVREG`;
CREATE TABLE `LEVREG` (
  `LEVNR` varchar(10) NOT NULL default '',
  `LEVORGNR` varchar(12) default NULL,
  `LEVNAMN` varchar(30) NOT NULL default '',
  `LEVADRESS` varchar(30) default NULL,
  `LEVPOSTNR` varchar(6) default NULL,
  `LEVPOSTADR` varchar(30) default NULL,
  `LEVLAND` varchar(30) default NULL,
  `LEVTFNNR` varchar(15) default NULL,
  `LEVFAXNR` varchar(15) default NULL,
  `LEVTELEX` varchar(10) default NULL,
  `LEVEMAIL` varchar(30) default NULL,
  `LEVPOSTGIRONR` varchar(10) default NULL,
  `LEVBANKGIRONR` varchar(10) default NULL,
  `LEVREFERENT` varchar(20) default NULL,
  `LEVREFTFN` varchar(15) default NULL,
  `LEVMOMSKOD` char(1) default '1',
  `LEVSKULD` decimal(10,2) default NULL,
  `LEVKONTO` varchar(4) default NULL,
  `LEVKUNDNR` varchar(30) default NULL,
  `LEVVALUTA` char(3) default NULL,
  `BETALVILKOR` char(3) default NULL,
  PRIMARY KEY  (`LEVNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVREG`
--


/*!40000 ALTER TABLE `LEVREG` DISABLE KEYS */;
LOCK TABLES `LEVREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVREG` ENABLE KEYS */;

--
-- Table structure for table `LEVRESK`
--

DROP TABLE IF EXISTS `LEVRESK`;
CREATE TABLE `LEVRESK` (
  `LEVNR` varchar(10) NOT NULL default '',
  `FAKTURANR` varchar(20) NOT NULL default '',
  `REGDATUM` date default NULL,
  `FAKTDATUM` date default NULL,
  `EXPIREDATUM` date default NULL,
  `FAKTTEXT` varchar(100) default NULL,
  `BAR` char(2) default NULL,
  `MOMSPROCENT` decimal(3,2) default NULL,
  `VALUTA` char(3) default NULL,
  `VALUTAKURS` decimal(3,2) default NULL,
  `VALUTABELOPP` decimal(10,2) default NULL,
  `LEVKTONR` varchar(4) default NULL,
  `FAKTBELOPP` decimal(10,2) default NULL,
  `MOMSKTONR` varchar(4) default NULL,
  `MOMSBELOPP` decimal(10,2) default NULL,
  `DEBETKONTONR` varchar(4) default NULL,
  `DEBETBELOPP` decimal(10,2) default NULL,
  `USERID` varchar(20) default NULL,
  `VERNR` int(11) default NULL,
  `BETALD` enum('J','N') default 'N',
  `BETALDDATUM` date default NULL,
  `OCRNR` varchar(20) default NULL,
  PRIMARY KEY  (`LEVNR`,`FAKTURANR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVRESK`
--


/*!40000 ALTER TABLE `LEVRESK` DISABLE KEYS */;
LOCK TABLES `LEVRESK` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVRESK` ENABLE KEYS */;

--
-- Table structure for table `LEVSETT`
--

DROP TABLE IF EXISTS `LEVSETT`;
CREATE TABLE `LEVSETT` (
  `LEVSETTNR` char(3) NOT NULL default '',
  `LEVSETTTEXT` varchar(150) NOT NULL default '',
  PRIMARY KEY  (`LEVSETTNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVSETT`
--


/*!40000 ALTER TABLE `LEVSETT` DISABLE KEYS */;
LOCK TABLES `LEVSETT` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVSETT` ENABLE KEYS */;

--
-- Table structure for table `LEVVILLKOR`
--

DROP TABLE IF EXISTS `LEVVILLKOR`;
CREATE TABLE `LEVVILLKOR` (
  `VILLKORSNR` char(3) NOT NULL default '',
  `VILLKORSTEXT` varchar(150) NOT NULL default '',
  PRIMARY KEY  (`VILLKORSNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVVILLKOR`
--


/*!40000 ALTER TABLE `LEVVILLKOR` DISABLE KEYS */;
LOCK TABLES `LEVVILLKOR` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVVILLKOR` ENABLE KEYS */;

--
-- Table structure for table `ORDERRADREG`
--

DROP TABLE IF EXISTS `ORDERRADREG`;
CREATE TABLE `ORDERRADREG` (
  `ORDERNR` varchar(10) NOT NULL default '',
  `ORDERRAD` int(4) NOT NULL default '0',
  `KUNDNR` varchar(10) NOT NULL default '',
  `RADORDERTYP` enum('N','D') default 'N',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `BENEMNING` varchar(60) default NULL,
  `LEVERANSVECKA` varchar(5) default NULL,
  `BESTELLT` decimal(10,2) NOT NULL default '0.00',
  `APRIS` decimal(10,2) NOT NULL default '0.00',
  `SUMMA` decimal(10,2) NOT NULL default '0.00',
  `MOMSKR` decimal(10,2) NOT NULL default '0.00',
  `LEVERERAT` decimal(10,2) default NULL,
  `RESTNOTERAT` decimal(10,2) default NULL,
  `RADRABATT` decimal(2,1) default NULL,
  `KALKYLPRIS` decimal(10,2) default NULL,
  `LEVDATUM` date default NULL,
  `ENHET` varchar(4) default 'ST',
  `FAKTURERAT` decimal(10,2) default NULL,
  PRIMARY KEY  (`ORDERNR`,`ORDERRAD`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ORDERRADREG`
--


/*!40000 ALTER TABLE `ORDERRADREG` DISABLE KEYS */;
LOCK TABLES `ORDERRADREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `ORDERRADREG` ENABLE KEYS */;

--
-- Table structure for table `ORDERREG`
--

DROP TABLE IF EXISTS `ORDERREG`;
CREATE TABLE `ORDERREG` (
  `ORDERNR` varchar(10) NOT NULL default '',
  `KUNDNR` varchar(10) NOT NULL default '',
  `ORDERTYP` enum('N','D','E','F') default 'N',
  `ORDERSTATUS` enum('A','N','F','B') default 'A',
  `ORDERDATUM` date default NULL,
  `LEVDATUM` date default NULL,
  `KUNDNAMN` varchar(60) default NULL,
  `KUNDADRESS` varchar(30) default NULL,
  `KUNDPOSTNR` varchar(6) default NULL,
  `KUNDPOSTADR` varchar(30) default NULL,
  `KUNDLAND` varchar(30) default NULL,
  `ERREF` varchar(20) default NULL,
  `LEVADRESS` varchar(30) default NULL,
  `LEVPOSTNR` varchar(6) default NULL,
  `LEVPOSTADR` varchar(30) default NULL,
  `LEVLAND` varchar(30) default NULL,
  `VARREF` varchar(20) default NULL,
  `SELJARE` varchar(20) default NULL,
  `GODSMERKE` varchar(100) default NULL,
  `BETVILLKTYP` enum('F','P','K') NOT NULL default 'F',
  `BETVILLKOR` char(3) default '001',
  `LEVVILLKOR` char(3) default '001',
  `LEVSETT` char(3) default '001',
  `PLOCKLISTA` enum('J','N') default 'J',
  `FOLJESEDEL` enum('J','N') default 'J',
  `FRAKTAVG` enum('J','N') default 'J',
  `SKATTEKOD` char(3) NOT NULL default '001',
  `MOMS` decimal(3,2) default NULL,
  `VALUTA` char(3) default 'SEK',
  `EXPORTKOD` char(3) default '001',
  `SPRAKKOD` char(3) default 'sv',
  `ORDERSUMMA` decimal(10,2) default NULL,
  `FRAKTSUMMA` decimal(10,2) default NULL,
  `FRAKTMOMSKR` decimal(10,2) default NULL,
  `ORDERMOMS` decimal(10,2) default NULL,
  `ORDERTOTAL` decimal(10,2) default NULL,
  PRIMARY KEY  (`ORDERNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ORDERREG`
--


/*!40000 ALTER TABLE `ORDERREG` DISABLE KEYS */;
LOCK TABLES `ORDERREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `ORDERREG` ENABLE KEYS */;

--
-- Table structure for table `PLOCKLISTEREG`
--

DROP TABLE IF EXISTS `PLOCKLISTEREG`;
CREATE TABLE `PLOCKLISTEREG` (
  `PLOCKNR` int(11) NOT NULL auto_increment,
  `ORDERNR` varchar(10) NOT NULL default '',
  `ORDERRAD` int(4) NOT NULL default '0',
  `KUNDNR` varchar(10) NOT NULL default '',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `BENEMNING` varchar(60) default NULL,
  `LEVERANSVECKA` varchar(5) default NULL,
  `BESTELLT` decimal(10,2) NOT NULL default '0.00',
  `ATTLEVERERA` decimal(10,2) NOT NULL default '0.00',
  `LEVERERAT` decimal(10,2) NOT NULL default '0.00',
  `PLOCKAT` decimal(10,2) NOT NULL default '0.00',
  `RESTNOTERAT` decimal(10,2) NOT NULL default '0.00',
  `LEVDATUM` date default NULL,
  `ENHET` varchar(4) default NULL,
  `PLOCKSTATUS` enum('P','U','B') default 'P',
  `PLOCKDATUM` date NOT NULL default '0000-00-00',
  PRIMARY KEY  (`PLOCKNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `PLOCKLISTEREG`
--


/*!40000 ALTER TABLE `PLOCKLISTEREG` DISABLE KEYS */;
LOCK TABLES `PLOCKLISTEREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `PLOCKLISTEREG` ENABLE KEYS */;

--
-- Table structure for table `PRISLISTA`
--

DROP TABLE IF EXISTS `PRISLISTA`;
CREATE TABLE `PRISLISTA` (
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `PRIS1` decimal(10,2) default '0.00',
  `PRIS2` decimal(10,2) default '0.00',
  `PRIS3` decimal(10,2) default '0.00',
  `PRIS4` decimal(10,2) default '0.00',
  `PRIS5` decimal(10,2) default '0.00',
  PRIMARY KEY  (`ARTIKELNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `PRISLISTA`
--


/*!40000 ALTER TABLE `PRISLISTA` DISABLE KEYS */;
LOCK TABLES `PRISLISTA` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `PRISLISTA` ENABLE KEYS */;

--
-- Table structure for table `PRODUKTGRUPP`
--

DROP TABLE IF EXISTS `PRODUKTGRUPP`;
CREATE TABLE `PRODUKTGRUPP` (
  `PRODKLASS` varchar(5) NOT NULL default '',
  `BESKRIVNING` varchar(30) default NULL,
  `MOMSKOD` varchar(5) default NULL,
  PRIMARY KEY  (`PRODKLASS`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `PRODUKTGRUPP`
--


/*!40000 ALTER TABLE `PRODUKTGRUPP` DISABLE KEYS */;
LOCK TABLES `PRODUKTGRUPP` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `PRODUKTGRUPP` ENABLE KEYS */;

--
-- Table structure for table `PROGRAM`
--

DROP TABLE IF EXISTS `PROGRAM`;
CREATE TABLE `PROGRAM` (
  `PRGNR` char(3) NOT NULL default '',
  `MENYAVD` varchar(20) default NULL,
  `MENYGRP` varchar(30) default NULL,
  `MENYTXT` varchar(30) default NULL,
  `PROGRAM` varchar(8) default NULL,
  PRIMARY KEY  (`PRGNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `PROGRAM`
--


/*!40000 ALTER TABLE `PROGRAM` DISABLE KEYS */;
LOCK TABLES `PROGRAM` WRITE;
INSERT INTO `PROGRAM` (`PRGNR`, `MENYAVD`, `MENYGRP`, `MENYTXT`, `PROGRAM`) VALUES ('026','Ekonomi','Valutaadministration','Ändra valuta','CHGVALW'),('025','Ekonomi','Valutaadministration','Ny valuta','ADDVALW'),('024','Ekonomi','Kostnadställeadministration','Lista kostnadsställen','LSTKSTW'),('023','Ekonomi','Kostnadställeadministration','Visa ett kostnadsställe','DSPKSTW'),('022','Ekonomi','Kostnadställeadministration','Ta bort kostnadställe',''),('021','Ekonomi','Kostnadställeadministration','Ändra kostnadställe',''),('020','Ekonomi','Kostnadställeadministration','Nytt kostnadställe','ADDKSTW'),('019','Ekonomi','Kontoadministration','Lista konton','LSTKTOW'),('018','Ekonomi','Kontoadministration','Visa konto','DSPKTOW'),('017','Ekonomi','Kontoadministration','Ta bort konto',''),('016','Ekonomi','Kontoadministration','Ändra konto','CHGKTOW'),('015','Ekonomi','Kontoadministration','Nytt konto','ADDKTOW'),('013','Ekonomi','Bokföring','Registrera verifikation','BOKFORSW'),('012','Administration','Funktionsadministration','Lista funktioner','LSTFNCW'),('011','Administration','Funktionsadministration','Ny funktion','ADDFNCW'),('010','Administration','Behörighetsadministration','Lista behörigheter','LSTRGTW'),('009','Administration','Behörighetsadministration','Visa behörighet',''),('007','Administration','Behörighetsadministration','Ändra behörighet',''),('006','Administration','Behörighetsadministration','Ny behörighet','ADDRGTW'),('003','Administration','Användaradministration','Ta bort användare','DELUSRW'),('005','Administration','Användaradministration','Lista användare','LSTUSRW'),('002','Administration','Användaradministration','Ändra användarinfo','CHGUSRW'),('014','Ekonomi','Bokföring','Registrera ver. standard','BOKFORSW'),('008','Administration','Behörighetsadministration','Ta bort behörighet','DELRGTW'),('004','Administration','Användaradministration','Visa en användare','DSPUSRW'),('001','Administration','Användaradministration','Ny användare','ADDUSRW'),('027','Ekonomi','Valutaadministration','Ta bort valuta','DELVALW'),('028','Ekonomi','Valutaadministration','Visa valuta','DSPVALW'),('029','Ekonomi','Valutaadministration','Lista valutor','LSTVALW'),('030','Ekonomi','Rapporter','Kontorapport','RPTKTOW'),('031','Ekonomi','Rapporter','Rapportgenerator','RPTGENW'),('032','Ekonomi','Räkenskapsår','Nytt bokföringsår','ADDBARW'),('033','Ekonomi','Räkenskapsår','Ändra bokföringsårsdata','CHGBARW'),('034','Administration','Företagsdata','Ny post','ADDFTGW'),('035','Administration','Företagsdata','Ändra post','CHGFTGW'),('036','Administration','Företagsdata','Visa företagsdata','DSPFTGW'),('037','Försäljning','Kunddata','Ny kund','ADDKUW'),('038','Försäljning','Kunddata','Ny leveransadress för kund','ADDLEVPW'),('039','Inköp','Leverantörsdata','Ny leverantör','ADDLEVW'),('040','Inköp','Leverantörsdata','Visa en leverantör','DSPLEVW'),('041','Inköp','Leverantörsdata','Ändra leverantörsdata','CHGLEVW'),('042','Ekonomi','Bokföring','Reg. leverantörsfaktura','LEVFAKTW'),('043','Ekonomi','Rapporter','Leverantörsreskontra','LEVRESKW'),('054','Administration','Betalningsvillkor','Lista betalningsvillkor','LSTBETVW'),('044','Ekonomi','Rapporter','Förfallna levfakturor','ATTBETW'),('045','Ekonomi','Rapporter','Saldolista','SDOLISW'),('046','Försäljning','Kunddata','Visa kunddata','DSPKUW'),('047','Försäljning','Kunddata','Ändra kunddata','CHGKUW'),('048','Försäljning','Kunddata','Lista kunder','LSTKUW'),('049','Administration','Företagsdata','Byta företag','BYTFTGW'),('050','Materialhantering','Artikeldata','Ny artikel','ADDARW'),('051','Materialhantering','Artikeldata','Visa grunddata för en artikel','DSPARW'),('052','Materialhantering','Artikeldata','Visa en artikels ekonomidata','DSPAREW'),('053','Materialhantering','Artikeldata','Ändra artikeldata','CHGARW'),('055','Administration','Betalningsvillkor','Nya betalningsvillkor','ADDBETVW'),('056','Materialhantering','Artikeldata','Lista artiklar','LSTARW'),('057','Administration','Betalningsvillkor','Ändra betalningsvillkor','CHGBETVW'),('058','Inköp','Beställningar','Registrera inköpsorder','ADDINKW'),('059','Inköp','Beställningar','(Ändra beställning)','CHGINKW'),('060','Inköp','Beställningar','(Annulera beställning)','DELINKW'),('061','Inköp','Beställningar','Visa beställning','DSPINKW'),('062','Inköp','Beställningar','Beställningsstock','LSTINKW'),('063','Inköp','Beställningar','Skriv ut beställning','PRTINKW'),('064','Inköp','Beställningar','(Avprickning följesedel)','UPDINKW'),('065','Försäljning','Kundorder','Registrera kundorder','ADDORDW'),('066','Försäljning','Kundorder','Ändra kundorder','CHGORDW'),('067','Försäljning','Kundorder','(Makulera kundorder)','DELORDW'),('068','Försäljning','Kundorder','Visa en kundorder','DSPORDW'),('069','Försäljning','Kundorder','Lista kundorder','LSTORDW'),('070','Försäljning','Kundorder','Skriva ut plocklista','PLORDW'),('071','Försäljning','Kundorder','(Skriva ut följesedel)','FSORDW'),('072','Försäljning','Kundorder','Fakturera kundorder','KUFAKTW'),('074','Administration','Företagsdata','Ny text i textregistret','ADDTXTW'),('073','Inköp','Leverantörsdata','Lista leverantörer','LSTLEVW'),('076','Administration','Leveransvillkor','Nya leveransvillkor','ADDLEVVW'),('075','Administration','Företagsdata','Radera post i textregistret','DELTXTW'),('077','Administration','Leveransvillkor','Lista leveransvillkor','LSTLEVVW'),('078','Administration','Leveranssätt','Nya leveranssätt','ADDLEVSW'),('079','Administration','Leveranssätt','Lista leveranssätt','LSTLEVSW'),('080','Ekonomi','Rapporter','Balansräkning','BALRPTW'),('081','Ekonomi','Rapporter','Huvudbok','HUVBOKW'),('082','Ekonomi','Rapporter','Dagbok','DAGBOKW'),('083','Försäljning','Kunddata','Lista kunders leveransplatser','LSTLEVPW'),('084','Administration','Företagsdata','Ny databasregistrering','ADDFORW'),('085','Administration','Företagsdata','Lista databaser','LSTFORW'),('086','Materialhantering','Artikeladmin.','Ny produktklass/produktgrupp','ADDPKDW'),('087','Materialhantering','Artikeladmin.','Lista produktklass/produktgrup','LSTPKDW'),('088','Ekonomi','Räkenskapsår','Visa bokföringsår','DSPBARW'),('089','Administration','Företagsdata','Lista företagsdata','LSTFTGW'),('090','Ekonomi','Rapporter','Resultatrapport','RESRPTW'),('091','Ekonomi','Räkenskapsår','Lista alla räkenskapsår','LSTBARW'),('092','Försäljning','Kunddata','Söka kunder','SRCHKUW'),('093','Ekonomi','Rapporter','Skapa SIE-fil','RPTSIEW'),('094','Försäljning','Kundorder','Pricka av plocklista','PLCHGW'),('095','Ekonomi','Rapporter','Kundreskontra','KURESKW'),('096','Administration','Företagsdata','Lista texter i TEXTREG','LSTTXTW'),('097','Administration','Företagsdata','Visa en post i TEXTREG','DSPTXTW'),('098','Materialhantering','Artikeldata','Söka artikel','SRCHARW'),('099','Ekonomi','Bokföring','Reg. betald kundfaktura','KUFAKTBW'),('100','Materialhantering','Artikeladmin.','Lista prislistor','LSTPRISW'),('101','Materialhantering','Artikeladmin.','Ladda nya prislistor','ADDPRISW'),('102','Materialhantering','Artikeladmin.','Ändra i prislistor','CHGPRISW'),('103','Administration','Funktionsadministration','Lista program/moduler','LSTPGMW'),('104','Försäljning','Offerter','Registrera offert','ADDOFFW'),('105','Försäljning','Offerter','Visa en offert','DSPOFFW'),('106','Materialhantering','Artikeladmin.','Visa lagerställepost','DSPLSW'),('107','Materialhantering','Artikeladmin.','Radera lagerställepost','DELLSW'),('108','Materialhantering','Artikeladmin.','Ändra lagerställepost','CHGLSW'),('109','Försäljning','Offerter','Ändra en offert','CHGOFFW'),('110','Försäljning','Offerter','Radera en offert','DELOFFW'),('111','Försäljning','Offerter','Skriv ut en offert','PRTOFFW'),('112','Försäljning','Offerter','Göra en offert till order','OFF2ORDW'),('113','Administration','Behörighetsadministration','Tilldela en användare total be','TOTRGTW'),('114','Administration','Betalningsvillkor','Radera betalningsvillkor','DELBETVW');
UNLOCK TABLES;
/*!40000 ALTER TABLE `PROGRAM` ENABLE KEYS */;

--
-- Table structure for table `RIGHTS`
--

DROP TABLE IF EXISTS `RIGHTS`;
CREATE TABLE `RIGHTS` (
  `USERID` varchar(20) NOT NULL default '',
  `TRNSID` varchar(8) NOT NULL default '',
  PRIMARY KEY  (`USERID`,`TRNSID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `RIGHTS`
--


/*!40000 ALTER TABLE `RIGHTS` DISABLE KEYS */;
LOCK TABLES `RIGHTS` WRITE;
INSERT INTO `RIGHTS` (`USERID`, `TRNSID`) VALUES ('ADMIN','ADDBARW'),('ADMIN','ADDRGTW'),('ADMIN','BARADD'),('ADMIN','BYTFTGW'),('ADMIN','PRGLST'),('ADMIN','RGTADD'),('ADMIN','TRNSLST'),('OLFIX','ADDRGTW'),('OLFIX','ARICHK'),('OLFIX','BARDSP'),('OLFIX','KTOCHK'),('OLFIX','KTOLST'),('OLFIX','KTOVIEW'),('OLFIX','PRGLST'),('OLFIX','RGTADD'),('OLFIX','RGTCHK'),('OLFIX','RGTDEL'),('OLFIX','RGTLST'),('OLFIX','TRHDADD'),('OLFIX','TRNSADD'),('OLFIX','TRNSDEL'),('OLFIX','USERADD'),('OLFIX','USERLST'),('OLFIX','VERUPD'),('TESTARE','LSTUSRW'),('TESTARE','PRGLST'),('TESTARE','RGTCHK'),('TESTARE','USERADD'),('TESTARE','USERDSP'),('TESTARE','USERLST');
UNLOCK TABLES;
/*!40000 ALTER TABLE `RIGHTS` ENABLE KEYS */;

--
-- Table structure for table `STDLEVPLATS`
--

DROP TABLE IF EXISTS `STDLEVPLATS`;
CREATE TABLE `STDLEVPLATS` (
  `STDLEVPLATS` char(3) NOT NULL default '',
  `KUNDNR` varchar(10) NOT NULL default '',
  `ADRESS` varchar(30) NOT NULL default '',
  `POSTNR` varchar(6) NOT NULL default '',
  `POSTADR` varchar(30) NOT NULL default '',
  `LAND` varchar(30) default NULL,
  PRIMARY KEY  (`STDLEVPLATS`,`KUNDNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `STDLEVPLATS`
--


/*!40000 ALTER TABLE `STDLEVPLATS` DISABLE KEYS */;
LOCK TABLES `STDLEVPLATS` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `STDLEVPLATS` ENABLE KEYS */;

--
-- Table structure for table `TEXTREG`
--

DROP TABLE IF EXISTS `TEXTREG`;
CREATE TABLE `TEXTREG` (
  `TEXTNR` char(3) NOT NULL default '',
  `TXT` text,
  PRIMARY KEY  (`TEXTNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `TEXTREG`
--


/*!40000 ALTER TABLE `TEXTREG` DISABLE KEYS */;
LOCK TABLES `TEXTREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `TEXTREG` ENABLE KEYS */;

--
-- Table structure for table `TRANSID`
--

DROP TABLE IF EXISTS `TRANSID`;
CREATE TABLE `TRANSID` (
  `TRNSID` varchar(8) NOT NULL default '',
  `TRNSTXT` varchar(60) default NULL,
  PRIMARY KEY  (`TRNSID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `TRANSID`
--


/*!40000 ALTER TABLE `TRANSID` DISABLE KEYS */;
LOCK TABLES `TRANSID` WRITE;
INSERT INTO `TRANSID` (`TRNSID`, `TRNSTXT`) VALUES ('ARICHK','Kontrollera om visst bokföringsår finns'),('BARDSP','Hämta data för angivet bokföringsår'),('BARCHK','Kontrollera om visst bokföringsår finns'),('BOKF','Bokföringsprogram'),('FORDSP','Visa info om databas nr x'),('FTGUPD','Uppdatera företagsdata'),('KSTADD','Nyupplägg av kostnadsställe'),('KSTCHK','Kontrollera om visst kostnadställe finns'),('KSTDSP','Visa info för ett kostnadställe'),('KSTLST','Lista kostnadsställen på skärm'),('KTOADD','Lägga till en ny post i konto'),('KTOCHG','Ändra info för ett kontonr'),('KTOCHK','Kontrollera om visst konto finns'),('KTODEL','Ta bort post i konto (endast utan transaktioner)'),('KTODSP','Visa info på ett konto'),('KTOLST','Lista alla konton, nr och text'),('KTORPT','Lista alla poster i tabellen VERRAD'),('KTOUPD','Uppdatera konto med antingen debet eller kredit'),('KTOVIEW','Visa kontonr och benämning på skärm'),('PRGLST','Lista program'),('RGTADD','Lägga till behörighet till transaktioner'),('RGTCHK','Kontrolera användares behörighet'),('RGTDEL','Ta bort behörighet till transaktioner'),('RGTDSP','Visa behörigheter för en användare'),('RGTLST','Lista alla behörigheter'),('TRHDADD','Lägga till ny loggpost i TRHD'),('TRNSADD','Ny post i TRANSID'),('TRNSCHG','Ändra post i TRANSID'),('TRNSDEL','Ta bort post i TRANSID'),('TRNSDSP','Visa enstaka TRANSID'),('TRNSLST','Lista alla TRANSID'),('USERADD','Ny post i USER'),('USERCHG','Ändra post i USER'),('USERDEL','Ta bort post i USER'),('USERDSP','Visa en användare'),('USERLST','Lista alla användare'),('VALLST','Lista valutor'),('VALADD','Lägga upp en ny valuta'),('VALCHG','Ändra valutainformation'),('VALDEL','Ta bort en valuta'),('VALDSP','Visa en valuta'),('VERUPD','Nyuppläggning av verifikat'),('VERDSP','Visa enstaka verifikation'),('VRDADD','Ny detaljpost för verifikation till VERD'),('VRHADD','Ny huvudpost för verifikation till VERH'),('WRREC','Skriva post till tempfilen /tmp/vernr.txt'),('ATTBET','Lista leverantörsfakturor att betala'),('BARADD','Lägga upp nytt bokföringsår'),('BARCHG','Ändra data för angivet bokföringsår'),('BARFND','Hitta bokföringsår för angivet datum'),('BETDSP','Visa ett betalningsvillkor'),('FTGADD','Lägga upp en ny företagspost'),('FTGDSP','Visa företagsdata'),('FTGLST','Lista posttyper för företagsdata'),('FTGLIS','Lista företagsdata'),('KUADD','Registrera nya kunder'),('KUCHG','Ändra kunddata'),('KUCHK','Kontrollera om kundnr finns'),('KUDSP','Visa kunddata'),('KULST','Lista kunder, kundnr och namn'),('LEVADD','Lägga upp en ny leverantör'),('LEVCHG','Ändra leverantörsdata'),('LEVDSP','Visa en leverantör'),('LEVLST','Lista leverantörer,nr och namn'),('LRESRPT','Lista alla obetalda poster i tabellen LEVRESK'),('LRESADD','Ny post i leverantörsreskontran'),('RPTCRE','Rapportgenerator. Skapa rapporter'),('SLPADD','Standardleveransplats'),('TRNTST','Detta är en testfunktion'),('ARCHK','Kontrollera om artikelnummer finns'),('ARADD','Lägga upp en ny artikel'),('AR2ADD','Lägga upp ny artikel i lagerställeregister'),('ARDSP','Visa grunddata för en artikel'),('ARDSPL','Visa lagerdata för en artikel'),('ARCHG','Ändra grunddata för en artikel'),('ARCHGL','Ändra lagerställedata för en artikel'),('BETLST','Lista betalningsvillkor'),('BETADD','Lägga upp ett nytt betalningsvillkor'),('ARLST','Lista artiklar(artikelnr,benämn1,benämn2)'),('BETCHG','Ändra data för betalningsvillkor'),('TXTDSP','Visa texter ur TEXTREG'),('TXTADD','Lägg upp en ny post i TEXTREG'),('INKADD','Lägga upp en ny inköpsorder'),('INKRADD','Lägga upp en ny inköpsorderrad'),('TXTDEL','Radera post i TEXTREG'),('INKRLST','Lista alla rader på angiven inköpsorder'),('INKHDSP','Visa orderhuvud för angiven inköpsorder'),('INKLST','Beställningsstock'),('LEVVDSP','Visa ett leveransvillkor'),('LEVSDSP','Visa ett leveranssätt'),('LEVVADD','Lägga upp ett nytt leveransvillkor'),('LEVSADD','Lägga upp ett nytt leveranssätt'),('LEVVLST','Lista leveransvillkor'),('LEVSLST','Lista leveranssätt'),('VERHDSP','Hämta mindatum och maxdatum för angivet bokf.år'),('VERHLST','Lista verifikationers huvudposter för önskat bokföringsår'),('HBOKRPT','Huvudboksrapport'),('DBOKRPT','Dagboksrapport'),('PRTAPI','Utskriftsinterface'),('LEVPLST','Lista kunders leveransadresser'),('FORCHK','Kontr. om databas finns i tabell DATABAS'),('FORADD','Ny databas i tabellen DATABAS'),('FORLST','Lista databaser i tabell DATABAS'),('PKDADD','Ny produktgrupp/produktkod/produktklass'),('PKDLST','Lista produktgrupper/produktkoder/produktklasser'),('WKUDSP','Visa begränsade kunddata för webbkund'),('ARLSTL','Lista artiklar med lagersaldo'),('ARLIS','Lista artiklar för angiven produktklass'),('ARLSPK','Lista artiklar för angiven produktkod'),('AR2UPD','Uppdatera artikelpost i LAGERSTELLEREG'),('BARLST','Lista bokföringsår'),('KUSRCH','Söka kunder på namn, postnr, tfnnr eller postadr'),('LEVPDSP','Visa en standardleveransplats'),('ORDADD','Nyupplägg av kundorderhuvud'),('ORDCHK','Kontrollera diverse uppgifter på kundorder'),('ORDDSP','Visa en kundorders huvudpost'),('ORDRDSP','Visa en kundorders orderrader'),('PKDDSP','Visa en produktgrupp/produktkod/produktklass'),('SIEEXPK','SIE-export av kontoplan'),('SIEEXPR','SIE-export av resultat'),('SIEEXPV','SIE-export av verifikat'),('DBCHK','Lista databaser registrerade i databasen mysql'),('ORDLST2','Lista kundorder med begränsad information'),('ORDLST','Lista kundorder'),('PICKADD','Nytt plock av kundorderrad'),('PICKDSP','Visa plockade men ej utskrivna plock'),('PICKLST','Lista avprickade kundorderrader'),('KRESADD','Ny post till kundreskontran'),('ORADUPD','Uppdatera önskat fält i ORDERRADREG'),('ORDRUPD','Uppdatera ORDERRADREG'),('ORDUPD','Uppdatera önskat fält i ORDERREG'),('ARLSPK2','Lista artiklar/produktkod med saldo'),('KRESLST','Lista poster i kundreskontran med expiredatum'),('ORDRADD','Lägga upp ny rad på kundorder'),('ARSRCH','Söka artiklar'),('FAKTDSP','Visa data på kundfaktura'),('KRELST','Lista poster i kundreskontran med fakturadatum'),('KRESUPD','Uppdatering av betalda kundfakturor'),('OFFADD','Nyupplägg av offerthuvud'),('OFFRADD','Nyupplägg av offertrad'),('OFFDSP','Visa en offerts huvudpost'),('OFFLST','Lista offerter'),('OFFDEL','Radera offerter'),('ORDCHG','Ändra kundorder'),('ORDRCHG','Ändra rad på kundorder'),('PRISDSP','Visa prislistepriser på önskad artikel'),('PRISUPD','Uppdatera PRISLISTA'),('TXTLST','Lista poster i TEXTREG');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TRANSID` ENABLE KEYS */;

--
-- Table structure for table `TRHD`
--

DROP TABLE IF EXISTS `TRHD`;
CREATE TABLE `TRHD` (
  `TRNSNR` int(11) NOT NULL auto_increment,
  `TRNSID` varchar(8) NOT NULL default '',
  `TID` varchar(20) NOT NULL default '',
  `USERID` varchar(20) default NULL,
  `TRNSDATA` varchar(255) default NULL,
  PRIMARY KEY  (`TRNSNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `TRHD`
--


/*!40000 ALTER TABLE `TRHD` DISABLE KEYS */;
LOCK TABLES `TRHD` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `TRHD` ENABLE KEYS */;

--
-- Table structure for table `USR`
--

DROP TABLE IF EXISTS `USR`;
CREATE TABLE `USR` (
  `USERID` varchar(20) NOT NULL default '',
  `NAMN` varchar(30) default NULL,
  `AVD` varchar(10) default NULL,
  `GRUPP` varchar(10) default NULL,
  PRIMARY KEY  (`USERID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `USR`
--


/*!40000 ALTER TABLE `USR` DISABLE KEYS */;
LOCK TABLES `USR` WRITE;
INSERT INTO `USR` (`USERID`, `NAMN`, `AVD`, `GRUPP`) VALUES ('OLFIX','Olfix Superuser','IT','Stab'),('TESTARE','Testare Test','Prov','Utv'),('ADMINA','Admin Adminstratör','IT','Stab'),('ADMIN','Jan Olfixsson','Ekonomi','Stab');
UNLOCK TABLES;
/*!40000 ALTER TABLE `USR` ENABLE KEYS */;

--
-- Table structure for table `VALUTA`
--

DROP TABLE IF EXISTS `VALUTA`;
CREATE TABLE `VALUTA` (
  `VALUTAID` char(3) NOT NULL default '',
  `LAND` varchar(15) default NULL,
  `SALJ` decimal(3,2) default NULL,
  `KOP` decimal(3,2) default NULL,
  `BETECKNING` varchar(15) default NULL,
  PRIMARY KEY  (`VALUTAID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `VALUTA`
--


/*!40000 ALTER TABLE `VALUTA` DISABLE KEYS */;
LOCK TABLES `VALUTA` WRITE;
INSERT INTO `VALUTA` (`VALUTAID`, `LAND`, `SALJ`, `KOP`, `BETECKNING`) VALUES ('DKK','Danmark','1.22','1.22','Kronor'),('NOK','Norge','1.23','1.23','Kronor'),('NYZ','Nya Zeeland','4.45','4.45','Dollar'),('SAR','Saudiarabien','2.40','2.40','Riyal'),('HKD','Honkong','0.00','0.00','Dollar'),('MYR','Malaysia','2.36','2.36','Ringgit'),('SGD','Singapore','5.08','5.08','Dollar'),('CAD','Kanada','5.66','5.66','Dollar'),('AUD','Australien','5.03','5.03','Dollar'),('USD','USA','8.97','8.97','Dollar'),('JPY','Japan','7.38','7.38','Yen'),('GBP','Storbritanien','14.26','14.26','Pund'),('EUR','Europa','9.08','9.08','Euro'),('CHF','Schweiz','0.00','0.00','France'),('SEK','Sverige','0.99','0.99','Kronor'),('EEK','Estland','0.59','0.57','Kronor');
UNLOCK TABLES;
/*!40000 ALTER TABLE `VALUTA` ENABLE KEYS */;

--
-- Table structure for table `VERHUVUD`
--

DROP TABLE IF EXISTS `VERHUVUD`;
CREATE TABLE `VERHUVUD` (
  `VERNR` int(11) NOT NULL default '0',
  `ARID` char(2) NOT NULL default '',
  `VERDATUM` date default NULL,
  `REGDAT` date default NULL,
  `DEBET` decimal(10,2) default NULL,
  `KREDIT` decimal(10,2) default NULL,
  `VERTEXT` varchar(60) default NULL,
  `KORRIGERAR` int(11) default NULL,
  `KORRIGERAD` int(11) default NULL,
  `USERID` varchar(20) default NULL,
  PRIMARY KEY  (`VERNR`,`ARID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `VERHUVUD`
--


/*!40000 ALTER TABLE `VERHUVUD` DISABLE KEYS */;
LOCK TABLES `VERHUVUD` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `VERHUVUD` ENABLE KEYS */;

--
-- Table structure for table `VERRAD`
--

DROP TABLE IF EXISTS `VERRAD`;
CREATE TABLE `VERRAD` (
  `VERNR` int(11) NOT NULL default '0',
  `RADNR` smallint(6) NOT NULL default '0',
  `ARID` char(2) NOT NULL default '',
  `KTONR` varchar(4) default NULL,
  `BELOPP` decimal(10,2) default NULL,
  `DK` enum('D','K') default NULL,
  `KSTALLE` varchar(4) default NULL,
  `PROJEKT` varchar(4) default NULL,
  `SUBKTO` varchar(4) default NULL,
  `DEFINITIV` enum('J','N') default 'N',
  `STRUKEN` enum('J','N') default 'N',
  PRIMARY KEY  (`VERNR`,`RADNR`,`ARID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `VERRAD`
--


/*!40000 ALTER TABLE `VERRAD` DISABLE KEYS */;
LOCK TABLES `VERRAD` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `VERRAD` ENABLE KEYS */;

--
-- Current Database: `olfixtst`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `olfixtst` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `olfixtst`;

--
-- Table structure for table `ARTIKELREG`
--

DROP TABLE IF EXISTS `ARTIKELREG`;
CREATE TABLE `ARTIKELREG` (
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `ARBENEMNING1` varchar(60) NOT NULL default '',
  `ARBENEMNING2` varchar(60) default NULL,
  `ARENHET` varchar(5) default NULL,
  `ARFPRIS` decimal(10,2) default NULL,
  `ARLEDTID` char(3) default NULL,
  `ARPRODKLASS` varchar(5) default NULL,
  `ARPRODKTO` varchar(5) default NULL,
  `ARLEVNR1` varchar(10) default NULL,
  `ARLEVNR2` varchar(10) default NULL,
  `ARLEVNR3` varchar(10) default NULL,
  `ARNETTOVIKT` decimal(10,2) default NULL,
  `ARARTTYP` enum('0','1','2','3','4') default '0',
  `ARSTRUKT` enum('','B','I','T','F') default '',
  `ARURBENEMNING` varchar(60) default NULL,
  `ARURLAND` varchar(30) default NULL,
  `ARURARTNR` varchar(30) default NULL,
  `ARTULLTAX` varchar(10) default NULL,
  `ARVOLYM` decimal(4,3) default NULL,
  `AROMRFAKTOR` int(11) NOT NULL default '1',
  PRIMARY KEY  (`ARTIKELNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ARTIKELREG`
--


/*!40000 ALTER TABLE `ARTIKELREG` DISABLE KEYS */;
LOCK TABLES `ARTIKELREG` WRITE;
INSERT INTO `ARTIKELREG` (`ARTIKELNR`, `ARBENEMNING1`, `ARBENEMNING2`, `ARENHET`, `ARFPRIS`, `ARLEDTID`, `ARPRODKLASS`, `ARPRODKTO`, `ARLEVNR1`, `ARLEVNR2`, `ARLEVNR3`, `ARNETTOVIKT`, `ARARTTYP`, `ARSTRUKT`, `ARURBENEMNING`, `ARURLAND`, `ARURARTNR`, `ARTULLTAX`, `ARVOLYM`, `AROMRFAKTOR`) VALUES ('1000-1001','Att använda GNU/LINUX','Linus Walleij','ST','117.00','7','1000','','100','200','300','0.00','2','','Att använda GNU/LINUX','Sverige','ISBN 91-44-03400-8','','0.000',1),('1000-1002','Linux MAGNUM','Jack Tacket,Jr och Steven Burn','ST','117.00','7','1000','','100','200','300','0.00','2','','Linux MAGNUM','Sverige','ISBN 0-7645-2508-5','','0.000',1),('1000-1003','Linux På egen hand','Steve Oualline och Eric Foster','ST','117.00','7','1000','','100','200','300','0.00','2','','Linux På egen hand','Sverige','ISBN 013-019716-5','','0.000',1),('1000-1004','C++ programmering','Stephen Prata','ST','117.00','7','1001','','100','200','300','0.00','2','','Linux På egen hand','Sverige','ISBN 91-86201-34-4','','0.000',1),('1000-1005','Programming with Qt','Matthias Kalle Dalheimer','ST','117.00','7','1002','','100','200','300','0.00','2','','Programming with Qt','Sverige','ISBN 0-596-00064-2','','0.000',1),('1000-1006','The C Programming language','Brian W Kernighan och Dennis M','ST','117.00','7','1003','','100','200','300','0.00','2','','The C Programming language','USA','ISBN 91-970296-45','','0.000',1),('1000-1007','The C Programming lang.Facit','Clovis Tondo,Scott Gimpel','ST','117.00','7','1003','','100','200','300','0.00','2','','The C Programming lang.Facit','USA','ISBN 91-970296-88','','0.000',1),('1000-1008','Vägen till C','Ulf Bilting,Jan Skansholm','ST','117.00','7','1003','','100','200','300','0.00','2','','Vägen till C','Sverige','ISBN 91-44-26732-0','','0.000',1),('1000-1009','Arbeta med C','J A Illik','ST','117.00','7','1003','','100','200','300','0.00','2','','Arbeta med C','Sverige','ISBN 91-86200-40-2','','0.000',1),('1000-1010','Nyckeln till C','Alan C Plantz','ST','117.00','7','1003','','100','200','300','0.00','2','','Nyckeln till C','Sverige','ISBN 91-86200-75-5','','0.000',1),('1000-1011','Professional Linux Programming','Neil Mattew and Richard Stones','ST','117.00','7','1000','','100','200','300','0.00','2','','Professional Linux Programming','USA','ISBN 1861003013','','0.000',1),('1000-1012','Qt Programming in 24 Hours','Daniel Solin','ST','117.00','7','1002','','100','200','300','0.00','2','','Qt Programming in 24 Hours','USA','ISBN 0-672-31869-5','','0.000',1),('1000-1013','C++ GUI Programming with Qt 3','Jasmine Blanchette, Mark Summerfield','ST','117.00','7','1002','','100','200','300','0.00','2','','C++ GUI programming with Qt 3','USA','ISBN 0-13-124072-2','','0.000',1),('1000-1014','Practical Qt','Mattias Kalle Dalheimer,Jesper Pedersen','ST','117.00','7','1002','','100','200','300','0.00','2','','Practical Qt','Tyskland','ISBN 3-89864-260-1','','0.000',1),('2000-9999','Test','Björn','st','25.00',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0',NULL,NULL,NULL,NULL,NULL,NULL,1);
UNLOCK TABLES;
/*!40000 ALTER TABLE `ARTIKELREG` ENABLE KEYS */;

--
-- Table structure for table `BETVILKOR`
--

DROP TABLE IF EXISTS `BETVILKOR`;
CREATE TABLE `BETVILKOR` (
  `BETVILKOR` char(3) NOT NULL default '',
  `DAGAR` char(3) default NULL,
  `BESKRIVNING` varchar(40) NOT NULL default '',
  PRIMARY KEY  (`BETVILKOR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `BETVILKOR`
--


/*!40000 ALTER TABLE `BETVILKOR` DISABLE KEYS */;
LOCK TABLES `BETVILKOR` WRITE;
INSERT INTO `BETVILKOR` (`BETVILKOR`, `DAGAR`, `BESKRIVNING`) VALUES ('021','30','30 dagar netto'),('022','25','25 dagar netto'),('023','10','10 dagar netto'),('024','0','Kontantköp'),('025','30','Postförskott'),('026','60','60 dagar netto'),('001','30','30 dagar netto'),('002','20','20 dagar netto'),('003','10','10 dagar netto'),('004','0','Kontantköp'),('005','30','Postförskott'),('006','60','60 dagar netto'),('012','120','120 dagar netto');
UNLOCK TABLES;
/*!40000 ALTER TABLE `BETVILKOR` ENABLE KEYS */;

--
-- Table structure for table `BOKFAR`
--

DROP TABLE IF EXISTS `BOKFAR`;
CREATE TABLE `BOKFAR` (
  `ARID` char(2) NOT NULL default '',
  `BENAMNING` varchar(25) default NULL,
  `ARSTART` date default NULL,
  `ARSLUT` date default NULL,
  `ARLAST` enum('J','N') default 'N',
  `SENVERDAT` date default NULL,
  `VERNR` int(11) default NULL,
  `KONTOPLAN` varchar(15) default NULL,
  `BESKATTNINGSAR` varchar(4) default NULL,
  PRIMARY KEY  (`ARID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `BOKFAR`
--


/*!40000 ALTER TABLE `BOKFAR` DISABLE KEYS */;
LOCK TABLES `BOKFAR` WRITE;
INSERT INTO `BOKFAR` (`ARID`, `BENAMNING`, `ARSTART`, `ARSLUT`, `ARLAST`, `SENVERDAT`, `VERNR`, `KONTOPLAN`, `BESKATTNINGSAR`) VALUES ('SS','2003-01-01--2003-12-31','2003-01-01','2003-12-31','N','0000-00-00',987124,'EUBAS2003','2003'),('ST','2003-01-01--2003-12-31','2003-01-01','2003-12-31','N','0000-00-00',987124,'EUBAS2003','2003'),('AD','2003-01-01--2003-12-31','2003-01-01','2003-12-31','N','2004-01-02',101,'EUBAS97','2003'),('AE','2005-01-01--2005-12-31','2005-01-01','2005-12-31','N','0000-00-00',1,'EUBAS2003','2005'),('09','test','2009-01-01','2009-12-31','N','0000-00-00',1,'test','2009'),('ZZ','2006-01-01--2006-12-31','2006-01-01','2006-12-31','N','0000-00-00',79,'TEST2006','2006');
UNLOCK TABLES;
/*!40000 ALTER TABLE `BOKFAR` ENABLE KEYS */;

--
-- Table structure for table `FTGDATA`
--

DROP TABLE IF EXISTS `FTGDATA`;
CREATE TABLE `FTGDATA` (
  `POSTTYP` varchar(5) NOT NULL default '',
  `POSTBESKR` varchar(60) default NULL,
  `FDATA` text,
  PRIMARY KEY  (`POSTTYP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `FTGDATA`
--


/*!40000 ALTER TABLE `FTGDATA` DISABLE KEYS */;
LOCK TABLES `FTGDATA` WRITE;
INSERT INTO `FTGDATA` (`POSTTYP`, `POSTBESKR`, `FDATA`) VALUES ('FNAMN','Företagsnamn','PROGRAM AB'),('FTGNR','Företagsnummer','991199-1991'),('ADR1','Postadress','Box 72'),('ADR2','Postnummer till Postadress','199 98'),('ADR3','Ort till Postadress','PROGSTAD'),('ADR4','Besöksadress','Syntaxvägen 99'),('ADR5','Postnr till Besöksadress','199 98'),('ADR6','Ort till Besöksadress','PROGSTAD'),('ADR7','Godsadress','Verktygsgatan 11'),('ADR8','Postnr till Godsadress','199 97'),('ADR9','Ort till Godsadress','PROGSTAD'),('TFNVX','Telefonnummer till vx','09-199300'),('TFN1','Telefonnummer','09-199300'),('TFN2','Mobiltelefonnummer','070-98765411'),('TFNMB','Mobiltelefonnummer','070-98765411'),('TFAX','Telefaxnummer','09-199397'),('TELEX','Telexnummer','12345'),('EML1','E-mailadress','jan.pihlgren.se'),('MOMSI','Momskonto, ingående moms','2641'),('MOMSU','Momskonto, utgående moms','2611'),('MOMS1','Momssats 1','25'),('MOMS2','Momssats 2','12'),('MOMS3','Momssats 3','6'),('MOMS4','Momssats 4',' '),('MOMS5','Momssats 5',' '),('AUTOK','Automatkontering J/N?,\"N','N'),('KORNR','Senast använda kundordernr','201'),('BF1','Bokföringsperiod 1','Januari'),('BF2','Bokföringsperiod 2','Februari'),('BF3','Bokföringsperiod 3','Mars'),('BF4','Bokföringsperiod 4','April'),('BF5','Bokföringsperiod 5','Maj'),('BF6','Bokföringsperiod 6','Juni'),('BF7','Bokföringsperiod 7','Juli'),('BF8','Bokföringsperiod 8','Augusti'),('BF9','Bokföringsperiod 9','September'),('BF10','Bokföringsperiod 10','Oktober'),('BF11','Bokföringsperiod 11','Novemper'),('BF12','Bokföringsperiod 12','December'),('BF13','Bokföringsperiod 13','Januari'),('INKNR','Senast använda inköpsordernr','0'),('SNIKD','Branschtillhörighet','82301'),('OFFNR','Senast använda offertnummer','107'),('FAKNR','Senaste fakturanr på kundorder','50'),('FKNR2','Senaste fakturanr p kundorder,serie 2','100075'),('FKNRS','Antal fakturanummerserier,default = 1','1'),('KFKTO','Konto för kundfordringar',NULL),('INKTO','Konto för inbetalningar',NULL),('SKUNR','Senast använda kundnummer','4379'),('BGNR','Bankgironummer','9999-9999'),('PGNR','Postgironummer','999999-9'),('WKUNR','Senast använda webbkundnummer','4379\"'),('MNR','Momsnummer','9558-9999-06');
UNLOCK TABLES;
/*!40000 ALTER TABLE `FTGDATA` ENABLE KEYS */;

--
-- Table structure for table `INKRADREG`
--

DROP TABLE IF EXISTS `INKRADREG`;
CREATE TABLE `INKRADREG` (
  `INKORDNR` varchar(10) NOT NULL default '',
  `INKORDRADNR` int(4) NOT NULL default '0',
  `ARTIKELNR` varchar(30) default NULL,
  `BENEMNING` varchar(30) default NULL,
  `LEVARTIKELNR` varchar(30) default NULL,
  `LEVBENEMNING` varchar(30) default NULL,
  `ENHET` varchar(5) default NULL,
  `BESTANTAL` decimal(10,2) default NULL,
  `LEVERERAT` decimal(10,2) default NULL,
  `RESTNOTERAT` decimal(10,2) default NULL,
  `INKPRIS` decimal(10,2) default NULL,
  `LEVVECKA` varchar(5) default NULL,
  `TORDNR` int(6) default NULL,
  `OPNR` int(6) default NULL,
  PRIMARY KEY  (`INKORDNR`,`INKORDRADNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `INKRADREG`
--


/*!40000 ALTER TABLE `INKRADREG` DISABLE KEYS */;
LOCK TABLES `INKRADREG` WRITE;
INSERT INTO `INKRADREG` (`INKORDNR`, `INKORDRADNR`, `ARTIKELNR`, `BENEMNING`, `LEVARTIKELNR`, `LEVBENEMNING`, `ENHET`, `BESTANTAL`, `LEVERERAT`, `RESTNOTERAT`, `INKPRIS`, `LEVVECKA`, `TORDNR`, `OPNR`) VALUES ('6712',10,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','D/A Omvandlare 12-bit','ST','25.00','0.00','25.00','95.00','351',0,0),('23',10,'1173-1175','Spänningsregulator positiv',NULL,NULL,'uA78H','0.00','0.00','100.00','0.00','100',30,4084),('19',40,'1173-7513','Microprocessor','SY6502','','ST','20.00','5.00','15.00','63.00','402',0,0),('19',30,'1173-7300','1024x1 bit static RAM','21022DC','','ST','20.00','0.00','20.00','10.05','402',0,0),('19',20,'1173-7300','1024x1 bit static RAM','21022DC','','ST','20.00','10.00','10.00','10.05','401',0,0),('19',10,'1173-7206','Dual Monostable Multivibrator','SN74LS123N','','ST','20.00','0.00','20.00','4.75','402',0,0),('18',10,'1173-0911','Spänningsregulator positiv','uA7805AWC','','ST','10.00','0.00','10.00','1.50','402',0,0),('18',30,'1173-1175','Spänningsregulator positiv','uA78H05ASC','Voltage regulator 5V','ST','10.00','0.00','10.00','30.00','402',0,0),('18',50,'1173-1447','Timerkrets','ICM7555','Timer','ST','10.00','0.00','10.00','5.45','402',0,0),('18',20,'1173-0963','Spänningsregulator negativ','uA79M05AUC','','ST','10.00','10.00','0.00','5.50','402',0,0),('18',40,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','D/A Omvandlare 12-bit','ST','10.00','0.00','10.00','95.00','402',0,0),('18',60,'1173-6910','Quadruple 2input NAND gate','SN74LS00N','Quadruple 2input NAND gate','ST','10.00','0.00','10.00','1.45','402',0,0),('27',10,'1173-1175','Spänningsregulator positiv','uA78H05ASC','Voltage regulator 5V','','100.00','0.00','100.00','30.00','4093',0,0),('26',20,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','','','100.00','0.00','100.00','95.00','4074',0,0),('26',10,'1173-1175','Spänningsregulator positiv','uA78H05ASC','Voltage regulator 5V','','100.00','0.00','100.00','30.00','4074',0,0),('25',10,'1173-1175','Spänningsregulator positiv','uA78H05ASC','Voltage regulator 5V','','100.00','0.00','100.00','30.00','4074',0,0),('25',20,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','','','100.00','0.00','100.00','95.00','4074',0,0),('27',20,'1173-1445','D/A Omvandlare 12-bit','DAC1220LCN','','','100.00','0.00','100.00','95.00','4093',0,0),('27',30,'1173-1447','Timerkrets','ICM7555','Timer','','100.00','0.00','100.00','5.45','4093',0,0),('28',10,'1173-7300','1024x1 bit statiskt RAM','2102 2DC','','','100.00','0.00','100.00','10.05','4094',0,0),('28',20,'1173-7701','Quad 2-input NOR Gate','MC14000BCP','','','100.00','0.00','100.00','1.45','4101',0,0),('28',30,'1173-7802','4-Bit Aritmetic Logic Unit','MC14581BCP','','','100.00','0.00','100.00','20.00','4101',0,0);
UNLOCK TABLES;
/*!40000 ALTER TABLE `INKRADREG` ENABLE KEYS */;

--
-- Table structure for table `INKREG`
--

DROP TABLE IF EXISTS `INKREG`;
CREATE TABLE `INKREG` (
  `INKORDNR` varchar(10) NOT NULL default '',
  `BESTTYP` enum('N','D','I','L','A') default NULL,
  `ORDERDATUM` date default NULL,
  `LEVNR` varchar(10) default NULL,
  `LEVNAMN` varchar(30) default NULL,
  `LEVADRESS` varchar(30) default NULL,
  `LEVPOSTNR` varchar(6) default NULL,
  `LEVPOSTADR` varchar(30) default NULL,
  `LEVLAND` varchar(30) default NULL,
  `LEVVALUTA` char(3) default NULL,
  `LEVBETVILLKOR` varchar(50) default NULL,
  `LEVVILLKOR` varchar(150) default NULL,
  `LEVSETT` varchar(150) default NULL,
  `GODSMERKE` varchar(30) default NULL,
  `KOMMENTAR` varchar(250) default NULL,
  `BESTTEXT` text,
  `VARREF` varchar(30) default NULL,
  `VARREFTFN` varchar(15) default NULL,
  `VARREFFAX` varchar(15) default NULL,
  `ERREF` varchar(20) default NULL,
  `LEVDATUM` date default NULL,
  `KUNDNR` varchar(30) default NULL,
  `FTGNAMN` varchar(30) default NULL,
  `FTGADR` varchar(30) default NULL,
  `FTGPOSTNR` varchar(6) default NULL,
  `FTGPOSTADR` varchar(30) default NULL,
  `SPRAKKOD` char(3) default 'sv',
  `BEKREFTKOD` enum('H','D','E') default 'E',
  `ORDERSTATUS` enum('N','F','B','M') default 'N',
  `UTSKRIFTSKOD` enum('J','N') default 'J',
  `ORDERSUMMA` decimal(10,2) default NULL,
  PRIMARY KEY  (`INKORDNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `INKREG`
--


/*!40000 ALTER TABLE `INKREG` DISABLE KEYS */;
LOCK TABLES `INKREG` WRITE;
INSERT INTO `INKREG` (`INKORDNR`, `BESTTYP`, `ORDERDATUM`, `LEVNR`, `LEVNAMN`, `LEVADRESS`, `LEVPOSTNR`, `LEVPOSTADR`, `LEVLAND`, `LEVVALUTA`, `LEVBETVILLKOR`, `LEVVILLKOR`, `LEVSETT`, `GODSMERKE`, `KOMMENTAR`, `BESTTEXT`, `VARREF`, `VARREFTFN`, `VARREFFAX`, `ERREF`, `LEVDATUM`, `KUNDNR`, `FTGNAMN`, `FTGADR`, `FTGPOSTNR`, `FTGPOSTADR`, `SPRAKKOD`, `BEKREFTKOD`, `ORDERSTATUS`, `UTSKRIFTSKOD`, `ORDERSUMMA`) VALUES ('6712','N','2003-12-13','9999','Testleverantör AB','Delivery Street 1C','199 99','LEVSTAD','Sverige','SEK','60 dagar netto','EXW','ASG kundnr:99901111','Godsmäre','Kommentar','Endast komplett order får levereras\nLevereras med ASG','Jan Pihlgren','09-199311','09-199312','Caroline Seljare','2003-12-15','98765','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J',NULL),('18','N','2003-12-24','9999','Testleverantör AB','Delivery Street 1C','199 99','LEVSTAD','Sverige','SEK','30 dagar netto','EXW','ASG kundnr:99901111','P-order','Kommentar','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.','Jan Pihlgren','09-199321','09-199322','Caroline Seljare','2004-01-10','98765','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J','1389.00'),('19','N','2003-12-24','9999','Testleverantör AB','Delivery Street 1C','199 99','LEVSTAD','Sverige','SEK','20 dagar netto','QWOUTA','ASG','Godsmärke','Kommentar','Beställningseftertext','Jan Pihlgren','09-199341','09-199342','Caroline Seljare','2004-01-10','98765','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J','1757.00'),('27','N','2004-02-05','126','Dataspecialisten AB','Storgatan 1','199 11','STORSTAD','Sverige','SEK',' 30 dagar netto',' EXW',' Schenker kundnr:11105232','PELLE','Direkt','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.\n  \n\n\n\n','Jan Pihlgren','09-112233','09112239','Ola Norman','2004-02-25','567891','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J','13045.00'),('26','N','2004-02-05','123','Leverantör AB','Postgatan 33','199 99','DATABY','SVERIGE','SEK',' 20 dagar netto',' EXW',' Schenker kundnr:11105232','KALLE PALL 26','Detta är en kommentar','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.\n  \n\n\n\n','Jan Pihlgren','08-59112449','09-112233','Per Josefsson','2004-02-15','12345678','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J','12500.00'),('25','N','2004-02-05','124','Distributör AB','Brevgatan 1A','199 99','DATABY','SVERIGE','EUR',' 30 dagar netto','','','','','','Jan Pihlgren','','','Lena Bertils','2004-02-05','12345678','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J','12500.00'),('28','N','2004-02-16','124','Distributör AB','Brevgatan 1A','199 99','DATABY','SVERIGE','EUR',' 30 dagar netto',' EXW',' Schenker kundnr:11105232','Godsmärke för beställning nr 2','','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.\n  \n\n\n\n','Jan Pihlgren','','','Lena Bertils','2004-02-26','12345678','PROGRAM AB','Verktygsgatan 11','199 97','PROGSTAD','sv','E','N','J','3150.00');
UNLOCK TABLES;
/*!40000 ALTER TABLE `INKREG` ENABLE KEYS */;

--
-- Table structure for table `KSTALLE`
--

DROP TABLE IF EXISTS `KSTALLE`;
CREATE TABLE `KSTALLE` (
  `ARID` char(2) NOT NULL default '',
  `KSTALLE` varchar(4) NOT NULL default '',
  `BENAMNING` varchar(100) default NULL,
  PRIMARY KEY  (`ARID`,`KSTALLE`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KSTALLE`
--


/*!40000 ALTER TABLE `KSTALLE` DISABLE KEYS */;
LOCK TABLES `KSTALLE` WRITE;
INSERT INTO `KSTALLE` (`ARID`, `KSTALLE`, `BENAMNING`) VALUES ('SS','9999','Project Mercury');
UNLOCK TABLES;
/*!40000 ALTER TABLE `KSTALLE` ENABLE KEYS */;

--
-- Table structure for table `KTOPLAN`
--

DROP TABLE IF EXISTS `KTOPLAN`;
CREATE TABLE `KTOPLAN` (
  `ARID` char(2) NOT NULL default '',
  `KTONR` varchar(4) NOT NULL default '',
  `BENAMNING` varchar(100) default NULL,
  `MANUELL` enum('J','N') default 'J',
  `MOMSKOD` varchar(4) default NULL,
  `SRUNR` int(3) default NULL,
  `KSTALLE` varchar(4) default NULL,
  `PROJEKT` varchar(4) default NULL,
  `SUBKTO` varchar(4) default NULL,
  `KTOPLAN` varchar(15) default NULL,
  `IB` decimal(10,2) default NULL,
  `UB` decimal(10,2) default NULL,
  PRIMARY KEY  (`KTONR`,`ARID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KTOPLAN`
--


/*!40000 ALTER TABLE `KTOPLAN` DISABLE KEYS */;
LOCK TABLES `KTOPLAN` WRITE;
INSERT INTO `KTOPLAN` (`ARID`, `KTONR`, `BENAMNING`, `MANUELL`, `MOMSKOD`, `SRUNR`, `KSTALLE`, `PROJEKT`, `SUBKTO`, `KTOPLAN`, `IB`, `UB`) VALUES ('AC','1010','Kassa','J','',0,'','','','BAS90','0.00','0.00'),('AC','1020','Postgiro','J','',0,'','','','BAS90','0.00','0.00'),('AC','1040','Checkkonto','J','',0,'','','','BAS90','0.00','0.00'),('AC','1050','Bank','J','',0,'','','','BAS90','0.00','0.00'),('AC','1120','Aktier och andelar','J','',0,'','','','BAS90','0.00','0.00'),('AC','1210','Kundfodringar','J','',0,'','','','BAS90','0.00','0.00'),('AC','1230','Belånade kundfodringar (factoring)','J','',0,'','','','BAS90','0.00','0.00'),('AC','1310','Förutbetalda hyreskostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','1330','Förutbetalda försäkringskostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','1350','Upplupna hyresintäkter','J','',0,'','','','BAS90','0.00','0.00'),('AC','1360','Upplupna ränteintäkter','J','',0,'','','','BAS90','0.00','0.00'),('AC','1410','Fordringar hos anställda','J','',0,'','','','BAS90','0.00','0.00'),('AC','1430','Fordringar hos leverantörer','J','',0,'','','','BAS90','0.00','0.00'),('AC','1450','Skattefordringar','J','',0,'','','','BAS90','0.00','0.00'),('AC','1470','Ingåendemervardesskatt (moms)','J','',0,'','','','BAS90','0.00','0.00'),('AC','1510','Lager','J','',0,'','','','BAS90','0.00','0.00'),('AC','1530','Produkter i arbete (PIA)','J','',0,'','','','BAS90','0.00','0.00'),('AC','1560','Förnödenheter','J','',0,'','','','BAS90','0.00','0.00'),('AC','1580','Förskott till leverantörer','J','',0,'','','','BAS90','0.00','0.00'),('AC','1620','Aktier och andelar','J','',0,'','','','BAS90','0.00','0.00'),('AC','1710','Patent','J','',0,'','','','BAS90','0.00','0.00'),('AC','1730','Goodwill','J','',0,'','','','BAS90','0.00','0.00'),('AC','1810','Arbetsmaskiner','J','',0,'','','','BAS90','0.00','0.00'),('AC','1819','Värdeminskning inventarier','J','',0,'','','','BAS90','0.00','0.00'),('AC','1820','Inventarier','J','',0,'','','','BAS90','0.00','0.00'),('AC','1840','Bilar','J','',0,'','','','BAS90','0.00','0.00'),('AC','1849','Värdeminskning bilar','J','',0,'','','','BAS90','0.00','0.00'),('AC','1910','Byggnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','1919','Värdeminskning byggnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','2010','Skulder under indrivning','J','',0,'','','','BAS90','0.00','0.00'),('AC','2110','Leverantörsskulder','J','',0,'','','','BAS90','0.00','0.00'),('AC','2210','Skatteskulder','J','',0,'','','','BAS90','0.00','0.00'),('AC','2250','Skuld preliminärskatt','J','',0,'','','','BAS90','0.00','0.00'),('AC','2310','Upplupna löner','J','',0,'','','','BAS90','0.00','0.00'),('AC','2320','Upplupna semesterlöner','J','',0,'','','','BAS90','0.00','0.00'),('AC','2330','Upplupna sociala avgifter','J','',0,'','','','BAS90','0.00','0.00'),('AC','2340','Upplupna räntekostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','2410','Utgående mervärdesskatt (moms)','J','',0,'','','','BAS90','0.00','0.00'),('AC','2480','Mervärdesskatt, redovisningskonto','J','',0,'','','','BAS90','0.00','0.00'),('AC','2510','Personalens källskatt','J','',0,'','','','BAS90','0.00','0.00'),('AC','2530','Införsel','J','',0,'','','','BAS90','0.00','0.00'),('AC','2560','Fackföreningsavgifter','J','',0,'','','','BAS90','0.00','0.00'),('AC','2590','Ã–vriga löneavdrag','J','',0,'','','','BAS90','0.00','0.00'),('AC','2610','Förskott från kunder','J','',0,'','','','BAS90','0.00','0.00'),('AC','2620','Skulder till personal','J','',0,'','','','BAS90','0.00','0.00'),('AC','2630','Avräkning, factoring','J','',0,'','','','BAS90','0.00','0.00'),('AC','2640','Låneskulder','J','',0,'','','','BAS90','0.00','0.00'),('AC','2720','Checkkredit','J','',0,'','','','BAS90','0.00','0.00'),('AC','2790','Ã–vriga långfristiga skulder','J','',0,'','','','BAS90','0.00','0.00'),('AC','2810','Lagerreserv','J','',0,'','','','BAS90','0.00','0.00'),('AC','2880','Obeskattade intäkter','J','',0,'','','','BAS90','0.00','0.00'),('AC','2910','Eget kapital','J','',0,'','','','BAS90','0.00','0.00'),('AC','3010','Försäljning','J','',0,'','','','BAS90','0.00','0.00'),('AC','3082','Bonus','J','',0,'','','','BAS90','0.00','0.00'),('AC','3512','Försäljning skrot','J','',0,'','','','BAS90','0.00','0.00'),('AC','3610','Fakturerat emballage','J','',0,'','','','BAS90','0.00','0.00'),('AC','3640','Faktureringskostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','3770','Ã…tervunna kundförluster','J','',0,'','','','BAS90','0.00','0.00'),('AC','3780','Ã–resutjämning','J','',0,'','','','BAS90','0.00','0.00'),('AC','3810','Hyresintäkter','J','',0,'','','','BAS90','0.00','0.00'),('AC','3910','Erhållna statliga bidrag','J','',0,'','','','BAS90','0.00','0.00'),('AC','4010','Inköp av varor och material','J','',0,'','','','BAS90','0.00','0.00'),('AC','4610','Legoarbeten','J','',0,'','','','BAS90','0.00','0.00'),('AC','4910','Förändring lager','J','',0,'','','','BAS90','0.00','0.00'),('AC','4930','Förändring av material i produktion (PIA)','J','',0,'','','','BAS90','0.00','0.00'),('AC','5010','Löner till personal','J','',0,'','','','BAS90','0.00','0.00'),('AC','5310','Löner till företagsledare','J','',0,'','','','BAS90','0.00','0.00'),('AC','5220','Löner till tjänstemän','J','',0,'','','','BAS90','0.00','0.00'),('AC','5340','Erssättning för måltidskostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','5450','Kostnader för bil','J','',0,'','','','BAS90','0.00','0.00'),('AC','5520','Traktamenten vid tjänsteresa','J','',0,'','','','BAS90','0.00','0.00'),('AC','5530','Bilersättningar','J','',0,'','','','BAS90','0.00','0.00'),('AC','5610','Lagstadgade arbetsgivaravgifter','J','',0,'','','','BAS90','0.00','0.00'),('AC','5620','Egenavgifter','J','',0,'','','','BAS90','0.00','0.00'),('AC','5630','Löneskatt','J','',0,'','','','BAS90','0.00','0.00'),('AC','5710','Pensionsförsäkringsavgifter','J','',0,'','','','BAS90','0.00','0.00'),('AC','5810','Utbildning','J','',0,'','','','BAS90','0.00','0.00'),('AC','6010','Lokalhyra','J','',0,'','','','BAS90','0.00','0.00'),('AC','6050','Elektricitet','J','',0,'','','','BAS90','0.00','0.00'),('AC','6070','Städning av lokaler','J','',0,'','','','BAS90','0.00','0.00'),('AC','6110','Hyra arbetsmaskiner','J','',0,'','','','BAS90','0.00','0.00'),('AC','6210','Elektricitet','J','',0,'','','','BAS90','0.00','0.00'),('AC','6230','Eldningsolja','J','',0,'','','','BAS90','0.00','0.00'),('AC','6260','Bensin mm','J','',0,'','','','BAS90','0.00','0.00'),('AC','6410','Förbrukningsinventarier','J','',0,'','','','BAS90','0.00','0.00'),('AC','6460','Förbrukningsmateriel','J','',0,'','','','BAS90','0.00','0.00'),('AC','6510','Kontorsmateriel','J','',0,'','','','BAS90','0.00','0.00'),('AC','6730','Redovisningskostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','6740','ADB-tjänster','J','',0,'','','','BAS90','0.00','0.00'),('AC','6750','Konsultarvoden för speciella utredningar','J','',0,'','','','BAS90','0.00','0.00'),('AC','6780','Advokatkostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','6810','Telefon och telegram','J','',0,'','','','BAS90','0.00','0.00'),('AC','6830','Datakommunikation','J','',0,'','','','BAS90','0.00','0.00'),('AC','6850','Porto','J','',0,'','','','BAS90','0.00','0.00'),('AC','6911','Personbilar,drivmedel','J','',0,'','','','BAS90','0.00','0.00'),('AC','6912','Personbilar,försäkring och skatt','J','',0,'','','','BAS90','0.00','0.00'),('AC','6913','Personbilar,reparationer','J','',0,'','','','BAS90','0.00','0.00'),('AC','6915','Personbilar,leasing','J','',0,'','','','BAS90','0.00','0.00'),('AC','6919','Personbilar,övrigt','J','',0,'','','','BAS90','0.00','0.00'),('AC','7010','Frakter,transporter mm','J','',0,'','','','BAS90','0.00','0.00'),('AC','7050','Resekostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','7150','Försäljningsprovisioner','J','',0,'','','','BAS90','0.00','0.00'),('AC','7210','Annonsering','J','',0,'','','','BAS90','0.00','0.00'),('AC','7310','Företagsförsäkringar','J','',0,'','','','BAS90','0.00','0.00'),('AC','7350','Kundförluster','J','',0,'','','','BAS90','0.00','0.00'),('AC','7410','Styrelsearvoden','J','',0,'','','','BAS90','0.00','0.00'),('AC','7620','Patentkostnader för egna patent','J','',0,'','','','BAS90','0.00','0.00'),('AC','7670','Tidningar,tidskrifter,facklitteratur','J','',0,'','','','BAS90','0.00','0.00'),('AC','7710','Vatten och avlopp','J','',0,'','','','BAS90','0.00','0.00'),('AC','7720','Bränsle','J','',0,'','','','BAS90','0.00','0.00'),('AC','7810','Resultat vid avyttring av maskiner och inventarier','J','',0,'','','','BAS90','0.00','0.00'),('AC','7815','Bokfört värde på maskiner och inventarier','J','',0,'','','','BAS90','0.00','0.00'),('AC','7911','Avskrivning av maskiner','J','',0,'','','','BAS90','0.00','0.00'),('AC','7912','Avskrivning av inventarier','J','',0,'','','','BAS90','0.00','0.00'),('AC','7914','Avskrivning av bilar mm','J','',0,'','','','BAS90','0.00','0.00'),('AC','8010','Utdelning på aktier och andelar','J','',0,'','','','BAS90','0.00','0.00'),('AC','8020','Ränteintäkter','J','',0,'','','','BAS90','0.00','0.00'),('AC','8050','Ränteintäkter på kundfodringar','J','',0,'','','','BAS90','0.00','0.00'),('AC','8120','Räntekostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','8150','Räntekostnader för leverantörsskulder','J','',0,'','','','BAS90','0.00','0.00'),('AC','8170','Bankkostnader','J','',0,'','','','BAS90','0.00','0.00'),('AC','8910','Ã…rets skattekostnad','J','',0,'','','','BAS90','0.00','0.00'),('AC','8980','Egenavgifter','J','',0,'','','','BAS90','0.00','0.00'),('AC','8999','Redovisat resultat','J','',0,'','','','BAS90','0.00','0.00'),('AD','1210','Maskiner','J','1',0,'','','','EUBAS97','0.00','0.00'),('AD','1219','Ack avskrivningar maskiner','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1220','Inventarier','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1229','Ack avskrivningar inventarier','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1409','Beräknad förändring lager','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1510','Kundfordringar','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1613','Ã–vriga förskott anställda','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1650','Momsfordran','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1710','Förutbetalda hyresutgifter','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1790','Ã–vriga internfordringar','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1910','Kassa','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','1920','Postgiro','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2081','Aktiekapital','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2330','Checkräkningskredit','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2350','Banklån','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2440','Leverantörsskulder','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2611','Utgående moms','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2615','Utgående moms EU-förvärv','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2641','Ingående moms','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2645','Ingående moms utland','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2710','Källskatt (A-skatt)','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2920','Upplupna semesterlöner','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','2941','Upplupna arbetsgivaravgifter','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','3041','Försäljning Jonaid','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','3051','Försäljning Zuhaib','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','3960','Kursvinst rörelsen','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','3990','Ã–vriga intäkter','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','4010','Materialkostnad','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','4056','Varuinköp EU','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','5010','Lokalhyra','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','5090','Ã–vriga lokalkostnader','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','5830','Kost och logi','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','5900','Reklam och PR','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','6071','Representation, avdragsgill','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','6110','Kontorsmateriel','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','6200','Telefon och Post','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','6310','Företagsförsäkringar','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','6970','Tidningar, facklitteratur','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','6992','Ã–vriga kostnader, ej avdragsgilla','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7010','Löner anställda','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7082','Semesterlön','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7221','Lön Yasar','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7231','Lön Anila','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7321','Skattefria traktamenten','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7331','Skattefri bilersättning','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7384','Arbetskläder','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7510','Arbetsgivaravgifter','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7570','AMF','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7620','Sjuk- och hälsovård','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7690','Ã–vriga personalkostnader','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7831','Avskrivningar maskiner','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7832','Avskrivningar inventarier','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','7960','Kursförlust rörelsen','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','8400','Räntekostnader','J','',0,'','','','EUBAS97','0.00','0.00'),('AD','8490','Ã–vriga finansiella kostnader','J','',0,'','','','EUBAS97','0.00','0.00'),('SS','9999','Testkonto3','J','1',100,'2000','3000','4000','EUBAS97','0.00','0.00');
UNLOCK TABLES;
/*!40000 ALTER TABLE `KTOPLAN` ENABLE KEYS */;

--
-- Table structure for table `KUNDKATEGORI`
--

DROP TABLE IF EXISTS `KUNDKATEGORI`;
CREATE TABLE `KUNDKATEGORI` (
  `KATEGORINR` char(3) NOT NULL default '',
  `BESKRIVNING` varchar(40) NOT NULL default '',
  PRIMARY KEY  (`KATEGORINR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KUNDKATEGORI`
--


/*!40000 ALTER TABLE `KUNDKATEGORI` DISABLE KEYS */;
LOCK TABLES `KUNDKATEGORI` WRITE;
INSERT INTO `KUNDKATEGORI` (`KATEGORINR`, `BESKRIVNING`) VALUES ('003','Webbkund'),('001','Normalkund');
UNLOCK TABLES;
/*!40000 ALTER TABLE `KUNDKATEGORI` ENABLE KEYS */;

--
-- Table structure for table `KUNDREG`
--

DROP TABLE IF EXISTS `KUNDREG`;
CREATE TABLE `KUNDREG` (
  `KUNDNR` varchar(10) NOT NULL default '',
  `KUNDORGNR` varchar(12) default NULL,
  `NAMN` varchar(60) NOT NULL default '',
  `ADRESS` varchar(30) default NULL,
  `POSTNR` varchar(10) default NULL,
  `POSTADR` varchar(30) default NULL,
  `LAND` varchar(30) default NULL,
  `TFNNR` varchar(15) default NULL,
  `EMAILADR` varchar(30) default NULL,
  `FAXNR` varchar(15) default NULL,
  `ERREFERENT` varchar(30) default NULL,
  `ERREFTFNNR` varchar(15) default NULL,
  `ERREFEMAIL` varchar(60) default NULL,
  `SELJARE` varchar(20) default NULL,
  `FRITEXT` varchar(100) default NULL,
  `VALUTA` char(3) default NULL,
  `BETALVILLKOR` char(3) default NULL,
  `LEVVILLKOR` char(3) default NULL,
  `LEVSETT` char(3) default NULL,
  `DISTRIKT` char(3) default NULL,
  `KUNDKATEGORI` char(3) default NULL,
  `STDLEVPLATS` char(3) default '001',
  `ORDERERKENNANDE` enum('J','N') default 'J',
  `PLOCKLISTA` enum('J','N') default 'J',
  `FOLJESEDEL` enum('J','N') default 'J',
  `KRAVBREV` enum('J','N') default 'J',
  `SPRAKKOD` char(3) default NULL,
  `EXPAVGIFT` enum('J','N') default 'J',
  `FRAKTAVG` enum('J','N') default 'J',
  `KREDITLIMIT` decimal(10,2) default NULL,
  `KREDITDAGAR` int(11) default NULL,
  `KREDITKOD` char(3) default NULL,
  `EXPORTKOD` char(3) default NULL,
  `SKATTEKOD` char(3) default NULL,
  `RABATTKOD` char(3) default NULL,
  `DROJMALSRTA` enum('J','N') default 'J',
  `DROJMALSFAKTURA` enum('J','N') default 'J',
  `SAMLINGSFAKT` enum('J','N') default 'J',
  `SENASTEKRAVDATUM` date default NULL,
  `SKULD` decimal(10,2) default NULL,
  `ORDERSTOCK` decimal(10,2) default NULL,
  `PRISLISTA` int(11) default NULL,
  PRIMARY KEY  (`KUNDNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KUNDREG`
--


/*!40000 ALTER TABLE `KUNDREG` DISABLE KEYS */;
LOCK TABLES `KUNDREG` WRITE;
INSERT INTO `KUNDREG` (`KUNDNR`, `KUNDORGNR`, `NAMN`, `ADRESS`, `POSTNR`, `POSTADR`, `LAND`, `TFNNR`, `EMAILADR`, `FAXNR`, `ERREFERENT`, `ERREFTFNNR`, `ERREFEMAIL`, `SELJARE`, `FRITEXT`, `VALUTA`, `BETALVILLKOR`, `LEVVILLKOR`, `LEVSETT`, `DISTRIKT`, `KUNDKATEGORI`, `STDLEVPLATS`, `ORDERERKENNANDE`, `PLOCKLISTA`, `FOLJESEDEL`, `KRAVBREV`, `SPRAKKOD`, `EXPAVGIFT`, `FRAKTAVG`, `KREDITLIMIT`, `KREDITDAGAR`, `KREDITKOD`, `EXPORTKOD`, `SKATTEKOD`, `RABATTKOD`, `DROJMALSRTA`, `DROJMALSFAKTURA`, `SAMLINGSFAKT`, `SENASTEKRAVDATUM`, `SKULD`, `ORDERSTOCK`, `PRISLISTA`) VALUES ('4376','[NULL]','Nya Test AB','Provgatan 2','199 99','LILLEBY','Sverige','09-999990','info@test.se','09-999999','Karl Andersson','09-999991','karl.a@test.se','Caroline Seljare','Fritt textfält','SEK','1','001','001','Kal','Sof','002','J','J','J','J','sv','J','J','2000.00',0,'[NU','[NU','[NU','[NU','J','J','J','0000-00-00','0.00','0.00',NULL),('4377','[NULL]','Nya Kund AB','Provgatan 23','199 97','LILLEBY','Sverige','09-999190','info@kund.se','09-999199','Per Karlsson','09-999191','per.k@kund.se','Josef Seljare','Vår nya kund','SEK','1','001','001','Ã–re','Sof','001','J','J','J','J','sv','J','J','2000.00',0,'','011','001','001','J','J','J','0000-00-00','0.00','0.00',NULL),('4378','[NULL]','Nya Storkund AB','Fina gatan 2','100 01','LYXBY','Sverige','09-109990','info@storkund.se','09-109999','Carl von Petersen','09-109991','c.p@storkund.se','Carolina Seljare','Detta är en stor kund','SEK','2','001','003','LYX','009','010','J','J','J','N','sv','J','J','100000.00',45,'001','001','001','001','J','J','J','0000-00-00','0.00','0.00',NULL),('4379','[NULL]','Nya Småkund AB','Myrstigen 32','199 02','SMÃ…STAD','Sverige','09-129990','info@smakund.se','09-129999','Lillemor AndrÃ©n','09-129991','lillemor.a@smakund.se','Caroline Seljare','Den lilla kunden','SEK','1','001','001','Ã–re','Sft','002','J','J','J','J','sv','J','J','5000.00',30,'001','001','001','001','J','J','J','0000-00-00','0.00','0.00',NULL),('4375',NULL,'Lilla Kunden Eftr AB','Bakgatan 1C','199 09','SMÃ…STAD','Sverige','09-390000','info@lillakundeneftr.se','09-390009','Lillemor AndrÃ©n','09-390001','lillemor@lillakundeneftr.se','Lilleman Karlsson','Byte av företagsnamn Testföretaget','SEK','1','001','001','003','003','002','J','J','J','J','sv','J','J','13500.00',0,'001','001','001','001','J','J','J',NULL,NULL,NULL,NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `KUNDREG` ENABLE KEYS */;

--
-- Table structure for table `KURESK`
--

DROP TABLE IF EXISTS `KURESK`;
CREATE TABLE `KURESK` (
  `ORDERNR` varchar(10) NOT NULL default '',
  `FAKTURANR` varchar(20) NOT NULL default '',
  `KUNDNR` varchar(10) NOT NULL default '',
  `FAKTURADATUM` date default NULL,
  `EXPIREDATUM` date default NULL,
  `NETTOBELOPP` decimal(10,2) default NULL,
  `MOMSBELOPP` decimal(10,2) default NULL,
  `FAKTURABELOPP` decimal(10,2) default NULL,
  `BETALD` enum('J','N') NOT NULL default 'N',
  `BETALDATUM` date default NULL,
  `USERID` varchar(20) default NULL,
  `VALUTA` char(3) default 'SEK',
  `VALUTAKURS` decimal(10,2) NOT NULL default '1.00',
  `VALUTABELOPP` decimal(10,2) default '0.00',
  `BAR` char(2) default NULL,
  `VERNR` int(11) default NULL,
  `MOMSKTONR` varchar(4) default NULL,
  `KTONR` varchar(4) default NULL,
  `DEBETBELOPP` decimal(10,2) default NULL,
  PRIMARY KEY  (`ORDERNR`,`FAKTURANR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `KURESK`
--


/*!40000 ALTER TABLE `KURESK` DISABLE KEYS */;
LOCK TABLES `KURESK` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `KURESK` ENABLE KEYS */;

--
-- Table structure for table `LAGERSTELLEREG`
--

DROP TABLE IF EXISTS `LAGERSTELLEREG`;
CREATE TABLE `LAGERSTELLEREG` (
  `ARLAGST` char(1) NOT NULL default '',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `ARLAGHYLLA` varchar(10) default NULL,
  `ARLAGSALDO` decimal(10,2) default NULL,
  `ARINVGRP` char(3) default NULL,
  `ARABC` char(2) default NULL,
  `ARVALUTA` char(3) default NULL,
  `ARIPRIS` decimal(10,2) default '0.00',
  `ARIKVANT0` decimal(10,2) default '0.00',
  `ARIKVANT1` decimal(10,2) default '0.00',
  `ARIKVANT2` decimal(10,2) default '0.00',
  `ARKALKPRIS` decimal(10,2) default '0.00',
  `ARPLANKPRIS` decimal(10,2) default '0.00',
  `ARFRYSTKPRIS` decimal(10,2) default '0.00',
  `ARBESTKVANT` decimal(10,2) default '0.00',
  `ARBESTPUNKT` decimal(10,2) default '0.00',
  `AROMKOST` decimal(10,2) default '0.00',
  `RESERVERAT` decimal(10,2) default NULL,
  PRIMARY KEY  (`ARTIKELNR`,`ARLAGST`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LAGERSTELLEREG`
--


/*!40000 ALTER TABLE `LAGERSTELLEREG` DISABLE KEYS */;
LOCK TABLES `LAGERSTELLEREG` WRITE;
INSERT INTO `LAGERSTELLEREG` (`ARLAGST`, `ARTIKELNR`, `ARLAGHYLLA`, `ARLAGSALDO`, `ARINVGRP`, `ARABC`, `ARVALUTA`, `ARIPRIS`, `ARIKVANT0`, `ARIKVANT1`, `ARIKVANT2`, `ARKALKPRIS`, `ARPLANKPRIS`, `ARFRYSTKPRIS`, `ARBESTKVANT`, `ARBESTPUNKT`, `AROMKOST`, `RESERVERAT`) VALUES ('1','1000-1001','ABC002','103.00','001','A','SEK','125.50','60.00','75.00','50.00','160.00','202.50','160.00','62.00','125.00','34.50',NULL),('1','1000-1002','AAA001','126.00','1','A','SEK','30.00','0.00','0.00','0.00','35.00','0.00','0.00','0.00','100.00','0.00',NULL),('1','1000-1003','AAA001','75.00','1','A','SEK','1.50','0.00','0.00','0.00','1.60','0.00','0.00','0.00','100.00','0.00',NULL),('1','1000-1004','AAA001','10.00','1','A','SEK','5.50','0.00','0.00','0.00','6.65','0.00','0.00','0.00','50.00','0.00',NULL),('1','1000-1005','AAA002','27.00','1','A','SEK','95.00','0.00','0.00','0.00','100.00','0.00','0.00','0.00','25.00','0.00',NULL),('1','1000-1006','AAA002','536.00','2','A','SEK','5.45','0.00','0.00','0.00','6.85','0.00','0.00','0.00','150.00','0.00',NULL),('1','1000-1007','AAA003','243.00','2','A','SEK','1.45','0.00','0.00','0.00','1.65','0.00','0.00','0.00','200.00','0.00',NULL),('1','1000-1008','AAA003','263.00','2','A','SEK','4.75','0.00','0.00','0.00','5.15','0.00','0.00','0.00','100.00','0.00',NULL),('1','1000-1009','AAB001','458.00','2','A','SEK','10.05','0.00','0.00','0.00','11.65','0.00','0.00','0.00','350.00','0.00',NULL),('1','1000-1010','AAB001','27.00','1','A','SEK','45.45','0.00','0.00','0.00','50.35','0.00','0.00','0.00','30.00','0.00',NULL),('1','1000-1011','AAC001','11.00','1','A','SEK','98.00','0.00','0.00','0.00','103.00','0.00','0.00','0.00','65.00','5.00',NULL),('1','1000-1012','AAA004','34.00','1','A','SEK','1.45','0.00','0.00','0.00','2.05','0.00','0.00','0.00','50.00','0.00',NULL),('1','1000-1013','AAA005','32.00','1','A','SEK','20.00','0.00','0.00','0.00','23.00','0.00','0.00','0.00','30.00','0.00',NULL),('1','1000-1014','AAB001','6.00','2','A','SEK','55.00','0.00','0.00','0.00','70.00','0.00','0.00','0.00','10.00','0.00',NULL),('1','Test','TEST001','12.00','100','C','SEK','50.00','25.00','0.00','0.00','0.00','0.00','0.00','0.00','0.00','0.00',NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `LAGERSTELLEREG` ENABLE KEYS */;

--
-- Table structure for table `LEVPRISER`
--

DROP TABLE IF EXISTS `LEVPRISER`;
CREATE TABLE `LEVPRISER` (
  `KUNDNR` varchar(10) NOT NULL default '',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `BENEMNING` varchar(60) default '0',
  `PRIS` decimal(10,2) default '0.00',
  `MATERIALKLASS` varchar(5) default '0',
  `ENHET` varchar(5) default '0',
  `XREF` varchar(30) default '0',
  PRIMARY KEY  (`KUNDNR`,`ARTIKELNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVPRISER`
--


/*!40000 ALTER TABLE `LEVPRISER` DISABLE KEYS */;
LOCK TABLES `LEVPRISER` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVPRISER` ENABLE KEYS */;

--
-- Table structure for table `LEVREG`
--

DROP TABLE IF EXISTS `LEVREG`;
CREATE TABLE `LEVREG` (
  `LEVNR` varchar(10) NOT NULL default '',
  `LEVORGNR` varchar(12) default NULL,
  `LEVNAMN` varchar(30) NOT NULL default '',
  `LEVADRESS` varchar(30) default NULL,
  `LEVPOSTNR` varchar(6) default NULL,
  `LEVPOSTADR` varchar(30) default NULL,
  `LEVLAND` varchar(30) default NULL,
  `LEVTFNNR` varchar(15) default NULL,
  `LEVFAXNR` varchar(15) default NULL,
  `LEVTELEX` varchar(10) default NULL,
  `LEVEMAIL` varchar(30) default NULL,
  `LEVPOSTGIRONR` varchar(10) default NULL,
  `LEVBANKGIRONR` varchar(10) default NULL,
  `LEVREFERENT` varchar(20) default NULL,
  `LEVREFTFN` varchar(15) default NULL,
  `LEVMOMSKOD` char(1) default '1',
  `LEVSKULD` decimal(10,2) default NULL,
  `LEVKONTO` varchar(4) default NULL,
  `LEVKUNDNR` varchar(30) default NULL,
  `LEVVALUTA` char(3) default NULL,
  `BETALVILKOR` char(3) default NULL,
  PRIMARY KEY  (`LEVNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVREG`
--


/*!40000 ALTER TABLE `LEVREG` DISABLE KEYS */;
LOCK TABLES `LEVREG` WRITE;
INSERT INTO `LEVREG` (`LEVNR`, `LEVORGNR`, `LEVNAMN`, `LEVADRESS`, `LEVPOSTNR`, `LEVPOSTADR`, `LEVLAND`, `LEVTFNNR`, `LEVFAXNR`, `LEVTELEX`, `LEVEMAIL`, `LEVPOSTGIRONR`, `LEVBANKGIRONR`, `LEVREFERENT`, `LEVREFTFN`, `LEVMOMSKOD`, `LEVSKULD`, `LEVKONTO`, `LEVKUNDNR`, `LEVVALUTA`, `BETALVILKOR`) VALUES ('9999','666667-9997','Testleverantör AB','Delivery Street 1C','199 99','LEVSTAD','Sverige','09-919191','09-919192','88888','kundtj@testlev.se','5559998-8','5998-9998','Lars Andersson','09-919193','1','0.00','2121','98765','SEK','1'),('1000','','ICA Stjärnköp','','','MÄRSTA','','020-833333','','',' kundkontakt@ica.se','','','','','1','0.00','','','SEK','1'),('2001','','Carlsberg','','','','Sverige','020-788020','','','','','','','','1','0.00','','','SEK','1'),('123','559999-9999','Leverantör AB','Postgatan 33','199 99','DATABY','SVERIGE','09-999999','09-999998','99999','kundtj@leverantor.se','4559999-9','5999-9999','Per Josefsson','09-999997','1','0.00','2440','12345678','SEK','2'),('124','559988-9999','Distributör AB','Brevgatan 1A','199 99','DATABY','SVERIGE','09-999199','09-999198','19999','kundtj@distributor.se','4559988-9','5988-9999','Lena Bertils','09-999997','1','0.00','2440','12345678','EUR','1'),('125','559955-5599','Försäljning AB','Säljgatan 3','199 11','BY','Sverige','09-119910','09-119919','11119','info@forsaljning.se','454511-1','4545-1111','Karl Säljare','09-119915','1','0.00','2110','98765','SEK','1'),('126','550101-5555','Dataspecialisten AB','Storgatan 1','199 11','STORSTAD','Sverige','09-112250','09-112259','22229','info@dataspecialisten.se','4512323-3','4512-5566','Ola Norman','09-112255','1','0.00','2110','567891','SEK','1'),('100','559901-9991','Bokförlag AB','Bokgatan 1','198 01','BOKBY','Sverige','09-909090','09-909010','99991','kundtj@bokforlag.se','5599999-9','5900-2222','Linda Bokman','09-909011','1','0.00','2110','33331','SEK','1'),('200','559902-9992','Stora Bokförlaget AB','Förlagsgatan 11','198 02','FÃ–RLAGSSTAD','Sverige','09-919190','09-919111','22222','kundtj@storaforlag.se','559998-2','5900-3333','Philip King','09-919196','1','0.00','2110','44440','SEK','1'),('300','559899-5559','Lilla Förlaget HB','Bokgränd 23','198 03','BOKBY','Sverige','09-808080','09-808081','89992','Kundtj@lillaforlaget.se','558800-8','5900-4444','Kerstin Bokare','09-808089','1','0.00','2110','55550','SEK','1');
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVREG` ENABLE KEYS */;

--
-- Table structure for table `LEVRESK`
--

DROP TABLE IF EXISTS `LEVRESK`;
CREATE TABLE `LEVRESK` (
  `LEVNR` varchar(10) NOT NULL default '',
  `FAKTURANR` varchar(20) NOT NULL default '',
  `REGDATUM` date default NULL,
  `FAKTDATUM` date default NULL,
  `EXPIREDATUM` date default NULL,
  `FAKTTEXT` varchar(100) default NULL,
  `BAR` char(2) default NULL,
  `MOMSPROCENT` decimal(3,2) default NULL,
  `VALUTA` char(3) default NULL,
  `VALUTAKURS` decimal(3,2) default NULL,
  `VALUTABELOPP` decimal(10,2) default NULL,
  `LEVKTONR` varchar(4) default NULL,
  `FAKTBELOPP` decimal(10,2) default NULL,
  `MOMSKTONR` varchar(4) default NULL,
  `MOMSBELOPP` decimal(10,2) default NULL,
  `DEBETKONTONR` varchar(4) default NULL,
  `DEBETBELOPP` decimal(10,2) default NULL,
  `USERID` varchar(20) default NULL,
  `VERNR` int(11) default NULL,
  `BETALD` enum('J','N') default 'N',
  `BETALDDATUM` date default NULL,
  `OCRNR` varchar(20) default NULL,
  PRIMARY KEY  (`LEVNR`,`FAKTURANR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVRESK`
--


/*!40000 ALTER TABLE `LEVRESK` DISABLE KEYS */;
LOCK TABLES `LEVRESK` WRITE;
INSERT INTO `LEVRESK` (`LEVNR`, `FAKTURANR`, `REGDATUM`, `FAKTDATUM`, `EXPIREDATUM`, `FAKTTEXT`, `BAR`, `MOMSPROCENT`, `VALUTA`, `VALUTAKURS`, `VALUTABELOPP`, `LEVKTONR`, `FAKTBELOPP`, `MOMSKTONR`, `MOMSBELOPP`, `DEBETKONTONR`, `DEBETBELOPP`, `USERID`, `VERNR`, `BETALD`, `BETALDDATUM`, `OCRNR`) VALUES ('123','1238866','2003-11-07','2003-11-04','2003-12-07','Inköp av bokhylla','AC','25.00','SEK','1.00','1100.00','2110','1100.00','1470','275.00','1810','825.00','ADMIN',22,'N',NULL,'76598234');
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVRESK` ENABLE KEYS */;

--
-- Table structure for table `LEVSETT`
--

DROP TABLE IF EXISTS `LEVSETT`;
CREATE TABLE `LEVSETT` (
  `LEVSETTNR` char(3) NOT NULL default '',
  `LEVSETTTEXT` varchar(150) NOT NULL default '',
  PRIMARY KEY  (`LEVSETTNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVSETT`
--


/*!40000 ALTER TABLE `LEVSETT` DISABLE KEYS */;
LOCK TABLES `LEVSETT` WRITE;
INSERT INTO `LEVSETT` (`LEVSETTNR`, `LEVSETTTEXT`) VALUES ('001','Schenker kundnr:11105232'),('002','ASG. Kundnr 111111'),('003','Post');
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVSETT` ENABLE KEYS */;

--
-- Table structure for table `LEVVILLKOR`
--

DROP TABLE IF EXISTS `LEVVILLKOR`;
CREATE TABLE `LEVVILLKOR` (
  `VILLKORSNR` char(3) NOT NULL default '',
  `VILLKORSTEXT` varchar(150) NOT NULL default '',
  PRIMARY KEY  (`VILLKORSNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `LEVVILLKOR`
--


/*!40000 ALTER TABLE `LEVVILLKOR` DISABLE KEYS */;
LOCK TABLES `LEVVILLKOR` WRITE;
INSERT INTO `LEVVILLKOR` (`VILLKORSNR`, `VILLKORSTEXT`) VALUES ('001','EXW'),('002','EYW'),('003','');
UNLOCK TABLES;
/*!40000 ALTER TABLE `LEVVILLKOR` ENABLE KEYS */;

--
-- Table structure for table `OFFERTRADREG`
--

DROP TABLE IF EXISTS `OFFERTRADREG`;
CREATE TABLE `OFFERTRADREG` (
  `OFFERTNR` varchar(10) NOT NULL default '',
  `ORDERNR` varchar(10) default '',
  `ORDERRAD` int(4) NOT NULL default '0',
  `KUNDNR` varchar(10) NOT NULL default '',
  `RADORDERTYP` enum('N','D') default 'N',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `BENEMNING` varchar(60) default NULL,
  `LEVERANSVECKA` varchar(5) default NULL,
  `BESTELLT` decimal(10,2) NOT NULL default '0.00',
  `APRIS` decimal(10,2) NOT NULL default '0.00',
  `SUMMA` decimal(10,2) NOT NULL default '0.00',
  `MOMSKR` decimal(10,2) NOT NULL default '0.00',
  `LEVERERAT` decimal(10,2) default NULL,
  `RESTNOTERAT` decimal(10,2) default NULL,
  `RADRABATT` decimal(2,1) default NULL,
  `KALKYLPRIS` decimal(10,2) default NULL,
  `LEVDATUM` date default NULL,
  `ENHET` varchar(4) default 'ST',
  `FAKTURERAT` decimal(10,2) default NULL,
  PRIMARY KEY  (`ORDERRAD`,`OFFERTNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `OFFERTRADREG`
--


/*!40000 ALTER TABLE `OFFERTRADREG` DISABLE KEYS */;
LOCK TABLES `OFFERTRADREG` WRITE;
INSERT INTO `OFFERTRADREG` (`OFFERTNR`, `ORDERNR`, `ORDERRAD`, `KUNDNR`, `RADORDERTYP`, `ARTIKELNR`, `BENEMNING`, `LEVERANSVECKA`, `BESTELLT`, `APRIS`, `SUMMA`, `MOMSKR`, `LEVERERAT`, `RESTNOTERAT`, `RADRABATT`, `KALKYLPRIS`, `LEVDATUM`, `ENHET`, `FAKTURERAT`) VALUES ('9','0',10,'4375','N','1000-1001','Att använda GNU/LINUX','6173','0.00','117.00','0.00','25.00',NULL,NULL,NULL,NULL,NULL,'ST',NULL),('9','0',20,'4375','N','1000-1010','Nyckeln till C','6173','1.00','117.00','124.02','7.02',NULL,NULL,NULL,NULL,NULL,'ST',NULL),('1','1',10,'4379','','1000-1001','Att använda GNU/LINUX','6473','10.00','127.00','1587.50','317.50','0.00','0.00','0.0','0.00','0000-00-00','ST','0.00'),('1','1',20,'4379','','1000-1002','Linux MAGNUM','6448','4.00','117.00','585.00','117.00','0.00','0.00','0.0','0.00','0000-00-00','ST','0.00'),('107','0',10,'4377','N','1000-1001','Att använda GNU/LINUX','6484','20.00','117.00','2925.00','585.00',NULL,NULL,NULL,NULL,NULL,'ST',NULL),('106','0',10,'4378','N','1000-1001','Att använda GNU/LINUX','6471','1.00','176.00','220.00','44.00',NULL,'1.00',NULL,NULL,NULL,'ST','0.00'),('106','0',20,'4378','N','1000-1004','C++ programmering','6471','1.00','117.00','124.02','7.02','99.00','23.00','11.0','2000.00','2006-11-28','ST','0.00'),('107','0',30,'4377','N','1000-1004','C++ programmering','6484','20.00','234.00','4960.80','280.80',NULL,NULL,NULL,NULL,NULL,'ST',NULL),('107','0',20,'4377','N','1000-1003','Linux På egen hand','6484','20.00','98.00','2450.00','490.00',NULL,NULL,NULL,NULL,NULL,'ST',NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `OFFERTRADREG` ENABLE KEYS */;

--
-- Table structure for table `OFFERTREG`
--

DROP TABLE IF EXISTS `OFFERTREG`;
CREATE TABLE `OFFERTREG` (
  `OFFERTNR` varchar(10) NOT NULL default '',
  `ORDERNR` varchar(10) default '',
  `KUNDNR` varchar(10) NOT NULL default '',
  `ORDERTYP` enum('N','D','E','F') default 'N',
  `ORDERSTATUS` enum('A','N','F','B') default 'A',
  `ORDERDATUM` date default NULL,
  `LEVDATUM` date default NULL,
  `KUNDNAMN` varchar(60) default NULL,
  `KUNDADRESS` varchar(30) default NULL,
  `KUNDPOSTNR` varchar(6) default NULL,
  `KUNDPOSTADR` varchar(30) default NULL,
  `KUNDLAND` varchar(30) default NULL,
  `ERREF` varchar(20) default NULL,
  `LEVADRESS` varchar(30) default NULL,
  `LEVPOSTNR` varchar(6) default NULL,
  `LEVPOSTADR` varchar(30) default NULL,
  `LEVLAND` varchar(30) default NULL,
  `VARREF` varchar(20) default NULL,
  `SELJARE` varchar(20) default NULL,
  `GODSMERKE` varchar(100) default NULL,
  `BETVILLKTYP` enum('F','P','K') NOT NULL default 'F',
  `BETVILLKOR` char(3) default '001',
  `LEVVILLKOR` char(3) default '001',
  `LEVSETT` char(3) default '001',
  `PLOCKLISTA` enum('J','N') default 'J',
  `FOLJESEDEL` enum('J','N') default 'J',
  `FRAKTAVG` enum('J','N') default 'J',
  `SKATTEKOD` char(3) NOT NULL default '001',
  `MOMS` decimal(3,2) default NULL,
  `VALUTA` char(3) default 'SEK',
  `EXPORTKOD` char(3) default '001',
  `SPRAKKOD` char(3) default 'sv',
  `ORDERSUMMA` decimal(10,2) default NULL,
  `FRAKTSUMMA` decimal(10,2) default NULL,
  `FRAKTMOMSKR` decimal(10,2) default NULL,
  `ORDERMOMS` decimal(10,2) default NULL,
  `ORDERTOTAL` decimal(10,2) default NULL,
  PRIMARY KEY  (`OFFERTNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `OFFERTREG`
--


/*!40000 ALTER TABLE `OFFERTREG` DISABLE KEYS */;
LOCK TABLES `OFFERTREG` WRITE;
INSERT INTO `OFFERTREG` (`OFFERTNR`, `ORDERNR`, `KUNDNR`, `ORDERTYP`, `ORDERSTATUS`, `ORDERDATUM`, `LEVDATUM`, `KUNDNAMN`, `KUNDADRESS`, `KUNDPOSTNR`, `KUNDPOSTADR`, `KUNDLAND`, `ERREF`, `LEVADRESS`, `LEVPOSTNR`, `LEVPOSTADR`, `LEVLAND`, `VARREF`, `SELJARE`, `GODSMERKE`, `BETVILLKTYP`, `BETVILLKOR`, `LEVVILLKOR`, `LEVSETT`, `PLOCKLISTA`, `FOLJESEDEL`, `FRAKTAVG`, `SKATTEKOD`, `MOMS`, `VALUTA`, `EXPORTKOD`, `SPRAKKOD`, `ORDERSUMMA`, `FRAKTSUMMA`, `FRAKTMOMSKR`, `ORDERMOMS`, `ORDERTOTAL`) VALUES ('9','0','4375','N','A','2006-04-26','2006-04-26','Lilla Kunden Eftr AB','Bakgatan 1C','199 09','SMÃ…STAD','Sverige','Lillemor AndrÃ©n','Bakgatan 1D','199 09','SMÃ…STAD','-',NULL,'Jan Pihlgren','','F','1','001','002','J','J','J','001','25.00','SEK','001','sv','124.02','0.00','0.00','0.00','0.00'),('1','0','4379','N','A','2006-11-02','2006-11-06','Big Brother','Storgatan 111','198 32','Storstad','Sverige','Bror','Storgatan 109','198 32','Storstad','',NULL,'Jan Pihlgren','Gosmärkesplats','F','1','','','J','J','J','001','25.00','','001','sv','1738.00','0.00','0.00','434.50','2172.50'),('107','0','4377','N','A','2006-11-30','0000-00-00','Nya Kund AB','Provgatan 23','199 97','LILLEBY','Sverige','Per Karlsson','Provgatan 23','199 97','LILLEBY','Sverige',NULL,'Jan Pihlgren','','F','1','001','001','J','J','J','001','25.00','SEK','001','sv','10335.80','0.00','0.00','0.00','0.00'),('106','0','4378','N','A','2006-11-20','2006-11-20','Nya Storkund AB','Fina gatan 2','100 01','LYXBY','Sverige','Carl von Petersen','Fina gatan 2','100 01','LYXBY','Sverige',NULL,'Jan Pihlgren','','F','2','001','010','J','J','J','001','25.00','SEK','001','sv','344.02','0.00','0.00','86.00','430.00');
UNLOCK TABLES;
/*!40000 ALTER TABLE `OFFERTREG` ENABLE KEYS */;

--
-- Table structure for table `ORDERRADREG`
--

DROP TABLE IF EXISTS `ORDERRADREG`;
CREATE TABLE `ORDERRADREG` (
  `ORDERNR` varchar(10) NOT NULL default '',
  `ORDERRAD` int(4) NOT NULL default '0',
  `KUNDNR` varchar(10) NOT NULL default '',
  `RADORDERTYP` enum('N','D') default 'N',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `BENEMNING` varchar(60) default NULL,
  `LEVERANSVECKA` varchar(5) default NULL,
  `BESTELLT` decimal(10,2) NOT NULL default '0.00',
  `APRIS` decimal(10,2) NOT NULL default '0.00',
  `SUMMA` decimal(10,2) NOT NULL default '0.00',
  `MOMSKR` decimal(10,2) NOT NULL default '0.00',
  `LEVERERAT` decimal(10,2) default NULL,
  `RESTNOTERAT` decimal(10,2) default NULL,
  `RADRABATT` decimal(2,1) default NULL,
  `KALKYLPRIS` decimal(10,2) default NULL,
  `LEVDATUM` date default NULL,
  `ENHET` varchar(4) default 'ST',
  `FAKTURERAT` decimal(10,2) default NULL,
  PRIMARY KEY  (`ORDERNR`,`ORDERRAD`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ORDERRADREG`
--


/*!40000 ALTER TABLE `ORDERRADREG` DISABLE KEYS */;
LOCK TABLES `ORDERRADREG` WRITE;
INSERT INTO `ORDERRADREG` (`ORDERNR`, `ORDERRAD`, `KUNDNR`, `RADORDERTYP`, `ARTIKELNR`, `BENEMNING`, `LEVERANSVECKA`, `BESTELLT`, `APRIS`, `SUMMA`, `MOMSKR`, `LEVERERAT`, `RESTNOTERAT`, `RADRABATT`, `KALKYLPRIS`, `LEVDATUM`, `ENHET`, `FAKTURERAT`) VALUES ('7',10,'4379','N','1000-1001','Att använda GNU/LINUX','6163','1.00','165.00','206.25','41.25',NULL,NULL,NULL,NULL,NULL,'ST',NULL),('7',20,'4379','N','1000-1002','Linux MAGNUM','6163','1.00','105.00','131.25','26.25',NULL,NULL,NULL,NULL,NULL,'ST',NULL),('8',20,'4375','N','1000-1010','Nyckeln till C','6164','1.00','125.00','132.50','7.50',NULL,NULL,NULL,NULL,NULL,'ST',NULL),('8',10,'4375','N','1000-1009','Arbeta med C','6164','1.00','117.00','124.02','7.02',NULL,NULL,NULL,NULL,NULL,'ST',NULL),('201',10,'4378','N','1000-1001','Att använda GNU/LINUX','6471','1.00','176.00','220.00','44.00',NULL,NULL,NULL,NULL,NULL,'ST',NULL),('201',20,'4378','N','1000-1004','C++ programmering','6471','1.00','117.00','124.02','7.02',NULL,NULL,NULL,NULL,NULL,'ST',NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `ORDERRADREG` ENABLE KEYS */;

--
-- Table structure for table `ORDERREG`
--

DROP TABLE IF EXISTS `ORDERREG`;
CREATE TABLE `ORDERREG` (
  `ORDERNR` varchar(10) NOT NULL default '',
  `KUNDNR` varchar(10) NOT NULL default '',
  `ORDERTYP` enum('N','D','E','F') default 'N',
  `ORDERSTATUS` enum('A','N','F','B') default 'A',
  `ORDERDATUM` date default NULL,
  `LEVDATUM` date default NULL,
  `KUNDNAMN` varchar(60) default NULL,
  `KUNDADRESS` varchar(30) default NULL,
  `KUNDPOSTNR` varchar(6) default NULL,
  `KUNDPOSTADR` varchar(30) default NULL,
  `KUNDLAND` varchar(30) default NULL,
  `ERREF` varchar(20) default NULL,
  `LEVADRESS` varchar(30) default NULL,
  `LEVPOSTNR` varchar(6) default NULL,
  `LEVPOSTADR` varchar(30) default NULL,
  `LEVLAND` varchar(30) default NULL,
  `VARREF` varchar(20) default NULL,
  `SELJARE` varchar(20) default NULL,
  `GODSMERKE` varchar(100) default NULL,
  `BETVILLKTYP` enum('F','P','K') NOT NULL default 'F',
  `BETVILLKOR` char(3) default '001',
  `LEVVILLKOR` char(3) default '001',
  `LEVSETT` char(3) default '001',
  `PLOCKLISTA` enum('J','N') default 'J',
  `FOLJESEDEL` enum('J','N') default 'J',
  `FRAKTAVG` enum('J','N') default 'J',
  `SKATTEKOD` char(3) NOT NULL default '001',
  `MOMS` decimal(3,2) default NULL,
  `VALUTA` char(3) default 'SEK',
  `EXPORTKOD` char(3) default '001',
  `SPRAKKOD` char(3) default 'sv',
  `ORDERSUMMA` decimal(10,2) default NULL,
  `FRAKTSUMMA` decimal(10,2) default NULL,
  `FRAKTMOMSKR` decimal(10,2) default NULL,
  `ORDERMOMS` decimal(10,2) default NULL,
  `ORDERTOTAL` decimal(10,2) default NULL,
  PRIMARY KEY  (`ORDERNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ORDERREG`
--


/*!40000 ALTER TABLE `ORDERREG` DISABLE KEYS */;
LOCK TABLES `ORDERREG` WRITE;
INSERT INTO `ORDERREG` (`ORDERNR`, `KUNDNR`, `ORDERTYP`, `ORDERSTATUS`, `ORDERDATUM`, `LEVDATUM`, `KUNDNAMN`, `KUNDADRESS`, `KUNDPOSTNR`, `KUNDPOSTADR`, `KUNDLAND`, `ERREF`, `LEVADRESS`, `LEVPOSTNR`, `LEVPOSTADR`, `LEVLAND`, `VARREF`, `SELJARE`, `GODSMERKE`, `BETVILLKTYP`, `BETVILLKOR`, `LEVVILLKOR`, `LEVSETT`, `PLOCKLISTA`, `FOLJESEDEL`, `FRAKTAVG`, `SKATTEKOD`, `MOMS`, `VALUTA`, `EXPORTKOD`, `SPRAKKOD`, `ORDERSUMMA`, `FRAKTSUMMA`, `FRAKTMOMSKR`, `ORDERMOMS`, `ORDERTOTAL`) VALUES ('201','4378','N','A','2006-11-20','2006-11-20','Nya Storkund AB','Fina gatan 2','100 01','LYXBY','Sverige','Carl von Petersen','Fina gatan 2','100 01','LYXBY','Sverige',NULL,'Jan Pihlgren','','F','2','001','010','J','J','J','001','25.00','SEK','001','sv','344.02','0.00','0.00','86.00','430.00'),('8','4375','N','A','2006-04-20','2006-04-20','Lilla Kunden Eftr AB','Bakgatan 1C','199 09','SMÃ…STAD','Sverige','Lillemor AndrÃ©n','Bakgatan 1D','199 09','SMÃ…STAD','-',NULL,'Jan Pihlgren','','F','1','001','002','J','J','J','001','25.00','SEK','001','sv','256.52','90.00','22.50','37.02','406.04'),('7','4379','N','A','2006-04-19','2006-04-19','Nya Småkund AB','Myrstigen 32','199 02','SMÃ…STAD','Sverige','Lillemor AndrÃ©n','Myrstigen 32','199 02','SMÃ…STAD','Sverige',NULL,'Jan Pihlgren','','F','1','001','002','J','J','J','001','25.00','SEK','001','sv','337.50','0.00','0.00','0.00','0.00');
UNLOCK TABLES;
/*!40000 ALTER TABLE `ORDERREG` ENABLE KEYS */;

--
-- Table structure for table `PLOCKLISTEREG`
--

DROP TABLE IF EXISTS `PLOCKLISTEREG`;
CREATE TABLE `PLOCKLISTEREG` (
  `PLOCKNR` int(11) NOT NULL auto_increment,
  `ORDERNR` varchar(10) NOT NULL default '',
  `ORDERRAD` int(4) NOT NULL default '0',
  `KUNDNR` varchar(10) NOT NULL default '',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `BENEMNING` varchar(60) default NULL,
  `LEVERANSVECKA` varchar(5) default NULL,
  `BESTELLT` decimal(10,2) NOT NULL default '0.00',
  `ATTLEVERERA` decimal(10,2) NOT NULL default '0.00',
  `LEVERERAT` decimal(10,2) NOT NULL default '0.00',
  `PLOCKAT` decimal(10,2) NOT NULL default '0.00',
  `RESTNOTERAT` decimal(10,2) NOT NULL default '0.00',
  `LEVDATUM` date default NULL,
  `ENHET` varchar(4) default NULL,
  `PLOCKSTATUS` enum('P','B') default 'P',
  `PLOCKDATUM` date NOT NULL default '0000-00-00',
  PRIMARY KEY  (`PLOCKNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `PLOCKLISTEREG`
--


/*!40000 ALTER TABLE `PLOCKLISTEREG` DISABLE KEYS */;
LOCK TABLES `PLOCKLISTEREG` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `PLOCKLISTEREG` ENABLE KEYS */;

--
-- Table structure for table `PRISLISTA`
--

DROP TABLE IF EXISTS `PRISLISTA`;
CREATE TABLE `PRISLISTA` (
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `PRIS1` decimal(10,2) default '0.00',
  `PRIS2` decimal(10,2) default '0.00',
  `PRIS3` decimal(10,2) default '0.00',
  `PRIS4` decimal(10,2) default '0.00',
  `PRIS5` decimal(10,2) default '0.00',
  PRIMARY KEY  (`ARTIKELNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `PRISLISTA`
--


/*!40000 ALTER TABLE `PRISLISTA` DISABLE KEYS */;
LOCK TABLES `PRISLISTA` WRITE;
INSERT INTO `PRISLISTA` (`ARTIKELNR`, `PRIS1`, `PRIS2`, `PRIS3`, `PRIS4`, `PRIS5`) VALUES ('1000-1001','120.00','110.00','105.00','0.00','5.50'),('1000-1002','320.00','300.00','0.00','0.00','0.00'),('1000-1003','305.00','295.00','0.00','0.00','0.00'),('1000-1004','335.00','320.00','0.00','0.00','0.00'),('1000-1005','250.00','220.00','200.00','0.00','0.00'),('1000-1006','195.00','0.00','0.00','0.00','0.00'),('1000-1007','85.00','0.00','0.00','0.00','0.00'),('1000-1008','205.00','0.00','0.00','0.00','0.00'),('1000-1012','435.00','415.00','0.00','0.00','0.00'),('1000-1014','385.00','375.00','0.00','0.00','0.00'),('1000-1009','0.00','0.00','0.00','0.00','0.00'),('1000-1010','0.00','0.00','0.00','0.00','0.00'),('1000-1011','0.00','0.00','0.00','0.00','0.00');
UNLOCK TABLES;
/*!40000 ALTER TABLE `PRISLISTA` ENABLE KEYS */;

--
-- Table structure for table `PRODUKTGRUPP`
--

DROP TABLE IF EXISTS `PRODUKTGRUPP`;
CREATE TABLE `PRODUKTGRUPP` (
  `PRODKLASS` varchar(5) NOT NULL default '',
  `BESKRIVNING` varchar(30) default NULL,
  `MOMSKOD` varchar(5) default NULL,
  PRIMARY KEY  (`PRODKLASS`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `PRODUKTGRUPP`
--


/*!40000 ALTER TABLE `PRODUKTGRUPP` DISABLE KEYS */;
LOCK TABLES `PRODUKTGRUPP` WRITE;
INSERT INTO `PRODUKTGRUPP` (`PRODKLASS`, `BESKRIVNING`, `MOMSKOD`) VALUES ('2200','Hårddiskar','MOMS1'),('2500','Bildskärmar','MOMS1'),('2300','Tangentbord','MOMS1'),('2400','Routers','MOMS1'),('2100','Switchar','MOMS1'),('1001','C++-programmering','MOMS3'),('1002','Qt-böcker','MOMS3'),('1003','C-programmering','MOMS3');
UNLOCK TABLES;
/*!40000 ALTER TABLE `PRODUKTGRUPP` ENABLE KEYS */;

--
-- Table structure for table `PROGRAM`
--

DROP TABLE IF EXISTS `PROGRAM`;
CREATE TABLE `PROGRAM` (
  `PRGNR` char(3) NOT NULL default '',
  `MENYAVD` varchar(20) default NULL,
  `MENYGRP` varchar(30) default NULL,
  `MENYTXT` varchar(30) default NULL,
  `PROGRAM` varchar(8) default NULL,
  PRIMARY KEY  (`PRGNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `PROGRAM`
--


/*!40000 ALTER TABLE `PROGRAM` DISABLE KEYS */;
LOCK TABLES `PROGRAM` WRITE;
INSERT INTO `PROGRAM` (`PRGNR`, `MENYAVD`, `MENYGRP`, `MENYTXT`, `PROGRAM`) VALUES ('001','Administration','Användaradministration','Ny användare','ADDUSRW'),('002','Administration','Användaradministration','Ändra användarinfo','CHGUSRW'),('003','Administration','Användaradministration','Ta bort användare','DELUSRW'),('004','Administration','Användaradministration','Visa en användare','DSPUSRW'),('005','Administration','Användaradministration','Lista användare','LSTUSRW'),('006','Administration','Behörighetsadministration','Ny behörighet','ADDRGTW'),('007','Administration','Behörighetsadministration','Ändra behörighet',''),('008','Administration','Behörighetsadministration','Ta bort behörighet','DELRGTW'),('009','Administration','Behörighetsadministration','Visa behörighet',''),('010','Administration','Behörighetsadministration','Lista behörigheter','LSTRGTW'),('011','Administration','Funktionsadministration','Ny funktion','ADDFNCW'),('012','Administration','Funktionsadministration','Lista funktioner','LSTFNCW'),('013','Ekonomi','Bokföring','Registrera verifikation','BOKFORSW'),('014','Ekonomi','Bokföring','Registrera ver. standard','BOKFORSW'),('015','Ekonomi','Kontoadministration','Nytt konto','ADDKTOW'),('016','Ekonomi','Kontoadministration','Ändra konto','CHGKTOW'),('017','Ekonomi','Kontoadministration','Ta bort konto',''),('018','Ekonomi','Kontoadministration','Visa konto','DSPKTOW'),('019','Ekonomi','Kontoadministration','Lista konton','LSTKTOW'),('020','Ekonomi','Kostnadställeadministration','Nytt kostnadställe','ADDKSTW'),('021','Ekonomi','Kostnadställeadministration','Ändra kostnadställe',''),('022','Ekonomi','Kostnadställeadministration','Ta bort kostnadställe',''),('023','Ekonomi','Kostnadställeadministration','Visa ett kostnadsställe','DSPKSTW'),('024','Ekonomi','Kostnadställeadministration','Lista kostnadsställen','LSTKSTW'),('025','Ekonomi','Valutaadministration','Ny valuta','ADDVALW'),('026','Ekonomi','Valutaadministration','Ändra valuta','CHGVALW'),('027','Ekonomi','Valutaadministration','Ta bort valuta','DELVALW'),('028','Ekonomi','Valutaadministration','Visa valuta','DSPVALW'),('029','Ekonomi','Valutaadministration','Lista valutor','LSTVALW'),('030','Ekonomi','Rapporter','Kontorapport','RPTKTOW'),('031','Ekonomi','Rapporter','Rapportgenerator','RPTGENW'),('032','Ekonomi','Räkenskapsår','Nytt bokföringsår','ADDBARW'),('033','Ekonomi','Räkenskapsår','Ändra bokföringsårsdata','CHGBARW'),('034','Administration','Företagsdata','Ny post','ADDFTGW'),('035','Administration','Företagsdata','Ändra post','CHGFTGW'),('036','Administration','Företagsdata','Visa företagsdata','DSPFTGW'),('037','Försäljning','Kunddata','Ny kund','ADDKUW'),('038','Försäljning','Kunddata','Ny leveransadress för kund','ADDLEVPW'),('039','Inköp','Leverantörsdata','Ny leverantör','ADDLEVW'),('040','Inköp','Leverantörsdata','Visa en leverantör','DSPLEVW'),('041','Inköp','Leverantörsdata','Ändra leverantörsdata','CHGLEVW'),('042','Ekonomi','Bokföring','Reg. leverantörsfaktura','LEVFAKTW'),('043','Ekonomi','Rapporter','Leverantörsreskontra','LEVRESKW'),('044','Ekonomi','Rapporter','Förfallna levfakturor','ATTBETW'),('045','Ekonomi','Rapporter','Saldolista','SDOLISW'),('046','Försäljning','Kunddata','Visa kunddata','DSPKUW'),('047','Försäljning','Kunddata','Ändra kunddata','CHGKUW'),('048','Försäljning','Kunddata','Lista kunder','LSTKUW'),('049','Administration','Företagsdata','Byta företag','BYTFTGW'),('050','Materialhantering','Artikeldata','Ny artikel','ADDARW'),('051','Materialhantering','Artikeldata','Visa grunddata för en artikel','DSPARW'),('052','Materialhantering','Artikeldata','Visa en artikels ekonomidata','DSPAREW'),('053','Materialhantering','Artikeldata','Ändra artikeldata','CHGARW'),('054','Administration','Betalningsvillkor','Lista betalningsvillkor','LSTBETVW'),('055','Administration','Betalningsvillkor','Nya betalningsvillkor','ADDBETVW'),('056','Materialhantering','Artikeldata','Lista artiklar','LSTARW'),('057','Administration','Betalningsvillkor','Ändra betalningsvillkor','CHGBETVW'),('058','Inköp','Beställningar','Registrera inköpsorder','ADDINKW'),('059','Inköp','Beställningar','(Ändra beställning)','CHGINKW'),('060','Inköp','Beställningar','(Annulera beställning)','DELINKW'),('061','Inköp','Beställningar','Visa beställning','DSPINKW'),('062','Inköp','Beställningar','Beställningsstock','LSTINKW'),('063','Inköp','Beställningar','Skriv ut beställning','PRTINKW'),('064','Inköp','Beställningar','(Avprickning följesedel)','UPDINKW'),('065','Försäljning','Kundorder','Registrera kundorder','ADDORDW'),('066','Försäljning','Kundorder','Ändra kundorder','CHGORDW'),('067','Försäljning','Kundorder','(Makulera kundorder)','DELORDW'),('068','Försäljning','Kundorder','Visa en kundorder','DSPORDW'),('069','Försäljning','Kundorder','Lista kundorder','LSTORDW'),('070','Försäljning','Kundorder','Skriva ut plocklista','PLORDW'),('071','Försäljning','Kundorder','(Skriva ut följesedel)','FSORDW'),('072','Försäljning','Kundorder','Fakturera kundorder','KUFAKTW'),('074','Administration','Företagsdata','Ny text i textregistret','ADDTXTW'),('073','Inköp','Leverantörsdata','Lista leverantörer','LSTLEVW'),('076','Administration','Leveransvillkor','Nya leveransvillkor','ADDLEVVW'),('075','Administration','Företagsdata','Radera post i textregistret','DELTXTW'),('077','Administration','Leveransvillkor','Lista leveransvillkor','LSTLEVVW'),('078','Administration','Leveranssätt','Nya leveranssätt','ADDLEVSW'),('079','Administration','Leveranssätt','Lista leveranssätt','LSTLEVSW'),('080','Ekonomi','Rapporter','Balansräkning','BALRPTW'),('081','Ekonomi','Rapporter','Huvudbok','HUVBOKW'),('082','Ekonomi','Rapporter','Dagbok','DAGBOKW'),('083','Försäljning','Kunddata','Lista kunders leveransplatser','LSTLEVPW'),('084','Administration','Företagsdata','Ny databasregistrering','ADDFORW'),('085','Administration','Företagsdata','Lista databaser','LSTFORW'),('086','Materialhantering','Artikeladmin.','Ny produktklass/produktgrupp','ADDPKDW'),('087','Materialhantering','Artikeladmin.','Lista produktklass/produktgrup','LSTPKDW'),('088','Ekonomi','Räkenskapsår','Visa bokföringsår','DSPBARW'),('089','Administration','Företagsdata','Lista företagsdata','LSTFTGW'),('090','Ekonomi','Rapporter','Resultatrapport','RESRPTW'),('091','Ekonomi','Räkenskapsår','Lista alla räkenskapsår','LSTBARW'),('092','Försäljning','Kunddata','Söka kunder','SRCHKUW'),('093','Ekonomi','Rapporter','Skapa SIE-fil','RPTSIEW'),('094','Försäljning','Kundorder','Pricka av plocklista','PLCHGW'),('095','Ekonomi','Rapporter','Kundreskontra','KURESKW'),('096','Administration','Företagsdata','Lista texter i TEXTREG','LSTTXTW'),('097','Administration','Företagsdata','Visa en post i TEXTREG','DSPTXTW'),('098','Materialhantering','Artikeldata','Söka artikel','SRCHARW'),('099','Ekonomi','Bokföring','Reg. betald kundfaktura','KUFAKTBW'),('100','Materialhantering','Artikeladmin.','Lista prislistor','LSTPRISW'),('101','Materialhantering','Artikeladmin.','Ladda nya prislistor','ADDPRISW'),('102','Materialhantering','Artikeladmin.','Ändra i prislistor','CHGPRISW'),('103','Administration','Funktionsadministration','Lista program/moduler','LSTPGMW'),('104','Försäljning','Offerter','Registrera offert','ADDOFFW'),('105','Försäljning','Offerter','Visa en offert','DSPOFFW'),('106','Materialhantering','Artikeladmin.','Visa lagerställepost','DSPLSW'),('107','Materialhantering','Artikeladmin.','Radera lagerställepost','DELLSW'),('108','Materialhantering','Artikeladmin.','Ändra lagerställepost','CHGLSW'),('109','Försäljning','Offerter','Ändra en offert','CHGOFFW'),('110','Försäljning','Offerter','Radera en offert','DELOFFW'),('111','Försäljning','Offerter','Skriv ut en offert','PRTOFFW'),('112','Försäljning','Offerter','Göra en offert till order','OFF2ORDW'),('113','Administration','Behörighetsadministration','Tilldela en användare total be','TOTRGTW'),('114','Administration','Betalningsvillkor','Radera betalningsvillkor','DELBETVW');
UNLOCK TABLES;
/*!40000 ALTER TABLE `PROGRAM` ENABLE KEYS */;

--
-- Table structure for table `RIGHTS`
--

DROP TABLE IF EXISTS `RIGHTS`;
CREATE TABLE `RIGHTS` (
  `USERID` varchar(20) NOT NULL default '',
  `TRNSID` varchar(8) NOT NULL default '',
  PRIMARY KEY  (`USERID`,`TRNSID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `RIGHTS`
--


/*!40000 ALTER TABLE `RIGHTS` DISABLE KEYS */;
LOCK TABLES `RIGHTS` WRITE;
INSERT INTO `RIGHTS` (`USERID`, `TRNSID`) VALUES ('GUEST','ARLIS'),('GUEST','ARLSPK'),('GUEST','ARLST'),('GUEST','ARLSTL'),('GUEST','VALDSP'),('GUEST','VALLST'),('GUEST','WKUDSP'),('ADMIN','ADDARW'),('ADMIN','ADDBARW'),('ADMIN','ADDBETVW'),('ADMIN','ADDFNCW'),('ADMIN','ADDFORW'),('ADMIN','ADDFTGW'),('ADMIN','ADDINKW'),('ADMIN','ADDKSTW'),('ADMIN','ADDKTOW'),('ADMIN','ADDKUW'),('ADMIN','ADDLEVPW'),('ADMIN','ADDLEVSW'),('ADMIN','ADDLEVVW'),('ADMIN','ADDLEVW'),('ADMIN','ADDLPLW'),('ADMIN','ADDOFFW'),('ADMIN','ADDORDW'),('ADMIN','ADDPKDW'),('ADMIN','ADDRGTW'),('ADMIN','ADDTXTW'),('ADMIN','ADDUSRW'),('ADMIN','ADDVALW'),('ADMIN','ADMIN'),('ADMIN','AR2ADD'),('ADMIN','AR2DSP'),('ADMIN','AR2UPD'),('ADMIN','ARADD'),('ADMIN','ARCHG'),('ADMIN','ARCHGL'),('ADMIN','ARCHK'),('ADMIN','ARDSP'),('ADMIN','ARDSPL'),('ADMIN','ARICHK'),('ADMIN','ARLSPK'),('ADMIN','ARLSPK2'),('ADMIN','ARLST'),('ADMIN','ARLSTL'),('ADMIN','ARSRCH'),('ADMIN','ATTBET'),('ADMIN','ATTBETW'),('ADMIN','BALRPTW'),('ADMIN','BARADD'),('ADMIN','BARCHG'),('ADMIN','BARCHK'),('ADMIN','BARCHK2'),('ADMIN','BARDSP'),('ADMIN','BARDSP2'),('ADMIN','BARDSP3'),('ADMIN','BARFND'),('ADMIN','BARLST'),('ADMIN','BETADD'),('ADMIN','BETCHG'),('ADMIN','BETDSP'),('ADMIN','BETLST'),('ADMIN','BETVDEL'),('ADMIN','BOKF'),('ADMIN','BOKFORSW'),('ADMIN','BOKFORW'),('ADMIN','BYTFTGW'),('ADMIN','CHGARW'),('ADMIN','CHGBARW'),('ADMIN','CHGBETVW'),('ADMIN','CHGFTGW'),('ADMIN','CHGKTOW'),('ADMIN','CHGKUW'),('ADMIN','CHGLEVW'),('ADMIN','CHGLSW'),('ADMIN','CHGOFFW'),('ADMIN','CHGORDW'),('ADMIN','CHGPRISW'),('ADMIN','CHGUSRW'),('ADMIN','CHGVALW'),('ADMIN','CPYKTOW'),('ADMIN','DAGBOKW'),('ADMIN','DATABASE'),('ADMIN','DBCHK'),('ADMIN','DBOKRPT'),('ADMIN','DELBETVW'),('ADMIN','DELLSW'),('ADMIN','DELOFFW'),('ADMIN','DELRGTW'),('ADMIN','DELTXTW'),('ADMIN','DELUSRW'),('ADMIN','DELVALW'),('ADMIN','DSPAREW'),('ADMIN','DSPARW'),('ADMIN','DSPBARW'),('ADMIN','DSPFTG1W'),('ADMIN','DSPFTGW'),('ADMIN','DSPINKW'),('ADMIN','DSPKSTW'),('ADMIN','DSPKTOW'),('ADMIN','DSPKUW'),('ADMIN','DSPLEVVW'),('ADMIN','DSPLEVW'),('ADMIN','DSPLSW'),('ADMIN','DSPOFFW'),('ADMIN','DSPORDW'),('ADMIN','DSPTXTW'),('ADMIN','DSPUSRW'),('ADMIN','DSPVALW'),('ADMIN','FAKTDSP'),('ADMIN','FORADD'),('ADMIN','FORCHK'),('ADMIN','FORDSP'),('ADMIN','FORLST'),('ADMIN','FSORDW'),('ADMIN','FTGADD'),('ADMIN','FTGADM'),('ADMIN','FTGDSP'),('ADMIN','FTGLIS'),('ADMIN','FTGLST'),('ADMIN','FTGUPD'),('ADMIN','HBOKRPT'),('ADMIN','HUVBOKW'),('ADMIN','INKADD'),('ADMIN','INKHDSP'),('ADMIN','INKLST'),('ADMIN','INKRADD'),('ADMIN','INKRLST'),('ADMIN','KRELST'),('ADMIN','KRESADD'),('ADMIN','KRESCHK'),('ADMIN','KRESLST'),('ADMIN','KRESUPD'),('ADMIN','KSTADD'),('ADMIN','KSTCHK'),('ADMIN','KSTDSP'),('ADMIN','KSTLST'),('ADMIN','KTOADD'),('ADMIN','KTOCHG'),('ADMIN','KTOCHK'),('ADMIN','KTODSP'),('ADMIN','KTOLST'),('ADMIN','KTORPT'),('ADMIN','KTORPT2'),('ADMIN','KTOVIEW'),('ADMIN','KUADD'),('ADMIN','KUCHG'),('ADMIN','KUCHK'),('ADMIN','KUDSP'),('ADMIN','KUFAKTBW'),('ADMIN','KUFAKTW'),('ADMIN','KULST'),('ADMIN','KURESKW'),('ADMIN','KUSRCH'),('ADMIN','LEVADD'),('ADMIN','LEVCHG'),('ADMIN','LEVDSP'),('ADMIN','LEVFAKTW'),('ADMIN','LEVLST'),('ADMIN','LEVPDSP'),('ADMIN','LEVPLST'),('ADMIN','LEVRESKW'),('ADMIN','LEVSADD'),('ADMIN','LEVSDSP'),('ADMIN','LEVSLST'),('ADMIN','LEVVADD'),('ADMIN','LEVVDSP'),('ADMIN','LEVVLST'),('ADMIN','LRESADD'),('ADMIN','LRESRPT'),('ADMIN','LSDEL'),('ADMIN','LSTARW'),('ADMIN','LSTBARW'),('ADMIN','LSTBETVW'),('ADMIN','LSTFNCW'),('ADMIN','LSTFORW'),('ADMIN','LSTFTGW'),('ADMIN','LSTINKW'),('ADMIN','LSTKSTW'),('ADMIN','LSTKTOW'),('ADMIN','LSTKUW'),('ADMIN','LSTLEVPW'),('ADMIN','LSTLEVSW'),('ADMIN','LSTLEVVW'),('ADMIN','LSTLEVW'),('ADMIN','LSTORDW'),('ADMIN','LSTPGMW'),('ADMIN','LSTPKDW'),('ADMIN','LSTRGTW'),('ADMIN','LSTTXTW'),('ADMIN','LSTUSRW'),('ADMIN','LSTVALW'),('ADMIN','OFF2ORDW'),('ADMIN','OFFADD'),('ADMIN','OFFCHG'),('ADMIN','OFFDEL'),('ADMIN','OFFDSP'),('ADMIN','OFFLST'),('ADMIN','OFFRADD'),('ADMIN','OFFRCHG'),('ADMIN','OFFRDSP'),('ADMIN','OLFIX'),('ADMIN','OLFIXHLP'),('ADMIN','OLFIXTW'),('ADMIN','OLFIXW'),('ADMIN','ORADUPD'),('ADMIN','ORDADD'),('ADMIN','ORDCHG'),('ADMIN','ORDCHK'),('ADMIN','ORDDSP'),('ADMIN','ORDLST'),('ADMIN','ORDLST2'),('ADMIN','ORDRADD'),('ADMIN','ORDRCHG'),('ADMIN','ORDRDSP'),('ADMIN','ORDRUPD'),('ADMIN','ORDUPD'),('ADMIN','ORRUPD'),('ADMIN','PICKADD'),('ADMIN','PICKDSP'),('ADMIN','PICKLST'),('ADMIN','PKDADD'),('ADMIN','PKDDSP'),('ADMIN','PKDLST'),('ADMIN','PLCHGW'),('ADMIN','PLORDW'),('ADMIN','PRGLST'),('ADMIN','PRISDSP'),('ADMIN','PRISUPD'),('ADMIN','PRTAPI'),('ADMIN','PRTINKW'),('ADMIN','PRTOFFW'),('ADMIN','RESRPTW'),('ADMIN','RGTADD'),('ADMIN','RGTCHK'),('ADMIN','RGTDEL'),('ADMIN','RGTDSP'),('ADMIN','RGTLST'),('ADMIN','RPTCRE'),('ADMIN','RPTGENW'),('ADMIN','RPTKTOW'),('ADMIN','RPTSIEW'),('ADMIN','SDOLISW'),('ADMIN','SIEEXPK'),('ADMIN','SIEEXPR'),('ADMIN','SIEEXPV'),('ADMIN','SLPADD'),('ADMIN','SRCHARW'),('ADMIN','SRCHKUW'),('ADMIN','STYRMAN'),('ADMIN','TESTW'),('ADMIN','TOTADD'),('ADMIN','TOTRGT'),('ADMIN','TOTRGTW'),('ADMIN','TRHDADD'),('ADMIN','TRNSADD'),('ADMIN','TRNSLST'),('ADMIN','TXTADD'),('ADMIN','TXTDEL'),('ADMIN','TXTDSP'),('ADMIN','TXTLST'),('ADMIN','USERADD'),('ADMIN','USERCHG'),('ADMIN','USERDEL'),('ADMIN','USERDSP'),('ADMIN','USERLST'),('ADMIN','VALADD'),('ADMIN','VALCHG'),('ADMIN','VALDEL'),('ADMIN','VALDSP'),('ADMIN','VALLST'),('ADMIN','VERHDSP'),('ADMIN','VERHLST'),('ADMIN','VERUPD'),('ADMIN','WKUDSP'),('ADMIN','WRREC'),('JAPI','TSTFNC'),('OLFIX','ADDRGTW'),('OLFIX','ARICHK'),('OLFIX','BARDSP'),('OLFIX','KTOCHK'),('OLFIX','KTOLST'),('OLFIX','KTOVIEW'),('OLFIX','PRGLST'),('OLFIX','RGTADD'),('OLFIX','RGTCHK'),('OLFIX','RGTDEL'),('OLFIX','RGTLST'),('OLFIX','TRHDADD'),('OLFIX','TRNSADD'),('OLFIX','TRNSDEL'),('OLFIX','USERADD'),('OLFIX','USERLST'),('OLFIX','VERUPD'),('TESTARE','KUCHK'),('TESTARE','LSTUSRW'),('TESTARE','PRGLST'),('TESTARE','RGTCHK'),('TESTARE','USERADD'),('TESTARE','USERDSP'),('TESTARE','USERLST');
UNLOCK TABLES;
/*!40000 ALTER TABLE `RIGHTS` ENABLE KEYS */;

--
-- Table structure for table `STDLEVPLATS`
--

DROP TABLE IF EXISTS `STDLEVPLATS`;
CREATE TABLE `STDLEVPLATS` (
  `STDLEVPLATS` char(3) NOT NULL default '',
  `KUNDNR` varchar(10) NOT NULL default '',
  `ADRESS` varchar(30) NOT NULL default '',
  `POSTNR` varchar(6) NOT NULL default '',
  `POSTADR` varchar(30) NOT NULL default '',
  `LAND` varchar(30) default NULL,
  PRIMARY KEY  (`STDLEVPLATS`,`KUNDNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `STDLEVPLATS`
--


/*!40000 ALTER TABLE `STDLEVPLATS` DISABLE KEYS */;
LOCK TABLES `STDLEVPLATS` WRITE;
INSERT INTO `STDLEVPLATS` (`STDLEVPLATS`, `KUNDNR`, `ADRESS`, `POSTNR`, `POSTADR`, `LAND`) VALUES ('002','4375','Bakgatan 1D','199 09','SMÃ…STAD','-'),('001','4375','Bakgatan 1C','199 09','SMÃ…STAD','Sverige'),('555','4375','Testgatan 3','199 02','PROVSTAD','Sverige'),('001','4376','Industrigatan 13','199 21','LILLEBY','Sverige'),('002','4376','Bokhållargatan 3','199 19','LILLEBY','Sverige'),('001','tst','TestAdress','123456','Testpostadr','-');
UNLOCK TABLES;
/*!40000 ALTER TABLE `STDLEVPLATS` ENABLE KEYS */;

--
-- Table structure for table `TEXTREG`
--

DROP TABLE IF EXISTS `TEXTREG`;
CREATE TABLE `TEXTREG` (
  `TEXTNR` char(3) NOT NULL default '',
  `TXT` text,
  PRIMARY KEY  (`TEXTNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `TEXTREG`
--


/*!40000 ALTER TABLE `TEXTREG` DISABLE KEYS */;
LOCK TABLES `TEXTREG` WRITE;
INSERT INTO `TEXTREG` (`TEXTNR`, `TXT`) VALUES ('002','Endast komplett order får levereras.\nLeverans ska ske med Danzas/ASG.\nVårt kundnr hos Danzas/ASG är 991145.'),('003','Detta är ytterligare ett test med textregistret.\nMed radnr 2.\nOch med rad nr 3.\n'),('001','Ordererkännande önskas inom 3 arbetsdagar (om ej redan bekräftats)\nAnge alltid vårt artikelnummer på följesedel och faktura.\n');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TEXTREG` ENABLE KEYS */;

--
-- Table structure for table `TRANSID`
--

DROP TABLE IF EXISTS `TRANSID`;
CREATE TABLE `TRANSID` (
  `TRNSID` varchar(8) NOT NULL default '',
  `TRNSTXT` varchar(60) default NULL,
  PRIMARY KEY  (`TRNSID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `TRANSID`
--


/*!40000 ALTER TABLE `TRANSID` DISABLE KEYS */;
LOCK TABLES `TRANSID` WRITE;
INSERT INTO `TRANSID` (`TRNSID`, `TRNSTXT`) VALUES ('ARICHK','Kontrollera om visst bokföringsår finns'),('BARDSP','Hämta data för angivet bokföringsår'),('BARCHK','Kontrollera om visst bokföringsår finns'),('BOKF','Bokföringsprogram'),('FORDSP','Visa info om databas nr x'),('FTGUPD','Uppdatera företagsdata'),('KSTADD','Nyupplägg av kostnadsställe'),('KSTCHK','Kontrollera om visst kostnadställe finns'),('KSTDSP','Visa info för ett kostnadställe'),('KSTLST','Lista kostnadsställen på skärm'),('KTOADD','Lägga till en ny post i konto'),('KTOCHG','Ändra info för ett kontonr'),('KTOCHK','Kontrollera om visst konto finns'),('KTODEL','Ta bort post i konto (endast utan transaktioner)'),('KTODSP','Visa info på ett konto'),('KTOLST','Lista alla konton, nr och text'),('KTORPT','Lista alla poster i tabellen VERRAD'),('KTOUPD','Uppdatera konto med antingen debet eller kredit'),('KTOVIEW','Visa kontonr och benämning på skärm'),('PRGLST','Lista program'),('RGTADD','Lägga till behörighet till transaktioner'),('RGTCHK','Kontrolera användares behörighet'),('RGTDEL','Ta bort behörighet till transaktioner'),('RGTDSP','Visa behörigheter för en användare'),('RGTLST','Lista alla behörigheter'),('TRHDADD','Lägga till ny loggpost i TRHD'),('TRNSADD','Ny post i TRANSID'),('TRNSCHG','Ändra post i TRANSID'),('TRNSDEL','Ta bort post i TRANSID'),('TRNSDSP','Visa enstaka TRANSID'),('TRNSLST','Lista alla TRANSID'),('USERADD','Ny post i USER'),('USERCHG','Ändra post i USER'),('USERDEL','Ta bort post i USER'),('USERDSP','Visa en användare'),('USERLST','Lista alla användare'),('VALLST','Lista valutor'),('VALADD','Lägga upp en ny valuta'),('VALCHG','Ändra valutainformation'),('VALDEL','Ta bort en valuta'),('VALDSP','Visa en valuta'),('VERUPD','Nyuppläggning av verifikat'),('VERDSP','Visa enstaka verifikation'),('VRDADD','Ny detaljpost för verifikation till VERD'),('VRHADD','Ny huvudpost för verifikation till VERH'),('WRREC','Skriva post till tempfilen /tmp/vernr.txt'),('ATTBET','Lista leverantörsfakturor att betala'),('BARADD','Lägga upp nytt bokföringsår'),('BARCHG','Ändra data för angivet bokföringsår'),('BARFND','Hitta bokföringsår för angivet datum'),('BETDSP','Visa ett betalningsvillkor'),('FTGADD','Lägga upp en ny företagspost'),('FTGDSP','Visa företagsdata'),('FTGLST','Lista posttyper för företagsdata'),('FTGLIS','Lista företagsdata'),('KUADD','Registrera nya kunder'),('KUCHG','Ändra kunddata'),('KUCHK','Kontrollera om kundnr finns'),('KUDSP','Visa kunddata'),('KULST','Lista kunder, kundnr och namn'),('LEVADD','Lägga upp en ny leverantör'),('LEVCHG','Ändra leverantörsdata'),('LEVDSP','Visa en leverantör'),('LEVLST','Lista leverantörer,nr och namn'),('LRESRPT','Lista alla obetalda poster i tabellen LEVRESK'),('LRESADD','Ny post i leverantörsreskontran'),('RPTCRE','Rapportgenerator. Skapa rapporter'),('SLPADD','Standardleveransplats'),('TRNTST','Detta är en testfunktion'),('ARCHK','Kontrollera om artikelnummer finns'),('ARADD','Lägga upp en ny artikel'),('AR2ADD','Lägga upp ny artikel i lagerställeregister'),('ARDSP','Visa grunddata för en artikel'),('ARDSPL','Visa lagerdata för en artikel'),('ARCHG','Ändra grunddata för en artikel'),('ARCHGL','Ändra lagerställedata för en artikel'),('BETLST','Lista betalningsvillkor'),('BETADD','Lägga upp ett nytt betalningsvillkor'),('ARLST','Lista artiklar(artikelnr,benämn1,benämn2)'),('BETCHG','Ändra data för betalningsvillkor'),('TXTDSP','Visa texter ur TEXTREG'),('TXTADD','Lägg upp en ny post i TEXTREG'),('INKADD','Lägga upp en ny inköpsorder'),('INKRADD','Lägga upp en ny inköpsorderrad'),('TXTDEL','Radera post i TEXTREG'),('INKRLST','Lista alla rader på angiven inköpsorder'),('INKHDSP','Visa orderhuvud för angiven inköpsorder'),('INKLST','Beställningsstock'),('LEVVDSP','Visa ett leveransvillkor'),('LEVSDSP','Visa ett leveranssätt'),('LEVVADD','Lägga upp ett nytt leveransvillkor'),('LEVSADD','Lägga upp ett nytt leveranssätt'),('LEVVLST','Lista leveransvillkor'),('LEVSLST','Lista leveranssätt'),('VERHDSP','Hämta mindatum och maxdatum för angivet bokf.år'),('VERHLST','Lista verifikationers huvudposter för önskat bokföringsår'),('HBOKRPT','Huvudboksrapport'),('DBOKRPT','Dagboksrapport'),('PRTAPI','Utskriftsinterface'),('LEVPLST','Lista kunders leveransadresser'),('FORCHK','Kontr. om databas finns i tabell DATABAS'),('FORADD','Ny databas i tabellen DATABAS'),('FORLST','Lista databaser i tabell DATABAS'),('PKDADD','Ny produktgrupp/produktkod/produktklass'),('PKDLST','Lista produktgrupper/produktkoder/produktklasser'),('WKUDSP','Visa begränsade kunddata för webbkund'),('ARLSTL','Lista artiklar med lagersaldo'),('ARLIS','Lista artiklar för angiven produktklass'),('ARLSPK','Lista artiklar för angiven produktkod'),('AR2UPD','Uppdatera artikelpost i LAGERSTELLEREG'),('BARLST','Lista bokföringsår'),('KUSRCH','Söka kunder på namn, postnr, tfnnr eller postadr'),('LEVPDSP','Visa en standardleveransplats'),('ORDADD','Nyupplägg av kundorderhuvud'),('ORDCHK','Kontrollera diverse uppgifter på kundorder'),('ORDDSP','Visa en kundorders huvudpost'),('ORDRDSP','Visa en kundorders orderrader'),('PKDDSP','Visa en produktgrupp/produktkod/produktklass'),('SIEEXPK','SIE-export av kontoplan'),('SIEEXPR','SIE-export av resultat'),('SIEEXPV','SIE-export av verifikat'),('DBCHK','Lista databaser registrerade i databasen mysql'),('ORDLST2','Lista kundorder med begränsad information'),('ORDLST','Lista kundorder'),('PICKADD','Nytt plock av kundorderrad'),('PICKDSP','Visa plockade men ej utskrivna plock'),('PICKLST','Lista avprickade kundorderrader'),('KRESADD','Ny post till kundreskontran'),('ORADUPD','Uppdatera önskat fält i ORDERRADREG'),('ORDRUPD','Uppdatera ORDERRADREG'),('ORDUPD','Uppdatera önskat fält i ORDERREG'),('ARLSPK2','Lista artiklar/produktkod med saldo'),('KRESLST','Lista poster i kundreskontran'),('ORDRADD','Lägga upp ny rad på kundorder'),('TXTLST','Lista texter i TEXTREG'),('DSPTXTW','Visa en text i textregistret'),('ARSRCH','Söka artikel'),('PRISDSP','Visa prislistepriser på önskad artikel'),('OFFADD','Registrera ny offert (huvudet)'),('OFFRADD','Registrera ny offert (rad)'),('OFFLST','Lista offerter'),('OFFDSP','Visa en offert'),('OFFRDSP','Visa alla offertrader för en offert'),('LSDEL','Radera post i LAGERSTELLEREG.'),('OFFCHG','Uppdatera offertregistret.'),('OFFRCHG','Ändra/uppdatera offertrader'),('OFFDEL','Radera offerter'),('TOTRGT','Skapa totala rättigheter för en användare.'),('TOTADD','Ge en användare fullständig behörighet.'),('DATABASE','Hantera olika databaser'),('BETVDEL','Radera ett betalningsvillkor.');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TRANSID` ENABLE KEYS */;

--
-- Table structure for table `TRHD`
--

DROP TABLE IF EXISTS `TRHD`;
CREATE TABLE `TRHD` (
  `TRNSNR` int(11) NOT NULL auto_increment,
  `TRNSID` varchar(8) NOT NULL default '',
  `TID` varchar(20) NOT NULL default '',
  `USERID` varchar(20) default NULL,
  `TRNSDATA` varchar(255) default NULL,
  PRIMARY KEY  (`TRNSNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `TRHD`
--


/*!40000 ALTER TABLE `TRHD` DISABLE KEYS */;
LOCK TABLES `TRHD` WRITE;
INSERT INTO `TRHD` (`TRNSNR`, `TRNSID`, `TID`, `USERID`, `TRNSDATA`) VALUES (1,'VERADD','2003-1','JAPI','1120 -:- K -:- 1980'),(2,'VERADD','2003-1','JAPI','1120 -:- K -:- 1980'),(3,'VERADD','2003-1','JAPI','1120 -:- K -:- 1980'),(4,'VERADD','2003-11-09_08:34:45','JAPI','1120 -:- K -:- 1980'),(5,'VERADD','2003-11-09_08:34:45','JAPI','1120 -:- K -:- 1980'),(6,'VERADD','2003-11-09_08:48:45','ADMIN','1120 -:- K -:- 1980'),(7,'ARCHGW','2003-11-18_07:05:41','ADMIN','_:_1_:_Test1_:_ABC002_:_100_:_001_:_A_:_SEK_:_125.50_:_50_:_75_:_50_:_198.00_:_202.50_:_195.00_:_62_:_125_:_26.50_:_'),(8,'ARCHGL','2003-11-18_07:10:49','ADMIN','_:_1_:_Test1_:_ABC002_:_100_:_001_:_A_:_SEK_:_125.50_:_50_:_75_:_50_:_198.00_:_202.50_:_195.00_:_62_:_125_:_27.50_:_'),(9,'CHGARW','2003-11-18_07:34:25','ADMIN','_:_1_:_Test1_:_ABC002_:_100.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_155.00_:_202.50_:_155.00_:_62.00_:_125.00_:_27.50_:_'),(10,'CHGARW','2003-11-18_07:38:32','ADMIN','_:_1_:_Test1_:_ABC002_:_100.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_27.5_:_'),(11,'CHGARW','2003-11-18_07:51:01','ADMIN','_:_1_:_Test1_:_ABC002_:_100.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_'),(12,'CHGARW','2003-11-18_12:00:34','ADMIN','_:_1_:_Test1_:_ABC002_:_101.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_'),(13,'CHGARW','2003-11-18_12:04:40','ADMIN','_:_1_:_Test1_:_ABC002_:_102.00_:_001_:_A_:_SEK_:_125.50_:_50.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_'),(14,'CHGARW','2003-11-18_12:08:29','ADMIN','_:_1_:_Test1_:_ABC002_:_102.00_:_001_:_A_:_SEK_:_125.50_:_60.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_'),(15,'CHGARW','2003-11-18_12:12:36','ADMIN','_:_1_:_Test1_:_ABC002_:_103.00_:_001_:_A_:_SEK_:_125.50_:_60.00_:_75.00_:_50.00_:_160.00_:_202.50_:_160.00_:_62.00_:_125.00_:_34.50_:_'),(16,'CHGARW','2003-11-24_05:45:08','ADMIN','_:_1_:_1173-7540_:_AAC001_:_11.00_:_1_:_A_:_SEK_:_98.00_:_0.00_:_0.00_:_0.00_:_103.00_:_0.00_:_103.00_:_0.00_:_65.00_:_5.00_:_'),(17,'CHGARW','2003-11-24_06:39:57','ADMIN','_:_1_:_1173-7540_:_AAC001_:_11.00_:_1_:_A_:_SEK_:_98.00_:_0.00_:_0.00_:_0.00_:_103.00_:_0.00_:_103.00_:_0.00_:_65.00_:_5.00_:_'),(18,'CHGARW','2003-11-24_06:52:13','ADMIN','_:_1_:_1173-7540_:_AAC001_:_11.00_:_1_:_A_:_SEK_:_98.00_:_0.00_:_0.00_:_0.00_:_103.00_:_0.00_:_103.00_:_0.00_:_65.00_:_5.00_:_'),(19,'CHGARW','2003-11-24_07:00:22','ADMIN','_:_1_:_1173-7540_:_AAC001_:_11.00_:_1_:_A_:_SEK_:_98.00_:_0.00_:_0.00_:_0.00_:_103.00_:_0.00_:_0.00_:_0.00_:_65.00_:_5.00_:_'),(20,'CHGARW','2003-11-24_07:01:10','ADMIN','_:_1_:_1173-1445_:_AAA002_:_27.00_:_1_:_A_:_SEK_:_95.00_:_0.00_:_0.00_:_0.00_:_100.00_:_0.00_:_0.00_:_0.00_:_25.00_:_0.00_:_'),(21,'CHGARW','2003-12-07_04:40:48','ADMIN','_:_1_:_7310070059208_:_1_:_2.00_:_1_:_A_:_SEK_:_10.90_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_'),(22,'CHGARW','2003-12-07_04:53:24','ADMIN','_:_1_:_7310070125002_:_1_:_3.00_:_1_:_A_:_SEK_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_'),(23,'BOKFOR','2004-01-02_13:26:43','ADMIN','H AD 00000100 001 2440 D     10000.00           2004-01-02 jan      test nr 100                                                                                                  \n'),(24,'BOKFOR','2004-01-02_13:26:43','ADMIN','D AD 00000100 002 2611 K      2500.00                                                                                                                              l             \n'),(25,'BOKFOR','2004-01-02_13:26:43','ADMIN','D AD 00000100 003 4010 K      7500.00                                                                                                                              l             \n'),(26,'CHGARW','2006-05-03_15:16:36','jan','_:_1_:_2345_:_1_:_25_:_ _:_ _:_SEK_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0_:_0_:_0.00_:_'),(27,'CHGARW','2006-05-04_04:04:15','jan','_:_1_:_Test_:_a2_:_3_:_ _:_a_:_SEK_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00  18:(n_:_'),(28,'CHGLSW','2006-05-11_06:40:49','jan','_:_1_:_Test_:_TEST001_:_12_:_(null)_:_(null)_:_(null)_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:__:_'),(29,'CHGLSW','2006-05-11_06:42:04','jan','_:_1_:_Test_:_TEST001_:_12.00_:_100_:_C_:_SEK_:_50,0_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:__:_'),(30,'CHGLSW','2006-05-11_06:44:27','jan','_:_1_:_Test_:_TEST001_:_12.00_:_100_:_C_:_SEK_:_50.00_:_25_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:_0.00_:__:_');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TRHD` ENABLE KEYS */;

--
-- Table structure for table `USR`
--

DROP TABLE IF EXISTS `USR`;
CREATE TABLE `USR` (
  `USERID` varchar(20) NOT NULL default '',
  `NAMN` varchar(30) default NULL,
  `AVD` varchar(10) default NULL,
  `GRUPP` varchar(10) default NULL,
  PRIMARY KEY  (`USERID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `USR`
--


/*!40000 ALTER TABLE `USR` DISABLE KEYS */;
LOCK TABLES `USR` WRITE;
INSERT INTO `USR` (`USERID`, `NAMN`, `AVD`, `GRUPP`) VALUES ('OLFIX','Olfix Superuser','IT','Stab'),('ADMIN','Jan Pihlgren','IT','Utveckling'),('TESTARE','Testare Test','IT','Stab'),('CARRO','Caroline Inköpare','Inköp','Prod'),('ADMINA','Administratör av OLFIX','IT','Stab'),('GUEST','Guest Apache','Apache','Webb');
UNLOCK TABLES;
/*!40000 ALTER TABLE `USR` ENABLE KEYS */;

--
-- Table structure for table `VALUTA`
--

DROP TABLE IF EXISTS `VALUTA`;
CREATE TABLE `VALUTA` (
  `VALUTAID` char(3) NOT NULL default '',
  `LAND` varchar(15) default NULL,
  `SALJ` decimal(3,2) default NULL,
  `KOP` decimal(3,2) default NULL,
  `BETECKNING` varchar(15) default NULL,
  PRIMARY KEY  (`VALUTAID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `VALUTA`
--


/*!40000 ALTER TABLE `VALUTA` DISABLE KEYS */;
LOCK TABLES `VALUTA` WRITE;
INSERT INTO `VALUTA` (`VALUTAID`, `LAND`, `SALJ`, `KOP`, `BETECKNING`) VALUES ('DKK','Danmark','1.22','1.22','Kronor'),('NOK','Norge','1.23','1.23','Kronor'),('NYZ','Nya Zeeland','4.45','4.45','Dollar'),('SAR','Saudiarabien','2.40','2.40','Riyal'),('HKD','Honkong','0.00','0.00','Dollar'),('MYR','Malaysia','2.36','2.36','Ringgit'),('SGD','Singapore','5.08','5.08','Dollar'),('CAD','Kanada','5.66','5.66','Dollar'),('AUD','Australien','5.03','5.03','Dollar'),('USD','USA','8.97','8.97','Dollar'),('JPY','Japan','7.38','7.38','Yen'),('GBP','Storbritanien','14.26','14.26','Pund'),('EUR','Europa','9.08','9.08','Euro'),('CHF','Schweiz','0.00','0.00','France'),('SEK','Sverige','1.00','1.00','Kronor'),('SEC','TestSverige','1.99','1.98','Kroner');
UNLOCK TABLES;
/*!40000 ALTER TABLE `VALUTA` ENABLE KEYS */;

--
-- Table structure for table `VERHUVUD`
--

DROP TABLE IF EXISTS `VERHUVUD`;
CREATE TABLE `VERHUVUD` (
  `VERNR` int(11) NOT NULL default '0',
  `ARID` char(2) NOT NULL default '',
  `VERDATUM` date default NULL,
  `REGDAT` date default NULL,
  `DEBET` decimal(10,2) default NULL,
  `KREDIT` decimal(10,2) default NULL,
  `VERTEXT` varchar(60) default NULL,
  `KORRIGERAR` int(11) default NULL,
  `KORRIGERAD` int(11) default NULL,
  `USERID` varchar(20) default NULL,
  PRIMARY KEY  (`VERNR`,`ARID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `VERHUVUD`
--


/*!40000 ALTER TABLE `VERHUVUD` DISABLE KEYS */;
LOCK TABLES `VERHUVUD` WRITE;
INSERT INTO `VERHUVUD` (`VERNR`, `ARID`, `VERDATUM`, `REGDAT`, `DEBET`, `KREDIT`, `VERTEXT`, `KORRIGERAR`, `KORRIGERAD`, `USERID`) VALUES (8,'AC','2003-06-27','2003-06-27','3000.00','0.00','Test av hela LEVFAKTW',0,0,'ADMIN'),(4,'AC','2003-06-03','2003-06-03','2000.00','0.00','Inköp av skrivbord',0,0,'ADMIN'),(7,'AC','2003-06-26','2003-06-26','10000.00','0.00','test WRREC',0,0,'ADMIN'),(3,'AC','2003-05-20','2003-05-20','10000.00','0.00','Bokhylla',0,0,'ADMIN'),(2,'AC','2003-05-20','2003-05-20','1000.00','0.00','test nr 2',0,0,'ADMIN'),(1,'AC','2003-05-20','2003-05-20','1000.00','0.00','Test av sortering och DK +-',0,0,'ADMIN'),(9,'AC','2003-06-27','2003-06-27','5000.00','0.00','totaltest nr 2 av LEVFAKTW',0,0,'ADMIN'),(10,'AC','2003-06-27','2003-06-27','5800.00','0.00','Soffgrupp',0,0,'ADMIN'),(11,'AC','2003-07-01','2003-07-01','0.00','0.00','',0,0,'ADMIN'),(12,'AC','2003-07-01','2003-07-01','100.00','0.00','test',0,0,'ADMIN'),(13,'AC','2003-07-02','2003-07-02','4540.00','0.00','test valuta',0,0,'ADMIN'),(14,'AC','2003-07-02','2003-07-02','1500.00','0.00','Inköp av möbler',0,0,'ADMIN'),(15,'AC','2003-07-02','2003-07-02','4540.00','0.00','inköp material',0,0,'ADMIN'),(16,'AC','2003-07-02','2003-07-02','3632.00','0.00','Inköp av material',0,0,'ADMIN'),(17,'AC','2003-07-03','2003-07-03','3139.50','0.00','test',0,0,'ADMIN'),(18,'AC','2003-07-09','2003-07-09','1000.00','0.00','test ocrnummer',0,0,'ADMIN'),(19,'AC','2003-07-09','2003-07-09','3000.00','0.00','test nr 2 av OCR',0,0,'ADMIN'),(20,'AC','2003-07-09','2003-07-09','36320.00','0.00','Inköp av stålbalk',0,0,'ADMIN'),(21,'AC','2003-07-10','2003-07-10','5000.00','0.00','Test av vernr',0,0,'ADMIN'),(22,'AC','2003-07-10','2003-07-10','1000.00','0.00','test',0,0,'ADMIN'),(23,'AC','2003-07-09','2003-07-09','2000.00','0.00','test',0,0,'ADMIN'),(24,'AC','2003-07-10','2003-07-10','9080.00','0.00','test av OCR',0,0,'ADMIN'),(1,'AD','2003-07-30','2003-07-30','300000.00','0.00','Lån eget kapital',0,0,'ADMIN'),(2,'AD','2003-07-30','2003-07-30','499450.00','0.00','Insättning checkräkningskredit',0,0,'ADMIN'),(3,'AD','2003-07-30','2003-07-30','0.00','60000.00','Lokalhyra 1.a kv 2003',0,0,'ADMIN'),(7,'AD','2003-08-01','2003-08-01','0.00','2000.00','Mässingplåt. 1 mm. 0,5 m3',0,0,'ADMIN'),(8,'AD','2003-08-02','2003-08-02','0.00','2000.00','Al-plåt. 1 mm. 1 m3',0,0,'ADMIN'),(9,'AD','2003-08-03','2003-08-03','0.00','3000.00','Järnplåt. 1 mm. 1 m3',0,0,'ADMIN'),(10,'AD','2003-08-04','2003-08-04','0.00','3000.00','Järnplåt. 0,6 mm. 1,5 m3',0,0,'ADMIN'),(11,'AD','2003-08-05','2003-08-05','0.00','3000.00','Järnplåt. 0,3 mm. 3 m3.',0,0,'ADMIN'),(12,'AD','2003-08-06','2003-08-06','0.00','3000.00','Al-plåt 0,75 mm. 2 m3.',0,0,'ADMIN'),(13,'AD','2003-08-07','2003-08-07','0.00','1000.00','Alplåt 0,5 mm 1m3',0,0,'ADMIN'),(14,'AD','2003-08-08','2003-08-08','0.00','1000.00','Al-plåt 1 m3',0,0,'ADMIN'),(15,'AD','2003-08-09','2003-08-09','0.00','36320.00','U-balk. Al. 5 m.',0,0,'ADMIN'),(16,'AD','2003-08-10','2003-08-10','0.00','1000.00','Järnplåt. 0,3 mm. 1 m3',0,0,'ADMIN'),(17,'AD','2003-08-11','2003-08-11','0.00','5000.00','I-balk',0,0,'ADMIN'),(18,'AD','2003-08-11','2003-08-11','0.00','2500.00','Järnplåt. 1 mm. 1 m3',0,0,'ADMIN'),(19,'AD','2003-08-12','2003-08-12','0.00','50000.00','U-balk aluminium. 7 m.',0,0,'ADMIN'),(20,'AD','2003-08-12','2003-08-12','0.00','2000.00','Järnplåt. 0,6mm. 1 m3',0,0,'ADMIN'),(21,'AD','2003-08-13','2003-08-13','0.00','1000.00','Aluminiumplåt. 1 m3',0,0,'ADMIN'),(22,'AD','2003-08-13','2003-08-13','0.00','4000.00','Printerpapper',0,0,'ADMIN'),(23,'AD','2003-08-13','2003-08-13','0.00','5000.00','Pärmar,Kollegieblock,Kopieringspapper',0,0,'ADMIN'),(25,'AC','2003-08-13','2003-08-13','0.00','54480.00','test',0,0,'ADMIN'),(24,'AD','2003-08-16','2003-08-16','0.00','25000.00','Bokhyllor',0,0,'ADMIN'),(25,'AD','2003-09-11','2003-09-11','0.00','40860.00','Aluminiumprofil U',0,0,'ADMIN');
UNLOCK TABLES;
/*!40000 ALTER TABLE `VERHUVUD` ENABLE KEYS */;

--
-- Table structure for table `VERRAD`
--

DROP TABLE IF EXISTS `VERRAD`;
CREATE TABLE `VERRAD` (
  `VERNR` int(11) NOT NULL default '0',
  `RADNR` smallint(6) NOT NULL default '0',
  `ARID` char(2) NOT NULL default '',
  `KTONR` varchar(4) default NULL,
  `BELOPP` decimal(10,2) default NULL,
  `DK` enum('D','K') default NULL,
  `KSTALLE` varchar(4) default NULL,
  `PROJEKT` varchar(4) default NULL,
  `SUBKTO` varchar(4) default NULL,
  `DEFINITIV` enum('J','N') default 'N',
  `STRUKEN` enum('J','N') default 'N',
  PRIMARY KEY  (`VERNR`,`RADNR`,`ARID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `VERRAD`
--


/*!40000 ALTER TABLE `VERRAD` DISABLE KEYS */;
LOCK TABLES `VERRAD` WRITE;
INSERT INTO `VERRAD` (`VERNR`, `RADNR`, `ARID`, `KTONR`, `BELOPP`, `DK`, `KSTALLE`, `PROJEKT`, `SUBKTO`, `DEFINITIV`, `STRUKEN`) VALUES (4,3,'AC','1820','1500.00','K','','','','N','N'),(7,1,'AC','2110','10000.00','D','','','','N','N'),(7,2,'AC','1470','1200.00','K','','','','N','N'),(4,2,'AC','1470','500.00','K','','','','N','N'),(4,1,'AC','2110','2000.00','D','','','','N','N'),(3,3,'AC','1820','7500.00','K','','','','N','N'),(3,2,'AC','1470','2500.00','K','','','','N','N'),(3,1,'AC','2110','10000.00','D','','','','N','N'),(2,3,'AC','1470','250.00','K','','','','N','N'),(2,2,'AC','1510','750.00','K','','','','N','N'),(2,1,'AC','2110','1000.00','D','','','','N','N'),(1,1,'AC','1510','1000.00','D','','','','N','N'),(1,2,'AC','1470','250.00','K','','','','N','N'),(1,3,'AC','1510','750.00','K','','','','N','N'),(7,3,'AC','1810','8800.00','K','','','','N','N'),(8,1,'AC','2110','3000.00','D','','','','N','N'),(8,2,'AC','1470','750.00','K','','','','N','N'),(8,3,'AC','1810','2250.00','K','','','','N','N'),(9,1,'AC','2110','5000.00','D','','','','N','N'),(9,2,'AC','1470','1250.00','K','','','','N','N'),(9,3,'AC','1810','3750.00','K','','','','N','N'),(10,1,'AC','2110','5800.00','D','','','','N','N'),(10,2,'AC','1470','1450.00','K','','','','N','N'),(10,3,'AC','1810','4350.00','K','','','','N','N'),(11,1,'AC','2110','0.00','D','','','','N','N'),(11,2,'AC','1470','0.00','K','','','','N','N'),(11,3,'AC','1810','0.00','K','','','','N','N'),(12,1,'AC','2110','100.00','D','','','','N','N'),(12,2,'AC','1470','25.00','K','','','','N','N'),(12,3,'AC','4010','75.00','K','','','','N','N'),(13,1,'AC','2110','4540.00','D','','','','N','N'),(13,2,'AC','1470','1135.00','K','','','','N','N'),(13,3,'AC','4010','3405.00','K','','','','N','N'),(14,1,'AC','2110','1500.00','D','','','','N','N'),(14,2,'AC','1470','375.00','K','','','','N','N'),(14,3,'AC','1810','1125.00','K','','','','N','N'),(15,1,'AC','2110','4540.00','D','','','','N','N'),(15,2,'AC','1470','1135.00','K','','','','N','N'),(15,3,'AC','4010','3405.00','K','','','','N','N'),(16,1,'AC','2110','3632.00','D','','','','N','N'),(16,2,'AC','1470','908.00','K','','','','N','N'),(16,3,'AC','4010','2724.00','K','','','','N','N'),(17,1,'AC','2110','3139.50','D','','','','N','N'),(17,3,'AC','4010','2354.62','K','','','','N','N'),(17,2,'AC','1470','784.88','K','','','','N','N'),(18,1,'AC','2110','1000.00','D','','','','N','N'),(18,2,'AC','1470','250.00','K','','','','N','N'),(18,3,'AC','4010','750.00','K','','','','N','N'),(19,1,'AC','2110','3000.00','D','','','','N','N'),(19,2,'AC','1470','750.00','K','','','','N','N'),(19,3,'AC','4010','2250.00','K','','','','N','N'),(20,1,'AC','2110','36320.00','D','','','','N','N'),(20,2,'AC','1470','9080.00','K','','','','N','N'),(20,3,'AC','4010','27240.00','K','','','','N','N'),(21,1,'AC','2110','5000.00','D','','','','N','N'),(21,2,'AC','1470','1250.00','K','','','','N','N'),(21,3,'AC','4010','3750.00','K','','','','N','N'),(22,1,'AC','2110','1000.00','D','','','','N','N'),(22,2,'AC','1470','250.00','K','','','','N','N'),(22,3,'AC','4010','750.00','K','','','','N','N'),(23,1,'AC','2110','2000.00','D','','','','N','N'),(23,2,'AC','1470','500.00','K','','','','N','N'),(23,3,'AC','4010','1500.00','K','','','','N','N'),(24,1,'AC','2110','9080.00','D','','','','N','N'),(24,2,'AC','1470','2270.00','K','','','','N','N'),(24,3,'AC','4010','6810.00','K','','','','N','N'),(1,2,'AD','2081','300000.00','K','','','','N','N'),(1,1,'AD','2330','300000.00','D','','','','N','N'),(2,1,'AD','2330','499450.00','D','','','','N','N'),(2,2,'AD','2350','500000.00','K','','','','N','N'),(2,3,'AD','8490','550.00','D','','','','N','N'),(3,1,'AD','2330','60000.00','K','','','','N','N'),(3,2,'AD','2641','12000.00','D','','','','N','N'),(3,3,'AD','5010','48000.00','D','','','','N','N'),(7,2,'AD','2641','500.00','D','','','','N','N'),(7,1,'AD','2440','2000.00','K','','','','N','N'),(8,1,'AD','2440','2000.00','K','','','','N','N'),(7,3,'AD','4010','1500.00','D','','','','N','N'),(8,2,'AD','2641','500.00','D','','','','N','N'),(8,3,'AD','4010','1500.00','D','','','','N','N'),(9,1,'AD','2440','3000.00','K','','','','N','N'),(9,2,'AD','2641','750.00','D','','','','N','N'),(9,3,'AD','4010','2250.00','D','','','','N','N'),(10,1,'AD','2440','3000.00','K','','','','N','N'),(10,2,'AD','2641','750.00','D','','','','N','N'),(10,3,'AD','4010','2250.00','D','','','','N','N'),(11,1,'AD','2440','3000.00','K','','','','N','N'),(11,2,'AD','2641','750.00','D','','','','N','N'),(11,3,'AD','4010','2250.00','D','','','','N','N'),(12,1,'AD','2440','3000.00','K','','','','N','N'),(12,2,'AD','2641','750.00','D','','','','N','N'),(12,3,'AD','4010','2250.00','D','','','','N','N'),(13,1,'AD','2440','1000.00','K','','','','N','N'),(13,2,'AD','2641','250.00','D','','','','N','N'),(13,3,'AD','4010','750.00','D','','','','N','N'),(14,1,'AD','2440','1000.00','K','','','','N','N'),(14,2,'AD','2641','250.00','D','','','','N','N'),(14,3,'AD','4010','750.00','D','','','','N','N'),(15,1,'AD','2440','36320.00','K','','','','N','N'),(15,2,'AD','2641','9080.00','D','','','','N','N'),(15,3,'AD','4010','27240.00','D','','','','N','N'),(16,1,'AD','2440','1000.00','K','','','','N','N'),(16,2,'AD','2641','250.00','D','','','','N','N'),(16,3,'AD','4010','750.00','D','','','','N','N'),(17,1,'AD','2440','5000.00','K','','','','N','N'),(17,2,'AD','2641','1250.00','D','','','','N','N'),(17,3,'AD','4010','3750.00','D','','','','N','N'),(18,1,'AD','2440','2500.00','K','','','','N','N'),(18,2,'AD','2641','625.00','D','','','','N','N'),(18,3,'AD','4010','1875.00','D','','','','N','N'),(19,1,'AD','2440','50000.00','K','','','','N','N'),(19,2,'AD','2641','12500.00','D','','','','N','N'),(19,3,'AD','4010','37500.00','D','','','','N','N'),(20,1,'AD','2440','2000.00','K','','','','N','N'),(20,2,'AD','2641','500.00','D','','','','N','N'),(20,3,'AD','4010','1500.00','D','','','','N','N'),(21,1,'AD','2440','1000.00','K','','','','N','N'),(21,2,'AD','2641','250.00','D','','','','N','N'),(21,3,'AD','4010','750.00','D','','','','N','N'),(22,1,'AD','2440','4000.00','K','','','','N','N'),(22,2,'AD','2641','1000.00','D','','','','N','N'),(22,3,'AD','6110','3000.00','D','','','','N','N'),(23,1,'AD','2440','5000.00','K','','','','N','N'),(23,2,'AD','2641','1250.00','D','','','','N','N'),(23,3,'AD','6110','3750.00','D','','','','N','N'),(25,1,'AC','2110','54480.00','K','','','','N','N'),(25,2,'AC','1470','13620.00','D','','','','N','N'),(25,3,'AC','4010','40860.00','D','','','','N','N'),(24,1,'AD','2440','25000.00','K','','','','N','N'),(24,2,'AD','2641','6250.00','D','','','','N','N'),(24,3,'AD','1220','18750.00','D','','','','N','N'),(25,1,'AD','2440','40860.00','K','','','','N','N'),(25,2,'AD','2611','10215.00','D','','','','N','N'),(25,3,'AD','4010','30645.00','D','','','','N','N');
UNLOCK TABLES;
/*!40000 ALTER TABLE `VERRAD` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

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
