/*
Parikh Shivam
ICSI 402
Assignment 2
UNIX ID: sp191221
*/

extern FILE *inputFile; // file pointer

extern unsigned char bufferOne; // unsigned character for first byte
extern unsigned char bufferTwo; // unsigned character for second byte

extern int i; // for loop incrementer
extern int packetId; // to hold packet id
extern size_t result; // hold size

extern int identityValue; // hold identity value 128 or 0

extern int isData; // set to 1 if there is at least 1
extern int isControl; // set to 1 if there is at least 1

extern int payLoad; // payload will be stored

extern int numControlPackets; // number of control packets
extern int numDataPackets;    // hold number of data packets

extern int highestData;    //store the highest data packet
extern int highestControl; //store the highest control packet

extern int largestPayLoad; //store largest payload size

extern unsigned char maskDefine; //mask value to define what kind of packet
extern unsigned char maskAmount; //mask value to get payload size


extern int checkArrayData[];     // array to track received data packets
extern int checkArrayControl[];  // array to track received control packets
            
        
        
        