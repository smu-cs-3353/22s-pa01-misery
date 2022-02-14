//
// Created by mikec_g1kgiu8 on 1/26/2022.
//
#include <iostream>
#include "BruteForceAlgo.h"
#include "MostExpensiveFirstAlgo.h"
#include "CustomAlgo.h"

using namespace std;


int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "Error: Command line argument needed. Enter your command line argument after the executable." << endl;
        cout << "Example (output is the executable name): ./output ../input/PictureInfo.txt" << endl;
    } else {
        BruteForceAlgo firstAlgorithm;
        firstAlgorithm.findOptimalPlacement(argv);

        MostExpensiveFirstAlgo secondAlgorithm;
        secondAlgorithm.findOptimalPlacement(argv);

        CustomAlgo thirdAlgorithm;
        thirdAlgorithm.findOptimalPlacement(argv);
    }

    return 0;
}