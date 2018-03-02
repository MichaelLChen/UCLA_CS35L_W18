//ZihengXu 704756821
//lab5 sfrobu.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>


int num_cmps = 0;
int cmp(const void* in1, const void* in2)
{
  const char* a = *(const char**)in1;
  const char* b = *(const char**)in2;
  num_cmps++;
  while(1){
  	if(*a == ' ' && *b == ' ') { return 0; }
	else if (*a == ' ' || ((*a^42) < (*b^42))) { return -1; }
	else if (*b == ' ' || ((*a^42) > (*b^42))) { return 1; }
	a++;
	b++;
  }
}

void check_read(ssize_t read_stat)
{
  if(read_stat < 0)
  {
	fprintf(stderr, "Fail to read.");
	exit(1);
  }
}

int main(void)
{
  char **str_ptr;
  char *arr_f;
  size_t itr_w = 0;
  struct stat fileStat;
  size_t i;
  size_t j;
  if(fstat(0,&fileStat) < 0) 
  {
	fprintf(stderr, "Status info error about this file."); 
	exit(1);
  }
  if(S_ISREG(fileStat.st_mode))
  {
	arr_f = (char*)malloc(fileStat.st_size * sizeof(char));
	int ptr_c = 0;
	ssize_t _stat = read(0, arr_f, fileStat.st_size);
	int count = 1;
	if(_stat > 0)
	{
	  for(i = 0; i < fileStat.st_size; i+=count)
	  {
		count = 1;
		if(i == fileStat.st_size - 1){
		  arr_f[i] = ' ';
		}
		if(arr_f[i] == ' ')
		{
		  for(j = i; arr_f[j] != ' '; j++)
		  {
			count++;
		  }
		  ptr_c++;
		}
	  }
	}
	str_ptr = (char**)malloc(ptr_c * sizeof(char*));
	int flag = 0;
	for(i = 0; i < fileStat.st_size; i++)
	{
	  if(flag == 0 && arr_f[i] != ' ')
	  {
		str_ptr[itr_w] = &arr_f[i];
		itr_w++;
		flag = 1;
	  }
	  else if(flag == 1 && arr_f[i] == ' ')
	  {
		flag = 0;
	  }
	}
  }else{
	str_ptr = (char**)malloc(sizeof(char*));
  }

  char* str;
  str = (char*)malloc(sizeof(char));
  char cur[1];
  ssize_t cur_stat = read(0, cur, 1);
  if(cur_stat < 0)
  {
	fprintf(stderr, "Fail to read.");
	exit(1);
  }
  char nxt[1];
  ssize_t nxt_stat = read(0, nxt, 1);
  if(nxt_stat < 0)
  {
	fprintf(stderr, "Fail to read.");
	exit(1);
  }
  int itr_l = 0;
  while(cur_stat > 0)
  {
	str[itr_l] = cur[0]; 
	char* tmp = realloc(str, (itr_l+2)*sizeof(char));
	if(tmp != NULL)
	{
	  str = tmp;
	}
	else
	{
	  free(str);
	  fprintf(stderr, "Fail to allocate memory.");
	  exit(1);
	}

	if(cur[0] == ' ')
	{
	  str_ptr[itr_w] = str; 
	  char** anotherOne = realloc(str_ptr, (itr_w+2)*sizeof(char*));
	  if(anotherOne != NULL)
	  {
		str_ptr = anotherOne;
		itr_w++;
		str = NULL;
		str = (char*)malloc(sizeof(char));
		itr_l = -1; 
	  }
	  else
	  {
		free(str_ptr);
		fprintf(stderr, "Fail to allocate memory.");
		exit(1);
	  }
	}
	if(nxt_stat == 0 && cur[0] == ' ')
	{
	  break;
	}
	else if (cur[0] == ' ' && nxt[0] == ' ')
	{
	  while(cur[0] == ' ')
	  {
		cur_stat = read(0,cur,1);
		if(cur_stat < 0)
  		{
			fprintf(stderr, "Fail to read.");
			exit(1);
  		}
	  }
	  nxt_stat = read(0,nxt,1);
	  if(nxt_stat < 0)
	  {
		fprintf(stderr, "Fail to read.");
		exit(1);
  	  }
	  itr_l++;
	  continue;
	}
	else if(nxt_stat == 0)
	{
	  cur[0] = ' ';
	  itr_l++;
	  continue;
	}
	cur[0] = nxt[0];
	nxt_stat = read(0, nxt, 1);
	if(nxt_stat < 0)
  	{
		fprintf(stderr, "Fail to read.");
		exit(1);
  	}
	itr_l++;
  }
  qsort(str_ptr, itr_w, sizeof(char*), cmp);
  for(i = 0; i < itr_w; i++)
  {
	long str_ptrize = 0;
	for(j = 0; ;j++)
	{
	  str_ptrize++;
	  if(str_ptr[i][j] == ' ')
	  {
		break;
	  }
	}
	if(write(1,str_ptr[i], str_ptrize) == 0)
	{
	  fprintf(stderr, "Fail to write.");
	  exit(1);
	}
  }
  //fprintf(stderr, "Number of comparisons is: %i\n", num_cmps);
    free(str_ptr);
    exit(0);
 }
