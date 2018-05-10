#include "xx.h"
#include "xx.C"
void runxx() {
//gROOT->LoadMacro("xx.C");
TString dir= "../";
//TString dir= "/eos/uscms/store/user/qhuang2/SingleMuon/SMu16G-v1/170116_132215/";


ifstream infile("filelist");
string buffer;
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains(".root")==0) {k=-2; continue;}
TString outname="out"+infilename;

cout<<outname<<endl;

TFile *file1 =new TFile(dir+infilename);
TDirectory *dir1 = (TDirectory*)file1->Get("treeDumper");
TTree *tree1 = (TTree*) dir1->Get("PKUCandidates");
xx m1(tree1,outname);
m1.Loop();
m1.endJob();

}

}
