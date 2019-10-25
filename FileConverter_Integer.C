{
    #include <TTree.h>
    #include <TFile.h>
    
    #include <iostream>
    #include <bits/stdc++.h>

    ifstream fin;
    fin.open("out.txt");

    Int_t event, nHit;
    int x, y, z;
    double time_detect;
    Double_t eIn,eDep;
    Int_t trackID, copyNO, particleID;

    Double_t px,py,pz;

    // make TTree
    TTree* tree = new TTree("tree", "mc output"); 

    // make new File 
    TFile* nfn = new TFile("Integer_out.root","Recreate");

    // register the each variable as Branch by TTree::Branch Method
    tree->Branch("event", &event, "event/I");
    tree->Branch("nHit", &nHit, "nHit/I");
    tree->Branch("x", &x, "x/I");
    tree->Branch("y", &y, "y/I");
    tree->Branch("z", &z, "z/I");
    tree->Branch("time", &time_detect, "time_detect/D");
    tree->Branch("eIn", &eIn, "eIn/D");
    tree->Branch("eDep", &eDep, "eDep/D");
    tree->Branch("trackID", &trackID, "trackID");
    tree->Branch("copyNo", &copyNO, "copyNO/I");
    tree->Branch("particleID", &particleID, "particleID/I");

    // This is tried and true method about I/O
    Int_t loop =0;
    while(fin >> event >> nHit >> px >> py >> pz >> time_detect >> eIn >> eDep >> trackID >> copyNO >> particleID)
    {   
        x = int(px); 
        y = int(py);
        z = int(pz);
        
        tree->Fill();
        loop++;
    }
    tree->Write();
    nfn->Close();

} 
