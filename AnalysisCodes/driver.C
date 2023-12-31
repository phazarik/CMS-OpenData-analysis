#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
void driver(int sample=0)
{
  const char *hstfilename, *sumfilename; 
  TChain *chain = new TChain("Events/Events");
  AnaOpenData m_selec;//declared an instance of our class.
  
  //--------------------------------------------------------------------------//
  //               Choose the sample you want to run over                     //
  //--------------------------------------------------------------------------//

  if(sample==0){//EGamma data
    chain->Add("InputFiles/*.root");
    hstfilename = "OutputHists/hst_sample.root";
    sumfilename = "OutPutHists/sum_sample.txt";
    m_selec.SetData(1);
    m_selec.SetYear(2018);
  }

  std::cout<<"Output : "<<hstfilename<<std::endl;
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSumFileName(sumfilename);
  m_selec.SetVerbose(0);//set verbosity level for output.
  
  //this calls the Process function for each event in the chain
  //and runs the m_selec code over it.
  chain->Process(&m_selec);
    
}
