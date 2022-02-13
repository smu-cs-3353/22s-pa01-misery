# PA 01: The Art Gallery
 by Michael Doherty

## Project Description
In this project, I needed to develop three algorithms that would determine the optimal subset of pictures to place on a wall such that, if all pictures were sold, it would maximize profit. All pictures are placed along the centerline of the wall, and the length and height of the wall, as well as the value, width, and height of each picture, were given to me. Thus, I created a brute force algorithm, which finds the best possible solution (but is incredibly slow at large dataset sizes), a most expensive picture first algorithm (which places the pictures on the wall starting with the most expensive first), and a custom algorithm that attempts to find a better solution than the most expensive picture first algorithm while being significantly faster than the brute force algorithm.

## Building and Executing

## Brute Force Algorithm
The Brute Force Algorithm's goal is to find the combination of pictures that results in the highest total value. To do so, it generates all possible combinations of the pictures. It compares each combination's total price and total length to the current best price and the wall length. If a combination's price is the highest found so far, and the combination of pictures fits on the wall, then the algorithm stores that combination. After all combinations have been generated and checked, the algorithm returns the combination with the best possible price (given that it also fits on the wall). The results are outputted to a file.

## Most Expensive First Algorithm
The Most Expensive First Algorithm's goal is to generate a much faster solution than brute force by simply placing the pictures on the wall from most expensive to least expensive, skipping any pictures that do not fit on the wall. To do this, I used a Quick Sort algorithm to sort the picture data from highest picture value to lowest picture value. Then I iterated over the sorted data, adding each picture to the wall if it fit in the remaining wall space. The results are outputted to a file. 

## Custom Algorithm
The Custom Algorithm's goal is to generate a faster solution than brute force while finding a solution with a higher value than most expensive first. To do this, I used a Quick Sort algorithm to sort the pictures by the ratio of the cost of each picture to the amount of space it takes up (with the highest ratio being first). Thus, a picture that costs $20 with a width of 5 units would be placed before a picture that costs $20 with a width of 10 units. After sorting the picture data, I used a recursive function (called findOptimalPlacement) to iterate through every picture, placing each picture on the wall if it fit, only ending if a solution that takes up all wall space is found. If such a solution isn't initally found, then the function backtracks and removes the last picture placed on the wall. It then tries to place subsequent pictures on the wall until all wall space is taken up. This process is repeated until a solution that takes up all wall space is found. In the case that no such solution exists, the program stores the solution that takes up the most wall space and uses that instead.

## Sample Input

## Sample Output
