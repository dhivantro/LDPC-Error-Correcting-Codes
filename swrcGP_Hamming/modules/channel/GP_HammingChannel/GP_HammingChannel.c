// Software Recording Channel (SWRC) platform in C.
// Name      : GP_HammingChannel
// Type      : module.
// Path      : modules/channel/GP_HammingChannel
// Dependency: 
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Mon Sep 13 16:36:32 2021
// Comment   : The first-trial (7,4) Hamming channel module for the  group project 
//             team 

#include "GP_HammingChannel.h"
// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel) {
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  GP_HammingChannel->N                = 0;
  GP_HammingChannel->R                = 0.0;
  GP_HammingChannel->SNR              = 0.0;
// Fields automatically included in every module that request $args{i}
  GP_HammingChannel->trainFlag        = 0;
  GP_HammingChannel->N_train          = 0;
  GP_HammingChannel->i_train          = 0;
  GP_HammingChannel->numberOfMult     = 0;
  GP_HammingChannel->aveNoOfMultPerFrame = 0.0;
  GP_HammingChannel->numberOfAdd      = 0;
  GP_HammingChannel->aveNoOfAddPerFrame = 0.0;
  GP_HammingChannel->numberOfComp     = 0;
  GP_HammingChannel->aveNoOfCompPerFrame = 0.0;
  GP_HammingChannel->simTime          = 0.0;
  GP_HammingChannel->aveSimTimePerFrame = 0.0;
  GP_HammingChannel->numberOfCalls    = 0;
}

// Frees up all the memory in the structure
void freeGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel) {
  if (GP_HammingChannel==NULL) {printf("GP_HammingChannel=NULL in function freeGP_HammingChannelStruct not free'ing\n");return;}
  int i;
  GP_HammingChannel->N          =0;
  GP_HammingChannel->R          =0.0;
  GP_HammingChannel->SNR        =0.0;
  GP_HammingChannel->trainFlag  =0;
  GP_HammingChannel->N_train    =0;
  GP_HammingChannel->i_train    =0;
  GP_HammingChannel->numberOfMult=0;
  GP_HammingChannel->aveNoOfMultPerFrame=0.0;
  GP_HammingChannel->numberOfAdd=0;
  GP_HammingChannel->aveNoOfAddPerFrame=0.0;
  GP_HammingChannel->numberOfComp=0;
  GP_HammingChannel->aveNoOfCompPerFrame=0.0;
  GP_HammingChannel->simTime    =0.0;
  GP_HammingChannel->aveSimTimePerFrame=0.0;
  GP_HammingChannel->numberOfCalls=0;
  //free(GP_HammingChannel);GP_HammingChannel=NULL;
}

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel, char *name, int index, int pre) {
  int i,j;
  char *preString,*name2;
  if (GP_HammingChannel==NULL) {printf("%s%s=NULL\n",preString,name);return;}
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  printf("%s[--%d:%s--------\n",preString,index,name);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
    printf("%s  int                  %s->N=%d\n",preString,name,GP_HammingChannel->N);                 // Print int N
    printf("%s  double               %s->R=%lf\n",preString,name,GP_HammingChannel->R);                // Print double R
    printf("%s  double               %s->SNR=%lf\n",preString,name,GP_HammingChannel->SNR);            // Print double SNR
// Fields automatically included in every module that request $args{i}
    printf("%s  uint8_t              %s->trainFlag=%"SCNu8"\n",preString,name,GP_HammingChannel->trainFlag); // Print uint8_t trainFlag
    printf("%s  long int             %s->N_train=%ld\n",preString,name,GP_HammingChannel->N_train);    // Print long int N_train
    printf("%s  long int             %s->i_train=%ld\n",preString,name,GP_HammingChannel->i_train);    // Print long int i_train
    printf("%s  long unsigned int    %s->numberOfMult=%lu\n",preString,name,GP_HammingChannel->numberOfMult); // Print long unsigned int numberOfMult
    printf("%s  double               %s->aveNoOfMultPerFrame=%lf\n",preString,name,GP_HammingChannel->aveNoOfMultPerFrame); // Print double aveNoOfMultPerFrame
    printf("%s  long unsigned int    %s->numberOfAdd=%lu\n",preString,name,GP_HammingChannel->numberOfAdd); // Print long unsigned int numberOfAdd
    printf("%s  double               %s->aveNoOfAddPerFrame=%lf\n",preString,name,GP_HammingChannel->aveNoOfAddPerFrame); // Print double aveNoOfAddPerFrame
    printf("%s  long unsigned int    %s->numberOfComp=%lu\n",preString,name,GP_HammingChannel->numberOfComp); // Print long unsigned int numberOfComp
    printf("%s  double               %s->aveNoOfCompPerFrame=%lf\n",preString,name,GP_HammingChannel->aveNoOfCompPerFrame); // Print double aveNoOfCompPerFrame
    printf("%s  double               %s->simTime=%lf\n",preString,name,GP_HammingChannel->simTime);    // Print double simTime
    printf("%s  double               %s->aveSimTimePerFrame=%lf\n",preString,name,GP_HammingChannel->aveSimTimePerFrame); // Print double aveSimTimePerFrame
    printf("%s  long unsigned int    %s->numberOfCalls=%lu\n",preString,name,GP_HammingChannel->numberOfCalls); // Print long unsigned int numberOfCalls
  printf("%s---%d:%s-------]\n",preString,index,name);
  free(preString);
}

// Store random values into the fields of GP_HammingChannelStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel) {
  int idum=1;SWRC_randomize(&idum);
  //GP_HammingChannel->N=rand();
  //GP_HammingChannel->R=ran2(&idum);
  //GP_HammingChannel->SNR=ran2(&idum);
}

// Initialize an array of GP_HammingChannelStruct's to sane starting values
void initArrayGP_HammingChannelStruct (arrayGP_HammingChannelStruct *GP_HammingChannel) {
  GP_HammingChannel->N_x=0;
  GP_HammingChannel->x=NULL;
}

// Allocate memory for an array of N GP_HammingChannelStruct's
void allocateArrayGP_HammingChannelStruct (arrayGP_HammingChannelStruct *GP_HammingChannel,int N) {
  int i;
  GP_HammingChannel->N_x=N;
  GP_HammingChannel->x = (GP_HammingChannelStruct*)realloc(GP_HammingChannel->x,N*sizeof(GP_HammingChannelStruct));
  for (i=0;i<GP_HammingChannel->N_x;i++) {
    initGP_HammingChannelStruct(&GP_HammingChannel->x[i]);
  }
}

// Free an array of GP_HammingChannelStruct's
void freeArrayGP_HammingChannelStruct (arrayGP_HammingChannelStruct *GP_HammingChannel) {
  if (GP_HammingChannel==NULL) {printf("GP_HammingChannel=NULL in function freeArrayGP_HammingChannelStruct not free'ing\n");return;}
  int i;
  for (i=0;i<GP_HammingChannel->N_x;i++) {
    freeGP_HammingChannelStruct(&GP_HammingChannel->x[i]);
  } free(GP_HammingChannel->x);GP_HammingChannel->x=NULL;
}

// Fill the arrayGP_HammingChannelStruct with random values.
// The GP_HammingChannel->N_GP_HammingChannel parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_HammingChannelStruct (arrayGP_HammingChannelStruct *GP_HammingChannel) {
  int i;
  for (i=0;i<GP_HammingChannel->N_x;i++) randomizeGP_HammingChannelStruct(&GP_HammingChannel->x[i]);
}

// Print arrayGP_HammingChannelStruct
void printArrayGP_HammingChannelStruct (arrayGP_HammingChannelStruct *GP_HammingChannel) {
  int i;
  for (i=0;i<GP_HammingChannel->N_x;i++) {
    printGP_HammingChannelStruct(&GP_HammingChannel->x[i],"GP_HammingChannel",i,0);
  }
}

// Initialize a double array of GP_HammingChannelStruct to sane startup values
void initDoubleArrayGP_HammingChannelStruct (doubleArrayGP_HammingChannelStruct *GP_HammingChannel) {
  GP_HammingChannel->N_N_x=0;
  GP_HammingChannel->N_x=NULL;
  GP_HammingChannel->x=NULL;
}

// Allocate memory for a rectangular double array of GP_HammingChannelStruct
void allocateDoubleArrayGP_HammingChannelStruct (doubleArrayGP_HammingChannelStruct *GP_HammingChannel, int N, int M) {
  int i,j;
  GP_HammingChannel->N_N_x=N;
  GP_HammingChannel->N_x=(long unsigned int*)realloc(GP_HammingChannel->N_x,N*sizeof(long unsigned int));
  for (i=0;i<GP_HammingChannel->N_N_x;i++) GP_HammingChannel->N_x[i]=M;
  GP_HammingChannel->x=(GP_HammingChannelStruct**)realloc(GP_HammingChannel->x,N*sizeof(GP_HammingChannelStruct*));
  for (i=0;i<GP_HammingChannel->N_N_x;i++) {
    GP_HammingChannel->x[i]=(GP_HammingChannelStruct*)calloc(M,sizeof(GP_HammingChannelStruct));
  for(j=0;j<GP_HammingChannel->N_x[i];j++) initGP_HammingChannelStruct(&GP_HammingChannel->x[i][j]);
  }
}

// Free a double array of GP_HammingChannelStruct's
void freeDoubleArrayGP_HammingChannelStruct (doubleArrayGP_HammingChannelStruct *GP_HammingChannel) {
  int i;
  for (i=0;i<GP_HammingChannel->N_N_x;i++) {
    if (GP_HammingChannel->x[i]!=NULL) free(GP_HammingChannel->x[i]);
  }
  free(GP_HammingChannel->N_x);GP_HammingChannel->N_x=NULL;
  free(GP_HammingChannel->x);GP_HammingChannel->x=NULL;
}

// Print arrayGP_HammingChannelStruct
void printDoubleArrayGP_HammingChannelStruct (doubleArrayGP_HammingChannelStruct *GP_HammingChannel, char *name, int index, int pre) {
}

// Plot function generates any plots associated with the 
// structure
void plotGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel, const char *filename) {
}

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile) {
  int i;
 //Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Pack int N
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->N,1,sizeof(int),cfgFile);
  // Pack double R
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->R,1,sizeof(double),cfgFile);
  // Pack double SNR
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->SNR,1,sizeof(double),cfgFile);
 //Fields automatically included in every module that request $args{i}
  // Pack uint8_t trainFlag
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Pack long int N_train
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->N_train,1,sizeof(long int),cfgFile);
  // Pack long int i_train
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->i_train,1,sizeof(long int),cfgFile);
  // Pack long unsigned int numberOfMult
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfMultPerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfAdd
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfAddPerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfComp
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfCompPerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Pack double simTime
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->simTime,1,sizeof(double),cfgFile);
  // Pack double aveSimTimePerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfCalls
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile) {
  int i;
  freeGP_HammingChannelStruct(GP_HammingChannel);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Unpack int N
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->N,1,sizeof(int),cfgFile);
  // Unpack double R
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->R,1,sizeof(double),cfgFile);
  // Unpack double SNR
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->SNR,1,sizeof(double),cfgFile);
// Fields automatically included in every module that request $args{i}
  // Unpack uint8_t trainFlag
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Unpack long int N_train
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->N_train,1,sizeof(long int),cfgFile);
  // Unpack long int i_train
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->i_train,1,sizeof(long int),cfgFile);
  // Unpack long unsigned int numberOfMult
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfMultPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfAdd
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfAddPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfComp
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfCompPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Unpack double simTime
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->simTime,1,sizeof(double),cfgFile);
  // Unpack double aveSimTimePerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfCalls
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// Pack the contents of arrayGP_HammingChannelStruct to a uint8_vector
void packArrayGP_HammingChannelStruct (arrayGP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile) {
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_HammingChannel->x,GP_HammingChannel->N_x,sizeof(GP_HammingChannelStruct),cfgFile);
}

// Unpack the contents of arrayGP_HammingChannelStruct from a uint8_vector.
void unpackArrayGP_HammingChannelStruct (arrayGP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile) {
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->N_x,1,sizeof(long unsigned int),cfgFile);
  GP_HammingChannel->x = (GP_HammingChannelStruct*)realloc(GP_HammingChannel->x,GP_HammingChannel->N_x*sizeof(GP_HammingChannelStruct));
  SWRC_unpackFromUint8((uint8_t*)GP_HammingChannel->x,GP_HammingChannel->N_x,sizeof(GP_HammingChannelStruct),cfgFile);
}

// Pack the contents of doubleArrayGP_HammingChannelStruct to a uint8_vector
void packDoubleArrayGP_HammingChannelStruct (doubleArrayGP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile) {
  int i;
  SWRC_packToUint8((uint8_t*)&GP_HammingChannel->N_N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_HammingChannel->N_x,GP_HammingChannel->N_N_x,sizeof(long unsigned int),cfgFile);
  for (i=0;i<GP_HammingChannel->N_N_x;i++) 
    SWRC_packToUint8((uint8_t*)GP_HammingChannel->x[i],GP_HammingChannel->N_x[i],sizeof(GP_HammingChannelStruct),cfgFile);
}

// Unpack the contents of doubleArrayGP_HammingChannelStruct from a uint8_vector
void unpackDoubleArrayGP_HammingChannelStruct (doubleArrayGP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile) {
  int i;
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingChannel->N_N_x,1,sizeof(long unsigned int),cfgFile);
  // allocate memory for and unpack GP_HammingChannel->N_GP_HammingChannel
  GP_HammingChannel->N_x=(long unsigned int*) realloc(GP_HammingChannel->N_x,GP_HammingChannel->N_N_x*sizeof(long unsigned int));
  SWRC_unpackFromUint8((uint8_t*)GP_HammingChannel->N_x,GP_HammingChannel->N_N_x,sizeof(long unsigned int),cfgFile);
  // allocate memory for GP_HammingChannel->GP_HammingChannel
  GP_HammingChannel->x=(GP_HammingChannelStruct**)realloc(GP_HammingChannel->x,GP_HammingChannel->N_N_x*sizeof(GP_HammingChannelStruct*));
  for (i=0;i<GP_HammingChannel->N_N_x;i++) {
    SWRC_unpackFromUint8((uint8_t*)GP_HammingChannel->x[i],GP_HammingChannel->N_x[i],sizeof(GP_HammingChannelStruct),cfgFile);
  }
}

// Function for loading the struct
int loadGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel, char *filename) {
}

// Function for saving the struct
void saveGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel, char *filename) {
}

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_HammingChannelStruct (GP_HammingChannelStruct *GP_HammingChannel, char *arg) {
  int i;
  SWRC_removeSpaces(arg);
   if (SWRC_readSingleArgumentFromString(arg,"N",&GP_HammingChannel->N,"%d")==1) {
     printf("N=%d\n",GP_HammingChannel->N);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"R",&GP_HammingChannel->R,"%lf")==1) {
  //   printf("R=%lf\n",GP_HammingChannel->R);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"SNR",&GP_HammingChannel->SNR,"%lf")==1) {
  //   printf("SNR=%lf\n",GP_HammingChannel->SNR);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"trainFlag",&GP_HammingChannel->trainFlag,"%"SCNu8"")==1) {
  //   printf("trainFlag=%"SCNu8"\n",GP_HammingChannel->trainFlag);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"N_train",&GP_HammingChannel->N_train,"%ld")==1) {
  //   printf("N_train=%ld\n",GP_HammingChannel->N_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"i_train",&GP_HammingChannel->i_train,"%ld")==1) {
  //   printf("i_train=%ld\n",GP_HammingChannel->i_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfMult",&GP_HammingChannel->numberOfMult,"%lu")==1) {
  //   printf("numberOfMult=%lu\n",GP_HammingChannel->numberOfMult);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfMultPerFrame",&GP_HammingChannel->aveNoOfMultPerFrame,"%lf")==1) {
  //   printf("aveNoOfMultPerFrame=%lf\n",GP_HammingChannel->aveNoOfMultPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfAdd",&GP_HammingChannel->numberOfAdd,"%lu")==1) {
  //   printf("numberOfAdd=%lu\n",GP_HammingChannel->numberOfAdd);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfAddPerFrame",&GP_HammingChannel->aveNoOfAddPerFrame,"%lf")==1) {
  //   printf("aveNoOfAddPerFrame=%lf\n",GP_HammingChannel->aveNoOfAddPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfComp",&GP_HammingChannel->numberOfComp,"%lu")==1) {
  //   printf("numberOfComp=%lu\n",GP_HammingChannel->numberOfComp);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfCompPerFrame",&GP_HammingChannel->aveNoOfCompPerFrame,"%lf")==1) {
  //   printf("aveNoOfCompPerFrame=%lf\n",GP_HammingChannel->aveNoOfCompPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"simTime",&GP_HammingChannel->simTime,"%lf")==1) {
  //   printf("simTime=%lf\n",GP_HammingChannel->simTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveSimTimePerFrame",&GP_HammingChannel->aveSimTimePerFrame,"%lf")==1) {
  //   printf("aveSimTimePerFrame=%lf\n",GP_HammingChannel->aveSimTimePerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfCalls",&GP_HammingChannel->numberOfCalls,"%lu")==1) {
  //   printf("numberOfCalls=%lu\n",GP_HammingChannel->numberOfCalls);
  // }
  if (*arg!='\0') {
    printf("GP_HammingChannel module: Remaining unknown parms in arg list:%s\n Please correct and run again.\n",arg);exit(-1);
  }
}

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_HammingChannel (GP_HammingChannelStruct *GP_HammingChannel, signalStruct *signal, const char *command) {
  char commandParameter[400];
  int i;
  printf("processCommandGP_HammingChannel:%s\n",command);
  for(i=0;i<400 && i<strlen(command);) {
    if (SWRC_matchCommand(command,"load",&i,commandParameter,400)==1) {
	loadGP_HammingChannelStruct(GP_HammingChannel,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"print",&i,commandParameter,400)==1) {
	printGP_HammingChannelStruct(GP_HammingChannel,"GP_HammingChannel",0,0);
	continue;
    }

    if (SWRC_matchCommand(command,"setParm",&i,commandParameter,400)==1) {
	setParmGP_HammingChannelStruct(GP_HammingChannel,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"checkParm",&i,commandParameter,400)==1) {
	checkParametersGP_HammingChannel(GP_HammingChannel);
	continue;
    }

    if (SWRC_matchCommand(command,"precomp",&i,commandParameter,400)==1) {
	precompGP_HammingChannel(GP_HammingChannel);
	continue;
    }

    if (SWRC_matchCommand(command,"postcomp",&i,commandParameter,400)==1) {
	postcompGP_HammingChannel(GP_HammingChannel,0);
	continue;
    }

    if (SWRC_matchCommand(command,"help",&i,commandParameter,400)==1) {
	helpCommandGP_HammingChannel(0);
	continue;
    }

    if (SWRC_matchCommand(command,"run",&i,commandParameter,400)==1) {
	runGP_HammingChannel(GP_HammingChannel, signal);
	continue;
    }

    printf("processCommandGP_HammingChannel: Unknown command:%s\n",&command[i]);
    break;
  }
}

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_HammingChannel (int index) {
  printf("Commands recognized by %d:GP_HammingChannelStruct:\n",index);
  printf("  \"print();\"        : print the GP_HammingChannelStruct fields\n");
  printf("  \"setParm(arg);\"   : set the GP_HammingChannelStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
}

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_HammingChannel (GP_HammingChannelStruct *GP_HammingChannel) {
  int output=0;
  //if (GP_HammingChannel->N==0) {output++;printf("GP_HammingChannel->N needed, but not set\n");}
  //if (GP_HammingChannel->R==0.0) {output++;printf("GP_HammingChannel->R needed, but not set\n");}
  //if (GP_HammingChannel->SNR==0.0) {output++;printf("GP_HammingChannel->SNR needed, but not set\n");}
  //if (GP_HammingChannel->trainFlag==0) {output++;printf("GP_HammingChannel->trainFlag needed, but not set\n");}
  //if (GP_HammingChannel->N_train==0) {output++;printf("GP_HammingChannel->N_train needed, but not set\n");}
  //if (GP_HammingChannel->i_train==0) {output++;printf("GP_HammingChannel->i_train needed, but not set\n");}
  //if (GP_HammingChannel->numberOfMult==0) {output++;printf("GP_HammingChannel->numberOfMult needed, but not set\n");}
  //if (GP_HammingChannel->aveNoOfMultPerFrame==0.0) {output++;printf("GP_HammingChannel->aveNoOfMultPerFrame needed, but not set\n");}
  //if (GP_HammingChannel->numberOfAdd==0) {output++;printf("GP_HammingChannel->numberOfAdd needed, but not set\n");}
  //if (GP_HammingChannel->aveNoOfAddPerFrame==0.0) {output++;printf("GP_HammingChannel->aveNoOfAddPerFrame needed, but not set\n");}
  //if (GP_HammingChannel->numberOfComp==0) {output++;printf("GP_HammingChannel->numberOfComp needed, but not set\n");}
  //if (GP_HammingChannel->aveNoOfCompPerFrame==0.0) {output++;printf("GP_HammingChannel->aveNoOfCompPerFrame needed, but not set\n");}
  //if (GP_HammingChannel->simTime==0.0) {output++;printf("GP_HammingChannel->simTime needed, but not set\n");}
  //if (GP_HammingChannel->aveSimTimePerFrame==0.0) {output++;printf("GP_HammingChannel->aveSimTimePerFrame needed, but not set\n");}
  //if (GP_HammingChannel->numberOfCalls==0) {output++;printf("GP_HammingChannel->numberOfCalls needed, but not set\n");}
  return(output);
}

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_HammingChannel (GP_HammingChannelStruct *GP_HammingChannel) {
  GP_HammingChannel->i_train=0;
  GP_HammingChannel->numberOfMult=0;
  GP_HammingChannel->aveNoOfMultPerFrame=0.0;
  GP_HammingChannel->numberOfAdd=0;
  GP_HammingChannel->aveNoOfAddPerFrame=0.0;
  GP_HammingChannel->numberOfComp=0;
  GP_HammingChannel->aveNoOfCompPerFrame=0.0;
  GP_HammingChannel->simTime=0.0;
  GP_HammingChannel->aveSimTimePerFrame=0.0;
  GP_HammingChannel->numberOfCalls=0;
}

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_HammingChannel (GP_HammingChannelStruct *GP_HammingChannel, char finishedFlag) {
  GP_HammingChannel->aveNoOfMultPerFrame=(double)GP_HammingChannel->numberOfMult/GP_HammingChannel->numberOfCalls;
  GP_HammingChannel->aveNoOfAddPerFrame=(double)GP_HammingChannel->numberOfAdd/GP_HammingChannel->numberOfCalls;
  GP_HammingChannel->aveNoOfCompPerFrame=(double)GP_HammingChannel->numberOfComp/GP_HammingChannel->numberOfCalls;
  GP_HammingChannel->aveSimTimePerFrame=(double)GP_HammingChannel->simTime/GP_HammingChannel->numberOfCalls;
}

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_HammingChannel (GP_HammingChannelStruct *GP_HammingChannel) {
  GP_HammingChannel->i_train=0;
}

// Function called after training. Free allocated memory etc...
void posttrainGP_HammingChannel (GP_HammingChannelStruct *GP_HammingChannel) {
}

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_HammingChannel (GP_HammingChannelStruct *GP_HammingChannel, signalStruct *signal) {
  if ((GP_HammingChannel->trainFlag&1)==1) { // Training complete, call the run function
    printf("Running GP_HammingChannel\n");
    runGP_HammingChannel(GP_HammingChannel,signal);
    return(1);
  } else {                 // Do the training
    printf("Training GP_HammingChannel %ld/%ld\n",GP_HammingChannel->i_train,GP_HammingChannel->N_train);
    // Accumulate the statistics
    GP_HammingChannel->i_train++;
    if (GP_HammingChannel->i_train>=GP_HammingChannel->N_train) { // Statistics accumulated, post-training computation
      GP_HammingChannel->trainFlag=1;
    }
    return(0);
  }
}

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_HammingChannel (GP_HammingChannelStruct *GP_HammingChannel,berResultStruct *berResult) {
  //pushBerResultField(berResult,"N","int","%1d",&GP_HammingChannel->N);
  //pushBerResultField(berResult,"R","double","%1lf",&GP_HammingChannel->R);
  //pushBerResultField(berResult,"SNR","double","%3lf",&GP_HammingChannel->SNR);
  //pushBerResultField(berResult,"trainFlag","uint8_t","%9"SCNu8"",&GP_HammingChannel->trainFlag);
  //pushBerResultField(berResult,"N_train","long int","%7ld",&GP_HammingChannel->N_train);
  //pushBerResultField(berResult,"i_train","long int","%7ld",&GP_HammingChannel->i_train);
  //pushBerResultField(berResult,"numberOfMult","long unsigned int","%12lu",&GP_HammingChannel->numberOfMult);
  //pushBerResultField(berResult,"aveNoOfMultPerFrame","double","%19lf",&GP_HammingChannel->aveNoOfMultPerFrame);
  //pushBerResultField(berResult,"numberOfAdd","long unsigned int","%11lu",&GP_HammingChannel->numberOfAdd);
  //pushBerResultField(berResult,"aveNoOfAddPerFrame","double","%18lf",&GP_HammingChannel->aveNoOfAddPerFrame);
  //pushBerResultField(berResult,"numberOfComp","long unsigned int","%12lu",&GP_HammingChannel->numberOfComp);
  //pushBerResultField(berResult,"aveNoOfCompPerFrame","double","%19lf",&GP_HammingChannel->aveNoOfCompPerFrame);
  //pushBerResultField(berResult,"simTime","double","%7lf",&GP_HammingChannel->simTime);
  //pushBerResultField(berResult,"aveSimTimePerFrame","double","%18lf",&GP_HammingChannel->aveSimTimePerFrame);
  //pushBerResultField(berResult,"numberOfCalls","long unsigned int","%13lu",&GP_HammingChannel->numberOfCalls);
}

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_HammingChannel (GP_HammingChannelStruct *GP_HammingChannel, signalStruct *signal) {
  int i;
  clock_t beginTime, endTime;
  int N_input,N_output;
  uint8_t *input;
  uint8_t *output;
  beginTime=clock();
  printf("In function runGP_HammingChannel\n");
  // Allocate memory for 1 more signal. The output of this function should go there.
  // USER NEEDS TO EDIT: the LENGTH of the output vector and the TYPE of
  // the output vector 0=uint8_t, 1=char, 2=int, 3=unsigned int, 4=long unsigned int, 5=float, 6=double
  // The type of the input vector should also be set correctly by the USER.
  N_input  = signal->N[signal->N_N-1];        // Length of the input vector
  input    = (uint8_t*) signal->x[signal->N_N-1]; // Assign pointer to the input memory
  N_output = GP_HammingChannel->N; //has error
  // N_output = 7; // Length of output vector
  output   = (uint8_t*) incrementByOneSignal(signal,N_output,0,"GP_HammingChannel");    // Create a new output vector on end of signal list
  
  // Computation engine :

  //output[0]=1;
  for(i=0; i<N_output; i++){
    output[i]=input[i];
  }

  printf("\n\n\n %d \n\n\n ",  GP_HammingChannel->N);

  // printAllSignals(signal); exit(-1);
  
  // Save the time for the computation engine
  endTime = clock();
  GP_HammingChannel->simTime+=(double)(endTime-beginTime)/CLOCKS_PER_SEC;
  GP_HammingChannel->numberOfCalls++;
}


