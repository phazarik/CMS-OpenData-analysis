//C++
//Class: MasterAnalyzer
//Original Author: Raj Handique
//Created on: 4 January 2023

//include header files//

#include "MinimumBiasAnalyzer.h"

// -------- member functions ---------- //

//--------------------------------------------//
// This Function will collect the necessary   //
// information required from the AOD & AODSIM //
// files and put them in a Flat NTuple or a   //
// TTree - readable in ROOT                   //
//--------------------------------------------//

void 
MinimumBiasAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace std;

  Handle<reco::PFJetCollection> Jets;
  iEvent.getByLabel(InputTag("ak5PFJets"), Jets);


  //--------------------- initialization of the arrays -------------------------//
  
  
  // Reco Jet Candidate //
  
  nJet=0;
  Jet_e.clear();
  Jet_pt.clear();
  Jet_eta.clear();
  Jet_phi.clear();
  Jet_mass.clear();
  Jet_area.clear();
  Jet_chEmEF.clear();
  Jet_chHEF.clear();
  Jet_neEmEF.clear();
  Jet_neHEF.clear();
  Jet_nConstituents.clear();
  

  // Filling RecoJet Collection in the TTree (Flat NTuple)

  if(Jets.isValid()){
    
    for(reco::PFJetCollection::const_iterator rJet=Jets->begin(); rJet!=Jets->end(); rJet++){
      
      if(rJet->pt()>15){

	Jet_e.push_back(rJet->energy());
	Jet_pt.push_back(rJet->pt());	
	Jet_eta.push_back(rJet->eta());
	Jet_phi.push_back(rJet->phi());
	Jet_mass.push_back(rJet->mass());
	Jet_area.push_back(rJet->jetArea());
	Jet_chEmEF.push_back(rJet->chargedEmEnergyFraction());
	Jet_chHEF.push_back(rJet->chargedHadronEnergyFraction());
	Jet_neEmEF.push_back(rJet->neutralEmEnergyFraction());
	Jet_neHEF.push_back(rJet->neutralHadronEnergyFraction());
	Jet_nConstituents.push_back(rJet->nConstituents());
      }

      nJet = Jet_pt.size();
    }
  }
  
  mtree->Fill();
  return;
  
}

DEFINE_FWK_MODULE(MinimumBiasAnalyzer);
