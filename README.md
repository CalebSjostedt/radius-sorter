# Radius Sorter
POC using Merge and Insertion sort for covid "detection"



## File input
The input file (defaulted to input.txt) has a header line that is used to run the actual code
On the first line, the first two integers represent the X and Y coordinates of your location. The third integer represents the total number of X,Y coordinate pairs to be entered into the linked list. The fourth and fifth integers represent the queries of X,Y pairs in the linked list and the threshold for the merge sort algorithm.

The lines after the first are the inputted X,Y pairs and the queries. Since there is no gap between the X,Y pairs and queries, it is imperative that there are proper totals for both pairs and queries.

## Running the program
Run the program with clang and mingw using the ```gcc radiussort.c -lm``` command in cli. the ```-lm``` argument is passed to prevent an error with the math library.

The program will output a text file (defaulted to out.txt) with the input sorted by radius from your location coordinates followed by the results of the queries.
