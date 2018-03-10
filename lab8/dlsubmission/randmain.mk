CFLAGS = -O2 -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd

randlibsw.so:
	gcc $(CFLAGS) -fPIC -c randlibsw.c -o randlibsw.o
	gcc $(CFLAGS) -shared -o randlibsw.so randlibsw.o

randlibhw.so:
	gcc $(CFLAGS) -fPIC -c randlibhw.c -o randlibhw.o
	gcc $(CFLAGS) -shared -o randlibhw.so randlibhw.o

randmain:
	gcc $(CFLAGS) -c randcpuid.c -o randcpuid.o
	gcc $(CFLAGS) -c randmain.c -o randmain.o
	gcc $(CFLAGS) -ldl -Wl,-rpath=$(PWD) randmain.o randcpuid.o -o randmain
