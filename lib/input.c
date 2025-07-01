#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

struct termios origin_termios;

void raw_mode_off(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin_termios);
}

void raw_mode_on(){

  tcgetattr(STDIN_FILENO, &origin_termios);
  atexit(raw_mode_off);

  struct termios raw = origin_termios;

  raw.c_iflag &= ~(IXON | ICRNL);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);


  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}



int main(){

  raw_mode_on();
  
  char letter;
  

  while(read(STDIN_FILENO, &letter, 1) == 1 && letter != 'q'){
    if (iscntrl(letter)) {
      printf("%d \n", letter);
    } else {
      printf("%c / %d \n", letter, letter);
    }

  }
  

  return 0;
}
