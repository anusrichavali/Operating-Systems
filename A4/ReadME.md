<h1> Assignment 4 </h1>
<h3> Anusri Chavali </h3>
<p> In the code for A4, the structure has two loops. The first loop is to process the first line of input which calls the deep program. The second loop processes all subsequent lines of input, and parallely processes the multiplication of each line of input with the previous line's Result Sum. </p>
<p> To run the following code: run gcc matrixmult_parallel.c -o matrixmult_parallel and gcc matrixmult_multiw_deep.c -o matrixmult_multi_deep </p>
<p> Test Case 1: ./matrixmult_multi_deep test/A1.txt test/W1.txt test/W2.txt test/W3.txt <br/>
                test/W4.txt test/W5.txt test/W6.txt test/W7.txt <br/>
                test/W8.txt <br/>
prints: <br/>
Rsum = [ <br/>
71350 54770 54770 54770 54770 54770 54770 97080 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 <br/>
] <br/>
</p>
<p> Test Case 2 (Not enough files on first line): Run the command ./matrixmult_multi_deep test/A1.txt. Expected output is "Needs at least 1 input for W matrix". Should print directly to stderr since this is caught in parent process. </p>
<p> Test Case 3 (Invalid path on first line): Run ./matrixmult_multi_deep test/A5.txt test/W1.txt. 
"error: cannot open file test/A5.txt  Terminating, exit code 1." prints to PID.err. </p>
<p> Test Case 4 (invalid path in stdin): Run ./matrixmult_multi_deep test/A1.txt test/W2.txt, then input t in stdin. In PID.err, you should see error: cannot open file t. Terminating, exit code 1.Then, Rsum full of 0s should print to stdout. This is because tokens are processed within a while loop, and after that loop, Rsum is taken from the file and printed. However, Rsum will store only 0s if stdin is not valid, because Rsum is zeroed after every iteration. </p>
<> Valgrind: If you run, valgrind --leak-check=full ./matrixmult_multi_deep, you should see "in use at exit: 0 bytes in 0 blocks", "total heap usage: 0 allocs, 0 frees, 0 bytes allocated", and "All heap blocks were freed -- no leaks are possible"  </p>