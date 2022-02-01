//
// Created by mikec_g1kgiu8 on 1/26/2022.
//
#include <math.h>
#include <vector>

using namespace std;

vector<vector<int>> getSubsets(vector<int>);

#include <iostream>

int main() {
    //Brute Force Algorithm
    int wallLength = 1024; //FIXME need to change to reading in from a file
    int wallHeight = 768;
    int numArtPieces = 4;
    vector<int> pictureIDs = {12, 9, 23, 1};
    vector<int> pictureValues = {300, 200, 250, 100};
    vector<int> pictureWidths = {1023, 300, 800, 100};
    vector<int> pictureHeights = {767, 100, 700, 100};

    //the following subset generator was found at: https://www.includehelp.com/cpp-programs/print-all-possible-subset-of-a-set.aspx
    int counter = pow(2, 4); //FIXME change 4 to number of pictures
    int totalPrice = 0;
    vector<vector<int>> subsets = getSubsets(pictureIDs);
    for (int i = 0; i < subsets.size(); i++) {
        for (int j = 0; j < subsets[i].size(); j++) {
            cout << subsets[i][j] << " ";
        }
        cout << endl;
    }


//    for (int i = 0; i < counter; i++) {
//        int tempPrice = 0;
//        for (int j = 0; j < 4; j++) { //FIXME change 4 to number of pictures
//            if ((i & (1 << j)) != 0)
//                cout << pictureIDs[j] << " ";
//        }
//        cout << endl;
//    }

//    for (int i = 0; i < 4; i++) {
//        int tempPrice = 0;
//        counter = pow(2, 4 - 1 - i); //FIXME change 4 to number of pictures
//        for (int j = 0; j < counter; j++) {
//
//        }
//    }
}

vector<vector<int>> getSubsets(vector<int> pictureIDs) { //inspired by code found at: https://stackoverflow.com/questions/728972/finding-all-the-subsets-of-a-set
    vector<vector<int>> subsets;
    vector<int> empty;
    subsets.push_back(empty);

    for (int i = 0; i < pictureIDs.size(); i++) {
        vector<vector<int>> temp = subsets;

        for (int j = 0; j < temp.size(); j++) {
            temp[j].push_back(pictureIDs[i]);
        }
        for (int j = 0; j < temp.size(); j++) {
            subsets.push_back(temp[j]);
        }
    }

    return subsets;
}