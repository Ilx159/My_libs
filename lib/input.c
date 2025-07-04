#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "input.h"

struct termios origin_termios;

char ver = 0;

void raw_mode_off(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin_termios);
  ver = 0;
}

void raw_mode_on(){

  tcgetattr(STDIN_FILENO, &origin_termios);
  atexit(raw_mode_off);

  struct termios raw = origin_termios;

  raw.c_iflag &= ~(IXON | ICRNL);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
  ver = 1;
  
} 

char input(){
  char key;

  if(!ver){
    printf("raw_mode is disable");
    return -1;
  }
  if(read(STDIN_FILENO, &key, 1) == 1)
    return key;
}
