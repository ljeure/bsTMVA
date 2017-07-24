#!/bin/bash

# this code should be called by the runDoAnalysis.sh file, which sets 
# METHOD, BINMIN and BINMAX

DOANALYSISPP_FIT=0
DOANALYSISPP_MCSTUDY=0
DOANALYSISPbPb_FIT=1
DOANALYSISPbPb_MCSTUDY=0
DORAA=0

PDFOUTPUTLOCATIONANDNAME="plotFits/$BINMIN-$BINMAX"
PDFOUTPUTLOCATIONANDNAME=$PDFOUTPUTLOCATIONANDNAME"/"$METHOD".pdf"

LUMIPP=34.6 # B analysis
INPUTMCPP="../test/ntB_pp_MC_"$BINMIN"_"$BINMAX".root"
INPUTDATAPP="../test/ntB_pp_Data_"$BINMIN"_"$BINMAX".root"
TRGPP="(HLT_DmesonPPTrackingGlobal_Dpt3_v1)";

TRGPPMC="(HLT_DmesonPPTrackingGlobal_Dpt3_v1)";
#TRGPPMC="1"

# PbPb cut from original Bs presentation
#CUTPP="TMath::Abs(By)<2.4&&abs(Bmumumass-3.096916)<0.15&&Bmass>5.&&Bmass<6.&&Btrk1Pt>1.5&&Btrk2Pt>1.5&&Bchi2cl>0.1&&(Bd0/Bd0Err)>5.&&cos(Bdtheta)>0.8&&Bmu1pt>1.5&&Bmu2pt>1.5&&Bpt>15.0&&TMath::Abs(Btktkmass-1.019455)<0.05&&Blxy>0.1"

CUTPP="&&MLP>6"

SELGENPP="TMath::Abs(Gy)<2.4 && abs(GpdgId)==521 && (GisSignal==13 || GisSignal==14)"
SELGENPPACCPP="TMath::Abs(Gy)<2.4 && abs(GpdgId)==521 && (GisSignal==13 || GisSignal==14) && Gtk1pt>1.0 && TMath::Abs(Gtk1eta)<2.4"
RECOONLYPP=$CUTPP
ISMCPP=0
ISDOWEIGHTPP=0
LABELPP="pp"
OUTPUTFILEPP="ROOTfiles/hPtSpectrumBplusPP.root"
OUTPUTFILEMCSTUDYPP="ROOTfiles/MCstudiesPP.root"
NPFIT_PP="3.12764e1*Gaus(x,5.33166,3.64663e-2)*(x<5.33166)+(x>=5.33166)*3.12764e1*Gaus(x,5.33166,1.5204e-1)+2.11124e2*TMath::Erf(-(x-5.14397)/6.43194e-2) + 2.11124e2"

if [ $DOANALYSISPP_FIT -eq 1 ]; then
  g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe
  ./fitB.exe 0 "$INPUTDATAPP"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP" "$NPFIT_PP" 0 0 0 "$PDFOUTPUTLOCATIONANDNAME" 
  rm fitB.exe
fi

if [ $DOANALYSISPP_MCSTUDY -eq 1 ]; then
  g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe
  ./MCefficiency.exe  0 "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP&&$TRGPPMC"  "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$ISDOWEIGHTPP"
  rm MCefficiency.exe
fi

LUMIPbPb=34.6   #B analysis

INPUTMCPbPb="../test/ntB_PbPb_MC_"$BINMIN"_"$BINMAX".root"
INPUTDATAPbPb="../test/ntB_PbPb_Data_"$BINMIN"_"$BINMAX".root"

TRGPbPbMC="HLT_HIL1DoubleMu0_v1"
TRGPbPb="HLT_HIL1DoubleMu0_v1"

CUTPbPb="BDT>-.8"

SELGENPbPb="TMath::Abs(Gy)<2.4 && abs(GpdgId)==521 && (GisSignal==13 || GisSignal==14)"
SELGENPbPbACCPbPb="TMath::Abs(Gy)<2.4 && abs(GpdgId)==521 && (GisSignal==13 || GisSignal==14) && Gtk1pt>2.5 && TMath::Abs(Gtk1eta)<2.4"
RECOONLYPbPb=$CUTPbPb
ISMCPbPb=0
ISDOWEIGHTPbPb=1
LABELPbPb="PbPb"
OUTPUTFILEPbPb="ROOTfiles/hPtSpectrumBplusPbPb.root"
OUTPUTFILEMCSTUDYPbPb="ROOTfiles/MCstudiesPbPb.root"

NPFIT_PbPb="3.39711e1*Gaus(x,5.35002e0,3.87952e-2)*(x<5.35002e0)+(x>=5.35002e0)*3.39711e1*Gaus(x,5.35002e0,1.14232e-1)+2.16376e2*TMath::Erf(-(x-5.14189)/8.66243e-2) + 2.16376e2"
CENTPbPbMIN=0
CENTPbPbMAX=100

if [ $DOANALYSISPbPb_FIT -eq 1 ]; then
  g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe
  ./fitB.exe 1 "$INPUTDATAPbPb"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
  rm fitB.exe
fi

if [ $DOANALYSISPbPb_MCSTUDY -eq 1 ]; then
  g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe
  ./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
  rm MCefficiency.exe
fi


OUTPUTFILERAA="ROOTfiles/outputRAA.root"
if [ $DORAA -eq 1 ]; then
  g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe
  ./NuclearModificationFactor.exe "$OUTPUTFILEPP" "$OUTPUTFILEPbPb" "$OUTPUTFILEMCSTUDYPP" "$OUTPUTFILEMCSTUDYPbPb" "$LABELPbPb" "$OUTPUTFILERAA" 0 "$LUMIPP" "$LUMIPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
  rm NuclearModificationFactor.exe
fi
