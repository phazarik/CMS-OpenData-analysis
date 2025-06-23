/*=============================
Header file for miniNtupleMaker
==============================*/

#ifndef MININTUPLEMAKER_H
#define MININTUPLEMAKER_H

//---------------------------------
// system include files
//---------------------------------
#include <memory>
#include <vector>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/View.h"

//---------------------------------
// user include files
//---------------------------------

// For pat objects
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/MET.h"

// For gen objects
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"

// ROOT Objects
#include "TTree.h"
#include "TFile.h"

using namespace std;
using namespace edm;

// Class Declaration //
class miniNtupleMaker : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
    explicit miniNtupleMaker(const edm::ParameterSet&);
    ~miniNtupleMaker() override;
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
    void beginJob() override;
    void analyze(const edm::Event&, const edm::EventSetup&) override;
    void endJob() override;
    // ----- member data ----- //
    edm::EDGetTokenT<pat::MuonCollection> muonToken_;
    edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
    edm::EDGetTokenT<pat::JetCollection> jetToken_;
    edm::EDGetTokenT<pat::PhotonCollection> photonToken_;
    edm::EDGetTokenT<pat::TauCollection> tauToken_;
    edm::EDGetTokenT<pat::METCollection> metToken_;
    edm::EDGetTokenT<reco::GenParticleCollection> genParticleToken_;
    edm::EDGetTokenT<reco::GenJetCollection> genJetToken_;  

    TTree *mTree;

    // Particle collection initialisation //

    int nMuons;
    std::vector<float> muonEnergy;
    std::vector<float> muonPt;
    std::vector<float> muonEta;
    std::vector<float> muonPhi;
    std::vector<float> muonMass;
    std::vector<int> muonCharge;
    std::vector<int> muonPdgId;
    std::vector<float> muonPx;
    std::vector<float> muonPy;
    std::vector<float> muonPz;

    int nElectrons;
    std::vector<float> electronEnergy;
    std::vector<float> electronPt;
    std::vector<float> electronEta;
    std::vector<float> electronPhi;
    std::vector<float> electronMass;
    std::vector<int> electronCharge;
    std::vector<int> electronPdgId;
    std::vector<float> electronPx;
    std::vector<float> electronPy;
    std::vector<float> electronPz;

    int nJets;
    std::vector<float> jetEnergy;
    std::vector<float> jetPt;
    std::vector<float> jetEta;
    std::vector<float> jetPhi;
    std::vector<float> jetMass;
    std::vector<int> jetPdgId;
    std::vector<float> jetPx;
    std::vector<float> jetPy;
    std::vector<float> jetPz;

    int nPhotons;
    std::vector<float> photonEnergy;
    std::vector<float> photonPt;
    std::vector<float> photonEta;
    std::vector<float> photonPhi;
    std::vector<float> photonMass;
    std::vector<int> photonPdgId;
    std::vector<float> photonPx;
    std::vector<float> photonPy;
    std::vector<float> photonPz;

    int nTaus;
    std::vector<float> tauEnergy;
    std::vector<float> tauPt;
    std::vector<float> tauEta;
    std::vector<float> tauPhi;
    std::vector<float> tauMass;
    std::vector<int> tauCharge;
    std::vector<int> tauPdgId;
    std::vector<float> tauPx;
    std::vector<float> tauPy;
    std::vector<float> tauPz;

    int nMETs;
    std::vector<float> metEnergy;
    std::vector<float> metPt;
    std::vector<float> metEta;
    std::vector<float> metPhi;
    std::vector<float> metPx;
    std::vector<float> metPy;
    std::vector<float> metPz;

    int nGenParticles;
    std::vector<float> genParticleEnergy;
    std::vector<float> genParticlePt;
    std::vector<float> genParticleEta;
    std::vector<float> genParticlePhi;
    std::vector<float> genParticleMass;
    std::vector<int> genParticlePdgId;
    std::vector<int> genParticleStatus;
    std::vector<float> genParticlePx;
    std::vector<float> genParticlePy;
    std::vector<float> genParticlePz;

    int nGenJets;
    std::vector<float> genJetEnergy;
    std::vector<float> genJetPt;
    std::vector<float> genJetEta;
    std::vector<float> genJetPhi;
    std::vector<float> genJetMass;
    std::vector<float> genJetPx;
    std::vector<float> genJetPy;
    std::vector<float> genJetPz;


};  

miniNtupleMaker::miniNtupleMaker(const edm::ParameterSet& iConfig) {
    // Constructor implementation
    edm::Service<TFileService> fs;
    mTree = fs->make<TTree>("Events", "EventInfo"); 

    // Initialize branches for the tree
    mTree->Branch("nMuons", &nMuons, "nMuons/I");
    mTree->GetBranch("nMuons")->SetTitle("Number of muons in the event");
    mTree->Branch("muonEnergy", &muonEnergy);
    mTree->GetBranch("muonEnergy")->SetTitle("Energy of muons");
    mTree->Branch("muonPt", &muonPt);
    mTree->GetBranch("muonPt")->SetTitle("Transverse momentum of muons");
    mTree->Branch("muonEta", &muonEta);
    mTree->GetBranch("muonEta")->SetTitle("Pseudorapidity of muons");
    mTree->Branch("muonPhi", &muonPhi);
    mTree->GetBranch("muonPhi")->SetTitle("Azimuthal angle of muons");
    mTree->Branch("muonMass", &muonMass);
    mTree->GetBranch("muonMass")->SetTitle("Mass of muons");
    mTree->Branch("muonCharge", &muonCharge);
    mTree->GetBranch("muonCharge")->SetTitle("Charge of muons");
    mTree->Branch("muonPdgId", &muonPdgId);
    mTree->GetBranch("muonPdgId")->SetTitle("PDG ID of muons");
    mTree->Branch("muonPx", &muonPx); 
    mTree->GetBranch("muonPx")->SetTitle("X component of muon momentum");
    mTree->Branch("muonPy", &muonPy);
    mTree->GetBranch("muonPy")->SetTitle("Y component of muon momentum");
    mTree->Branch("muonPz", &muonPz);   
    mTree->GetBranch("muonPz")->SetTitle("Z component of muon momentum");

    mTree->Branch("nElectrons", &nElectrons, "nElectrons/I");
    mTree->GetBranch("nElectrons")->SetTitle("Number of electrons in the event");
    mTree->Branch("electronEnergy", &electronEnergy);
    mTree->GetBranch("electronEnergy")->SetTitle("Energy of electrons");
    mTree->Branch("electronPt", &electronPt);
    mTree->GetBranch("electronPt")->SetTitle("Transverse momentum of electrons");
    mTree->Branch("electronEta", &electronEta);
    mTree->GetBranch("electronEta")->SetTitle("Pseudorapidity of electrons");
    mTree->Branch("electronPhi", &electronPhi);
    mTree->GetBranch("electronPhi")->SetTitle("Azimuthal angle of electrons");
    mTree->Branch("electronMass", &electronMass);
    mTree->GetBranch("electronMass")->SetTitle("Mass of electrons");
    mTree->Branch("electronCharge", &electronCharge);
    mTree->GetBranch("electronCharge")->SetTitle("Charge of electrons");
    mTree->Branch("electronPdgId", &electronPdgId);
    mTree->GetBranch("electronPdgId")->SetTitle("PDG ID of electrons");
    mTree->Branch("electronPx", &electronPx);
    mTree->GetBranch("electronPx")->SetTitle("X component of electron momentum");
    mTree->Branch("electronPy", &electronPy);
    mTree->GetBranch("electronPy")->SetTitle("Y component of electron momentum");
    mTree->Branch("electronPz", &electronPz);   
    mTree->GetBranch("electronPz")->SetTitle("Z component of electron momentum");

    mTree->Branch("nJets", &nJets, "nJets/I");
    mTree->GetBranch("nJets")->SetTitle("Number of jets in the event");
    mTree->Branch("jetEnergy", &jetEnergy);
    mTree->GetBranch("jetEnergy")->SetTitle("Energy of jets");
    mTree->Branch("jetPt", &jetPt);
    mTree->GetBranch("jetPt")->SetTitle("Transverse momentum of jets");
    mTree->Branch("jetEta", &jetEta);
    mTree->GetBranch("jetEta")->SetTitle("Pseudorapidity of jets");
    mTree->Branch("jetPhi", &jetPhi);
    mTree->GetBranch("jetPhi")->SetTitle("Azimuthal angle of jets");
    mTree->Branch("jetMass", &jetMass);
    mTree->GetBranch("jetMass")->SetTitle("Mass of jets");
    mTree->Branch("jetPdgId", &jetPdgId);
    mTree->GetBranch("jetPdgId")->SetTitle("PDG ID of jets");
    mTree->Branch("jetPx", &jetPx);
    mTree->GetBranch("jetPx")->SetTitle("X component of jet momentum");
    mTree->Branch("jetPy", &jetPy);
    mTree->GetBranch("jetPy")->SetTitle("Y component of jet momentum");
    mTree->Branch("jetPz", &jetPz);
    mTree->GetBranch("jetPz")->SetTitle("Z component of jet momentum");

    mTree->Branch("nPhotons", &nPhotons, "nPhotons/I");
    mTree->GetBranch("nPhotons")->SetTitle("Number of photons in the event");
    mTree->Branch("photonEnergy", &photonEnergy);   
    mTree->GetBranch("photonEnergy")->SetTitle("Energy of photons");
    mTree->Branch("photonPt", &photonPt);
    mTree->GetBranch("photonPt")->SetTitle("Transverse momentum of photons");
    mTree->Branch("photonEta", &photonEta);
    mTree->GetBranch("photonEta")->SetTitle("Pseudorapidity of photons");
    mTree->Branch("photonPhi", &photonPhi);
    mTree->GetBranch("photonPhi")->SetTitle("Azimuthal angle of photons");
    mTree->Branch("photonMass", &photonMass);   
    mTree->GetBranch("photonMass")->SetTitle("Mass of photons");
    mTree->Branch("photonPdgId", &photonPdgId);
    mTree->GetBranch("photonPdgId")->SetTitle("PDG ID of photons");
    mTree->Branch("photonPx", &photonPx);
    mTree->GetBranch("photonPx")->SetTitle("X component of photon momentum");
    mTree->Branch("photonPy", &photonPy);
    mTree->GetBranch("photonPy")->SetTitle("Y component of photon momentum");
    mTree->Branch("photonPz", &photonPz);
    mTree->GetBranch("photonPz")->SetTitle("Z component of photon momentum");

    mTree->Branch("nTaus", &nTaus, "nTaus/I");
    mTree->GetBranch("nTaus")->SetTitle("Number of taus in the event");
    mTree->Branch("tauEnergy", &tauEnergy);
    mTree->GetBranch("tauEnergy")->SetTitle("Energy of taus");
    mTree->Branch("tauPt", &tauPt);
    mTree->GetBranch("tauPt")->SetTitle("Transverse momentum of taus");
    mTree->Branch("tauEta", &tauEta);
    mTree->GetBranch("tauEta")->SetTitle("Pseudorapidity of taus");
    mTree->Branch("tauPhi", &tauPhi);
    mTree->GetBranch("tauPhi")->SetTitle("Azimuthal angle of taus");
    mTree->Branch("tauMass", &tauMass);
    mTree->GetBranch("tauMass")->SetTitle("Mass of taus");
    mTree->Branch("tauCharge", &tauCharge);
    mTree->GetBranch("tauCharge")->SetTitle("Charge of taus");
    mTree->Branch("tauPdgId", &tauPdgId);
    mTree->GetBranch("tauPdgId")->SetTitle("PDG ID of taus");
    mTree->Branch("tauPx", &tauPx);
    mTree->GetBranch("tauPx")->SetTitle("X component of tau momentum");
    mTree->Branch("tauPy", &tauPy);
    mTree->GetBranch("tauPy")->SetTitle("Y component of tau momentum");
    mTree->Branch("tauPz", &tauPz);
    mTree->GetBranch("tauPz")->SetTitle("Z component of tau momentum");

    mTree->Branch("nMETs", &nMETs, "nMETs/I");
    mTree->GetBranch("nMETs")->SetTitle("Number of METs in the event");
    mTree->Branch("metEnergy", &metEnergy);
    mTree->GetBranch("metEnergy")->SetTitle("Energy of MET");
    mTree->Branch("metPt", &metPt);
    mTree->GetBranch("metPt")->SetTitle("Transverse momentum of MET");
    mTree->Branch("metEta", &metEta);
    mTree->GetBranch("metEta")->SetTitle("Pseudorapidity of MET");
    mTree->Branch("metPhi", &metPhi);
    mTree->GetBranch("metPhi")->SetTitle("Azimuthal angle of MET");
    mTree->Branch("metPx", &metPx);
    mTree->GetBranch("metPx")->SetTitle("X component of MET momentum");
    mTree->Branch("metPy", &metPy);
    mTree->GetBranch("metPy")->SetTitle("Y component of MET momentum");
    mTree->Branch("metPz", &metPz);
    mTree->GetBranch("metPz")->SetTitle("Z component of MET momentum");
    
    mTree->Branch("nGenParticles", &nGenParticles, "nGenParticles/I");
    mTree->GetBranch("nGenParticles")->SetTitle("Number of generator-level particles in the event");
    mTree->Branch("genParticleEnergy", &genParticleEnergy);
    mTree->GetBranch("genParticleEnergy")->SetTitle("Energy of generator-level particles");
    mTree->Branch("genParticlePt", &genParticlePt);
    mTree->GetBranch("genParticlePt")->SetTitle("Transverse momentum of generator-level particles");
    mTree->Branch("genParticleEta", &genParticleEta);
    mTree->GetBranch("genParticleEta")->SetTitle("Pseudorapidity of generator-level particles");
    mTree->Branch("genParticlePhi", &genParticlePhi);
    mTree->GetBranch("genParticlePhi")->SetTitle("Azimuthal angle of generator-level particles");
    mTree->Branch("genParticleMass", &genParticleMass); 
    mTree->GetBranch("genParticleMass")->SetTitle("Mass of generator-level particles");
    mTree->Branch("genParticlePdgId", &genParticlePdgId);
    mTree->GetBranch("genParticlePdgId")->SetTitle("PDG ID of generator-level particles");
    mTree->Branch("genParticleStatus", &genParticleStatus);
    mTree->GetBranch("genParticleStatus")->SetTitle("Status of generator-level particles");
    mTree->Branch("genParticlePx", &genParticlePx);
    mTree->GetBranch("genParticlePx")->SetTitle("X component of generator-level particle momentum");
    mTree->Branch("genParticlePy", &genParticlePy);
    mTree->GetBranch("genParticlePy")->SetTitle("Y component of generator-level particle momentum");
    mTree->Branch("genParticlePz", &genParticlePz);
    mTree->GetBranch("genParticlePz")->SetTitle("Z component of generator-level particle momentum");

    mTree->Branch("nGenJets", &nGenJets, "nGenJets/I");
    mTree->GetBranch("nGenJets")->SetTitle("Number of generator-level jets in the event");
    mTree->Branch("genJetEnergy", &genJetEnergy);
    mTree->GetBranch("genJetEnergy")->SetTitle("Energy of generator-level jets");
    mTree->Branch("genJetPt", &genJetPt);
    mTree->GetBranch("genJetPt")->SetTitle("Transverse momentum of generator-level jets");
    mTree->Branch("genJetEta", &genJetEta);
    mTree->GetBranch("genJetEta")->SetTitle("Pseudorapidity of generator-level jets");
    mTree->Branch("genJetPhi", &genJetPhi);
    mTree->GetBranch("genJetPhi")->SetTitle("Azimuthal angle of generator-level jets");
    mTree->Branch("genJetMass", &genJetMass);
    mTree->GetBranch("genJetMass")->SetTitle("Mass of generator-level jets");
    mTree->Branch("genJetPx", &genJetPx);
    mTree->GetBranch("genJetPx")->SetTitle("X component of generator-level jet momentum");
    mTree->Branch("genJetPy", &genJetPy);
    mTree->GetBranch("genJetPy")->SetTitle("Y component of generator-level jet momentum");
    mTree->Branch("genJetPz", &genJetPz);
    mTree->GetBranch("genJetPz")->SetTitle("Z component of generator-level jet momentum");

}   

miniNtupleMaker::~miniNtupleMaker(){
    // Destructor implementation
}

void miniNtupleMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    // Function to fill the descriptions of the parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    // Add parameters here if needed
    descriptions.addDefault(desc);
}


#endif