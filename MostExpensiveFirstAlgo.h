//
// Created by mikec_g1kgiu8 on 2/2/2022.
//

#ifndef INC_22S_PA01_MISERY_MOSTEXPENSIVEFIRSTALGO_H
#define INC_22S_PA01_MISERY_MOSTEXPENSIVEFIRSTALGO_H

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


class MostExpensiveFirstAlgo {
    private:
        vector<vector<int>> findOptimalPlacement(vector<int>, vector<int>, vector<int>, vector<int>, int);
        void sortByMostExpensive(vector<int>&, vector<int>&, vector<int>&, vector<int>&, int, int);

        void swap(int*, int*);
        int partition(vector<int>&, vector<int>&, vector<int>&, vector<int>&, int, int);

    public:
        void findOptimalPlacement(char**);
};


#endif //INC_22S_PA01_MISERY_MOSTEXPENSIVEFIRSTALGO_H
