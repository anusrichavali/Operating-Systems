<h1> Assignment 1 </h1>
<h2> Author: Anusri Chavali </h2>
<h2> Date Last Modified: 09/10/2023 </h2>
<p> Purpose: This program reads integers from file inputs into matrices and performs multiplication and addition operations on the matrices. </p>
<p> Test Case 1 (three files are correctly input, having varying amounts of values, rows, and columns): After compiling, run the following command: ./matrixmult test/A1.txt test/W1.txt test/B1.txt. Output should be: Result of A1*W1+B1 = { 111 191 391 51 11 }. Repeat w/ the following sets (A2, W2, B2) & (A3, W3, B3). The respective outcomes should be: Result of A2*W2+B2 = { 701 151 191 51 11 } and Result of A3*W3+B3 = { 11 19 39 55 55 }. </p>
<p> Test Case 2 (One file is empty): After compiling, run the following command: ./matrixmult test/A4.txt test/W3.txt test/B1.txt. The file A4.txt is empty; the array will be populated by 0s. The result should be: Result of A4*W3+B1 = { 1 1 1 1 1 }. Since A is populated by 0s, all the products of A4 * W3 will be 0, and all the 1s from B are added to 0s. </p>
<p> Test Case 3 (an invalid path is provided): After compiling, run the command: 
./matrixmult test/A4.txt test/W3.txt test/B6.txt. B6.txt does not exist, and the result should be: error: cannot open file B6.txt
Terminating, exit code 1. Another command to run for this case is: ./matrixmult test/A4.txt test/W3.txt 4, where 4 is an input. The output should be: error: cannot open file 4 
Terminating, exit code 1. </p>
<p> Test Case 4 (insufficient or extra arguments): After compiling, run the command: ./matrixmult test/A4.txt test/W3.txt test/B6.txt test/B4.txt. Also, run the command: ./matrixmult. The result for both should be: error: expecting exactly 3 files as input
Terminating, exit code 1. </p>
<p> Test Case 5 (W file has not enough rows or columns): After compiling, run ./matrixmult test/A1.txt test/W4.txt test/B2.txt. W4.txt does not have enough rows or columns. It should be filled with 0s previously in the program, so the result will be as follows: Result of A1*W4+B2 = { 11 21 31 41 11 }. This requires a specific test since this is the only 2D array in the program, and reading into it has more complexities. </p>
<p> Test Case 6 (A file has more rows than 1): After compiling, run ./matrixmult test/A5.txt test/W2.txt test/B2.txt. A5.txt has 2 rows, and the loop should only read the first row, even if it does not have enough columns. The result of this should be: Result of A5*W2+B2 = { 51 12 15 6 2 }. This is the result of a multiplication between A = [1, 2, 0], W = [[10, 3, 4, 5, 1], [20, 4, 5, 0, 0], [10, 1, 5, 0, 0]] plus B = [1, 1, 1, 1, 1]. We should test this since the other A files all have one row, and in our case we only want to read from the first row of the file. </p>