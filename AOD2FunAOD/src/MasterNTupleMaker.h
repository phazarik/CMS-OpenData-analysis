//C++
//Class: MasterNTupleMaker_headerfile
//Original Author: Raj Handique
//Created on: 7 March 2024

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

//class to extract PFCandidates

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

//class to extract Reco Jets

#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

//class to extract GenJet

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"

//class to extract GenParticles

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

//classes to extract Reco Muons

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

// classes to extract Reco Electrons

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"

// classes to extract Reco Photons

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

// classes to extract PFTaus

#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TauReco/interface/PFTauFwd.h"


//files to read

#include "TTree.h"
#include "TFile.h"

class MasterNTupleMaker : public edm::EDAnalyzer{
 public:
  explicit MasterNTupleMaker(const edm::ParameterSet&);
  ~MasterNTupleMaker();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
 private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
  // -------------- member data --------------------
  
  TTree *mtree;
  
  // Particle Flow Candidates Collection initialization 

  int nPFCandidate;
  std::vector<float> PFCand_e;
  std::vector<float> PFCand_pt;
  std::vector<float> PFCand_eta;
  std::vector<float> PFCand_phi;
  std::vector<float> PFCand_mass;
  std::vector<float> PFCand_charge;
  std::vector<int> PFCand_pdgId;
  std::vector<float> PFCand_px;
  std::vector<float> PFCand_py;
  std::vector<float> PFCand_pz;
  std::vector<float> PFCand_hoERatio;
  std::vector<float> PFCand_rawEcalEnergy;
  std::vector<float> PFCand_rawHcalEnergy;

  // Reco Jet atkt5 Collection initialization

  int nJet;
  std::vector<float> Jet_e;
  std::vector<float> Jet_pt;
  std::vector<float> Jet_eta;
  std::vector<float> Jet_phi;
  std::vector<float> Jet_mass;
  std::vector<int> Jet_pdgId;
  std::vector<float> Jet_px;
  std::vector<float> Jet_py;
  std::vector<float> Jet_pz;
  std::vector<int> Jet_nConstituents;

  // Gen Jet Collection initialization

  int nGenJet;
  std::vector<float> GenJet_e;
  std::vector<float> GenJet_pt;
  std::vector<float> GenJet_eta;
  std::vector<float> GenJet_phi;
  std::vector<float> GenJet_mass;
  std::vector<int> GenJet_pdgId;
  std::vector<int> GenJet_status;
  std::vector<float> GenJet_px;
  std::vector<float> GenJet_py;
  std::vector<float> GenJet_pz;
  std::vector<int> GenJet_nConstituents;
  
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

  // Reco Electron Collection 

  int nElectron;
  std::vector<float> Electron_e;
  std::vector<float> Electron_pt;
  std::vector<float> Electron_eta;
  std::vector<float> Electron_phi;
  std::vector<float> Electron_mass;
  std::vector<int> Electron_pdgId;
  std::vector<int> Electron_charge;
  std::vector<float> Electron_px;
  std::vector<float> Electron_py;
  std::vector<float> Electron_pz;
  
  // Reco Photon Collection

  int nPhoton;
  std::vector<float> Photon_e;
  std::vector<float> Photon_pt;
  std::vector<float> Photon_eta;
  std::vector<float> Photon_phi;
  std::vector<float> Photon_mass;
  std::vector<int> Photon_charge;
  std::vector<int> Photon_pdgId;
  std::vector<float> Photon_px;
  std::vector<float> Photon_py;
  std::vector<float> Photon_pz;
  
  // PFTau Collection

  int nPFTau;
  std::vector<float> PFTau_e;
  std::vector<float> PFTau_pt;
  std::vector<float> PFTau_eta;
  std::vector<float> PFTau_phi;
  std::vector<float> PFTau_mass;
  std::vector<float> PFTau_charge;
  std::vector<float> PFTau_pdgId;
  std::vector<float> PFTau_px;
  std::vector<float> PFTau_py;
  std::vector<float> PFTau_pz;

}; 

// Constructor & Destructor

MasterNTupleMaker::MasterNTupleMaker(const edm::ParameterSet& iConfig)
{
  
  edm::Service<TFileService> fs;
  mtree = fs->make<TTree>("Events", "Events");
 
  // Particle Flow Candidate Collection Tree initialization //
  
  mtree->Branch("nPFCandidate", &nPFCandidate);
  mtree->GetBranch("nPFCandidate")->SetTitle("Number of Particle Flow Candidates"); 
  mtree->Branch("PFCand_e", &PFCand_e);
  mtree->GetBranch("PFCand_e")->SetTitle("Particle Flow Candidate Energy");
  mtree->Branch("PFCand_pt", &PFCand_pt);
  mtree->GetBranch("PFCand_pt")->SetTitle("Particle Flow Candidate transverse momentum");
  mtree->Branch("PFCand_eta", &PFCand_eta);
  mtree->GetBranch("PFCand_eta")->SetTitle("Particle Flow Candidate pseudorapidity");
  mtree->Branch("PFCand_phi", &PFCand_phi);
  mtree->GetBranch("PFCand_phi")->SetTitle("Particle Flow Candidate polar angle");
  mtree->Branch("PFCand_mass", &PFCand_mass);
  mtree->GetBranch("PFCand_mass")->SetTitle("Particle Flow Candidate mass");
  mtree->Branch("PFCand_charge", &PFCand_charge);
  mtree->GetBranch("PFCand_charge")->SetTitle("Particle Flow Candidate charge");
  mtree->Branch("PFCand_pdgId", &PFCand_pdgId);
  mtree->GetBranch("PFCand_pdgId")->SetTitle("Particle Flow Candidate ID");
  mtree->Branch("PFCand_px", &PFCand_px);
  mtree->GetBranch("PFCand_px")->SetTitle("Particle Flow Candidate transverse momentum x-component");
  mtree->Branch("PFCand_py", &PFCand_py);
  mtree->GetBranch("PFCand_py")->SetTitle("Particle Flow Candidate transverse momentum y-component");
  mtree->Branch("PFCand_pz", &PFCand_pz);
  mtree->GetBranch("PFCand_pz")->SetTitle("Particle Flow Candidate transverse momentum z-component");
  mtree->Branch("PFCand_hoERatio", &PFCand_hoERatio);
  mtree->GetBranch("PFCand_hoERatio")->SetTitle("Particle Flow Candidate shower shape");
  mtree->Branch("PFCand_rawEcalEnergy", &PFCand_rawEcalEnergy);
  mtree->GetBranch("PFCand_rawEcalEnergy")->SetTitle("Particle Flow Candidate Raw Electron Calorimeter Energy");
  mtree->Branch("PFCand_rawHcalEnergy", &PFCand_rawHcalEnergy);
  mtree->GetBranch("PFCand_rawHcalEnergy")->SetTitle("Particle Flow Candidate Raw Hadron Calorimeter Energy");
  
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
  mtree->Branch("Jet_pdgId", &Jet_pdgId);
  mtree->GetBranch("Jet_pdgId")->SetTitle("Jet ID");
  mtree->Branch("Jet_px", &Jet_px);
  mtree->GetBranch("Jet_px")->SetTitle("Jet transverse momentum x-component");
  mtree->Branch("Jet_py", &Jet_py);
  mtree->GetBranch("Jet_py")->SetTitle("Jet transverse momentum y-component");
  mtree->Branch("Jet_pz", &Jet_pz);
  mtree->GetBranch("Jet_pz")->SetTitle("Jet transverse momentum z-component");
  mtree->Branch("Jet_nConstituents", &Jet_nConstituents);
  mtree->GetBranch("Jet_nConstituents")->SetTitle("Jet Constituents");

  // Gen Jet Collection initialization //

  mtree->Branch("nGenJet", &nGenJet);
  mtree->GetBranch("nGenJet")->SetTitle("Number of Generator Level Jets"); 
  mtree->Branch("GenJet_e", &GenJet_e);
  mtree->GetBranch("GenJet_e")->SetTitle("Generator Level Jet Energy");
  mtree->Branch("GenJet_pt", &GenJet_pt);
  mtree->GetBranch("GenJet_pt")->SetTitle("Generator Level Jet transverse momentum");
  mtree->Branch("GenJet_eta", &GenJet_eta);
  mtree->GetBranch("GenJet_eta")->SetTitle("Generator Level Jet pseudorapidity");
  mtree->Branch("GenJet_phi", &GenJet_phi);
  mtree->GetBranch("GenJet_phi")->SetTitle("Generator Level Jet polar angle");
  mtree->Branch("GenJet_mass", &GenJet_mass);
  mtree->GetBranch("GenJet_mass")->SetTitle("Generator Level Jet mass");
  mtree->Branch("GenJet_pdgId", &GenJet_pdgId);
  mtree->GetBranch("GenJet_pdgId")->SetTitle("Generator Level Jet ID");
  mtree->Branch("GenJet_px", &GenJet_px);
  mtree->GetBranch("GenJet_px")->SetTitle("Generator Level Jet transverse momentum x-component");
  mtree->Branch("GenJet_py", &GenJet_py);
  mtree->GetBranch("GenJet_py")->SetTitle("Generator Level Jet transverse momentum y-component");
  mtree->Branch("GenJet_pz", &GenJet_pz);
  mtree->GetBranch("GenJet_pz")->SetTitle("Generator Level Jet transverse momentum z-component");  
  mtree->Branch("GenJet_nConstituents", &GenJet_nConstituents);
  mtree->GetBranch("GenJet_nConstituents")->SetTitle("Generator Level Jet constituents");
  
  
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

  // Electron Collection initialization //

  mtree->Branch("nElectron", &nElectron);
  mtree->GetBranch("nElectron")->SetTitle("Number of Electrons"); 
  mtree->Branch("Electron_e", &Electron_e);
  mtree->GetBranch("Electron_e")->SetTitle("Electron Energy");
  mtree->Branch("Electron_pt", &Electron_pt);
  mtree->GetBranch("Electron_pt")->SetTitle("Electron Transverse Momentum");
  mtree->Branch("Electron_eta", &Electron_eta);
  mtree->GetBranch("Electron_eta")->SetTitle("Electron pseudorapidity");
  mtree->Branch("Electron_phi", &Electron_phi);
  mtree->GetBranch("Electron_phi")->SetTitle("Electron Polar Angle");
  mtree->Branch("Electron_mass", &Electron_mass);
  mtree->GetBranch("Electron_mass")->SetTitle("Electron mass");
  mtree->Branch("Electron_charge", &Electron_charge);
  mtree->GetBranch("Electron_charge")->SetTitle("Electron charge");
  mtree->Branch("Electron_pdgId", &Electron_pdgId);
  mtree->GetBranch("Electron_pdgId")->SetTitle("Electron pdgId");
  mtree->Branch("Electron_px", &Electron_px);
  mtree->GetBranch("Electron_px")->SetTitle("Electron Transverse momentum x-component");
  mtree->Branch("Electron_py", &Electron_py);
  mtree->GetBranch("Electron_py")->SetTitle("Electron Transverse momentum y-component");  
  mtree->Branch("Electron_pz", &Electron_pz);
  mtree->GetBranch("Electron_pz")->SetTitle("Electron Transverse momentum z-component");


  // Photon Collection initialization //

  mtree->Branch("nPhoton", &nPhoton);
  mtree->GetBranch("nPhoton")->SetTitle("Number of Photons"); 
  mtree->Branch("Photon_e", &Photon_e);
  mtree->GetBranch("Photon_e")->SetTitle("Photon Energy");
  mtree->Branch("Photon_pt", &Photon_pt);
  mtree->GetBranch("Photon_pt")->SetTitle("Photon Transverse Momentum");
  mtree->Branch("Photon_eta", &Photon_eta);
  mtree->GetBranch("Photon_eta")->SetTitle("Photon pseudorapidity");
  mtree->Branch("Photon_phi", &Photon_phi);
  mtree->GetBranch("Photon_phi")->SetTitle("Photon Polar Angle");
  mtree->Branch("Photon_mass", &Photon_mass);
  mtree->GetBranch("Photon_mass")->SetTitle("Photon mass");
  mtree->Branch("Photon_charge", &Photon_charge);
  mtree->GetBranch("Photon_charge")->SetTitle("Photon charge");
  mtree->Branch("Photon_pdgId", &Photon_pdgId);
  mtree->GetBranch("Photon_pdgId")->SetTitle("Photon pdgId");
  mtree->Branch("Photon_px", &Photon_px);
  mtree->GetBranch("Photon_px")->SetTitle("Photon Transverse momentum x-component");
  mtree->Branch("Photon_py", &Photon_py);
  mtree->GetBranch("Photon_py")->SetTitle("Photon Transverse momentum y-component");  
  mtree->Branch("Photon_pz", &Photon_pz);
  mtree->GetBranch("Photon_pz")->SetTitle("Photon Transverse momentum z-component");

  // PFTau Collection //

  mtree->Branch("nPFTau", &nPFTau);
  mtree->GetBranch("nPFTau")->SetTitle("Number of PFTaus"); 
  mtree->Branch("PFTau_e", &PFTau_e);
  mtree->GetBranch("PFTau_e")->SetTitle("PFTau Energy");
  mtree->Branch("PFTau_pt", &PFTau_pt);
  mtree->GetBranch("PFTau_pt")->SetTitle("PFTau Transverse Momentum");
  mtree->Branch("PFTau_eta", &PFTau_eta);
  mtree->GetBranch("PFTau_eta")->SetTitle("PFTau pseudorapidity");
  mtree->Branch("PFTau_phi", &PFTau_phi);
  mtree->GetBranch("PFTau_phi")->SetTitle("PFTau Polar Angle");
  mtree->Branch("PFTau_mass", &PFTau_mass);
  mtree->GetBranch("PFTau_mass")->SetTitle("PFTau mass");
  mtree->Branch("PFTau_charge", &PFTau_charge);
  mtree->GetBranch("PFTau_charge")->SetTitle("PFTau charge");
  mtree->Branch("PFTau_pdgId", &PFTau_pdgId);
  mtree->GetBranch("PFTau_pdgId")->SetTitle("PFTau pdgId");
  mtree->Branch("PFTau_px", &PFTau_px);
  mtree->GetBranch("PFTau_px")->SetTitle("PFTau Transverse momentum x-component");
  mtree->Branch("PFTau_py", &PFTau_py);
  mtree->GetBranch("PFTau_py")->SetTitle("PFTau Transverse momentum y-component");  
  mtree->Branch("PFTau_pz", &PFTau_pz);
  mtree->GetBranch("PFTau_pz")->SetTitle("PFTau Transverse momentum z-component");  

}

MasterNTupleMaker::~MasterNTupleMaker()
{
  //Put anything that needs to be deleted
  //De-allocation of memory
}

void
MasterNTupleMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
 //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

