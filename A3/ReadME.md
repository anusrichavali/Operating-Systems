<h2>Assignment 3</h2>
<h3> Author: Anusri Chavali </h3>
<h3> Date Last Modified: 10/9 </h3>
<p> Instructions: First, compile matrixmult_parallel.c by navigating to A3 directory, then running, gcc matrixmult_parallel.c -o matrixmult_parallel. Then, compile matrixmult_multiw by running gcc matrixmult_multiw.c -o matrixmult_multiw. Both are done in A3 directory, since a copy of the parallel c program has been made in A3. </p>
<p> Runtime: After running on the ssame test case (1) 3 times, I got 0.02, 0.03, and 0.01 second runtimes. The average of this is (0.02 + 0.03 + 0.01)/3 = 0.02 second average runtime. </P>
<p> Test Case 1: After compiling matrixmult_multiw.c, run the command ./matrixmult_multiw test/A.txt test/W1.txt test/W2.txt test/W3.txt. The expected output is 3 out files and 3 err files, 1 of each for each pid. cat (err file) should be empty for all 3. The cat (out file) for command 1: <br/>
Starting command 1: child 30817 of parent 30816 <br/>
test/A.txt = [ <br/>
1 0 1 1 0 0 0 0 <br/>
2 1 1 1 0 0 0 0 <br/>
1 1 1 1 0 0 0 0 <br/>
1 1 1 1 0 0 0 0 <br/>
1 2 1 1 0 0 0 0 <br/>
1 3 1 1 0 0 0 0 <br/>
0 4 1 1 0 0 0 0 <br/>
1 1 1 1 0 0 0 0 <br/>
]<br/>
test/W1.txt = [<br/>
1 3 4 5 1 0 0 0 <br/>
2 4 5 0 0 0 0 0 <br/>
1 1 5 0 0 0 0 0 <br/>
1 1 5 0 0 0 0 0 <br/>
1 1 5 0 0 0 0 0 <br/>
1 1 5 0 0 0 0 0 <br/>
1 1 5 0 0 0 0 0 <br/>
1 1 5 0 0 0 0 0 <br/>
]<br/>
R = [<br/>
3 5 14 5 1 0 0 0 <br/>
6 12 23 10 2 0 0 0 <br/>
5 9 19 5 1 0 0 0 <br/>
5 9 19 5 1 0 0 0 <br/>
7 13 24 5 1 0 0 0 <br/>
9 17 29 5 1 0 0 0 <br/>
10 18 30 0 0 0 0 0 <br/>
5 9 19 5 1 0 0 0 <br/>
]<br/>
Finished child 30817 of parent 30816<br/>
Exited with exitcode = 0<br/>

cat (out) for command 2: <br/>
Starting command 2: child 30818 of parent 30816 <br/>
test/A.txt = [<br/>
1 0 1 1 0 0 0 0 <br/>
2 1 1 1 0 0 0 0 <br/>
1 1 1 1 0 0 0 0 <br/>
1 1 1 1 0 0 0 0 <br/>
1 2 1 1 0 0 0 0 <br/>
1 3 1 1 0 0 0 0 <br/>
0 4 1 1 0 0 0 0 <br/>
1 1 1 1 0 0 0 0 <br/>
]<br/>
test/W2.txt = [<br/>
10 3 4 5 1 0 0 0 <br/>
20 4 5 0 0 0 0 0 <br/>
10 1 5 0 0 0 0 0 <br/>
10 0 0 0 0 0 0 0 <br/>
20 0 0 0 0 0 0 0 <br/>
20 0 0 0 0 0 0 0 <br/>
20 0 0 0 0 0 0 0 <br/>
20 0 0 0 0 0 0 0 <br/>
]<br/>
R = [<br/>
30 4 9 5 1 0 0 0 <br/>
60 11 18 10 2 0 0 0 <br/>
50 8 14 5 1 0 0 0 <br/>
50 8 14 5 1 0 0 0 <br/>
70 12 19 5 1 0 0 0 <br/>
90 16 24 5 1 0 0 0 <br/>
100 17 25 0 0 0 0 0 <br/>
50 8 14 5 1 0 0 0 <br/>
]<br/>
Finished child 30818 of parent 30816<br/>
Exited with exitcode = 0<br/>

cat (out) for command 3:<br/>
Starting command 3: child 30819 of parent 30816<br/>
test/A.txt = [<br/>
1 0 1 1 0 0 0 0 <br/>
2 1 1 1 0 0 0 0 <br/>
1 1 1 1 0 0 0 0 <br/>
1 1 1 1 0 0 0 0 <br/>
1 2 1 1 0 0 0 0 <br/>
1 3 1 1 0 0 0 0 <br/>
0 4 1 1 0 0 0 0 <br/>
1 1 1 1 0 0 0 0 <br/>
]<br/>
test/W3.txt = [<br/>
1 3 4 5 1 0 0 0 <br/>
2 4 5 2 2 0 0 0 <br/>
1 1 5 11 12 0 0 0 <br/>
1 1 5 11 12 0 0 0 <br/>
1 1 5 11 12 0 0 0 <br/>
1 1 5 11 12 0 0 0 <br/>
1 1 5 11 12 0 0 0 <br/>
1 1 5 11 12 0 0 0 <br/>
]<br/>
R = [<br/>
3 5 14 27 25 0 0 0 <br/>
6 12 23 34 28 0 0 0 <br/>
5 9 19 29 27 0 0 0 <br/>
5 9 19 29 27 0 0 0 <br/>
7 13 24 31 29 0 0 0 <br/>
9 17 29 33 31 0 0 0 <br/>
10 18 30 30 32 0 0 0 <br/>
5 9 19 29 27 0 0 0 <br/>
]<br/>
Finished child 30819 of parent 30816<br/>
Exited with exitcode = 0<br/>

<p> Test Case 2 (Non-existent file): After compiling, run the command ./matrixmult_multiw test/A.txt test/B.txt. B.txt does not exist. The expected outcome is two files, one out file and one err file. The out file should have an output such as: Starting command 1: child 31088 of parent 31087. The err file should have an output such as: error: cannot open file test/B.txt 
Terminating, exit code 1.
Killed with signal 256 </p>

<p> Test Case 3 (Not enough inputs): After compiling, run the command ./matrixmult_multiw test/A.txt. Also, run the command ./matrixmult_multiw. The outcome in both cases is that "Needs at least 1 input for W matrix." is printed to stderr in the terminal. No output files are generated. </P>