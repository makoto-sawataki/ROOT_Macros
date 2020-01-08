// analysis.C
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TSystem.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

void analysis() 
{
    // *** For ROOT files ***
    //TFile *f = new TFile("DataFile.root"); // you can add here your root file
    //
    // ------ If you have .root file, you should define tree pointer and then you should cast it from registered tree name. ------
    //TTree *tree;
    //tree = (TTree *)f->Get("tree"); // for example, if your root file has the name "gaus", you should do "f->Get("gaus")".
    //int event;
    //int particle;

    //double x, y, z;
    // ---- set addresses what you want to use. --------
    //tree->SetBranchAddress("event", &event);
    //tree->SetBranchAddress("particle", &particle);
    //tree->SetBranchAddress("x", &x);
    //tree->SetBranchAddress("y", &y);
    //tree->SetBranchAddress("z", &z);
    //
    //int nEntry = tree->GetEntries();

    // make new TTree
    //TFile *file = new TFile("freeConstruct.root", "RECREATE");
    //TTree *freeC = new TTree("freeC", "freeC");
    //
    //Double_t x_out, y_out, z_out;
    //Double_t theta, theta_a, phi;
    //freeC->Branch("x_out", &x_out);
    //freeC->Branch("y_out", &y_out);
    //freeC->Branch("theta", &theta);
    //freeC->Branch("theta_a", &theta_a);
    //freeC->Branch("phi", &phi);
    
    // **** For Not ROOT files *****
    ifstream fin;
    fin.open("DataFile.txt");           // you can change your file name here ""の中をファイル名に書き換えてください。
    
    // Define 2D histogram 
    TH2D*  h2 = new Th2D("myhist", "2D Projection", xbins, xmin, xmax, ybins, ymin,ymax);   // xbins and ybins mean the number of bins. xbinsとybinsはビンの数です。 
    // Check file 
    if (!fin)
    {
        std::cout <<  "Unable to open file";        // here, if the read file doesn't have some data, output this message. もし読み込むファイルがおかしかったら、エラーメッセージを出力するようにしています。
    }
    Double_t x,y,z;         // As you know, you should define the values
    Double_t x_inter, y_inter, z_inter;     // intersection values
    Int_t loop = 0;         // loop counter
    while( fin << x << y << z)
    {
        // code here what you want to calculate
        
        // this is the finding calculation of intersection 
    
        x_out = x1 + (0 - z1) * (x - x1) / (z - z1);        // 
        y_out = y1 + (0 - z1) * (y - y1) / (z - z1);        // 
        z_out = 0;

        // calculate angle from two point
        Double_t dx, dy, dz, leng;
        dx = x - x1;
        dy = y - y1;
        dz = z - z1;
        leng = sqrtl((dx * dx) + (dy * dy) + (dz * dz));

        Double_t pi = 3.141592653589793238462643383279;
        theta = fabs(atan2(dz, dx) * 180 / pi);
        theta_a = fabs(acos(dz / leng) * 180 / pi);
        phi = atan2(dy, dx) * 180 / pi;
        //cout << x_out << " mm"<< "   " << y_out << " mm"<< "   when z =  " << z_out << " mm"<< endl;
        //getchar();
    }

    freeC->Write();
    file->Close();
}
