//
// Created by mikec_g1kgiu8 on 2/1/2022.
//

#include "BruteForceAlgo.h"

void BruteForceAlgo::findOptimalPlacement(char** argv) {
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

    vector<vector<int>> theOptimalSolution = findOptimalValue(pictureIDs, pictureValues, pictureWidths, pictureHeights, wallLength);

    cout << theOptimalSolution.at(0).at(0) << endl;
    vector<int> optimalIDs = theOptimalSolution.at(1);
    vector<int> optimalValues = theOptimalSolution.at(2);
    vector<int> optimalWidths = theOptimalSolution.at(3);
    vector<int> optimalHeights = theOptimalSolution.at(4);

    for (int i = 0; i < optimalIDs.size(); i++) {
        cout << optimalIDs.at(i) << " " << optimalValues.at(i) << " " << optimalWidths.at(i) << " " << optimalHeights.at(i) << endl;
    }
}

vector<vector<int>> BruteForceAlgo::findOptimalValue(vector<int> pictureIDs, vector<int> pictureValues, vector<int> pictureWidths, vector<int> pictureHeights, int wallLength) { //inspired by code found at: https://stackoverflow.com/questions/728972/finding-all-the-subsets-of-a-set
    vector<vector<int>> IDSubsets;
    vector<vector<int>> valueSubsets;
    vector<vector<int>> widthSubsets;
    vector<vector<int>> heightSubsets;

    vector<int> empty;
    IDSubsets.push_back(empty);
    valueSubsets.push_back(empty);
    widthSubsets.push_back(empty);
    heightSubsets.push_back(empty);

    int bestPrice = -1;
    vector<vector<int>> results;


    for (int i = 0; i < pictureIDs.size(); i++) {
        vector<vector<int>> IDTemp = IDSubsets;
        vector<vector<int>> valueTemp = valueSubsets;
        vector<vector<int>> widthTemp = widthSubsets;
        vector<vector<int>> heightTemp = heightSubsets;

        int currentPrice, currentLength;
//        cout << "Size: " << temp.size() << endl;

        for (int j = 0; j < IDTemp.size(); j++) {
            IDTemp[j].push_back(pictureIDs[i]);
            valueTemp[j].push_back(pictureValues[i]);
            widthTemp[j].push_back(pictureWidths[i]);
            heightTemp[j].push_back(pictureHeights[i]);
        }
        for (int j = 0; j < IDTemp.size(); j++) {
            currentPrice = 0;
            currentLength = 0;
            for (int k = 0; k < IDTemp[j].size(); k++) {
//                cout << IDTemp[j][k] << " ";
                currentPrice += valueTemp[j][k];
                currentLength += widthTemp[j][k];
            }
//            cout << endl;

            if (currentPrice > bestPrice && currentLength < wallLength) {
                vector<vector<int>> theBest;
                vector<int> theBestPrice;
                theBestPrice.push_back(currentPrice);
                bestPrice = currentPrice;

                theBest.push_back(theBestPrice);
                theBest.push_back(IDTemp[j]);
                theBest.push_back(valueTemp[j]);
                theBest.push_back(widthTemp[j]);
                theBest.push_back(heightTemp[j]);

                results = theBest;
            }

            IDSubsets.push_back(IDTemp[j]);
            valueSubsets.push_back(valueTemp[j]);
            widthSubsets.push_back(widthTemp[j]);
            heightSubsets.push_back(heightTemp[j]);
        }
    }

    return results;
}
