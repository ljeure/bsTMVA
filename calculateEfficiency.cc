/*
 * calculateEfficiency.cc
 * Luke Eure
 * 7 June 2017
 * a simple macro to calculate the adjusted efficiency of B production to be
 * used in cross section calculations. Run the macro from the containing
 * directory by doing "root calculateEfficiency.cc"
 */

void calculateEfficiency() { 
  
  // import the monte carlo data
  TFile *f = TFile::Open("/data/HeavyFlavourRun2/TMVA_Luke/Dntuple_20170428_pp_BuToD0Pi_20151212_v2_DfinderMC_pp_20170423_BtoD0Pi_Dpt5Dy1Tketa2_pthatweight.root");
  TTree* tree = (TTree*) f->Get("ntBptoD0pi");
  TTree* genTree = (TTree*) f->Get("ntGen");
  
  // the prefilter used in the anlysis with non-numerical expressions removed
  // (the non-numerical expressions are used for noise-reduction in data and
  //  are unnecessary for monte carlo data)
  TCut prefilter = "abs(PVz)<15 && TMath::Abs(Dy)<1. && Dmass>5&&Dmass<6 && Dtrk1PtErr/Dtrk1Pt<0.3 && DRestrk1PtErr/DRestrk1Pt<0.3 && DRestrk2PtErr/DRestrk2Pt<0.3 &&  Dtrk1Pt>0.5 && DRestrk1Pt>0.5 && DRestrk2Pt>0.5 && DtktkRespt>8 && abs(DtktkResmass-1.87)<0.03 && Dchi2cl>0.05 && DtktkRes_chi2cl>0.05 && Dalpha<0.2 && DtktkRes_alpha<0.2 && (DsvpvDistance/DsvpvDisErr)>2.0 && (DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.0 && abs(Dtrk1Eta)<1.5 && abs(DRestrk1Eta)<1.5 && abs(DRestrk2Eta)<1.5";

  // cuts for the respectice energy ranges came from TMVA's cutsGA method
  TCut cut_10_15 = "Dpt>10 && Dpt<15 && Dtrk1Pt>2.3170705656871102 && DRestrk1Pt>0.60080866903897268 && DRestrk2Pt>0.34514955119647112 && DtktkRespt>8.1132923836150503 && Dchi2cl>0.057988272342992454 && DtktkRes_chi2cl>0.053023889609986281 && Dalpha<0.16350691515542917 && DtktkRes_alpha<0.19839796655225722 && DsvpvDistance/DsvpvDisErr>2.7681832761976963 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>2.415025544981896";
  TCut cut_15_20 = "Dpt>15 && Dpt<20 && Dtrk1Pt>1.1769508323267215 && DRestrk1Pt>0.4967023525503147 && DRestrk2Pt>0.39046239070969135 && DtktkRespt>7.9533424123326384 && Dchi2cl>0.043858958123795373 && DtktkRes_chi2cl>0.043151381204515879 && Dalpha<0.081597806070864198 && DtktkRes_alpha<0.20103730287740149 && DsvpvDistance/DsvpvDisErr>2.6724468018584711 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>2.3168995223678879";
  TCut cut_20_40 = "Dpt>20 && Dpt<40 && Dtrk1Pt>1.5119066783466506 && DRestrk1Pt>0.30536377790210678 && DRestrk2Pt>0.36338212403760983 && DtktkRespt>7.8250794441627303 && Dchi2cl>0.051459643814556165 && DtktkRes_chi2cl>0.043374341702374246 && Dalpha<0.19826644414562558 && DtktkRes_alpha<0.20011998802556244 && DsvpvDistance/DsvpvDisErr>3.1977048738596423 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>3.2666225677967122";
  TCut cut_40_100 = "Dpt>40 && Dpt<100 && Dtrk1Pt>3.1283988174549324 && DRestrk1Pt>0.87633860909130834 && DRestrk2Pt>0.49219084823940806 && DtktkRespt>7.4482612362135594 && Dchi2cl>0.042252454543442439 && DtktkRes_chi2cl>0.055413157979800419 && Dalpha<0.075990655431829757 && DtktkRes_alpha<0.1960009217583123 && DsvpvDistance/DsvpvDisErr>2.9228773605879357 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>2.9237382468189037";

  TCut cCut_40_100 = " Dtrk1Pt>0.5 && DRestrk1Pt>0.5 && DRestrk2Pt>0.5 && Dtrk1Pt>3.1283988174549324 && DRestrk1Pt>0.87633860909130834 && DRestrk2Pt>0.49219084823940806 && abs(Dtrk1Eta)<1.5 && abs(DRestrk1Eta)<1.5 && abs(DRestrk2Eta)<1.5";
  TCut dCut_40_100 ="Dtrk1PtErr/Dtrk1Pt<0.3 && DRestrk1PtErr/DRestrk1Pt<0.3 && DRestrk2PtErr/DRestrk2Pt<0.3 &&  DtktkRespt>8 && abs(DtktkResmass-1.87)<0.03 && Dchi2cl>0.05 && DtktkRes_chi2cl>0.05 && Dalpha<0.2 && DtktkRes_alpha<0.2 && (DsvpvDistance/DsvpvDisErr)>2.0 && (DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.0";

  // total cuts for numerator
  TCut aCuts = (cut_20_40 || cut_40_100) && prefilter && "Dgen==23333";
  TCut bCuts = "TMath::Abs(Gy)<1. && (GisSignal == 1 || GisSignal == 2)";
  TCut cCuts = cCut_40_100 && "TMath::Abs(Gy)<1. && (GisSignal == 1 || GisSignal == 2)";
  TCut dCuts = dCut_40_100 && "(GisSignal == 1 || GisSignal == 2)";

  // apply cuts and creat TEventLists in order to get the number of candidates
  tree->Draw(">>elista", aCuts);
  TEventList *elista = (TEventList*)gDirectory->Get("elista");
  Int_t a = elista->GetN();  // number of events to pass cuts

  genTree->Draw(">>elistc", cCuts);
  TEventList *elistc = (TEventList*)gDirectory->Get("elistc");
  Int_t c = elistc->GetN();  // number of events to pass cuts
  genTree->Draw(">>elistb", bCuts);
  TEventList *elistb = (TEventList*)gDirectory->Get("elistb");
  Int_t b = elistb->GetN();  // number of events to pass cuts


  genTree->Draw(">>elistd", dCuts);
  TEventList *elistd = (TEventList*)gDirectory->Get("elistd");
  Int_t d = elistd->GetN();  // number of events to pass cuts

  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;
  std::cout << "c = " << c << std::endl;
  std::cout << "d = " << d << std::endl;

  std::cout << "total efficiency:       " << (double) a / b << std::endl;
  std::cout << "acceptance efficiency component 1: " << (double) c / b << std::endl;
  std::cout << "recontruction efficiency component 2: " << (double) d / c << std::endl;
  std::cout << "d meson selection efficiency component 3: " << (double) a / d << std::endl;
}



// do all the same analysis for 10-15 and 15020 GeV
// after this we can try splitting the efficiency  into multple parts :
//    1. (gen with cuts on rapidity, and signle track cuts on eta and pt) / gend with rapidity cuts  [c / b]
//    2. (D reconstructed and reconstructed track selection with cuts that refer to reconstructed tracks (i.e. tracks that refer to the quality of the tracks)) / numerator of 1 [d / c]
//    3. numerator of original efficiency / numerator of 2  [ a / d]
