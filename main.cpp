//
// Created by mikec_g1kgiu8 on 1/26/2022.
//
#include <cmath> //FIXME is this used?
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<vector<int>> getSubsets(vector<int>);


int main(int argc, char** argv) {
    //Brute Force Algorithm
//    int wallLength = 1024; //FIXME need to change to reading in from a file
//    int wallHeight = 768;
//    int numArtPieces = 4;
//    vector<int> pictureIDs = {12, 9, 23, 1};
//    vector<int> pictureValues = {300, 200, 250, 100};
//    vector<int> pictureWidths = {1023, 300, 800, 100};
//    vector<int> pictureHeights = {767, 100, 700, 100};
    ifstream input(argv[1]);

    int wallLength, wallHeight, numArtPieces;
    input >> wallLength >> wallHeight >> numArtPieces;

    vector<int> pictureIDs, pictureValues, pictureWidths, pictureHeights;
    int pictureID, pictureValue, pictureWidth, pictureHeight;

    for (int i = 0; i < numArtPieces; i++) {
        input >> pictureID >> pictureValue >> pictureWidth >> pictureHeight;

        pictureIDs.push_back(pictureID);
        pictureValues.push_back(pictureValue);
        pictureWidths.push_back(pictureWidth);
        pictureHeights.push_back(pictureHeight);
    }

    vector<vector<int>> subsets = getSubsets(pictureIDs);
    for (int i = 0; i < subsets.size(); i++) {
        for (int j = 0; j < subsets[i].size(); j++) {
            cout << subsets[i][j] << " ";
        }
        cout << endl;
    }
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