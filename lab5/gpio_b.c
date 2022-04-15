#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <linux/gpio.h>

/* you may want to look at the contents of this file, to understand
 the various elements of the data structure shown in the code below */

int main(int argc, char *argv[])
{ 
    int fd0 = open("/dev/gpiochip0",O_RDWR); // open the file descriptor
    struct gpiochip_info cinfo;
    ioctl(fd0,GPIO_GET_CHIPINFO_IOCTL,&cinfo); // get the chip information
    fprintf(stdout, "GPIO chip 0: %s, \"%s\", %u lines\n", 
        cinfo.name, cinfo.label, cinfo.lines);

    struct gpiohandle_request req_pb; // push button
    struct gpiohandle_data event;
    struct gpiohandle_request req_GY; // Green and Yellow
    struct gpiohandle_data data_GY; // for data bit

    req_pb.lines = 1; //pin 11 push button
    req_pb.lineoffsets[0] = 11; //pin 11 push button

    req_pb.flags = GPIOHANDLE_REQUEST_INPUT;

    req_GY.lines = 3; // 1 pins in this handler    x
    req_GY.lineoffsets[0] = 4; //pin 4 - Green LED
    req_GY.lineoffsets[1] = 17; //pin 17 - Yellow LED
    req_GY.lineoffsets[2] = 27; //pin 27 - Red LED

    req_GY.flags = GPIOHANDLE_REQUEST_OUTPUT; // set them to be output

    ioctl(fd0, GPIO_GET_LINEHANDLE_IOCTL, &req_GY); // now get the line handler req_GY
    ioctl(fd0, GPIO_GET_LINEHANDLE_IOCTL, &req_pb); // now get the line handler req_GY

    data_GY.values[0] = 1; // set initial value of Green LED to High (ON)
    data_GY.values[1] = 0; // set initial value of Yellow LED to Low (Off)
    data_GY.values[2] = 0; // set initial value of Red LED to Low (Off)
    ioctl(req_GY.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data_GY); // output data bits
    
    usleep(1000000);

    while(1){
        ioctl(fd0, GPIO_GET_LINEHANDLE_IOCTL, &req_pb); // now get the line handler req_GY
        ioctl(req_pb.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &event); // output data bits
        ioctl(fd0, GPIO_GET_LINEHANDLE_IOCTL, &req_GY); // now get the line handler req_GY 
        if(event.values[0]==1){
            data_GY.values[2] = 1; // toggle
        }else{
            data_GY.values[2] = 0; // toggle
        }
        data_GY.values[0] = !data_GY.values[0]; // toggle
        data_GY.values[1] = !data_GY.values[1]; // toggle
        ioctl(req_GY.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data_GY); // output data bits
        usleep(100000); //sleep for 1 second
        data_GY.values[2] = 0; // toggle
        ioctl(req_GY.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data_GY); // output data bits
    }
    close(req_pb.fd); // release line
    close(req_GY.fd); // release line
    close(fd0); // close the file
    exit(EXIT_SUCCESS);

}//main 
