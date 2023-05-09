#!/bin/bash
gcc -Wall -c bsm.c -std=c99
g++ -Wall -c Prob.cc
g++ -Wall Prob.o bsm.o -lglobes -lgsl -lgslcblas -O3 -o Probability
./Probability 
rm *.o