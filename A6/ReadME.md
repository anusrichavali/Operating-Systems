<h2>Assignment 6</h2>
<h3> Author: Anusri Chavali </h3>
<h3> Date Last Modified: 12/3 </h3>
<h3> The purpose of this code is to use multithreading to compute the individual cells fo a result matrix containing the product of matrices A and W. After computing one initial matrix, the rpogram continuously reallocates R as long as new A matrices are sent from the parent process, and then computes the added 64 cells using multithreading. </h3>
<p> Instructions: First, compile matrixmult_threaded.c by running gcc -D_REENTRANT -pthread -o matrixmult_threaded matrixmult_threaded.c. Then, compile matrixmult_multwa.c by running gcc matrixmult_multiwa.c -o matrixmult_multiwa. Sending any filenames as inputs for testing will require the form test/___. To run, use the command ./matrixmult_multiwa test/___ test/____. Then, you can keep sending filenames in the form test/___. When you don't want to send any more files, terminate using ctrl d. </p>
<p> Average runtime: For the command ./matrixmult_multiwa test/A1.txt test/W1.txt test/W2.txt, with inputs test/A2.txt, test/A3.txt and test/A1.txt, the average runtime is (0.027s + 0.029s + 0.035s)/3 = 0.03 seconds. </p>
<p> Valgrind detected no leaks, all heap blocks have been freed </p>
<p> Test Case 1 (one filename inputs, 2 child processes): For the command ./matrixmult_multiwa test/A1.txt test/W1.txt, with inputs test/A2.txt and test/A3.txt, the output of an array R should look like this: <br/>
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
<p> Sources: For this assignment, I used the source "Geeks for Geeks: Multiplication of Matrix Using Threads", which helped me implement the algorithm for computing product by threads and then joining them together </p>
