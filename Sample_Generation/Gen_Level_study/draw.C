#include "TMath.h"

void draw() {

double XMIN = -1;
double XMAX = -1;
double YMIN = -1;
long YMAX   = 100;
int rebin=1;


/*
h1_typeLL 
h1_typeLN 
h1_typeP 
h1_phoPt 
h1_phoPt_HAD 
h1_phoPt_FSR 
h1_nDauZ 
h1_nDauW 
h1_mZDau 
h1_mZDauLL
h1_mWDau 
h1_mWDauLL
*/



// --Lumi and xsec
	const double Lumi         = 150000.0;
	

// --read file,hist
	TFile *fscheme1        = TFile::Open("output/scheme1.root")     ;
	TFile *fscheme2        = TFile::Open("output/scheme2.root")     ;
	TFile *fscheme3		   = TFile::Open("output/scheme3.root")     ;
	TFile *fscheme4		   = TFile::Open("output/scheme4.root")     ;

	//TFile *fscheme4_wm     = TFile::Open("scheme4_wm.root")     ;
	//TFile *fscheme4_wp     = TFile::Open("scheme4_wp.root")     ;


	TString baseBranch = "GenInfo";

	//TString Branchname = "phoPt"; XMAX=100; XMIN=0; rebin=2; YMAX=300;YMIN=-100;
	//TString Branchname = "phoPt_HAD"; XMAX=100; XMIN=0; rebin=5; YMAX=200; YMIN=-50;
	//TString Branchname = "phoPt_FSR"; XMAX=100; XMIN=0; rebin=1; YMAX=100; YMIN=-50;
	//TString Branchname = "mZDau"; XMAX=140; XMIN=60; rebin=1; YMAX=600; YMIN=-100;
	TString Branchname = "mZDauLL"; XMAX=140; XMIN=0; rebin=1; YMAX=300; YMIN=-100;
	//TString Branchname = "mWDau"; XMAX=120; XMIN=60; rebin=1; YMAX=1500; YMIN=-10;
	//TString Branchname = "mWDauLL"; XMAX=120; XMIN=60; rebin=1; YMAX=700; YMIN=-10;
	
	//TString Branchname = "typeLL"; XMAX=4; XMIN=0; rebin=1; YMAX=2000; YMIN=-100;
	//TString Branchname = "typeLN"; XMAX=4; XMIN=0; rebin=1; YMAX=2000; YMIN=-100;
	//TString Branchname = "typeP"; XMAX=5; XMIN=0; rebin=1; YMAX=1000; YMIN=-100;
	//TString Branchname = "nDauZ"; XMAX=10; XMIN=0; rebin=1; YMAX=100; YMIN=0;
	//TString Branchname = "nDauW"; XMAX=10; XMIN=0; rebin=1; YMAX=10000; YMIN=0;
	
	TString histname = baseBranch + "/" + "h1_" + Branchname;
	

// --Weighting	
	TH1F *hscheme1    = (TH1F*)fscheme1->Get(histname); hscheme1->Scale(Lumi/10000.) ;
	TH1F *hscheme2    = (TH1F*)fscheme2->Get(histname); hscheme2->Scale(Lumi/10000.) ;
	TH1F *hscheme3    = (TH1F*)fscheme3->Get(histname); hscheme3->Scale(Lumi/9950.) ;
	TH1F *hscheme4    = (TH1F*)fscheme4->Get(histname); hscheme4->Scale(Lumi/20000.) ;

	//TH1F *hscheme4_wm = (TH1F*)fscheme4_wm->Get(histname); //hscheme4_wm->Scale(Lumi/10000.) ;
	//TH1F *hscheme4_wp = (TH1F*)fscheme4_wp->Get(histname); //hscheme4_wp->Scale(Lumi/10000.) ;


// --histrogram design	
	
	hscheme1->SetLineWidth(4); hscheme1->SetLineColor(46);
	hscheme2->SetLineWidth(4); hscheme2->SetLineColor(42);
	hscheme3->SetLineWidth(4); hscheme3->SetLineColor(38);
	hscheme4->SetLineWidth(4); hscheme4->SetLineColor(3);
	
	//hscheme4_wm->SetLineWidth(4); hscheme4_wm->SetLineColor(8);
	//hscheme4_wp->SetLineWidth(4); hscheme4_wp->SetLineColor(29);


// --rebinning
	hscheme1->Rebin(rebin);
	hscheme2->Rebin(rebin);
	hscheme3->Rebin(rebin);
	hscheme4->Rebin(rebin);
//	hscheme4_wm->Rebin(rebin);
//	hscheme4_wp->Rebin(rebin);

// --Pad Design
   gStyle->SetOptStat(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadColor(0);
   gStyle->SetFrameBorderMode(0);


	double binwidth= hscheme1->GetBinWidth(1);



	TCanvas* c1 = new TCanvas("c1", "c1", 500, 500);
		TPad *pad1 = new TPad("pad1", "pad1", 0.0, 0.0001, 1.0, 1.0);
		//   pad1->SetBottomMargin(0.01);
		pad1->SetGrid();
		   //pad1->SetLogy();
		pad1->Draw();
		pad1->cd();
		TH2F *null1 = new TH2F("null1","", 2, XMIN, XMAX, 2, YMIN,YMAX);
		null1->GetYaxis()->SetTitle(Form("Number of events / %3.1f GeV",binwidth));
		null1->GetXaxis()->SetTitle(Branchname);
		null1->GetYaxis()->SetTitleOffset(1.8);
		null1->GetXaxis()->SetTitleOffset(1.2);
		null1->GetYaxis()->SetTitleSize(0.03);
		null1->GetYaxis()->SetLabelSize(0.03);
		null1->Draw();
		hscheme1->Draw("same hist");
		hscheme2->Draw("same hist");
		hscheme3->Draw("same hist");
		hscheme4->Draw("same hist");
		//hscheme4_wm->Draw("same hist");
	  	//hscheme4_wp->Draw("same hist");

// --legend	
	TLegend *l0 = new TLegend(0.65,0.89,0.90,0.65);
		l0->SetFillStyle(0);
		l0->SetBorderSize(0);
		l0->SetTextSize(0.03);

	  TLegendEntry* l01 = l0->AddEntry(hscheme1,"scheme1"   ,"l"  );    l01->SetTextColor(hscheme1->GetLineColor());  
	  TLegendEntry* l02 = l0->AddEntry(hscheme2,"scheme2"   ,"l"  );    l02->SetTextColor(hscheme2->GetLineColor());  
	  TLegendEntry* l03 = l0->AddEntry(hscheme3,"scheme3"   ,"l"  );    l03->SetTextColor(hscheme3->GetLineColor());  
	  TLegendEntry* l04 = l0->AddEntry(hscheme4,"scheme4"   ,"l"  );    l04->SetTextColor(hscheme4->GetLineColor());  
	  //TLegendEntry* l04 = l0->AddEntry(hscheme4_wm,"scheme4_wm"   ,"l"  );    l04->SetTextColor(hscheme4_wm->GetLineColor());  
	  //TLegendEntry* l05 = l0->AddEntry(hscheme4_wp,"scheme4_wp"   ,"l"  );    l05->SetTextColor(hscheme4_wp->GetLineColor());  
	
		l0->Draw();

		pad1->cd();
			TLatex latex;
			latex.SetNDC();
			latex.SetTextSize(0.04);
			latex.SetTextAlign(11);
			latex.DrawLatex(0.6,0.91,Form("%.1f fb^{-1} (13 TeV)", Lumi/1000.0));

	TString outname = Branchname + ".png";
	//c1->Print(outname);

	//double maxIntibin = hscheme1->GetXaxis()->FindBin(2000);
	cout << hscheme1->Integral() << endl;
	cout << hscheme2->Integral() << endl;
	cout << hscheme3->Integral() << endl;
	cout << hscheme4->Integral() << endl;
	//cout << hscheme4_wm->Integral() << endl;
	//cout << hscheme4_wp->Integral() << endl;
}
