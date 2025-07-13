#define I_INPUT_H
#ifdef I_INPUT_H

typedef unsigned char u_int8;

typedef struct{
  unsigned short type;
  unsigned short code;
  unsigned int value;
}I_input;

u_int8 Init_input(char *event_path);
u_int8 Read_input(I_input inputs[3]);
void Exit_input();


#endif
