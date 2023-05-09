#include <iostream>
#include <cmath>
#include <string.h>
#include<float.h>
#include<complex.h>
#include <vector>
#include<gsl/gsl_complex.h>
#include<gsl/gsl_complex_math.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include <globes/globes.h>
#include<fstream>

#include <algorithm>

extern "C"
{
	#include "bsm.h"
}

using namespace std;

char AEDLFILE[] = "DUNE_GLoBES.glb";


int main(int argc, char * argv[])
{

	glbInit(argv[0]);
	glbInitExperiment(AEDLFILE, &glb_experiment_list[0], &glb_num_of_exps);

	ofstream outBSM;
	outBSM.open("BSMprobability_cmueDUNEn.dat");

	double dm21 = 7.55e-5;
	double dm31 = 2.50e-3;
	double theta12 = asin(sqrt(0.320));
	double theta23 = asin(sqrt(0.547));
	double theta13 = asin(sqrt(0.02160));
	double deltacp = -0.68 * M_PI;

bsm_init_probability_engine_3();

	glbRegisterProbabilityEngine(8 * 9 - 3,
                               &bsm_probability_matrix,
							   &bsm_set_oscillation_parameters,
  							   &bsm_get_oscillation_parameters,
  							   NULL);
	/* Define "true" oscillation parameter vector */
	glb_params true_values = glbAllocParams();
  
	for(unsigned int i=0; i < 69; i++)
	{
	glbSetOscParams(true_values, 0.0, i);
	}

	glbDefineParams(true_values,theta12,theta13,theta23,deltacp,dm21,dm31);

	double abs_a_ee = 0;
	double abs_a_mue = 0;//-2.0e-23 / 1.0e-9;
	double arg_a_mue = 0;
	double abs_a_etau = 0;
	double arg_a_etau = 0;
	double abs_a_mumu = 0;
	double abs_a_mutau = 0;
	double arg_a_mutau = 0;
	double abs_a_tautau = 0;

	double abs_c_ee = 0;
	double abs_c_mue = -2.0e-32 / 1.0e-9;
	double arg_c_mue = 0;
	double abs_c_etau = 0;
	double arg_c_etau = 0;
	double abs_c_mumu = 0;
	double abs_c_mutau = 0;
	double arg_c_mutau = 0;
	double abs_c_tautau = 0;

	//############ LIV Parameter #################################//
	glbSetOscParams(true_values, abs_a_ee, 51);  // a_ee 
	glbSetOscParams(true_values, abs_a_mue, 52);  // a_mue magnitude
    glbSetOscParams(true_values, arg_a_mue, 53);  // a_mue phase
    glbSetOscParams(true_values, abs_a_etau, 54);  // a_etau 
    glbSetOscParams(true_values, arg_a_etau, 55);  // a_etau phase
    glbSetOscParams(true_values, abs_a_mumu, 56);  // a_mumu
    glbSetOscParams(true_values, abs_a_mutau, 57);  // a_mutau
    glbSetOscParams(true_values, arg_a_mutau, 58);  // a_mutau phase
    glbSetOscParams(true_values, abs_a_tautau, 59);  // a_tautau

	glbSetOscParams(true_values, abs_c_ee, 60);  // c_ee 
	glbSetOscParams(true_values, abs_c_mue, 61);  // c_mue magnitude
    glbSetOscParams(true_values, arg_c_mue, 62);  // c_mue phase
    glbSetOscParams(true_values, abs_c_etau, 63);  // c_etau 
    glbSetOscParams(true_values, arg_c_etau, 64);  // c_etau phase
    glbSetOscParams(true_values, abs_c_mumu, 65);  // c_mumu
    glbSetOscParams(true_values, abs_c_mutau, 66);  // c_mutau
    glbSetOscParams(true_values, arg_c_mutau, 67);  // c_mutau phase
    glbSetOscParams(true_values, abs_c_tautau, 68);  // c_tautau

	glbSetDensityParams(true_values,1.0,GLB_ALL);

	glb_params input_errors = glbAllocParams();
  	
	glbSetDensityParams(input_errors, 0.05, GLB_ALL);
	glbSetInputErrors(input_errors);

	glbSetOscillationParameters(true_values);
	glbSetRates();

	double energy, prob_BSM;
	double emin= 0.25 ; //GeV
	double emax=8 ; //GeV
	double step= 1000;
	//double L = 1300; // km
  
	for (energy=emin;energy<=emax;energy+=(emax-emin)/step)
	{
	glbSetOscillationParameters(true_values);
	//prob_BSM=glbVacuumProbability(2,1,+1,energy,L);
	prob_BSM=glbProfileProbability(0,2,1,+1,energy);
	outBSM<<energy<<"  "<<prob_BSM<<endl;
	}

	outBSM.close();

	glbFreeParams(true_values);
 	return 0;

}

//int p = find(bsm_param_strings[801].begin(),bsm_param_strings[801].end(),"ABS_A_V_MUE");
	//cout << p << endl;

//for (int p=0;p<69;p++){
	//	cout << p << " " <<  bsm_param_strings[p] << endl;
	//}
