<h2>Assignment 5</h2>
<h3> Author: Anusri Chavali </h3>
<h3> Date Last Modified: 11/19 </h3>
<h3> The purpose of this code is to use pipes and memory allocation to continuously send stdin inputs to a child process from the parent, and print a result array storing the computation of each A matrix sent through the pipe and the child's delegated W matrix. </h3>
<p> Instructions: First, compile matrixmult_parallel.c by running gcc matrixmult_parallel.c -o matrixmult_parallel. Then, compile matrixmult_multwa.c by running gcc matrixmult_multiwa.c -o matrixmult_multiwa. Sending any filenames as inputs for testing will require the form test/___. </p>
<p> Average runtime: For the command ./matrixmult_multiwa test/A1.txt test/W1.txt test/W2.txt, with inputs test/A2.txt and test/A3.txt, the average runtime is (0.008s + 0.015s + 0.007s)/3 = 0.01 seconds. </p>
<p> Valgrind detected no leaks, all heap blocks have been freed </p>
<p> Test Case 1 (two filename inputs, 2 child processes): For the command ./matrixmult_multiwa test/A1.txt test/W1.txt test/W2.txt, with inputs test/A2.txt and test/A3.txt, the output of an array R should look like this: <br/>
test/A1.txt x test/W1.txt <br/>
test/A2.txt x test/W1.txt <br/>
test/A3.txt x test/W1.txt <br/>
R = [ <br/> 
110 190 390 50 10 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
70 150 190 50 10 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
11 19 39 5 1 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
]<br/>
Finished child 25716 of parent 25715 <br/>
Exited with exitcode = 0 <br/>
The result matrix has 3 computations, A1 x W1, A2 x W1, and A3 x W1. </p>
<p> Test Case 2 (Invalid input): For the command, test/A1.txt test/W1.txt with the input "test". "test" is not a valid filename; the out file has the line: test/A1.txt x test/W1.txt, and the err file has the line: can't open file. Killed with signal 1 -- This is the output because the first computation works, but can not open the input file. </p>
