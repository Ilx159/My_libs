#include <stdio.h>
#include "input.h"

int main(){

  char c = 0;

  raw_mode_on();

  while (c != 'q') {
    c = input();
    printf("%d\n\r", c);
    fflush(stdout);
  }

  return 0;
}
