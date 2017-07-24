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
TString selgen = "TMath::Abs(Gy)<2.4 && abs(GpdgId)==521 && (GisSignal==13 || GisSignal==14)";

///////PbPb section
TString inputSname_PP = "/data/bmeson2017/MC/loop_BsMC_PbPb_pthat10.root";
TString inputBname_PP = "/data/wangj/Data2015/Bntuple/PbPb/Bntuple_BfinderData_PbPb_20160406_bPt5jpsiPt0tkPt0p8_BpB0BsX_skimhlt.root";

TString mycut_PP="TMath::Abs(By)<2.4&&Bmass>5.&&Bmass<6.&&abs(Bmumumass-3.096916)<0.15&&Bchi2cl>0.1&&(Bd0/Bd0Err)>5.&&TMath::Abs(Btktkmass-1.019455)<0.05&&Blxy>0.1";//&&Btrk1Pt>1.5&&Btrk2Pt>1.5&&cos(Bdtheta)>0.8&&Bmu1pt>1.5&&Bmu2pt>1.5&&Bpt>15.0";

TString mycuts_PP = Form("%s&& Bgen==23333",mycut_PP.Data());
TString mycutb_PP = Form("%s&& abs(Bmass-5.279)>0.2&&abs(Bmass-5.279)<0.3",mycut_PP.Data());
TString mycutg_PP = "abs(Gy)<2.4&&GisSignal==6&&abs(GpdgId)==531";

double lum_pp=1;//should never be used
double lum_PP=34.6;//HP

//////////pp section
TString inputSname_pp = "/data/HeavyFlavourRun2/TMVA_Luke/Dntuple_20170428_pp_BuToD0Pi_20151212_v2_DfinderMC_pp_20170423_BtoD0Pi_Dpt5Dy1Tketa2_pthatweight.root";
TString inputBname_pp = "/data/HeavyFlavourRun2/TMVA_Luke/Dntuple_20170428_HeavyFlavor_DfinderData_pp_20170423_BtoD0Pi_Dpt10Dy1Alpha0p2Svpv2Tketa1p5EvtSkim.root";
TString myTrg_pp = "(HLT_DmesonPPTrackingGlobal_Dpt8_v1 || HLT_DmesonPPTrackingGlobal_Dpt15_v1 || HLT_DmesonPPTrackingGlobal_Dpt20_v1 || HLT_DmesonPPTrackingGlobal_Dpt30_v1 || HLT_DmesonPPTrackingGlobal_Dpt50_v1)";

// cut we decided after eta anlysis
//TString mycut_pp = "abs(PVz)<15 && pBeamScrapingFilter && pPAprimaryVertexFilter && Dmass>5&&Dmass<6 && Dtrk1highPurity && DRestrk1highPurity && DRestrk2highPurity && Dtrk1PtErr/Dtrk1Pt<0.3 && DRestrk1PtErr/DRestrk1Pt<0.3 && DRestrk2PtErr/DRestrk2Pt<0.3 &&  Dtrk1Pt>0.5 && DRestrk1Pt>0.5 && DRestrk2Pt>0.5 && DtktkRespt>8 && abs(DtktkResmass-1.87)<0.03 && Dchi2cl>0.05 && DtktkRes_chi2cl>0.05 && Dalpha<0.2 && DtktkRes_alpha<0.2 && (DsvpvDistance/DsvpvDisErr)>2.0 && (DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.0 && abs(Dtrk1Eta)<1.5 && abs(DRestrk1Eta)<1.5 && abs(DRestrk2Eta)<1.5 && TMath::Abs(Dy)<1.0"; 

//original cut for new macro
TString mycut_pp = "abs(PVz)<15 && pBeamScrapingFilter && pPAprimaryVertexFilter && TMath::Abs(Dy)<1.0 && Dmass>5&&Dmass<6 && Dtrk1highPurity && DRestrk1highPurity && DRestrk2highPurity && Dtrk1PtErr/Dtrk1Pt<0.3 && DRestrk1PtErr/DRestrk1Pt<0.3 && DRestrk2PtErr/DRestrk2Pt<0.3 && abs(Dtrk1Eta)<1.0 && abs(DRestrk1Eta)<1.0 && abs(DRestrk2Eta)<1.0 && Dtrk1Pt>0.5 && DRestrk1Pt>0.5 && DRestrk2Pt>0.5 && DtktkRespt>0 && abs(DtktkResmass-1.87)<0.03 && Dchi2cl>0.05 && DtktkRes_chi2cl>0.05 && Dalpha<3.2 && DtktkRes_alpha<3.2 && (DsvpvDistance/DsvpvDisErr)>0.0 && (DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>0.0"; 

// remove all after Dtrk1 
//"((DtktkRes_lxyBS/DtktkRes_lxyBSErr)>2.5";
TString DAnacut_pp = "DtktkRes_alpha<0.12&&((DtktkRespt>2&&DtktkRespt<4&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>5.86&&DtktkRes_alpha>0.224)||(DtktkRespt>4&&DtktkRespt<5&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>5.46&&DtktkRes_alpha>0.196)||(DtktkRespt>5&&DtktkRespt<6&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.86&&DtktkRes_alpha>0.170)||(DtktkRespt>6&&DtktkRespt<8&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.54&&DtktkRes_alpha>0.125)||(DtktkRespt>8&&DtktkRespt<10&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.42&&DtktkRes_alpha>0.091)||(DtktkRespt>10&&DtktkRespt<15&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>4.06&&DtktkRes_alpha>0.069)||(DtktkRespt>15&&DtktkRespt<20&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.71&&DtktkRes_alpha>0.056)||(DtktkRespt>20&&DtktkRespt<25&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>3.25&&DtktkRes_alpha>0.054)||(DtktkRespt>25&&(DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.97&&DtktkRes_alpha>0.050)))";
TString mycuts_pp = Form("%s &&Dgen==23333",mycut_pp.Data());
//TString mycutb_pp = Form("%s &&abs(Dmass-5.279)>0.2&&abs(Dmass-5.279)<0.3",mycut_pp.Data());
TString mycutb_pp = Form("%s &&(Dmass-5.279)>0.2&&(Dmass-5.279)<0.5&& %s",mycut_pp.Data(), myTrg_pp.Data());
TString mycutg_pp = "abs(Gy)<1.0&&abs(GpdgId)==521&&(GisSignal==13 || GisSignal==14)";

