//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 30 14:50:45 2024 by ROOT version 6.28/04
// from TTree Events/Events
// found on file: testoutput.root
//////////////////////////////////////////////////////////

#ifndef cmsAna_h
#define cmsAna_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>


//Additional headers
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include "TLorentzVector.h"
#include <fstream>
#include <iostream>
#include "TString.h"
#include <bitset>
#include <time.h>


class cmsAna : public TSelector {
public :
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  // Readers to access the data (delete the ones you do not need).
  TTreeReaderValue<Int_t> nGenParticle = {fReader, "nGenParticle"};
  TTreeReaderArray<float> GenParticle_e = {fReader, "GenParticle_e"};
  TTreeReaderArray<float> GenParticle_pt = {fReader, "GenParticle_pt"};
  TTreeReaderArray<float> GenParticle_eta = {fReader, "GenParticle_eta"};
  TTreeReaderArray<float> GenParticle_phi = {fReader, "GenParticle_phi"};
  TTreeReaderArray<float> GenParticle_mass = {fReader, "GenParticle_mass"};
  TTreeReaderArray<int> GenParticle_pdgId = {fReader, "GenParticle_pdgId"};
  TTreeReaderArray<float> GenParticle_px = {fReader, "GenParticle_px"};
  TTreeReaderArray<float> GenParticle_py = {fReader, "GenParticle_py"};
  TTreeReaderArray<float> GenParticle_pz = {fReader, "GenParticle_pz"};
  TTreeReaderValue<Int_t> nMuon = {fReader, "nMuon"};
  TTreeReaderArray<float> Muon_e = {fReader, "Muon_e"};
  TTreeReaderArray<float> Muon_pt = {fReader, "Muon_pt"};
  TTreeReaderArray<float> Muon_eta = {fReader, "Muon_eta"};
  TTreeReaderArray<float> Muon_phi = {fReader, "Muon_phi"};
  TTreeReaderArray<float> Muon_mass = {fReader, "Muon_mass"};
  TTreeReaderArray<int> Muon_charge = {fReader, "Muon_charge"};
  TTreeReaderArray<int> Muon_pdgId = {fReader, "Muon_pdgId"};
  TTreeReaderArray<float> Muon_px = {fReader, "Muon_px"};
  TTreeReaderArray<float> Muon_py = {fReader, "Muon_py"};
  TTreeReaderArray<float> Muon_pz = {fReader, "Muon_pz"};


  cmsAna(TTree * /*tree*/ =0) { }
  virtual ~cmsAna() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();


  //user defined functions //

  void SetHstFileName(const char *HstFileName){ _HstFileName = HstFileName;}
  void SetSumFileName(const char *SumFileName){ _SumFileName = SumFileName;}
  void SetVerbose(int verbose){ _verbosity = verbose; }
  void SetData(int data){_data = data;}
  void SetYear(int year){_year = year;}
  void BookHistograms();

  
public:
  struct Hists {
    //Histograms are declared here.

    TH1F *hist[10];
  };

  //Each particle is represented as a struct
  //with the following properties.
  struct Particle {
    TLorentzVector v;
    int id;
    int index;
    int status;
    int pdgid;
    int charge;
    float radius;
    float px;
    float py;
    float pz;
    float e;
    int nConstituents;

    
  };

  void Sortpt(vector<Particle> vec);

protected:
  Hists h;

private:
  //Global variables are declared here.
  //Those whose valued as not assigned need to be initialized in the Begin() part.

  TFile *_HstFile; //The output file
  const char *_HstFileName;
  const char *_SumFileName;
  int _verbosity,_data, _lep, _year; //These values are assigned by the functions defined above.

  
  //Vectors to keep the particles in each event:
  vector<Particle> Muons;
  vector<Particle> GenPart;
  vector<Particle> GenMuon;
  

  //Event counters: (needs to be initialized in the main code)
  int nEvtTotal;

  time_t start, end;
  
  ClassDef(cmsAna,0);

};

#endif

#ifdef cmsAna_cxx
void cmsAna::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  fReader.SetTree(tree);
}

Bool_t cmsAna::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}


#endif // #ifdef cmsAna_cxx
