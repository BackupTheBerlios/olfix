LOGGFILE=/$HOME/tmp/Kompilering.log
WORKDIR=/opt/olfix/src
date > $LOGGFILE
echo "***** Add *****"
echo "===== AddArtikel, ADDARW" >> $LOGGFILE
cd $WORKDIR/AddArtikel 
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE 
make clean >> $LOGGFILE

echo "===== AddBar, ADDBARW" >> $LOGGFILE
cd $WORKDIR/AddBar
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddBestellning, ADDINKW" >> $LOGGFILE
cd $WORKDIR/AddBestellning
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddBetalvillkor, ADDBETW" >> $LOGGFILE
cd $WORKDIR/AddBetalvillkor
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddForetag, ADDFORW" >> $LOGGFILE
cd $WORKDIR/AddForetag
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddFtgData, ADDFTGW" >> $LOGGFILE
cd $WORKDIR/AddFtgData
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddFunk, ADDFNCW" >> $LOGGFILE
cd $WORKDIR/AddFunk
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddKonto, ADDKTOW" >> $LOGGFILE
cd $WORKDIR/AddKonto
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddKstalle, ADDKSTW" >> $LOGGFILE
cd $WORKDIR/AddKstalle
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddKund, ADDKUW" >> $LOGGFILE
cd $WORKDIR/AddKund
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddLagerplats, ADDLPLW" >> $LOGGFILE
cd $WORKDIR/AddLagerplats
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddLev, ADDLEVW" >> $LOGGFILE
cd $WORKDIR/AddLev
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddLevsett, ADDLEVSW" >> $LOGGFILE
cd $WORKDIR/AddLevsett
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddLevvillkor, ADDLEVVW" >> $LOGGFILE
cd $WORKDIR/AddLevvillkor
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddOrder, ADDORDW" >> $LOGGFILE
cd $WORKDIR/AddOrder
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddProdkod, ADDORDW" >> $LOGGFILE
cd $WORKDIR/AddProdkod
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE
#******************************************************************
# Kolla detta?
#******************************************************************
echo "===== AddProg,??, ej färdig!" >> $LOGGFILE
#cd $WORKDIR/AddProg
#qmake >> $LOGGFILE
#make >> $LOGGFILE
#make clean >> $LOGGFILE
#******************************************************************

echo "===== AddRights, ADDRGTW" >> $LOGGFILE
cd $WORKDIR/AddRights
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddStdLevplats, ADDLEVPW" >> $LOGGFILE
cd $WORKDIR/AddStdLevplats
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddText, ADDTXTW" >> $LOGGFILE
cd $WORKDIR/AddText
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddUser, ADDUSRW" >> $LOGGFILE
cd $WORKDIR/AddUser
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddValuta, ADDVALW" >> $LOGGFILE
cd $WORKDIR/AddValuta
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** B *****"
echo "===== Balansrapport, BALRPTW" >> $LOGGFILE
cd $WORKDIR/Balansrapport
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== BokforStd, BOKFORSW" >> $LOGGFILE
cd $WORKDIR/BokforStd
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Change *****"

echo "===== ChangeArtikel, CHGARW" >> $LOGGFILE
cd $WORKDIR/ChangeArtikel
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeBar, CHGBARW" >> $LOGGFILE
cd $WORKDIR/ChangeBar
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeBetalvillkor, CHGBETVW" >> $LOGGFILE
cd $WORKDIR/ChangeBetalvillkor
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeForetag, BYTFTGW" >> $LOGGFILE
cd $WORKDIR/ChangeForetag
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeFtgData, CHGFTGW" >> $LOGGFILE
cd $WORKDIR/ChangeFtgData
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeKonto, CHGKTOW" >> $LOGGFILE
cd $WORKDIR/ChangeKonto
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeKund, CHGKUW" >> $LOGGFILE
cd $WORKDIR/ChangeKund
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeLev, CHGLEVW" >> $LOGGFILE
cd $WORKDIR/ChangeLev
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeUser, CHGUSRW" >> $LOGGFILE
cd $WORKDIR/ChangeUser
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeValuta, CHGVALW" >> $LOGGFILE
cd $WORKDIR/ChangeValuta
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChgPlocklistaKundorder, PLCHGW" >> $LOGGFILE
cd $WORKDIR/ChgPlocklistaKundorder
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Del *****"

echo "===== Dagbok, DAGBOKW" >> $LOGGFILE
cd $WORKDIR/Dagbok
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DelRights, DELRGTW" >> $LOGGFILE
cd $WORKDIR/DelRights
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DelText, DELTXTW" >> $LOGGFILE
cd $WORKDIR/DelText
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DelUser, DELUSRW" >> $LOGGFILE
cd $WORKDIR/DelUser
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DelValuta, DELVALW" >> $LOGGFILE
cd $WORKDIR/DelValuta
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Dsp *****"

echo "===== DspArtikelEkonomidata, DSPAREW" >> $LOGGFILE
cd $WORKDIR/DspArtikelEkonomidata
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspArtikelGrunddata, DSPARW" >> $LOGGFILE
cd $WORKDIR/DspArtikelGrunddata
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspBar, DSPBARW" >> $LOGGFILE
cd $WORKDIR/DspBar
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspBestellning, DSPINKW" >> $LOGGFILE
cd $WORKDIR/DspBestellning
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspFtgData, DSPFTGW" >> $LOGGFILE
cd $WORKDIR/DspFtgData
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspKonto, DSPKTOW" >> $LOGGFILE
cd $WORKDIR/DspKonto
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspKstalle, DSPKSTW" >> $LOGGFILE
cd $WORKDIR/DspKstalle
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspKund, DSPKUW" >> $LOGGFILE
cd $WORKDIR/DspKund
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspLev, DSPLEVW" >> $LOGGFILE
cd $WORKDIR/DspLev
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspOrder, DSPORDW" >> $LOGGFILE
cd $WORKDIR/DspOrder
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspText, DSPTXTW" >> $LOGGFILE
cd $WORKDIR/DspText
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspUser, DSPUSRW" >> $LOGGFILE
cd $WORKDIR/DspUser
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspValuta, DSPVALW" >> $LOGGFILE
cd $WORKDIR/DspValuta
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** H *****"

echo "===== HelpOlfix, OLFIXHLP" >> $LOGGFILE
cd $WORKDIR/HelpOlfix
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== HittaKund, SRCHKUW" >> $LOGGFILE
cd $WORKDIR/HittaKund
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== Huvudbok, HUVBOKW" >> $LOGGFILE
cd $WORKDIR/Huvudbok
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** K *****"

echo "===== Kontorapport, RPTKTOW" >> $LOGGFILE
cd $WORKDIR/Kontorapport
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Kund *****"

echo "===== KundFaktura, KUFAKTW" >> $LOGGFILE
cd $WORKDIR/KundFaktura
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== KundFakturaBetald, KUFAKTW" >> $LOGGFILE
cd $WORKDIR/KundFakturaBetald
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== KundReskontra, KURESKW" >> $LOGGFILE
cd $WORKDIR/KundReskontra
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Leverantör *****"

echo "===== LevFaktAttBetala, ATTBETW" >> $LOGGFILE
cd $WORKDIR/LevFaktAttBetala
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== LevFaktura, LEVFAKTW" >> $LOGGFILE
cd $WORKDIR/LevFaktura
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== LevReskontra, LEVRESKW" >> $LOGGFILE
cd $WORKDIR/LevReskontra
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** List *****"

echo "===== ListArtikel, LISTARW" >> $LOGGFILE
cd $WORKDIR/ListArtikel
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListBar, LSTBARW" >> $LOGGFILE
cd $WORKDIR/ListBar
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListBestellningsstock, LSTINKW" >> $LOGGFILE
cd $WORKDIR/ListBestellningsstock
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListBetalvillkor, LSTBETVW" >> $LOGGFILE
cd $WORKDIR/ListBetalvillkor
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListForetag, LSTFORW" >> $LOGGFILE
cd $WORKDIR/ListForetag
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListForetagsdata, LSTFTGW" >> $LOGGFILE
cd $WORKDIR/ListForetagsdata
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListFunc, LSTFNCW" >> $LOGGFILE
cd $WORKDIR/ListFunc
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListKonto, LSTKTOW" >> $LOGGFILE
cd $WORKDIR/ListKonto
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListKst, LSTKSTW" >> $LOGGFILE
cd $WORKDIR/ListKst
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListKund, LSTKUW" >> $LOGGFILE
cd $WORKDIR/ListKund
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListKundorder, LSTORDW" >> $LOGGFILE
cd $WORKDIR/ListKundorder
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListLev, LSTLEVW" >> $LOGGFILE
cd $WORKDIR/ListLev
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListLevplats, LSTLEVPW" >> $LOGGFILE
cd $WORKDIR/ListLevplats
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListLevsett, LSTLEVSW" >> $LOGGFILE
cd $WORKDIR/ListLevsett
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListLevvillkor, LSTLEVVW" >> $LOGGFILE
cd $WORKDIR/ListLevvillkor
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListProdkod, LSTPKDW" >> $LOGGFILE
cd $WORKDIR/ListProdkod
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListRights, LSTRGTW" >> $LOGGFILE
cd $WORKDIR/ListRights
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListTextreg, LSTTXTW" >> $LOGGFILE
cd $WORKDIR/ListTextreg
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListUser, LSTUSRW" >> $LOGGFILE
cd $WORKDIR/ListUser
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListValuta, LSTVALW" >> $LOGGFILE
cd $WORKDIR/ListValuta
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Meny *****"

echo "===== MenyOlfixW, OLFIXW" >> $LOGGFILE
cd $WORKDIR/MenyOlfixW
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Prt *****"

echo "===== PrtBestellning, PRTINKW" >> $LOGGFILE
cd $WORKDIR/PrtBestellning
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== PrtBestellningKundorder, FSORDW" >> $LOGGFILE
cd $WORKDIR/PrtFoljesedelKundorder
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== PrtPlocklistaKundorder, PLORDW" >> $LOGGFILE
cd $WORKDIR/PrtPlocklistaKundorder
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== RapportGen, RPTGENW" >> $LOGGFILE
cd $WORKDIR/RapportGen
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== Resultatrapport, RESRPTW" >> $LOGGFILE
cd $WORKDIR/Resultatrapport
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== RptSIEfil, RPTSIEW" >> $LOGGFILE
cd $WORKDIR/RptSIEfil
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== Saldolista, SDOLISW" >> $LOGGFILE
cd $WORKDIR/Saldolista
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== SoekArtikel, SRCHARW" >> $LOGGFILE
cd $WORKDIR/SoekArtikel
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

date > $LOGGFILE
echo "***** KLART *****"