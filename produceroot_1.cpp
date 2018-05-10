#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TLegend.h"
#include "TStyle.h"
#include <string>
#include <stdio.h>
#include "TFile.h"

using namespace std;

Double_t ptmin,ptmax;
Double_t ptlow[9]={25,30,35,40,45,50,60,80,120};
Double_t pthigh[9]={30,35,40,45,50,60,80,120,400};

void slectree(TTree *t1,int isprom){
  TTree *t;
  t=t1;
  char optname[20];
  if(isprom==0){
    sprintf(optname,"truePhoton.root");
  }else{
    sprintf(optname,"fakePhoton.root");
  }
  Int_t lep;
  Int_t nlooseeles;
  Int_t nloosemus;
  Double_t mtVlepJECnew;
  Double_t ptlep1;
  Double_t etalep1;
  Double_t MET_et;
  Int_t photon_isprompt[6];
  Double_t photon_drla[6];
  Double_t photon_hoe[6];
  Double_t photon_nhiso[6];
  Double_t photon_phoiso[6];
  Double_t photon_chiso[6];
  Double_t photon_sieie[6];
  Double_t photon_pt[6];
  Double_t photon_eta[6];
  Double_t scalef;
  t->SetBranchAddress("scalef",&scalef);
  t->SetBranchAddress("lep",&lep);
  t->SetBranchAddress("nlooseeles",&nlooseeles);
  t->SetBranchAddress("nloosemus",&nloosemus);
  t->SetBranchAddress("mtVlepJECnew",&mtVlepJECnew);
  t->SetBranchAddress("ptlep1",&ptlep1);
  t->SetBranchAddress("etalep1",&etalep1);
  t->SetBranchAddress("MET_et",&MET_et);
  t->SetBranchAddress("photon_isprompt",photon_isprompt);
  t->SetBranchAddress("photon_drla",photon_drla);
  t->SetBranchAddress("photon_hoe",photon_hoe);
  t->SetBranchAddress("photon_nhiso",photon_nhiso);
  t->SetBranchAddress("photon_phoiso",photon_phoiso);
  t->SetBranchAddress("photon_chiso",photon_chiso);
  t->SetBranchAddress("photon_sieie",photon_sieie);
  t->SetBranchAddress("photon_pt",photon_pt);
  t->SetBranchAddress("photon_eta",photon_eta);

  Double_t scalef0,scalef1;
  Double_t sieie_med,sieie_los;
  Double_t chiso_med,chiso_los;
  TFile *opt=new TFile(optname,"recreate");
  TTree *medtree=new TTree("medtree","medium_id");
  medtree->Branch("sieie_med",&sieie_med,"sieie_med/D");
  medtree->Branch("chiso_med",&chiso_med,"chiso_med/D");
  medtree->Branch("scalef0",&scalef0,"scalef0/D");
  TTree *lostree=new TTree("lostree","loose_id");
  lostree->Branch("sieie_los",&sieie_los,"sieie_los/D");
  lostree->Branch("chiso_los",&chiso_los,"chiso_los/D");
  lostree->Branch("scalef1",&scalef1,"scalef1/D");
  /*TTree *los5tree=new TTree("los5tree","loose_id5");
  los5tree->Branch("sieie_los5",&sieie_los5,"sieie_los5/D");
  los5tree->Branch("chiso_los5",&chiso_los5,"chiso_los5/D");
  los5tree->Branch("scalef2",&scalef2,"scalef2/D");*/

  bool wjet;
  bool photon_cut[2];
  bool medium;
  bool loose;
  bool tmp[2];
  //bool loose5;
  Double_t pho_pt[3];
  Int_t flag[3];
  Int_t total[3]={0};
  Long64_t nentries=t->GetEntries();
  for (Long64_t jentry=0; jentry<nentries/*jentry<2000*/;jentry++){
    t->GetEntry(jentry);
    pho_pt[0]=0.;pho_pt[1]=0.;pho_pt[2]=0.;
    flag[0]=100;flag[1]=100;flag[2]=100;
    for (int j=0;j<6;j++) {
       wjet = (lep==13 && nlooseeles==0 && nloosemus<2 && mtVlepJECnew>30 && ptlep1>30 && fabs(etalep1)<2.5 && MET_et>35);
       tmp[0]=(photon_isprompt[j] == 1);
       tmp[1]=(photon_isprompt[j] != 1);
       photon_cut[0] = (photon_drla[j]>0.5 && fabs(photon_eta[j])<1.442);
       photon_cut[1] = (photon_isprompt[j] == 1  &&  photon_drla[j]>0.5 && fabs(photon_eta[j])<1.442);
       /////////////////////////////////////////////////////////////////////////
       /*loose5 = (photon_hoe[j]<0.0396 && photon_nhiso[j]>(10.910+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j])&& photon_nhiso[j]<5*(10.910+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j]) && photon_phoiso[j]<(2.571+0.0047*photon_pt[j]) && photon_chiso[j]<0.441) ||
       (photon_hoe[j]<0.0396 && photon_nhiso[j]<(2.725+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j]) && photon_phoiso[j]>(3.630+0.0047*photon_pt[j]) && photon_phoiso[j]<5*(3.630+0.0047*photon_pt[j]) && photon_chiso[j]<0.441) ||
       (photon_hoe[j]<0.0396 && photon_nhiso[j]<(2.725+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j]) && photon_phoiso[j]<(2.571+0.0047*photon_pt[j]) && photon_chiso[j]<5*1.295 && photon_chiso[j]>1.295);
       /////////////////////////////////////////////////////////////////////////
       loose5 = photon_hoe[j]< 5*0.0597 && photon_nhiso[j]<5*(10.910+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j]) && photon_phoiso[j]<3.630+0.0047*photon_pt[j];*/
       medium = photon_hoe[j]<0.0396 && photon_nhiso[j]<2.725+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<2.571+0.0047*photon_pt[j];
       loose = photon_hoe[j]<0.0597 && photon_nhiso[j]<10.910+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<3.630+0.0047*photon_pt[j];
        if ( wjet && photon_cut[isprom] && tmp[isprom]) {
          /*if (loose5) {
            total[0]++;
            if (pho_pt[0]<photon_pt[j]){
              pho_pt[0]=photon_pt[j];
              flag[0]=j;
            }
          }*/
          if (medium) {
            total[0]++;
            if (pho_pt[0]<photon_pt[j]){
              pho_pt[0]=photon_pt[j];
              flag[0]=j;
            }
          }
          if (loose) {
            total[1]++;
            if (pho_pt[1]<photon_pt[j]){
              pho_pt[1]=photon_pt[j];
              flag[1]=j;
            }
          }
        }
      /*if ( j==5 && flag[0]!=100) {
        sieie_los5=photon_sieie[flag[0]];
        chiso_los5=photon_chiso[flag[0]];
        scalef0=scalef;
        los5tree->Fill();
      }*/
      if ( j==5 && flag[0]!=100) {
        sieie_med=photon_sieie[flag[0]];
        chiso_med=photon_chiso[flag[0]];
        scalef0=scalef;
        medtree->Fill();
        //cout<<sieie_los5<<"\t"<<sieie_los<<"\t"<<sieie_med<<endl;
      }
      if ( j==5 && flag[1]!=100) {
        sieie_los=photon_sieie[flag[1]];
        chiso_los=photon_chiso[flag[1]];
        scalef1=scalef;
        lostree->Fill();
      }
    }
  }
  opt->Write();
  //cout<<"loose5_total:"<<total[0]<<endl;
  cout<<"medium_total:"<<total[0]<<endl;
  cout<<"loose_total:"<<total[1]<<endl;
}
int produceroot(){
  /*Tt *t = new Tt("treeDumper/PKUCandidates");
  t->Add("../treePKU*.root");*/
  TFile *f=new TFile("outwa.root");
  TTree *t=(TTree*)f->Get("demo");
  slectree(t,0);
  f=new TFile("wajet.root");
  t=(TTree*)f->Get("demo");
  slectree(t,1);
  return 0;
}
