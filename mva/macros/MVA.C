#include "../header.h"
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <vector>
#include <iostream>
#include "../../prefilter.h"
#define MAX_XB       20000

void MVA(int pbpb, float ptMin , float ptMax, string mvatype)
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
	TTree *t = (TTree*)inf->Get("ntphi");

	Int_t   Bsize;
	Float_t Btrk1Pt[MAX_XB];
	Float_t Btrk2Pt[MAX_XB];
  Float_t Btktkpt[MAX_XB];
	Float_t Bchi2cl[MAX_XB];
	Float_t Balpha[MAX_XB];
	Float_t BsvpvDistance[MAX_XB];
	Float_t BsvpvDisErr[MAX_XB];

	t->SetBranchAddress("Bsize", &Bsize);
	t->SetBranchAddress("Btrk1Pt", Btrk1Pt);
	t->SetBranchAddress("Btrk2Pt", Btrk2Pt);
	t->SetBranchAddress("Btktkpt", Btktkpt);
	t->SetBranchAddress("Bchi2cl", Bchi2cl);
	t->SetBranchAddress("Balpha", Balpha);
	t->SetBranchAddress("BsvpvDistance", BsvpvDistance);
	t->SetBranchAddress("BsvpvDisErr", BsvpvDisErr);

	std::vector<std::string> theInputVars;
	string a1="Btrk1Pt";
	string a2="Btrk2Pt";
	string a3="Btktkpt";
	string a4="Bchi2cl";
	string a5="Balpha";
	string a6="BsvpvDistance/BsvpvDisErr";

	theInputVars.push_back(a1);
	theInputVars.push_back(a2);
	theInputVars.push_back(a3); 
	theInputVars.push_back(a4); 
	theInputVars.push_back(a5); 
	theInputVars.push_back(a6); 

	vector<double> inputValues;
	ReadLD   readLD(theInputVars);
	ReadMLP  readMLP(theInputVars);
	ReadBDT  readBDT(theInputVars);
	ReadBDTB readBDTB(theInputVars);

	TFile *outf = new TFile(ofname,"recreate");
	TTree *mvaTree = new TTree("mvaTree","MVA");

	double LD[MAX_XB];
	double MLP[MAX_XB];
	double BDT[MAX_XB];
	double BDTB[MAX_XB];
	mvaTree->Branch("Bsize",&Bsize,"Bsize/I");
	mvaTree->Branch("LD",  LD,  Form("%s[Bsize]/D","LD"));
	mvaTree->Branch("MLP", MLP, Form("%s[Bsize]/D","MLP"));
	mvaTree->Branch("BDT", BDT, Form("%s[Bsize]/D","BDT"));
	mvaTree->Branch("BDTB",BDTB,Form("%s[Bsize]/D","BDTB"));

	for(int i=0;i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		if(i%1000000==0) cout <<i<<" / "<<t->GetEntries()<<endl;
		for(int j=0;j<Bsize;j++)
		{
			inputValues.clear();
			inputValues.push_back(Btrk1Pt[j]);
			inputValues.push_back(Btrk2Pt[j]);
    	inputValues.push_back(Btktkpt[j]);
			inputValues.push_back(Bchi2cl[j]);
			inputValues.push_back(Balpha[j]);
			inputValues.push_back(BsvpvDistance[j]/BsvpvDisErr[j]);

			LD[j]=readLD.GetMvaValue(inputValues);      
			MLP[j]=readMLP.GetMvaValue(inputValues);      
			BDT[j]=readBDT.GetMvaValue(inputValues);      
			BDTB[j]=readBDTB.GetMvaValue(inputValues);      
		}
		mvaTree->Fill();
	}
  std::cout  << "1\n";
	outf->cd();
	outf->Write();
	outf->Close();
}
