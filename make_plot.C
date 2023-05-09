#include "TH1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

void make_plot(){

    auto gr  = new TGraph("probability_DUNE.dat");
    auto grBSM  = new TGraph("BSMprobability_cmueDUNE.dat");
    auto grBSMn  = new TGraph("BSMprobability_cmueDUNEn.dat");

    gr->GetXaxis()->SetRangeUser(0.25,8.0);
    gr->GetYaxis()->SetRangeUser(0,1);
    gr->SetTitle("Probability of appearance #nu_{#mu} to #nu_{e};E (GeV);P_{#mu e}");
    gr->GetXaxis()->CenterTitle();
    gr->GetYaxis()->CenterTitle();
    gr->GetYaxis()->SetNdivisions(505);

    grBSMn->SetLineStyle(2);

    grBSM->SetLineColor(kRed);
    grBSMn->SetLineColor(kRed);

    gr->Draw();
    grBSM->Draw("SAME");
    grBSMn->Draw("SAME");
}
