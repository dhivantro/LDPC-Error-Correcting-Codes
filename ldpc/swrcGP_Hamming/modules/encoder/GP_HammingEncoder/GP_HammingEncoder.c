// Software Recording Channel (SWRC) platform in C.
// Name      : GP_HammingEncoder
// Type      : module.
// Path      : modules/encoder/GP_HammingEncoder
// Dependency: 
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Mon Sep 13 16:36:14 2021
// Comment   : The first-trial (7,4) Hamming encoder for the group project 
//             team 

#include "GP_HammingEncoder.h"
// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder) {
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  GP_HammingEncoder->N                = 0;
  GP_HammingEncoder->M                = 0;
  GP_HammingEncoder->K                = 0;
  GP_HammingEncoder->R                = 0.0;
// Fields automatically included in every module that request $args{i}
  GP_HammingEncoder->trainFlag        = 0;
  GP_HammingEncoder->N_train          = 0;
  GP_HammingEncoder->i_train          = 0;
  GP_HammingEncoder->numberOfMult     = 0;
  GP_HammingEncoder->aveNoOfMultPerFrame = 0.0;
  GP_HammingEncoder->numberOfAdd      = 0;
  GP_HammingEncoder->aveNoOfAddPerFrame = 0.0;
  GP_HammingEncoder->numberOfComp     = 0;
  GP_HammingEncoder->aveNoOfCompPerFrame = 0.0;
  GP_HammingEncoder->simTime          = 0.0;
  GP_HammingEncoder->aveSimTimePerFrame = 0.0;
  GP_HammingEncoder->numberOfCalls    = 0;
}

// Frees up all the memory in the structure
void freeGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder) {
  if (GP_HammingEncoder==NULL) {printf("GP_HammingEncoder=NULL in function freeGP_HammingEncoderStruct not free'ing\n");return;}
  int i;
  GP_HammingEncoder->N          =0;
  GP_HammingEncoder->M          =0;
  GP_HammingEncoder->K          =0;
  GP_HammingEncoder->R          =0.0;
  GP_HammingEncoder->trainFlag  =0;
  GP_HammingEncoder->N_train    =0;
  GP_HammingEncoder->i_train    =0;
  GP_HammingEncoder->numberOfMult=0;
  GP_HammingEncoder->aveNoOfMultPerFrame=0.0;
  GP_HammingEncoder->numberOfAdd=0;
  GP_HammingEncoder->aveNoOfAddPerFrame=0.0;
  GP_HammingEncoder->numberOfComp=0;
  GP_HammingEncoder->aveNoOfCompPerFrame=0.0;
  GP_HammingEncoder->simTime    =0.0;
  GP_HammingEncoder->aveSimTimePerFrame=0.0;
  GP_HammingEncoder->numberOfCalls=0;
  //free(GP_HammingEncoder);GP_HammingEncoder=NULL;
}

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder, char *name, int index, int pre) {
  int i,j;
  char *preString,*name2;
  if (GP_HammingEncoder==NULL) {printf("%s%s=NULL\n",preString,name);return;}
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  printf("%s[--%d:%s--------\n",preString,index,name);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
    printf("%s  int                  %s->N=%d\n",preString,name,GP_HammingEncoder->N);                 // Print int N
    printf("%s  int                  %s->M=%d\n",preString,name,GP_HammingEncoder->M);                 // Print int M
    printf("%s  int                  %s->K=%d\n",preString,name,GP_HammingEncoder->K);                 // Print int K
    printf("%s  double               %s->R=%lf\n",preString,name,GP_HammingEncoder->R);                // Print double R
// Fields automatically included in every module that request $args{i}
    printf("%s  uint8_t              %s->trainFlag=%"SCNu8"\n",preString,name,GP_HammingEncoder->trainFlag); // Print uint8_t trainFlag
    printf("%s  long int             %s->N_train=%ld\n",preString,name,GP_HammingEncoder->N_train);    // Print long int N_train
    printf("%s  long int             %s->i_train=%ld\n",preString,name,GP_HammingEncoder->i_train);    // Print long int i_train
    printf("%s  long unsigned int    %s->numberOfMult=%lu\n",preString,name,GP_HammingEncoder->numberOfMult); // Print long unsigned int numberOfMult
    printf("%s  double               %s->aveNoOfMultPerFrame=%lf\n",preString,name,GP_HammingEncoder->aveNoOfMultPerFrame); // Print double aveNoOfMultPerFrame
    printf("%s  long unsigned int    %s->numberOfAdd=%lu\n",preString,name,GP_HammingEncoder->numberOfAdd); // Print long unsigned int numberOfAdd
    printf("%s  double               %s->aveNoOfAddPerFrame=%lf\n",preString,name,GP_HammingEncoder->aveNoOfAddPerFrame); // Print double aveNoOfAddPerFrame
    printf("%s  long unsigned int    %s->numberOfComp=%lu\n",preString,name,GP_HammingEncoder->numberOfComp); // Print long unsigned int numberOfComp
    printf("%s  double               %s->aveNoOfCompPerFrame=%lf\n",preString,name,GP_HammingEncoder->aveNoOfCompPerFrame); // Print double aveNoOfCompPerFrame
    printf("%s  double               %s->simTime=%lf\n",preString,name,GP_HammingEncoder->simTime);    // Print double simTime
    printf("%s  double               %s->aveSimTimePerFrame=%lf\n",preString,name,GP_HammingEncoder->aveSimTimePerFrame); // Print double aveSimTimePerFrame
    printf("%s  long unsigned int    %s->numberOfCalls=%lu\n",preString,name,GP_HammingEncoder->numberOfCalls); // Print long unsigned int numberOfCalls
  printf("%s---%d:%s-------]\n",preString,index,name);
  free(preString);
}

// Store random values into the fields of GP_HammingEncoderStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder) {
  int idum=1;SWRC_randomize(&idum);
  //GP_HammingEncoder->N=rand();
  //GP_HammingEncoder->M=rand();
  //GP_HammingEncoder->K=rand();
  //GP_HammingEncoder->R=ran2(&idum);
}

// Initialize an array of GP_HammingEncoderStruct's to sane starting values
void initArrayGP_HammingEncoderStruct (arrayGP_HammingEncoderStruct *GP_HammingEncoder) {
  GP_HammingEncoder->N_x=0;
  GP_HammingEncoder->x=NULL;
}

// Allocate memory for an array of N GP_HammingEncoderStruct's
void allocateArrayGP_HammingEncoderStruct (arrayGP_HammingEncoderStruct *GP_HammingEncoder,int N) {
  int i;
  GP_HammingEncoder->N_x=N;
  GP_HammingEncoder->x = (GP_HammingEncoderStruct*)realloc(GP_HammingEncoder->x,N*sizeof(GP_HammingEncoderStruct));
  for (i=0;i<GP_HammingEncoder->N_x;i++) {
    initGP_HammingEncoderStruct(&GP_HammingEncoder->x[i]);
  }
}

// Free an array of GP_HammingEncoderStruct's
void freeArrayGP_HammingEncoderStruct (arrayGP_HammingEncoderStruct *GP_HammingEncoder) {
  if (GP_HammingEncoder==NULL) {printf("GP_HammingEncoder=NULL in function freeArrayGP_HammingEncoderStruct not free'ing\n");return;}
  int i;
  for (i=0;i<GP_HammingEncoder->N_x;i++) {
    freeGP_HammingEncoderStruct(&GP_HammingEncoder->x[i]);
  } free(GP_HammingEncoder->x);GP_HammingEncoder->x=NULL;
}

// Fill the arrayGP_HammingEncoderStruct with random values.
// The GP_HammingEncoder->N_GP_HammingEncoder parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_HammingEncoderStruct (arrayGP_HammingEncoderStruct *GP_HammingEncoder) {
  int i;
  for (i=0;i<GP_HammingEncoder->N_x;i++) randomizeGP_HammingEncoderStruct(&GP_HammingEncoder->x[i]);
}

// Print arrayGP_HammingEncoderStruct
void printArrayGP_HammingEncoderStruct (arrayGP_HammingEncoderStruct *GP_HammingEncoder) {
  int i;
  for (i=0;i<GP_HammingEncoder->N_x;i++) {
    printGP_HammingEncoderStruct(&GP_HammingEncoder->x[i],"GP_HammingEncoder",i,0);
  }
}

// Initialize a double array of GP_HammingEncoderStruct to sane startup values
void initDoubleArrayGP_HammingEncoderStruct (doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder) {
  GP_HammingEncoder->N_N_x=0;
  GP_HammingEncoder->N_x=NULL;
  GP_HammingEncoder->x=NULL;
}

// Allocate memory for a rectangular double array of GP_HammingEncoderStruct
void allocateDoubleArrayGP_HammingEncoderStruct (doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder, int N, int M) {
  int i,j;
  GP_HammingEncoder->N_N_x=N;
  GP_HammingEncoder->N_x=(long unsigned int*)realloc(GP_HammingEncoder->N_x,N*sizeof(long unsigned int));
  for (i=0;i<GP_HammingEncoder->N_N_x;i++) GP_HammingEncoder->N_x[i]=M;
  GP_HammingEncoder->x=(GP_HammingEncoderStruct**)realloc(GP_HammingEncoder->x,N*sizeof(GP_HammingEncoderStruct*));
  for (i=0;i<GP_HammingEncoder->N_N_x;i++) {
    GP_HammingEncoder->x[i]=(GP_HammingEncoderStruct*)calloc(M,sizeof(GP_HammingEncoderStruct));
  for(j=0;j<GP_HammingEncoder->N_x[i];j++) initGP_HammingEncoderStruct(&GP_HammingEncoder->x[i][j]);
  }
}

// Free a double array of GP_HammingEncoderStruct's
void freeDoubleArrayGP_HammingEncoderStruct (doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder) {
  int i;
  for (i=0;i<GP_HammingEncoder->N_N_x;i++) {
    if (GP_HammingEncoder->x[i]!=NULL) free(GP_HammingEncoder->x[i]);
  }
  free(GP_HammingEncoder->N_x);GP_HammingEncoder->N_x=NULL;
  free(GP_HammingEncoder->x);GP_HammingEncoder->x=NULL;
}

// Print arrayGP_HammingEncoderStruct
void printDoubleArrayGP_HammingEncoderStruct (doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder, char *name, int index, int pre) {
}

// Plot function generates any plots associated with the 
// structure
void plotGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder, const char *filename) {
}

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile) {
  int i;
 //Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Pack int N
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->N,1,sizeof(int),cfgFile);
  // Pack int M
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->M,1,sizeof(int),cfgFile);
  // Pack int K
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->K,1,sizeof(int),cfgFile);
  // Pack double R
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->R,1,sizeof(double),cfgFile);
 //Fields automatically included in every module that request $args{i}
  // Pack uint8_t trainFlag
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Pack long int N_train
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->N_train,1,sizeof(long int),cfgFile);
  // Pack long int i_train
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->i_train,1,sizeof(long int),cfgFile);
  // Pack long unsigned int numberOfMult
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfMultPerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfAdd
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfAddPerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfComp
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfCompPerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Pack double simTime
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->simTime,1,sizeof(double),cfgFile);
  // Pack double aveSimTimePerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfCalls
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile) {
  int i;
  freeGP_HammingEncoderStruct(GP_HammingEncoder);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Unpack int N
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->N,1,sizeof(int),cfgFile);
  // Unpack int M
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->M,1,sizeof(int),cfgFile);
  // Unpack int K
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->K,1,sizeof(int),cfgFile);
  // Unpack double R
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->R,1,sizeof(double),cfgFile);
// Fields automatically included in every module that request $args{i}
  // Unpack uint8_t trainFlag
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Unpack long int N_train
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->N_train,1,sizeof(long int),cfgFile);
  // Unpack long int i_train
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->i_train,1,sizeof(long int),cfgFile);
  // Unpack long unsigned int numberOfMult
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfMultPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfAdd
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfAddPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfComp
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfCompPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Unpack double simTime
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->simTime,1,sizeof(double),cfgFile);
  // Unpack double aveSimTimePerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfCalls
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// Pack the contents of arrayGP_HammingEncoderStruct to a uint8_vector
void packArrayGP_HammingEncoderStruct (arrayGP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile) {
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_HammingEncoder->x,GP_HammingEncoder->N_x,sizeof(GP_HammingEncoderStruct),cfgFile);
}

// Unpack the contents of arrayGP_HammingEncoderStruct from a uint8_vector.
void unpackArrayGP_HammingEncoderStruct (arrayGP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile) {
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->N_x,1,sizeof(long unsigned int),cfgFile);
  GP_HammingEncoder->x = (GP_HammingEncoderStruct*)realloc(GP_HammingEncoder->x,GP_HammingEncoder->N_x*sizeof(GP_HammingEncoderStruct));
  SWRC_unpackFromUint8((uint8_t*)GP_HammingEncoder->x,GP_HammingEncoder->N_x,sizeof(GP_HammingEncoderStruct),cfgFile);
}

// Pack the contents of doubleArrayGP_HammingEncoderStruct to a uint8_vector
void packDoubleArrayGP_HammingEncoderStruct (doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile) {
  int i;
  SWRC_packToUint8((uint8_t*)&GP_HammingEncoder->N_N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_HammingEncoder->N_x,GP_HammingEncoder->N_N_x,sizeof(long unsigned int),cfgFile);
  for (i=0;i<GP_HammingEncoder->N_N_x;i++) 
    SWRC_packToUint8((uint8_t*)GP_HammingEncoder->x[i],GP_HammingEncoder->N_x[i],sizeof(GP_HammingEncoderStruct),cfgFile);
}

// Unpack the contents of doubleArrayGP_HammingEncoderStruct from a uint8_vector
void unpackDoubleArrayGP_HammingEncoderStruct (doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile) {
  int i;
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingEncoder->N_N_x,1,sizeof(long unsigned int),cfgFile);
  // allocate memory for and unpack GP_HammingEncoder->N_GP_HammingEncoder
  GP_HammingEncoder->N_x=(long unsigned int*) realloc(GP_HammingEncoder->N_x,GP_HammingEncoder->N_N_x*sizeof(long unsigned int));
  SWRC_unpackFromUint8((uint8_t*)GP_HammingEncoder->N_x,GP_HammingEncoder->N_N_x,sizeof(long unsigned int),cfgFile);
  // allocate memory for GP_HammingEncoder->GP_HammingEncoder
  GP_HammingEncoder->x=(GP_HammingEncoderStruct**)realloc(GP_HammingEncoder->x,GP_HammingEncoder->N_N_x*sizeof(GP_HammingEncoderStruct*));
  for (i=0;i<GP_HammingEncoder->N_N_x;i++) {
    SWRC_unpackFromUint8((uint8_t*)GP_HammingEncoder->x[i],GP_HammingEncoder->N_x[i],sizeof(GP_HammingEncoderStruct),cfgFile);
  }
}

// Function for loading the struct
int loadGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder, char *filename) {
}

// Function for saving the struct
void saveGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder, char *filename) {
}

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_HammingEncoderStruct (GP_HammingEncoderStruct *GP_HammingEncoder, char *arg) {
  int i;
  SWRC_removeSpaces(arg);
   if (SWRC_readSingleArgumentFromString(arg,"N",&GP_HammingEncoder->N,"%d")==1) {
     printf("N=%d\n",GP_HammingEncoder->N);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"M",&GP_HammingEncoder->M,"%d")==1) {
  //   printf("M=%d\n",GP_HammingEncoder->M);
  // }
   if (SWRC_readSingleArgumentFromString(arg,"K",&GP_HammingEncoder->K,"%d")==1) {
     printf("K=%d\n",GP_HammingEncoder->K);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"R",&GP_HammingEncoder->R,"%lf")==1) {
  //   printf("R=%lf\n",GP_HammingEncoder->R);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"trainFlag",&GP_HammingEncoder->trainFlag,"%"SCNu8"")==1) {
  //   printf("trainFlag=%"SCNu8"\n",GP_HammingEncoder->trainFlag);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"N_train",&GP_HammingEncoder->N_train,"%ld")==1) {
  //   printf("N_train=%ld\n",GP_HammingEncoder->N_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"i_train",&GP_HammingEncoder->i_train,"%ld")==1) {
  //   printf("i_train=%ld\n",GP_HammingEncoder->i_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfMult",&GP_HammingEncoder->numberOfMult,"%lu")==1) {
  //   printf("numberOfMult=%lu\n",GP_HammingEncoder->numberOfMult);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfMultPerFrame",&GP_HammingEncoder->aveNoOfMultPerFrame,"%lf")==1) {
  //   printf("aveNoOfMultPerFrame=%lf\n",GP_HammingEncoder->aveNoOfMultPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfAdd",&GP_HammingEncoder->numberOfAdd,"%lu")==1) {
  //   printf("numberOfAdd=%lu\n",GP_HammingEncoder->numberOfAdd);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfAddPerFrame",&GP_HammingEncoder->aveNoOfAddPerFrame,"%lf")==1) {
  //   printf("aveNoOfAddPerFrame=%lf\n",GP_HammingEncoder->aveNoOfAddPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfComp",&GP_HammingEncoder->numberOfComp,"%lu")==1) {
  //   printf("numberOfComp=%lu\n",GP_HammingEncoder->numberOfComp);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfCompPerFrame",&GP_HammingEncoder->aveNoOfCompPerFrame,"%lf")==1) {
  //   printf("aveNoOfCompPerFrame=%lf\n",GP_HammingEncoder->aveNoOfCompPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"simTime",&GP_HammingEncoder->simTime,"%lf")==1) {
  //   printf("simTime=%lf\n",GP_HammingEncoder->simTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveSimTimePerFrame",&GP_HammingEncoder->aveSimTimePerFrame,"%lf")==1) {
  //   printf("aveSimTimePerFrame=%lf\n",GP_HammingEncoder->aveSimTimePerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfCalls",&GP_HammingEncoder->numberOfCalls,"%lu")==1) {
  //   printf("numberOfCalls=%lu\n",GP_HammingEncoder->numberOfCalls);
  // }
  if (*arg!='\0') {
    printf("GP_HammingEncoder module: Remaining unknown parms in arg list:%s\n Please correct and run again.\n",arg);exit(-1);
  }
}

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_HammingEncoder (GP_HammingEncoderStruct *GP_HammingEncoder, signalStruct *signal, const char *command) {
  char commandParameter[400];
  int i;
  printf("processCommandGP_HammingEncoder:%s\n",command);
  for(i=0;i<400 && i<strlen(command);) {
    if (SWRC_matchCommand(command,"load",&i,commandParameter,400)==1) {
	loadGP_HammingEncoderStruct(GP_HammingEncoder,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"print",&i,commandParameter,400)==1) {
	printGP_HammingEncoderStruct(GP_HammingEncoder,"GP_HammingEncoder",0,0);
	continue;
    }

    if (SWRC_matchCommand(command,"setParm",&i,commandParameter,400)==1) {
	setParmGP_HammingEncoderStruct(GP_HammingEncoder,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"checkParm",&i,commandParameter,400)==1) {
	checkParametersGP_HammingEncoder(GP_HammingEncoder);
	continue;
    }

    if (SWRC_matchCommand(command,"precomp",&i,commandParameter,400)==1) {
	precompGP_HammingEncoder(GP_HammingEncoder);
	continue;
    }

    if (SWRC_matchCommand(command,"postcomp",&i,commandParameter,400)==1) {
	postcompGP_HammingEncoder(GP_HammingEncoder,0);
	continue;
    }

    if (SWRC_matchCommand(command,"help",&i,commandParameter,400)==1) {
	helpCommandGP_HammingEncoder(0);
	continue;
    }

    if (SWRC_matchCommand(command,"run",&i,commandParameter,400)==1) {
	runGP_HammingEncoder(GP_HammingEncoder, signal);
	continue;
    }

    printf("processCommandGP_HammingEncoder: Unknown command:%s\n",&command[i]);
    break;
  }
}

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_HammingEncoder (int index) {
  printf("Commands recognized by %d:GP_HammingEncoderStruct:\n",index);
  printf("  \"print();\"        : print the GP_HammingEncoderStruct fields\n");
  printf("  \"setParm(arg);\"   : set the GP_HammingEncoderStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
}

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_HammingEncoder (GP_HammingEncoderStruct *GP_HammingEncoder) {
  int output=0;
  //if (GP_HammingEncoder->N==0) {output++;printf("GP_HammingEncoder->N needed, but not set\n");}
  //if (GP_HammingEncoder->M==0) {output++;printf("GP_HammingEncoder->M needed, but not set\n");}
  //if (GP_HammingEncoder->K==0) {output++;printf("GP_HammingEncoder->K needed, but not set\n");}
  //if (GP_HammingEncoder->R==0.0) {output++;printf("GP_HammingEncoder->R needed, but not set\n");}
  //if (GP_HammingEncoder->trainFlag==0) {output++;printf("GP_HammingEncoder->trainFlag needed, but not set\n");}
  //if (GP_HammingEncoder->N_train==0) {output++;printf("GP_HammingEncoder->N_train needed, but not set\n");}
  //if (GP_HammingEncoder->i_train==0) {output++;printf("GP_HammingEncoder->i_train needed, but not set\n");}
  //if (GP_HammingEncoder->numberOfMult==0) {output++;printf("GP_HammingEncoder->numberOfMult needed, but not set\n");}
  //if (GP_HammingEncoder->aveNoOfMultPerFrame==0.0) {output++;printf("GP_HammingEncoder->aveNoOfMultPerFrame needed, but not set\n");}
  //if (GP_HammingEncoder->numberOfAdd==0) {output++;printf("GP_HammingEncoder->numberOfAdd needed, but not set\n");}
  //if (GP_HammingEncoder->aveNoOfAddPerFrame==0.0) {output++;printf("GP_HammingEncoder->aveNoOfAddPerFrame needed, but not set\n");}
  //if (GP_HammingEncoder->numberOfComp==0) {output++;printf("GP_HammingEncoder->numberOfComp needed, but not set\n");}
  //if (GP_HammingEncoder->aveNoOfCompPerFrame==0.0) {output++;printf("GP_HammingEncoder->aveNoOfCompPerFrame needed, but not set\n");}
  //if (GP_HammingEncoder->simTime==0.0) {output++;printf("GP_HammingEncoder->simTime needed, but not set\n");}
  //if (GP_HammingEncoder->aveSimTimePerFrame==0.0) {output++;printf("GP_HammingEncoder->aveSimTimePerFrame needed, but not set\n");}
  //if (GP_HammingEncoder->numberOfCalls==0) {output++;printf("GP_HammingEncoder->numberOfCalls needed, but not set\n");}
  return(output);
}

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_HammingEncoder (GP_HammingEncoderStruct *GP_HammingEncoder) {
  GP_HammingEncoder->i_train=0;
  GP_HammingEncoder->numberOfMult=0;
  GP_HammingEncoder->aveNoOfMultPerFrame=0.0;
  GP_HammingEncoder->numberOfAdd=0;
  GP_HammingEncoder->aveNoOfAddPerFrame=0.0;
  GP_HammingEncoder->numberOfComp=0;
  GP_HammingEncoder->aveNoOfCompPerFrame=0.0;
  GP_HammingEncoder->simTime=0.0;
  GP_HammingEncoder->aveSimTimePerFrame=0.0;
  GP_HammingEncoder->numberOfCalls=0;
}

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_HammingEncoder (GP_HammingEncoderStruct *GP_HammingEncoder, char finishedFlag) {
  GP_HammingEncoder->aveNoOfMultPerFrame=(double)GP_HammingEncoder->numberOfMult/GP_HammingEncoder->numberOfCalls;
  GP_HammingEncoder->aveNoOfAddPerFrame=(double)GP_HammingEncoder->numberOfAdd/GP_HammingEncoder->numberOfCalls;
  GP_HammingEncoder->aveNoOfCompPerFrame=(double)GP_HammingEncoder->numberOfComp/GP_HammingEncoder->numberOfCalls;
  GP_HammingEncoder->aveSimTimePerFrame=(double)GP_HammingEncoder->simTime/GP_HammingEncoder->numberOfCalls;
}

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_HammingEncoder (GP_HammingEncoderStruct *GP_HammingEncoder) {
  GP_HammingEncoder->i_train=0;
}

// Function called after training. Free allocated memory etc...
void posttrainGP_HammingEncoder (GP_HammingEncoderStruct *GP_HammingEncoder) {
}

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_HammingEncoder (GP_HammingEncoderStruct *GP_HammingEncoder, signalStruct *signal) {
  if ((GP_HammingEncoder->trainFlag&1)==1) { // Training complete, call the run function
    printf("Running GP_HammingEncoder\n");
    runGP_HammingEncoder(GP_HammingEncoder,signal);
    return(1);
  } else {                 // Do the training
    printf("Training GP_HammingEncoder %ld/%ld\n",GP_HammingEncoder->i_train,GP_HammingEncoder->N_train);
    // Accumulate the statistics
    GP_HammingEncoder->i_train++;
    if (GP_HammingEncoder->i_train>=GP_HammingEncoder->N_train) { // Statistics accumulated, post-training computation
      GP_HammingEncoder->trainFlag=1;
    }
    return(0);
  }
}

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_HammingEncoder (GP_HammingEncoderStruct *GP_HammingEncoder,berResultStruct *berResult) {
  //pushBerResultField(berResult,"N","int","%1d",&GP_HammingEncoder->N);
  //pushBerResultField(berResult,"M","int","%1d",&GP_HammingEncoder->M);
  //pushBerResultField(berResult,"K","int","%1d",&GP_HammingEncoder->K);
  //pushBerResultField(berResult,"R","double","%1lf",&GP_HammingEncoder->R);
  //pushBerResultField(berResult,"trainFlag","uint8_t","%9"SCNu8"",&GP_HammingEncoder->trainFlag);
  //pushBerResultField(berResult,"N_train","long int","%7ld",&GP_HammingEncoder->N_train);
  //pushBerResultField(berResult,"i_train","long int","%7ld",&GP_HammingEncoder->i_train);
  //pushBerResultField(berResult,"numberOfMult","long unsigned int","%12lu",&GP_HammingEncoder->numberOfMult);
  //pushBerResultField(berResult,"aveNoOfMultPerFrame","double","%19lf",&GP_HammingEncoder->aveNoOfMultPerFrame);
  //pushBerResultField(berResult,"numberOfAdd","long unsigned int","%11lu",&GP_HammingEncoder->numberOfAdd);
  //pushBerResultField(berResult,"aveNoOfAddPerFrame","double","%18lf",&GP_HammingEncoder->aveNoOfAddPerFrame);
  //pushBerResultField(berResult,"numberOfComp","long unsigned int","%12lu",&GP_HammingEncoder->numberOfComp);
  //pushBerResultField(berResult,"aveNoOfCompPerFrame","double","%19lf",&GP_HammingEncoder->aveNoOfCompPerFrame);
  //pushBerResultField(berResult,"simTime","double","%7lf",&GP_HammingEncoder->simTime);
  //pushBerResultField(berResult,"aveSimTimePerFrame","double","%18lf",&GP_HammingEncoder->aveSimTimePerFrame);
  //pushBerResultField(berResult,"numberOfCalls","long unsigned int","%13lu",&GP_HammingEncoder->numberOfCalls);
}

#define row_B 46
#define column_B 68
#define expFactor 5
#define column_msg_B 22             //size of msg parts in B matrix
#define sizeC (column_B*expFactor)  //size of codeword
#define sizeMsg (expFactor*column_msg_B)

int B[row_B][column_B];
int H[row_B][column_B][expFactor][expFactor];
int H_2D [row_B*expFactor] [column_B*expFactor];
int parity[expFactor];
// int sizeMsg = expFactor*column_msg_B; //Get from make file ->N
int newInput[sizeMsg];

//variables in for loop
int i=0;
int j=0;
int k=0;
int m=0;
int pK=0;
int pM=0;

int syndrome(int codeword[]){

  //This section calculates the syndrome to check validity of final codeword
  //If syndrome is 0, it is a valid codeword
  //If syndrome is 1, it is an invalid codeword

  int column_H = column_B * expFactor;
  int row_H = row_B * expFactor;

  int multiply[column_H], sum_temp[]={};
  int synd[row_H];
  int sum ;

  for (i=0; i<row_H; i++)
    {
      for (j=0; j<column_H; j++)
	{
	  multiply[j] = H_2D[i][j] * codeword[j];
	 	  
	  //printf("\ni: %d ",i);
	}
      //printf("\n\n");
      sum = 0;

      for (k=0; k<column_H; k++)
	{
	  sum = sum + multiply[k]; //Updating
	}

      synd[i] = sum%2;   //perform modulo 2
      //printf("\n%d",synd[i]%2); 
      // if (synd[i] != 0)
      //	{
      //	  //printf("\n\n Invalid Codeword \n\n");
      //	}
      // else
      //{
      //  //printf("\n\n Valid Codeword \n\n");
      //}
    
    }
  int ss=0;
  for(i=0; i<row_H; i++)
    {
      ss+=synd[i];
    }

  // printf("\n\n%d ",ss);
  return ss;

}

//Function to print codeword
void print_codeword(int codeword[]){

  int i;
  
  printf("\n\n--------------------codeword:-------------\n\n");
  for(i=0; i<sizeC; i++)
    {
      printf("%d ", codeword[i]);   
    }

  printf("\n\n-------------Codeword is printed---------------\n\n");
}

//Appending final non-shifted p1 to codeworf
void append_p1(int codeword[]){
  //append p1 to codeword
  for(i=0; i<expFactor; i++)
    {
      codeword[i+sizeMsg] = parity[i];      
      //printf("\n%d",parity[i]); 
    }
  //print_codeword();
}

void rotating_p1(int start, int end){

  while (start < end)
    {
      int temp = parity[start];
      parity[start] = parity[end];
      parity[end] = temp;
      start++;
      end--;
    }
}

//Function to shift p1 and get original p1 bits
void shifting_p1(int n, int z, int codeword[]){

  rotating_p1(0, z-1);
  rotating_p1(0, n-1);
  rotating_p1(n, z-1);

  append_p1(codeword);
}


void get_parity(int newInput[], int codeword[]){

  int m, k, i, j, r, b, q, z=expFactor, sum, bb;
  int product[]={}, prodIM[row_B*z], multiply[z], temp[z], sum_temp[z];


  
  //-------------------P1------------------//
  
  //reset parity array
  for(i=0; i<z; i++)
   {
     parity[i]=0;  //temp
     sum_temp[i] = 0;
   }

  //Finding p1
  for(m=0; m<column_msg_B; m++) //1st x col of H (msg part)
    {
      for(k=0; k<4; k++) //1st 4 rows of B
	{
	  //printf("\nH Col %d ",m);
	  // printf("\nH Row %d ",k);
	  for(i=0; i<z; i++) //First I col... got z bits
	    {
	      //printf("\nI col %d:  ",i);
	      
	      for(j=0; j<z; j++) //First I row... got z bits
		{
		  //printf("%d ",m);
		  
		    temp[j] = newInput[j + m*z];
		      
		    multiply[j] = (temp[j] * H[k][m][i][j] );
	     
		    //printf(" %d", H[k][m][i][j]);
		   //printf("\n");		  		  
		}//j

	      //printf("\n\n");
	       int sum=0;
	       for(r=0; r<z; r++)
	      	{
	        sum = sum + multiply[r]; //value of product of every I*m
	        		
	      	}
	       	     
	       prodIM[i] = sum;
	       sum_temp[i] = sum_temp[i] + prodIM[i];
        			       	      
	    }//i
	  
	   
	}//k
    }//m

   for(int r=0; r<z; r++)
	{
	      
	  parity[r] = sum_temp[r]%2;     //perform modulo 2 
	   //printf("\n %d  ", parity[r]);
	   
	     }
  
   //print_codeword();

   //printf("\n");

  //---------------Reshifting for P1--------------//
  //Now, need to shift the parity[] to get original bits (non-shifted version).
  //Getting value of p1 shift value from B
    int n;

    //Choose such that n is not -1.
    //If value in B is -1, then the H is z-by-z 0 matrix.
    //This causes the p1 to be all 0s because I*p1. Hence, need to choose non -1 value.
    if (B[1][column_msg_B] == -1)  
      { n = B[2][column_msg_B]; }
    else
      { n = B[1][column_msg_B]; }
    //printf("\n%d",z-n-1);
    shifting_p1( n, z, codeword); //shift by n to the right to get original parity bit

    //print_codeword();

    
    
    //-------P2 TO P4-------//

    //reset parity array
      for(i=0; i<z; i++)
      {
	parity[i]=0;
	sum_temp[i] = 0;
      }

      int  cword_temp[(column_B - column_msg_B - 1)*z];  //Initialise temp with size to avoid stack smashing
      
    //traverse by row and Hcolumn in codeword (all msg and one p)
      for(q=0; q<3; q++)  //Only until 3 rows 
	{
      for (m=0; m<column_msg_B+(q+1); m++ ) //all msg columns and p1 column
      {
	//printf("\nm: %d \n",m);
	for (k=0; k<(1+q); k++) 
	  {
	    //printf("\nk: %d ",k);
	    
	    for (i=0; i<z; i++) //I row
	      {
		for (j=0; j<z; j++) //I col
		  {

		    temp[j] = codeword[j + m*z];  //Assign temp to codeword of z index (z=expFactor)
		    //printf("\nm:%d k:%d i:%d   %d ",m,k,i,j+m*z);
		  
		    multiply[j] = (temp[j] * H[k][m][i][j] );  //Individual element multiplication of I and msg bits
		     //printf("%d ",  H[k][m][i][j]);
		     //printf("\nm: %d  k: %d i: %d  j: %d",m,k,i,j);
		  }//j

		//printf("\n");
		//SUm of individual products of I*msg
		int sum=0;
		for(r=0; r<z; r++)
		  {
		    sum = sum + multiply[r]; 		 
		  }
		//printf(" \n %d ",sum);
	      
		prodIM[i] = sum;
	        sum_temp[i] = sum_temp[i] + prodIM[i];  //Summing up values of I*msg to get parity bits
		//printf(" \n %d  %d",m,sum_temp[i]);	           
		
	      }//i
	    	    
		 //printf("\n");
	  }//k

	//append parity bits to temp codeword
	int w;
	for(w=0; w<z; w++)
	  {
	    parity[w] = sum_temp[w];
	    cword_temp[w+q*z] = parity[w];
	    //printf("\nm: %d   %d ",m,w+q*z);
	    //printf("\nk:%d %d",k, cword_temp[(sizeMsg+z) + w + q*z] );	    	    
	  }

      }//m

      //reset arrays before going to next loop
          int y;
	  for(y=0; y<z; y++)
	    {
	      parity[y]=0;
	      prodIM[y]=0;
	      sum_temp[y]=0;
	    }

	}//q

      //Append cword_temp(containing p2-p4) to final codeword
      for(bb=0; bb<(3*z); bb++)
	  {	    
	    codeword[(sizeMsg+z) + bb] = cword_temp[bb]%2; //perform modulo 2
	    //printf("\n %d ",codeword[(sizeMsg+z) + bb]);
	    
	  }
      //print_codeword();
      
    
    //-------P5 TO PN-------//

    //reset parity array
      for(i=0; i<z; i++)
      {
	parity[i]=0;
      }

      int cword_temp2[(column_B - column_msg_B - 4)*z]; //fix stash smashing
           
     //traverse by row and Hcolumn in codeword (all msg bits and p1-p4)
      for(q=0; q<(column_B - column_msg_B - 4); q++)  //<length of parity bits from p5 to pn
	{
	  for (m=0; m<column_msg_B+(q+4); m++ ) 
      {
	//printf("\nm: %d\n ",m);
	for (k=4+q; k<(5+q); k++) //Starts from 5th row
	  {
	    //printf("\nk: %d ",k);
	    
	    for (i=0; i<z; i++) 
	      {
		for (j=0; j<z; j++) 
		  {

		    temp[j] = codeword[j + m*z]; //Assign codeword to temp
		    
		    multiply[j] = (temp[j] * H[k][m][i][j] );  //Multiplying I(from H) with msg bits
		     //printf("%d ", j + m*z);
		     //printf("\nk: %d  m: %d",k,m);
		  }//j

		//printf("\n");
		//Continuing matrix multiplication by summing up the individual product
		int sum=0;
		for(r=0; r<z; r++)
		  {
		    sum = sum + multiply[r]; //value of product of every I*m		 
		  }
		//printf(" \n %d ",sum);
	      
		prodIM[i] = sum;
	        sum_temp[i] = sum_temp[i] + prodIM[i]; //Sum up all the I*msg components to find parity bits
		//printf(" \nm:%d  %d",m,sum_temp[i]);	           
		
	      }//i
	   
	  }//k

	//append parity bits to temp codeword
	int w;
	for(w=0; w<z; w++)
	  {
	    parity[w] = sum_temp[w];
	    cword_temp2[w+q*z] = parity[w];
	    //printf("\nm: %d   %d ",m,w+q*z);
	    //printf("\nk:%d %d",k, cword_temp2[w + q*z] );	    	    
	  }

      }//m

	  //Reset arrays before going into next loop
	  int y; 
	  for(y=0; y<z; y++)
	    {
	      parity[y]=0;
	      prodIM[y]=0;
	      sum_temp[y]=0;
	    }

	}//q

      //append cword_temp array to final codeword starting from p5 index
      for(bb=0; bb< (column_B - column_msg_B - 4) * z; bb++)
	  {	    
	    codeword[(sizeMsg+4*z) + bb] = cword_temp2[bb]%2; //perform modulo 2 operation
	    //printf("\n %d ",(sizeMsg+4*z) + bb);	    
	  }      
    
}//get_parity fx


void initialise_codeword(int newInput[], int codeword[])
{

  int i, j, k;
  

  for(i=0; i<sizeC; i++)
    {
      codeword[i] = 0;
    }

  // int sizeMsg = expFactor*column_msg_B;
  //int sizeMsg = GP_HammingEncoder->K; 

    //Append message or input bits to codeword array
   for (k=0; k<sizeMsg; k++) //row index of input
    {    	
      //printf("\n%d ",k);
	  codeword[k] =newInput[k];
	  //codeword_temp[k] = input[k];
	 
    }

  // get_parity(input);
  
}

void convert(){

  int k, m, i ,j;

   //printf("\n\n-----------------------------------------\n\n");
   //printf("            Converting 4D H to 2D H            ");
   //printf("\n\n-----------------------------------------\n\n");
   
   for (k=0; k<row_B; k++)  //row B
    {
      for (i=0; i<expFactor; i++)
	{
	  for (m=0; m<column_B; m++) //column B
	    {
	      for (j=0; j<expFactor; j++)
		{
		  H_2D[((expFactor-1)*k)+k+i][((expFactor-1)*m)+m+j] = H[k][m][i][j];
		  //printf("\n k:%d m:%d i:%d j:%d index:[%d][%d]   H_old: %d Hnew: %d",k,m,i,j, ((5-1)*k)+k+i, ((5-1)*m)+m+j,  H[k][m][i][j], Hnew[(3*k)+i][(3*m)+j]);
		}
	    }
	}
    }
   //printf("\n\n");

  for (i=0; i<(row_B*expFactor); i++)
    {
      for (j=0; j<(column_B*expFactor); j++)
	{
	  //printf("%d",H_2D[i][j]);
	}
      //printf("\n");
    }

  //printf("\n\n\n Finish converting to 2D H  \n\n\n");

}


 void zeros_matrix()
 {
   for (i=0;i<expFactor;i++)
     {
       for (j=0;j<expFactor;j++)
 	{
 	  if (i==j)
 	    {
 	      H[k][m][i][j]=1;
 	    }
 	  else
 	    {
 	      H[k][m][i][j]=0;
 	    }
 	  //printf("H[%d][%d][%d][%d]: %d\n",k, m, i, j, H[k][m][i][j]);
 	}
     }
 }

void positive_matrix()
 {
   for (i=0;i<expFactor;i++)
     {
       for (j=0;j<expFactor;j++)
 	{
 	  if (i==j)
 	    {
 	      H[k][m][i][j]=1;
 	    }
 	  else
 	    {
 	      H[k][m][i][j]=0;
 	    }
 	  //printf("H[%d][%d][%d][%d]: %d\n",k,m,i,j, H[k][m][i][j]);
 	}

     }
   int n,N, temp;
   N=B[k][m];
   for (n=0;n<N;n++)
    {
        for (i=0;i<expFactor;i++)
        {
            temp=H[pK][pM][i][expFactor-1];
            for (j=expFactor-1;j>0;j--)
            {
                H[k][m][i][j]= H[k][m][i][j-1];
            }
            H[k][m][i][0]= temp;
        }
    }
}


 void negative_matrix()
 {
   for (i=0;i<expFactor;i++)
     {
       for (j=0;j<expFactor;j++)
 	{
 	  H[k][m][i][j]=0;
 	  //To check result of negative numbers
 	  //printf("H[%d][%d][%d][%d]: %d\n",k,m,i,j, H[k][m][i][j]);
 	}
     }
 }

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_HammingEncoder (GP_HammingEncoderStruct *GP_HammingEncoder, signalStruct *signal) {
  int i;
  clock_t beginTime, endTime;
  int N_input,N_output;
  uint8_t *input;
  uint8_t *output;
  beginTime=clock();
  printf("In function runGP_HammingEncoder\n");
  // Allocate memory for 1 more signal. The output of this function should go there.
  // USER NEEDS TO EDIT: the LENGTH of the output vector and the TYPE of
  // the output vector 0=uint8_t, 1=char, 2=int, 3=unsigned int, 4=long unsigned int, 5=float, 6=double
  // The type of the input vector should also be set correctly by the USER.
  N_input  = signal->N[signal->N_N-1];        // Length of the input vector
  input    = (uint8_t*) signal->x[signal->N_N-1]; // Assign pointer to the input memory
  N_output = GP_HammingEncoder->N; // Length of output vector
  output   = (uint8_t*) incrementByOneSignal(signal,N_output,0,"GP_HammingEncoder");    // Create a new output vector on end of signal list
  
  // Computation engine :
  int codeword[sizeC];
   
  //Import base matrix from txt file
  FILE* f;
  f=fopen("NR_1_2_5.txt", "r");
  if (!feof(f))
    {
      for (k=0;k<row_B;k++)
        {
	  for (j=0;j<column_B;j++)
            {
	      fscanf(f, "%d",&B[k][j]);
	      //printf("B[%d][%d]: %d\n", k, j, B[k][j]);
            }
        }
    }
  fclose(f);
  //Check whether the elements is positive, negative or zero
  for (k=0;k<row_B;k++)
    {
      for (m=0;m<column_B;m++)
        {
 	  if (B[k][m]==0)
 	    {
	      zeros_matrix();
 	    }
 	  else if (B[k][m]<0)
 	    {
	      negative_matrix();
 	    }
 	  else if (B[k][m]>0)
	    {
	      //printf("B[%d][%d]=%d is positive\n", k, m, B[k][m]);
	      pK=k;
	      pM=m;
	      positive_matrix();
	      //printf("K: %d, M=%d\n", pK, pM);
 	    }
 	}
    }
   
  for (i=0;i<sizeMsg;i++)
    {
      newInput[i]= (int) input[i];
    }
  initialise_codeword(newInput, codeword);
  //print_codeword(codeword);
  get_parity(newInput, codeword); //Calculate parity bits
  convert();                   //Convert 4D H to 2D H
  // print_codeword(codeword);
    // //write H into text file
   FILE * file;
   file = fopen ("H_matrix2.txt", "w+");
   int row_H=row_B*expFactor;
   int column_H=column_B*expFactor;
   for (k=0;k<row_H;k++)
     {
       for (m=0;m<column_H;m++)
	 {
	   fprintf(file, "%d ", H_2D[k][m]);
	 }
       fprintf(file, "\n");
     }
   fclose(file);
   printf("Done write\n");
  // int check = syndrome(codeword);  
  //To check for valid codeword

  // if (check == 0)
  //   {
  //     printf("\n\nValue of check is : %d ",check);
  //     printf("\n\nCodeword is Valid\n\n\n");
  //   }
  // else
  //   {
  //     printf("\n\nValue of check is : %d ",check);
  //     printf("\n\nCodeword is Invalid\n\n\n");
  //   }

  //Codeword=output
  for(i=0; i<N_output; i++)
    {
      output[i] = (uint8_t) codeword[i];
    }
  
  // Save the time for the computation engine
  endTime = clock();
  GP_HammingEncoder->simTime+=(double)(endTime-beginTime)/CLOCKS_PER_SEC;
  GP_HammingEncoder->numberOfCalls++;
}


