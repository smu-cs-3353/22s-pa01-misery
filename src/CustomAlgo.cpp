//
// Created by mikec_g1kgiu8 on 2/8/2022.
//

#include "CustomAlgo.h"

void CustomAlgo::findOptimalPlacement(char** argv) {
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

    //the following line sorts the arrays by cost per unit of space (highest to lowest)
    sortByCostPerUnit(pictureIDs, pictureValues, pictureWidths, pictureHeights, 0, pictureWidths.size() - 1);

    vector<vector<int>> theSolution, backupSolution;
    int totalCost = 0;
    int backupCost = 0;
    findOptimalPlacement(pictureIDs, pictureValues, pictureWidths, pictureHeights,
                         wallLength, 0, theSolution, backupSolution, wallLength, totalCost, backupCost, false);

    string fileName = argv[1];
    for (int i = 0; i < 4; i++) { //removes the .txt ending
        fileName.pop_back();
    }
    fileName += "-custom.txt";
    fileName.at(3) = 'o';
    fileName.at(4) = 'u';
    fileName.insert(5, 1, 't');

    ofstream output(fileName);

    output << totalCost << endl;

    for (int i = 0; i < theSolution.size(); i++) { //outputs the data of the pictures on the wall
        vector<int> temp = theSolution.at(i);
        for (int j = 0; j < temp.size(); j++) {
            output << temp.at(j) << " ";
        }
        output << endl;
    }

    output.close();

}

//recursive function that tries to find a solution that takes up all wall space. While looking for such a solution, it
//stores the combination of pictures with the highest value that it finds in backupSolution; if backupSolution has a
//higher total value than a solution that takes up all wall space, it will look for another solution that takes up all
//wall space. If no solution is found that has a higher value than backupSolution and takes up all wall space, then
//backupSolution is used as the solution
bool CustomAlgo::findOptimalPlacement(vector<int> pictureIDs, vector<int> pictureValues, vector<int> pictureWidths,
                                      vector<int> pictureHeights, int wallLength, int start, vector<vector<int>>& theSolution,
                                      vector<vector<int>>& backupSolution, int& backupSpaceRemaining, int& totalCost, int& backupCost, bool recursiveCall) {

    for (int i = start; i < pictureWidths.size(); i++) { //iterates through the picture dataset until it finds a picture that can fit on the wall
        if (pictureWidths.at(i) <= wallLength) { //if the picture fits on the wall

            vector<int> temp = {pictureIDs.at(i), pictureValues.at(i), pictureWidths.at(i), pictureHeights.at(i)};
            theSolution.push_back(temp); //add the picture data to theSolution
            totalCost += pictureValues.at(i); //updates totalCost

            //the following line is if the current solution takes up more space than the backupSolution and its price is better
            if (wallLength - pictureWidths.at(i) < backupSpaceRemaining && totalCost > backupCost) {
                backupSolution = theSolution; //update backupSolution
                backupSpaceRemaining = wallLength - pictureWidths.at(i); //update backupSpaceRemaining
                backupCost = totalCost; //update backupCost
            }

            if (findOptimalPlacement(pictureIDs, pictureValues, pictureWidths, pictureHeights,
                                     wallLength - pictureWidths.at(i), i + 1, theSolution, backupSolution,
                                     backupSpaceRemaining, totalCost, backupCost, true)) { //recursive call that returns true if the best solution is found
                return true;
            } else {
                totalCost -= pictureValues.at(i); //removes the picture's value from totalCost (as the picture was removed from the wall by backtracking)
            }
            
        } else if (wallLength == 0) { //if a solution that takes up all wall space is found
            if (backupCost > totalCost) { //if, after finding a solution that fills the entire wall, the backupSolution has a better total value
                totalCost = backupCost; //change the cost to the backupCost
                theSolution = backupSolution; //change the solution to backupSolution
            }
            return true; //return true
        }
    }

    if (!theSolution.empty()) { //if the optimal solution is not found, then remove the last picture from the wall
        theSolution.pop_back();
    }

    if (recursiveCall) { //if it's a recursive call, backtrack (which causes a picture to be removed from the wall)
        return false;
    } else { //if it's not a recursive call (and thus called from findOptimalPlacement) and a solution that takes up all
        //wall space is not found. In this case, we use backupSolution (which contains the solution with the highest value found)
        theSolution = backupSolution;
        totalCost = backupCost;
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
