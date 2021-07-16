#include <stdio.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <iostream>
#include <math.h>
using namespace std;

 void Massa_Invariante() {
//Acessando a tree com os eventos 
   TFile *f = new TFile("output4.root");
   TTree *tree = (TTree*)f->Get("aod2nanoaod/Events");

// Declarando os Vetores do TLorentzVector-------------------------------------------
   TLorentzVector A; 
   TLorentzVector B; 
   TLorentzVector C;

   TLorentzVector D; 
   TLorentzVector E; 
   TLorentzVector F;

// Declarando as variaveis-----------------------------------------------------------
   //RECO___________________________________
   UInt_t           nMuon;
   Float_t         Muon_pt[9];
   Float_t         Muon_eta[9];
   Float_t         Muon_phi[9];
   Float_t         Muon_mass[9];
   Int_t           Muon_charge[9];
   UInt_t           Muon_genPartIdx[9];

   //GEN____________________________________
   UInt_t           nGenPart;
   Float_t         GenPart_pt[9];
   Float_t         GenPart_eta[9];
   Float_t         GenPart_phi[9];
   Float_t         GenPart_mass[9];
   UInt_t           GenPart_status[9];
   UInt_t           GenPart_pdgld[9];

  

// Lista de branches----------------------------------------------------------------------------
  //RECO___________________________________
   TBranch        *b_nMuon;   //!
   TBranch        *b_Muon_pt;   //!
   TBranch        *b_Muon_eta;   //!
   TBranch        *b_Muon_phi;   //!
   TBranch        *b_Muon_mass;   //!
   TBranch        *b_Muon_charge;   //!
   TBranch        *b_Muon_genPartIdx;

   //GEN____________________________________
   TBranch        *b_nGenPart;   //!
   TBranch        *b_GenPart_pt;   //!
   TBranch        *b_GenPart_eta;   //!
   TBranch        *b_GenPart_phi;   //!
   TBranch        *b_GenPart_mass;   //!
   TBranch        *b_GenPart_status;   //!
   TBranch        *b_GenPart_pdgld;   //!
   
  // Lista de trees-----------------------------------------------------------------------------------------
   //RECO_______________________________________________________________
   tree->SetBranchAddress("nMuon", &nMuon);
   tree->SetBranchAddress("Muon_pt", &Muon_pt);
   tree->SetBranchAddress("Muon_eta", &Muon_eta);
   tree->SetBranchAddress("Muon_phi", &Muon_phi);
   tree->SetBranchAddress("Muon_mass", &Muon_mass);
   tree->SetBranchAddress("Muon_charge", &Muon_charge);
   tree->SetBranchAddress("Muon_genPartIdx", &Muon_genPartIdx);

   //GEN_________________________________________________________________
   tree->SetBranchAddress("nGenPart", &nGenPart);
   tree->SetBranchAddress("GenPart_pt", &GenPart_pt);
   tree->SetBranchAddress("GenPart_eta", &GenPart_eta);
   tree->SetBranchAddress("GenPart_phi", &GenPart_phi);
   tree->SetBranchAddress("GenPart_mass", &GenPart_mass);
   tree->SetBranchAddress("GenPart_status", &GenPart_status);
   tree->SetBranchAddress("GenPart_pdgId", &GenPart_pdgld);
   
   // Declarando Histogramas------------------------------------------------------------------------------
   TH1F *h1 = new TH1F("h1", "Massa de 2 Muons(RECO)", 200, 0, 200);
   h1->GetXaxis()->SetTitle("Massa (GeV)");
   h1->GetYaxis()->SetTitle("Eventos");

   TH1F *h2 = new TH1F("h2", "Massa de 2 Muons(Gen)", 200, 0, 200);
   h2->GetXaxis()->SetTitle("Massa (GeV)");
   h2->GetYaxis()->SetTitle("Eventos");
   
   // Inicio do Loop em todos os eventos--------------------------------------------------------------------
   Int_t nentries= (Int_t)tree->GetEntries();
   for (Int_t i = 0; i<nentries; i++) {
     tree->GetEntry(i);
     //RECO_____________________________________________________________________________________
     if(nMuon == 2 && Muon_charge[0] != Muon_charge[1] && Muon_pt[1] > 3.5 && Muon_pt[0] > 3.5 && abs(Muon_eta[1]) < 2.1  && abs(Muon_eta[0]) < 2.1){ //Criterios de seleção para a reconstrução de 2 muons RECO
       A.SetPtEtaPhiM(Muon_pt[0], Muon_eta[0], Muon_phi[0], Muon_mass[0]);
       B.SetPtEtaPhiM(Muon_pt[1], Muon_eta[1], Muon_phi[1], Muon_mass[1]);
       h1->Fill((A + B).M());
      }
    
     //GEN_______________________________________________________________________________________
     if(nGenPart == 2 && GenPart_pdgld[0] != GenPart_pdgld[1] && GenPart_pt[0] > 3.5 && abs(GenPart_eta[0]) < 2.1  && GenPart_pt[1] > 3.5 && abs(GenPart_eta[1]) < 2.1){ //Criterios de seleção para a reconstrução de 2 muons GEN
       D.SetPtEtaPhiM(GenPart_pt[0], GenPart_eta[0], GenPart_phi[0], GenPart_mass[0]);
       E.SetPtEtaPhiM(GenPart_pt[1], GenPart_eta[1], GenPart_phi[1], GenPart_mass[1]);
       F= D + E;
       h2->Fill((D + E).M());
      } 
    }

   // Canvas para Mostrar os Histogramas
   TCanvas *t1 = new TCanvas("t1", "t1", 800, 600);
   t1->Divide(1,1);
   t1->cd(1);
   h1->Draw();

   TCanvas *t2 = new TCanvas("t2", "t2", 800, 600);
   t2->Divide(1,1);
   t2->cd(1);
   h2->Draw();
  }