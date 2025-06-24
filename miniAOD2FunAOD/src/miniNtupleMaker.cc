//-----------------------------------------------------
// Original Author: Raj Handique
// Date Created: 20 June 2025
// C/C++ Source Code
// FunAOD NtupleMaker from miniAOD
//-----------------------------------------------------

#include "miniNtupleMaker.h"

//---------------------------------
// user defined functions
//---------------------------------

using namespace std;

void
miniNtupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    // Analyze the event and fill the ntuple
    // This function will be implemented later
    
    using namespace edm;

    edm::Handle<pat::MuonCollection> recoMuons;
    iEvent.getByToken(muonToken_, recoMuons);
    edm::Handle<pat::ElectronCollection> recoElectrons;
    iEvent.getByToken(electronToken_, recoElectrons);
    edm::Handle<pat::JetCollection> recoJets;
    iEvent.getByToken(jetToken_, recoJets);
    edm::Handle<pat::PhotonCollection> recoPhotons;
    iEvent.getByToken(photonToken_, recoPhotons);
    edm::Handle<pat::TauCollection> recoTaus;
    iEvent.getByToken(tauToken_, recoTaus);
    edm::Handle<pat::METCollection> recoMETs;
    iEvent.getByToken(metToken_, recoMETs);
    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByToken(genParticleToken_, genParticles);
    edm::Handle<reco::GenJetCollection> genJets;
    iEvent.getByToken(genJetToken_, genJets);

    //------------------------ initialisation of vectors ------------------------//

    nMuons = 0;
    muonEnergy.clear();
    muonPt.clear();
    muonEta.clear();
    muonPhi.clear();
    muonMass.clear();
    muonCharge.clear();
    muonPdgId.clear();
    muonPx.clear();
    muonPy.clear();
    muonPz.clear();

    nElectrons = 0;
    electronEnergy.clear();
    electronPt.clear();
    electronEta.clear();         
    electronPhi.clear();
    electronMass.clear();
    electronCharge.clear();
    electronPdgId.clear();
    electronPx.clear();
    electronPy.clear();
    electronPz.clear();

    nJets = 0;
    jetEnergy.clear();
    jetPt.clear();
    jetEta.clear();
    jetPhi.clear();
    jetMass.clear();
    jetPdgId.clear();
    jetPx.clear();
    jetPy.clear();
    jetPz.clear();

    nPhotons = 0;
    photonEnergy.clear();
    photonPt.clear();
    photonEta.clear();
    photonPhi.clear();
    photonMass.clear();
    photonPdgId.clear();
    photonPx.clear();
    photonPy.clear();
    photonPz.clear();

    nTaus = 0;
    tauEnergy.clear();
    tauPt.clear();
    tauEta.clear();
    tauPhi.clear();
    tauMass.clear();
    tauCharge.clear();
    tauPdgId.clear();
    tauPx.clear();
    tauPy.clear();
    tauPz.clear();

    nMETs = 0;
    metEnergy.clear();
    metPt.clear();
    metEta.clear();
    metPhi.clear();
    metPx.clear();
    metPy.clear();
    metPz.clear();

    nGenParticles = 0;
    genParticleEnergy.clear();
    genParticlePt.clear();
    genParticleEta.clear();
    genParticlePhi.clear();
    genParticleMass.clear();
    genParticlePdgId.clear();
    genParticleStatus.clear();
    genParticlePx.clear();
    genParticlePy.clear();
    genParticlePz.clear();

    nGenJets = 0;
    genJetEnergy.clear();
    genJetPt.clear();
    genJetEta.clear();
    genJetPhi.clear();
    genJetMass.clear();
    genJetPx.clear();
    genJetPy.clear();
    genJetPz.clear();

    //------------------------ filling the vectors ------------------------//

    if(recoMuons.isValid()) {
        for(const auto& muon : *recoMuons){
            muonEnergy.push_back(muon.energy());
            muonPt.push_back(muon.pt());
            muonEta.push_back(muon.eta());
            muonPhi.push_back(muon.phi());
            muonMass.push_back(muon.mass());
            muonCharge.push_back(muon.charge());
            muonPdgId.push_back(muon.pdgId());
            muonPx.push_back(muon.px());
            muonPy.push_back(muon.py());
            muonPz.push_back(muon.pz());
        }
        nMuons = muonPt.size();
    }

    if(recoElectrons.isValid()) {
        for(const auto& electron : *recoElectrons){
            electronEnergy.push_back(electron.energy());
            electronPt.push_back(electron.pt());
            electronEta.push_back(electron.eta());
            electronPhi.push_back(electron.phi());
            electronMass.push_back(electron.mass());
            electronCharge.push_back(electron.charge());
            electronPdgId.push_back(electron.pdgId());
            electronPx.push_back(electron.px());
            electronPy.push_back(electron.py());
            electronPz.push_back(electron.pz());
        }
        nElectrons = electronPt.size();
    }

    if(recoJets.isValid()) {
        for(const auto& jet : *recoJets){
            jetEnergy.push_back(jet.energy());
            jetPt.push_back(jet.pt());
            jetEta.push_back(jet.eta());
            jetPhi.push_back(jet.phi());
            jetMass.push_back(jet.mass());
            jetPdgId.push_back(jet.pdgId());
            jetPx.push_back(jet.px());
            jetPy.push_back(jet.py());
            jetPz.push_back(jet.pz());
        }
        nJets = jetPt.size();
    }

    if(recoPhotons.isValid()) {
        for(const auto& photon : *recoPhotons){
            photonEnergy.push_back(photon.energy());
            photonPt.push_back(photon.pt());
            photonEta.push_back(photon.eta());
            photonPhi.push_back(photon.phi());
            photonMass.push_back(photon.mass());
            photonPdgId.push_back(photon.pdgId());
            photonPx.push_back(photon.px());
            photonPy.push_back(photon.py());
            photonPz.push_back(photon.pz());
        }
        nPhotons = photonPt.size();
    }

    if(recoTaus.isValid()) {
        for(const auto& tau : *recoTaus){
            tauEnergy.push_back(tau.energy());
            tauPt.push_back(tau.pt());
            tauEta.push_back(tau.eta());
            tauPhi.push_back(tau.phi());
            tauMass.push_back(tau.mass());
            tauCharge.push_back(tau.charge());
            tauPdgId.push_back(tau.pdgId());
            tauPx.push_back(tau.px());
            tauPy.push_back(tau.py());
            tauPz.push_back(tau.pz());
        }
        nTaus = tauPt.size();
    }

    if(recoMETs.isValid()) {
        for(const auto& met : *recoMETs){
            metEnergy.push_back(met.energy());
            metPt.push_back(met.pt());
            metEta.push_back(met.eta());
            metPhi.push_back(met.phi());
            metPx.push_back(met.px());
            metPy.push_back(met.py());
            metPz.push_back(met.pz());
        }
        nMETs = metPt.size();
    }

    if(genParticles.isValid()) {
        for(const auto& genParticle : *genParticles){
            genParticleEnergy.push_back(genParticle.energy());
            genParticlePt.push_back(genParticle.pt());
            genParticleEta.push_back(genParticle.eta());
            genParticlePhi.push_back(genParticle.phi());
            genParticleMass.push_back(genParticle.mass());
            genParticlePdgId.push_back(genParticle.pdgId());
            genParticleStatus.push_back(genParticle.status());
            genParticlePx.push_back(genParticle.px());
            genParticlePy.push_back(genParticle.py());
            genParticlePz.push_back(genParticle.pz());
        }
        nGenParticles = genParticlePt.size();
    }

    if(genJets.isValid()) {
        for(const auto& genJet : *genJets){
            genJetEnergy.push_back(genJet.energy());
            genJetPt.push_back(genJet.pt());
            genJetEta.push_back(genJet.eta());
            genJetPhi.push_back(genJet.phi());
            genJetMass.push_back(genJet.mass());
            genJetPx.push_back(genJet.px());
            genJetPy.push_back(genJet.py());
            genJetPz.push_back(genJet.pz());
        }
        nGenJets = genJetPt.size();
    }

    mTree->Fill();
    return;

}

void
miniNtupleMaker::beginJob(){
    std::cout<<"miniNtupleMaker has started!"<<std::endl;
}
void
miniNtupleMaker::endJob(){
    std::cout<<"miniNtupleMaker has ended!"<<std::endl;
}
DEFINE_FWK_MODULE(miniNtupleMaker);


