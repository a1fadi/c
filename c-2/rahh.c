#include <stdio.h>

int main() {
  int a = 100;
  printf("%d\n", a);
  int *p = &a;
  printf("%p\n",(void*)p);
  ++(*p++);
  printf("%p\n",(void*)p);
  printf("%d\n",a);
  return 0;
}