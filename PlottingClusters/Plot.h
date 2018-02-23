//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 19 18:35:42 2017 by ROOT version 6.08/07
// from TTree PfTree/PF Cluster tree
// found on file: ../applyRegressionClusters/testingTree_withRegression.root
//////////////////////////////////////////////////////////

#ifndef Plot_h
#define Plot_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Plot {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nClus;
   Float_t         clusrawE;
   Float_t         cluscorrE;
   Float_t         clusPt;
   Float_t         clusEta;
   Float_t         clusRho;
   Float_t         clusPhi;
   Float_t         clusLayer;
   Int_t           clusSize;
   Int_t           clusIetaIx;
   Int_t           clusIphiIy;
   Float_t         clusPS1;
   Float_t         clusPS2;
   Int_t           clusFlag;
   Float_t         rho;
   Int_t           nvtx;
   Float_t         genEnergy;
   Float_t         genPt;
   Float_t         genEta;
   Float_t         genPhi;
   UShort_t        genStatusFlag;
   Double_t        ietamod20;
   Double_t        iphimod20;
   Double_t        tgtvar;
   Float_t         response;
   Float_t         resolution;
   Float_t         e91X;
   Float_t         e91Xres;

   // List of branches
   TBranch        *b_nClus;   //!
   TBranch        *b_clusrawE;   //!
   TBranch        *b_cluscorrE;   //!
   TBranch        *b_clusPt;   //!
   TBranch        *b_clusEta;   //!
   TBranch        *b_clusRho;   //!
   TBranch        *b_clusPhi;   //!
   TBranch        *b_clusLayer;   //!
   TBranch        *b_clusSize;   //!
   TBranch        *b_clusIetaIx;   //!
   TBranch        *b_clusIphiIy;   //!
   TBranch        *b_clusPS1;   //!
   TBranch        *b_clusPS2;   //!
   TBranch        *b_clusFlag;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_genEnergy;   //!
   TBranch        *b_genPt;   //!
   TBranch        *b_genEta;   //!
   TBranch        *b_genPhi;   //!
   TBranch        *b_genStatusFlag;   //!
   TBranch        *b_ietamod20;   //!
   TBranch        *b_iphimod20;   //!
   TBranch        *b_tgtvar;   //!
   TBranch        *b_response;   //!
   TBranch        *b_resolution;   //!
   TBranch        *b_e91X;   //!
   TBranch        *b_e91Xres;   //!

   Plot(TTree *tree=0);
   virtual ~Plot();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(string region, string flag /*FULL, FULL*/);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Plot_cxx
Plot::Plot(TTree *tree) : fChain(0) 
{//all_weights/pfClusters_noPU_PU_withRegression.root
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  /*if (tree == 0) {
     //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../applyRegressionClusters/pfClusters_noPU_PU_withRegression.root")
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../applyRegressionClusters/pfClusters_noPU_withRegression.root");
      if (!f || !f->IsOpen()) {
	//f = new TFile("../applyRegressionClusters/pfClusters_noPU_PU_withRegression.root");
	f = new TFile("../applyRegressionClusters/pfClusters_noPU_withRegression.root");
      }
      //TDirectory * dir = (TDirectory*)f->Get("../applyRegressionClusters/pfClusters_noPU_PU_withRegression.root:/een_analyzer");
      TDirectory * dir = (TDirectory*)f->Get("../applyRegressionClusters/pfClusters_noPU_withRegression.root:/een_analyzer");
      dir->GetObject("PfTree",tree);

   }
   Init(tree);
  */
}

Plot::~Plot()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Plot::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Plot::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Plot::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nClus", &nClus, &b_nClus);
   fChain->SetBranchAddress("clusrawE", &clusrawE, &b_clusrawE);
   fChain->SetBranchAddress("cluscorrE", &cluscorrE, &b_cluscorrE);
   fChain->SetBranchAddress("clusPt", &clusPt, &b_clusPt);
   fChain->SetBranchAddress("clusEta", &clusEta, &b_clusEta);
   fChain->SetBranchAddress("clusRho", &clusRho, &b_clusRho);
   fChain->SetBranchAddress("clusPhi", &clusPhi, &b_clusPhi);
   fChain->SetBranchAddress("clusLayer", &clusLayer, &b_clusLayer);
   fChain->SetBranchAddress("clusSize", &clusSize, &b_clusSize);
   fChain->SetBranchAddress("clusIetaIx", &clusIetaIx, &b_clusIetaIx);
   fChain->SetBranchAddress("clusIphiIy", &clusIphiIy, &b_clusIphiIy);
   fChain->SetBranchAddress("clusPS1", &clusPS1, &b_clusPS1);
   fChain->SetBranchAddress("clusPS2", &clusPS2, &b_clusPS2);
   fChain->SetBranchAddress("clusFlag", &clusFlag, &b_clusFlag);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("genEnergy", &genEnergy, &b_genEnergy);
   fChain->SetBranchAddress("genPt", &genPt, &b_genPt);
   fChain->SetBranchAddress("genEta", &genEta, &b_genEta);
   fChain->SetBranchAddress("genPhi", &genPhi, &b_genPhi);
   fChain->SetBranchAddress("genStatusFlag", &genStatusFlag, &b_genStatusFlag);
   fChain->SetBranchAddress("ietamod20", &ietamod20, &b_ietamod20);
   fChain->SetBranchAddress("iphimod20", &iphimod20, &b_iphimod20);
   fChain->SetBranchAddress("tgtvar", &tgtvar, &b_tgtvar);
   fChain->SetBranchAddress("response", &response, &b_response);
   fChain->SetBranchAddress("resolution", &resolution, &b_resolution);
   fChain->SetBranchAddress("e91X", &e91X, &b_e91X);
   fChain->SetBranchAddress("e91Xres", &e91Xres, &b_e91Xres);
   Notify();
}

Bool_t Plot::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Plot::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Plot::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Plot_cxx
