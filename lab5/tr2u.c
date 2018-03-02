//ZihengXu 704756821
//lab5 tr2u.c 
//unbuffered
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


int main(int argc, const char* argv[]){  
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
  int j;


  for(i=0; i<lengthFrom; i++){
    for (int j = i+1; j < lengthFrom; j++)
    {
      if (from[i] == from[j])
      { 
        fprintf(stderr, "FROM has duplicate bytes.\n");
        exit(1);
      }
    }
  }

  lengthFrom = strlen(from);
  ssize_t read_result;
  char c;
  while(1){
    read_result = read(STDIN_FILENO, &c, 1);
    if(read_result < 0){
      fprintf(stderr, "Fail to input.\n");
      exit(1);
    }
    if(read_result == 0)
      break;

    size_t k;
    for (k=0; k<lengthFrom; k++){
      if(from[k]==c){
        c = to[k];
      }
    }
    read_result = write(STDOUT_FILENO, &c, 1);

    if(read_result < 0){
      fprintf(stderr, "Fail to output.\n");
      exit(1);
    }
  }
  return 0;
}
