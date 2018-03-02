//ZihengXu 704756821
//Lab6
//readme.txt

1. $ wget http://web.cs.ucla.edu/classes/winter18/cs35L/assign/srt.tgz
	I downloaded 'Brian Allen's SRT implementation', 
	using 'wget' command. 
2. $ tar -xf srt.tgz
	And then I use -xf option to untar this tgz file.
3. $ make clean check
   I ran this command after I had changed main.c 
   and updated Makefile with '-lpthread' in 'LDLIBS'.
   This command gives me the following output:



[classgxu@lnxsrv07 ~/CS35L/lab6/srt]$ make clean check
rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o main.o main.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm -lpthread
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m45.258s
user	0m45.245s
sys		0m0.003s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m21.374s
user	0m42.472s
sys		0m0.002s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m11.332s
user	0m44.811s
sys		0m0.001s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m5.946s
user	0m46.080s
sys		0m0.002s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
done


	From the output, we can see that: 
	The real time decreases significantly as the number 
	of threads increases. However, the user time and the 
	sys time are relatively stable. 
	This indicates that using more threads does not 
	improve the algorithm itself here in this case, but 
	the parallelism does speed up the program in a sense 
	that the value of real time is roughly the user time 
	divided by number of threads.
	Also, the user time goes up a little bit as number of 
	threads increases, probably because creating more 
	threads contributes to those extra time cost.

	Organizing the variables was one of the main issues I 
	ran into, since I moved many variables from the main 
	function to global. Also, there was some pointer issues after compiling the program, but it works well 
	after some changes.


