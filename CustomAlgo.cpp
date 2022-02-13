//
// Created by mikec_g1kgiu8 on 2/8/2022.
//

#include "CustomAlgo.h"

void CustomAlgo::findOptimalPlacement(char** argv) {
    cout << endl << "THIRD: " << endl;
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

    vector<vector<int>> theSolution;
    findOptimalPlacement(pictureIDs, pictureValues, pictureWidths, pictureHeights, wallLength, 0, theSolution, false);

    int totalPrice = 0;

    for (int i = 0; i < theSolution.size(); i++) {
        vector<int> temp = theSolution.at(i);
        totalPrice += temp.at(1);
    }

    cout << totalPrice << endl;

    for (int i = 0; i < theSolution.size(); i++) {
        vector<int> temp = theSolution.at(i);
        for (int j = 0; j < temp.size(); j++) {
            cout << temp.at(j) << " ";
        }
        cout << endl;
    }

}

bool CustomAlgo::findOptimalPlacement(vector<int> pictureIDs, vector<int> pictureValues, vector<int> pictureWidths, vector<int> pictureHeights, int wallLength, int start, vector<vector<int>>& theSolution, bool recursiveCall) {
    vector<vector<int>> backupSolution;

    for (int i = start; i < pictureWidths.size(); i++) {
        if (pictureWidths.at(i) <= wallLength) {

//            cout << "Wall Length: " << wallLength << endl;
//            cout << "Adding " << pictureIDs.at(i) << " " << pictureValues.at(i) << " " << pictureWidths.at(i) << " " << pictureHeights.at(i) << endl;
            vector<int> temp = {pictureIDs.at(i), pictureValues.at(i), pictureWidths.at(i), pictureHeights.at(i)};
            theSolution.push_back(temp);
            backupSolution.push_back(temp); //FIXME backup is here

//            cout << "Math: " << wallLength - pictureWidths.at(i) << endl;

            if (findOptimalPlacement(pictureIDs, pictureValues, pictureWidths, pictureHeights, wallLength - pictureWidths.at(i), i + 1, theSolution, true)) {
                return true;
            }

//            theSolution.insert(theSolution.end(), anotherTemp.begin(), anotherTemp.end());
            wallLength -= pictureWidths.at(i);

        } else if (wallLength == 0) { //FIXME what threshold to use??
//            cout << "Bonjour" << endl;
            return true;
        }
    }

//    cout << "Returning theSolution" << endl;
//    cout << "Removing last element" << endl;

//    for (int i = 0; i < theSolution.at(theSolution.size() - 1).size(); i++) {
//        theSolution.at(theSolution.size() - 1).pop_back();
//    }

    if (theSolution.size() > 0) {
        theSolution.pop_back();
    }

    if (recursiveCall) {
        return false;
    } else {
        cout << "Using backup" << endl;
        theSolution = backupSolution;
        return true;
    }
}

//FIXME what I'm trying to do:
//Loop through the vectors, adding pictures to the wall
//once the remaining space on the wall is 0, return the pictures
//if you can't get it to equal 0, backtrack to the previous picture

