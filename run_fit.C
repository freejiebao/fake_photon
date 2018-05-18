#include "fit.C"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Double_t lowpt[9]={25,30,35,40,45,50,60,80,120};
Double_t highpt[9]={30,35,40,45,50,60,80,120,400};
Double_t truedata[9]={673.346,431.562,308.228,209.455,172.462,232.315,212.123,132.004,80.4759};
Double_t chisolow[32]={3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,9,9,9,10,10};
Double_t chisohigh[32]={5,7,9,11,13,15,6,8,10,12,14,7,9,11,13,15,8,10,12,14,9,11,13,15,10,12,14,11,13,15,12,14};
string lie[]={"5","6","7","8","9","10","11","12","13","14","15"};

string change(Double_t test);
void closure(int k);
void tryfit(int k);
void run_fit();


int main(){
	run_fit();
	return 0;
}

string change(Double_t test){
	string str1;
	stringstream ss;
	ss.clear();
	ss<<test;
	ss>>str1;
	return str1;
}

void closure(int k){
	string val[11][8]={{"*","*","*","*","*","*","*","*"},
										 {"*","*","*","*","*","*","*","*"},
									   {"*","*","*","*","*","*","*","*"},
									   {"*","*","*","*","*","*","*","*"},
								     {"*","*","*","*","*","*","*","*"},
							       {"*","*","*","*","*","*","*","*"},
						         {"*","*","*","*","*","*","*","*"},
					           {"*","*","*","*","*","*","*","*"},
				             {"*","*","*","*","*","*","*","*"},
			               {"*","*","*","*","*","*","*","*"},
		                 {"*","*","*","*","*","*","*","*"}};
	Int_t sum=0;
  ifstream in(Form("source_%.f_%.f",lowpt[k],highpt[k]));
  ofstream out(Form("closure_%.f_%.f",lowpt[k],highpt[k]));
  string line,pt;
  stringstream ss;
  Double_t fit=0.,error=0.,data=0.;
	Double_t test[32];

  if(in){
    while(getline(in,line)){
        ss<<line;
        ss>>fit>>error>>data;
        test[sum]=TMath::Abs(fit-data)/error;
        //cout<<test<<endl;
      //i++;
      ss.clear();
			sum++;
    }
  }else{
    cout<<"no such file"<<endl;
  }

	val[0][0]=Form("%.3f",test[0]);
	val[2][0]=Form("%.3f",test[1]);
	val[4][0]=Form("%.3f",test[2]);
	val[6][0]=Form("%.3f",test[3]);
	val[8][0]=Form("%.3f",test[4]);
	val[10][0]=Form("%.3f",test[5]);

	val[1][1]=Form("%.3f",test[6]);
	val[3][1]=Form("%.3f",test[7]);
	val[5][1]=Form("%.3f",test[8]);
	val[7][1]=Form("%.3f",test[9]);
	val[9][1]=Form("%.3f",test[10]);

	val[2][2]=Form("%.3f",test[11]);
	val[4][2]=Form("%.3f",test[12]);
	val[6][2]=Form("%.3f",test[13]);
	val[8][2]=Form("%.3f",test[14]);
	val[10][2]=Form("%.3f",test[15]);

	val[3][3]=Form("%.3f",test[16]);
	val[5][3]=Form("%.3f",test[17]);
	val[7][3]=Form("%.3f",test[18]);
	val[9][3]=Form("%.3f",test[19]);

	val[4][4]=Form("%.3f",test[20]);
	val[6][4]=Form("%.3f",test[21]);
	val[8][4]=Form("%.3f",test[22]);
	val[10][4]=Form("%.3f",test[23]);

	val[5][5]=Form("%.3f",test[24]);
	val[7][5]=Form("%.3f",test[25]);
	val[9][5]=Form("%.3f",test[26]);

	val[6][6]=Form("%.3f",test[27]);
  val[8][6]=Form("%.3f",test[28]);
  val[10][6]=Form("%.3f",test[29]);

	val[7][7]=Form("%.3f",test[30]);
	val[9][7]=Form("%.3f",test[31]);
  out<<"loose id, pt:"<<lowpt[k]<<"-"<<highpt[k]<<endl;
	//out<<" "<<"\t"<<"3"<<"\t"<<"4"<<"\t"<<"5"<<"\t"<<"6"<<"\t"<<"7"<<"\t"<<"8"<<"\t"<<"9"<<"\t"<<"10"<<"\t"<<endl;
	for(int q=0; q<11; q++){
		for(int p=0; p<8; p++){
			out<<val[q][p]<<"\t";
		}
		out<<endl;
	}
	in.close();
	out.close();
}

void tryfit(int k) {
	TFile* fdata = TFile::Open(Form("wajet_%0.f_%0.f_data.root", lowpt[k], highpt[k]));
	TFile* ftrue = TFile::Open(Form("wa_%0.f_%0.f_true.root", lowpt[k], highpt[k]));
//	TFile* ftrue = TFile::Open(Form("../fit_produce/ZA_%0.f_%0.f_true.root", lowpt, highpt));
	TFile* ffake = TFile::Open(Form("wajet_%0.f_%0.f_fake.root", lowpt[k], highpt[k]));
//	TFile* ffake = TFile::Open(Form("../fit_produce/ZJets_FX_%0.f_%0.f_fake.root", lowpt, highpt));

	TH1F* hdata_ = (TH1F*)fdata->Get("histo");
	TH1F* htrue_ = (TH1F*)ftrue->Get("histo");
	TH1F* hfake[32];
	for (Int_t i = 0; i < 32; i++) {
		hfake[i] = (TH1F*)ffake->Get(Form("chiso %0.f %0.f %0.d", chisolow[i], chisohigh[i], i+1));
		fit(hdata_,htrue_,hfake[i],k,i);
	}
	closure(k);
}

void run_fit(){
	/*string str="";
	ofstream opf("closure",ios::out);

	str=fit(25,30);
	str+=" 696.836";
	opf<<str<<endl;
  str="";

	str=fit(30,35);
	str+=" 442.904";
	opf<<str<<endl;
  str="";

	str=fit(35,40);
	str+=" 318.863";
	opf<<str<<endl;
  str="";

	str=fit(40,45);
	str+=" 215.68";
	opf<<str<<endl;
  str="";

	str=fit(45,50);
	str+=" 176.689";
	opf<<str<<endl;
  str="";

	str=fit(50,60);
	str+=" 238.755";
	opf<<str<<endl;
  str="";

	str=fit(60,80);
	str+=" 216.645";
	opf<<str<<endl;
  str="";

	str=fit(80,120);
	str+=" 135.062";
	opf<<str<<endl;
  str="";

	str=fit(120,400);
	str+=" 82.8212";
	opf<<str<<endl;
  str="";

	opf.close();*/
	for (int i=0; i<9; i++){
		tryfit(i);
	}
}
