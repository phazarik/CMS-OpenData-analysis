//C++
//Class: MasterAnalyzer
//Original Author: Raj Handique
//Created on: 28 December 2023

//include header files//

#include "MasterAnalyzer.h"

// -------- member functions ---------- //

//--------------------------------------------//
// This Function will collect the necessary   //
// information required from the AOD & AODSIM //
// files and put them in a Flat NTuple or a   //
// TTree - readable in ROOT                   //
//--------------------------------------------//

void 
MasterAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace std;

  Handle<reco::PFCandidateCollection> particleFlow;
  iEvent.getByLabel(InputTag("particleFlow"), particleFlow);

  Handle<reco::PFJetCollection> recoJets;
  iEvent.getByLabel(InputTag("ak5PFJets"), recoJets);

  Handle<reco::GenJetCollection> genJets;
  iEvent.getByLabel(InputTag("ak5GenJets"), genJets);

  Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(InputTag("genParticles"), genParticles);

  //--------------------- initialization of the arrays -------------------------//
  
  // Particle Flow Candidates //

  numPFCandidates=0;
  PFCand_e.clear();
  PFCand_pt.clear();
  PFCand_eta.clear();
  PFCand_phi.clear();
  PFCand_mass.clear();
  PFCand_charge.clear();
  PFCand_pdgId.clear();
  PFCand_status.clear();
  PFCand_px.clear();
  PFCand_py.clear();
  PFCand_pz.clear();
  PFCand_hoERatio.clear();
  PFCand_rawEcalEnergy.clear();
  PFCand_rawHcalEnergy.clear();
  
  // Reco Jet Candidate //

  numRecoJets=0;
  RecoJet_e.clear();
  RecoJet_pt.clear();
  RecoJet_eta.clear();
  RecoJet_phi.clear();
  RecoJet_mass.clear();
  RecoJet_pdgId.clear();
  RecoJet_status.clear();
  RecoJet_px.clear();
  RecoJet_py.clear();
  RecoJet_pz.clear();

  // Gen Jet Collection //

  numGenJets=0;
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

  numGenParticles=0;
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

  // Filling Particle Flow Candidates in the TTree (Flat NTuple)

  if(particleFlow.isValid()){
    
    numPFCandidates=particleFlow->size();
    
    for(reco::PFCandidateCollection::const_iterator pf=particleFlow->begin(); pf!=particleFlow->end(); pf++){
      
      float hoERatio = (pf->hoEnergy())/(pf->rawHoEnergy());

      if(pf->pt()>1){
	
	PFCand_e.push_back(pf->energy());
	PFCand_eta.push_back(pf->eta());
	PFCand_phi.push_back(pf->phi());
	PFCand_mass.push_back(pf->mass());
	PFCand_charge.push_back(pf->charge());
	PFCand_pdgId.push_back(pf->pdgId());
	PFCand_status.push_back(pf->status());
	PFCand_pt.push_back(pf->pt());
	PFCand_px.push_back(pf->px());
	PFCand_py.push_back(pf->py());
	PFCand_pz.push_back(pf->pz());

	PFCand_hoERatio.push_back(hoERatio);
	PFCand_rawEcalEnergy.push_back(pf->rawEcalEnergy());
	PFCand_rawHcalEnergy.push_back(pf->rawHcalEnergy());
      }
    }    
  }

  // Filling RecoJet Collection in the TTree (Flat NTuple)

  if(recoJets.isValid()){
    
    numRecoJets=recoJets->size();
    
    for(reco::PFJetCollection::const_iterator rJet=recoJets->begin(); rJet!=recoJets->end(); rJet++){
      
      if(rJet->pt()>0.8){
	
	RecoJet_e.push_back(rJet->energy());
	RecoJet_pt.push_back(rJet->pt());	
	RecoJet_eta.push_back(rJet->eta());
	RecoJet_phi.push_back(rJet->phi());
	RecoJet_mass.push_back(rJet->mass());
	RecoJet_pdgId.push_back(rJet->pdgId());
	RecoJet_status.push_back(rJet->status());
	RecoJet_px.push_back(rJet->px());
	RecoJet_py.push_back(rJet->py());
	RecoJet_pz.push_back(rJet->pz());
      }
    }
  }

  // Filling GenJet Collection in the TTree (Flat NTuple)
  
  if(genJets.isValid()){
    numGenJets=genJets->size();
    
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
    }
  }
  
  //Filling Generator Level Particles in the TTree (Flat NTuple)

  if(genParticles.isValid()){
    
    numGenParticles=genParticles->size();
    
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
    }
  }
  mtree->Fill();
  return;
  
}

DEFINE_FWK_MODULE(MasterAnalyzer);
