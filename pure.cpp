void slectree(TTree* t1, Int_t isprom){
  Int_t count1=0,count2=0,count3=0;
  TTree *t;
  t=t1;
  Int_t lep_;
  Int_t nlooseeles_;
  Int_t nloosemus_;
  Double_t mtVlepJECnew_;
  Double_t ptlep1_;
  Double_t etalep1_;
  Double_t MET_et_;
  Int_t photon_isprompt_[6];
  Double_t photon_drla_[6];
  Double_t photon_hoe_[6];
  Double_t photon_nhiso_[6];
  Double_t photon_phoiso_[6];
  Double_t photon_chiso_[6];
  Double_t photon_sieie_[6];
  Double_t photon_pt_[6];
  Double_t photon_eta_[6];
  Double_t scalef_;
  t->SetBranchAddress("scalef",&scalef_);
  t->SetBranchAddress("lep",&lep_);
  t->SetBranchAddress("nlooseeles",&nlooseeles_);
  t->SetBranchAddress("nloosemus",&nloosemus_);
  t->SetBranchAddress("mtVlepJECnew",&mtVlepJECnew_);
  t->SetBranchAddress("ptlep1",&ptlep1_);
  t->SetBranchAddress("etalep1",&etalep1_);
  t->SetBranchAddress("MET_et",&MET_et_);
  t->SetBranchAddress("photon_isprompt",photon_isprompt_);
  t->SetBranchAddress("photon_drla",photon_drla_);
  t->SetBranchAddress("photon_hoe",photon_hoe_);
  t->SetBranchAddress("photon_nhiso",photon_nhiso_);
  t->SetBranchAddress("photon_phoiso",photon_phoiso_);
  t->SetBranchAddress("photon_chiso",photon_chiso_);
  t->SetBranchAddress("photon_sieie",photon_sieie_);
  t->SetBranchAddress("photon_pt",photon_pt_);
  t->SetBranchAddress("photon_eta",photon_eta_);

  TFile *opt;
  if (isprom == 0){
    opt=new TFile("wapure.root","recreate");
  }
  if ( isprom == 1) {
    opt=new TFile("wjetspure.root","recreate");
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

  TTree *demo=new TTree("demo","demo");
  demo->Branch("lep",&lep,"lep/I");
  demo->Branch("nlooseeles",&nlooseeles,"nlooseeles/I");
  demo->Branch("nloosemus",&nloosemus,"nloosemus/I");
  demo->Branch("mtVlepJECnew",&mtVlepJECnew,"mtVlepJECnew/D");
  demo->Branch("ptlep1",&ptlep1,"ptlep1/D");
  demo->Branch("etalep1",&etalep1,"etalep1/D");
  demo->Branch("MET_et",&MET_et,"MET_et/D");
  demo->Branch("scalef",&scalef,"scalef/D");
  demo->Branch("photon_isprompt",photon_isprompt,"photon_isprompt[6]/I");
  demo->Branch("photon_drla",photon_drla,"photon_drla[6]/D");
  demo->Branch("photon_hoe",photon_hoe,"photon_hoe[6]/D");
  demo->Branch("photon_nhiso",photon_nhiso,"photon_nhiso[6]/D");
  demo->Branch("photon_phoiso",photon_phoiso,"photon_phoiso[6]/D");
  demo->Branch("photon_chiso",photon_chiso,"photon_chiso[6]/D");
  demo->Branch("photon_sieie",photon_sieie,"photon_sieie[6]/D");
  demo->Branch("photon_pt",photon_pt,"photon_pt[6]/D");
  demo->Branch("photon_eta",photon_eta,"photon_eta[6]/D");

  Int_t flag=0;
  Long64_t n=t->GetEntries();
  for(Long64_t i=0; i<n; i++){
    t->GetEntry(i);
    if(isprom==0){
      for (int j=0; j<6; j++) {
        //cout<<"i:"<<i<<"\t"<<"j:"<<j<<"\t"<<photon_isprompt[j]<<endl;
       if (photon_isprompt_[j]==1) {
         flag++;
        }
      }
      //cout<<"flag:"<<flag<<endl;
      if (flag!=0){
        lep=lep_;
        nlooseeles=nlooseeles_;
        nloosemus=nloosemus_;
        mtVlepJECnew=mtVlepJECnew_;
        ptlep1=ptlep1_;
        etalep1=etalep1_;
        MET_et=MET_et_;
        scalef=scalef_;
        for(int k=0; k<6; k++){
          photon_isprompt[k]=photon_isprompt_[k];
          photon_drla[k]=photon_drla_[k];
          photon_hoe[k]=photon_hoe_[k];
          photon_nhiso[k]=photon_nhiso_[k];
          photon_phoiso[k]=photon_phoiso_[k];
          photon_chiso[k]=photon_chiso_[k];
          photon_sieie[k]=photon_sieie_[k];
          photon_pt[k]=photon_pt_[k];
          photon_eta[k]=photon_eta_[k];
        }
        count1++;
        //cout<<"position of first true photon:"<<j<<endl;
        demo->Fill();
      }
    }

    if(isprom==1){
      for (int p=0; p<6; p++) {
       if (photon_isprompt_[p]!=1) {
         flag++;
       }
      }
      if (flag==6){
         lep=lep_;
         nlooseeles=nlooseeles_;
         nloosemus=nloosemus_;
         mtVlepJECnew=mtVlepJECnew_;
         ptlep1=ptlep1_;
         etalep1=etalep1_;
         MET_et=MET_et_;
         scalef=scalef_;
         for(int q=0; q<6; q++){
           photon_isprompt[q]=photon_isprompt_[q];
           photon_drla[q]=photon_drla_[q];
           photon_hoe[q]=photon_hoe_[q];
           photon_nhiso[q]=photon_nhiso_[q];
           photon_phoiso[q]=photon_phoiso_[q];
           photon_chiso[q]=photon_chiso_[q];
           photon_sieie[q]=photon_sieie_[q];
           photon_pt[q]=photon_pt_[q];
           photon_eta[q]=photon_eta_[q];
         }
         count1++;
         demo->Fill();
       }
    }
    flag=0;
  }
  opt->Write();
  cout<<"total entries:"<<n<<"\t"<<"after filter, the left entries:"<<count1<<endl;
}

int pure(){
  /*Tt *t = new Tt("treeDumper/PKUCandidates");
  t->Add("../treePKU*.root");*/
  TFile *f=new TFile("outwa.root");
  TTree *t=(TTree*)f->Get("demo");
  slectree(t,0);

  TFile *f1=new TFile("outwjet.root");
  TTree *t1=(TTree*)f1->Get("demo");
  slectree(t1,1);

  return 0;
}
