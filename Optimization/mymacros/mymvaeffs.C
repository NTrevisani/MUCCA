#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

#include "tmvaglob.C"

#include "RQ_OBJECT.h"

#include "TH1.h"
#include "TROOT.h"
#include "TList.h"
#include "TIterator.h"
#include "TStyle.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TH2.h"
#include "TFormula.h"
#include "TFile.h"
#include "TApplication.h"
#include "TKey.h"
#include "TClass.h"
#include "TGaxis.h"

#include "TGWindow.h"
#include "TGButton.h"
#include "TGLabel.h"
#include "TGNumberEntry.h"

using namespace std;

Float_t significance(Float_t nSig, Float_t nBkg){
  if (nSig != 0 || nBkg != 0)
    return nSig / sqrt(nSig + nBkg);
  else {
    cout<<"I cannot compute signifince. Let's say it is 0 ;)"<<endl;
    return 0;
  }
}

void mymvaeffs(TString input = "TMVA.root",
	       TString train = "BDTG18",
	       Float_t sigEvents = 12,
	       Float_t bkgEvents = 11000
	       ){

  // Reading input file  
  TFile* inputFile = new TFile(input,"READ");

  TString sigName = "Method_BDT/" + train + "/MVA_" + train + "_effS";
  TH1F* MVAsignal = (TH1F*) inputFile -> Get(sigName);
  MVAsignal -> Scale(sigEvents / MVAsignal -> Integral());
  //MVAsignal -> Draw();

  TString bkgName = "Method_BDT/" + train + "/MVA_" + train + "_effB";
  TH1F* MVAbackground = (TH1F*) inputFile -> Get(bkgName);
  MVAbackground -> Scale(bkgEvents / MVAbackground -> Integral());
  //MVAbackground -> Draw("same");

  if (MVAsignal->GetNbinsX() != MVAbackground->GetNbinsX()){
    cout<<"The two histograms have a different number of bins"<<endl;
    cout<<"I CANNOT WORK THIS WAY!!"<<endl;
    return;
  }
    
  Float_t nBins = MVAsignal->GetNbinsX();  

  TH1F* h_significance = (TH1F*)MVAsignal->Clone("h_significance");

  float maxSig = -9999.;
  float MVAmax = 0.;

  for (Int_t i = 1; i < nBins + 1; ++i){
    if (i % 100 == 0)
      cout<<"Bin number: "<<i<<", nSig: "<<MVAsignal->Integral(i,nBins)<<", nBkg: "<<MVAbackground->Integral(i,nBins)<<", significance: "<<significance(MVAsignal->Integral(i,nBins),MVAbackground->Integral(i,nBins))<<endl;
    Float_t localSig = significance(MVAsignal->Integral(i,nBins),MVAbackground->Integral(i,nBins));
    if (localSig > maxSig){
      maxSig = localSig;
      MVAmax = h_significance->GetBinCenter(i);
    }
    h_significance->SetBinContent(i,localSig);
  }

  cout<<"Best MVA cut: "<<MVAmax<<". It allows you to get a significance of: "<<maxSig<<endl;

  //Drawing stuff
  h_significance->SetLineColor(kGreen+1);
  h_significance->SetLineWidth(3);
  TString title = "Significance vs MVA cut for " + train + "training";
  h_significance->SetTitle(title);
  h_significance->GetXaxis()->SetTitle("MVA Output");
  h_significance->GetYaxis()->SetTitle("#frac{S}{#sqrt{S + B}}");
  h_significance->GetYaxis()->SetTitleOffset(2);
  gStyle->SetOptStat(0);

  char latexString[80];
  sprintf(latexString,"Best MVA cut: %3f", MVAmax);
  char latexString2[80];
  sprintf(latexString2,"Best significance: %3f", maxSig);

  TLatex* tl = new TLatex(0.2,0.35,latexString);
  tl->SetNDC();
  tl->SetTextSize(0.03);
  TLatex* tl2 = new TLatex(0.2,0.30,latexString2);
  tl2->SetNDC();
  tl2->SetTextSize(0.03);

  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  c1->cd();
  TPad* pad1 = new TPad("pad1","pad1",0.,0.,1.,1.);
  pad1->Draw();
  pad1->SetLeftMargin(0.15);
  pad1->cd();
  h_significance->Draw();
  tl->Draw("same");
  tl2->Draw("same");
  TString save = "plots/Significance" + train + ".png";
  c1->Print(save);
}


