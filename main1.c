#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char **argv){
  if(argc < 2){
    printf("Error,use %s <command>\n",argv[0]);
    return -1;  ``
  }
  return 0;
}