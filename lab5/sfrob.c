#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int frobcmp(char const* a, char const* b);
char decode(const char* c);
void checkAllocError(void* ptr);
int cmpWrapper(const void* a, const void* b);
int sfrob();

const char spaceByte = ' ';
const size_t INITIAL_ARR_SIZE = 100;


int main(){
  sfrob();
  return 0;
}


int sfrob(){
  
  char** buffer;
  char* currentStr;
  char cur;
  size_t size_str, size_line, count_str, count_line;
  int count_file=0;
  int isEndOfFile;
  int (*cmp) (const void*, const void*);
  cmp = &cmpWrapper;

  size_str = INITIAL_ARR_SIZE;
  size_line = INITIAL_ARR_SIZE;
  count_str = 0;
  count_line = 0;

  cur = getchar();
  if(ferror(stdin)){
      fprintf(stderr, "Fail to read stdin");
      exit(1);
  }
  if(cur == EOF)
    return 0;
  else
    isEndOfFile=0;

  currentStr = (char*) malloc(size_str * sizeof(char));
  checkAllocError(currentStr);

  buffer = (char**) malloc(size_line * sizeof(char*));
  checkAllocError(buffer);

  while(!isEndOfFile){
    if(count_str >= size_str){

      size_str = size_str * 2;
      currentStr = (char*)realloc(currentStr, size_str*sizeof(char));
      checkAllocError(currentStr);
    }
    currentStr[count_str] = cur;
    count_str++;
    count_file++;


    if(cur == spaceByte || cur == EOF){
      if(count_line >= size_line){

	size_line = 2 * size_line;
	buffer = (char**)realloc(buffer, size_line*sizeof(char*));
      }
      buffer[count_line] = currentStr;
      size_str = INITIAL_ARR_SIZE;
      count_str = 0;
      count_line++;
      currentStr = malloc(size_str*sizeof(char));
      checkAllocError(currentStr);
    }

    isEndOfFile=feof(stdin);
    if(!isEndOfFile){
      cur = getchar();
      if(ferror(stdin)){
	fprintf(stderr, "Fail to read stdin");
	exit(1);
      }
    }

  }


  qsort(buffer, count_line, sizeof(char*), cmp);

  size_t i, j;

  for (i=0; i< count_line; i++){
    char* outputLine = buffer[i];
    int j = 0;
    char c = outputLine[j];
    while(c!=spaceByte&&c!=EOF){
      putchar(c);
      if(ferror(stdin)){
	fprintf(stderr, "Fail to output");
	exit(1);
      }
      j++;
      c = outputLine[j];
    }
    if(j != 0)
      putchar(spaceByte);
    if(ferror(stdin)){
    	  fprintf(stderr, "Fail to output");
    	  exit(1);
    }
  }

  for(i = 0; i < count_line; i++){
    free(buffer[i]);
  }
  free(buffer);
  free(currentStr);
  return 0;
}

void checkAllocError(void* ptr){
  if(ptr == 0){
      fprintf(stderr, "Fail to create memory buffer");
      exit(1);
  }
}

int cmpWrapper(const void* a, const void* b)
{
  return frobcmp(*((const char**) a), *((const char**) b));
}

int frobcmp(char const* a, char const* b){
  for(;*a==*b;a++, b++){
    if(*a == spaceByte){
      return 0;
    }
  }
  if(*a == spaceByte)
    return -1;
  if(*b == spaceByte)
    return 1;
  return (decode(a)<decode(b) ? -1:1);
}

char decode (const char* c){
  return (*c)^42;
}

