//
// Created by mikec_g1kgiu8 on 1/26/2022.
//
#include <cmath> //FIXME is this used?
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include "BruteForceAlgo.h"
#include "MostExpensiveFirstAlgo.h"
#include "CustomAlgo.h"

using namespace std;


int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "Error: Command line argument needed. Enter your command line argument after the executable." << endl;
        cout << "Example (output is the executable name): ./output ../input/PictureInfo.txt" << endl;
    } else {
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

        start = std::chrono::high_resolution_clock::now();
        BruteForceAlgo firstAlgorithm;
        firstAlgorithm.findOptimalPlacement(argv);
        end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> time_in_seconds = end - start;
        cout << fixed << "BruteForceAlgo Duration: " << time_in_seconds.count() << endl;

        start = std::chrono::high_resolution_clock::now();
        MostExpensiveFirstAlgo secondAlgorithm;
        secondAlgorithm.findOptimalPlacement(argv);
        end = std::chrono::high_resolution_clock::now();

        /*std::chrono::duration<double>*/ time_in_seconds = end - start;
        cout << fixed << "MostExpensiveFirstAlgo Duration: " << time_in_seconds.count() << endl;

        start = std::chrono::high_resolution_clock::now();
        CustomAlgo thirdAlgorithm;
        thirdAlgorithm.findOptimalPlacement(argv);
        end = std::chrono::high_resolution_clock::now();

        time_in_seconds = end - start;
        cout << fixed << "CustomAlgo Duration: " << time_in_seconds.count() << endl;
    }

    return 0;
}