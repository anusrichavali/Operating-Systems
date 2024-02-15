<h1> Assignment 2 </h1>
<h3> Author: Anusri Chavali </h3>
<h3> Date Last Modified: 09/24/2023 </h3>
<h3> Purpose: Uses parallel processing to compute the dot product of 2 square matrices with dimensions [8][8] </h3>
<p> 1. In this program, I repurposed some code from A1 in order to read the file input values into 8 by 8 matrices. I also repurposed some code from A1 to calculate the dot product of each row of A with the W matrix. </p>
<p> 2. A for loop is used to create 8 child processes, each which computes the dot product of one of the 8 rows of A and W matrix. Then, pipes are used to write the computed arrays from the child processes into the result matrix of parent process. </p>
<p> The runtime of the first process is 0.01 seconds. The runtime of the second and third process is 0.00 seconds. The average of these runtimes is (0.01 + 0.00 + 0.00)/3, which is 0.00333 seconds. </p>
<p> Test Case 1: After compiling, run the following command: ./matrixmult_p test/A.txt test/W.txt. This tests a successful output for 2 located files containing appropriate values.  The result should be: <br/>
Result of test/A.txt*test/W.txt = [  <br/>
11 7 0 0 0 11 0 0   <br/>
21 13 0 0 0 21 0 0   <br/>
16 10 0 0 0 16 0 0   <br/>
16 10 0 0 0 16 0 0   <br/>
21 13 0 0 0 21 0 0   <br/>
26 16 0 0 0 26 0 0   <br/>
26 16 0 0 0 26 0 0   <br/>
16 10 0 0 0 16 0 0   <br/>
]  <br/>
</p> Test Case 2: In this case, A2 is empty. After compiling, run the followign command: ./matrixmult_p test/A2.txt test/W.txt. This demonstrates the successful output for computation using empty file. The result should be: <br/>
Result of test/A2.txt*test/W.txt = [ <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/> 
]  <br/>
</p>
<p> Test Case 3: In this case, A3 is not an existing file. After compiling, run the following command. The output should be: error: cannot open file test/A3.txt 
Terminating, exit code 1. </p>
<p> Test Case 4: In this case, not enough columns or rows are provided in A. After compiling, run the command: ./matrixmult_p test/A4.txt test/W.txt. The computation should be successful as the array is full of 0s where values from file are not provided. The output should be: <br/>
Result of test/A4.txt*test/W.txt = [  <br/>
5 3 0 0 0 5 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
0 0 0 0 0 0 0 0   <br/>
]  <br/>
Runtime 0.00 seconds  <br/>
</p>
<p> Test Case 5: In this case, not enough arguments are provided. After compiling, run the command ./matrixmult_p test/A4.txt. The output should be: error: expecting exactly 2 files as input
Terminating, exit code 1. </p>
<p> Test Case 6: In this case, too many arguments are provided. After compiling, run the command ./matrixmult_p test/A4.txt test/W.txt test/A.txt. The output should be: error: expecting exactly 2 files as input
Terminating, exit code 1. </p>
