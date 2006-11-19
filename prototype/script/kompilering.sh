LOGGFILE=/$HOME/tmp/Kompilering.log
TARGETDIR=/opt/olfix/bin
WORKDIR=/opt/olfix/src
date > $LOGGFILE
echo "***** Add *****"
echo "===== AddArtikel, ADDARW" >> $LOGGFILE
cd $WORKDIR/AddArtikel 
qmake -project "TARGET=ADDARW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE 
make clean >> $LOGGFILE

echo "===== AddBar, ADDBARW" >> $LOGGFILE
cd $WORKDIR/AddBar
qmake -project "TARGET=ADDBARW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddBestellning, ADDINKW" >> $LOGGFILE
cd $WORKDIR/AddBestellning
qmake -project "TARGET=ADDINKW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddBetalvillkor, ADDBETW" >> $LOGGFILE
cd $WORKDIR/AddBetalvillkor
qmake -project "TARGET=ADDBETW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddForetag, ADDFORW" >> $LOGGFILE
cd $WORKDIR/AddForetag
qmake -project "TARGET=ADDFORW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddFtgData, ADDFTGW" >> $LOGGFILE
cd $WORKDIR/AddFtgData
qmake -project "TARGET=ADDFTGW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddFunk, ADDFNCW" >> $LOGGFILE
cd $WORKDIR/AddFunk
qmake -project "TARGET=ADDFNCW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddKonto, ADDKTOW" >> $LOGGFILE
cd $WORKDIR/AddKonto
qmake -project "TARGET=ADDKTOW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddKstalle, ADDKSTW" >> $LOGGFILE
cd $WORKDIR/AddKstalle
qmake -project "TARGET=ADDKSTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddKund, ADDKUW" >> $LOGGFILE
cd $WORKDIR/AddKund
qmake -project "TARGET=ADDKUW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddLagerplats, ADDLPLW" >> $LOGGFILE
cd $WORKDIR/AddLagerplats
qmake -project "TARGET=ADDLPLW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddLev, ADDLEVW" >> $LOGGFILE
cd $WORKDIR/AddLev
qmake -project "TARGET=ADDLEVW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddLevsett, ADDLEVSW" >> $LOGGFILE
cd $WORKDIR/AddLevsett
qmake -project "TARGET=ADDLEVSW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddLevvillkor, ADDLEVVW" >> $LOGGFILE
cd $WORKDIR/AddLevvillkor
qmake -project "TARGET=ADDLEVVW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddOffert, ADDOFFW" >> $LOGGFILE
cd $WORKDIR/AddOffert
qmake -project "TARGET=ADDOFFW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddOrder, ADDORDW" >> $LOGGFILE
cd $WORKDIR/AddOrder
qmake -project "TARGET=ADDORDW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddProdkod, ADDPKDW" >> $LOGGFILE
cd $WORKDIR/AddProdkod
qmake -project "TARGET=ADDPKDW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
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
qmake -project "TARGET=ADDRGTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddStdLevplats, ADDLEVPW" >> $LOGGFILE
cd $WORKDIR/AddStdLevplats
qmake -project "TARGET=ADDLEVPW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddText, ADDTXTW" >> $LOGGFILE
cd $WORKDIR/AddText
qmake -project "TARGET=ADDTXTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddUser, ADDUSRW" >> $LOGGFILE
cd $WORKDIR/AddUser
qmake -project "TARGET=ADDUSRW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== AddValuta, ADDVALW" >> $LOGGFILE
cd $WORKDIR/AddValuta
qmake -project "TARGET=ADDVALW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** B *****"
echo "===== Balansrapport, BALRPTW" >> $LOGGFILE
cd $WORKDIR/Balansrapport
qmake -project "TARGET=ADDRPTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== BokforStd, BOKFORSW" >> $LOGGFILE
cd $WORKDIR/BokforStd
qmake -project "TARGET=BOKFORSW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Change *****"

echo "===== ChangeArtikel, CHGARW" >> $LOGGFILE
cd $WORKDIR/ChangeArtikel
qmake -project "TARGET=CHGARW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeBar, CHGBARW" >> $LOGGFILE
cd $WORKDIR/ChangeBar
qmake -project "TARGET=CHGBARW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeBetalvillkor, CHGBETVW" >> $LOGGFILE
cd $WORKDIR/ChangeBetalvillkor
qmake -project "TARGET=CHGBETVW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeForetag, BYTFTGW" >> $LOGGFILE
cd $WORKDIR/ChangeForetag
qmake -project "TARGET=BYTFTGW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeFtgData, CHGFTGW" >> $LOGGFILE
cd $WORKDIR/ChangeFtgData
qmake -project "TARGET=CHGFTGW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeKonto, CHGKTOW" >> $LOGGFILE
cd $WORKDIR/ChangeKonto
qmake -project "TARGET=CHGKTOW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeKund, CHGKUW" >> $LOGGFILE
cd $WORKDIR/ChangeKund
qmake -project "TARGET=CHGKUW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeLev, CHGLEVW" >> $LOGGFILE
cd $WORKDIR/ChangeLev
qmake -project "TARGET=CHGLEVW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeLagerstelle, CHGLSW" >> $LOGGFILE
cd $WORKDIR/ChangeLagerstelle
qmake -project "TARGET=CHGLSW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeOrder, CHGORDW" >> $LOGGFILE
cd $WORKDIR/ChangeOrder
qmake -project "TARGET=CHGORDW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeOffert, CHGOFFW" >> $LOGGFILE
cd $WORKDIR/ChangeOffert
qmake -project "TARGET=CHGOFFW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeUser, CHGUSRW" >> $LOGGFILE
cd $WORKDIR/ChangeUser
qmake -project "TARGET=CHGUSRW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChangeValuta, CHGVALW" >> $LOGGFILE
cd $WORKDIR/ChangeValuta
qmake -project "TARGET=CHGVALW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ChgPlocklistaKundorder, PLCHGW" >> $LOGGFILE
cd $WORKDIR/ChgPlocklistaKundorder
qmake -project "TARGET=PLCHGW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== Dagbok, DAGBOKW" >> $LOGGFILE
cd $WORKDIR/Dagbok
qmake -project "TARGET=DAGBOKW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Del *****"

echo "===== DelOffert, DELOFFW" >> $LOGGFILE
cd $WORKDIR/DelOffert
qmake -project "TARGET=DELOFFW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DelLagerstelle, DELLSW" >> $LOGGFILE
cd $WORKDIR/DelLagerstelle
qmake -project "TARGET=DELLSW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DelRights, DELRGTW" >> $LOGGFILE
cd $WORKDIR/DelRights
qmake -project "TARGET=DELRGTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DelText, DELTXTW" >> $LOGGFILE
cd $WORKDIR/DelText
qmake -project "TARGET=DELTXTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DelUser, DELUSRW" >> $LOGGFILE
cd $WORKDIR/DelUser
qmake -project "TARGET=DELUSRW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DelValuta, DELVALW" >> $LOGGFILE
cd $WORKDIR/DelValuta
qmake -project "TARGET=DELVALW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Dsp *****"

echo "===== DspArtikelEkonomidata, DSPAREW" >> $LOGGFILE
cd $WORKDIR/DspArtikelEkonomidata
qmake -project "TARGET=DSPAREW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspArtikelGrunddata, DSPARW" >> $LOGGFILE
cd $WORKDIR/DspArtikelGrunddata
qmake -project "TARGET=DSPARW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspBar, DSPBARW" >> $LOGGFILE
cd $WORKDIR/DspBar
qmake -project "TARGET=DSPBARW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspBestellning, DSPINKW" >> $LOGGFILE
cd $WORKDIR/DspBestellning
qmake -project "TARGET=DSPINKW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspFtgData, DSPFTGW" >> $LOGGFILE
cd $WORKDIR/DspFtgData
qmake -project "TARGET=DSPFTGW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspKonto, DSPKTOW" >> $LOGGFILE
cd $WORKDIR/DspKonto
qmake -project "TARGET=DSPKTOW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspKstalle, DSPKSTW" >> $LOGGFILE
cd $WORKDIR/DspKstalle
qmake -project "TARGET=DSPKSTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspKund, DSPKUW" >> $LOGGFILE
cd $WORKDIR/DspKund
qmake -project "TARGET=DSPKUW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspLev, DSPLEVW" >> $LOGGFILE
cd $WORKDIR/DspLev
qmake -project "TARGET=DSPLEVW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspLagerstelle, DELLSW" >> $LOGGFILE
cd $WORKDIR/DspLagerstelle
qmake -project "TARGET=DSPLSW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspOrder, DSPORDW" >> $LOGGFILE
cd $WORKDIR/DspOrder
qmake -project "TARGET=DSPORDW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspText, DSPTXTW" >> $LOGGFILE
cd $WORKDIR/DspText
qmake -project "TARGET=DSPTXTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspUser, DSPUSRW" >> $LOGGFILE
cd $WORKDIR/DspUser
qmake -project "TARGET=DSPUSR" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== DspValuta, DSPVALW" >> $LOGGFILE
cd $WORKDIR/DspValuta
qmake -project "TARGET=DSPVALW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** H *****"

echo "===== HelpOlfix, OLFIXHLP" >> $LOGGFILE
cd $WORKDIR/HelpOlfix
qmake -project "TARGET=OLFIXHLP" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== HittaKund, SRCHKUW" >> $LOGGFILE
cd $WORKDIR/HittaKund
qmake -project "TARGET=SRCKUW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== Huvudbok, HUVBOKW" >> $LOGGFILE
cd $WORKDIR/Huvudbok
qmake -project "TARGET=HUVBOKW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** K *****"

echo "===== Kontorapport, RPTKTOW" >> $LOGGFILE
cd $WORKDIR/Kontorapport
qmake -project "TARGET=RPTKTOW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Kund *****"

echo "===== KundFaktura, KUFAKTW" >> $LOGGFILE
cd $WORKDIR/KundFaktura
qmake -project "TARGET=KUFAKTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== KundFakturaBetald, KUFAKTBW" >> $LOGGFILE
cd $WORKDIR/KundFakturaBetald
qmake -project "TARGET=KUFAKTBW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== KundReskontra, KURESKW" >> $LOGGFILE
cd $WORKDIR/KundReskontra
qmake -project "TARGET=KURESKW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Leverantör *****"

echo "===== LevFaktAttBetala, ATTBETW" >> $LOGGFILE
cd $WORKDIR/LevFaktAttBetala
qmake -project "TARGET=ATTBETW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== LevFaktura, LEVFAKTW" >> $LOGGFILE
cd $WORKDIR/LevFaktura
qmake -project "TARGET=LEVFAKTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== LevReskontra, LEVRESKW" >> $LOGGFILE
cd $WORKDIR/LevReskontra
qmake -project "TARGET=LEVRESKW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** List *****"

echo "===== ListArtikel, LSTARW" >> $LOGGFILE
cd $WORKDIR/ListArtikel
qmake -project "TARGET=LSTARW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListBar, LSTBARW" >> $LOGGFILE
cd $WORKDIR/ListBar
qmake -project "TARGET=LSTBARW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListBestellningsstock, LSTINKW" >> $LOGGFILE
cd $WORKDIR/ListBestellningsstock
qmake -project "TARGET=LSTINKW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListBetalvillkor, LSTBETVW" >> $LOGGFILE
cd $WORKDIR/ListBetalvillkor
qmake -project "TARGET=LSTBETVW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListForetag, LSTFORW" >> $LOGGFILE
cd $WORKDIR/ListForetag
qmake -project "TARGET=LSTFORW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListForetagsdata, LSTFTGW" >> $LOGGFILE
cd $WORKDIR/ListForetagsdata
qmake -project "TARGET=LSTFTGW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListFunc, LSTFNCW" >> $LOGGFILE
cd $WORKDIR/ListFunc
qmake -project "TARGET=LSTFNCW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListKonto, LSTKTOW" >> $LOGGFILE
cd $WORKDIR/ListKonto
qmake -project "TARGET=LSTKTOW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListKst, LSTKSTW" >> $LOGGFILE
cd $WORKDIR/ListKst
qmake -project "TARGET=LSTKSTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListKund, LSTKUW" >> $LOGGFILE
cd $WORKDIR/ListKund
qmake -project "TARGET=LSTKUW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListKundorder, LSTORDW" >> $LOGGFILE
cd $WORKDIR/ListKundorder
qmake -project "TARGET=LSTORDW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListLev, LSTLEVW" >> $LOGGFILE
cd $WORKDIR/ListLev
qmake -project "TARGET=LSTLEVW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListLevplats, LSTLEVPW" >> $LOGGFILE
cd $WORKDIR/ListLevplats
qmake -project "TARGET=LSTLEVPW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListLevsett, LSTLEVSW" >> $LOGGFILE
cd $WORKDIR/ListLevsett
qmake -project "TARGET=LSTLEVSW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListLevvillkor, LSTLEVVW" >> $LOGGFILE
cd $WORKDIR/ListLevvillkor
qmake -project "TARGET=LSTLEVVW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListProdkod, LSTPKDW" >> $LOGGFILE
cd $WORKDIR/ListProdkod
qmake -project "TARGET=LSTPKDW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListRights, LSTRGTW" >> $LOGGFILE
cd $WORKDIR/ListRights
qmake -project "TARGET=LSTRGTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListTextreg, LSTTXTW" >> $LOGGFILE
cd $WORKDIR/ListTextreg
qmake -project "TARGET=LSTTXTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListUser, LSTUSRW" >> $LOGGFILE
cd $WORKDIR/ListUser
qmake -project "TARGET=LSTUSRW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== ListValuta, LSTVALW" >> $LOGGFILE
cd $WORKDIR/ListValuta
qmake -project "TARGET=LSTVALW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Meny *****"

echo "===== MenyOlfixW, OLFIXW" >> $LOGGFILE
cd $WORKDIR/MenyOlfixW
qmake -project "TARGET=OLFIXW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "***** Prt *****"

echo "===== PrtBestellning, PRTINKW" >> $LOGGFILE
cd $WORKDIR/PrtBestellning
qmake -project "TARGET=PRTINKW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== PrtBestellningKundorder, FSORDW" >> $LOGGFILE
cd $WORKDIR/PrtFoljesedelKundorder
qmake -project "TARGET=FSORDW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== PrtPlocklistaKundorder, PLORDW" >> $LOGGFILE
cd $WORKDIR/PrtPlocklistaKundorder
qmake -project "TARGET=PLORDW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== RapportGen, RPTGENW" >> $LOGGFILE
cd $WORKDIR/RapportGen
qmake -project "TARGET=RPTGENW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== Resultatrapport, RESRPTW" >> $LOGGFILE
cd $WORKDIR/Resultatrapport
qmake -project "TARGET=RESRPTW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== RptSIEfil, RPTSIEW" >> $LOGGFILE
cd $WORKDIR/RptSIEfil
qmake -project "TARGET=RPTSIEW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== Saldolista, SDOLISW" >> $LOGGFILE
cd $WORKDIR/Saldolista
qmake -project "TARGET=SDOLISW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== SoekArtikel, SRCHARW" >> $LOGGFILE
cd $WORKDIR/SoekArtikel
qmake -project "TARGET=SRCARW" "DESTDIR+=$TARGETDIR" >> $LOGGFILE
qmake >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE
make clean >> $LOGGFILE

echo "===== C-program" >> $LOGGFILE
cd $WORKDIR/C
make clean >> $LOGGFILE
make >> $LOGGFILE 2>> $LOGGFILE

date > $LOGGFILE
echo "***** KLART *****"