#include <stdio.h>
#include "I_input.h"

int main(int argc, char *argv[]){

  I_input My_input;
  Init_input("event4");
  while (My_input.code != 16 && Read_input(&My_input));
  Exit_input();
  return 0;
}
