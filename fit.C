#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
#include <sstream>

using namespace std;
using namespace RooFit;

Double_t lowp[9]={25,30,35,40,45,50,60,80,120};
Double_t highp[9]={30,35,40,45,50,60,80,120,400};
//Double_t meddata[9]={673.346,431.562,308.228,209.455,172.462,232.315,212.123,132.004,80.4759};
//Double_t meddata[9]={356.436,244.029,175.853,128.387,95.3019,135.169,147.579,114.372,74.5076};//in fact, its pure data of loose id, not medium
//Double_t meddata[9]={361.847,248.008,178.256,130.466,96.4932,137.189,149.405,116.126,74.6354};//in fact, its pure data of 5*loose id, not medium
//Double_t meddata[9]={343.789,235.839,170.433,124.252,92.1307,131.857,143.057,111.314,73.2027};//medium
//Double_t meddata[9]={800.004,348.874,215.735,120.683,85.2058,99.335,66.5427,52.2641,12.6274};//medium fake
//Double_t meddata[9]={1711.46,823.544,497.428,298.87,193.573,250.71,186.389,160.47,58.2073};//5*loose fake
Double_t meddata[9]={1071.14,465.244,280.952,162.624,120.507,139.548,94.9723,91.7217,27.3025};//loose fake
Double_t losdata[9]={696.836,442.904,318.863,215.68,176.689,238.755,216.645,135.062,82.8212};

Double_t chilow[32]={3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,9,9,9,10,10};
Double_t chihigh[32]={5,7,9,11,13,15,6,8,10,12,14,7,9,11,13,15,8,10,12,14,9,11,13,15,10,12,14,11,13,15,12,14};

string fit(TH1F* hdata_, TH1F* htrue_, TH1F* hfake_, int k, int sideband){

	/*TFile* fdata = TFile::Open(Form("wajet_%0.f_%0.f_data.root", lowp[k], highp[k]));
	TFile* ftrue = TFile::Open(Form("wa_%0.f_%0.f_true.root", lowp[k], highp[k]));
//	TFile* ftrue = TFile::Open(Form("../fit_produce/ZA_%0.f_%0.f_true.root", lowp[k], highp[k]));
	TFile* ffake = TFile::Open(Form("wajet_%0.f_%0.f_fake.root", lowp[k], highp[k]));
//	TFile* ffake = TFile::Open(Form("../fit_produce/ZJets_FX_%0.f_%0.f_fake.root", lowp[k], highp[k]));

	TH1F* hdata_ = (TH1F*)fdata->Get("histo");
	TH1F* htrue_ = (TH1F*)ftrue->Get("histo");
	TH1F* hfake_ = (TH1F*)ffake->Get("histo");
*/
  ofstream opf(Form("source_%.f_%.f",lowp[k],highp[k]),ios::app);
	string str="";
	Int_t nBins = 9;
	Double_t bins[10];
	for (Int_t i=0;i<10;i++){
		bins[i] = 0.0040 + 0.002*i;
	}

	TH1* hdata = hdata_->Rebin(nBins, "hdata", bins);
	TH1* htrue = htrue_->Rebin(nBins, "htrue", bins);
	TH1* hfake = hfake_->Rebin(nBins, "hfake", bins);
	for (Int_t i=0; i<10; i++){
		cout<<hdata->GetBinContent(i)<<endl;
		cout<<htrue->GetBinContent(i)<<endl;
		cout<<hfake->GetBinContent(i)<<endl;
	}

	for (Int_t i=0; i<nBins; i++){
		if (hdata->GetBinContent(i+1)<=0) hdata->SetBinContent(i+1,0.000000);
		if (htrue->GetBinContent(i+1)<=0) htrue->SetBinContent(i+1,0.000000);
		if (hfake->GetBinContent(i+1)<=0) hfake->SetBinContent(i+1,0.000000);
	}

	Double_t nData = hdata->GetSumOfWeights();
	RooRealVar sieie("sieie", "sieie", 0.0040, 0.0180);


	RooDataHist data_hist("datahist", "datahist", sieie, hdata);
	RooDataHist true_hist("truehist", "truehist", sieie, htrue);
	RooDataHist fake_hist("fakehist", "fakehist", sieie, hfake);

	RooHistPdf true_pdf("truepdf", "truepdf", sieie, true_hist);
	RooHistPdf fake_pdf("fakepdf", "fakepdf", sieie, fake_hist);

	RooRealVar nTrue("true number", "true number", 0.5*nData, 0, nData);
	RooRealVar nFake("fake number", "fake number", 0.5*nData, 0, nData);

	RooExtendPdf etrue_pdf("ntrue", "ntrue", true_pdf, nTrue);
	RooExtendPdf efake_pdf("nfake", "nfake", fake_pdf, nFake);

	RooAddPdf fullpdf("full_pdf", "true_plus_fake", RooArgList(etrue_pdf,efake_pdf));

	fullpdf.fitTo(data_hist, SumW2Error(kFALSE), Extended(kTRUE));
	RooChi2Var chi2("chi2", "chi2", fullpdf, data_hist);
	Double_t chi2ToNDF = chi2.getVal() / (nBins - 2);

	RooPlot* xframe = sieie.frame(Title(Form("Barrel region, %0.f GeV < photon PT < %0.f GeV,  %0.f < chiso < %0.f",lowp[k], highp[k],chilow[sideband],chihigh[sideband])), Bins(nBins));
	data_hist.plotOn(xframe);
	fullpdf.plotOn(xframe, Name("sum"), LineColor(kRed));
	fullpdf.plotOn(xframe, Components("ntrue"), Name("true"),LineColor(kGreen), LineStyle(9));
	fullpdf.plotOn(xframe, Components("nfake"), Name("fake"),LineColor(kBlue), LineStyle(9));


	TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
	xframe->GetXaxis()->SetTitle("#sigma_{i#etai#eta}");
	xframe->GetYaxis()->SetTitleOffset(1.4);
	xframe->Draw();


	hdata->SetLineColor(kRed);
	hdata->SetLineWidth(3);
	hfake->SetLineColor(kBlue);
	hfake->SetLineStyle(5);
	hfake->SetLineWidth(3);
	htrue->SetLineColor(kGreen);
	htrue->SetLineStyle(5);
	htrue->SetLineWidth(3);
	TLegend *leg = new TLegend(0.7, 0.8, 0.88, 0.88, NULL, "brNDC");
	leg->SetFillColor(10);
	leg->AddEntry(hdata, "Fit result", "L");
	leg->AddEntry(htrue, "Ture photons", "L");
	leg->AddEntry(hfake, "Fake photons", "L");
	leg->Draw("same");


	TString strChi = "#chi^{2}/ndf=";
	float chiFloat = (100 * chi2ToNDF);
	int chiInt = chiFloat;
	strChi += (chiInt / 100);
	strChi += ".";
	strChi += (chiInt % 100);
	TLatex *textChi2 = new TLatex(0.7, 0.75, strChi);
	textChi2->SetNDC();
	textChi2->SetTextSize(0.03);
	textChi2->SetLineWidth(1);
	textChi2->Draw();




	Double_t nDataInWindowErr = 0.;
	Double_t nDataInWindow_1 = hdata->Integral(1,1);
        Double_t nDataInWindow_2 = hdata->Integral(2,2);
        Double_t nDataInWindow_3 = hdata->Integral(3,3);
        Double_t nDataInWindow_4 = hdata->Integral(4,4);
        Double_t nDataInWindow_5 = hdata->Integral(5,5);
        Double_t nDataInWindow_6 = hdata->Integral(6,6);
	Double_t nDataInWindow_7 = hdata->Integral(7,7);
	Double_t nDataInWindow = hdata->IntegralAndError(2,nBins/3,nDataInWindowErr);
	cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
					 cout<<"hdata(1)_lowedge:"<<hdata->GetBinLowEdge(1)<<"\t"<<"hdata(1)_content:"<<hdata->GetBinContent(1)<<endl;
	Double_t nDatatotal = hdata->Integral();
	Double_t nTrue_fit = nTrue.getVal();
	Double_t nTrue_fitErr = nTrue.getError();
	Double_t nFake_fit = nFake.getVal();
	Double_t nFake_fitErr = nFake.getError();
	sieie.setRange("window",0.0062,0.0102);
	RooRealVar* fracFake = (RooRealVar*)efake_pdf.createIntegral(sieie,sieie,"window");
	Double_t nFake_inwindow = nFake_fit*fracFake->getVal();
	Double_t nFake_inwindowErr = sqrt(nFake_fitErr*nFake_fitErr*fracFake->getVal()*fracFake->getVal()+
										nFake_fit*nFake_fit*fracFake->getError()*fracFake->getError());
	RooRealVar* fracTrue = (RooRealVar*)etrue_pdf.createIntegral(sieie,sieie,"window");
	Double_t nTrue_inwindow = nTrue_fit*fracTrue->getVal();
	Double_t nTrue_inwindowErr = sqrt(nTrue_fitErr*nTrue_fitErr*fracTrue->getVal()*fracTrue->getVal()+
										nTrue_fit*nTrue_fit*fracTrue->getError()*fracTrue->getError());

	Double_t fakerate = nFake_inwindow/nDataInWindow;
	Double_t fakerateErr = sqrt(nFake_inwindowErr*nFake_inwindowErr/(nDataInWindow*nDataInWindow)
								+ nFake_inwindow*nFake_inwindow*nDataInWindowErr*nDataInWindowErr/(nDataInWindow
									*nDataInWindow*nDataInWindow*nDataInWindow));

	ofstream myfile(TString("fakerate_") + Form("photon_pt%0.f_%0.f_chiso_%0.f_%0.f.txt", lowp[k], highp[k],chilow[sideband],chihigh[sideband]),ios::out);

	myfile << "data in window = " << nDataInWindow << "+-" << nDataInWindowErr <<" "<<nDataInWindow_1<<" "<<nDataInWindow_2<<" "<<nDataInWindow_3<<" "<<nDataInWindow_4<<" "<<nDataInWindow_5<<" "<<nDataInWindow_6<<" "<<nDataInWindow_7<<std::endl;
	myfile << "nDatatotal = " << nDatatotal << std::endl;
	myfile << "fake number = "<< nFake_fit << "+-" <<nFake_fitErr <<std::endl;
	myfile << "true number = "<< nTrue_fit << "+-" << nTrue_fitErr <<std::endl;
	myfile << "fake in window = "<< nFake_inwindow << "+-" <<nFake_inwindowErr <<std::endl;
	myfile << "true in window = "<< nTrue_inwindow << "+-" <<nTrue_inwindowErr <<std::endl;
	myfile << "fakerate = " << fakerate << "+-" <<fakerateErr <<std::endl;
	myfile << "chi2ToNDF = " << chi2ToNDF <<std::endl;

	string str1="",str2="";
	stringstream ss;
	ss.clear();
	ss<<nFake_fit;
	ss>>str1;
	ss.clear();
	ss<<nFake_fitErr;
	ss>>str2;
	ss.clear();
	str1=str1+" "+str2;
	ss<<meddata[k];
	ss>>str2;
	ss.clear();
	str1=str1+" "+str2;
	cout<<str1<<"Hhhhhhhhhhhh"<<endl;
  opf<<str1<<endl;
  opf.close();
	TString strFR = "FR = (";
        float FRFloat = (1000 * fakerate);
        int FRInt = FRFloat;
        strFR += (FRInt/10);
        strFR += ".";
        strFR += (FRInt%10);
        strFR += "+-";
        float FRErrFloat = (1000 * fakerateErr);
        int FRErrInt = FRErrFloat;
        strFR += (FRErrInt/10);
        strFR += ".";
        strFR += (FRErrInt%10);
        strFR += ")%";
        TLatex *textFR = new TLatex(0.67,0.7,strFR);
        textFR->SetNDC();
        textFR->SetTextSize(0.03);
        textFR->SetLineWidth(1);
        textFR->Draw();

	char buffer[256];
	sprintf(buffer, "pt_%0.f_%0.f_sideband_%0.f_%0.f.png",lowp[k],highp[k],chilow[sideband],chihigh[sideband]);
	c1->SaveAs(buffer);

/*	TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);
	c2->cd();

	gStyle->SetOptStat(0);
	hfake->SetLineStyle(1);
	htrue->SetLineStyle(1);
	htrue -> SetTitle(Form("template comparision: pt %0.f_%0.f",lowp[k],highp[k]));
  htrue -> DrawNormalized("Hist,e");
	hfake -> SetTitle("template comparision");
	hfake -> DrawNormalized("Hist,same,e");

	TLegend *leg2 = new TLegend(0.5, 0.8, 0.68, 0.88, NULL, "brNDC");
	leg2->SetFillColor(10);
	leg2->AddEntry(htrue, "Ture photons", "L");
	leg2->AddEntry(hfake, "Fake photons", "L");
	leg2->Draw("same");
	c2->SaveAs(Form("%0.f_%0.fnormalized.png",lowp[k],highp[k]));*/
  return str1;
}
