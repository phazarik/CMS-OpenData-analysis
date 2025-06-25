#define cmsAna_cxx
// The class definition in cmsAna.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("cmsAna.C")
// root> T->Process("cmsAna.C","some options")
// root> T->Process("cmsAna.C+")
//


#include "cmsAna.h"
#include <TH2.h>
#include <TStyle.h>

void cmsAna::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
}

void cmsAna::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  //Initialization of some global variables:
  time(&start);
  nEvtTotal = 0;

  //Creating the output file:
  _HstFile = new TFile(_HstFileName,"recreate");
  BookHistograms();
    
  TString option = GetOption();

}

Bool_t cmsAna::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetLocalEntry(entry);


  //Setting verbosity:
  //Verbosity determines the number of processed events after which
  //the root prompt is supposed to display a status update.
  if(_verbosity==0 && nEvtTotal%1000==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;      
  else if(_verbosity>0 && nEvtTotal%1000==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;

  nEvtTotal++;
  
  //---------------------------------------------------------------------------------------//
  //                                                                                       // 
  //                               Initialization of Arrays                                //
  //                                                                                       //
  //---------------------------------------------------------------------------------------//  


  int num_muons=0;
  
  // Muons Array //

  Muons.clear();

  for(int i=0; i<(*nMuon); i++){
    
    Particle temp;
    temp.v.SetPtEtaPhiM(Muon_pt[i], Muon_eta[i], Muon_phi[i], 0.105);
    temp.index = i;
    temp.id = Muon_pdgId[i];
    temp.px = Muon_px[i];
    temp.py = Muon_py[i];
    temp.pz = Muon_pz[i];
    temp.e = Muon_e[i];
    temp.charge = Muon_charge[i];

    // muons having pT over 30 GeV
    
    bool passCuts = temp.v.Pt()>30 && fabs(temp.v.Eta())<2.4;
    passCuts = passCuts && fabs(temp.id)==13;
    
    if(passCuts) {Muons.push_back(temp);
      num_muons++;
    }
    
  }

  Sortpt(Muons);

     
  //---------------------------------------------------------------------------------------//
  //                                                                                       // 
  //                               Analysis Block Starts Here                              //
  //                                                                                       //
  //---------------------------------------------------------------------------------------//
  

  
  for(int i=0; i<(int)Muons.size(); i++){
    h.hist[1]->Fill(Muons.at(i).v.Pt());
    h.hist[2]->Fill(Muons.at(i).v.Eta());
    h.hist[3]->Fill(Muons.at(i).v.Phi());
    h.hist[4]->Fill(Muons.at(i).v.M());
    
  }

  // Plotting Di Muon pT
  
  if((int)Muons.size()>1){      
    float inv_mass_muon = (Muons.at(0).v + Muons.at(1).v).M();
    h.hist[5] -> Fill(inv_mass_muon);
  }
   
  
  return kTRUE;
}

void cmsAna::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

  //Writing the saving the output file:
  _HstFile->Write();
  _HstFile->Close();
  
  //Printing out some information using the event counters after the event loop has run.
  cout<<"----------------------------------------------------------"<<endl;
  cout<<"Summary:"                    <<endl;
  cout<<"nEvtTotal = "  <<nEvtTotal   <<endl;
  cout<<"----------------------------------------------------------"<<endl;

  time(&end);

  double time_taken = double(end-start);
  cout<<"\nTime taken by the program is : "<<(int)time_taken<<" seconds \n"<<endl;
  

}

void cmsAna::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

}


//User Defined Function//

void cmsAna::BookHistograms(){

 h.hist[1] = new TH1F("Muon_pT", "Transverse Momentum of Muon", 100, 0, 100);  
 h.hist[2] = new TH1F("Muon_eta", "Pseudorapidity of Muon", 100, -3, 3);   
 h.hist[3] = new TH1F("Muon_phi", "Polar Angle of Muon", 100, -4, 4);
 h.hist[4] = new TH1F("Muon_mass", "Mass of Muons", 100, -1, 1);
 h.hist[5] = new TH1F("Dimuon_inv_mass", "; #mu#mu mass (GeV/c^{2}); Events/GeV", 100, 0, 200);
}



void cmsAna::Sortpt(vector<Particle> vec)
{
  //This functions sorts an array in the decreasing order of pT.
  for(int i=0; i<(int)vec.size()-1; i++){
    for(int j=i+1; j<(int)vec.size(); j++){
      if(vec.at(i).v.Pt() < vec.at(j).v.Pt()) swap(vec.at(i), vec.at(j));
    }
  }
}
