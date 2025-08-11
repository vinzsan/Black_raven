#include <stdio.h>

void ubahNilai(int *nilai,int nilai_baru){
  *nilai = nilai_baru;
}

int main(){
  int nilai1  = 10;
  printf("%d\n",nilai1);
  ubahNilai(&nilai1,20);
  printf("%d",nilai1);
  return 0;
}