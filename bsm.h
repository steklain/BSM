#ifndef __BSM_H
#define __BSM_H

#include <globes/globes.h>

// Arrangement of oscillation parameters in glb_params data structure:
//   th12,    th13,    th23,    deltaCP,
//   dm21,    dm31,    dm41,    dm51,    ...,
//   th14,    th24,    th34,    th15,    th25,    ...,
//   delta_1, delta_2, ...
//
//   |\eps|^s_{ee},   \phi^s_{ee},   ..., |\eps^s_{sn,e}|,  \phi^s_{sn,e},
//                ...                ...                 ...
//   |\eps|^s_{e,sn}, \phi^s_{e,sn}, ..., |\eps^s_{sn,sn}|, \phi^s_{sn,sn},
//
//   \eps^m_{ee},     |\eps^m_{e\mu}|, \phi^m_{e\mu},  ...,  |\eps^m_{e,sn}|,   \phi^m_{e,sn}
//                    \eps^m_{\mu\mu},                 ...,  |\eps^m_{\mu,sn}|, \phi^m_{\mu,sn}
//                                                     ...         ...
//                                                           \eps^m_{sn,sn}
//
//   |\eps|^d_{ee},   \phi^d_{ee},   ..., |\eps^d_{sn,e}|,  \phi^d_{sn,e},
//                ...                ...                 ...
//   |\eps|^d_{e,sn}, \phi^d_{e,sn}, ..., |\eps^d_{sn,sn}|, \phi^d_{sn,sn}
//
//   \a_{ee},     |\a_{e\mu}|, \phi^a_{e\mu},  ...,  |\a_{e,sn}|,   \phi^a_{e,sn}
//                    \a_{\mu\mu},                 ...,  |\a_{\mu,sn}|, \phi^a_{\mu,sn}
//                                                     ...         ...
//                                                           \a_{sn,sn}
//
//   \c_{ee},     |\c_{e\mu}|, \phi^c_{e\mu},  ...,  |\c_{e,sn}|,   \phi^c_{e,sn}
//                    \c_{\mu\mu},                 ...,  |\c_{\mu,sn}|, \phi^c_{\mu,sn}
//                                                     ...         ...
//                                                           \c_{sn,sn}

// Names of oscillation parameters
extern char bsm_param_strings[][64];

#define MAX_FLAVORS      9

// Function declarations
// ---------------------

// bsm.c
int bsm_init_probability_engine_3();
int bsm_init_probability_engine(int _n_flavors, int _rotation_order[][2], int _phase_order[]);
int bsm_free_probability_engine();
int bsm_set_oscillation_parameters(glb_params p, void *user_data);
int bsm_get_oscillation_parameters(glb_params p, void *user_data);
int bsm_filtered_probability_matrix_cd(double P[MAX_FLAVORS][MAX_FLAVORS],
        double E, double L, double V, double sigma, int cp_sign);
int bsm_probability_matrix(double _P[3][3], int cp_sign, double E,
        int psteps, const double *length, const double *density,
        double filter_sigma, void *user_data);
int bsm_probability_matrix_all(double P[MAX_FLAVORS][MAX_FLAVORS], int cp_sign, double E,
    int psteps, const double *length, const double *density,
    double filter_sigma, void *user_data);
int bsm_probability_matrix_m_to_f(double P[MAX_FLAVORS][MAX_FLAVORS], int cp_sign, double E,
    int psteps, const double *length, const double *density,
    double filter_sigma, void *user_data);
int bsm_print_gsl_matrix_complex(gsl_matrix_complex *A);

// prem.c
int LoadPREMProfile(const char *prem_file);
double GetPREMDensity(double t, double L);
double GetAvgPREMDensity(double L_tot, double L1, double L2);
int GetPREM3LayerApprox(double L, int *n_layers, double *lengths,
                        double *densities);

#endif

