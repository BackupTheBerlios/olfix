# Connection: olfix_1
# Host: localhost
# Saved: 2006-03-26 11:45:38
# 
-- MySQL dump 9.07
--
-- Host: localhost    Database: olfixtst
---------------------------------------------------------
-- Server version	4.1.12

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES latin1 */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


--
-- Table structure for table 'LEVPRISER'
--
use olfix;

DROP TABLE IF EXISTS `LEVPRISER`;
CREATE TABLE `LEVPRISER` (
  `KUNDNR` varchar (10) NOT NULL default '',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `BENEMNING` varchar(60) default '0',
  `PRIS` decimal(10,2) default '0',
  `MATERIALKLASS` varchar(5) default '0',
  `ENHET` varchar(5) default '0',
  `XREF` varchar(30) default '0',
  PRIMARY KEY  (`KUNDNR`,`ARTIKELNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table 'LEVPRISER'
--

use olfixtst;

DROP TABLE IF EXISTS 'LEVPRISER';
CREATE TABLE `LEVPRISER` (
  `KUNDNR` varchar (10) NOT NULL default '',
  `ARTIKELNR` varchar(30) NOT NULL default '',
  `BENEMNING` varchar(60) default '0',
  `PRIS` decimal(10,2) default '0',
  `MATERIALKLASS` varchar(5) default '0',
  `ENHET` varchar(5) default '0',
  `XREF` varchar(30) default '0',
  PRIMARY KEY  (`KUNDNR`,`ARTIKELNR`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table 'LEVPRISER'
--

