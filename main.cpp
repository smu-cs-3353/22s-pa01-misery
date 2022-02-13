//
// Created by mikec_g1kgiu8 on 1/26/2022.
//
#include <cmath> //FIXME is this used?
#include <vector>
#include <iostream>
#include <fstream>
#include "BruteForceAlgo.h"
#include "MostExpensiveFirstAlgo.h"

using namespace std;


int main(int argc, char** argv) {
    BruteForceAlgo firstAlgorithm;
    firstAlgorithm.findOptimalPlacement(argv);

    MostExpensiveFirstAlgo secondAlgorithm;
    secondAlgorithm.findOptimalPlacement(argv);
}

//FIXME BruteForce should probably be able to run a dataset of around 25 in 5 minutes (or so)