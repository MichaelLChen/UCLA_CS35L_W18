// ZihengXu 704756821
// Lab4 
// sfrob.c

#include<stdio.h>
#include<stdlib.h>

int cmp_frob(const void* p1, const void* p2){
	const char* ptr1 = *(const char**)p1;
	const char* ptr2 = *(const char**)p2;
	for(;; ptr1++, ptr2++){
		if (*ptr1 == ' ' && *ptr2 == ' ')
		{
			return 0;
		}
		if (*ptr1 == ' ' || ((*ptr1^42)<(*ptr2^42)))
		{
			return -1;
		}
		if (*ptr2 == ' ' || ((*ptr1^42)>(*ptr2^42)))
		{
			return 1;
		}
	}
}


int main()
{
	char* str;
	char** str_ptr;
	char cur;
	char cur_nxt;
	
	cur = getchar();
	if(ferror(stdin))
	{
		fprintf(stderr, "Fail to read.\n");
		exit(1);
	}
	cur_nxt = getchar();
	if(ferror(stdin))
	{
		fprintf(stderr, "Fail to read.\n");
		exit(1);
	}
	
	str = (char*)malloc(sizeof(char));
	str_ptr = (char**)malloc(sizeof(char*));

	int itr_alpha = 0;
	int itr = 0;

	while(cur != EOF && !ferror(stdin)){
		str[itr_alpha] = cur;
		char* reallosp = realloc(str, (itr_alpha+2)*sizeof(char));
		if (reallosp == NULL)
		{
		 	free(str);
		 	fprintf(stderr, "Fail to allocate memory.\n");
		 	exit(1);
		}else{
		 	str = reallosp;
		}
		if (cur == ' ')
		{
			str_ptr[itr] = str;
		 	char** allocsp = realloc(str_ptr,(itr+2)*sizeof(char*));
		 	if (allocsp == NULL)
		 	{
		 		free(str_ptr);
		 		fprintf(stderr, "Fail to allocate memory.\n");
		 		exit(1);
		 	}else{
		 		str_ptr = allocsp;
		 		itr += 1;
		 		str = NULL;
		 		str = (char*)malloc(sizeof(char));
		 		itr_alpha = -1;

		 	}
		 	
		 	if (cur_nxt == EOF) { break;}
		 	
		 	if (cur_nxt == ' ')
		 	{
		 		while (cur == ' '){
		 			cur = getchar();
		 			if(ferror(stdin)){
						fprintf(stderr, "Fail to read.\n");
						exit(1);
					}
		 		}
		 		cur_nxt = getchar();
		 		if(ferror(stdin)){
					fprintf(stderr, "Fail to read.\n");
					exit(1);
				}
				itr_alpha += 1;
				continue;
		 	}
		}
		if (cur_nxt == EOF)
		{
			cur = ' ';
			itr_alpha += 1;
			continue;
		}
		cur = cur_nxt;
		cur_nxt = getchar();
		if(ferror(stdin)){
			fprintf(stderr, "Fail to read.\n");
			exit(1);
		}
		itr_alpha += 1;

	}

	qsort(str_ptr,itr, sizeof(char*),cmp_frob);

	for (int i = 0; i < itr; i++)
	{
		for (int j = 0; ; j++)
		{
			if (putchar(str_ptr[i][j]) == EOF)
			{
				fprintf(stderr, "Reached the end of file.\n");
				exit(1);
			}
			if (str_ptr[i][j] == ' ') { break;}
		}
	}
	
	for (int i = 0; i < itr; i++)
	{
		free(str_ptr[i]);
	}
	free(str_ptr);


	return 0;
}
