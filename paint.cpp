#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include <string>
#include <stdio.h>
#include "TFile.h"

using namespace std;

/*char cleg[7];
Int_t cont1=0,cont2=0;

void sysstyle(){
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadBottomMargin(0.3);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
}

void histstyle(TH1D *h1,int i,TLegend *leg){
  h1->SetStats(kFALSE);
  h1->SetLineColor(color[i]);
  h1->GetXaxis()->SetTitleSize(0.043);
  h1->GetYaxis()->SetTitleSize(0.043);
  h1->SetLineWidth(1);
  //h1->DrawNormalized("HIST e,SAME");
  h1->Draw("HIST e,SAME");
  if(i==0)
  leg->AddEntry(h1,"photon_chiso[0]<0.441","l");
  else{
    sprintf(cleg,"photon_chiso[0]>%d",2*i);
    leg->AddEntry(h1,cleg,"l");
  }
}

void compare(TTree* t0,TTree* t1,TTree* t2){
  Double_t sieie_med,sieie_los,sieie_los5;
  Double_t chiso_med,chiso_los,chiso_los5;
  Double_t scalef0,scalef1,scalef2;
  t0->SetBranchAddress("sieie_med",&sieie_med);
  t0->SetBranchAddress("chiso_med",&chiso_med);
  t0->SetBranchAddress("scalef0",&scalef0);
  t1->SetBranchAddress("sieie_los",&sieie_los);
  t1->SetBranchAddress("chiso_los",&chiso_los);
  t1->SetBranchAddress("scalef1",&scalef1);
  t2->SetBranchAddress("sieie_los5",&sieie_los5);
  t2->SetBranchAddress("chiso_los5",&chiso_los5);
  t2->SetBranchAddress("scalef2",&scalef2);
  TH1D *hmed0 = new TH1D("hmed0","photon_sieie distribution;photon_sieie;count",bin,0.,0.018);
  TH1D *hmed1 = new TH1D("hmed1","photon_sieie distribution;photon_sieie;count",bin,0.,0.018);
  TH1D *hlos0 = new TH1D("hlos0","photon_sieie distribution;photon_sieie;count",bin,0.,0.018);
  TH1D *hlos1 = new TH1D("hlos1","photon_sieie distribution;photon_sieie;count",bin,0.,0.018);
  Long64_t n=t0->GetEntries();
  for(Long64_t i=0;i<n;i++){
    t0->GetEntry(i);
    if (chiso_med<0.441){
      hmed0->Fill(sieie_med,scalef0);
      cont1++;
    }
    if (chiso_med>4 && chiso_med<10 ){
      hmed1->Fill(sieie_med,scalef0);
    }
  }
  n=t1->GetEntries();
  for(Long64_t i=0;i<n;i++){
    t1->GetEntry(i);
    if (chiso_los<0.441){
      hlos0->Fill(sieie_los,scalef1);
    }
    if (chiso_los>4 && chiso_los<10 ){
      hlos1->Fill(sieie_los,scalef1);
    }
  }
  n=t2->GetEntries();
  for(Long64_t i=0;i<n;i++){
    t2->GetEntry(i);
    hlos50->Fill(sieie_los5);
    cont2++;
  }
  TCanvas *c3 = new TCanvas("c3","c3",800,600);
  c3->SetLogy();
  TLegend *l3 = new TLegend(0.15,0.66,0.45,0.86);
  l3->SetBorderSize(2);
  l3->SetFillColor(0);
  c3->cd();
  //histstyle2(hlos51, 6, l3);
  histstyle2(hmed0, 1, l3);
  histstyle2(hmed1, 2, l3);
  histstyle2(hlos0, 3, l3);
  histstyle2(hlos1, 4, l3);
  histstyle2(hlos50, 5, l3);

  l3->Draw();
  c3->SaveAs("c3.eps");
  cout<<"number of medium id:"<<cont1<<endl;
  cout<<"number of medium mix loose id:"<<cont2<<endl;
}

void histstyle2(TH1D *h1,int i,TLegend *leg){
h1->SetStats(kFALSE);
h1->SetLineStyle(line[i-1]);
h1->SetLineColor(color[i-1]);
h1->GetXaxis()->SetTitleSize(0.043);
h1->GetYaxis()->SetTitleSize(0.043);
h1->SetLineWidth(linwid[i-1]);
h1->DrawNormalized("HIST e,SAME");
switch (i) {
  case 1:
  leg->AddEntry(h1,"medium id && photon_chiso<0.441","l");
  break;
  case 2:
  leg->AddEntry(h1,"medium id && 4<photon_chiso<10","l");
  break;
  case 3:
  leg->AddEntry(h1,"loose id && photon_chiso<0.441","l");
  break;
  case 4:
  leg->AddEntry(h1,"loose id && 4<photon_chiso<10","l");
  break;
  case 5:
  leg->AddEntry(h1,"medium mix loose id","l");
  break;
  case 6:
  leg->AddEntry(h1,"5*loose id && 4<photon_chiso<10","l");
  break;
}
}*/

void paint(){
  TFile *f1=new TFile("truephoton.root");
  TFile *f2=new TFile("fakephoton.root");

  TTree *truemed=(TTree *)f1->Get("medtree");
  TTree *truelos=(TTree *)f1->Get("lostree");
  TTree *fakemed=(TTree *)f2->Get("medtree");
  TTree *fakelos=(TTree *)f2->Get("lostree");

  Double_t tsieie_med,tsieie_los,fsieie_med,fsieie_los;
  Double_t tchiso_med,tchiso_los,fchiso_med,fchiso_los;
  Double_t tscalef_med,tscalef_los,fscalef_med,fscalef_los;

  truemed->SetBranchAddress("sieie_med",&tsieie_med);
  truemed->SetBranchAddress("chiso_med",&tchiso_med);
  truemed->SetBranchAddress("scalef0",&tscalef_med);

  truelos->SetBranchAddress("sieie_los",&tsieie_los);
  truelos->SetBranchAddress("chiso_los",&tchiso_los);
  truelos->SetBranchAddress("scalef1",&tscalef_los);

  fakemed->SetBranchAddress("sieie_med",&fsieie_med);
  fakemed->SetBranchAddress("chiso_med",&fchiso_med);
  fakemed->SetBranchAddress("scalef0",&fscalef_med);

  fakelos->SetBranchAddress("sieie_los",&fsieie_los);
  fakelos->SetBranchAddress("chiso_los",&fchiso_los);
  fakelos->SetBranchAddress("scalef1",&fscalef_los);

  TCanvas *c1=new TCanvas("c1","c1");

  TFile *opt=new TFile("result.root","recreate");
  TH1D *th1=new TH1D("th1","th1",50,0.,0.018);
  TH1D *th2=new TH1D("th2","th2",50,0.,0.018);
  TH1D *fh1=new TH1D("fh1","fh1",50,0.,0.018);
  TH1D *fh2=new TH1D("fh2","fh2",50,0.,0.018);

  Long64_t n1=truemed->GetEntries();
  Long64_t n2=truelos->GetEntries();
  Long64_t n3=fakemed->GetEntries();
  Long64_t n4=fakelos->GetEntries();

  for(Long64_t i=0; i<n1; i++){
    truemed->GetEntry(i);
    if(tchiso_med<0.441){
      th1->Fill(tsieie_med);
    }
    if(tchiso_med<10 && tchiso_med>4){
      th2->Fill(tsieie_med);
    }
  }
  for(Long64_t i=0; i<n3; i++){
    fakemed->GetEntry(i);
    if(fchiso_med<0.441){
      fh1->Fill(fsieie_med);
    }
    if(fchiso_med<10 && fchiso_med>4){
      fh2->Fill(fsieie_med);
    }
  }
  opt->Write();
}
