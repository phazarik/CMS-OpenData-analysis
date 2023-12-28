//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec 28 16:09:45 2023 by ROOT version 6.26/10
// from TTree Events/Events
// found on file: sample_input.root
//////////////////////////////////////////////////////////

#ifndef AnaOpenData_h
#define AnaOpenData_h

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

class AnaOpenData : public TSelector {
public :
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  // Readers to access the data (delete the ones you do not need).
  TTreeReaderValue<Int_t> numPFCandidates = {fReader, "numPFCandidates"};
  TTreeReaderArray<float> PFCand_e = {fReader, "PFCand_e"};
  TTreeReaderArray<float> PFCand_pt = {fReader, "PFCand_pt"};
  TTreeReaderArray<float> PFCand_eta = {fReader, "PFCand_eta"};
  TTreeReaderArray<float> PFCand_phi = {fReader, "PFCand_phi"};
  TTreeReaderArray<float> PFCand_mass = {fReader, "PFCand_mass"};
  TTreeReaderArray<float> PFCand_charge = {fReader, "PFCand_charge"};
  TTreeReaderArray<int> PFCand_pdgId = {fReader, "PFCand_pdgId"};
  TTreeReaderArray<int> PFCand_status = {fReader, "PFCand_status"};
  TTreeReaderArray<float> PFCand_px = {fReader, "PFCand_px"};
  TTreeReaderArray<float> PFCand_py = {fReader, "PFCand_py"};
  TTreeReaderArray<float> PFCand_pz = {fReader, "PFCand_pz"};
  TTreeReaderArray<float> PFCand_hoERatio = {fReader, "PFCand_hoERatio"};
  TTreeReaderArray<float> PFCand_rawEcalEnergy = {fReader, "PFCand_rawEcalEnergy"};
  TTreeReaderArray<float> PFCand_rawHcalEnergy = {fReader, "PFCand_rawHcalEnergy"};
  TTreeReaderValue<Int_t> numRecoJets = {fReader, "numRecoJets"};
  TTreeReaderArray<float> RecoJet_e = {fReader, "RecoJet_e"};
  TTreeReaderArray<float> RecoJet_pt = {fReader, "RecoJet_pt"};
  TTreeReaderArray<float> RecoJet_eta = {fReader, "RecoJet_eta"};
  TTreeReaderArray<float> RecoJet_phi = {fReader, "RecoJet_phi"};
  TTreeReaderArray<float> RecoJet_mass = {fReader, "RecoJet_mass"};
  TTreeReaderArray<int> RecoJet_pdgId = {fReader, "RecoJet_pdgId"};
  TTreeReaderArray<int> RecoJet_status = {fReader, "RecoJet_status"};
  TTreeReaderArray<float> RecoJet_px = {fReader, "RecoJet_px"};
  TTreeReaderArray<float> RecoJet_py = {fReader, "RecoJet_py"};
  TTreeReaderArray<float> RecoJet_pz = {fReader, "RecoJet_pz"};
  TTreeReaderValue<Int_t> numGenJets = {fReader, "numGenJets"};
  TTreeReaderArray<float> GenJet_e = {fReader, "GenJet_e"};
  TTreeReaderArray<float> GenJet_pt = {fReader, "GenJet_pt"};
  TTreeReaderArray<float> GenJet_eta = {fReader, "GenJet_eta"};
  TTreeReaderArray<float> GenJet_phi = {fReader, "GenJet_phi"};
  TTreeReaderArray<float> GenJet_mass = {fReader, "GenJet_mass"};
  TTreeReaderArray<int> GenJet_pdgId = {fReader, "GenJet_pdgId"};
  TTreeReaderArray<int> GenJet_status = {fReader, "GenJet_status"};
  TTreeReaderArray<float> GenJet_px = {fReader, "GenJet_px"};
  TTreeReaderArray<float> GenJet_py = {fReader, "GenJet_py"};
  TTreeReaderArray<float> GenJet_pz = {fReader, "GenJet_pz"};
  TTreeReaderValue<Int_t> numGenParticles = {fReader, "numGenParticles"};
  TTreeReaderArray<float> GenParticle_e = {fReader, "GenParticle_e"};
  TTreeReaderArray<float> GenParticle_pt = {fReader, "GenParticle_pt"};
  TTreeReaderArray<float> GenParticle_eta = {fReader, "GenParticle_eta"};
  TTreeReaderArray<float> GenParticle_phi = {fReader, "GenParticle_phi"};
  TTreeReaderArray<float> GenParticle_mass = {fReader, "GenParticle_mass"};
  TTreeReaderArray<int> GenParticle_pdgId = {fReader, "GenParticle_pdgId"};
  TTreeReaderArray<int> GenParticle_status = {fReader, "GenParticle_status"};
  TTreeReaderArray<float> GenParticle_px = {fReader, "GenParticle_px"};
  TTreeReaderArray<float> GenParticle_py = {fReader, "GenParticle_py"};
  TTreeReaderArray<float> GenParticle_pz = {fReader, "GenParticle_pz"};


  AnaOpenData(TTree * /*tree*/ =0) { }
  virtual ~AnaOpenData() { }
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

  //User defined functions are declared here
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
    int momid;
    int status;
    int pdgid;
    int charge;
  };

protected:
  Hists h;

private:
  //Global variables are declared here.
  //Those whose valued as not assigned need to be initialized in the Begin() part.
  TFile *_HstFile; //The output file
  const char *_HstFileName;
  const char *_SumFileName;
  int _verbosity,_data, _lep, _year; //These values are assigned by the functions defined above.
  float metpt, metphi;

  //Vectors to keep the particles in each event:
  vector<Particle> PFall, PFelectron;

  //Event counters: (needs to be initialized in the main code)
  int nEvtTotal,nEvtRan,nEvtTrigger;

  time_t start, end;
  
  ClassDef(AnaOpenData,0);

};

#endif

#ifdef AnaOpenData_cxx
void AnaOpenData::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  fReader.SetTree(tree);
}

Bool_t AnaOpenData::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}


#endif // #ifdef AnaOpenData_cxx
