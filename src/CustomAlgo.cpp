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

    for (int i = 0; i < numArtPieces; i++) { //reads all the picture data and stores it in vectors
        input >> pictureID >> pictureValue >> pictureWidth >> pictureHeight;

        pictureIDs.push_back(pictureID);
        pictureValues.push_back(pictureValue);
        pictureWidths.push_back(pictureWidth);
        pictureHeights.push_back(pictureHeight);
    }

    //the following line sorts the arrays by cost per unit of space (highest to lowest)
    sortByCostPerUnit(pictureIDs, pictureValues, pictureWidths, pictureHeights, 0, pictureWidths.size() - 1);

    vector<vector<int>> theSolution, backupSolution;
    findOptimalPlacement(pictureIDs, pictureValues, pictureWidths, pictureHeights, wallLength, 0, theSolution, backupSolution, wallLength, false);

    int totalPrice = 0;

    for (int i = 0; i < theSolution.size(); i++) {
        vector<int> temp = theSolution.at(i);
        totalPrice += temp.at(1);
    }

    string fileName = argv[1];
    for (int i = 0; i < 4; i++) { //removes the .txt ending
        fileName.pop_back();
    }
    fileName += "-custom.txt";

    ofstream output(fileName);

    output << totalPrice << endl;

    for (int i = 0; i < theSolution.size(); i++) { //outputs the data of the pictures on the wall
        vector<int> temp = theSolution.at(i);
        for (int j = 0; j < temp.size(); j++) {
            output << temp.at(j) << " ";
        }
        output << endl;
    }

    output.close();

}

//recursive function that tries to find a solution that takes up all wall space. If no such solution exists, it finds
//the solution that takes up the most wall space (which is stored in backupSolution)
bool CustomAlgo::findOptimalPlacement(vector<int> pictureIDs, vector<int> pictureValues, vector<int> pictureWidths,
                                      vector<int> pictureHeights, int wallLength, int start, vector<vector<int>>& theSolution,
                                      vector<vector<int>>& backupSolution, int& backupWidth, bool recursiveCall) {

    for (int i = start; i < pictureWidths.size(); i++) { //iterates through the picture dataset until it finds a picture that can fit on the wall
        if (pictureWidths.at(i) <= wallLength) { //if the picture fits on the wall

            vector<int> temp = {pictureIDs.at(i), pictureValues.at(i), pictureWidths.at(i), pictureHeights.at(i)};
            theSolution.push_back(temp); //add the picture data to theSolution

            if (wallLength - pictureWidths.at(i) < backupWidth) { //if the current solution takes up more space than the backupSolution
                backupSolution = theSolution;
                backupWidth = wallLength - pictureWidths.at(i);
            }


            if (findOptimalPlacement(pictureIDs, pictureValues, pictureWidths, pictureHeights,
                                     wallLength - pictureWidths.at(i), i + 1, theSolution, backupSolution,
                                     backupWidth, true)) { //recursive call that returns true if the solution is found
                return true;
            }

        } else if (wallLength == 0) { //if a solution that takes up all wall space is found
            return true; //return true
        }
    }

    if (!theSolution.empty()) { //if the optimal solution is not found, then remove the last picture from theSolution
        theSolution.pop_back();
    }

    if (recursiveCall) { //if it's a recursive call, return false
        return false;
    } else { //if it's not a recursive call (and thus called from findOptimalPlacement), then no combination results in all wall
             //space being taken up. In this case, we use backupSolution (which contains the solution that takes up the most wall space)
        theSolution = backupSolution;
        return true;
    }
}

//The following sorting algorithm is a quick sort algorithm inspired by code found at: https://www.geeksforgeeks.org/quick-sort/
void CustomAlgo::sortByCostPerUnit(vector<int>& pictureIDs, vector<int>& pictureValues, vector<int>& pictureWidths, vector<int>& pictureHeights, int low, int high) {
    if (low < high) {
        int partitionIndex = partition(pictureIDs, pictureValues, pictureWidths, pictureHeights, low, high);

        sortByCostPerUnit(pictureIDs, pictureValues, pictureWidths, pictureHeights, low, partitionIndex - 1);
        sortByCostPerUnit(pictureIDs, pictureValues, pictureWidths, pictureHeights, partitionIndex + 1, high);
    }
}

int CustomAlgo::partition(vector<int>& pictureIDs, vector<int>& pictureValues, vector<int>& pictureWidths, vector<int>& pictureHeights, int low, int high) {
    double pivot = double(pictureValues.at(high)) / pictureWidths.at(high); //ratio of amount of money per unit of space
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (double(pictureValues.at(j)) / pictureWidths.at(j) > pivot) { //ratio of amount of money per unit of space
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

void CustomAlgo::swap(int* a, int* b) { //swaps the values passed to it
    int temp = *a;
    *a = *b;
    *b = temp;
}
