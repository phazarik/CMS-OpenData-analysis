//C++
//Class: MasterNTupleMaker
//Original Author: Raj Handique
//Created on: 10 January 2024

//include header files//

#include "MasterNTupleMaker.h"

// -------- member functions ---------- //

//--------------------------------------------//
// This Function will collect the necessary   //
// information required from the AOD & AODSIM //
// files and put them in a Flat NTuple or a   //
// TTree - readable in ROOT                   //
//--------------------------------------------//

void 
MasterNTupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace std;

  Handle<reco::PFCandidateCollection> particleFlow;
  iEvent.getByLabel(InputTag("particleFlow"), particleFlow);

  Handle<reco::PFJetCollection> Jets;
  iEvent.getByLabel(InputTag("ak5PFJets"), Jets);

  Handle<reco::GenJetCollection> genJets;
  iEvent.getByLabel(InputTag("ak5GenJets"), genJets);

  Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(InputTag("genParticles"), genParticles);

  Handle<reco::MuonCollection> recoMuons;
  iEvent.getByLabel(InputTag("muons"), recoMuons);

  Handle<reco::GsfElectronCollection> recoElectrons;
  iEvent.getByLabel(InputTag("gsfElectrons"), recoElectrons);

  Handle<reco::PhotonCollection> recoPhotons;
  iEvent.getByLabel(InputTag("photons"), recoPhotons);

  

  //--------------------- initialization of the arrays -------------------------//
  
  // Particle Flow Candidates //

  nPFCandidate=0;
  PFCand_e.clear();
  PFCand_pt.clear();
  PFCand_eta.clear();
  PFCand_phi.clear();
  PFCand_mass.clear();
  PFCand_charge.clear();
  PFCand_pdgId.clear();
  PFCand_px.clear();
  PFCand_py.clear();
  PFCand_pz.clear();
  PFCand_hoERatio.clear();
  PFCand_rawEcalEnergy.clear();
  PFCand_rawHcalEnergy.clear();
  
  // Reco Jet Candidate //

  nJet=0;
  Jet_e.clear();
  Jet_pt.clear();
  Jet_eta.clear();
  Jet_phi.clear();
  Jet_mass.clear();
  Jet_pdgId.clear();
  Jet_px.clear();
  Jet_py.clear();
  Jet_pz.clear();

  // Gen Jet Collection //

  nGenJet=0;
  GenJet_e.clear();
  GenJet_pt.clear();
  GenJet_eta.clear();
  GenJet_phi.clear();
  GenJet_mass.clear();
  GenJet_pdgId.clear();
  GenJet_status.clear();
  GenJet_px.clear();
  GenJet_py.clear();
  GenJet_pz.clear();

  // Gen Particle Collection //

  nGenParticle=0;
  GenParticle_e.clear();
  GenParticle_pt.clear();
  GenParticle_eta.clear();
  GenParticle_phi.clear();
  GenParticle_mass.clear();
  GenParticle_pdgId.clear();
  GenParticle_status.clear();
  GenParticle_px.clear();
  GenParticle_py.clear();
  GenParticle_pz.clear();

  // Reco Muon Collection //
  nMuon=0;
  Muon_e.clear();
  Muon_pt.clear();
  Muon_eta.clear();
  Muon_phi.clear();
  Muon_mass.clear();
  Muon_pdgId.clear();
  Muon_charge.clear();
  Muon_px.clear();
  Muon_py.clear();
  Muon_pz.clear();
  
  // Reco Electron Collection //
  nElectron=0;
  Electron_e.clear();
  Electron_pt.clear();
  Electron_eta.clear();
  Electron_phi.clear();
  Electron_mass.clear();
  Electron_pdgId.clear();
  Electron_charge.clear();
  Electron_px.clear();
  Electron_py.clear();
  Electron_pz.clear();

  // Reco Photon Collection //
  nPhoton=0;
  Photon_e.clear();
  Photon_pt.clear();
  Photon_eta.clear();
  Photon_phi.clear();
  Photon_mass.clear();
  Photon_charge.clear();
  Photon_pdgId.clear();
  Photon_px.clear();
  Photon_py.clear();
  Photon_pz.clear();
  

  // Filling Particle Flow Candidates in the TTree (Flat NTuple)

  if(particleFlow.isValid()){
    
    
    for(reco::PFCandidateCollection::const_iterator pf=particleFlow->begin(); pf!=particleFlow->end(); pf++){
      
      float hoERatio = (pf->hoEnergy())/(pf->rawHoEnergy());

      if(pf->pt()>1){
	
	PFCand_e.push_back(pf->energy());
	PFCand_eta.push_back(pf->eta());
	PFCand_phi.push_back(pf->phi());
	PFCand_mass.push_back(pf->mass());
	PFCand_charge.push_back(pf->charge());
	PFCand_pdgId.push_back(pf->pdgId());
	PFCand_pt.push_back(pf->pt());
	PFCand_px.push_back(pf->px());
	PFCand_py.push_back(pf->py());
	PFCand_pz.push_back(pf->pz());

	PFCand_hoERatio.push_back(hoERatio);
	PFCand_rawEcalEnergy.push_back(pf->rawEcalEnergy());
	PFCand_rawHcalEnergy.push_back(pf->rawHcalEnergy());
      }

      nPFCandidate=PFCand_pt.size();
    }    
  }

  // Filling RecoJet Collection in the TTree (Flat NTuple)

  if(Jets.isValid()){
    
    
    for(reco::PFJetCollection::const_iterator rJet=Jets->begin(); rJet!=Jets->end(); rJet++){
      
      if(rJet->pt()>0.8){
	
	Jet_e.push_back(rJet->energy());
	Jet_pt.push_back(rJet->pt());	
	Jet_eta.push_back(rJet->eta());
	Jet_phi.push_back(rJet->phi());
	Jet_mass.push_back(rJet->mass());
	Jet_pdgId.push_back(rJet->pdgId());
	Jet_px.push_back(rJet->px());
	Jet_py.push_back(rJet->py());
	Jet_pz.push_back(rJet->pz());
      }

       nJet=Jet_pt.size();
    }
  }

  // Filling GenJet Collection in the TTree (Flat NTuple)
  
  if(genJets.isValid()){
    
    for(reco::GenJetCollection::const_iterator gJet=genJets->begin(); gJet!=genJets->end(); gJet++){
      
      if(gJet->pt()>0.8){
	
	GenJet_e.push_back(gJet->energy());
	GenJet_pt.push_back(gJet->pt());	
	GenJet_eta.push_back(gJet->eta());
	GenJet_phi.push_back(gJet->phi());
	GenJet_mass.push_back(gJet->mass());
	GenJet_pdgId.push_back(gJet->pdgId());
	GenJet_status.push_back(gJet->status());
	GenJet_px.push_back(gJet->px());
	GenJet_py.push_back(gJet->py());
	GenJet_pz.push_back(gJet->pz());
      }

      nGenJet=GenJet_pt.size();
    }
  }
  
  //Filling Generator Level Particles in the TTree (Flat NTuple)

  if(genParticles.isValid()){
    
    
    for(reco::GenParticleCollection::const_iterator genPart=genParticles->begin(); genPart!=genParticles->end(); genPart++){
      
      if(genPart->pt()>0.8){
	
	GenParticle_e.push_back(genPart->energy());
	GenParticle_pt.push_back(genPart->pt());
	GenParticle_eta.push_back(genPart->eta());
	GenParticle_phi.push_back(genPart->phi());
	GenParticle_mass.push_back(genPart->mass());
	GenParticle_pdgId.push_back(genPart->pdgId());
	GenParticle_status.push_back(genPart->status());
	GenParticle_px.push_back(genPart->px());
	GenParticle_py.push_back(genPart->py());
	GenParticle_pz.push_back(genPart->pz());
      }

      nGenParticle=GenParticle_pt.size();
    }
  }

  // Filling up Muons in the TTree (Flat NTuple)
  
  if(recoMuons.isValid()){

    for(reco::MuonCollection::const_iterator rMuon=recoMuons->begin(); rMuon!=recoMuons->end(); rMuon++ ){
      if(rMuon->pt()>3){
	
	Muon_e.push_back(rMuon->energy());
	Muon_pt.push_back(rMuon->pt());
	Muon_eta.push_back(rMuon->eta());
	Muon_phi.push_back(rMuon->phi());
	Muon_mass.push_back(rMuon->mass());
	Muon_pdgId.push_back(rMuon->pdgId());
	Muon_charge.push_back(rMuon->charge());
        Muon_px.push_back(rMuon->px());
	Muon_py.push_back(rMuon->py());
	Muon_pz.push_back(rMuon->pz());
      }
      nMuon=Muon_pt.size();
    }
  }

  // Filling up Electron in the TTree (Flat NTuple)

  if(recoElectrons.isValid()){
    
    for(reco::GsfElectronCollection::const_iterator rElectron=recoElectrons->begin(); rElectron!=recoElectrons->end(); rElectron++){
      if(rElectron->pt()>3){
	
	Electron_e.push_back(rElectron->energy());
	Electron_pt.push_back(rElectron->pt());
	Electron_eta.push_back(rElectron->eta());
	Electron_phi.push_back(rElectron->phi());
	Electron_mass.push_back(rElectron->mass());
	Electron_pdgId.push_back(rElectron->pdgId());
	Electron_charge.push_back(rElectron->charge());
	Electron_px.push_back(rElectron->px());
	Electron_py.push_back(rElectron->py());
	Electron_pz.push_back(rElectron->pz());
      }
      nElectron=Electron_pt.size();
    }
  }

  // Filling Photons in the TTree (Flat NTuple)

  if(recoPhotons.isValid()){
    
    for(reco::PhotonCollection::const_iterator rPhoton=recoPhotons->begin(); rPhoton!=recoPhotons->end(); rPhoton++){
      if(rPhoton->pt()>3){
	
	Photon_e.push_back(rPhoton->energy());
	Photon_pt.push_back(rPhoton->pt());
	Photon_eta.push_back(rPhoton->eta());
	Photon_phi.push_back(rPhoton->phi());
	Photon_mass.push_back(rPhoton->mass());
	Photon_pdgId.push_back(rPhoton->pdgId());
	Photon_charge.push_back(rPhoton->charge());
	Photon_px.push_back(rPhoton->px());
	Photon_py.push_back(rPhoton->py());
	Photon_pz.push_back(rPhoton->pz());
      }
      nPhoton=Photon_pt.size();
    }
  }
  
  mtree->Fill();
  return;
  
}

DEFINE_FWK_MODULE(MasterNTupleMaker);
