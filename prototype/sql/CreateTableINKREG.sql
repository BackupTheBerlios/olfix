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
use olfixtst;
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