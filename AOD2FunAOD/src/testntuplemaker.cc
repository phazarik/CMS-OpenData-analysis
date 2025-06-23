//C++
//Class: TestNTupleMaker
//Original Author: Raj Handique
//Created on: 29 May 2024

//include header files//

#include "testntuplemaker.h"

// -------- member functions ---------- //

//--------------------------------------------//
// This Function will collect the necessary   //
// information required from the AOD & AODSIM //
// files and put them in a Flat NTuple or a   //
// TTree - readable in ROOT                   //
//--------------------------------------------//

void 
testntuplemaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace std;

  Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(InputTag("genParticles"), genParticles);

  Handle<reco::MuonCollection> recoMuons;
  iEvent.getByLabel(InputTag("muons"), recoMuons);

  

  //--------------------- initialization of the arrays -------------------------//
  

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
  
  mtree->Fill();
  return;
  
}

DEFINE_FWK_MODULE(testntuplemaker);
