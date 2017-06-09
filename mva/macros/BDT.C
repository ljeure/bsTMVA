#include "../header.h"
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <vector>
#include <iostream>
#include "../../prefilter.h"
#define MAX_XB       20000

void BDT(int pbpb, float ptMin , float ptMax, string mvatype)
{
	void makeoutput(TString infname, TString ofname, TString mvatype);

	MVAtype = (TString)mvatype;
	isPbPb = (bool)pbpb;
	ptmin = ptMin;
	ptmax = ptMax;
	if(isPbPb)
	{
		inputSname = inputSname_PP;
		inputBname = inputBname_PP;
		colsyst = "PbPb";
	}
	else{
		inputSname = inputSname_pp;
		inputBname = inputBname_pp;
		colsyst = "pp";
	}

	TString outfile1 =Form("../MVAfiles/%s_%s_%.0f_%.0f_DATA.root",MVAtype.Data(),colsyst.Data(),ptMin,ptMax) ;
	makeoutput(inputBname,outfile1,MVAtype);
	TString outfile2 =Form("../MVAfiles/%s_%s_%.0f_%.0f_MC.root",MVAtype.Data(),colsyst.Data(),ptMin,ptMax) ;
	makeoutput(inputSname,outfile2,MVAtype);
}

void makeoutput(TString infname, TString ofname, TString mvatype)
{
	TFile *inf = new TFile(infname);
	TTree *t = (TTree*)inf->Get("ntBptoD0pi");

	Int_t   Dsize;
	Float_t Dtrk1Pt[MAX_XB];
	Float_t DRestrk1Pt[MAX_XB];
	Float_t DRestrk2Pt[MAX_XB];
	Float_t DtktkRespt[MAX_XB];
	Float_t Dchi2cl[MAX_XB];
	Float_t DtktkRes_chi2cl[MAX_XB];
	Float_t Dalpha[MAX_XB];
	Float_t DtktkRes_alpha[MAX_XB];
	Float_t DsvpvDistance[MAX_XB];
	Float_t DsvpvDisErr[MAX_XB];
	Float_t DtktkRes_svpvDistance[MAX_XB];
	Float_t DtktkRes_svpvDisErr[MAX_XB];

	t->SetBranchAddress("Dsize", &Dsize);
	t->SetBranchAddress("Dtrk1Pt", Dtrk1Pt);
	t->SetBranchAddress("DRestrk1Pt", DRestrk1Pt);
	t->SetBranchAddress("DRestrk2Pt", DRestrk2Pt);
	t->SetBranchAddress("DtktkRespt", DtktkRespt);
	t->SetBranchAddress("Dchi2cl", Dchi2cl);
	t->SetBranchAddress("DtktkRes_chi2cl", DtktkRes_chi2cl);
	t->SetBranchAddress("Dalpha", Dalpha);
	t->SetBranchAddress("DtktkRes_alpha", DtktkRes_alpha);
	t->SetBranchAddress("DsvpvDistance", DsvpvDistance);
	t->SetBranchAddress("DsvpvDisErr", DsvpvDisErr);
	t->SetBranchAddress("DtktkRes_svpvDistance", DtktkRes_svpvDistance);
	t->SetBranchAddress("DtktkRes_svpvDisErr", DtktkRes_svpvDisErr);

	std::vector<std::string> theInputVars;
	string a1="Dtrk1Pt";
	string a2="DRestrk1Pt";
	string a3="DRestrk2Pt";
	string a4="DtktkRespt";
	string a5="Dchi2cl";
	string a6="DtktkRes_chi2cl";
	string a7="Dalpha";
	string a8="DtktkRes_alpha";
	string a9="DsvpvDistance/DsvpvDisErr";
	string a10="DtktkRes_svpvDistance/DtktkRes_svpvDisErr";
	theInputVars.push_back(a1);
	theInputVars.push_back(a2);
	theInputVars.push_back(a3);
	theInputVars.push_back(a4); 
	theInputVars.push_back(a5); 
	theInputVars.push_back(a6); 
	theInputVars.push_back(a7); 
	theInputVars.push_back(a8); 
	theInputVars.push_back(a9); 
	theInputVars.push_back(a10); 

	vector<double> inputValues;
	//cout<<"kf1500"<<endl;
	ReadBDT mva(theInputVars);
	//cout<<"kf1600"<<endl;

	TFile *outf = new TFile(ofname,"recreate");
	TTree *mvaTree = new TTree("mvaTree","MVA");

	double MVA[MAX_XB];
	mvaTree->Branch("Dsize",&Dsize,"Dsize/I");
	mvaTree->Branch(mvatype.Data(),MVA,Form("%s[Dsize]/D",mvatype.Data()));

	for(int i=0;i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		if(i%1000000==0) cout <<i<<" / "<<t->GetEntries()<<endl;
		for(int j=0;j<Dsize;j++)
		{
			inputValues.clear();
			inputValues.push_back(Dtrk1Pt[j]);
			inputValues.push_back(DRestrk1Pt[j]);
			inputValues.push_back(DRestrk2Pt[j]);
			inputValues.push_back(DtktkRespt[j]);
			inputValues.push_back(Dchi2cl[j]);
			inputValues.push_back(DtktkRes_chi2cl[j]);
			inputValues.push_back(Dalpha[j]);
			inputValues.push_back(DtktkRes_alpha[j]);
			inputValues.push_back(DsvpvDistance[j]/DsvpvDisErr[j]);
			inputValues.push_back(DtktkRes_svpvDistance[j]/DtktkRes_svpvDisErr[j]);
			MVA[j]=mva.GetMvaValue(inputValues);      
		}
		mvaTree->Fill();
	}
	outf->cd();
	outf->Write();
	outf->Close();
}
