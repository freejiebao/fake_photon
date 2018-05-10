#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void xx::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L xx.C
//      Root > xx t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();

  Long64_t npp = fChain->GetEntries("theWeight>0.");
  Long64_t nmm = fChain->GetEntries("theWeight<0.");
  std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;


	TFile * input1 = new TFile ("puweight.root");
        TH1* h = NULL;
        input1->GetObject("h2",h);


   Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries; jentry++) {
      //  for (Long64_t jentry=0; jentry<10000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
            // std::cout<<nb<<std::endl;
      // if (Cut(ientry) < 0) continue;


     if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu1<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;
     if(m_dataset=="outWAJJ.root"){ scalef=1000.*0.776/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outwa.root"){ scalef=1000.*178.6/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outwjet.root"){ scalef=1000.*61526.7/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outZJets.root"){ scalef=1000.*5765.4/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outZA.root"){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outTTA.root"){ scalef=1000.*3.697/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outTTJets.root"){ scalef=1000.*831.76/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outSTs.root"){ scalef=1000.*3.36/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outSTtbarw.root"){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outSTtw.root"){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outSTt.root"){ scalef=1000.*136.02/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outSTtbar.root"){ scalef=1000.*80.95/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outWW.root"){ scalef=1000.*118.7/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outWZ.root"){ scalef=1000.*47.13/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outZZ.root"){ scalef=1000.*16.523/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outDY.root"){ scalef=1000.*5765.4/float(npp-nmm)*fabs(theWeight)/theWeight; }
     if(m_dataset=="outW3Jets.root"){ scalef=1000.*942.3/float(npp-nmm)*fabs(theWeight)/theWeight; }

     if(m_dataset !="outSMu.root" && m_dataset !="outSEle.root")  {
        pileupWeight=h->GetBinContent(h->GetXaxis()->FindBin(npT));


//////////////////photon electron veto scalefactor
		if(photonet>10 && photonet<200)
		{
			if(fabs(photoneta)>0 && fabs(photoneta)<1.4442){scalef=scalef*0.9978;}
			if(fabs(photoneta)>1.566 && fabs(photoneta)<2.5){scalef=scalef*0.9931;}
		}

/*
//////////////////photon medium ID scalefactor
		if(photonet>20 && photonet<35)
		{
			if(photoneta>-2.5 && photoneta<-2){scalef=scalef*0.939;}
			if(photoneta>-2 && photoneta<-1.566){scalef=scalef*0.955;}
			if(photoneta>-1.444 && photoneta<-0.8){scalef=scalef*0.974;}
			if(photoneta>-0.8 && photoneta<0){scalef=scalef*0.963;}
			if(photoneta>0 && photoneta<0.8){scalef=scalef*0.966;}
			if(photoneta>0.8 && photoneta<1.444){scalef=scalef*0.978;}
			if(photoneta>1.566 && photoneta<2){scalef=scalef*0.95;}
			if(photoneta>2 && photoneta<2.5){scalef=scalef*0.934;}
		}
		if(photonet>35 && photonet<50)
		{
			if(photoneta>-2.5 && photoneta<-2){scalef=scalef*0.955;}
			if(photoneta>-2 && photoneta<-1.566){scalef=scalef*0.971;}
			if(photoneta>-1.444 && photoneta<-0.8){scalef=scalef*0.974;}
			if(photoneta>-0.8 && photoneta<0){scalef=scalef*0.961;}
			if(photoneta>0 && photoneta<0.8){scalef=scalef*0.97;}
			if(photoneta>0.8 && photoneta<1.444){scalef=scalef*0.977;}
			if(photoneta>1.566 && photoneta<2){scalef=scalef*0.971;}
			if(photoneta>2 && photoneta<2.5){scalef=scalef*0.96;}
		}
		if(photonet>50 && photonet<90)
		{
			if(photoneta>-2.5 && photoneta<-2){scalef=scalef*0.961;}
			if(photoneta>-2 && photoneta<-1.566){scalef=scalef*0.969;}
			if(photoneta>-1.444 && photoneta<-0.8){scalef=scalef*0.97;}
			if(photoneta>-0.8 && photoneta<0){scalef=scalef*0.953;}
			if(photoneta>0 && photoneta<0.8){scalef=scalef*0.958;}
			if(photoneta>0.8 && photoneta<1.444){scalef=scalef*0.968;}
			if(photoneta>1.566 && photoneta<2){scalef=scalef*0.966;}
			if(photoneta>2 && photoneta<2.5){scalef=scalef*0.96;}
		}
		if(photonet>90 && photonet<500)
		{
			if(photoneta>-2.5 && photoneta<-2){scalef=scalef*0.972;}
			if(photoneta>-2 && photoneta<-1.566){scalef=scalef*0.996;}
			if(photoneta>-1.444 && photoneta<-0.8){scalef=scalef*1.022;}
			if(photoneta>-0.8 && photoneta<0){scalef=scalef*0.992;}
			if(photoneta>0 && photoneta<0.8){scalef=scalef*1;}
			if(photoneta>0.8 && photoneta<1.444){scalef=scalef*1.019;}
			if(photoneta>1.566 && photoneta<2){scalef=scalef*0.993;}
			if(photoneta>2 && photoneta<2.5){scalef=scalef*1.02;}
		}
*/

double bf=0.54976;   double gh=0.45024;
	if(lep==13)
	{
//////////////////////muon tracking scalefactor
		if(fabs(etalep1)<0.20000004){scalef=scalef*0.9969965;}
                if(fabs(etalep1)>0.20000004 && fabs(etalep1)<0.40000002){scalef=scalef*0.9977118;}
                if(fabs(etalep1)>0.40000002 && fabs(etalep1)<0.59999999){scalef=scalef*0.9980776;}
                if(fabs(etalep1)>0.59999999 && fabs(etalep1)<0.80000004){scalef=scalef*0.9978039;}
                if(fabs(etalep1)>0.80000004 && fabs(etalep1)<1.00000003){scalef=scalef*0.9979708;}
                if(fabs(etalep1)>1.00000003 && fabs(etalep1)<1.20000008){scalef=scalef*0.9971477;}
                if(fabs(etalep1)>1.20000008 && fabs(etalep1)<1.40000008){scalef=scalef*0.9962274;}
                if(fabs(etalep1)>1.40000008 && fabs(etalep1)<1.60000003){scalef=scalef*0.9954786;}
                if(fabs(etalep1)>1.60000003 && fabs(etalep1)<1.80000004){scalef=scalef*0.9957808;}
                if(fabs(etalep1)>1.80000004 && fabs(etalep1)<2.00000004){scalef=scalef*0.9938919;}
                if(fabs(etalep1)>2.00000004 && fabs(etalep1)<2.20000001){scalef=scalef*0.9929427;}
                if(fabs(etalep1)>2.20000001 && fabs(etalep1)<2.4){scalef=scalef*0.9873133;}

//////////////////////muon trigger scalefactor
		if(ptlep1>26 && ptlep1<30)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.97493*bf+0.986981*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.951008*bf+0.96284*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.981343*bf+0.98392*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.899932*bf+0.913885*gh);}
		}
		if(ptlep1>30 && ptlep1<40)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.9784*bf+0.991048*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.961095*bf+0.971896*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.994604*bf+0.99655*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.941213*bf+0.948634*gh);}
		}
		if(ptlep1>40 && ptlep1<50)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.978602*bf+0.992596*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.962331*bf+0.974604*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.996797*bf+1.00213*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.953082*bf+0.962964*gh);}
		}
		if(ptlep1>50 && ptlep1<60)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.979472*bf+0.992018*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.962257*bf+0.975398*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.996425*bf+1.00241*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.954931*bf+0.967069*gh);}
		}
		if(ptlep1>60 && ptlep1<120)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.976239*bf+0.993243*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.959941*bf+0.970948*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.995473*bf+1.00316*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.943909*bf+0.962784*gh);}
		}
		if(ptlep1>120 && ptlep1<200)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.971637*bf+0.981393*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.940402*bf+0.954439*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(1.00587*bf+1.00509*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.972007*bf+0.983115*gh);}
		}
		if(ptlep1>200 && ptlep1<500)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.974591*bf+0.993894*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.927055*bf+0.977128*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.970003*bf+0.998426*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.903481*bf+0.935949*gh);}
		}
//////////////////////muon tight ID  and tight ISO scalefactor
		if(ptlep1>20 && ptlep1<25)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.980779*bf+0.993173*gh)*(0.987723*bf+0.981144*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.961656*bf+0.985596*gh)*(0.993162*bf+0.997662*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.982584*bf+0.990863*gh)*(0.989717*bf+0.993687*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.970229*bf+0.981501*gh)*(0.975341*bf+0.994233*gh);}
		}
		if(ptlep1>25 && ptlep1<30)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.979747*bf+0.98699*gh)*(0.993733*bf+0.992791*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.959323*bf+0.984686*gh)*(1.001*bf+0.999726*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.982259*bf+0.990917*gh)*(0.994223*bf+0.99796*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.969708*bf+0.979109)*(0.985961*bf+0.999098*gh);}
		}
		if(ptlep1>30 && ptlep1<40)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.981756*bf+0.987596*gh)*(0.994052*bf+0.993452*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.965162*bf+0.983914*gh)*(0.999295*bf+0.999598*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.984453*bf+0.992066*gh)*(0.997134*bf+0.99898*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.967787*bf+0.971526*gh)*(0.993083*bf+1.00006*gh);}
		}
		if(ptlep1>40 && ptlep1<50)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.982723*bf+0.989777*gh)*(0.995378*bf+0.9952*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.967988*bf+0.983265*gh)*(0.997179*bf+0.998324*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.987816*bf+0.993847*gh)*(0.997531*bf+0.998603*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.97077*bf+0.974776)*(0.99677*bf+1.00022*gh);}
		}
		if(ptlep1>50 && ptlep1<60)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.979586*bf+0.984749*gh)*(0.996878*bf+0.996716*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.969637*bf+0.980582*gh)*(0.999354*bf+0.998887*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.985261*bf+0.985655*gh)*(0.997972*bf+0.9988*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.967764*bf+0.967651*gh)*(0.997456*bf+1*gh);}
		}
		if(ptlep1>60 && ptlep1<120)
		{
			if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.992805*bf+0.99137*gh)*(0.998548*bf+0.999064*gh);}
			if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.967575*bf+0.983879*gh)*(0.999297*bf+0.998908*gh);}
			if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.988935*bf+0.989594*gh)*(0.999017*bf+0.999453*gh);}
			if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.963107*bf+0.963199*gh)*(1.00152*bf+1.00153*gh);}
		}
	}

	if(lep==11)
	{
//////////////////////electron reco scalefactor
		if(etalep1> -2.5 && etalep1<-2.45){scalef=scalef*1.3176;}
		if(etalep1> -2.45 && etalep1<-2.4){scalef=scalef*1.11378;}
		if(etalep1> -2.4 && etalep1<-2.3){scalef=scalef*1.02463;}
		if(etalep1> -2.3 && etalep1<-2.2){scalef=scalef*1.01364;}
		if(etalep1> -2.2 && etalep1<-2){scalef=scalef*1.00728;}
		if(etalep1> -2 && etalep1<-1.8){scalef=scalef*0.994819;}
		if(etalep1> -1.8 && etalep1<-1.63){scalef=scalef*0.994786;}
		if(etalep1> -1.63 && etalep1<-1.566){scalef=scalef*0.991632;}
		if(etalep1> -1.566 && etalep1<-1.444){scalef=scalef*0.963129;}
		if(etalep1> -1.444 && etalep1<-1.2){scalef=scalef*0.989701;}
		if(etalep1> -1.2 && etalep1<-1){scalef=scalef*0.985656;}
		if(etalep1> -1 && etalep1<-0.6){scalef=scalef*0.981595;}
		if(etalep1> -0.6 && etalep1<-0.4){scalef=scalef*0.984678;}
		if(etalep1> -0.4 && etalep1<-0.2){scalef=scalef*0.981614;}
		if(etalep1> -0.2 && etalep1<0){scalef=scalef*0.980433;}
		if(etalep1> 0 && etalep1<0.2){scalef=scalef*0.984552;}
		if(etalep1> 0.2 && etalep1<0.4){scalef=scalef*0.988764;}
		if(etalep1> 0.4 && etalep1<0.6){scalef=scalef*0.987743;}
		if(etalep1> 0.6 && etalep1<1){scalef=scalef*0.987743;}
		if(etalep1> 1 && etalep1<1.2){scalef=scalef*0.987743;}
		if(etalep1> 1.2 && etalep1<1.444){scalef=scalef*0.98768;}
		if(etalep1> 1.444 && etalep1<1.566){scalef=scalef*0.967598;}
		if(etalep1> 1.566 && etalep1<1.63){scalef=scalef*0.989627;}
		if(etalep1> 1.63 && etalep1<1.8){scalef=scalef*0.992761;}
		if(etalep1> 1.8 && etalep1<2){scalef=scalef*0.991761;}
		if(etalep1> 2 && etalep1<2.2){scalef=scalef*0.99794;}
		if(etalep1> 2.2 && etalep1<2.3){scalef=scalef*1.00104;}
		if(etalep1> 2.3 && etalep1<2.4){scalef=scalef*0.989507;}
		if(etalep1> 2.4 && etalep1<2.45){scalef=scalef*0.970519;}
		if(etalep1> 2.45 && etalep1< 2.5){scalef=scalef*0.906667;}

//////////////////////electron tight ID scalefactor
		if(ptlep1>10 && ptlep1<20)
		{
			if(etalep1>-2.5 && etalep1<-2){scalef=scalef*0.807;}
			if(etalep1>-2 && etalep1<-1.566){scalef=scalef*0.829;}
			if(etalep1>-1.566 && etalep1<-1.444){scalef=scalef*1.033;}
			if(etalep1>-1.444 && etalep1<-0.8){scalef=scalef*1.008;}
			if(etalep1>-0.8 && etalep1<0){scalef=scalef*0.941;}
			if(etalep1>0 && etalep1<0.8){scalef=scalef*0.946;}
			if(etalep1>0.8 && etalep1<1.444){scalef=scalef*0.990;}
			if(etalep1>1.444 && etalep1<1.566){scalef=scalef*1.034;}
			if(etalep1>1.566 && etalep1<2){scalef=scalef*0.827;}
			if(etalep1>2 && etalep1<2.5){scalef=scalef*0.797;}
		}
                if(ptlep1>20 && ptlep1<35)
		{
                        if(etalep1>-2.5 && etalep1<-2){scalef=scalef*0.882;}
                        if(etalep1>-2 && etalep1<-1.566){scalef=scalef*0.927;}
                        if(etalep1>-1.566 && etalep1<-1.444){scalef=scalef*1.008;}
                        if(etalep1>-1.444 && etalep1<-0.8){scalef=scalef*0.972;}
                        if(etalep1>-0.8 && etalep1<0){scalef=scalef*0.953;}
                        if(etalep1>0 && etalep1<0.8){scalef=scalef*0.982;}
                        if(etalep1>0.8 && etalep1<1.444){scalef=scalef*0.975;}
                        if(etalep1>1.444 && etalep1<1.566){scalef=scalef*0.975;}
                        if(etalep1>1.566 && etalep1<2){scalef=scalef*0.909;}
                        if(etalep1>2 && etalep1<2.5){scalef=scalef*0.863;}
		}
                if(ptlep1>35 && ptlep1<50)
		{
                        if(etalep1>-2.5 && etalep1<-2){scalef=scalef*0.919;}
                        if(etalep1>-2 && etalep1<-1.566){scalef=scalef*0.967;}
                        if(etalep1>-1.566 && etalep1<-1.444){scalef=scalef*0.988;}
                        if(etalep1>-1.444 && etalep1<-0.8){scalef=scalef*0.975;}
                        if(etalep1>-0.8 && etalep1<0){scalef=scalef*0.953;}
                        if(etalep1>0 && etalep1<0.8){scalef=scalef*0.978;}
                        if(etalep1>0.8 && etalep1<1.444){scalef=scalef*0.979;}
                        if(etalep1>1.444 && etalep1<1.566){scalef=scalef*0.98;}
                        if(etalep1>1.566 && etalep1<2){scalef=scalef*0.969;}
                        if(etalep1>2 && etalep1<2.5){scalef=scalef*0.938;}
		}
                if(ptlep1>50 && ptlep1<90)
		{
                        if(etalep1>-2.5 && etalep1<-2){scalef=scalef*0.94;}
                        if(etalep1>-2 && etalep1<-1.566){scalef=scalef*0.981;}
                        if(etalep1>-1.566 && etalep1<-1.444){scalef=scalef*0.995;}
                        if(etalep1>-1.444 && etalep1<-0.8){scalef=scalef*0.972;}
                        if(etalep1>-0.8 && etalep1<0){scalef=scalef*0.953;}
                        if(etalep1>0 && etalep1<0.8){scalef=scalef*0.978;}
                        if(etalep1>0.8 && etalep1<1.444){scalef=scalef*0.979;}
                        if(etalep1>1.444 && etalep1<1.566){scalef=scalef*0.98;}
                        if(etalep1>1.566 && etalep1<2){scalef=scalef*0.969;}
                        if(etalep1>2 && etalep1<2.5){scalef=scalef*0.938;}
		}
                if(ptlep1>90 && ptlep1<500)
		{
                        if(etalep1>-2.5 && etalep1<-2){scalef=scalef*1.051;}
                        if(etalep1>-2 && etalep1<-1.566){scalef=scalef*1.006;}
                        if(etalep1>-1.566 && etalep1<-1.444){scalef=scalef*1.104;}
                        if(etalep1>-1.444 && etalep1<-0.8){scalef=scalef*0.989;}
                        if(etalep1>-0.8 && etalep1<0){scalef=scalef*0.975;}
                        if(etalep1>0 && etalep1<0.8){scalef=scalef*1.012;}
                        if(etalep1>0.8 && etalep1<1.444){scalef=scalef*1.011;}
                        if(etalep1>1.444 && etalep1<1.566){scalef=scalef*1.007;}
                        if(etalep1>1.566 && etalep1<2){scalef=scalef*0.988;}
                        if(etalep1>2 && etalep1<2.5){scalef=scalef*1.021;}
		}

//////////////////////electron trigger scalefactor
		if(etalep1>-2.5 && etalep1<-2)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.3182096 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.7820068 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9318768 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*1.000077 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9870918 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*1.001992 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9936575 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9842311 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9907963 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9822313 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9707005 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9504389 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9624528 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9586949 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9391737 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.948074 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9443794 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.8885222 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9108052 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9350205 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9327958 ;}
			if(ptlep1>200){scalef=scalef*0.9719728 ;}
		}
		if(etalep1>-2 && etalep1<-1.8)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.5475377 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8283806 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9135174 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9029545 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9306931 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9243566 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.938806 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9448075 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9431488 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9454783 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9439244 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9431761 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9547325 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9415073 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9566987 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9220593 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9253467 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9447766 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9108052 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9350205 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9327958 ;}
			if(ptlep1>200){scalef=scalef*0.9719728 ;}
		}
		if(etalep1>-1.8 && etalep1<-1.566)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.6938331 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8352862 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.8587083 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.899146 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9253654 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9233223 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9198195 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.92685 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9297241 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9349895 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9518926 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9388806 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9448294 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9402492 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9289817 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9292382 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9440058 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.924945 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9108052 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9350205 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9327958 ;}
			if(ptlep1>200){scalef=scalef*0.9719728 ;}
		}
		if(etalep1>-1.566 && etalep1<-1.4442)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.6897396 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8503644 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.941945 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9886492 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9507815 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9585357 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9745861 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9802567 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9812833 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9965952 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9620197 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9600129 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.990295 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9621016 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9811452 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9504037 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*1.042705 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*1.0211 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9887272 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9449356 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9745761 ;}
			if(ptlep1>200){scalef=scalef*1.140692 ;}
		}
		if(etalep1>-1.4442 && etalep1<-1.1)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.6333747 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8003497 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.8862768 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.912227 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9357078 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9533795 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9580264 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.972843 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.977276 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9783739 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9837632 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9822462 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9790173 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.968755 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9732658 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9727969 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9774068 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9740885 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9987849 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9840915 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9806898 ;}
			if(ptlep1>200){scalef=scalef*0.9782041 ;}
		}
		if(etalep1>-1.1 && etalep1<-0.8)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.8166404 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.9074443 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9618506 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9715213 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9874655 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9916238 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9968492 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*1.001666 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*1.00499 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9991487 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.999807 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9985767 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9972746 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9903688 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9926456 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*1.002768 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9799505 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9966076 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9987849 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9840915 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9806898 ;}
			if(ptlep1>200){scalef=scalef*0.9782041 ;}
		}
		if(etalep1>-0.8 && etalep1<-0.6)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.8329575 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.9191953 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9563798 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9837372 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*1.009454 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*1.00294 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*1.013727 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*1.009487 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*1.016438 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*1.013889 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*1.012095 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*1.013824 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*1.004136 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.999871 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*1.00198 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9919166 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9949756 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.984424 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9863592 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9947541 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9781565 ;}
			if(ptlep1>200){scalef=scalef*0.9886977 ;}
		}
		if(etalep1>-0.6 && etalep1<-0.4)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.8752508 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8913705 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9387023 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9720112 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9944769 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.998752 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*1.010466 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*1.013707 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*1.015501 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*1.017263 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*1.016703 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*1.00338 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*1.010839 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9967599 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*1.000122 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.997751 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9929456 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9954594 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9863592 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9947541 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9781565 ;}
			if(ptlep1>200){scalef=scalef*0.9886977 ;}
		}
		if(etalep1>-0.4 && etalep1<-0.2)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.8274261 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.829784 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9068262 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9603051 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9680731 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9886557 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9904579 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*1.000361 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*1.006047 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*1.002173 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*1.0004 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*1.00328 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9979732 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9974181 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9891445 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*1.004661 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9974801 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9947351 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*1.008467 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9974332 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9961109 ;}
			if(ptlep1>200){scalef=scalef*0.9923206 ;}
		}
		if(etalep1>-0.2 && etalep1<0)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.724263 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.7907151 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.8669059 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9424832 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9574428 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9581608 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9844264 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9834529 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9946454 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9928963 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9948833 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9942179 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9966354 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9948582 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.980974 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9851322 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9998334 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9960083 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*1.008467 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9974332 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9961109 ;}
			if(ptlep1>200){scalef=scalef*0.9923206 ;}
		}
		if(etalep1>0 && etalep1<0.2)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.7217184 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.776099 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.8602316 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9256848 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9433902 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9489936 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9790693 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9874888 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9907391 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9899186 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9921989 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9836248 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9935923 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9992605 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.983616 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9899978 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9863723 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9826486 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9958808 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9795887 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9819741 ;}
			if(ptlep1>200){scalef=scalef*0.9780395 ;}
		}
		if(etalep1>0.2 && etalep1<0.4)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.759378 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8399172 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9080134 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9606896 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9634132 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9810522 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.974292 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9948505 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9946675 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9886543 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9931197 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9945845 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9918562 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9973431 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9846743 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9990344 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9822154 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9814618 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9958808 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9795887 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9819741 ;}
			if(ptlep1>200){scalef=scalef*0.9780395 ;}
		}
		if(etalep1>0.4 && etalep1<0.6)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.7232354 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8914133 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9339548 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9750587 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9863598 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9953613 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*1.00349 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*1.005288 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*1.014274 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*1.005719 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*1.00378 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9949885 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*1.00394 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9898361 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9777918 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9918221 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9930619 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9759932 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9930485 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9833286 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9891159 ;}
			if(ptlep1>200){scalef=scalef*0.9767458 ;}
		}
		if(etalep1>0.6 && etalep1<0.8)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.7348906 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.9260836 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9643677 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9869978 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9954782 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9955152 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*1.003092 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*1.018057 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*1.012396 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*1.007094 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*1.00942 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*1.002906 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*1.001554 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9980376 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*1.000318 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9811135 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9812834 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9843192 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9930485 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9833286 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9891159 ;}
			if(ptlep1>200){scalef=scalef*0.9767458 ;}
		}
		if(etalep1>0.8 && etalep1<1.1)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.6535427 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8939303 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9499141 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9779471 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9922779 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9927418 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*1.003308 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*1.006136 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*1.009423 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*1.005662 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*1.002433 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9991196 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*1.000173 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*1.000295 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9832635 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*1.000598 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9812558 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9919686 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*1.00463 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9880177 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9800646 ;}
			if(ptlep1>200){scalef=scalef*0.9744108 ;}
		}
		if(etalep1>1.1 && etalep1<1.4442)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.481539 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.7911923 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.8546475 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.905308 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9393054 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9450492 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9543536 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9651092 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9677254 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9758279 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9747216 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9839951 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9758868 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9832197 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9764721 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9874786 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*1.006655 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9906609 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*1.00463 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9880177 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9800646 ;}
			if(ptlep1>200){scalef=scalef*0.9744108;}
		}
		if(etalep1>1.4442 && etalep1<1.566)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.5783245 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8095429 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.9211123 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9407769 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9784723 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.975853 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9765796 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9891219 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9716365 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9966245 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9862242 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9764449 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9901218 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*1.009997 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9449676 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.925542 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*1.002228 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9900139 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9416501 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9767487 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*1.018561 ;}
			if(ptlep1>200){scalef=scalef*0.9253919 ;}
		}
		if(etalep1>1.566 && etalep1<1.8)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.5992121 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.8120483 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.8621458 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9033502 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9061232 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9380579 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9260212 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9432188 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9430979 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9508256 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9583072 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9446247 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9487005 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9577731 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9671014 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9209678 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9488215 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9091881 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9433161 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9476371 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9332212 ;}
			if(ptlep1>200){scalef=scalef*0.9388933 ;}
		}
		if(etalep1>1.8 && etalep1<2)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.4278183 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.7848874 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.8645481 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.9087641 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9040279 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.92636 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9169484 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9283603 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9380797 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9455874 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9360457 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9228125 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9454661 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.9191471 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9540949 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9452076 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9338838 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9053882 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9433161 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9476371 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9332212 ;}
			if(ptlep1>200){scalef=scalef*0.9388933 ;}
		}
		if(etalep1>2 && etalep1<2.5)
		{
			if(ptlep1>25 && ptlep1<28){scalef=scalef*0.2340308 ;}
			if(ptlep1>28 && ptlep1<30){scalef=scalef*0.6774325 ;}
			if(ptlep1>30 && ptlep1<32){scalef=scalef*0.8545982 ;}
			if(ptlep1>32 && ptlep1<34){scalef=scalef*0.903678 ;}
			if(ptlep1>34 && ptlep1<36){scalef=scalef*0.9396367 ;}
			if(ptlep1>36 && ptlep1<38){scalef=scalef*0.9444682 ;}
			if(ptlep1>38 && ptlep1<40){scalef=scalef*0.9614405 ;}
			if(ptlep1>40 && ptlep1<42){scalef=scalef*0.9634999 ;}
			if(ptlep1>42 && ptlep1<44){scalef=scalef*0.9672737 ;}
			if(ptlep1>44 && ptlep1<46){scalef=scalef*0.9538873 ;}
			if(ptlep1>46 && ptlep1<48){scalef=scalef*0.9560533 ;}
			if(ptlep1>48 && ptlep1<50){scalef=scalef*0.9607124 ;}
			if(ptlep1>50 && ptlep1<55){scalef=scalef*0.9461641 ;}
			if(ptlep1>55 && ptlep1<60){scalef=scalef*0.935406 ;}
			if(ptlep1>60 && ptlep1<65){scalef=scalef*0.9621278 ;}
			if(ptlep1>65 && ptlep1<70){scalef=scalef*0.9279007 ;}
			if(ptlep1>70 && ptlep1<80){scalef=scalef*0.9194907 ;}
			if(ptlep1>80 && ptlep1<90){scalef=scalef*0.9316405 ;}
			if(ptlep1>90 && ptlep1<100){scalef=scalef*0.9433161 ;}
			if(ptlep1>100 && ptlep1<120){scalef=scalef*0.9476371 ;}
			if(ptlep1>120 && ptlep1<200){scalef=scalef*0.9332212 ;}
			if(ptlep1>200){scalef=scalef*0.9388933 ;}
		}


	}

	}


   ExTree->Fill();

   }

   input1->Close();
}
