#define compare_cxx
#include "compare.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <map>
#include "TVector.h"
#include "TVectorF.h"
//#include "sigmaEff.C"
#include "TGraph.h"
#include "TLegend.h"
#include <algorithm>    // std::sort

//float sigmaEff(vector<float> v, float threshold, float& xmin, float& xmax);


bool debug = false;

void compare::Loop(string region, string flag /*FULL, FULL*/)
{

  using namespace std;

   bool dobarrel = false;
   bool doendcap = false;
   bool doZS     = false;
   bool doALL     = true;


   if(region=="EB"){
     dobarrel = true;
     doendcap = false;
   }

   if(region=="EE"){
     dobarrel = false;
     doendcap = true;
   }

   if(region=="FULL"){
     dobarrel = false;
     doendcap = false;
   }

   if(flag == "ZS")
     doZS = true;
   else if(flag == "ALL")
     {
       doZS = false;
       doALL = true;
     }
   else if(flag == "FULL")
     {
       doZS = false;
       doALL = false;
     }



   //std::map<string,TH1F*> hmap;

   cout<<"doZS "<<doZS<<endl;
   /////PT bounds
   vector<float> globalPt_bounds;

   if(!doZS){
     cout<<"Filling Global Pt bounds for FULL readout"<<endl;
     globalPt_bounds.push_back(0.25);
     globalPt_bounds.push_back(5);
     globalPt_bounds.push_back(20);
     globalPt_bounds.push_back(100);
   }
   else{
     globalPt_bounds.push_back(0.25);
     //globalPt_bounds.push_back(0.);
     //globalPt_bounds.push_back(6.0);
     globalPt_bounds.push_back(5.0);
   }

   cout<<"Global pt bound "<<globalPt_bounds[globalPt_bounds.size()-1]<<endl;

   vector<float> allPt_bounds;

   if(!doZS){

     for(int ii=1; ii<globalPt_bounds.size(); ii++){
       
       double stepsize = 0.475;
       double initialpoint = globalPt_bounds[ii-1];
       int end = 5;
       
       if(ii==2){
	 stepsize = 1.5;
	 end = 10;
       }
       
       if(ii==3){
	 stepsize = 8.2;
	 end = 10;
       }
       

       for(int jj=0; jj<end; jj++){
	 allPt_bounds.push_back(initialpoint + stepsize*jj);
       }//for(int jj=0; jj<globalPt_bounds.size(); jj++)

       if(ii==1)
	 allPt_bounds.push_back(initialpoint + (end-1)*stepsize + 1.425*2);
     }//for(int ii=0; ii<globalPt_bounds.size(); ii++)
     allPt_bounds.push_back(globalPt_bounds[globalPt_bounds.size()-1]);
   }//if(!doZS)
   else{

     //allPt_bounds.push_back(0);
     //for(int jj=0; jj<6; jj++){
     //for(int jj=0; jj<11; jj++){
     for(int jj=0; jj<2; jj++){
       //allPt_bounds.push_back(0.25 + 0.575*jj);
       //allPt_bounds.push_back(0.25 + 1.15*jj);
       //allPt_bounds.push_back(0.25 + 0.475*jj);
       //allPt_bounds.push_back(0.25 + 0.275*jj);
       allPt_bounds.push_back(0.25 + 1.15*jj);
     }
     allPt_bounds.push_back(6);
   }
   
   
   for(int ii=0; ii<allPt_bounds.size(); ii++)
     cout<<"Binning is "<<allPt_bounds[ii]<<endl;


   TVectorF TallPt_bounds(allPt_bounds.size(), &allPt_bounds[0]);

   TallPt_bounds.Print();
   //for(int ii=0; ii<TallPt_bounds.GetNoElements(); ii++)
   // cout<<"TallPt_bounds: Binning is "<<TallPt_bounds[ii]<<endl;
   

   /////ETA bounds
   vector<float> genEta_bounds;
   if(dobarrel){
     for(int jj=0; jj<21; jj++)
       genEta_bounds.push_back(0.0 + 0.075*jj); 
   }
   else{
     
     for(int jj=0; jj<21; jj++)
       genEta_bounds.push_back(1.4 + 0.055*jj); 
   }

   TVector TgenEta_bounds(genEta_bounds.size(), &genEta_bounds[0]);

   /////NVTX bounds
   vector<float> nvtx_bounds;
   for(int jj=0; jj<13; jj++)
     nvtx_bounds.push_back(1.0 + 5*jj); 

   TVector Tnvtx_bounds(nvtx_bounds.size(), &nvtx_bounds[0]);

   /////ETA bounds
   vector<float> clusSize_bounds;
   if(doZS){
     for(int jj=0; jj<6; jj++)
       clusSize_bounds.push_back(1.0 + jj); 
   }
   else{
     /*for(int jj=0; jj<6; jj++)
       clusSize_bounds.push_back(1.0 + jj); 
     */
     clusSize_bounds.push_back(1);
     clusSize_bounds.push_back(2);
     clusSize_bounds.push_back(3);
     clusSize_bounds.push_back(7);
     for(int jj=0; jj<5; jj++)
       //clusSize_bounds.push_back(5.0 + 5*jj); 
       clusSize_bounds.push_back(7.0 + 5*jj); 

   }
   
   TVector TclusSize_bounds(clusSize_bounds.size(), &clusSize_bounds[0]);


   for(int ii=0; ii<allPt_bounds.size(); ii++)
     cout<<"Printing allPt bounds just before defining hPT, Binning is "<<allPt_bounds[ii]<<endl;
   
   float* AallPt_bounds = &allPt_bounds[0];
   float* AglobalPt_bounds = &globalPt_bounds[0];
   float* AgenEta_bounds = &genEta_bounds[0];
   float* Anvtx_bounds = &nvtx_bounds[0];
   float* AclusSize_bounds = &clusSize_bounds[0];

   ////create histograms to find the bin which an event belongs to

   TH1F *hGPT = new TH1F("hGPT","",globalPt_bounds.size()-1,AglobalPt_bounds);
   TH1F *hPT = new TH1F("hPT","",allPt_bounds.size()-1,AallPt_bounds);
   TH1F *hETA = new TH1F("hETA","",genEta_bounds.size()-1,AgenEta_bounds);
   TH1F *hNVTX = new TH1F("hNVTX","",nvtx_bounds.size()-1,Anvtx_bounds);
   TH1F *hCSIZE = new TH1F("hCSIZE","",clusSize_bounds.size()-1,AclusSize_bounds);


   for(int ii=1; ii<=hPT->GetNbinsX(); ii++)
     cout<<"ii : binX "<<ii<<" "<<hPT->GetXaxis()->GetBinLowEdge(ii)<<" "<<hPT->GetXaxis()->GetBinUpEdge(ii)<<endl;
   
   for(int ii=1; ii<=hCSIZE->GetNbinsX(); ii++)
     cout<<"ii : clussize binX "<<ii<<" "<<hCSIZE->GetXaxis()->GetBinLowEdge(ii)<<" "<<hCSIZE->GetXaxis()->GetBinUpEdge(ii)<<endl;

   map<string,vector<float> > newCorrmap;
   map<string,vector<float> > oldCorrmap;
   map<string,vector<float> > rawCorrmap;

   map<string,TH1F* > hnewCorrmap;
   map<string,TH1F* > holdCorrmap;
   map<string,TH1F* > hrawCorrmap;

   map<string,vector<float> > newCorrmapMCv1;
   map<string,vector<float> > oldCorrmapMCv1;
   map<string,vector<float> > rawCorrmapMCv1;

   map<string,TH1F* > hnewCorrmapMCv1;
   map<string,TH1F* > holdCorrmapMCv1;
   map<string,TH1F* > hrawCorrmapMCv1;
   

   //int nbins   = 60;
   int nbins   = 100;
   double xmin = 0.6;
   double xmax = 1.6;

     for(int ii=0; ii<allPt_bounds.size()-1; ii++){
       
       hnewCorrmap[Form("genPT_%.3fTO%.3f",allPt_bounds[ii], allPt_bounds[ii+1])] = new TH1F(Form("eCorr91X_genPT_%fTO%f",allPt_bounds[ii], allPt_bounds[ii+1]),"", nbins,xmin,xmax);
       hnewCorrmapMCv1[Form("genPT_%.3fTO%.3f",allPt_bounds[ii], allPt_bounds[ii+1])] = new TH1F(Form("eCorr91X_genPT_%fTO%f",allPt_bounds[ii], allPt_bounds[ii+1]),"", nbins,xmin,xmax);
       
       holdCorrmap[Form("genPT_%.3fTO%.3f",allPt_bounds[ii], allPt_bounds[ii+1])] = new TH1F(Form("eCorr74X_genPT_%fTO%f",allPt_bounds[ii], allPt_bounds[ii+1]),"", nbins,xmin,xmax);
       holdCorrmapMCv1[Form("genPT_%.3fTO%.3f",allPt_bounds[ii], allPt_bounds[ii+1])] = new TH1F(Form("eCorr74X_genPT_%fTO%f",allPt_bounds[ii], allPt_bounds[ii+1]),"", nbins,xmin,xmax);
       
       hrawCorrmap[Form("genPT_%.3fTO%.3f",allPt_bounds[ii], allPt_bounds[ii+1])] = new TH1F(Form("raw_genPT_%fTO%f",allPt_bounds[ii], allPt_bounds[ii+1]),"", nbins,xmin,xmax);
       
       hrawCorrmapMCv1[Form("genPT_%.3fTO%.3f",allPt_bounds[ii], allPt_bounds[ii+1])] = new TH1F(Form("raw_genPT_%fTO%f",allPt_bounds[ii], allPt_bounds[ii+1]),"", nbins,xmin,xmax);
       
       cout<<"Nae of the histo for memory is "<<Form("genPT_%.3fTO%.3f",allPt_bounds[ii], allPt_bounds[ii+1])<<endl;
     }

     /*
     for(int kk=0; kk<globalPt_bounds.size()-1; kk++){
       for(int ii=0; ii<clusSize_bounds.size()-1; ii++){
	 
	 hnewCorrmap[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("eCorr91X_clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);

	 hnewCorrmapMCv1[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("eCorr91X_clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);

	 
	 holdCorrmap[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("eCorr74X_clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);

	 holdCorrmapMCv1[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("eCorr74X_clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);

	 
	 hrawCorrmap[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("raw_clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);

	 hrawCorrmapMCv1[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("raw_clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);
	 
	 cout<<"Nae of the histo for memory is "<<Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[ii], clusSize_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])<<endl;
       }//for(int ii=0; ii<clusSize_bounds.size()-1; ii++


       ///genETA
       for(int ii=0; ii<genEta_bounds.size()-1; ii++){
	 
	 hnewCorrmap[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("eCorr91X_genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);

	 hnewCorrmapMCv1[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("eCorr91X_genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);

	 
	 holdCorrmap[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("eCorr74X_genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);

	 holdCorrmapMCv1[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("eCorr74X_genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);
	 
	 hrawCorrmap[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("raw_genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);

	 hrawCorrmapMCv1[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])] = new TH1F(Form("raw_genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1]),"", nbins,xmin,xmax);
	 
	 cout<<"Nae of the histo for memory is "<<Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[ii], genEta_bounds[ii+1], globalPt_bounds[kk],  globalPt_bounds[kk+1])<<endl;
       }//for(int ii=0; ii<genEta_bounds.size()-1; ii++

     }//for(int ii=1; ii<globalPt_bounds.size(); ii++)
     */


     cout<<"openinign MCv2 root file"<<endl;
     TFile *fnew = TFile::Open("pfClusters_PU_withRegression.root");
     TTree *tnew = (TTree*)fnew->Get("een_analyzer/PfTree");
     Init(tnew);
     cout<<"openend MCv2 root file"<<endl;

  
  
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      double rawRatio = clusrawE/genEnergy;
      double oldRatio = cluscorrE/genEnergy;
      double newRatio = e91X/genEnergy;
      
      bool regioncut = false;

      if (dobarrel) {
	if (doZS) 
	  regioncut = clusLayer==-1 && clusFlag==1;
	else if(!doZS && !doALL)
	  regioncut = clusLayer==-1 && clusFlag==3;
	else if(!doZS && doALL)
	  regioncut = clusLayer==-1;
      }//if (dobarrel)
      else if (doendcap) {
	if (doZS) 
	  regioncut = clusLayer==-2 && clusFlag==1;
	else  if(!doZS && !doALL)
	  regioncut = clusLayer==-2 && clusFlag==3;
	else if(!doZS && doALL) 
	  regioncut = clusLayer==-2;
      }
      
      else {
	if (doZS) 
	  regioncut = (clusLayer==-2 ||  clusLayer==-1 ) && clusFlag==1;
	else if(!doZS && !doALL) 
	  regioncut = (clusLayer==-2 ||  clusLayer==-1 ) && clusFlag==3;
	else if(!doZS && doALL) 
	  regioncut = (clusLayer==-2 ||  clusLayer==-1 );
      }
      

      if(!regioncut) continue;

      //if(doZS)
      if(genPt > globalPt_bounds[globalPt_bounds.size()-1]) continue;
      if(genPt < globalPt_bounds[0]) continue;

      //if( genPt < 0.25 ) continue;
      int ptbin = hPT->FindBin(genPt);
      
      if(debug){
	cout<<"====NEW EVENT===="<<endl;
	cout<<"pt: pt bin "<<genPt<<" "<<ptbin<<endl;
	cout<<"pT bin : "<<allPt_bounds[ptbin-1]<<" "<<allPt_bounds[ptbin]<<endl;
	
	
	cout<<""<<endl;
	cout<<"Name inside the loop is "<<Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])<<endl;
      }



      newCorrmap[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])].push_back(newRatio); 
      oldCorrmap[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])].push_back(oldRatio); 
      rawCorrmap[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])].push_back(rawRatio); 

      hnewCorrmap[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])]->Fill(newRatio); 
      holdCorrmap[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])]->Fill(oldRatio); 
      hrawCorrmap[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])]->Fill(rawRatio); 


      if(debug) cout<<"Filled all pT "<<endl;

      int gptbin = hGPT->FindBin(genPt);

      /*      
      if(clusSize < clusSize_bounds[clusSize_bounds.size()-1]){

	int clusbin = hCSIZE->FindBin(clusSize);
	

	cout<<"===new event===="<<endl;
	cout<<" genPt : clusSize : "<<genPt<<" "<<clusSize<<endl;
	cout<<" genPt bin : clusBin : "<<gptbin<<" "<<clusbin<<endl;
	cout<<"clus bounds: "<<clusSize_bounds[clusbin-1]<<" "<<" "<<clusSize_bounds[clusbin]<<endl;
	cout<<"pt bounds: "<<globalPt_bounds[gptbin-1]<<" "<<" "<<globalPt_bounds[gptbin]<<endl;
	

	hnewCorrmap[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[clusbin-1], clusSize_bounds[clusbin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(newRatio); 
	holdCorrmap[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[clusbin-1], clusSize_bounds[clusbin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(oldRatio); 
	hrawCorrmap[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[clusbin-1], clusSize_bounds[clusbin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(rawRatio); 


	
	
      }
      */

      /*
      if(fabs(genEta) < genEta_bounds[genEta_bounds.size()-1]){
	
	
	//genEta
	int etabin = hETA->FindBin(genEta);
	
	
	hnewCorrmap[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[etabin-1], genEta_bounds[etabin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(newRatio); 
	holdCorrmap[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[etabin-1], genEta_bounds[etabin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(oldRatio); 
	hrawCorrmap[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[etabin-1], genEta_bounds[etabin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(rawRatio); 
      }

      int nvtxbin = hNVTX->FindBin(nvtx);
      */

   }


   ////Do the same using MCV1 samples
   //TFile *fold = TFile::Open("pfClusters_noPU_PU_withRegression_MCv1.root");
   TFile *fold = TFile::Open("pfClusters_PU_withRegression_OLD.root");
   TTree *told = (TTree*)fold->Get("een_analyzer/PfTree");
   Init(told);


  
  
   if (fChain == 0) return;

   nentries = fChain->GetEntriesFast();

   nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      double rawRatio = clusrawE/genEnergy;
      double oldRatio = cluscorrE/genEnergy;
      double newRatio = e91X/genEnergy;

      bool regioncut = false;

      if (dobarrel) {
	if (doZS) 
	  regioncut = clusLayer==-1 && clusFlag==1;
	else if(!doZS && !doALL)
	  regioncut = clusLayer==-1 && clusFlag==3;
	else if(!doZS && doALL)
	  regioncut = clusLayer==-1;
      }//if (dobarrel)
      else if (doendcap) {
	if (doZS) 
	  regioncut = clusLayer==-2 && clusFlag==1;
	else  if(!doZS && !doALL)
	  regioncut = clusLayer==-2 && clusFlag==3;
	else if(!doZS && doALL) 
	  regioncut = clusLayer==-2;
      }
      
      else {
	if (doZS) 
	  regioncut = (clusLayer==-2 ||  clusLayer==-1 ) && clusFlag==1;
	else if(!doZS && !doALL) 
	  regioncut = (clusLayer==-2 ||  clusLayer==-1 ) && clusFlag==3;
	else if(!doZS && doALL) 
	  regioncut = (clusLayer==-2 ||  clusLayer==-1 );
      }
      

      if(!regioncut) continue;

      //if(doZS)
      if(genPt > globalPt_bounds[globalPt_bounds.size()-1]) continue;
      if(genPt < globalPt_bounds[0]) continue;

      //if( genPt < 0.25 ) continue;
      int ptbin = hPT->FindBin(genPt);
      /*cout<<"====NEW EVENT===="<<endl;
      cout<<"pt: pt bin "<<genPt<<" "<<ptbin<<endl;
      cout<<"pT bin : "<<allPt_bounds[ptbin-1]<<" "<<allPt_bounds[ptbin]<<endl;
      */
      
      /*cout<<""<<endl;
      cout<<"Name inside the loop is "<<Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])<<endl;
      */

      newCorrmapMCv1[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])].push_back(newRatio); 
      oldCorrmapMCv1[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])].push_back(oldRatio); 
      rawCorrmapMCv1[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])].push_back(rawRatio); 

      hnewCorrmapMCv1[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])]->Fill(newRatio); 
      holdCorrmapMCv1[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])]->Fill(oldRatio); 
      hrawCorrmapMCv1[Form("genPT_%.3fTO%.3f",allPt_bounds[ptbin-1], allPt_bounds[ptbin])]->Fill(rawRatio); 



      int gptbin = hGPT->FindBin(genPt);

      /*      
      if(clusSize < clusSize_bounds[clusSize_bounds.size()-1]){

	int clusbin = hCSIZE->FindBin(clusSize);
	

	cout<<"===new event===="<<endl;
	cout<<" genPt : clusSize : "<<genPt<<" "<<clusSize<<endl;
	cout<<" genPt bin : clusBin : "<<gptbin<<" "<<clusbin<<endl;
	cout<<"clus bounds: "<<clusSize_bounds[clusbin-1]<<" "<<" "<<clusSize_bounds[clusbin]<<endl;
	cout<<"pt bounds: "<<globalPt_bounds[gptbin-1]<<" "<<" "<<globalPt_bounds[gptbin]<<endl;
	

	hnewCorrmapMCv1[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[clusbin-1], clusSize_bounds[clusbin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(newRatio); 
	holdCorrmapMCv1[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[clusbin-1], clusSize_bounds[clusbin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(oldRatio); 
	hrawCorrmapMCv1[Form("clusSIZE_%.0fTO%.0f_pT%.3fTO%.3f",clusSize_bounds[clusbin-1], clusSize_bounds[clusbin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(rawRatio); 


	
	
      }
      */

      /*
      if(fabs(genEta) < genEta_bounds[genEta_bounds.size()-1]){


	//genEta
	int etabin = hETA->FindBin(genEta);
	
	
	hnewCorrmapMCv1[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[etabin-1], genEta_bounds[etabin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(newRatio); 
	holdCorrmapMCv1[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[etabin-1], genEta_bounds[etabin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(oldRatio); 
	hrawCorrmapMCv1[Form("genEta_%.4fTO%.4f_pT%.3fTO%.3f",genEta_bounds[etabin-1], genEta_bounds[etabin], globalPt_bounds[gptbin-1], globalPt_bounds[gptbin])]->Fill(rawRatio); 
      }

      int nvtxbin = hNVTX->FindBin(nvtx);
      */

   }
   /////End of MC v1 samples




   //////Draw the pT histogram
   
   int W = 800;
   int H = 600;

   int H_ref = 600;
   int W_ref = 800;

   float T = 0.08*H_ref;
   float B = 0.12*H_ref;
   float L = 0.12*W_ref;
   float R = 0.04*W_ref;


   char *filename = new char[100];

   map<std::string,TH1F* >::iterator it;
   int ii=0;
   for( it = hnewCorrmap.begin(); it != hnewCorrmap.end(); ++it ) {

     TLegend* leg = new TLegend(0.150402,0.7125436,0.404975,0.8954704,NULL,"brNDC");
     //TLegend* leg = new TLegend(0.150402,0.7125436,0.404975,0.8954704,NULL,"brNDC");
     
     TCanvas *c = new TCanvas("c","c",50,50,W,H);
     gStyle->SetOptStat(0);
     cout<<""<<endl;
     cout<<"Name of the map "<<it->first<<endl;
     string name = it->first;

     //cout<<"Integral is raw : 714 : new "<<hrawCorrmap[name]->Integral()<<" "<<holdCorrmap[name]->Integral()<<" "<<hnewCorrmap[name]->Integral()<<endl;


     cout<<"Integral is MCv1 : MCv2 "<<hnewCorrmapMCv1[name]->Integral()<<" "<<hnewCorrmap[name]->Integral()<<endl;

     hnewCorrmap[name]->SetLineColor(2);
     hnewCorrmap[name]->SetLineWidth(2);
     hnewCorrmapMCv1[name]->SetLineColor(1);
     hnewCorrmapMCv1[name]->SetLineWidth(2);


     hrawCorrmap[name]->SetLineColor(2);
     hrawCorrmap[name]->SetLineWidth(2);
     hrawCorrmapMCv1[name]->SetLineColor(1);
     hrawCorrmapMCv1[name]->SetLineWidth(2);



     //hrawCorrmap[name]->SetLineColor(4);
     //hrawCorrmap[name]->SetLineWidth(2);

     double scale = hnewCorrmap[name]->Integral();
     hnewCorrmap[name]->Scale(1./scale);


     scale = hnewCorrmapMCv1[name]->Integral();
     hnewCorrmapMCv1[name]->Scale(1./scale);
     
     scale = hrawCorrmap[name]->Integral();
     hrawCorrmap[name]->Scale(1./scale);

     scale = hrawCorrmapMCv1[name]->Integral();
     hrawCorrmapMCv1[name]->Scale(1./scale);

     //scale = hrawCorrmap[name]->Integral();
     //hrawCorrmap[name]->Scale(1./scale);

     double dmax = 15;

     double max = TMath::Max(hnewCorrmap[name]->GetMaximum(), hnewCorrmapMCv1[name]->GetMaximum());

     //max = TMath::Max(max, hrawCorrmap[name]->GetMaximum());
     hnewCorrmap[name]->SetMaximum(max*dmax);
     hnewCorrmapMCv1[name]->SetMaximum(max*dmax);
     //holdCorrmap[name]->SetMaximum(max*1.5);
     //hrawCorrmap[name]->SetMaximum(max*1.5);

     c->SetLogy();
     hnewCorrmap[name]->Draw("HIST");
     hnewCorrmapMCv1[name]->Draw("HISTsame");
     //holdCorrmap[name]->Draw("HISTsame"); 
     //hrawCorrmap[name]->Draw("HISTsame");

     leg->AddEntry(hnewCorrmapMCv1[name],"NEW CORR on MCv1","lp");
     leg->AddEntry(hnewCorrmap[name],"NEW CORR on MCv2","lp");
     //leg->AddEntry(holdCorrmap[name],"OLD CORR","lp");
     //leg->AddEntry(hrawCorrmap[name],"RAW CORR","lp");

     leg->Draw();
     c->Modified();
     c->Update();
     
     sprintf(filename,"plots/histoPtnew_%s_%s_%s_Eff.png",name.c_str(),region.c_str(),flag.c_str());
     c->Print(filename);
     sprintf(filename,"plots/histoPtnew_%s_%s_%s_Eff.C",name.c_str(),region.c_str(),flag.c_str());
     c->Print(filename);

     /////Draw raw energies
     max = TMath::Max(hrawCorrmap[name]->GetMaximum(), hrawCorrmapMCv1[name]->GetMaximum());
     hrawCorrmap[name]->SetMaximum(max*dmax);
     hrawCorrmapMCv1[name]->SetMaximum(max*dmax);

     TCanvas *craw = new TCanvas("craw","craw",50,50,W,H);
     craw->SetLogy();
     gStyle->SetOptStat(0);
     craw->cd();
     hrawCorrmap[name]->Draw("HIST");
     hrawCorrmapMCv1[name]->Draw("HISTsame");
     leg->Draw();
     craw->Modified();
     craw->Update();

     sprintf(filename,"plots/histoPtRaw_%s_%s_%s_Eff.png",name.c_str(),region.c_str(),flag.c_str());
     craw->Print(filename);
     sprintf(filename,"plots/histoPtRaw_%s_%s_%s_Eff.C",name.c_str(),region.c_str(),flag.c_str());
     craw->Print(filename);



   }

}
