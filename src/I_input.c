#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <poll.h>
#include <unistd.h>
#include <linux/input.h>
#include "I_input.h"

const int timeout_ms = -1;
struct input_event input_data;
struct pollfd fileds[1];

u_int8 Init_input(char *event_path){ 
   
  fileds[0].fd = open("/dev/input/event4", O_RDONLY|O_NONBLOCK);
  
  if(fileds[0].fd<0){
    printf("Error to read the input archive");
    return 1;
  }
  fileds[0].events = POLLIN;
}

u_int8 Read_input(I_input inputs[3]){
   
  int ret;
  static int i = 0;
 
  ret = poll(fileds, 1, timeout_ms);
    
  if(ret>0){
    if(fileds[0].revents){
      ssize_t r = read(fileds[0].fd, &input_data, sizeof(input_data));
      if (r<0){
        printf("ERROR %d\n", (int)r);
        return 0;
      } else {
        if(i < 3) i = 0;
        inputs[i].type = input_data.type;    
        inputs[i].code = input_data.code;
        inputs[i].value = input_data.value;

        printf("\n\n%u / %u / %u", inputs[i].type, inputs[i].code, inputs[i].value);
        i++;
      }
    } else {
      printf("ERROR\n");
      return 0;
    }
  } else {
    printf("timeout\n");
    return 0;
  }
  
  

  return i;
}
void Exit_input(){
  close(fileds[0].fd);
}

