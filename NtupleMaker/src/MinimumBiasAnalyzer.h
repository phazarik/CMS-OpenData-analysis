//C++
//Class: MasterAnalyzer_headerfile
//Original Author: Raj Handique
//Created on: 4 January 2024 

//----------------------------------//
// All initialization & declaration //
// of classes, member functions,    //
// member data are done in this     //
// header file.                     //
//----------------------------------//

#include <vector>
#include <memory>

//system include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/View.h"

//class to extract Jet Information

#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/JetCollection.h"


//files to read

#include "TTree.h"
#include "TFile.h"

class MinimumBiasAnalyzer : public edm::EDAnalyzer{
 public:
  explicit MinimumBiasAnalyzer(const edm::ParameterSet&);
  ~MinimumBiasAnalyzer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
 private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
  // -------------- member data --------------------
  
  TTree *mtree;
  
  // Reco Jet atkt5 Collection initialization

  int nJet;
  std::vector<float> Jet_e;
  std::vector<float> Jet_pt;
  std::vector<float> Jet_eta;
  std::vector<float> Jet_phi;
  std::vector<float> Jet_mass;
  std::vector<float> Jet_area;
  std::vector<float> Jet_chEmEF;
  std::vector<float> Jet_chHEF;
  std::vector<float> Jet_neEmEF;
  std::vector<float> Jet_neHEF;
  std::vector<int> Jet_nConstituents; 

  
}; 

// Constructor & Destructor

MinimumBiasAnalyzer::MinimumBiasAnalyzer(const edm::ParameterSet& iConfig)
{
  
  edm::Service<TFileService> fs;
  mtree = fs->make<TTree>("Events", "Events");
  
  // Reco Jet Collection Tree initialization //

  mtree->Branch("nJet", &nJet);
  mtree->GetBranch("nJet")->SetTitle("Number of Jets"); 
  mtree->Branch("Jet_e", &Jet_e);
  mtree->GetBranch("Jet_e")->SetTitle("Jet Energy");
  mtree->Branch("Jet_pt", &Jet_pt);
  mtree->GetBranch("Jet_pt")->SetTitle("Jet transverse momentum");
  mtree->Branch("Jet_eta", &Jet_eta);
  mtree->GetBranch("Jet_eta")->SetTitle("Jet pseudorapidity");
  mtree->Branch("Jet_phi", &Jet_phi);
  mtree->GetBranch("Jet_phi")->SetTitle("Jet polar angle");
  mtree->Branch("Jet_mass", &Jet_mass);
  mtree->GetBranch("Jet_mass")->SetTitle("Jet mass");
  mtree->Branch("Jet_area", &Jet_area);
  mtree->GetBranch("Jet_area")->SetTitle("Jet area");  
  mtree->Branch("Jet_chEmEF", &Jet_chEmEF);
  mtree->GetBranch("Jet_chEmEF")->SetTitle("charged Electromagnetic Energy Fraction");
  mtree->Branch("Jet_chHEF", &Jet_chHEF);
  mtree->GetBranch("Jet_chHEF")->SetTitle("charged Hadron Energy Fraction");
  mtree->Branch("Jet_neEmEF", &Jet_neEmEF);
  mtree->GetBranch("Jet_neEmEF")->SetTitle("neutral Electromagnetic Energy Fraction");
  mtree->Branch("Jet_neHEF", &Jet_neHEF);
  mtree->GetBranch("Jet_neHEF")->SetTitle("neutral Hadron Energy Fraction");
  mtree->Branch("Jet_nConstituents", &Jet_nConstituents);
  mtree->GetBranch("Jet_nConstituents")->SetTitle("Number of particles in the Jet");
  
}

MinimumBiasAnalyzer::~MinimumBiasAnalyzer()
{
  //Put anything that needs to be deleted
  //De-allocation of memory
}

void
MinimumBiasAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
