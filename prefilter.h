bool isPbPb;
float ptmin;
float ptmax;
double luminosity;

TString inputSname;
TString inputBname;
TString mycut;
TString mycuts;
TString mycutb;
TString mycutg;
TString colsyst;
TString MVAtype;
TString npfile;
TString selgen = "TMath::Abs(Gy)<1.0 && abs(GpdgId)==521 && (GisSignal==13 || GisSignal==14)";

//////////pp section
TString inputSname_pp = "/data/HeavyFlavourRun2/TMVA_Luke/Dntuple_20170428_pp_BuToD0Pi_20151212_v2_DfinderMC_pp_20170423_BtoD0Pi_Dpt5Dy1Tketa2_pthatweight.root";
TString inputBname_pp = "/data/HeavyFlavourRun2/TMVA_Luke/Dntuple_20170428_HeavyFlavor_DfinderData_pp_20170423_BtoD0Pi_Dpt10Dy1Alpha0p2Svpv2Tketa1p5EvtSkim.root";
//TString myTrg_pp = "(HLT_DmesonPPTrackingGlobal_Dpt8_v1 || HLT_DmesonPPTrackingGlobal_Dpt15_v1 || HLT_DmesonPPTrackingGlobal_Dpt30_v1 || HLT_DmesonPPTrackingGlobal_Dpt50_v1)";
TString myTrg_pp = "(HLT_DmesonPPTrackingGlobal_Dpt8_v1 || HLT_DmesonPPTrackingGlobal_Dpt15_v1 || HLT_DmesonPPTrackingGlobal_Dpt20_v1 || HLT_DmesonPPTrackingGlobal_Dpt30_v1 || HLT_DmesonPPTrackingGlobal_Dpt50_v1)";
//TString myTrg_pp = "(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)";

// cut we decided after eta anlysis
TString mycut_pp = "abs(PVz)<15 && pBeamScrapingFilter && pPAprimaryVertexFilter && Dmass>5&&Dmass<6 && Dtrk1highPurity && DRestrk1highPurity && DRestrk2highPurity && Dtrk1PtErr/Dtrk1Pt<0.3 && DRestrk1PtErr/DRestrk1Pt<0.3 && DRestrk2PtErr/DRestrk2Pt<0.3 &&  Dtrk1Pt>0.5 && DRestrk1Pt>0.5 && DRestrk2Pt>0.5 && DtktkRespt>8 && abs(DtktkResmass-1.87)<0.03 && Dchi2cl>0.05 && DtktkRes_chi2cl>0.05 && Dalpha<0.2 && DtktkRes_alpha<0.2 && (DsvpvDistance/DsvpvDisErr)>2.0 && (DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.0 && abs(Dtrk1Eta)<1.5 && abs(DRestrk1Eta)<1.5 && abs(DRestrk2Eta)<1.5 && TMath::Abs(Dy)<1.0"; 
// remove all after Dtrk1 
//"((DtktkRes_lxyBS/DtktkRes_lxyBSErr)>2.5";
TString DAnacut_pp = "DtktkRes_alpha<0.12&&((DtktkRespt>2&&DtktkRespt<4&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>5.86&&DtktkRes_alpha>0.224)||(DtktkRespt>4&&DtktkRespt<5&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>5.46&&DtktkRes_alpha>0.196)||(DtktkRespt>5&&DtktkRespt<6&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.86&&DtktkRes_alpha>0.170)||(DtktkRespt>6&&DtktkRespt<8&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.54&&DtktkRes_alpha>0.125)||(DtktkRespt>8&&DtktkRespt<10&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.42&&DtktkRes_alpha>0.091)||(DtktkRespt>10&&DtktkRespt<15&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.06&&DtktkRes_alpha>0.069)||(DtktkRespt>15&&DtktkRespt<20&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.71&&DtktkRes_alpha>0.056)||(DtktkRespt>20&&DtktkRespt<25&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.25&&DtktkRes_alpha>0.054)||(DtktkRespt>25&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.97&&DtktkRes_alpha>0.050)))";
TString mycuts_pp = Form("%s &&Dgen==23333",mycut_pp.Data());
//TString mycutb_pp = Form("%s &&abs(Dmass-5.279)>0.2&&abs(Dmass-5.279)<0.3",mycut_pp.Data());
TString mycutb_pp = Form("%s &&(Dmass-5.279)>0.2&&(Dmass-5.279)<0.5&& %s",mycut_pp.Data(), myTrg_pp.Data());
TString mycutg_pp = "abs(Gy)<1.0&&abs(GpdgId)==521&&(GisSignal==13 || GisSignal==14)";

///////PbPb section
TString inputSname_PP = "/data/wangj/TutorialsSamples/tmvaBntupleRunII/Bntuple20160816_Bpt7svpv5p5Bpt10svpv3p5_BfinderMC_PbPb_Pythia8_BuToJpsiK_Bpt0_Pthat5_TuneCUEP8M1_20160816_bPt5jpsiPt0tkPt0p8_Bp.root";
TString inputBname_PP = "/data/wangj/TutorialsSamples/tmvaBntupleRunII/Bntuple20160816_Bpt7svpv5p5Bpt10svpv3p5_BfinderData_PbPb_20160816_bPt5jpsiPt0tkPt0p8_Bp.root";
TString mycut_PP="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&abs(PVz)<15&&TMath::Abs(By)<2.4&&TMath::Abs(Bmumumass-3.096916)<0.15&&Dmass>5&&Dmass<6&&((abs(Bmu1eta)<1.2 && Bmu1pt>3.5) || (abs(Bmu1eta)>1.2 && abs(Bmu1eta)<2.1 && Bmu1pt>(5.77-1.8*abs(Bmu1eta))) || (abs(Bmu1eta)>2.1 && abs(Bmu1eta)<2.4 && Bmu1pt>1.8)) && ((abs(Bmu2eta)<1.2 && Bmu2pt>3.5) || (abs(Bmu2eta)>1.2 && abs(Bmu2eta)<2.1 && Bmu2pt>(5.77-1.8*abs(Bmu2eta))) || (abs(Bmu2eta)>2.1 && abs(Bmu2eta)<2.4 && Bmu2pt>1.8)) && Bmu1TMOneStationTight && Bmu2TMOneStationTight && Bmu1InPixelLayer > 0 && (Bmu1InPixelLayer+Bmu1InStripLayer) > 5 && Bmu2InPixelLayer > 0 && (Bmu2InPixelLayer+Bmu2InStripLayer) > 5 && Bmu1dxyPV< 0.3 && Bmu2dxyPV< 0.3 && Bmu1dzPV<20 && Bmu2dzPV<20 && Bmu1isGlobalMuon && Bmu2isGlobalMuon && Bmu1TrgMatchFilterE>0 && Bmu2TrgMatchFilterE>0 && Btrk1highPurity && abs(Btrk1Eta)<2.4 && Btrk1Pt>0.8 && Bchi2cl>0.005 && ((Bpt<10 && (BsvpvDistance/BsvpvDisErr)>5.5) || (Bpt>10 && (BsvpvDistance/BsvpvDisErr)>3.5))";
TString mycuts_PP = Form("%s&& Dgen==23333",mycut_PP.Data()); 
TString mycutb_PP = Form("%s&& abs(Dmass-5.279)>0.2&&abs(Dmass-5.279)<0.3",mycut_PP.Data()); 
TString mycutg_PP = "abs(Gy)<2.4&&abs(GpdgId)==521&&GisSignal==1";

// NP FILES //
//TString NPinputMC_PP="/data/HeavyFlavourRun2/MC2015/Bntuple/PbPb/Bntuple20160618_Pythia8_BJpsiMM_ptJpsi_all_Hydjet_MB.root";
//TString NPcut_PP="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&abs(PVz)<15&&TMath::Abs(By)<2.4&&TMath::Abs(Bmumumass-3.096916)<0.15&&Dmass>5&&Dmass<6&&((abs(Bmu1eta)<1.2 && Bmu1pt>3.5) || (abs(Bmu1eta)>1.2 && abs(Bmu1eta)<2.1 && Bmu1pt>(5.77-1.8*abs(Bmu1eta))) || (abs(Bmu1eta)>2.1 && abs(Bmu1eta)<2.4 && Bmu1pt>1.8)) && ((abs(Bmu2eta)<1.2 && Bmu2pt>3.5) || (abs(Bmu2eta)>1.2 && abs(Bmu2eta)<2.1 && Bmu2pt>(5.77-1.8*abs(Bmu2eta))) || (abs(Bmu2eta)>2.1 && abs(Bmu2eta)<2.4 && Bmu2pt>1.8)) && Bmu1TMOneStationTight && Bmu2TMOneStationTight && Bmu1InPixelLayer > 0 && (Bmu1InPixelLayer+Bmu1InStripLayer) > 5 && Bmu2InPixelLayer > 0 && (Bmu2InPixelLayer+Bmu2InStripLayer) > 5 && Bmu1dxyPV< 0.3 && Bmu2dxyPV< 0.3 && Bmu1dzPV<20 && Bmu2dzPV<20 && Bmu1isGlobalMuon && Bmu2isGlobalMuon && ( ((BsvpvDistance/BsvpvDisErr)>6. && Bmumupt>3 && Btrk1Pt>1. && Bpt > 10 && Bpt < 15 && abs(By) < 2.4 && Bchi2cl > 0.2 && cos(Bdtheta) > 0.2 && Btrk1highPurity && abs(Btrk1Eta)<2.4) || ((BsvpvDistance/BsvpvDisErr)>5. && Bmumupt>3 && Btrk1Pt>1.5 && Bpt > 15 && Bpt < 20 && abs(By) < 2.4 && Bchi2cl > 0.005 && cos(Bdtheta) > 0.2 && Btrk1highPurity && abs(Btrk1Eta)<2.4) || ((BsvpvDistance/BsvpvDisErr)>4. && Bmumupt>3 && Btrk1Pt>1.5 && Bpt > 20 && Bpt < 50 && abs(By) < 2.4 && Bchi2cl > 0.005 && cos(Bdtheta) > 0.2 && Btrk1highPurity && abs(Btrk1Eta)<2.4) || ((BsvpvDistance/BsvpvDisErr)>4. && Bmumupt>3 && Btrk1Pt>1.5 && Bpt > 50 && Bpt < 100 && abs(By) < 2.4 && Bchi2cl > 0.005 && cos(Bdtheta) > 0.2 && Btrk1highPurity && abs(Btrk1Eta)<2.4))&&Dgen!=23333";
//TString NPout_PP="../BntupleRunII/CrossSection/ROOTfiles/NPFitPbPb.root";
//
//TString NPinputMC_pp="/data/HeavyFlavourRun2/MC2015/Bntuple/pp/Bntuple20160618_BJpsiMM_5p02TeV_TuneCUETP8M1.root";
//TString NPcut_pp ="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&TMath::Abs(By)<2.4&&TMath::Abs(Bmumumass-3.096916)<0.15&&Dmass>5&&Dmass<6&& ((abs(Bmu1eta)<1.2 && Bmu1pt>3.5) || (abs(Bmu1eta)>1.2 && abs(Bmu1eta)<2.1 && Bmu1pt>(5.77-1.8*abs(Bmu1eta))) || (abs(Bmu1eta)>2.1 && abs(Bmu1eta)<2.4 && Bmu1pt>1.8)) && ((abs(Bmu2eta)<1.2 && Bmu2pt>3.5) || (abs(Bmu2eta)>1.2 && abs(Bmu2eta)<2.1 && Bmu2pt>(5.77-1.8*abs(Bmu2eta))) || (abs(Bmu2eta)>2.1 && abs(Bmu2eta)<2.4 && Bmu2pt>1.8)) && Bmu1TMOneStationTight && Bmu2TMOneStationTight && Bmu1InPixelLayer > 0 && (Bmu1InPixelLayer+Bmu1InStripLayer) > 5 && Bmu2InPixelLayer > 0 && (Bmu2InPixelLayer+Bmu2InStripLayer) > 5 && Bmu1dxyPV< 0.3 && Bmu2dxyPV< 0.3 && Bmu1dzPV<20 && Bmu2dzPV<20 && Bmu1isGlobalMuon && Bmu2isGlobalMuon && Btrk1Pt>1. && abs(By) < 2.4 && Bchi2cl > 0.005 && Btrk1highPurity && abs(Btrk1Eta)<2.4 && cos(Bdtheta) > 0.2 && (BsvpvDistance/BsvpvDisErr)>4.&&Dgen!=23333";
//TString NPout_pp="../BntupleRunII/CrossSection/ROOTfiles/NPFitPP.root";

//double lum_PP=1.6419125;//MB
//double lum_pp=0.0381639;//MB
double lum_PP=15.5020+4.63386;//HP
double lum_pp=27.4;//HF
