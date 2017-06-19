#!/bin/bash

# this code should be called by the runDoAnalysis.sh file, which sets 
# METHOD, BINMIN and BINMAX

DOANALYSISPP_FIT=1
DOANALYSISPP_MCSTUDY=0
DOANALYSISPbPb_FIT=0
DOANALYSISPbPb_MCSTUDY=0
DORAA=0

PDFOUTPUTLOCATIONANDNAME="plotFits/crossSection/misc"
PDFOUTPUTLOCATIONANDNAME=$PDFOUTPUTLOCATIONANDNAME"/"$METHOD".pdf"

#LUMIPP=27.748 # paper 20170224, B analysis
#LUMIPP=25.8 # D analysis
LUMIPP=27.4 # D analysis
INPUTMCPP="../test/ntB_pp_MC_"$BINMIN"_"$BINMAX".root"
INPUTDATAPP="../test/ntB_pp_Data_"$BINMIN"_"$BINMAX".root"
#TRGPP="(HLT_DmesonPPTrackingGlobal_Dpt8_v1 || HLT_DmesonPPTrackingGlobal_Dpt15_v1 || HLT_DmesonPPTrackingGlobal_Dpt30_v1 || HLT_DmesonPPTrackingGlobal_Dpt50_v1)"
#TRGPP="(HLT_DmesonPPTrackingGlobal_Dpt8_v1 || HLT_DmesonPPTrackingGlobal_Dpt15_v1 || HLT_DmesonPPTrackingGlobal_Dpt20_v1 || HLT_DmesonPPTrackingGlobal_Dpt30_v1 || HLT_DmesonPPTrackingGlobal_Dpt50_v1)";


#TRGPP="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
#TRGPP="1"
TRGPPMC="1"

# prefilters
CUTPP="abs(PVz)<15 && pBeamScrapingFilter && pPAprimaryVertexFilter && Dmass>5&&Dmass<6 && Dtrk1highPurity && DRestrk1highPurity && DRestrk2highPurity && Dtrk1PtErr/Dtrk1Pt<0.3 && DRestrk1PtErr/DRestrk1Pt<0.3 && DRestrk2PtErr/DRestrk2Pt<0.3 &&  Dtrk1Pt>0.5 && DRestrk1Pt>0.5 && DRestrk2Pt>0.5 && DtktkRespt>8 && abs(DtktkResmass-1.87)<0.03 && Dchi2cl>0.05 && DtktkRes_chi2cl>0.05 && Dalpha<0.2 && DtktkRes_alpha<0.2 && (DsvpvDistance/DsvpvDisErr)>2.0 && (DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.0 && abs(Dtrk1Eta)<1.5 && abs(DRestrk1Eta)<1.5 && abs(DRestrk2Eta)<1.5 && TMath::Abs(Dy)<1."

#cuts for 20-40 ----------------------------------------------------------------
if [ "$BINMIN" = "20" -a "$BINMAX" = "40" ]; then
echo "20-40"
TRGPP="HLT_DmesonPPTrackingGlobal_Dpt15_v1";
# cutsGA
if [ "$METHOD" = "cutsGA" ]; then
CUTPP=$CUTPP" && Dtrk1Pt>1.5119066783466506 && DRestrk1Pt>0.30536377790210678 && DRestrk2Pt>0.36338212403760983 && DtktkRespt>7.8250794441627303 && Dchi2cl>0.051459643814556165 && DtktkRes_chi2cl>0.043374341702374246 && Dalpha<0.19826644414562558 && DtktkRes_alpha<0.20011998802556244 && DsvpvDistance/DsvpvDisErr>3.1977048738596423 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>3.2666225677967122"
fi

# cutsSA
if [ "$METHOD" = "cutsSA" ]; then
CUTPP=$CUTPP" && Dtrk1Pt>1.4844397710905781 && DRestrk1Pt>1.1235527445660458 && DRestrk2Pt>0.47124198653284882 && DtktkRespt>7.9203352686361228 && Dchi2cl>0.069173950728496747 && DtktkRes_chi2cl>0.058931826062455228 && Dalpha<0.15566915489397984 && DtktkRes_alpha<0.19714307317206459 && DsvpvDistance/DsvpvDisErr>3.7061885740403979 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>4.3363138312246523"
fi

### LD
if [ "$METHOD" = "LD" ]; then
  CUTPP=$CUTPP" && LD > "
fi
  
# MLP
if [ "$METHOD" = "MLP" ]; then
  CUTPP=$CUTPP" && MLP >"
fi

# BDT
if [ "$METHOD" = "BDT" ]; then
  CUTPP=$CUTPP" && BDT > .2"
fi
  
# BDTB
if [ "$METHOD" = "BDTB" ]; then
  CUTPP=$CUTPP" && BDTB >  "
fi
fi
#cuts for 40-100 ----------------------------------------------------------------
if [ "$BINMIN" = "40" -a "$BINMAX" = "100" ]; then
echo "40-100"
TRGPP="HLT_DmesonPPTrackingGlobal_Dpt30_v1";
# cutsGA
if [ "$METHOD" = "cutsGA" ]; then
CUTPP=$CUTPP" && Dtrk1Pt>3.1283988174549324 && DRestrk1Pt>0.87633860909130834 && DRestrk2Pt>0.49219084823940806 && DtktkRespt>7.4482612362135594 && Dchi2cl>0.042252454543442439 && DtktkRes_chi2cl>0.055413157979800419 && Dalpha<0.075990655431829757 && DtktkRes_alpha<0.1960009217583123 && DsvpvDistance/DsvpvDisErr>2.9228773605879357 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>2.9237382468189037"

fi

# cutsSA
if [ "$METHOD" = "cutsSA" ]; then
CUTPP=$CUTPP" && Dtrk1Pt>2.2832389864149776 && DRestrk1Pt>1.1785505053073921 && DRestrk2Pt>0.11226191496246736 && DtktkRespt>7.9509242348913354 && Dchi2cl>0.048233308827930033 && DtktkRes_chi2cl>0.047793650985811807 && Dalpha<0.12148664710213197 && DtktkRes_alpha<0.18348806753328883 && DsvpvDistance/DsvpvDisErr>2.8109177447134006 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>3.7490936393580707"

fi

### LD
if [ "$METHOD" = "LD" ]; then
  CUTPP=$CUTPP" && LD > "
fi
  
# MLP
if [ "$METHOD" = "MLP" ]; then
  CUTPP=$CUTPP" && MLP >"
fi

# BDT
if [ "$METHOD" = "BDT" ]; then
  CUTPP=$CUTPP" && BDT > .36"
fi
  
# BDTB
if [ "$METHOD" = "BDTB" ]; then
  CUTPP=$CUTPP" && BDTB >  "
fi
fi
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

#LUMIPbPb=13.1983052423 #paper 20170227, B analysis
#LUMIPbPb=15.5665   # from brilcalc, D analysis
LUMIPbPb=15.5020   # from brilcalc, D analysis
INPUTDATAPbPb="../Skim/Skim_ntD_EvtBase_20170323_DfinderData_PbPb_20170123_BtoD0Pi_Dpt10Dsvpv3Dalpha0p14Dchi20p05Dmass56Tkpt1Ressvpv3.root"
INPUTMCPbPb="../Skim/Skim_ntD_EvtBase_20170130_DfinderMC_PbPb_20170123_BtoD0Pi_dPt0tkPt2p5_Pythia8_nonprompt_Hydjet_MB_Dpt5tkPt2p5Decay3tktkResDecay3Skim_pthatweight.root"
#TRGPbPb="(HLT_HIDmesonHITrackingGlobal_Dpt20_v1 || HLT_HIDmesonHITrackingGlobal_Dpt40_v1 || HLT_HIDmesonHITrackingGlobal_Dpt60_v1)"
TRGPbPb="1"
TRGPbPbMC="1"
CUTPbPb="abs(PVz)<15 && pclusterCompatibilityFilter && pprimaryVertexFilter && phfCoincFilter3 && TMath::Abs(Dy)<2.4 && Dmass>5&&Dmass<6 && abs(Dtrk1Eta)<1.0 && Dtrk1Pt>0.5 && Dchi2cl>0.05 && DtktkRes_chi2cl>0.05 && Dalpha < 0.14 && (Dpt>10 && (DsvpvDistance/DsvpvDisErr)>3) && Dtrk1Pt > 2.5 && DRestrk1Pt > 2.5 && DRestrk2Pt > 2.5 && fabs(DtktkResmass-1.87) < 0.03 && DtktkRes_alpha < 0.1 && Dalpha < 0.14 && ((Dpt < 30 && Dalpha < 0.08 && DsvpvDistance/DsvpvDisErr > 5.) || (Dpt > 30))"
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
