/*
Parikh Shivam
ICSI 402
Assignment 2
UNIX ID: sp191221
*/

FILE *inputFile;

unsigned char bufferOne;
unsigned char bufferTwo;


int i = 0; // for loop incrementer
int packetId; // store packet id


int identityValue; // holds identity value 128 or 0

int isData = 0; // set to 1 if there is at least 1
int isControl = 0; // set to 1 if there is at least 1

int payLoad = 0; // store payload size

int numControlPackets = 0; // store number of control packets
int numDataPackets = 0;    // store number of data packets

int highestData = 0; // store highest data packet id
int highestControl = 0; // store highest control packet id

int largestPayLoad = 0; // store larget payload size

unsigned char maskDefine = 0x80; // mask value to know packet kind
unsigned char maskAmount = 0x7F; // mask value to know payload size


int checkArrayData[ARRAYSIZE];   // array to track received data packets
int checkArrayControl[ARRAYSIZE];// array to track received control packets
        
        
        
        
        