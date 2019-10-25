{
    #include <TTree.h>
    #include <TFile.h>
    
    #include <iostream>
    #include <bits/stdc++.h>

    //ifstream fin;
    //fin.open("out.root");

    TFile* fin = new TFile("out.root");
    TTree* tree = (TTree*)fin->Get("tree");

    Int_t event, nHit;
    double x,y,z;
    double Rtime;
    double eIn, eDep;
    Int_t trackID, copyNo, particle;

    tree->SetBranchAddress("event", &event);
    tree->SetBranchAddress("nHit", &nHit);
    tree->SetBranchAddress("x", &x);
    tree->SetBranchAddress("y", &y);
    tree->SetBranchAddress("z", &z);
    tree->SetBranchAddress("time", &Rtime);
    tree->SetBranchAddress("eIn", &eIn);
    tree->SetBranchAddress("eDep", &eDep);
    tree->SetBranchAddress("TrackID", &trackID);
    tree->SetBranchAddress("copyNo", &copyNo);
    tree->SetBranchAddress("particle", &particle);

    Int_t tEvent, tnHit;
    int tx, ty, tz;
    double time_detect;
    Double_t teIn, teDep;
    Int_t ttrackID, tcopyNO, tparticleID;

    
    // make new File 
    TFile* nfn = new TFile("Integer_out_test.root","RECREATE");
    // make TTree
    TTree* t = new TTree("t","output");
    // register the each variable as Branch by TTree::Branch Method
    t->Branch("event", &tEvent, "tEvent/I");
    t->Branch("nHit", &tnHit, "tnHit/I");
    t->Branch("x", &tx, "tx/I");
    t->Branch("y", &ty, "ty/I");
    t->Branch("z", &tz, "tz/I");
    t->Branch("time", &time_detect, "time_detect/D");
    t->Branch("eIn", &teIn, "eIn/D");
    t->Branch("eDep", &teDep, "eDep/D");
    t->Branch("trackID", &ttrackID, "trackID");
    t->Branch("copyNo", &tcopyNO, "copyNO/I");
    t->Branch("particleID", &tparticleID, "particleID/I");

    // This is tried and true method about registering TTree
    Int_t n = tree->GetEntries();
    for (int i = 0; i < n; ++i)
    {
        tree->GetEntry(i);
        
        //tEvent = event;
        //tnHit = tnHit;
        tx = int(x); 
        ty = int(y);
        tz = int(z);
        //time_detect = Rtime;
        //teIn = eIn;
        //teDep = eDep;
        //ttrackID = trackID;
        //tcopyNO = copyNo;
        //tparticleID = particle;
        
        t->Fill();
        
    }

    // ROOT can save automatically 
    // if the outputfile size larger than a certain size
    // So, you can comment out following code
    t->Write();

    // 
    nfn->Close();

} 
