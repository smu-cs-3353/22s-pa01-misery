//
// Created by mikec_g1kgiu8 on 2/1/2022.
//

#include "BruteForceAlgo.h"

void BruteForceAlgo::findOptimalPlacement(char** argv) {
    ifstream input(argv[1]);

    if (!input.is_open()) {
        cout << "Could not open " << argv[1] << endl;
        return;
    }

    int wallLength, wallHeight, numArtPieces;
    input >> wallLength >> wallHeight >> numArtPieces; //wall data + number of art pieces

    vector<int> pictureIDs, pictureValues, pictureWidths, pictureHeights;
    int pictureID, pictureValue, pictureWidth, pictureHeight;

    for (int i = 0; i < numArtPieces; i++) { //reads all the picture data and stores it in vectors
        input >> pictureID >> pictureValue >> pictureWidth >> pictureHeight;

        pictureIDs.push_back(pictureID);
        pictureValues.push_back(pictureValue);
        pictureWidths.push_back(pictureWidth);
        pictureHeights.push_back(pictureHeight);
    }

    //finds the best possible solution through brute force
    vector<vector<int>> theOptimalSolution = findOptimalValue(pictureIDs, pictureValues,
                                                              pictureWidths, pictureHeights, wallLength);

    string fileName = argv[1];
    for (int i = 0; i < 4; i++) { //gets rid of the .txt in fileName
        fileName.pop_back();
    }
    fileName += "-bruteforce.txt";
    fileName.at(3) = 'o';
    fileName.at(4) = 'u';
    fileName.insert(5, 1, 't');

    ofstream output(fileName);

    output << theOptimalSolution.at(0).at(0) << endl; //outputs the total value of the pictures on the wall
    vector<int> optimalIDs = theOptimalSolution.at(1);
    vector<int> optimalValues = theOptimalSolution.at(2);
    vector<int> optimalWidths = theOptimalSolution.at(3);
    vector<int> optimalHeights = theOptimalSolution.at(4);


    for (int i = 0; i < optimalIDs.size(); i++) { //outputs the data of the pictures on the wall
        output << optimalIDs.at(i) << " " << optimalValues.at(i) << " " << optimalWidths.at(i) << " " << optimalHeights.at(i) << endl;
    }

    output.close();
}

//inspired by code found at: https://stackoverflow.com/questions/728972/finding-all-the-subsets-of-a-set
vector<vector<int>> BruteForceAlgo::findOptimalValue(vector<int> pictureIDs, vector<int> pictureValues, vector<int> pictureWidths,
                                                     vector<int> pictureHeights, int wallLength) {
    vector<vector<int>> IDSubsets; //all subsets for picture IDs
    vector<vector<int>> valueSubsets; //all subsets for picture values
    vector<vector<int>> widthSubsets; //all subsets for picture widths
    vector<vector<int>> heightSubsets; //all subsets for picture heights

    vector<int> empty; //the empty subset
    IDSubsets.push_back(empty);
    valueSubsets.push_back(empty);
    widthSubsets.push_back(empty);
    heightSubsets.push_back(empty);

    int bestPrice = -1; //initializing bestPrice
    vector<vector<int>> results;

    for (int i = 0; i < pictureIDs.size(); i++) {
        vector<vector<int>> IDTemp = IDSubsets;
        vector<vector<int>> valueTemp = valueSubsets;
        vector<vector<int>> widthTemp = widthSubsets;
        vector<vector<int>> heightTemp = heightSubsets;

        int currentPrice, currentLength;

        for (int j = 0; j < IDTemp.size(); j++) { //loop size doubles every time i increases
            IDTemp[j].push_back(pictureIDs[i]);
            valueTemp[j].push_back(pictureValues[i]);
            widthTemp[j].push_back(pictureWidths[i]);
            heightTemp[j].push_back(pictureHeights[i]);
        }
        for (int j = 0; j < IDTemp.size(); j++) { //loop size doubles every time i increases
            currentPrice = 0;
            currentLength = 0;
            for (int k = 0; k < IDTemp[j].size(); k++) {
                currentPrice += valueTemp[j][k]; //calculates the current subset's total price
                currentLength += widthTemp[j][k]; //calculates the current subset's total width
            }

            if (currentPrice > bestPrice && currentLength <= wallLength) { //if a better solution is found
                vector<vector<int>> theBest;
                vector<int> theBestPrice;
                theBestPrice.push_back(currentPrice);
                bestPrice = currentPrice;

                theBest.push_back(theBestPrice);
                theBest.push_back(IDTemp[j]);
                theBest.push_back(valueTemp[j]);
                theBest.push_back(widthTemp[j]);
                theBest.push_back(heightTemp[j]);

                results = theBest; //stores the better solution
            }

            IDSubsets.push_back(IDTemp[j]);
            valueSubsets.push_back(valueTemp[j]);
            widthSubsets.push_back(widthTemp[j]);
            heightSubsets.push_back(heightTemp[j]);
        }
    }

    return results;
}
