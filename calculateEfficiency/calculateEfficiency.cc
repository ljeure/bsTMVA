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

  // reconstructed mc data
  TTree* tree = (TTree*) f->Get("ntBptoD0pi");

  // generated mc data
  TTree* genTree = (TTree*) f->Get("ntGen");
  
  // the prefilter used in the anlysis with non-numerical expressions removed
  // (the non-numerical expressions are used for noise-reduction in data and
  //  are unnecessary for monte carlo data)
  TCut prefilter = "abs(PVz)<15 && TMath::Abs(Dy)<1. && Dmass>5&&Dmass<6 && Dtrk1PtErr/Dtrk1Pt<0.3 && DRestrk1PtErr/DRestrk1Pt<0.3 && DRestrk2PtErr/DRestrk2Pt<0.3 && Dtrk1Pt>0.5 && DRestrk1Pt>0.5 && DRestrk2Pt>0.5 && DtktkRespt>8 && abs(DtktkResmass-1.87)<0.03 && Dchi2cl>0.05 && DtktkRes_chi2cl>0.05 && Dalpha<0.2 && DtktkRes_alpha<0.2 && (DsvpvDistance/DsvpvDisErr)>2.0 && (DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.0 && abs(Dtrk1Eta)<1.5 && abs(DRestrk1Eta)<1.5 && abs(DRestrk2Eta)<1.5";

  // cuts for the 20-40GeV range. Cuts were optimised using came from TMVA's 
  // cutsGA method. the aCut cuts are all the cuts optimized to extract signal.
  // the cCut cuts are the cuts on just momentum and eta.
  // the dCut cuts are the cuts that have to do with sigal quality
  TCut aCut_20_40 = "Dpt>20 && Dpt<40 && Dtrk1Pt>1.5119066783466506 && DRestrk1Pt>0.30536377790210678 && DRestrk2Pt>0.36338212403760983 && DtktkRespt>7.8250794441627303 && Dchi2cl>0.051459643814556165 && DtktkRes_chi2cl>0.043374341702374246 && Dalpha<0.19826644414562558 && DtktkRes_alpha<0.20011998802556244 && DsvpvDistance/DsvpvDisErr>3.1977048738596423 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>3.2666225677967122";
  TCut cCut_20_40 = "Gpt>20 && Gpt<40 && abs(Gtk1eta)<1.5 && Gtk1pt>1.5119066783466506 && GRestk1pt>.5 && GRestk2pt>0.36338212403760983 && abs(GRestk1eta)<1.5 && abs(GRestk2eta)<1.5";
  TCut dCut_20_40 = "Dpt>20 && Dpt<40 && Dchi2cl>0.051459643814556165 && DtktkRes_chi2cl>0.043374341702374246 && Dalpha<0.19826644414562558 && DtktkRes_alpha<0.20011998802556244 && DsvpvDistance/DsvpvDisErr>3.1977048738596423 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>3.2666225677967122";

  //TODO switch pt ranges back to 40-100
  // cuts for 40-100 GeV range.
  TCut aCut_40_100 = "Dpt>40 && Dpt<100 && Dtrk1Pt>3.1283988174549324 && DRestrk1Pt>0.87633860909130834 && DRestrk2Pt>0.49219084823940806 && DtktkRespt>7.4482612362135594 && Dchi2cl>0.042252454543442439 && DtktkRes_chi2cl>0.055413157979800419 && Dalpha<0.075990655431829757 && DtktkRes_alpha<0.1960009217583123 && DsvpvDistance/DsvpvDisErr>2.9228773605879357 && DtktkRes_svpvDistance/DtktkRes_svpvDisErr>2.9237382468189037";
  TCut cCut_40_100 = "Gpt>40 && Gpt<100 && abs(Gtk1eta)<1.5 && Gtk1pt>3.1283988174549324 && GRestk2pt>0.5 && GRestk1pt>0.5 && abs(GRestk1eta)<1.5 && abs(GRestk2eta)<1.5 &&GRestk1pt>0.87633860909130834 && GRestk2pt>0.49219084823940806";
  TCut dCut_40_100 = "Dpt>40 && Dpt<100 && abs(DtktkResmass-1.87)<0.03 && Dchi2cl>0.05 && DtktkRes_chi2cl>0.05 && Dalpha<0.2 && DtktkRes_alpha<0.2 && (DsvpvDistance/DsvpvDisErr)>2.0 && (DtktkRes_svpvDistance/DtktkRes_svpvDisErr)>2.0";

  // efficiency calculations proceed as follows:
  // a =  number of candidates left after cutting the reconstructed signal
  //      using the optimzed cuts
  // b =  number of candidates after cutting generated B signal on rapidity.
  //      The GisSignal cuts ensure that only the generated particles that are
  //      B mesons are kept
  // c =  number of candidates after cutting generated B signal on rapidity,
  //      momentum, and eta
  // d =  number of candidates left after cutting reconstructed signal with 
  //      the optimzed cuts that refer to signal quality
  TCut aCuts = (aCut_40_100) && prefilter && "Dgen==23333";
  TCut bCuts = "Gpt>40 && Gpt<100 &&TMath::Abs(Gy)<1. && (GisSignal == 13 || GisSignal == 14)";
  TCut cCuts = (cCut_40_100)
    && "TMath::Abs(Gy)<1. && (GisSignal == 13 || GisSignal == 14)";
  TCut dCuts = dCut_40_100;


  // do we cut along pt bin for b?
  // for 40-100:
  //  if yes: cross section is 379.786
  //  if no:  cross section is 996.356
  // for 20-40:
  //  if yes: cross section is 5326.73
  //  if no:  cross section is 19607.5

  // creat histograms and apply cuts to get the respective numbers of candidates
  TH1D * hista = new TH1D("hista", "", 1, 40, 100);
  tree->Project("hista","Dpt",aCuts);
  Double_t a = hista->GetEntries();

  std::cout << "a " << a << std::endl;

  TH1D * histb = new TH1D("histb", "", 1, 40, 100);
  genTree->Project("histb","Gpt",bCuts);
  Double_t b = histb->GetEntries();
  std::cout << "b " << b << std::endl;

  TH1D * histc = new TH1D("histc", "", 1, 40, 100);
  genTree->Project("histc","Gpt",cCuts);
  Double_t c = histc->GetEntries();
  
  TH1D * histd = new TH1D("histd", "", 1, 40, 100);
  tree->Project("histd","Dpt",dCuts);
  Double_t d = histd->GetEntries();

  std::cout << "\nacceptance                  : " << c / b << std::endl;
  std::cout << "recontruction efficiency    : "<< d / c << std::endl;
  std::cout << "d mes n selection efficiency: " << a / d << std::endl;
  std::cout << "total efficiency            : " << a / b << std::endl 
    << std::endl;

  // create efficiency graphs with error bars for 10pt bins from 20-100 GeV
  const Int_t n = 1;
  Double_t x[n], acceptance[n], recoEff[n], dSelectionEff[n], totalEff[n],
           accPErr[n], recPErr[n], dmsPErr[n], totPErr[n],
           accBErr[n], recBErr[n], dmsBErr[n], totBErr[n];
  for (Int_t i=0; i<n; ++i) {
    x[i] = 25+10*i;
    acceptance[i] =     histc->GetBinContent(i+1)/histb->GetBinContent(i+1);
    recoEff[i] =        histd->GetBinContent(i+1)/histc->GetBinContent(i+1);
    dSelectionEff[i] =  hista->GetBinContent(i+1)/histd->GetBinContent(i+1);
    totalEff[i] =       hista->GetBinContent(i+1)/histb->GetBinContent(i+1);
    
    // poisson errors
    accPErr[i] = histc->GetBinContent(i+1)/histb->GetBinContent(i+1)
      *sqrt(1/histc->GetBinContent(i+1)+1/histb->GetBinContent(i+1));
    recPErr[i] = histd->GetBinContent(i+1)/histc->GetBinContent(i+1)
      *sqrt(1/histd->GetBinContent(i+1)+1/histc->GetBinContent(i+1));
    dmsPErr[i] = hista->GetBinContent(i+1)/histd->GetBinContent(i+1)
      *sqrt(1/hista->GetBinContent(i+1)+1/histd->GetBinContent(i+1));
    totPErr[i] = histd->GetBinContent(i+1)/histb->GetBinContent(i+1)
      *sqrt(1/histd->GetBinContent(i+1)+1/histb->GetBinContent(i+1));

    // binomial errors
    accBErr[i] = 1/histb->GetBinContent(i+1)
      *sqrt(histc->GetBinContent(i+1)
          *(1-histc->GetBinContent(i+1)/histb->GetBinContent(i+1)));
    recBErr[i] = 1/histc->GetBinContent(i+1)
      *sqrt(histd->GetBinContent(i+1)
          *(1-histd->GetBinContent(i+1)/histc->GetBinContent(i+1)));
    dmsBErr[i] = 1/histd->GetBinContent(i+1)
      *sqrt(hista->GetBinContent(i+1)
          *(1-hista->GetBinContent(i+1)/histd->GetBinContent(i+1)));
    totBErr[i] = 1/histb->GetBinContent(i+1)
      *sqrt(histd->GetBinContent(i+1)
          *(1-histd->GetBinContent(i+1)/histb->GetBinContent(i+1)));
    std::cout << "binomial errors: \n";
    std::cout << "acceptance " << accBErr[i] << std::endl;
    std::cout << "reconstructed " << recBErr[i] << std::endl;
    std::cout << "d meson signal " << dmsBErr[i] << std::endl;
    std::cout << "total  " << totBErr[i] << std::endl;
  }



  TCanvas *c1 = new TCanvas("c1","acceptance");
  TGraphErrors* acceptanceGraph = new TGraphErrors(n,x,acceptance, accBErr);
  acceptanceGraph->SetFillColor(40);
  acceptanceGraph->SetTitle("Acceptance v. Pt");
  acceptanceGraph->GetXaxis()->SetTitle("Pt");
  acceptanceGraph->GetYaxis()->SetTitle("Acceptance");
  acceptanceGraph->Draw("AB");
  c1->Print("plotEfficiencies/acceptance.pdf");
  
  TCanvas *c2 = new TCanvas("c2","reconstruction efficiency");
  TGraphErrors* recoEffGraph = new TGraphErrors(n,x,recoEff, recBErr);
  recoEffGraph->SetFillColor(40);
  recoEffGraph->SetTitle("Reconstruction Efficiency v. Pt");
  recoEffGraph->GetXaxis()->SetTitle("Pt");
  recoEffGraph->GetYaxis()->SetTitle("Reconstruction Efficiency");
  recoEffGraph->Draw("AB");
  c2->Print("plotEfficiencies/reconstructionEfficiency.pdf");
  
  TCanvas *c3 = new TCanvas("c3","D selection efficiency");
  TGraphErrors* dSelectionEffGraph =
    new TGraphErrors(n,x,dSelectionEff, dmsBErr);
  dSelectionEffGraph->SetFillColor(40);
  dSelectionEffGraph->SetTitle("D Selection Efficiency v. Pt");
  dSelectionEffGraph->GetXaxis()->SetTitle("Pt");
  dSelectionEffGraph->GetYaxis()->SetTitle("D Selection Efficiency");
  dSelectionEffGraph->Draw("AB");
  c3->Print("plotEfficiencies/dSelectionEfficiency.pdf");
 
  TCanvas *c4 = new TCanvas("c4","total efficiency");
  TGraphErrors* totalEffGraph = new TGraphErrors(n,x,totalEff, totBErr);
  totalEffGraph->SetFillColor(40);
  totalEffGraph->SetTitle("Total Efficiency v. Pt");
  totalEffGraph->GetXaxis()->SetTitle("Pt");
  totalEffGraph->GetYaxis()->SetTitle("Total Efficiency");
  totalEffGraph->Draw("AB");
  c4->Print("plotEfficiencies/totalEfficiency.pdf");
  // calculation of cross section. To calculate the cross section we need
  // the yield, the branching ratio, the beta_prescale, the efficiency, and the
  // luminosity.
  // D_bar 0 pi+ decay fraction taken from 
  // http://pdg.arsip.lipi.go.id/2013/listings/rpp2013-list-B-plus-minus.pdf
  Double_t beta_prescale15 = 1/(2.594206e+01); // prescale for 15-30 trigger
  Double_t beta_prescale30 = 1/(4.070169e+00); // prescale for 30-50 trigger
  Double_t e_trigger = 1; // ? trigger efficiency is negligible for now
  Double_t BR = 1.8864e-4; //4.8e-3*3.93e-2
  Double_t luminosity = 27.4;
  Double_t efficiency = a/b;
  Double_t yield20 = 21.7;
  Double_t yield40 = 12.2788;

  Double_t cross_section = .5*yield40 /
    (efficiency*BR*beta_prescale30*luminosity);

  std::cout << "cross section: " << cross_section << std::endl;
}
 
// do all the same analysis for 10-15 and 15020 GeV
// after this we can try splitting the efficiency  into multple parts :
//    1. (gen with cuts on rapidity, and signle track cuts on eta and pt) / gend with rapidity cuts  [c / b]
//    2. (D reconstructed and reconstructed track selection with cuts that refer to reconstructed tracks (i.e. tracks that refer to the quality of the tracks)) / numerator of 1 [d / c]
//    3. numerator of original efficiency / numerator of 2  [ a / d]


// prefilter cuts for DRestrk1Pt and DRestrk2Pt are more strict than the optimized cuts.Is that okay?
