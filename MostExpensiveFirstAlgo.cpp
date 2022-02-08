//
// Created by mikec_g1kgiu8 on 2/2/2022.
//

#include "MostExpensiveFirstAlgo.h"

void MostExpensiveFirstAlgo::findOptimalPlacement(char** argv) {
    cout << "NEXT: " << endl;
    ifstream input(argv[1]);

    int wallLength, wallHeight, numArtPieces;
    input >> wallLength >> wallHeight >> numArtPieces;

    vector<int> pictureIDs, pictureValues, pictureWidths, pictureHeights;
    int pictureID, pictureValue, pictureWidth, pictureHeight;

    for (int i = 0; i < numArtPieces; i++) {
        input >> pictureID >> pictureValue >> pictureWidth >> pictureHeight;
        cout << pictureID << " " << pictureValue << " " << pictureWidth << " " << pictureHeight << endl;

        pictureIDs.push_back(pictureID);
        pictureValues.push_back(pictureValue);
        pictureWidths.push_back(pictureWidth);
        pictureHeights.push_back(pictureHeight);
    }
    cout << endl;

    sortByMostExpensive(pictureIDs, pictureValues, pictureWidths, pictureHeights, 0, pictureValues.size() - 1);

    for (int i = 0; i < pictureValues.size(); i++) {
        cout << pictureIDs.at(i) << " " << pictureValues.at(i) << " " << pictureWidths.at(i) << " " << pictureHeights.at(i) << endl;
    }

}

vector<vector<int>> MostExpensiveFirstAlgo::findOptimalPlacement(vector<int>, vector<int>, vector<int>, vector<int>, int) {
    //return vector<vector<int>>();
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
        if (pictureValues.at(j) < pivot) {
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

void MostExpensiveFirstAlgo::swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
