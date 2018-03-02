//ZihengXu 704756821
//lab5 tr2b.c
//buffered
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(int argc, char* argv[])
{
	const char* from, * to;
	int i;
	if(argc != 3){
		fprintf(stderr, "The number of arguments must be 2.\n");
		exit(1);
	}
	from = argv[1];
	to = argv[2];
	int lengthFrom = strlen(from);
	int lengthTo = strlen(to);
	if(lengthFrom == 0 || lengthTo == 0){
		fprintf(stderr, "Length of the operand cannot be 0.\n");
		exit(1);
	}
	if(lengthFrom != lengthTo){
		fprintf(stderr, "Length of two operands must be same.\n");
		exit(1);
	}
	for(i=0; i<lengthFrom; i++){
		for (int j = i+1; j < lengthFrom; j++){
			if (from[i] == from[j])
			{ 
				fprintf(stderr, "FROM has duplicate bytes.\n");
				exit(1);
			}
		}
	}

	char c = getchar();
	int did_find = 0;
	while(c != EOF)
	{
		for(i = 0; i < lengthFrom; i++){
			if(c == from[i]){
				putchar(to[i]);
				did_find = 1;
				break;
			}
			else
			{
				did_find = 0;
			}
		}
		if(!did_find){
			putchar(c);
		}
		c = getchar();
	}
	return 0;
}
