//C++
//Class: MasterNTupleMaker_headerfile
//Original Author: Raj Handique
//Created on: 29 May 2024

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

//class to extract GenParticles

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

//classes to extract Reco Muons

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

//files to read

#include "TTree.h"
#include "TFile.h"

class testntuplemaker : public edm::EDAnalyzer{
 public:
  explicit testntuplemaker(const edm::ParameterSet&);
  ~testntuplemaker();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
 private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
  // -------------- member data --------------------
  
  TTree *mtree;
 
  // Gen Particle Collection initialization
  
  int nGenParticle;
  std::vector<float> GenParticle_e;
  std::vector<float> GenParticle_pt;
  std::vector<float> GenParticle_eta;
  std::vector<float> GenParticle_phi;
  std::vector<float> GenParticle_mass;
  std::vector<int> GenParticle_pdgId;
  std::vector<int> GenParticle_status;
  std::vector<float> GenParticle_px;
  std::vector<float> GenParticle_py;
  std::vector<float> GenParticle_pz;

  // Reco Muon Collection initialization

  int nMuon;
  std::vector<float> Muon_e;
  std::vector<float> Muon_pt;
  std::vector<float> Muon_eta;
  std::vector<float> Muon_phi;
  std::vector<float> Muon_mass;
  std::vector<int> Muon_pdgId;
  std::vector<int> Muon_charge;
  std::vector<float> Muon_px;
  std::vector<float> Muon_py;
  std::vector<float> Muon_pz;

}; 

// Constructor & Destructor

testntuplemaker::testntuplemaker(const edm::ParameterSet& iConfig)
{
  
  edm::Service<TFileService> fs;
  mtree = fs->make<TTree>("Events", "Events");
  
  // Gen Particle Collection initialization //

  mtree->Branch("nGenParticle", &nGenParticle);
  mtree->GetBranch("nGenParticle")->SetTitle("Number of Generator Level Particles"); 
  mtree->Branch("GenParticle_e", &GenParticle_e);
  mtree->GetBranch("GenParticle_e")->SetTitle("Generator Level Particle Energy");
  mtree->Branch("GenParticle_pt", &GenParticle_pt);
  mtree->GetBranch("GenParticle_pt")->SetTitle("Generator Level Particle transverse momentum");
  mtree->Branch("GenParticle_eta", &GenParticle_eta);
  mtree->GetBranch("GenParticle_eta")->SetTitle("Generator Level Particle pseudorapidity");
  mtree->Branch("GenParticle_phi", &GenParticle_phi);
  mtree->GetBranch("GenParticle_phi")->SetTitle("Generator Level Particle polar angle");
  mtree->Branch("GenParticle_mass", &GenParticle_mass);
  mtree->GetBranch("GenParticle_mass")->SetTitle("Generator Level Particle mass");
  mtree->Branch("GenParticle_pdgId", &GenParticle_pdgId);
  mtree->GetBranch("GenParticle_pdgId")->SetTitle("Generator Level Particle ID");
  mtree->Branch("GenParticle_px", &GenParticle_px);
  mtree->GetBranch("GenParticle_px")->SetTitle("Generator Level Particle transverse momentum x-component");
  mtree->Branch("GenParticle_py", &GenParticle_py);
  mtree->GetBranch("GenParticle_py")->SetTitle("Generator Level Particle transverse momentum y-component");
  mtree->Branch("GenParticle_pz", &GenParticle_pz);
  mtree->GetBranch("GenParticle_pz")->SetTitle("Generator Level Particle transverse momentum z-component");  

  // Muon Collection initialization //

  mtree->Branch("nMuon", &nMuon);
  mtree->GetBranch("nMuon")->SetTitle("Number of Muons"); 
  mtree->Branch("Muon_e", &Muon_e);
  mtree->GetBranch("Muon_e")->SetTitle("Muon Energy");
  mtree->Branch("Muon_pt", &Muon_pt);
  mtree->GetBranch("Muon_pt")->SetTitle("Muon Transverse Momentum");
  mtree->Branch("Muon_eta", &Muon_eta);
  mtree->GetBranch("Muon_eta")->SetTitle("Muon pseudorapidity");
  mtree->Branch("Muon_phi", &Muon_phi);
  mtree->GetBranch("Muon_phi")->SetTitle("Muon Polar Angle");
  mtree->Branch("Muon_mass", &Muon_mass);
  mtree->GetBranch("Muon_mass")->SetTitle("Muon mass");
  mtree->Branch("Muon_charge", &Muon_charge);
  mtree->GetBranch("Muon_charge")->SetTitle("Muon charge");
  mtree->Branch("Muon_pdgId", &Muon_pdgId);
  mtree->GetBranch("Muon_pdgId")->SetTitle("Muon pdgId");
  mtree->Branch("Muon_px", &Muon_px);
  mtree->GetBranch("Muon_px")->SetTitle("Muon Transverse momentum x-component");
  mtree->Branch("Muon_py", &Muon_py);
  mtree->GetBranch("Muon_py")->SetTitle("Muon Transverse momentum y-component");  
  mtree->Branch("Muon_pz", &Muon_pz);
  mtree->GetBranch("Muon_pz")->SetTitle("Muon Transverse momentum z-component");

}

testntuplemaker::~testntuplemaker()
{
  //Put anything that needs to be deleted
  //De-allocation of memory
}

void
testntuplemaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
 //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

