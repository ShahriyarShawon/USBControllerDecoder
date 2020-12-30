#include <stdio.h>

// for types like uint32_t and uint8_t
#include <stdint.h>
// for open and read functions
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// change this to the input device your controller has
// you can see this by running the command `cat /proc/bus/input/devices`
#define GAMEPAD "/dev/input/js0"

// these are defined in the kernel documentation
#define JS_EVENT_BUTTON 0x01 /* button pressed/released */
#define JS_EVENT_AXIS 0x02  /* joystick moved */
#define JS_EVENT_INIT 0x80  /* initial state of device */

// each event is a 64 bits and structured like this
struct js_event {
    uint32_t time;     /* event timestamp in milliseconds */
    int16_t value;    /* value */
    uint8_t type;      /* event type */
    uint8_t number;    /* axis/button number */
};
void main(){
    int fd = open (GAMEPAD, O_RDONLY); 
    struct js_event gamepad_event;
    while (1){
        read(fd, &gamepad_event, sizeof(gamepad_event));
        if (gamepad_event.type == JS_EVENT_BUTTON){
            printf("Button Pressed\n");
        }
        if (gamepad_event.type == JS_EVENT_AXIS){
            printf("Joystick Analoged\n");
        }
        printf("Axis/Button Number: %d\nValue: %d\n\n",gamepad_event.number, gamepad_event.value);
        if (gamepad_event.type == JS_EVENT_INIT){
            printf("Initiated\n");
        }
    }

}


