//
// Created by mikec_g1kgiu8 on 2/2/2022.
//

#include "MostExpensiveFirstAlgo.h"

void MostExpensiveFirstAlgo::findOptimalPlacement(char** argv) {
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

    //sorts the picture data vectors from highest value to lowest value
    sortByMostExpensive(pictureIDs, pictureValues, pictureWidths, pictureHeights, 0, pictureValues.size() - 1);

    //finds the solution
    vector<vector<int>> theOptimalSolution = findOptimalPlacement(pictureIDs, pictureValues, pictureWidths, pictureHeights, wallLength);


    string fileName = argv[1];
    for (int i = 0; i < 4; i++) { //removes .txt from fileName
        fileName.pop_back();
    }
    fileName += "-highvalue.txt";

    ofstream output(fileName);

    output << theOptimalSolution.at(theOptimalSolution.size() - 1).at(0) << endl; //outputs the total value of the pictures on the wall

    for (int i = 0; i < theOptimalSolution.size() - 1; i++) { //outputs the data of the pictures on the wall
        vector<int> temp = theOptimalSolution.at(i);
        for (int j = 0; j < temp.size(); j++) {
            output << temp.at(j) << " ";
        }
        output << endl;
    }

    output.close();
}

vector<vector<int>> MostExpensiveFirstAlgo::findOptimalPlacement(vector<int> pictureIDs, vector<int> pictureValues, vector<int> pictureWidths, vector<int> pictureHeights, int wallLength) {
    vector<vector<int>> theSolution;
    int totalPrice = 0; //stores the total value of the pictures on the wall
    for (int i = 0; i < pictureValues.size(); i++) {
        if (pictureWidths.at(i) <= wallLength) { //if the picture fits on the wall
            wallLength -= pictureWidths.at(i); //remove the size of the picture from the remaining wall space

            vector<int> temp = {pictureIDs.at(i), pictureValues.at(i), pictureWidths.at(i), pictureHeights.at(i)};
            theSolution.push_back(temp); //add the picture to theSolution
            totalPrice += pictureValues.at(i); //update the total price
        } else if (wallLength <= 0) { //if the wall is full
            break;
        }
    }
    vector<int> temp = {totalPrice}; //store the total price
    theSolution.push_back(temp);

    return theSolution; //return theSolution
}

//The following sorting algorithm is a quick sort algorithm inspired by code found at: https://www.geeksforgeeks.org/quick-sort/
void MostExpensiveFirstAlgo::sortByMostExpensive(vector<int>& pictureIDs, vector<int>& pictureValues, vector<int>& pictureWidths, vector<int>& pictureHeights, int low, int high) {
    if (low < high) {
        int partitionIndex = partition(pictureIDs, pictureValues, pictureWidths, pictureHeights, low, high);

        sortByMostExpensive(pictureIDs, pictureValues, pictureWidths, pictureHeights, low, partitionIndex - 1);
        sortByMostExpensive(pictureIDs, pictureValues, pictureWidths, pictureHeights, partitionIndex + 1, high);
    }
}

int MostExpensiveFirstAlgo::partition(vector<int>& pictureIDs, vector<int>& pictureValues, vector<int>& pictureWidths, vector<int>& pictureHeights, int low, int high) {
    int pivot = pictureValues.at(high);
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (pictureValues.at(j) > pivot) {
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

//swaps the values of a and b
void MostExpensiveFirstAlgo::swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
