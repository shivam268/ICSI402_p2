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
#include "constants.h"
#include "globals.h"
#include "prototypes.h"



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
///											    ///
///		              MAIN METHOD STARTS		         ///
///								     			    ///
///////////////////////////////////////////////////////////////



// to run program user must types: p2 flag inputfile

int main(int args, char *argv[])
{
  
  
  
    // checks for number of argument entry
    if(args != COMMANDENTRY){ // if it's not 3 then exit the program
        printf("ERROR: Command entries are wrong \n"); // print error
        exit(1); // exit program
    }

    
    // open input file for read
  inputFile = fopen ( argv[NUMTWO] , "r" ); // open input file for read
  if (inputFile==NULL) { // if the open was unsuccessful
      fputs ("File error",stderr); exit (1); // print an error and exit
  }
    
    
    // set array to ZERO
    
    for(i = 0; i < ARRAYSIZE; i++){ // for loop to run through the array
        checkArrayData[i] = 0; // set each index value to 0
        checkArrayControl[i] = 0; // set each index value to 0
    }
    
    
    
    // we only need to error check fread once because there always be second byte followed by it
    
    while(fread ((void*)&bufferOne, NUMONE, NUMONE, inputFile) == 1){ // read until it reaches end of file-read first byte
          fread ((void*)&bufferTwo,NUMONE, NUMONE, inputFile);        // read second byte onto bufferTwo
        
        payLoad = 0; // initial payload set to 0
        
        // mask the 1st byte and store masked value as a payload
        // only use if it's a data packet
        payLoad = (int)bufferOne & maskAmount; // store masked value as an integer on payload
        
        packetId = (int)bufferTwo; // second byte holds packet id, so cast it in as an int
        
        identify(); // call indentify method will identify if it's a data or control packet
    }

    fclose (inputFile); // close file
    

    findHighest(); // call method to find highest control and data packets
    
    
    
    //figure out flag, if not identified then print out error and exit
    if(strcmp(argv[NUMONE],"-c") == 0){ // if flag is just for control packets
        printControlPacket(); // call method to print just information about control packets
        
    }else if(strcmp(argv[NUMONE],"-d") == 0){ // if flag is just for data packets
        printDataPacket(); // call method to print just information about data packets
        
    }
    else if(strcmp(argv[NUMONE],"-cd") == 0){ // fi flag is for both packet info
        printControlPacket(); // call method to print control packet info
        printDataPacket();    // and call method to print data packet info
    }
    else{ // if flag is not identified
        printf("Flag can't be identified \n"); // print message saying that
        exit(4); // and exit program
    }
    
    
  return 0;
}
///////////////////////////////////////////////////////////////
///									     		   ///
///			     MAIN METHOD ENDS	                  ///
///								     			  ///
//////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





    
        
        
        
        
        
        
        