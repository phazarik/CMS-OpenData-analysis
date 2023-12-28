#define AnaOpenData_cxx
// The class definition in AnaOpenData.h has been generated automatically
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
// root> T->Process("AnaOpenData.C")
// root> T->Process("AnaOpenData.C","some options")
// root> T->Process("AnaOpenData.C+")
//


#include "AnaOpenData.h"
#include <TH2.h>
#include <TStyle.h>
//Additional headers:
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

void AnaOpenData::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
}

void AnaOpenData::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  //Initialization of some global variables:
  time(&start);
  nEvtTotal = 0;
  //nEvtRan = 0;
  //nEvtTrigger=0;

  //Creating the output file:
  _HstFile = new TFile(_HstFileName,"recreate");
  BookHistograms();

  TString option = GetOption();

}

void AnaOpenData::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

  //Writing the saving the output file:
  _HstFile->Write();
  _HstFile->Close();

  //Printing out some information using the event counters after the event loop has run.
  cout<<"---------------------------------------------"<<endl;
  cout<<"Summary:"                    <<endl;
  cout<<"nEvtTotal = "  <<nEvtTotal   <<endl;
  //cout<<"nEvtRan = "    <<nEvtRan     <<endl;
  //cout<<"nEvtTrigger = "<<nEvtTrigger <<endl;
  cout<<"---------------------------------------------"<<endl;

  //You can also create a text file here as a summary, keeping the same information.
  //For example, the text file can take the name _SumFileName

}

void AnaOpenData::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

}

//--------------------------------------------------------------------------------------
//                                  The event loop:
//--------------------------------------------------------------------------------------

Bool_t AnaOpenData::Process(Long64_t entry)
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
  if(_verbosity==0 && nEvtTotal%100==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;      
  else if(_verbosity>0 && nEvtTotal%100==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;

  nEvtTotal++;

  //THE FOLLOWING TAKES PLACE FOR ONE EVENT AT A TIME
  
  //--------------------------------------------
  // Extracting information from the input file
  //--------------------------------------------
  
  //Creating an array of electrons per/event.
  //First, clear the arrays from the previous event (if any).
  int nele = 0;
  PFall.clear();
  PFelectron.clear();

  //Loopong over all the candidates to pick the ibjects we want:
  for(int i=0; i< (*numPFCandidates); i++){

    //Creating a temporaray object and setting its parameters from the input file.
    //If the parameters satisfy our needs, we will keep it in the PFelectron array.
    Particle temp;
    temp.index = i;
    temp.pdgid  = PFCand_pdgId[i];
    temp.charge = PFCand_charge[i];
    temp.status = PFCand_status[i];
    temp.v.SetPtEtaPhiM(PFCand_pt[i], PFCand_eta[i], PFCand_phi[i], PFCand_mass[i]);

    //For all PF objects:
    PFall.push_back(temp);
    
    //For PFelectrons:
    bool itis_stable   = temp.status == 1;
    bool kinematic_cuts = temp.v.Pt()>10 && fabs(temp.v.Eta()) < 2.4;
    bool itis_electron = fabs(temp.pdgid) == 11;

    if(itis_electron && itis_stable && kinematic_cuts){
      PFelectron.push_back(temp);
      nele ++;
    }

  }

  //Sorting the particle arrays in descenting order of pT:
  for(int i=0; i<(int)PFall.size()-1; i++){
    for(int j=i+1; j<(int)PFall.size(); j++){
      if(PFall[i].v.Pt() < PFall[j].v.Pt() ) swap(PFall.at(i), PFall.at(j));}}
  
  for(int i=0; i<(int)PFelectron.size()-1; i++){
    for(int j=i+1; j<(int)PFelectron.size(); j++){
      if(PFelectron[i].v.Pt() < PFelectron[j].v.Pt() ) swap(PFelectron.at(i), PFelectron.at(j));}}  


  //-------------------
  //  Analysis block
  //-------------------

  //Note : All the histograms that are being filled here need to be
  //initialized in the BookHistograms() function.
  //Otherwise the code will show runtime error.

  h.hist[0]->Fill((int)PFall.size());

  for(int i=0; i<(int)PFall.size(); i++){
    h.hist[1]->Fill(PFall.at(i).v.Pt());
  }
  
  if((int)PFall.size()>0){//For events containing at least one PF object
    h.hist[2]->Fill(PFall.at(0).v.Pt());
  }
  
  h.hist[3]->Fill((int)PFelectron.size());

  
  return kTRUE;
}

//-------------------------
// USER DEFINED FUNCTIONS
//-------------------------
void AnaOpenData::BookHistograms(){

  //Choose an appropriate binning scheme here.
  h.hist[0] = new TH1F("nPFall", "nPFall", 2000, 0, 2000);    
  h.hist[1] = new TH1F("PFall_pt", "ALl PF pT", 500, 0, 100);  //500 bins from x=0 to x=100
  h.hist[2] = new TH1F("PF0_pt", "Leading PF pT", 500, 0, 100);
  h.hist[3] = new TH1F("nPFele", "nPFele", 10, 0, 0);

}
