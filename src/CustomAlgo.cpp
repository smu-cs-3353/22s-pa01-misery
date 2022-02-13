//
// Created by mikec_g1kgiu8 on 2/8/2022.
//

#include "CustomAlgo.h"

void CustomAlgo::findOptimalPlacement(char** argv) {
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

    sortByLeastSpace(pictureIDs, pictureValues, pictureWidths, pictureHeights, 0, pictureWidths.size() - 1);

//    for (int i = 0; i < pictureWidths.size(); i++) {
//        cout << pictureWidths.at(i) << endl;
//    }

    vector<vector<int>> theSolution;
    findOptimalPlacement(pictureIDs, pictureValues, pictureWidths, pictureHeights, wallLength, 0, theSolution, false);

    int totalPrice = 0;

    for (int i = 0; i < theSolution.size(); i++) {
        vector<int> temp = theSolution.at(i);
        totalPrice += temp.at(1);
    }

    string fileName = argv[1];
    for (int i = 0; i < 4; i++) {
        fileName.pop_back();
    }
    fileName += "-custom.txt";

    ofstream output(fileName);

    output << totalPrice << endl;

    for (int i = 0; i < theSolution.size(); i++) {
        vector<int> temp = theSolution.at(i);
        for (int j = 0; j < temp.size(); j++) {
            output << temp.at(j) << " ";
        }
        output << endl;
    }

    output.close();

}

bool CustomAlgo::findOptimalPlacement(vector<int> pictureIDs, vector<int> pictureValues, vector<int> pictureWidths, vector<int> pictureHeights, int wallLength, int start, vector<vector<int>>& theSolution, bool recursiveCall) {
    vector<vector<int>> backupSolution;

    for (int i = start; i < pictureWidths.size(); i++) {
        if (pictureWidths.at(i) <= wallLength) {

            vector<int> temp = {pictureIDs.at(i), pictureValues.at(i), pictureWidths.at(i), pictureHeights.at(i)};
            theSolution.push_back(temp);
            backupSolution.push_back(temp); //FIXME backup is here


            if (findOptimalPlacement(pictureIDs, pictureValues, pictureWidths, pictureHeights, wallLength - pictureWidths.at(i), i + 1, theSolution, true)) {
                return true;
            }

            wallLength -= pictureWidths.at(i);

        } else if (wallLength == 0) { //FIXME what threshold to use??
            return true;
        }
    }

    if (theSolution.size() > 0) {
        theSolution.pop_back();
    }

    if (recursiveCall) {
        return false;
    } else {
//        cout << "Using backup" << endl;
        theSolution = backupSolution;
        return true;
    }
}

//The following sorting algorithm is a quick sort algorithm inspired by code found at: https://www.geeksforgeeks.org/quick-sort/
void CustomAlgo::sortByLeastSpace(vector<int>& pictureIDs, vector<int>& pictureValues, vector<int>& pictureWidths, vector<int>& pictureHeights, int low, int high) {
    if (low < high) {
        int partitionIndex = partition(pictureIDs, pictureValues, pictureWidths, pictureHeights, low, high);

        sortByLeastSpace(pictureIDs, pictureValues, pictureWidths, pictureHeights, low, partitionIndex - 1);
        sortByLeastSpace(pictureIDs, pictureValues, pictureWidths, pictureHeights, partitionIndex + 1, high);
    }
}

int CustomAlgo::partition(vector<int>& pictureIDs, vector<int>& pictureValues, vector<int>& pictureWidths, vector<int>& pictureHeights, int low, int high) {
    int pivot = pictureWidths.at(high);
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (pictureWidths.at(j) < pivot) {
            i++;
            swap(&pictureIDs.at(i), &pictureIDs.at(j));
            swap(&pictureValues.at(i), &pictureValues.at(j));
            swap(&pictureWidths.at(i), &pictureWidths.at(j));
            swap(&pictureHeights.at(i), &pictureHeights.at(j));
        }
    }
    swap(&pictureIDs.at(i + 1), &pictureIDs.at(high));
    swap(&pictureValues.at(i + 1), &pictureValues.at(high));
    swap(&pictureWidths.at(i + 1), &pictureWidths.at(high));
    swap(&pictureHeights.at(i + 1), &pictureHeights.at(high));

    return i + 1;
}

void CustomAlgo::swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//FIXME what I'm trying to do:
//Loop through the vectors, adding pictures to the wall
//once the remaining space on the wall is 0, return the pictures
//if you can't get it to equal 0, backtrack to the previous picture

