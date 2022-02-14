//
// Created by mikec_g1kgiu8 on 2/1/2022.
//

#ifndef INC_22S_PA01_MISERY_BRUTEFORCEALGO_H
#define INC_22S_PA01_MISERY_BRUTEFORCEALGO_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


class BruteForceAlgo {
    private:
        vector<vector<int>> findOptimalValue(vector<int>, vector<int>, vector<int>, vector<int>, int);

    public:
        void findOptimalPlacement(char**);
};


#endif //INC_22S_PA01_MISERY_BRUTEFORCEALGO_H
