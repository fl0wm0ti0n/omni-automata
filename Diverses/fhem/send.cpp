/*
 Usage for Elro 440: ./send <systemCode> <unitCode> <command>
 Usage for Intertechno: ./send <houseCode> <groupCode> <deviceCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{  
  /*
   output PIN is hardcoded for testing purposes
   see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
   for pin mapping of the raspberry pi GPIO connector
   */
  int PIN = 0;
  
  if (wiringPiSetup () == -1) return 1;
  RCSwitch mySwitch = RCSwitch();
  mySwitch.enableTransmit(PIN);
  
  if (argc==5)   // find out whether command style intertechno
  {
    char* houseCode = argv[1];
    int group = atoi(argv[2]);
    int device = atoi(argv[3]);
    int command  = atoi(argv[4]);
    printf("sending Intertechno format: houseCode[%c] group[%i] device[%i] command[%i]\n", houseCode[0], group, device, command);
    switch(command) {
    case 1:
        mySwitch.switchOn(houseCode[0], group, device);
        break;
    case 0:
        mySwitch.switchOff(houseCode[0], group, device);
        break;
    default:
        printf("command[%i] is unsupported\n", command);
        return -1;
    }
  }
  else if(argc==4)  // type elro440 controller
  {
    char* systemCode = argv[1]; 
    int unitCode = atoi(argv[2]);
    int command  = atoi(argv[3]);
    printf("sending Elro440 format: systemCode[%s] unitCode[%i] command[%i]\n", systemCode, unitCode, command);
    switch(command) {
        case 1:
            mySwitch.switchOn(systemCode, unitCode);
            break;
        case 0:
            mySwitch.switchOff(systemCode, unitCode);
            break;
        default:
            printf("command[%i] is unsupported\n", command);
            return -1;
    }
  }
  else
  {
    printf(" Usage for Elro 440: ./send <systemCode> <unitCode> <command>\n");
    printf(" Usage for Intertechno: ./send <houseCode> <groupCode> <deviceCode> <command>\n");
    printf(" Command is 0 for OFF and 1 for ON\n");
  }
  
  return 0;
}
