#include "fit.C"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;
Double_t lowpt[9]={25,30,35,40,45,50,60,80,120};
Double_t highpt[9]={30,35,40,45,50,60,80,120,400};
Double_t truedata[9]={673.346,431.562,308.228,209.455,172.462,232.315,212.123,132.004,80.4759};

void run_fit(){
	string str="";
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

	opf.close();
}


int main(){
	run_fit();
	return 0;
}
