void graphEfficiencies() {


  const Int_t NBINS = 2;
  Double_t edges[NBINS + 1] = {20, 40, 100};
  // Bin 1 corresponds to range [0.0, 0.2]
  // Bin 2 corresponds to range [0.2, 0.3] etc...

  TH1* h = new TH1D(/* name */ "h1", /* title */ "Total Efficiency",
      /* number of bins */ NBINS, /* edge array */ edges);

  h->SetBinContent(1, .400939);
  h->SetBinError(1, .00279387);

  h->SetBinContent(2, .500462);
  h->SetBinError(2, .00232898);

  h->Draw("E B");
/*
40-100:
  total efficiency                  : 0.500462 +- 0.00232898

  20-40:
  total efficiency                  : 0.400939 +-  0.00279387
*/

/*
  double nBins[3] = {20, 40, 100};

  TCanvas *c1 = new TCanvas("c1","acceptance");
  TH1D * accept = new TH1D("accept", "", 2, nBins);
  accept->SetBinContent(1, .908331);
  accept->SetBinContent(2, .919289 );
  accept->Draw();
  c1->Print("plotEfficiencies/acceptance.pdf");

  TCanvas *c2 = new TCanvas("c2","reconstruction efficiency");
  TH1D * reco = new TH1D("reco", "", 2, nBins);
  reco->SetBinContent(1, 0.604164);
  reco->SetBinContent(2, 0.648272);
  reco->Draw();
  c2->Print("plotEfficiencies/reconstructionEfficiency.pdf");

  TCanvas *c3 = new TCanvas("c3","D selection efficiency");
  TH1D * dsEff = new TH1D("dsEff", "", 2, nBins);
  dsEff->SetBinContent(1, 0.730599);
  dsEff->SetBinContent(2, 0.839772);
  dsEff->Draw();
  c3->Print("plotEfficiencies/dSelectionEfficiency.pdf");

  TCanvas *c4 = new TCanvas("c4","total efficiency");
  TH1D * totEff = new TH1D("totEff", "", 2, nBins);
  totEff->SetBinContent(1, 0.400939);
  totEff->SetBinContent(2, 0.500462);
  totEff->Draw();
  c4->Print("plotEfficiencies/totalEfficiency.pdf");
*/
}
