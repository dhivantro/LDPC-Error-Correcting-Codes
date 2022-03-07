#define _GNU_SOURCE    // needed for asprintf
// Software Recording Channel (SWRC) platform in C.
// Name      : swrcGP_Hamming
// Type      : main.
// Path      : 
// Dependency: modules/encoder/GP_HammingEncoder,modules/channel/GP_HammingChannel,modules/decoder/GP_HammingDecoder
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Mon Sep 13 16:37:37 2021
// Comment   : SWRC simulation for the first part of the group project simulating 
//             a Hamming code over an AWGN channel 

#include "swrcGP_Hamming.h"
#include <getopt.h>
#include <fcntl.h>
#include <sys/types.h> // needed for
#include <unistd.h>    // getpid()

///////////////////////////////////////////
// The main swrcGP_Hamming program
///////////////////////////////////////////
int main (int argc,char **argv) {
  char c;
  int i;
  // A cfgFile stores the configuration of a simulation as a string of bytes.
  // The bytes are stored in type uint8_vector
  // There is 1 cfgfile per module used in the simulation
  uint8_vector cfgFile[3];
  for (i=0;i<3;i++){
      SWRC_init_uint8_vector(&cfgFile[i]);
  }
  swrcGP_HammingStruct swrcGP_Hamming;
  initSwrcGP_HammingStruct(&swrcGP_Hamming);
  if (loadSwrcGP_HammingStruct(&swrcGP_Hamming,"swrcGP_Hamming.cfg")==1) { // load the swrcGP_Hamming.cfg file into the struct
    printf("Unable to load swrcGP_Hamming.cfg, resuming default configuration.\n");
  }
  // Process the command-line switches supplied by the user
  while ((c=getopt(argc,argv,"cp:rthsk0:1:2:3:"))!=EOF) {
    switch (c) {
    case '0':                                                  // process base module swrcGP_Hamming commands
      printf("whileSwitchCase swrcGP_Hamming module: swrcGP_Hamming. optarg=\"%s\"\n",optarg);
      processCommandSwrcGP_Hamming(&swrcGP_Hamming,&swrcGP_Hamming.signal,optarg);
      break;
    case '1':                                                 // process submodule GP_HammingEncoder commands
      printf("whileSwitchCase swrcGP_Hamming module: GP_HammingEncoder. optarg=\"%s\"\n",optarg);
      processCommandGP_HammingEncoder(&swrcGP_Hamming.GP_HammingEncoder,&swrcGP_Hamming.signal,optarg);
      break;
    case '2':                                                 // process submodule GP_HammingChannel commands
      printf("whileSwitchCase swrcGP_Hamming module: GP_HammingChannel. optarg=\"%s\"\n",optarg);
      processCommandGP_HammingChannel(&swrcGP_Hamming.GP_HammingChannel,&swrcGP_Hamming.signal,optarg);
      break;
    case '3':                                                 // process submodule GP_HammingDecoder commands
      printf("whileSwitchCase swrcGP_Hamming module: GP_HammingDecoder. optarg=\"%s\"\n",optarg);
      processCommandGP_HammingDecoder(&swrcGP_Hamming.GP_HammingDecoder,&swrcGP_Hamming.signal,optarg);
      break;
    case 'p': // print the structs
      //swrcGP_Hamming.printFlag=1;
      printf("swrcGP_Hamming: Printing struct.\n");
      if (SWRC_ifAnyChar(optarg,'0')) printSwrcGP_HammingStruct(&swrcGP_Hamming,"swrcGP_Hamming",0,0);
      if (SWRC_ifAnyChar(optarg,'1')) printGP_HammingEncoderStruct(&swrcGP_Hamming.GP_HammingEncoder,"swrcGP_Hamming->GP_HammingEncoder",1,0);
      if (SWRC_ifAnyChar(optarg,'2')) printGP_HammingChannelStruct(&swrcGP_Hamming.GP_HammingChannel,"swrcGP_Hamming->GP_HammingChannel",2,0);
      if (SWRC_ifAnyChar(optarg,'3')) printGP_HammingDecoderStruct(&swrcGP_Hamming.GP_HammingDecoder,"swrcGP_Hamming->GP_HammingDecoder",3,0);
      break;
    case 'c': // Precomputation for modules
      printf("swrcGP_Hamming: Precomputing mode.\n");
      precompSwrcGP_Hamming(&swrcGP_Hamming);
      break;
    case 't': // train the modules
      printf("swrcGP_Hamming: Training mode.\n");
      trainSwrcGP_Hamming(&swrcGP_Hamming);
      break;
    case 'r': // run the simulation modules
      printf("swrcGP_Hamming: Running simulation mode.\n");
      runSwrcGP_Hamming(&swrcGP_Hamming);
      break;
    case 'h': // print help for all modules
      printf("swrcGP_Hamming: Help.\n");
      helpCommandSwrcGP_Hamming(0);
      break;
    case 's': // save the config file
      printf("swrcGP_Hamming: Save.\n");
      saveSwrcGP_HammingStruct(&swrcGP_Hamming,"swrcGP_Hamming.cfg");
      break;
    case 'k': // check the parameters
      printf("swrcGP_Hamming: Check parameters.\n");
      checkParametersSwrcGP_Hamming(&swrcGP_Hamming);
      break;
    }
  }

  // Free the uint8Vectors 
  for (i=0;i<3;i++) {
      SWRC_free_uint8_vector(&cfgFile[i]);
  }
  freeSwrcGP_HammingStruct(&swrcGP_Hamming); 
  exit(0);
}
////////////////////////////////////////
// Functions for dealing with the struct
////////////////////////////////////////
// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initSwrcGP_HammingStruct (swrcGP_HammingStruct *swrcGP_Hamming) {
  uint8_t *tmp;
  int i;
  tmp=(uint8_t*)swrcGP_Hamming;
  for (i=0;i<sizeof(*swrcGP_Hamming);i++) tmp[i]=0; // zero out the entire structure avoid errors reported by valgrind.
// General housekeeping fields
  swrcGP_Hamming->startTime           = 0;
  swrcGP_Hamming->endTime             = 0;
  swrcGP_Hamming->runTime             = 0;
  swrcGP_Hamming->startTimeString[26] = ' ';
  swrcGP_Hamming->endTimeString[26]   = ' ';
  swrcGP_Hamming->CPID[99]            = ' ';
  swrcGP_Hamming->dumpEvery           = 3600;
// Fields for running the simulation
  swrcGP_Hamming->K                   = 0;
  swrcGP_Hamming->M                   = 0;
  swrcGP_Hamming->N                   = 0;
  swrcGP_Hamming->numberOfFrames      = 0;
  swrcGP_Hamming->numberOfFrameErrors = 0;
  swrcGP_Hamming->minNumberOfFrames   = 1000;
  swrcGP_Hamming->minNumberOfFrameErrors = 50;
  swrcGP_Hamming->maxNumberOfFrames   = 10000;
  swrcGP_Hamming->numberOfBits        = 0;
  swrcGP_Hamming->numberOfBitErrors   = 0;
  swrcGP_Hamming->BER                 = 0.0;
  swrcGP_Hamming->FER                 = 0.0;
  initSignalStruct(&swrcGP_Hamming->signal);

  //Initialize each submodule
  initGP_HammingEncoderStruct(&swrcGP_Hamming->GP_HammingEncoder);
  initGP_HammingChannelStruct(&swrcGP_Hamming->GP_HammingChannel);
  initGP_HammingDecoderStruct(&swrcGP_Hamming->GP_HammingDecoder);
  time(&swrcGP_Hamming->startTime);
}

// Frees up all the memory in the structure
void freeSwrcGP_HammingStruct (swrcGP_HammingStruct *swrcGP_Hamming) {
  //Free struct fields
  if (swrcGP_Hamming==NULL) {printf("swrcGP_Hamming=NULL in function freeSwrcGP_HammingStruct not free'ing\n");return;}
  int i;
  swrcGP_Hamming->startTime     =0;
  swrcGP_Hamming->endTime       =0;
  swrcGP_Hamming->runTime       =0;
  swrcGP_Hamming->startTimeString[26]=' ';
  swrcGP_Hamming->endTimeString[26]=' ';
  swrcGP_Hamming->CPID[99]      =' ';
  swrcGP_Hamming->dumpEvery     =3600;
  swrcGP_Hamming->K             =0;
  swrcGP_Hamming->M             =0;
  swrcGP_Hamming->N             =0;
  swrcGP_Hamming->numberOfFrames=0;
  swrcGP_Hamming->numberOfFrameErrors=0;
  swrcGP_Hamming->minNumberOfFrames=1000;
  swrcGP_Hamming->minNumberOfFrameErrors=50;
  swrcGP_Hamming->maxNumberOfFrames=10000;
  swrcGP_Hamming->numberOfBits  =0;
  swrcGP_Hamming->numberOfBitErrors=0;
  swrcGP_Hamming->BER           =0.0;
  swrcGP_Hamming->FER           =0.0;
  freeSignalStruct(&swrcGP_Hamming->signal);
  //free(swrcGP_Hamming);swrcGP_Hamming=NULL;

  //Free each submodule
  freeGP_HammingEncoderStruct(&swrcGP_Hamming->GP_HammingEncoder);
  freeGP_HammingChannelStruct(&swrcGP_Hamming->GP_HammingChannel);
  freeGP_HammingDecoderStruct(&swrcGP_Hamming->GP_HammingDecoder);
}

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printSwrcGP_HammingStruct (swrcGP_HammingStruct *swrcGP_Hamming, char *name, int index, int pre) {
  int i,j;
  char *preString,*name2;
  if (swrcGP_Hamming==NULL) {printf("%s%s=NULL\n",preString,name);return;}
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  printf("%s[--%d:%s--------\n",preString,index,name);
// General housekeeping fields
    printf("%s  time_t               %s->startTime=%lu\n",preString,name,swrcGP_Hamming->startTime);   // Print time_t startTime
    printf("%s  time_t               %s->endTime=%lu\n",preString,name,swrcGP_Hamming->endTime);       // Print time_t endTime
    printf("%s  time_t               %s->runTime=%lu\n",preString,name,swrcGP_Hamming->runTime);       // Print time_t runTime
    printf("%s  char                 %s->startTimeString[26]=%c\n",preString,name,swrcGP_Hamming->startTimeString[26]); // Print char startTimeString[26]
    printf("%s  char                 %s->endTimeString[26]=%c\n",preString,name,swrcGP_Hamming->endTimeString[26]); // Print char endTimeString[26]
    printf("%s  char                 %s->CPID[99]=%c\n",preString,name,swrcGP_Hamming->CPID[99]);      // Print char CPID[99]
    printf("%s  int                  %s->dumpEvery=%d\n",preString,name,swrcGP_Hamming->dumpEvery);    // Print int dumpEvery
// Fields for running the simulation
    printf("%s  int                  %s->K=%d\n",preString,name,swrcGP_Hamming->K);                    // Print int K
    printf("%s  int                  %s->M=%d\n",preString,name,swrcGP_Hamming->M);                    // Print int M
    printf("%s  int                  %s->N=%d\n",preString,name,swrcGP_Hamming->N);                    // Print int N
    printf("%s  int                  %s->numberOfFrames=%d\n",preString,name,swrcGP_Hamming->numberOfFrames); // Print int numberOfFrames
    printf("%s  int                  %s->numberOfFrameErrors=%d\n",preString,name,swrcGP_Hamming->numberOfFrameErrors); // Print int numberOfFrameErrors
    printf("%s  int                  %s->minNumberOfFrames=%d\n",preString,name,swrcGP_Hamming->minNumberOfFrames); // Print int minNumberOfFrames
    printf("%s  int                  %s->minNumberOfFrameErrors=%d\n",preString,name,swrcGP_Hamming->minNumberOfFrameErrors); // Print int minNumberOfFrameErrors
    printf("%s  int                  %s->maxNumberOfFrames=%d\n",preString,name,swrcGP_Hamming->maxNumberOfFrames); // Print int maxNumberOfFrames
    printf("%s  long int             %s->numberOfBits=%ld\n",preString,name,swrcGP_Hamming->numberOfBits); // Print long int numberOfBits
    printf("%s  int                  %s->numberOfBitErrors=%d\n",preString,name,swrcGP_Hamming->numberOfBitErrors); // Print int numberOfBitErrors
    printf("%s  double               %s->BER=%lf\n",preString,name,swrcGP_Hamming->BER);               // Print double BER
    printf("%s  double               %s->FER=%lf\n",preString,name,swrcGP_Hamming->FER);               // Print double FER
  printf("%s---%d:%s-------]\n",preString,index,name);
  free(preString);
}

// Plot function generates any plots associated with the 
// structure
void plotSwrcGP_HammingStruct (swrcGP_HammingStruct *swrcGP_Hamming, const char *filename) {
}

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packSwrcGP_HammingStruct (swrcGP_HammingStruct *swrcGP_Hamming, uint8_vector *cfgFile) {
  // Pack struct fields
  int i;
 //General housekeeping fields
  // Pack time_t startTime
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->startTime,1,sizeof(time_t),cfgFile);
  // Pack time_t endTime
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->endTime,1,sizeof(time_t),cfgFile);
  // Pack time_t runTime
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->runTime,1,sizeof(time_t),cfgFile);
  // Pack char startTimeString[26]
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->startTimeString[26],1,sizeof(char),cfgFile);
  // Pack char endTimeString[26]
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->endTimeString[26],1,sizeof(char),cfgFile);
  // Pack char CPID[99]
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->CPID[99],1,sizeof(char),cfgFile);
  // Pack int dumpEvery
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->dumpEvery,1,sizeof(int),cfgFile);
 //Fields for running the simulation
  // Pack int K
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->K,1,sizeof(int),cfgFile);
  // Pack int M
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->M,1,sizeof(int),cfgFile);
  // Pack int N
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->N,1,sizeof(int),cfgFile);
  // Pack int numberOfFrames
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->numberOfFrames,1,sizeof(int),cfgFile);
  // Pack int numberOfFrameErrors
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->numberOfFrameErrors,1,sizeof(int),cfgFile);
  // Pack int minNumberOfFrames
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->minNumberOfFrames,1,sizeof(int),cfgFile);
  // Pack int minNumberOfFrameErrors
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->minNumberOfFrameErrors,1,sizeof(int),cfgFile);
  // Pack int maxNumberOfFrames
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->maxNumberOfFrames,1,sizeof(int),cfgFile);
  // Pack long int numberOfBits
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->numberOfBits,1,sizeof(long int),cfgFile);
  // Pack int numberOfBitErrors
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->numberOfBitErrors,1,sizeof(int),cfgFile);
  // Pack double BER
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->BER,1,sizeof(double),cfgFile);
  // Pack double FER
  SWRC_packToUint8((uint8_t*)&swrcGP_Hamming->FER,1,sizeof(double),cfgFile);
  // signal
  SWRC_packSignalStruct(&swrcGP_Hamming->signal,cfgFile);

  // Pack Submodules
  packGP_HammingEncoderStruct(&swrcGP_Hamming->GP_HammingEncoder,&cfgFile[1]);
  packGP_HammingChannelStruct(&swrcGP_Hamming->GP_HammingChannel,&cfgFile[2]);
  packGP_HammingDecoderStruct(&swrcGP_Hamming->GP_HammingDecoder,&cfgFile[3]);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackSwrcGP_HammingStruct (swrcGP_HammingStruct *swrcGP_Hamming, uint8_vector *cfgFile) {
  // Unpack struct fields
  int i;
  freeSwrcGP_HammingStruct(swrcGP_Hamming);
// General housekeeping fields
  // Unpack time_t startTime
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->startTime,1,sizeof(time_t),cfgFile);
  // Unpack time_t endTime
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->endTime,1,sizeof(time_t),cfgFile);
  // Unpack time_t runTime
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->runTime,1,sizeof(time_t),cfgFile);
  // Unpack char startTimeString[26]
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->startTimeString[26],1,sizeof(char),cfgFile);
  // Unpack char endTimeString[26]
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->endTimeString[26],1,sizeof(char),cfgFile);
  // Unpack char CPID[99]
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->CPID[99],1,sizeof(char),cfgFile);
  // Unpack int dumpEvery
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->dumpEvery,1,sizeof(int),cfgFile);
// Fields for running the simulation
  // Unpack int K
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->K,1,sizeof(int),cfgFile);
  // Unpack int M
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->M,1,sizeof(int),cfgFile);
  // Unpack int N
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->N,1,sizeof(int),cfgFile);
  // Unpack int numberOfFrames
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->numberOfFrames,1,sizeof(int),cfgFile);
  // Unpack int numberOfFrameErrors
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->numberOfFrameErrors,1,sizeof(int),cfgFile);
  // Unpack int minNumberOfFrames
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->minNumberOfFrames,1,sizeof(int),cfgFile);
  // Unpack int minNumberOfFrameErrors
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->minNumberOfFrameErrors,1,sizeof(int),cfgFile);
  // Unpack int maxNumberOfFrames
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->maxNumberOfFrames,1,sizeof(int),cfgFile);
  // Unpack long int numberOfBits
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->numberOfBits,1,sizeof(long int),cfgFile);
  // Unpack int numberOfBitErrors
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->numberOfBitErrors,1,sizeof(int),cfgFile);
  // Unpack double BER
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->BER,1,sizeof(double),cfgFile);
  // Unpack double FER
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_Hamming->FER,1,sizeof(double),cfgFile);
  // signal
  SWRC_unpackSignalStruct(&swrcGP_Hamming->signal,cfgFile);

  // Unpack submodules
  unpackGP_HammingEncoderStruct(&swrcGP_Hamming->GP_HammingEncoder,&cfgFile[1]);
  unpackGP_HammingChannelStruct(&swrcGP_Hamming->GP_HammingChannel,&cfgFile[2]);
  unpackGP_HammingDecoderStruct(&swrcGP_Hamming->GP_HammingDecoder,&cfgFile[3]);
}

// Function for loading the struct
int loadSwrcGP_HammingStruct (swrcGP_HammingStruct *swrcGP_Hamming, char *filename) {
  int i;
  uint8_vector cfgFile[4];
  for (i=0;i<4;i++){SWRC_init_uint8_vector(&cfgFile[i]);}
  freeSwrcGP_HammingStruct(swrcGP_Hamming);
  long int startTime=SWRC_loaduint8_vector(cfgFile,4,"swrcGP_Hamming.cfg");
  if(startTime==1) { // no cfg file found
    return(1);
  }
  unpackSwrcGP_HammingStruct(swrcGP_Hamming,cfgFile);
  for (i=0;i<4;i++) {SWRC_free_uint8_vector(&cfgFile[i]);}
}

// Function for saving the struct
void saveSwrcGP_HammingStruct (swrcGP_HammingStruct *swrcGP_Hamming, char *filename) {
  int i;
  uint8_vector cfgFile[4];
  for (i=0;i<4;i++){SWRC_init_uint8_vector(&cfgFile[i]);}
  packSwrcGP_HammingStruct(swrcGP_Hamming,cfgFile);
  SWRC_saveuint8_vector(cfgFile,4,"swrcGP_Hamming.cfg",swrcGP_Hamming->startTime);
  for (i=0;i<4;i++) {SWRC_free_uint8_vector(&cfgFile[i]);}
}

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmSwrcGP_HammingStruct (swrcGP_HammingStruct *swrcGP_Hamming, char *arg) {
  int i;
  SWRC_removeSpaces(arg);
  // if (SWRC_readSingleArgumentFromString(arg,"startTime",&swrcGP_Hamming->startTime,"%lu")==1) {
  //   printf("startTime=%lu\n",swrcGP_Hamming->startTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"endTime",&swrcGP_Hamming->endTime,"%lu")==1) {
  //   printf("endTime=%lu\n",swrcGP_Hamming->endTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"runTime",&swrcGP_Hamming->runTime,"%lu")==1) {
  //   printf("runTime=%lu\n",swrcGP_Hamming->runTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"startTimeString[26]",&swrcGP_Hamming->startTimeString[26],"%c")==1) {
  //   printf("startTimeString[26]=%c\n",swrcGP_Hamming->startTimeString[26]);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"endTimeString[26]",&swrcGP_Hamming->endTimeString[26],"%c")==1) {
  //   printf("endTimeString[26]=%c\n",swrcGP_Hamming->endTimeString[26]);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"CPID[99]",&swrcGP_Hamming->CPID[99],"%c")==1) {
  //   printf("CPID[99]=%c\n",swrcGP_Hamming->CPID[99]);
  // }
   if (SWRC_readSingleArgumentFromString(arg,"dumpEvery",&swrcGP_Hamming->dumpEvery,"%d")==1) {
     printf("dumpEvery=%d\n",swrcGP_Hamming->dumpEvery);
   }
   if (SWRC_readSingleArgumentFromString(arg,"K",&swrcGP_Hamming->K,"%d")==1) {
     printf("K=%d\n",swrcGP_Hamming->K);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"M",&swrcGP_Hamming->M,"%d")==1) {
  //   printf("M=%d\n",swrcGP_Hamming->M);
  // }
   if (SWRC_readSingleArgumentFromString(arg,"N",&swrcGP_Hamming->N,"%d")==1) {
     printf("N=%d\n",swrcGP_Hamming->N);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfFrames",&swrcGP_Hamming->numberOfFrames,"%d")==1) {
  //   printf("numberOfFrames=%d\n",swrcGP_Hamming->numberOfFrames);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfFrameErrors",&swrcGP_Hamming->numberOfFrameErrors,"%d")==1) {
  //   printf("numberOfFrameErrors=%d\n",swrcGP_Hamming->numberOfFrameErrors);
  // }
   if (SWRC_readSingleArgumentFromString(arg,"minNumberOfFrames",&swrcGP_Hamming->minNumberOfFrames,"%d")==1) {
     printf("minNumberOfFrames=%d\n",swrcGP_Hamming->minNumberOfFrames);
   }
   if (SWRC_readSingleArgumentFromString(arg,"minNumberOfFrameErrors",&swrcGP_Hamming->minNumberOfFrameErrors,"%d")==1) {
     printf("minNumberOfFrameErrors=%d\n",swrcGP_Hamming->minNumberOfFrameErrors);
   }
   if (SWRC_readSingleArgumentFromString(arg,"maxNumberOfFrames",&swrcGP_Hamming->maxNumberOfFrames,"%d")==1) {
     printf("maxNumberOfFrames=%d\n",swrcGP_Hamming->maxNumberOfFrames);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfBits",&swrcGP_Hamming->numberOfBits,"%ld")==1) {
  //   printf("numberOfBits=%ld\n",swrcGP_Hamming->numberOfBits);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfBitErrors",&swrcGP_Hamming->numberOfBitErrors,"%d")==1) {
  //   printf("numberOfBitErrors=%d\n",swrcGP_Hamming->numberOfBitErrors);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"BER",&swrcGP_Hamming->BER,"%lf")==1) {
  //   printf("BER=%lf\n",swrcGP_Hamming->BER);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"FER",&swrcGP_Hamming->FER,"%lf")==1) {
  //   printf("FER=%lf\n",swrcGP_Hamming->FER);
  // }
  // setParmSignalStruct(&swrcGP_Hamming->signal, arg);
  if (*arg!='\0') {
    printf("swrcGP_Hamming module: Remaining unknown parms in arg list:%s\n Please correct and run again.\n",arg);exit(-1);
  }
}

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming, signalStruct *signal, const char *command) {
  char commandParameter[400];
  int i;
  printf("processCommandSwrcGP_Hamming:%s\n",command);
  for(i=0;i<400 && i<strlen(command);) {
    if (SWRC_matchCommand(command,"load",&i,commandParameter,400)==1) {
	loadSwrcGP_HammingStruct(swrcGP_Hamming,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"print",&i,commandParameter,400)==1) {
	printSwrcGP_HammingStruct(swrcGP_Hamming,"swrcGP_Hamming",0,0);
	continue;
    }

    if (SWRC_matchCommand(command,"setParm",&i,commandParameter,400)==1) {
	setParmSwrcGP_HammingStruct(swrcGP_Hamming,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"help",&i,commandParameter,400)==1) {
	helpCommandSwrcGP_Hamming(0);
	continue;
    }

    if (SWRC_matchCommand(command,"run",&i,commandParameter,400)==1) {
	generatePseudoRandomUserBitsSignal(&swrcGP_Hamming->signal,swrcGP_Hamming->K);
	continue;
    }

    if (SWRC_matchCommand(command,"printAllSignals",&i,commandParameter,400)==1) {
	printAllSignals(&swrcGP_Hamming->signal);
	continue;
    }

    if (SWRC_matchCommand(command,"saveSignalBinary",&i,commandParameter,400)==1) {
	saveSignalBinary_wrap(&swrcGP_Hamming->signal,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"loadSignalBinary",&i,commandParameter,400)==1) {
	loadSignalBinary_wrap(&swrcGP_Hamming->signal,commandParameter);
	continue;
    }

    printf("processCommandSwrcGP_Hamming: Unknown command:%s\n",&command[i]);
    break;
  }
}

// Provides instructions on the commands that this module is able to process.
void helpCommandSwrcGP_Hamming (int index) {
  printf("Commands recognized by %d:swrcGP_HammingStruct:\n",index);
  printf("  \"print();\"        : print the swrcGP_HammingStruct fields\n");
  printf("  \"setParm(arg);\"   : set the swrcGP_HammingStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
  helpCommandGP_HammingEncoder(1);
  helpCommandGP_HammingChannel(2);
  helpCommandGP_HammingDecoder(3);
}

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming) {
  int output=0;
  output+=checkParametersGP_HammingEncoder(&swrcGP_Hamming->GP_HammingEncoder);
  output+=checkParametersGP_HammingChannel(&swrcGP_Hamming->GP_HammingChannel);
  output+=checkParametersGP_HammingDecoder(&swrcGP_Hamming->GP_HammingDecoder);
  if (swrcGP_Hamming->M==0) {output++; printf("swrcGP_Hamming->M needed, but not set\n");}
  if (swrcGP_Hamming->K==0) {output++; printf("swrcGP_Hamming->K needed, but not set\n");}
  if (swrcGP_Hamming->N==0) {output++; printf("swrcGP_Hamming->N needed, but not set\n");}
  if (swrcGP_Hamming->N<swrcGP_Hamming->K || swrcGP_Hamming->N<swrcGP_Hamming->M) {output++; printf("N=%d must be bigger than K=%d and M=%d, but not set\n",swrcGP_Hamming->N,swrcGP_Hamming->K,swrcGP_Hamming->M);}  //Calculating M from N and K
  if (output==0) printf("All parameters check ok\n"); else printf("swrcGP_Hamming CheckParameters: %d parameters are not properly set\n",output);
  return(output);
}

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming) {
  time(&swrcGP_Hamming->startTime);
  time(&swrcGP_Hamming->endTime);
  strncpy(swrcGP_Hamming->startTimeString,ctime(&swrcGP_Hamming->startTime),24);
  
  //////////////////////////////////////////////////////////////////////////////////////////////
  swrcGP_Hamming->M=swrcGP_Hamming->N-swrcGP_Hamming->K;
  ///////////////////////////////////////////////////////////////////////
  /////////////////////////////////////
  swrcGP_Hamming->GP_HammingChannel.N = swrcGP_Hamming->N;
}

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming, char finishedFlag) {
  char hostname[90];
  if (finishedFlag!=' ') time(&swrcGP_Hamming->endTime);
  swrcGP_Hamming->runTime=swrcGP_Hamming->endTime-swrcGP_Hamming->startTime;
  strncpy(swrcGP_Hamming->endTimeString,ctime(&swrcGP_Hamming->endTime),24);
  gethostname(hostname,90);
  sprintf(swrcGP_Hamming->CPID,"%c%s_%d",finishedFlag,hostname,getpid());
}

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming) {
}

// Function called after training. Free allocated memory etc...
void posttrainSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming) {
}

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file. 
void trainSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming) {
  int i;
  int idum=1;SWRC_randomize(&idum);
  printf("In trainSwrcGP_Hamming\n");
  pretrainSwrcGP_Hamming(swrcGP_Hamming);
  pretrainGP_HammingEncoder(&swrcGP_Hamming->GP_HammingEncoder);
  pretrainGP_HammingChannel(&swrcGP_Hamming->GP_HammingChannel);
  pretrainGP_HammingDecoder(&swrcGP_Hamming->GP_HammingDecoder);
  pretrainSwrcGP_Hamming(swrcGP_Hamming);
  if (checkParametersSwrcGP_Hamming(swrcGP_Hamming)>0) {
    printf("Exiting swrcGP_Hamming\n");
    exit(-1);
  }
  while(((swrcGP_Hamming->GP_HammingEncoder.trainFlag&1)==0) || ((swrcGP_Hamming->GP_HammingChannel.trainFlag&1)==0) || ((swrcGP_Hamming->GP_HammingDecoder.trainFlag&1)==0)) {
    //////////////////////////////////
    // 0. generate the pseudorandom bit input
    //////////////////////////////////
    SWRC_printHeader("0. generatePseudoRandomUserBitsSignal");
    generatePseudoRandomUserBitsSignal(&swrcGP_Hamming->signal,swrcGP_Hamming->K);
    //////////////////////////////////
    // 1. train the GP_HammingEncoder module
    //////////////////////////////////
    SWRC_printHeader("1. GP_HammingEncoder");
    if (trainGP_HammingEncoder(&swrcGP_Hamming->GP_HammingEncoder,&swrcGP_Hamming->signal)==0)
      {freeSignalStruct(&swrcGP_Hamming->signal);continue;}
    //////////////////////////////////
    // 2. train the GP_HammingChannel module
    //////////////////////////////////
    SWRC_printHeader("2. GP_HammingChannel");
    if (trainGP_HammingChannel(&swrcGP_Hamming->GP_HammingChannel,&swrcGP_Hamming->signal)==0)
      {freeSignalStruct(&swrcGP_Hamming->signal);continue;}
    //////////////////////////////////
    // 3. train the GP_HammingDecoder module
    //////////////////////////////////
    SWRC_printHeader("3. GP_HammingDecoder");
    if (trainGP_HammingDecoder(&swrcGP_Hamming->GP_HammingDecoder,&swrcGP_Hamming->signal)==0)
      {freeSignalStruct(&swrcGP_Hamming->signal);continue;}
    //printAllSignals(&swrcGP_Hamming->signal);//exit(-1);
    freeSignalStruct(&swrcGP_Hamming->signal);
  }
  posttrainGP_HammingEncoder(&swrcGP_Hamming->GP_HammingEncoder);
  posttrainGP_HammingChannel(&swrcGP_Hamming->GP_HammingChannel);
  posttrainGP_HammingDecoder(&swrcGP_Hamming->GP_HammingDecoder);
  posttrainSwrcGP_Hamming(swrcGP_Hamming);
}

// Count the BER/FER between 2 signals in the signal struct
// obi is the original bit index 
// dbi is the detected bit index
void countBERSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming,int obi, int dbi) {
  int i;
  uint8_t *original, *detected;
  uint8_t frameError=0;
  swrcGP_Hamming->numberOfFrames++;
  swrcGP_Hamming->numberOfBits+=swrcGP_Hamming->N;
  original = (uint8_t*) swrcGP_Hamming->signal.x[obi];
  detected = (uint8_t*) swrcGP_Hamming->signal.x[dbi];
  //for (i=0;i<swrcGP_Hamming->N;i++) printf("%d",original[i]);printf("\n");
  //for (i=0;i<swrcGP_Hamming->N;i++) printf("%d",detected[i]);printf("\n");
  for (i=0;i<swrcGP_Hamming->N;i++) {
    if (original[i]!=detected[i]) {
      if (frameError==0) {
	swrcGP_Hamming->numberOfFrameErrors++;
	frameError=1;
      }
      swrcGP_Hamming->numberOfBitErrors++;
    }
  }
  swrcGP_Hamming->FER = ((double)swrcGP_Hamming->numberOfFrameErrors)/((double)swrcGP_Hamming->numberOfFrames);
  swrcGP_Hamming->BER = ((double)swrcGP_Hamming->numberOfBitErrors)/((double)swrcGP_Hamming->numberOfBits);
  printf("FER : %d/%d = %lf, BER : %d/%ld = %lf\n",swrcGP_Hamming->numberOfFrameErrors,swrcGP_Hamming->numberOfFrames,swrcGP_Hamming->FER,swrcGP_Hamming->numberOfBitErrors,swrcGP_Hamming->numberOfBits,swrcGP_Hamming->BER);
}

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming,berResultStruct *berResult,char *berResultFilename) {
  printf("In function initBerResultStructSwrcGP_Hamming\n");
  asprintf(&berResult->berResultFilename,"%s",berResultFilename);
  asprintf(&berResult->lockFilename,"%s.lock",berResultFilename);
  berResult->N_berResultFilename=strlen(berResult->berResultFilename);
  //pushBerResultField(berResult,"startTime","time_t","%10d",&swrcGP_Hamming->startTime);
  //pushBerResultField(berResult,"endTime","time_t","%10d",&swrcGP_Hamming->endTime);
  pushBerResultField(berResult,"runTime","time_t","%7d",&swrcGP_Hamming->runTime);
  pushBerResultField(berResult,"N","int","%5d",&swrcGP_Hamming->N);
  pushBerResultField(berResult,"M","int","%4d",&swrcGP_Hamming->M);
  pushBerResultField(berResult,"K","int","%4d",&swrcGP_Hamming->K);
  pushBerResultField(berResult,"#Frames","int","%7d",&swrcGP_Hamming->numberOfFrames);
  pushBerResultField(berResult,"#FramesErr","int","%10d",&swrcGP_Hamming->numberOfFrameErrors);
  pushBerResultField(berResult,"#Bits","long int","%10ld",&swrcGP_Hamming->numberOfBits);
  pushBerResultField(berResult,"#BitErr","int","%7d",&swrcGP_Hamming->numberOfBitErrors);
  pushBerResultField(berResult,"FER","double","%10.8lf",&swrcGP_Hamming->FER);
  pushBerResultField(berResult,"BER","double","%10.8lf",&swrcGP_Hamming->BER);
  initBerResultStructGP_HammingEncoder(&swrcGP_Hamming->GP_HammingEncoder,berResult);
  initBerResultStructGP_HammingChannel(&swrcGP_Hamming->GP_HammingChannel,berResult);
  initBerResultStructGP_HammingDecoder(&swrcGP_Hamming->GP_HammingDecoder,berResult);  
  pushBerResultField(berResult,"StartSimDateTime","char*","%26s",&swrcGP_Hamming->startTimeString);
  pushBerResultField(berResult,"EndSimDateTime","char*","%26s",&swrcGP_Hamming->endTimeString);
  pushBerResultField(berResult,"CPID","char*","%37s",&swrcGP_Hamming->CPID);
}

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runSwrcGP_Hamming (swrcGP_HammingStruct *swrcGP_Hamming) {
  int i;
  berResultStruct berResult;
  int idum=1;SWRC_randomize(&idum);
  initBerResultStruct(&berResult);
  printf("In runSwrcGP_Hamming\n");
  precompSwrcGP_Hamming(swrcGP_Hamming);
  precompGP_HammingEncoder(&swrcGP_Hamming->GP_HammingEncoder);
  precompGP_HammingChannel(&swrcGP_Hamming->GP_HammingChannel);
  precompGP_HammingDecoder(&swrcGP_Hamming->GP_HammingDecoder);
  precompSwrcGP_Hamming(swrcGP_Hamming);
  initBerResultStructSwrcGP_Hamming(swrcGP_Hamming,&berResult,"swrcGP_Hamming.berResult");
  if (checkParametersSwrcGP_Hamming(swrcGP_Hamming)>0) {
    printf("Exiting swrcGP_Hamming\n");
    exit(-1);
  }
  for (swrcGP_Hamming->numberOfFrames=0,swrcGP_Hamming->numberOfBits=0;(swrcGP_Hamming->numberOfFrames<swrcGP_Hamming->minNumberOfFrames || swrcGP_Hamming->numberOfFrameErrors<swrcGP_Hamming->minNumberOfFrameErrors) && (swrcGP_Hamming->numberOfFrames<swrcGP_Hamming->maxNumberOfFrames);) {
    //////////////////////////////////
    // 0. generate the pseudorandom bit input
    //////////////////////////////////
    SWRC_printHeader("0. generatePseudoRandomUserBitsSignal");
    generatePseudoRandomUserBitsSignal(&swrcGP_Hamming->signal,swrcGP_Hamming->K);
    //  printAllSignals(&swrcGP_Hamming->signal);exit(-1);
    //////////////////////////////////
    // 1. run the GP_HammingEncoder module
    //////////////////////////////////
    SWRC_printHeader("1. GP_HammingEncoder");
     runGP_HammingEncoder(&swrcGP_Hamming->GP_HammingEncoder,&swrcGP_Hamming->signal);
    //////////////////////////////////
    // 2. run the GP_HammingChannel module
    //////////////////////////////////
    SWRC_printHeader("2. GP_HammingChannel");
    runGP_HammingChannel(&swrcGP_Hamming->GP_HammingChannel,&swrcGP_Hamming->signal);
    //////////////////////////////////
    // 3. run the GP_HammingDecoder module
    //////////////////////////////////
    SWRC_printHeader("3. GP_HammingDecoder");
    runGP_HammingDecoder(&swrcGP_Hamming->GP_HammingDecoder,&swrcGP_Hamming->signal);
    //printAllSignals(&swrcGP_Hamming->signal);//exit(-1);
    //////////////////////////////////
    // 4. Count BER
    //////////////////////////////////
    SWRC_printHeader("4. Count BER");
     countBERSwrcGP_Hamming(swrcGP_Hamming,0,4); // Count the bit/frame errors. "1" and "5" are the indices of the 2 signals being compared and are hard-coded. User must set these values appropriately for their simulation.
    postcompSwrcGP_Hamming(swrcGP_Hamming,' '); // ' ' is a flag indicating this simulation is still ongoing
    saveBerResultFile(&berResult,&swrcGP_Hamming->startTime,&swrcGP_Hamming->endTime,&swrcGP_Hamming->runTime,swrcGP_Hamming->dumpEvery); // Try to save berResult
    freeSignalStruct(&swrcGP_Hamming->signal);
  }
  postcompGP_HammingEncoder(&swrcGP_Hamming->GP_HammingEncoder,'*');
  postcompGP_HammingChannel(&swrcGP_Hamming->GP_HammingChannel,'*');
  postcompGP_HammingDecoder(&swrcGP_Hamming->GP_HammingDecoder,'*');
  postcompSwrcGP_Hamming(swrcGP_Hamming,'*'); // '*' is a flag indicating this simulation is finished
  saveBerResultFile(&berResult,&swrcGP_Hamming->startTime,&swrcGP_Hamming->endTime,&swrcGP_Hamming->runTime,0); //force save of berResult.
  freeBerResultStruct(&berResult);	
}


