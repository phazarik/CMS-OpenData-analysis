/* ===========================================
   
  This is a graphing script to make histograms
  look presentable and ready for journal uses.
  Created on: 10 Jul, 2024
  Original Author: Raj Handique

  Steps to the execute/run the code:

  1. In the ROOT prompt,
  root [0] .x graphing.C -> will produce the desired plot
  =========================================== */

// user include header files 

#include <iostream>
#include <string>
#include <fstream>
#include <TFile.h>
#include <TH1.h>
#include <TH1F.h>
#include <TPaveText.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraph.h>

// Declaring all the functions necessary. The descriptions can be found commented
// along with them.

void decorate(TH1 *h, int linecolor, double linewidth){

  // This functions decorates the histogram with color and linewidth

  h->SetLineColor(linecolor);
  h->SetLineWidth(linewidth);
}


void graphing(){

  // The name of the input files (.root files)
  TString filename = "test_hist.root";
  
  // The name of the plot(s) to be accessed from the histogram file
  TString plotname = "Dimuon_inv_mass";

  // Opening the files using TFile
  TFile *file1 = new TFile(filename);

  // Opening and Assigning the histograms from the input file(s)
  TH1F *h1 = (TH1F*)file1->Get(plotname);

  // Decorating the histogram
  decorate(h1, kRed+0, 2.5);
  h1->SetStats(0);
  // Declaring a canvas
  TCanvas *c1 = new TCanvas("c1","CMS Open Data", 900, 600);

  h1->Draw("hist");
  
  // Writing the necessary information on the histogram
  TLatex t1, t2, t3;
  t1.SetTextSize(0.05);
  t2.SetTextSize(0.04);
  t3.SetTextSize(0.04);
  t1.DrawLatexNDC(0.66, 0.84, "CMS Open Data");
  t2.DrawLatexNDC(0.66, 0.79, "#it{#bf{Simulation}}");
  t3.DrawLatexNDC(0.2, 0.92, "DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola");

  c1->Update();

}

