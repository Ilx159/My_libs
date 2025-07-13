#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <linux/input.h>

typedef struct{
  unsigned short type;
  unsigned short code;
  unsigned int value;

}My_input_event;

const int timeout_ms = -1;

int main(int argc, char *argv[]){
  
  My_input_event inputs[3];

  struct input_event input_data;
  struct pollfd fileds[1];
  int ret;
  int contagens = 0;

  FILE* key_input;
  
  fileds[0].fd = open("/dev/input/event4", O_RDONLY|O_NONBLOCK);
  
  if(fileds[0].fd<0){
    printf("Error to read the input archive");
    return 1;
  }
  
  fileds[0].events = POLLIN;
  
  while(1){
    
    ret = poll(fileds, 1, timeout_ms);
    
    if(ret>0){
      if(fileds[0].revents){
        ssize_t r = read(fileds[0].fd, &input_data, sizeof(input_data));
        if (r<0){
          printf("ERROR %d\n", (int)r);
          return 1;
        } else {
          if(contagens < 3) contagens = 0;
          inputs[contagens].type = input_data.type;    
          inputs[contagens].code = input_data.code;
          inputs[contagens].value = input_data.value;

          printf("\n\n%u / %u / %u", inputs[contagens].type, inputs[contagens].code, inputs[contagens].value);
          contagens++;
        }
      } else {
        printf("ERROR\n");
      }
    } else {
      printf("timeout\n");
    }
  }
  close(fileds[0].fd);

  return 0;
}
