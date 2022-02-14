//
// Created by mikec_g1kgiu8 on 2/8/2022.
//

#ifndef INC_22S_PA01_MISERY_CUSTOMALGO_H
#define INC_22S_PA01_MISERY_CUSTOMALGO_H

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class CustomAlgo {
private:
    bool findOptimalPlacement(vector<int>, vector<int>, vector<int>, vector<int>, int, int, vector<vector<int>>&, vector<vector<int>>&, int&, int&, int&, bool);

    void sortByCostPerUnit(vector<int>&, vector<int>&, vector<int>&, vector<int>&, int, int);
    void swap(int*, int*);
    int partition(vector<int>&, vector<int>&, vector<int>&, vector<int>&, int, int);

public:
    void findOptimalPlacement(char**);
};


#endif //INC_22S_PA01_MISERY_CUSTOMALGO_H
