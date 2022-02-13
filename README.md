# PA 01: The Art Gallery
 by Michael Doherty

## Project Description
In this project, I needed to develop three algorithms that would determine the optimal subset of pictures to place on a wall such that, if all pictures were sold, it would maximize profit. All pictures are placed along the centerline of the wall, and the length and height of the wall, as well as the value, width, and height of each picture, were given to me. Thus, I created a brute force algorithm, which finds the best possible solution (but is incredibly slow at large dataset sizes), a most expensive picture first algorithm (which places the pictures on the wall starting with the most expensive first), and a custom algorithm that attempts to find a better solution than the most expensive picture first algorithm while being significantly faster than the brute force algorithm.

## Building and Executing
To build the program from the terminal, simply navigate to the src folder and use the command:  
**g++ main.cpp BruteForceAlgo.cpp CustomAlgo.cpp MostExpensiveFirstAlgo.cpp -o output**  
(Note that after the -o, you can name the executable whatever you want). To run the program, simply type the command:  
**./output ../input/PictureInfo.txt**  
(Again, note that output should be replaced with the name of your executable). As seen above, the program requires a single command line argument containing the picture data formatted like the sample input shown below. If no command line argument is given, the program outputs an error message.

## Brute Force Algorithm
The Brute Force Algorithm's goal is to find the combination of pictures that results in the highest total value. To do so, it generates all possible combinations of the pictures. It compares each combination's total price and total length to the current best price and the wall length. If a combination's price is the highest found so far, and the combination of pictures fits on the wall, then the algorithm stores that combination. After all combinations have been generated and checked, the algorithm returns the combination with the best possible price (given that it also fits on the wall). The results are outputted to a file.

## Most Expensive First Algorithm
The Most Expensive First Algorithm's goal is to generate a much faster solution than brute force by simply placing the pictures on the wall from most expensive to least expensive, skipping any pictures that do not fit on the wall. To do this, I used a Quick Sort algorithm to sort the picture data from highest picture value to lowest picture value. Then I iterated over the sorted data, adding each picture to the wall if it fit in the remaining wall space. The results are outputted to a file. 

## Custom Algorithm
The Custom Algorithm's goal is to generate a faster solution than brute force while finding a solution with a higher value than most expensive first. To do this, I used a Quick Sort algorithm to sort the pictures by the ratio of the cost of each picture to the amount of space it takes up (with the highest ratio being first). Thus, a picture that costs $20 with a width of 5 units would be placed before a picture that costs $20 with a width of 10 units. After sorting the picture data, I used a recursive function (called findOptimalPlacement) to iterate through every picture, placing each picture on the wall if it fit, only ending if a solution that takes up all wall space is found. If such a solution isn't initally found, then the function backtracks and removes the last picture placed on the wall. It then tries to place subsequent pictures on the wall until all wall space is taken up. This process is repeated until a solution that takes up all wall space is found. In the case that no such solution exists, the program stores the solution that takes up the most wall space and uses that instead.

## Sample Input
The input file should follow the following format:
- Line 1 should contain two integers separated by a space representing the length and height of the wall, respectively
- Line 2 contains a single integer 'n' that represents the total number of art pieces to follow
- Lines 3 to (3 + (n - 1)) should contain 4 integers each separated by spaces:
    - The first integer is the picture ID  
    - The second integer is the value of the picture  
    - The third integer is the width of the picture  
    - The fourth integer is the heigth of the picture  

An example input file is shown below:  
1024 768  
5  
49 632 417 858  
32 874 264 715  
20 150 545 795  
5 596 739 673  
80 279 991 146  

## Sample Output
The output consists of three output files, one for each algorithm. The names of the files contain the name of the input with "-bruteforce.txt", "-highvalue.txt" and "-custom.txt" appended depending on the algorithm used. For example, if an input file called "PictureInfo.txt" is used as the input, then the output will be:
PictureInfo-bruteforce.txt (for the brute force algorithm)
PictureInfo-highvalue.txt (for the most expensive first algorithm)
PictureInfo-custom.txt (for the custom algorithm)

For each output file, the first line contains the cumulative value of all pictures on the wall. Subsequent lines represent each picture on the wall and contain 4 integers each separated by spaces:
  - The first integer is the picture ID
  - The second integer is the value of the picture
  - The third integer is the width of the picture
  - The fourth integer is the heigth of the picture
A sample output for the brute force algorithm, based on the sample input from above, is shown below:  
1506  
49 632 417 858  
32 874 264 715  
