

#include <TH1.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

void ana::Loop()
{

  if (fChain == 0) return;
   
  // Declare histograms
  TH1F* el1_eta = new TH1F("el1_eta", "Pseudorapidity of the most energetic electron candidate"
			   , 100, -4, 4);
  TH1F* el2_eta = new TH1F("el2_eta", "Pseudorapidity of the second most energetic electron candidate"
			   , 100, -4, 4);
    
  TH1F* el1_pt = new TH1F("el1_pt", "pT of the most energetic electron candidate", 100, 0, 200);
  TH1F* el2_pt = new TH1F("el2_pt", "pT of the second most energetic electron candidate", 100, 0, 200);

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
   
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 
    // note that if we wanted to look at only a subset of a very large data set
    // we could change change nentries to a fixed number in the line above
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
     
    // Fill histograms (note that the electrons are already ordered in pT)
    el1_eta->Fill(f_lept1_eta);
    el2_eta->Fill(f_lept2_eta);
    el1_pt->Fill(f_lept1_pt);
    el2_pt->Fill(f_lept2_pt);

      
  } //end event loop
}  //end ana::Loop()
