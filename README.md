# PA 01: The Art Gallery
by Michael Doherty

## Project Description
In this project, I needed to develop three algorithms that would determine the optimal subset of pictures to place on a wall such that, if all pictures were sold, it would maximize profit. All pictures are placed along the centerline of the wall, and the length and height of the wall, as well as the value, width, and height of each picture, were given to me. Thus, I created a brute force algorithm, which finds the best possible solution (but is incredibly slow at large dataset sizes), a most expensive picture first algorithm (which places the pictures on the wall starting with the most expensive first), and a custom algorithm that attempts to find a better solution than the most expensive picture first algorithm while being significantly faster than the brute force algorithm.

## Building and Executing
To build the program from the terminal, simply navigate to the src folder in your terminal and use the command:  
**g++ main.cpp BruteForceAlgo.cpp CustomAlgo.cpp MostExpensiveFirstAlgo.cpp -o output**  
(Note that after the -o, you can name the executable whatever you want). To run the program, simply type the command:  
**./output ../input/PictureInfo.txt**  
(Again, note that output should be replaced with the name of your executable). As seen above, the program requires a single command line argument containing the picture data formatted like the sample input shown below. If no command line argument is given, the program outputs an error message. Other input files are avaliable to use, although it is not advisable to run them through the brute force algorithm (as it will take too long).

## Brute Force Algorithm
The Brute Force Algorithm's goal is to find the combination of pictures that results in the highest total value. To do so, it generates all possible combinations of the pictures. It compares each combination's total price and total length to the current best price and the wall length. If a combination's price is the highest found so far, and the combination of pictures fits on the wall, then the algorithm stores that combination. After all combinations have been generated and checked, the algorithm returns the combination with the best possible price (given that it also fits on the wall). The results are outputted to a file.

The Brute Force Algorithm took the longest to run by far; however, this was expected, as the number of subsets the algorithm has to generate increases exponentially as the number of pictures increases. The largest data set I could get to run with the Brute Force Algorithm was 23 pictures. The following graph compares the time it took the algorithm to run to the number of pictures in the data set:
![](images/Algo%20Project%201%20Graph%201.png)

## Most Expensive First Algorithm
The Most Expensive First Algorithm's goal is to generate a much faster solution than brute force by simply placing the pictures on the wall from most expensive to least expensive, skipping any pictures that do not fit on the wall. To do this, I used a Quick Sort algorithm to sort the picture data from highest picture value to lowest picture value. Then I iterated over the sorted data, adding each picture to the wall if it fit in the remaining wall space. The results are outputted to a file. 

The Most Expensive First Algorithm was extremely quick, even on large data sets; this was expected, as quick sort is extremely efficient and the algorithm only iterates through a single for loop once. The following graph compares the time it took the algorithm to run to the number of pictures in the data set:
![](images/Algo%20Project%201%20Graph%202.png)

## Custom Algorithm
The Custom Algorithm's goal is to generate a faster solution than brute force while finding a solution with a higher value than most expensive first. To do this, I used a Quick Sort algorithm to sort the pictures by the ratio of the cost of each picture to the amount of space it takes up (with the highest ratio being first). Thus, a picture that costs $20 with a width of 5 units would be placed before a picture that costs $20 with a width of 10 units. After sorting the picture data, I used a recursive function (called findOptimalPlacement) to iterate through every picture, placing each picture on the wall if it fit, only ending if a solution that takes up all wall space is found. If such a solution isn't initally found, then the function backtracks and removes the last picture placed on the wall. It then tries to place subsequent pictures on the wall until all wall space is taken up. This process is repeated until a solution that takes up all wall space is found. During this process, the algorithm compares each solution that does not take up all of the wall space to a "backup solution" and stores the solution it finds with the highest total value. In the event that there are no solutions that take up all of the wall space, the backup solution is used. Additionally, if a solution that takes up all of the wall space is found, its value is compared to the backup solution; if the backup solution has a higher total value, then the backup solution is used instead. Either way, the algorithm ends once a solution that takes up all wall space is found (even if the backup solution is used instead); this significantly speeds up the algorithm on large data sets.

My custom algorithm was also extremely quick, although it was consistently slower than the most expensive first algorithm. Nevertheless, my custom algorithm's speed allowed it to run extremely quickly on large data sets that would take brute force a long time. The following graph compares the time it took the algorithm to run to the number of pictures in the data set:
![](images/Algo%20Project%201%20Graph%203.png)

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

## Performance
Comparing the times of all three algorithms, the Brute Force Algorithm was significantly slower than the other two (as expected). As I mentioned above, my Custom Algorithm was consistently slower than the Most Expensive First Algorithm, but not by much. A comparison of the Custom Algorithm's runtime and the Most Expensive First Algorithm's runtime is shown below:
![](images/Algo%20Project%201%20Graph%204.png)

Comparing the accuracy at determining the best arrangement of pictures to maximize value, the Brute Force Algorithm was obviously the best (as it generates every possible combination to find the highest total value). However, when I tested my Custom Algorithm on the same data set as the Brute Force Algorithm, it consistenly found the same solution as the Brute Force Algorithm in a significantly faster time (that's why in the graph below you cannot see the blue line representing the Brute Force Algorithm, as the gray line representing my Custom Algorithm completely overlaps it). However, the Most Expensive First Algorithm, while initially finding the most optimal solution, was not able to continue to do so as the size of the data set increased. This can be observed in the following graph:
![](images/Algo%20Project%201%20Graph%206.png)
(Note for the above graph, the data set used was PictureInfo_2.txt. To get the different sizes, I simply changed the number on the second line (representing the number of pictures in the data set)).

I also tested the Most Expensive First Algorithm and my Custom Algorithm on data sets ranging from 100 to 5000 pictures (the Brute Force Algorithm was not used as it became impractical to use after 23 pictures). For each data set, my Custom Algorithm was consistenly finding better solutions than the Most Expensive First Algorithm; additionally, as the data sets grew larger, my Custom Algorithm consistenly found solutions that increased in total value, while the Most Expensive First Algorithm sometimes found solutions that decreased in total value from the smaller data set. This can be observed in the following graph:
![](images/Algo%20Project%201%20Graph%205.png)
(Note for the above graph, the data set used was test.txt. To get the different sizes, I simply changed the number on the second line (representing the number of pictures in the data set)).

Thus, for large data sets, my Custom Algorithm is clearly the best option. At smaller data sets, the Brute Force Algorithm is most optimal (although during my testing, my Custom Algorithm found the same solutions as the Brute Force Algorithm in a faster time). The Brute Force Algorithm's inefficiency at large data sets can be attributed to it being O(2<sup>n</sup>), as the number of subsets it has to generate increases exponentially as the data set increases. The Most Expensive First Algorithm is the fastest of the three algorithms, but its strategy of placing the most expensive pictures on the wall first, regardless of their size, becomes highly ineffective for large data sets (due to combinations of smaller pictures being worth more than the large value pictures it prioritizes). By taking into account how much each picture is worth per unit of space it takes up, my Custom Algorithm provides a much better solution at large data sets.

While the Brute Force Algorithm will inevitably produce the best ordering of pictures, it becomes impractical to use on data sets larger than about 23 pictures. On the other hand, the Most Expensive Picture First Algorithm will produce results extremely quickly, but its method of placing the most expensive pictures on the wall first becomes ineffective at large data sets. Thus, my Custom Algorithm, which provided quick and effective results, proves to be the most useful algorithm to use on large data sets.
