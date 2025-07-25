#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <poll.h>
#include <string.h>
#include <unistd.h>
#include <linux/input.h>
#include "I_input.h"

const int timeout_ms = -1;
struct input_event input_data;
struct pollfd fileds[1];

u_int8 Init_input(char *event_path){ 
  char path[20] = "/dev/input/";
  strcat(path, event_path); 
  fileds[0].fd = open(path, O_RDONLY|O_NONBLOCK);
  
  if(fileds[0].fd<0){
    printf("Error to read the input archive");
    return 0;
  }
  fileds[0].events = POLLIN;
  return 1;
}

u_int8 Read_input(I_input *inputs){
  int ret; 
  ret = poll(fileds, 1, timeout_ms); 
  if(ret>0){
    if(fileds[0].revents){
      for(u_int8 i = 1; i < 4; i++){
        ssize_t r = read(fileds[0].fd, &input_data, sizeof(input_data));
        if (r<0){
          printf("ERROR %d\n", (int)r);
          return 0;
        } else {
          if (i == 2){
            inputs->type = input_data.type;    
            inputs->code = input_data.code;
            inputs->value = input_data.value;
          }
        }
      }
    } else {
      printf("ERROR\n");
      return 0;
    }
  } else {
    printf("timeout\n");
    return 0;
  }
  
  

  return 1;
}
void Exit_input(){
  close(fileds[0].fd);
}

