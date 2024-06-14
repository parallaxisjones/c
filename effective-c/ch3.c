#include <stdio.h>

void swap(int *pa, int *pb) {
  int t = *pa;
  *pa = *pb;
  *pb = t;
}

int main(){
  int a = 21;
  int b = 17;

  printf("a = %d, b = %d\n",a, b);
  swap(&a, &b);

  printf("a = %d, b = %d\n",a, b);
  return 0;
}
