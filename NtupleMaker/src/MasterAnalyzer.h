//C++
//Class: MasterAnalyzer_headerfile
//Original Author: Raj Handique
//Created on: 28 December 2023

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
#include "DataFormats/ParticleFlowCandidate/interface/IsolatedPFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/IsolatedPFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateElectronExtra.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateElectronExtraFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidatePhotonExtra.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidatePhotonExtraFwd.h"

//class to extract Reco Jets

#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

//class to extract GenJet

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"

//class to extract GenParticles

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"


//files to read

#include "TTree.h"
#include "TFile.h"

class MasterAnalyzer : public edm::EDAnalyzer{
 public:
  explicit MasterAnalyzer(const edm::ParameterSet&);
  ~MasterAnalyzer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
 private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
  // -------------- member data --------------------
  
  TTree *mtree;
  
  // Particle Flow Candidates Collection initialization 

  int numPFCandidates;
  std::vector<float> PFCand_e;
  std::vector<float> PFCand_pt;
  std::vector<float> PFCand_eta;
  std::vector<float> PFCand_phi;
  std::vector<float> PFCand_mass;
  std::vector<float> PFCand_charge;
  std::vector<int> PFCand_pdgId;
  std::vector<int> PFCand_status;
  std::vector<float> PFCand_px;
  std::vector<float> PFCand_py;
  std::vector<float> PFCand_pz;
  std::vector<float> PFCand_hoERatio;
  std::vector<float> PFCand_rawEcalEnergy;
  std::vector<float> PFCand_rawHcalEnergy;

  // Reco Jet atkt5 Collection initialization

  int numRecoJets;
  std::vector<float> RecoJet_e;
  std::vector<float> RecoJet_pt;
  std::vector<float> RecoJet_eta;
  std::vector<float> RecoJet_phi;
  std::vector<float> RecoJet_mass;
  std::vector<int> RecoJet_pdgId;
  std::vector<int> RecoJet_status;
  std::vector<float> RecoJet_px;
  std::vector<float> RecoJet_py;
  std::vector<float> RecoJet_pz;

  // Gen Jet Collection initialization

  int numGenJets;
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

  // Gen Particle Collection initialization
  
  int numGenParticles;
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

}; 

// Constructor & Destructor

MasterAnalyzer::MasterAnalyzer(const edm::ParameterSet& iConfig)
{
  
  edm::Service<TFileService> fs;
  mtree = fs->make<TTree>("Events", "Events");
 
  // Particle Flow Candidate Collection Tree initialization //
  
  mtree->Branch("numPFCandidates", &numPFCandidates);
  mtree->GetBranch("numPFCandidates")->SetTitle("Number of Particle Flow Candidates"); 
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
  mtree->Branch("PFCand_status", &PFCand_status);
  mtree->GetBranch("PFCand_status")->SetTitle("Particle Flow Candidate status");
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

  mtree->Branch("numRecoJets", &numRecoJets);
  mtree->GetBranch("numRecoJets")->SetTitle("Number of Reconstructed Jets"); 
  mtree->Branch("RecoJet_e", &RecoJet_e);
  mtree->GetBranch("RecoJet_e")->SetTitle("Reconstructed Jet Energy");
  mtree->Branch("RecoJet_pt", &RecoJet_pt);
  mtree->GetBranch("RecoJet_pt")->SetTitle("Reconstructed Jet transverse momentum");
  mtree->Branch("RecoJet_eta", &RecoJet_eta);
  mtree->GetBranch("RecoJet_eta")->SetTitle("Reconstructed Jet pseudorapidity");
  mtree->Branch("RecoJet_phi", &RecoJet_phi);
  mtree->GetBranch("RecoJet_phi")->SetTitle("Reconstructed Jet polar angle");
  mtree->Branch("RecoJet_mass", &RecoJet_mass);
  mtree->GetBranch("RecoJet_mass")->SetTitle("Reconstructed Jet mass");
  mtree->Branch("RecoJet_pdgId", &RecoJet_pdgId);
  mtree->GetBranch("RecoJet_pdgId")->SetTitle("Reconstructed Jet ID");
  mtree->Branch("RecoJet_status", &RecoJet_status);
  mtree->GetBranch("RecoJet_status")->SetTitle("Reconstructed Jet status");
  mtree->Branch("RecoJet_px", &RecoJet_px);
  mtree->GetBranch("RecoJet_px")->SetTitle("Reconstructed Jet transverse momentum x-component");
  mtree->Branch("RecoJet_py", &RecoJet_py);
  mtree->GetBranch("RecoJet_py")->SetTitle("Reconstructed Jet transverse momentum y-component");
  mtree->Branch("RecoJet_pz", &RecoJet_pz);
  mtree->GetBranch("RecoJet_pz")->SetTitle("Reconstructed Jet transverse momentum z-component");

  // Gen Jet Collection initialization //

  mtree->Branch("numGenJets", &numGenJets);
  mtree->GetBranch("numGenJets")->SetTitle("Number of Generator Level Jets"); 
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
  mtree->Branch("GenJet_status", &GenJet_status);
  mtree->GetBranch("GenJet_status")->SetTitle("Generator Level Jet status");
  mtree->Branch("GenJet_px", &GenJet_px);
  mtree->GetBranch("GenJet_px")->SetTitle("Generator Level Jet transverse momentum x-component");
  mtree->Branch("GenJet_py", &GenJet_py);
  mtree->GetBranch("GenJet_py")->SetTitle("Generator Level Jet transverse momentum y-component");
  mtree->Branch("GenJet_pz", &GenJet_pz);
  mtree->GetBranch("GenJet_pz")->SetTitle("Generator Level Jet transverse momentum z-component");  
  
  // Gen Particle Collection initialization //

  mtree->Branch("numGenParticles", &numGenParticles);
  mtree->GetBranch("numGenParticles")->SetTitle("Number of Generator Level Particles"); 
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
  mtree->Branch("GenParticle_status", &GenParticle_status);
  mtree->GetBranch("GenParticle_status")->SetTitle("Generator Level Particle status");
  mtree->Branch("GenParticle_px", &GenParticle_px);
  mtree->GetBranch("GenParticle_px")->SetTitle("Generator Level Particle transverse momentum x-component");
  mtree->Branch("GenParticle_py", &GenParticle_py);
  mtree->GetBranch("GenParticle_py")->SetTitle("Generator Level Particle transverse momentum y-component");
  mtree->Branch("GenParticle_pz", &GenParticle_pz);
  mtree->GetBranch("GenParticle_pz")->SetTitle("Generator Level Particle transverse momentum z-component");  

}

MasterAnalyzer::~MasterAnalyzer()
{
  //Put anything that needs to be deleted
  //De-allocation of memory
}

void
MasterAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
 //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

