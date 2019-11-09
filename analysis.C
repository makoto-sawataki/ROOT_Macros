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

using namespace std;

void analysis() 
{
    TFile *f = new TFile("FreeSky_0901_790k_event.root");

    TTree *tree;

    tree = (TTree *)f->Get("tree");

    int event;
    int particle;

    double x, y, z;
    tree->SetBranchAddress("event", &event);
    tree->SetBranchAddress("particle", &particle);
    tree->SetBranchAddress("x", &x);
    tree->SetBranchAddress("y", &y);
    tree->SetBranchAddress("z", &z);

    int nEntry = tree->GetEntries();

    // make new TTree
    TFile *file = new TFile("freeConstruct.root", "RECREATE");
    TTree *freeC = new TTree("freeC", "freeC");

    Double_t x_out, y_out, z_out;
    Double_t theta, theta_a, phi;
    freeC->Branch("x_out", &x_out);
    freeC->Branch("y_out", &y_out);
    freeC->Branch("theta", &theta);
    freeC->Branch("theta_a", &theta_a);
    freeC->Branch("phi", &phi);

    for (Int_t iEntry = 0; iEntry < nEntry; ++iEntry)
    {
        tree->GetEntry(iEntry);
        double x1, y1, z1;
        int particle_i;

        if (particle == 13)
        {

            int pEvent;
            //pEvent = tree->SetBranchAddress("event", &event);

            //preserve particle, event, x,y,z when they are iEntry
            particle_i = particle;
            pEvent = event;
            x1 = x;
            y1 = y;
            z1 = z;
            tree->GetEntry(iEntry + 1);

            // judgement i "event" and i+1 "event"
            if (pEvent == event && particle == particle_i)
            {
                //cout << event << "   " << x << "     " << y << "      " << z << "    " << particle <<endl;
                //cout << pEvent << "   " << x1 << "     " << y1 << "      " << z1 << "    " << particle <<endl;
                //getchar();

                x_out = x1 + (0 - z1) * (x - x1) / (z - z1); // when you calculate for projection, you see the -X direction.
                y_out = y1 + (0 - z1) * (y - y1) / (z - z1); // So, you will see y (regarded as x direction) and z (regarded as y direction).
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

                freeC->Fill();

                //freeC->Write();
            }
        }
    }
/*
    TFile *fin = new TFile("Fe_30cm_800M_event.root","read");

    TTree *t;

    t = (TTree *)fin->Get("tree");

    int event_p;
    int particle_p;

    double x_p, y_p, z_p;
    t->SetBranchAddress("event", &event_p);
    t->SetBranchAddress("particle", &particle_p);
    t->SetBranchAddress("x", &x_p);
    t->SetBranchAddress("y", &y_p);
    t->SetBranchAddress("z", &z_p);

    Double_t x_Fe, y_Fe, z_Fe;
    Double_t theta_Fe, theta_a_Fe, phi_Fe;
    freeC->Branch("x_Fe", &x_Fe);
    freeC->Branch("y_Fe", &y_Fe);
    freeC->Branch("theta", &theta_Fe);
    freeC->Branch("theta_a", &theta_a_Fe);
    freeC->Branch("phi", &phi_Fe);

    int n = t->GetEntries();

    for (Int_t i = 0; i < n; ++i)
    {
        t->GetEntry(i);
        double x1, y1, z1;
        int particle_i;

        if (particle_p == 13)
        {

            int pEvent;
            //pEvent = tree->SetBranchAddress("event", &event);

            //preserve particle, event, x,y,z when they are iEntry
            particle_i = particle_p;
            pEvent = event_p;
            x1 = x_p;
            y1 = y_p;
            z1 = z_p;
            t->GetEntry(i + 1);

            // judgement i "event" and i+1 "event"
            if (pEvent == event_p && particle_p == particle_i)
            {
                //cout << event << "   " << x << "     " << y << "      " << z << "    " << particle <<endl;
                //cout << pEvent << "   " << x1 << "     " << y1 << "      " << z1 << "    " << particle <<endl;
                //getchar();

                x_Fe = x1 + (0 - z1) * (x_p - x1) / (z_p - z1); // when you calculate for projection, you see the -X direction.
                y_Fe = y1 + (0 - z1) * (y_p - y1) / (z_p - z1); // So, you will see y (regarded as x direction) and z (regarded as y direction).
                z_Fe = 0;

                // calculate angle from two point
                Double_t dx, dy, dz, leng;
                dx = x_p - x1;
                dy = y_p - y1;
                dz = z_p - z1;
                leng = sqrtl((dx * dx) + (dy * dy) + (dz * dz));

                Double_t pi = 3.141592653589793238462643383279;
                theta = fabs(atan2(dz, dx) * 180 / pi);
                theta_a = fabs(acos(dz / leng) * 180 / pi);
                phi = atan2(dy, dx) * 180 / pi;
                //cout << x_out << " mm"<< "   " << y_out << " mm"<< "   when z =  " << z_out << " mm"<< endl;
                //getchar();

                freeC->Fill();

            }
        }
    }
*/
    freeC->Write();
    file->Close();
}
