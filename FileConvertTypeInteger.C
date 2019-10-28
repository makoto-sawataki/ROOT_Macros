{
    // This macrro can convert any textfile to rootfile.
    #include <TTree.h>
    #include <TFile.h>
    #include <iostream>

    // Read the textfile
    ifstream fin;
    fin.open("20191008_out.txt");                       // you can change the inside contents 

    // Define variables
    int         event, nHit;
    int         x,y,z;
    double      time_detect;
    double      eDep, eIn;
    int         trackID, copyNo, particleID;

    double      px,py,pz;

    // make TTree
    TTree* tree = new TTree("tree", " mc");

    // make the each variale branch by TTree::Branch Method 
    tree->Branch("event", &event, "event/I");
    tree->Branch("nHit", &nHit, "nHit/I");
    tree->Branch("x", &x, "x/I");
    tree->Branch("y", &y, "y/I");
    tree->Branch("z", &z, "z/I");
    tree->Branch("time", &time_detect, "time_detect/D");
    tree->Branch("eIn", &eIn, "eIn/D");
    tree->Branch("eDep", &eDep, "eDep/D");
    tree->Branch("TrackID", &trackID, "trackID/I");
    tree->Branch("copyNo", &copyNo, "copyNo/I");
    tree->Branch("particle", &particleID, "particleID/I");

    // this is tried and true method when you would like to read text file on c++
    Int_t loop = 0;
    while (fin >> event >> nHit >> px >> py >> pz >> time_detect >> eIn >> eDep >> trackID >> copyNo >> particleID)
    {
        x = int(px);
        y = int(py);
        z = int(pz);

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