/*
Parikh Shivam
ICSI 402
Assignment 2
UNIX ID: sp191221
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>  
#include "externs.h"
#include "constants.h"
#include "prototypes.h"

  /*
 identity method will decide whether the packet is data packet or control packet
 and skips relevent bytes if nessesary
*/

void identify(){ // takes no parameters
    
    
    identityValue = (int)bufferOne & maskDefine; //it will masked and it will give value to determine data or control packet
    
    if(identityValue == IDENTITY){ // control packet
        
        isControl = 1; // there is atleast one control packet
        
        numControlPackets++; // increment number of control packets
        
        checkMarkArrayControl(packetId); // check mark the array for received control packet
    }
    else{ // Data Packet -- Skip the payload
        
        numDataPackets++; // increment data packet counter
        
        fseek (inputFile , payLoad , SEEK_CUR); // skeep the paload size, masked in main function
        
        // find out highest payload
        if(payLoad > largestPayLoad){ // if new payload is larger than we alread had then update payload
            largestPayLoad = payLoad; // copy new largest payload
        }
        
        isData = 1; // there is atleast one data packet
        
        checkMarkArrayData(packetId); // check mark the array for recieved data packet
    }
    
    
    
}


//findHighest() will find the highest control packet and heighest data packet

void findHighest(){ // takes no parameters
    // for loop to run through the data array and match the value with 1, and store the highest
    for(i = 0; i < ARRAYSIZE; i++){ // runs 0-255 times
        if(checkArrayData[i] == 1){ // if the current location value is 1
            highestData = i;        // store that location, and the last time is gets modified it will have that value
        }
    }
    
    // for loop to run through the control array and match the value with 1, and store the highest
    for(i = 0; i < ARRAYSIZE; i++){   // runs 0-255 times
        if(checkArrayControl[i] == 1){// if the current location value is 1
            highestControl = i;       // store that location, and the last time is gets modified it will have that value
        }
    }
}

void printControlPacket(){   // takes no parameters
    int firstPrintCheck = 0; // check if it has printed anything previously
    int lowerLimit;          // this will hold lower limit for range printing
    int higherLimit;         // this will hold higher limit for range printing
    
    if(isControl == 1){ // if there is data packet then print otherwise print message saying there are none control packets
        printf("Information about control packets: \n"); // prints string
        printf("Number of packets =  %d\n", numControlPackets); //print number of control packets
        printf("Largest Packet ID = %d\n", highestControl);     //print largest packet id for control packets
        printf("Missing packet IDs: ");                         //print missing packet ids
        //print out missing packets from Data Packet array
        for(i = 0; i < highestControl+NUMONE; i++){ //loop runs heighest number of times
            if(checkArrayControl[i] == 0){       //if array value is 0, it check is there is a list
                if(checkArrayControl[i+NUMONE] == 0 && checkArrayControl[i+NUMTWO]==0){ // if there is a list
                    
                    lowerLimit = i; //set lower limit to starting location of that list
                    higherLimit = i + NUMTWO; // and ending location at 3rd element
                    i = higherLimit+NUMONE;   // change starting location for i.
                    // check if list is longer than 3 elements, if it is then find that location
                    while(checkArrayControl[higherLimit+NUMONE] != 1){
                        higherLimit++;     //increment the higher limit
                        i = higherLimit+NUMONE; // i gets moved one to start after end of list
                    }
                    
                    // if there is already a first id printed then it will print COMMA before printing any ids.
                    
                    if(firstPrintCheck == 1){ // checks if the first id is printed
                        printf(",");          // prints comma
                    }
                    printf(" %d", lowerLimit); // prints lower limit
                    printf("-%d", higherLimit); // prints - and higher limit
                    firstPrintCheck = 1; // check mark that first time is printed, if program gets here second times-NoProb
                    
                    
                }
                else{ // if there is no list then print the location alone
                    if(firstPrintCheck == 1){ // check if we are not printing first time
                        printf(", ");         // print COMMA
                    }
                    printf("%d", i);          // print the packet id
                    firstPrintCheck = 1;// check mark that first time is printed, if program gets here second times-NoProb
                }
                
            }
            
        }
        printf("\n\n\n"); // print extra new lines
    }
    else{ // if there is no control packets print a message saying that
        printf("The input file does not have any control packets. \n"); // print string for no packets
        printf("\n"); // new line
    }
    
    
}





void printDataPacket(){ // takes no parameters
    int firstPrintCheck = 0; //check mark if it has printed previously
    int lowerLimit;          //this will hold lower limit
    int higherLimit;         //this will hold higher limit
    
    if(isData == 1){ // if there is data packet then print otherwise print message saying there are none data packets
        printf("Information about data packets: \n");  // print string for information followed by it
        printf("Number of packets =  %d\n", numDataPackets); // print number of data packets
        printf("Largest Packet ID = %d\n", highestData); // print largest packet id
        printf("Largest Payload size = %d\n", largestPayLoad); // print largest payload size
        printf("Missing packet IDs: "); // string saying print largest packet ids.
    //print out missing packets from Data Packet array
    for(i = 0; i < highestData+NUMONE; i++){ //loop runs heighest number of times
        if(checkArrayData[i] == 0){       //if array value is 0, it check is there is a list
            if(checkArrayData[i+NUMONE] == 0 && checkArrayData[i+NUMTWO]==0){ // if there is a list
                
                lowerLimit = i; //set lower limit to starting location of that list
                higherLimit = i + NUMTWO; // and ending location at 3rd element
                i = higherLimit+NUMONE; // i gets moved one to start after end of list
                
                // check if list is longer than 3 elements, if it is then find that location
                while(checkArrayData[higherLimit+NUMONE] != 1){
                    higherLimit++;     //increment the higher limit
                    i = higherLimit+NUMONE; // i gets moved one to start after end of list
                }
                
                if(firstPrintCheck == 1){ // check if first id is printed or not
                    printf(","); // print COMMA
                }
                
                printf(" %d", lowerLimit); // print lower limit
                printf("-%d", higherLimit); // print - and higherlimit
                firstPrintCheck = 1; // check mark that first time is printed, if program gets here second times-NoProb
            }
            else{ // if there is no list then print the location alone
                if(firstPrintCheck == 1){ // check if first id is printed or not
                    printf(","); // print COMMA
                }
                printf(" %d", i); // print packet id
                firstPrintCheck = 1; // check mark that first time is printed, if program gets here second times-NoProb
            }
            
        }
        
    }
        printf("\n\n\n"); // print extra new lines
  }
    else{ // print if there is no data about data packets 
        printf("The input file does not have any data packets. \n"); // string saying there is no data packets
        printf("\n"); // new line
    }
    
    
}




// goto location on array and set that to 1, because we received that packet
void checkMarkArrayControl(int index){ // takes integer value which is index for an array as a parameter
    checkArrayControl[index] = 1;      // sets the index location value to 1
}

// goto location on array and set that to 1, because we received that packet
void checkMarkArrayData(int index){ // takes integer value which is index for an array as a parameter
    checkArrayData[index] = 1;      // sets the index location value to 1
}
        
        
        
        