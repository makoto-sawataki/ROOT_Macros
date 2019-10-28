{
    // This macrro can convert any textfile to rootfile.
    #include <TTree.h>
    #include <TFile.h>
    #include <iostream>

    // Read the textfile
    ifstream fin;
    fin.open("20191008_out.txt");                       // you can change the inside contents 

    // Define variables
    Int_t       event, nHit;
    Double_t    x,y,z,
    Dobole_t    time_detect;
    Double_t    eDep, eIn;
    Int_t       trackID, copyNo, particleID;

    // make TTree
    TTree* tree = new TTree("tree", " mc");

    // make the each variale branch by TTree::Branch Method 
    tree->Branch("event", &event, "event/I");
    tree->Branch("nHit", &nHit, "nHit/I");
    tree->Branch("x", &x, "x/D");
    tree->Branch("y", &y, "y/D");
    tree->Branch("z", &z, "z/D");
    tree->Branch("time", &time_detect, "time_detect/D");
    tree->Branch("eIn", &eIn, "eIn/D");
    tree->Branch("eDep", &eDep, "eDep/D");
    tree->Branch("TrackID", &trackID, "trackID/I");
    tree->Branch("copyNo", &copyNo, "copyNo/I");
    tree->Branch("particle", &particleID, "particleID/I");

    // this is tried and true method when you would like to read text file on c++
    Int_t loop = 0;
    while (fin >> event >> nHit >> x >> y >> z >> time_detect >> eIn >> eDep >> trackID >> copyNo >> particleID)
    {
        // fill data
        tree->Fill();
        loop++;
    }
    

    // make TFile to save TTree
    TFile* fout = new TFile( "out.root", "RECREATE");

    tree->Write();

    fout->Close();

    return ;
}