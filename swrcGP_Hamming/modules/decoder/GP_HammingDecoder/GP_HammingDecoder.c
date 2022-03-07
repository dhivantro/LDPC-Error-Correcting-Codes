// Software Recording Channel (SWRC) platform in C.
// Name      : GP_HammingDecoder
// Type      : module.
// Path      : modules/decoder/GP_HammingDecoder
// Dependency: 
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Mon Sep 13 16:36:54 2021
// Comment   : The first-trial (7,4) Hamming encoder for the group project 
//             team 

#include "GP_HammingDecoder.h"
// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder) {
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  GP_HammingDecoder->N                = 0;
  GP_HammingDecoder->M                = 0;
  GP_HammingDecoder->K                = 0;
  GP_HammingDecoder->R                = 0.0;
// Fields automatically included in every module that request $args{i}
  GP_HammingDecoder->trainFlag        = 0;
  GP_HammingDecoder->N_train          = 0;
  GP_HammingDecoder->i_train          = 0;
  GP_HammingDecoder->numberOfMult     = 0;
  GP_HammingDecoder->aveNoOfMultPerFrame = 0.0;
  GP_HammingDecoder->numberOfAdd      = 0;
  GP_HammingDecoder->aveNoOfAddPerFrame = 0.0;
  GP_HammingDecoder->numberOfComp     = 0;
  GP_HammingDecoder->aveNoOfCompPerFrame = 0.0;
  GP_HammingDecoder->simTime          = 0.0;
  GP_HammingDecoder->aveSimTimePerFrame = 0.0;
  GP_HammingDecoder->numberOfCalls    = 0;
}

// Frees up all the memory in the structure
void freeGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder) {
  if (GP_HammingDecoder==NULL) {printf("GP_HammingDecoder=NULL in function freeGP_HammingDecoderStruct not free'ing\n");return;}
  int i;
  GP_HammingDecoder->N          =0;
  GP_HammingDecoder->M          =0;
  GP_HammingDecoder->K          =0;
  GP_HammingDecoder->R          =0.0;
  GP_HammingDecoder->trainFlag  =0;
  GP_HammingDecoder->N_train    =0;
  GP_HammingDecoder->i_train    =0;
  GP_HammingDecoder->numberOfMult=0;
  GP_HammingDecoder->aveNoOfMultPerFrame=0.0;
  GP_HammingDecoder->numberOfAdd=0;
  GP_HammingDecoder->aveNoOfAddPerFrame=0.0;
  GP_HammingDecoder->numberOfComp=0;
  GP_HammingDecoder->aveNoOfCompPerFrame=0.0;
  GP_HammingDecoder->simTime    =0.0;
  GP_HammingDecoder->aveSimTimePerFrame=0.0;
  GP_HammingDecoder->numberOfCalls=0;
  //free(GP_HammingDecoder);GP_HammingDecoder=NULL;
}

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder, char *name, int index, int pre) {
  int i,j;
  char *preString,*name2;
  if (GP_HammingDecoder==NULL) {printf("%s%s=NULL\n",preString,name);return;}
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  printf("%s[--%d:%s--------\n",preString,index,name);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
    printf("%s  int                  %s->N=%d\n",preString,name,GP_HammingDecoder->N);                 // Print int N
    printf("%s  int                  %s->M=%d\n",preString,name,GP_HammingDecoder->M);                 // Print int M
    printf("%s  int                  %s->K=%d\n",preString,name,GP_HammingDecoder->K);                 // Print int K
    printf("%s  double               %s->R=%lf\n",preString,name,GP_HammingDecoder->R);                // Print double R
// Fields automatically included in every module that request $args{i}
    printf("%s  uint8_t              %s->trainFlag=%"SCNu8"\n",preString,name,GP_HammingDecoder->trainFlag); // Print uint8_t trainFlag
    printf("%s  long int             %s->N_train=%ld\n",preString,name,GP_HammingDecoder->N_train);    // Print long int N_train
    printf("%s  long int             %s->i_train=%ld\n",preString,name,GP_HammingDecoder->i_train);    // Print long int i_train
    printf("%s  long unsigned int    %s->numberOfMult=%lu\n",preString,name,GP_HammingDecoder->numberOfMult); // Print long unsigned int numberOfMult
    printf("%s  double               %s->aveNoOfMultPerFrame=%lf\n",preString,name,GP_HammingDecoder->aveNoOfMultPerFrame); // Print double aveNoOfMultPerFrame
    printf("%s  long unsigned int    %s->numberOfAdd=%lu\n",preString,name,GP_HammingDecoder->numberOfAdd); // Print long unsigned int numberOfAdd
    printf("%s  double               %s->aveNoOfAddPerFrame=%lf\n",preString,name,GP_HammingDecoder->aveNoOfAddPerFrame); // Print double aveNoOfAddPerFrame
    printf("%s  long unsigned int    %s->numberOfComp=%lu\n",preString,name,GP_HammingDecoder->numberOfComp); // Print long unsigned int numberOfComp
    printf("%s  double               %s->aveNoOfCompPerFrame=%lf\n",preString,name,GP_HammingDecoder->aveNoOfCompPerFrame); // Print double aveNoOfCompPerFrame
    printf("%s  double               %s->simTime=%lf\n",preString,name,GP_HammingDecoder->simTime);    // Print double simTime
    printf("%s  double               %s->aveSimTimePerFrame=%lf\n",preString,name,GP_HammingDecoder->aveSimTimePerFrame); // Print double aveSimTimePerFrame
    printf("%s  long unsigned int    %s->numberOfCalls=%lu\n",preString,name,GP_HammingDecoder->numberOfCalls); // Print long unsigned int numberOfCalls
  printf("%s---%d:%s-------]\n",preString,index,name);
  free(preString);
}

// Store random values into the fields of GP_HammingDecoderStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder) {
  int idum=1;SWRC_randomize(&idum);
  //GP_HammingDecoder->N=rand();
  //GP_HammingDecoder->M=rand();
  //GP_HammingDecoder->K=rand();
  //GP_HammingDecoder->R=ran2(&idum);
}

// Initialize an array of GP_HammingDecoderStruct's to sane starting values
void initArrayGP_HammingDecoderStruct (arrayGP_HammingDecoderStruct *GP_HammingDecoder) {
  GP_HammingDecoder->N_x=0;
  GP_HammingDecoder->x=NULL;
}

// Allocate memory for an array of N GP_HammingDecoderStruct's
void allocateArrayGP_HammingDecoderStruct (arrayGP_HammingDecoderStruct *GP_HammingDecoder,int N) {
  int i;
  GP_HammingDecoder->N_x=N;
  GP_HammingDecoder->x = (GP_HammingDecoderStruct*)realloc(GP_HammingDecoder->x,N*sizeof(GP_HammingDecoderStruct));
  for (i=0;i<GP_HammingDecoder->N_x;i++) {
    initGP_HammingDecoderStruct(&GP_HammingDecoder->x[i]);
  }
}

// Free an array of GP_HammingDecoderStruct's
void freeArrayGP_HammingDecoderStruct (arrayGP_HammingDecoderStruct *GP_HammingDecoder) {
  if (GP_HammingDecoder==NULL) {printf("GP_HammingDecoder=NULL in function freeArrayGP_HammingDecoderStruct not free'ing\n");return;}
  int i;
  for (i=0;i<GP_HammingDecoder->N_x;i++) {
    freeGP_HammingDecoderStruct(&GP_HammingDecoder->x[i]);
  } free(GP_HammingDecoder->x);GP_HammingDecoder->x=NULL;
}

// Fill the arrayGP_HammingDecoderStruct with random values.
// The GP_HammingDecoder->N_GP_HammingDecoder parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_HammingDecoderStruct (arrayGP_HammingDecoderStruct *GP_HammingDecoder) {
  int i;
  for (i=0;i<GP_HammingDecoder->N_x;i++) randomizeGP_HammingDecoderStruct(&GP_HammingDecoder->x[i]);
}

// Print arrayGP_HammingDecoderStruct
void printArrayGP_HammingDecoderStruct (arrayGP_HammingDecoderStruct *GP_HammingDecoder) {
  int i;
  for (i=0;i<GP_HammingDecoder->N_x;i++) {
    printGP_HammingDecoderStruct(&GP_HammingDecoder->x[i],"GP_HammingDecoder",i,0);
  }
}

// Initialize a double array of GP_HammingDecoderStruct to sane startup values
void initDoubleArrayGP_HammingDecoderStruct (doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder) {
  GP_HammingDecoder->N_N_x=0;
  GP_HammingDecoder->N_x=NULL;
  GP_HammingDecoder->x=NULL;
}

// Allocate memory for a rectangular double array of GP_HammingDecoderStruct
void allocateDoubleArrayGP_HammingDecoderStruct (doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder, int N, int M) {
  int i,j;
  GP_HammingDecoder->N_N_x=N;
  GP_HammingDecoder->N_x=(long unsigned int*)realloc(GP_HammingDecoder->N_x,N*sizeof(long unsigned int));
  for (i=0;i<GP_HammingDecoder->N_N_x;i++) GP_HammingDecoder->N_x[i]=M;
  GP_HammingDecoder->x=(GP_HammingDecoderStruct**)realloc(GP_HammingDecoder->x,N*sizeof(GP_HammingDecoderStruct*));
  for (i=0;i<GP_HammingDecoder->N_N_x;i++) {
    GP_HammingDecoder->x[i]=(GP_HammingDecoderStruct*)calloc(M,sizeof(GP_HammingDecoderStruct));
  for(j=0;j<GP_HammingDecoder->N_x[i];j++) initGP_HammingDecoderStruct(&GP_HammingDecoder->x[i][j]);
  }
}

// Free a double array of GP_HammingDecoderStruct's
void freeDoubleArrayGP_HammingDecoderStruct (doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder) {
  int i;
  for (i=0;i<GP_HammingDecoder->N_N_x;i++) {
    if (GP_HammingDecoder->x[i]!=NULL) free(GP_HammingDecoder->x[i]);
  }
  free(GP_HammingDecoder->N_x);GP_HammingDecoder->N_x=NULL;
  free(GP_HammingDecoder->x);GP_HammingDecoder->x=NULL;
}

// Print arrayGP_HammingDecoderStruct
void printDoubleArrayGP_HammingDecoderStruct (doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder, char *name, int index, int pre) {
}

// Plot function generates any plots associated with the 
// structure
void plotGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder, const char *filename) {
}

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile) {
  int i;
 //Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Pack int N
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->N,1,sizeof(int),cfgFile);
  // Pack int M
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->M,1,sizeof(int),cfgFile);
  // Pack int K
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->K,1,sizeof(int),cfgFile);
  // Pack double R
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->R,1,sizeof(double),cfgFile);
 //Fields automatically included in every module that request $args{i}
  // Pack uint8_t trainFlag
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Pack long int N_train
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->N_train,1,sizeof(long int),cfgFile);
  // Pack long int i_train
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->i_train,1,sizeof(long int),cfgFile);
  // Pack long unsigned int numberOfMult
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfMultPerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfAdd
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfAddPerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfComp
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfCompPerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Pack double simTime
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->simTime,1,sizeof(double),cfgFile);
  // Pack double aveSimTimePerFrame
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfCalls
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile) {
  int i;
  freeGP_HammingDecoderStruct(GP_HammingDecoder);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Unpack int N
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->N,1,sizeof(int),cfgFile);
  // Unpack int M
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->M,1,sizeof(int),cfgFile);
  // Unpack int K
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->K,1,sizeof(int),cfgFile);
  // Unpack double R
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->R,1,sizeof(double),cfgFile);
// Fields automatically included in every module that request $args{i}
  // Unpack uint8_t trainFlag
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Unpack long int N_train
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->N_train,1,sizeof(long int),cfgFile);
  // Unpack long int i_train
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->i_train,1,sizeof(long int),cfgFile);
  // Unpack long unsigned int numberOfMult
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfMultPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfAdd
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfAddPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfComp
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfCompPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Unpack double simTime
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->simTime,1,sizeof(double),cfgFile);
  // Unpack double aveSimTimePerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfCalls
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// Pack the contents of arrayGP_HammingDecoderStruct to a uint8_vector
void packArrayGP_HammingDecoderStruct (arrayGP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile) {
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_HammingDecoder->x,GP_HammingDecoder->N_x,sizeof(GP_HammingDecoderStruct),cfgFile);
}

// Unpack the contents of arrayGP_HammingDecoderStruct from a uint8_vector.
void unpackArrayGP_HammingDecoderStruct (arrayGP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile) {
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->N_x,1,sizeof(long unsigned int),cfgFile);
  GP_HammingDecoder->x = (GP_HammingDecoderStruct*)realloc(GP_HammingDecoder->x,GP_HammingDecoder->N_x*sizeof(GP_HammingDecoderStruct));
  SWRC_unpackFromUint8((uint8_t*)GP_HammingDecoder->x,GP_HammingDecoder->N_x,sizeof(GP_HammingDecoderStruct),cfgFile);
}

// Pack the contents of doubleArrayGP_HammingDecoderStruct to a uint8_vector
void packDoubleArrayGP_HammingDecoderStruct (doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile) {
  int i;
  SWRC_packToUint8((uint8_t*)&GP_HammingDecoder->N_N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_HammingDecoder->N_x,GP_HammingDecoder->N_N_x,sizeof(long unsigned int),cfgFile);
  for (i=0;i<GP_HammingDecoder->N_N_x;i++) 
    SWRC_packToUint8((uint8_t*)GP_HammingDecoder->x[i],GP_HammingDecoder->N_x[i],sizeof(GP_HammingDecoderStruct),cfgFile);
}

// Unpack the contents of doubleArrayGP_HammingDecoderStruct from a uint8_vector
void unpackDoubleArrayGP_HammingDecoderStruct (doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile) {
  int i;
  SWRC_unpackFromUint8((uint8_t*)&GP_HammingDecoder->N_N_x,1,sizeof(long unsigned int),cfgFile);
  // allocate memory for and unpack GP_HammingDecoder->N_GP_HammingDecoder
  GP_HammingDecoder->N_x=(long unsigned int*) realloc(GP_HammingDecoder->N_x,GP_HammingDecoder->N_N_x*sizeof(long unsigned int));
  SWRC_unpackFromUint8((uint8_t*)GP_HammingDecoder->N_x,GP_HammingDecoder->N_N_x,sizeof(long unsigned int),cfgFile);
  // allocate memory for GP_HammingDecoder->GP_HammingDecoder
  GP_HammingDecoder->x=(GP_HammingDecoderStruct**)realloc(GP_HammingDecoder->x,GP_HammingDecoder->N_N_x*sizeof(GP_HammingDecoderStruct*));
  for (i=0;i<GP_HammingDecoder->N_N_x;i++) {
    SWRC_unpackFromUint8((uint8_t*)GP_HammingDecoder->x[i],GP_HammingDecoder->N_x[i],sizeof(GP_HammingDecoderStruct),cfgFile);
  }
}

// Function for loading the struct
int loadGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder, char *filename) {
}

// Function for saving the struct
void saveGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder, char *filename) {
}

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_HammingDecoderStruct (GP_HammingDecoderStruct *GP_HammingDecoder, char *arg) {
  int i;
  SWRC_removeSpaces(arg);
   if (SWRC_readSingleArgumentFromString(arg,"N",&GP_HammingDecoder->N,"%d")==1) {
     printf("N=%d\n",GP_HammingDecoder->N);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"M",&GP_HammingDecoder->M,"%d")==1) {
  //   printf("M=%d\n",GP_HammingDecoder->M);
  // }
   if (SWRC_readSingleArgumentFromString(arg,"K",&GP_HammingDecoder->K,"%d")==1) {
     printf("K=%d\n",GP_HammingDecoder->K);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"R",&GP_HammingDecoder->R,"%lf")==1) {
  //   printf("R=%lf\n",GP_HammingDecoder->R);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"trainFlag",&GP_HammingDecoder->trainFlag,"%"SCNu8"")==1) {
  //   printf("trainFlag=%"SCNu8"\n",GP_HammingDecoder->trainFlag);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"N_train",&GP_HammingDecoder->N_train,"%ld")==1) {
  //   printf("N_train=%ld\n",GP_HammingDecoder->N_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"i_train",&GP_HammingDecoder->i_train,"%ld")==1) {
  //   printf("i_train=%ld\n",GP_HammingDecoder->i_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfMult",&GP_HammingDecoder->numberOfMult,"%lu")==1) {
  //   printf("numberOfMult=%lu\n",GP_HammingDecoder->numberOfMult);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfMultPerFrame",&GP_HammingDecoder->aveNoOfMultPerFrame,"%lf")==1) {
  //   printf("aveNoOfMultPerFrame=%lf\n",GP_HammingDecoder->aveNoOfMultPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfAdd",&GP_HammingDecoder->numberOfAdd,"%lu")==1) {
  //   printf("numberOfAdd=%lu\n",GP_HammingDecoder->numberOfAdd);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfAddPerFrame",&GP_HammingDecoder->aveNoOfAddPerFrame,"%lf")==1) {
  //   printf("aveNoOfAddPerFrame=%lf\n",GP_HammingDecoder->aveNoOfAddPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfComp",&GP_HammingDecoder->numberOfComp,"%lu")==1) {
  //   printf("numberOfComp=%lu\n",GP_HammingDecoder->numberOfComp);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfCompPerFrame",&GP_HammingDecoder->aveNoOfCompPerFrame,"%lf")==1) {
  //   printf("aveNoOfCompPerFrame=%lf\n",GP_HammingDecoder->aveNoOfCompPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"simTime",&GP_HammingDecoder->simTime,"%lf")==1) {
  //   printf("simTime=%lf\n",GP_HammingDecoder->simTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveSimTimePerFrame",&GP_HammingDecoder->aveSimTimePerFrame,"%lf")==1) {
  //   printf("aveSimTimePerFrame=%lf\n",GP_HammingDecoder->aveSimTimePerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfCalls",&GP_HammingDecoder->numberOfCalls,"%lu")==1) {
  //   printf("numberOfCalls=%lu\n",GP_HammingDecoder->numberOfCalls);
  // }
  if (*arg!='\0') {
    printf("GP_HammingDecoder module: Remaining unknown parms in arg list:%s\n Please correct and run again.\n",arg);exit(-1);
  }
}

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_HammingDecoder (GP_HammingDecoderStruct *GP_HammingDecoder, signalStruct *signal, const char *command) {
  char commandParameter[400];
  int i;
  printf("processCommandGP_HammingDecoder:%s\n",command);
  for(i=0;i<400 && i<strlen(command);) {
    if (SWRC_matchCommand(command,"load",&i,commandParameter,400)==1) {
	loadGP_HammingDecoderStruct(GP_HammingDecoder,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"print",&i,commandParameter,400)==1) {
	printGP_HammingDecoderStruct(GP_HammingDecoder,"GP_HammingDecoder",0,0);
	continue;
    }

    if (SWRC_matchCommand(command,"setParm",&i,commandParameter,400)==1) {
	setParmGP_HammingDecoderStruct(GP_HammingDecoder,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"checkParm",&i,commandParameter,400)==1) {
	checkParametersGP_HammingDecoder(GP_HammingDecoder);
	continue;
    }

    if (SWRC_matchCommand(command,"precomp",&i,commandParameter,400)==1) {
	precompGP_HammingDecoder(GP_HammingDecoder);
	continue;
    }

    if (SWRC_matchCommand(command,"postcomp",&i,commandParameter,400)==1) {
	postcompGP_HammingDecoder(GP_HammingDecoder,0);
	continue;
    }

    if (SWRC_matchCommand(command,"help",&i,commandParameter,400)==1) {
	helpCommandGP_HammingDecoder(0);
	continue;
    }

    if (SWRC_matchCommand(command,"run",&i,commandParameter,400)==1) {
	runGP_HammingDecoder(GP_HammingDecoder, signal);
	continue;
    }

    printf("processCommandGP_HammingDecoder: Unknown command:%s\n",&command[i]);
    break;
  }
}

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_HammingDecoder (int index) {
  printf("Commands recognized by %d:GP_HammingDecoderStruct:\n",index);
  printf("  \"print();\"        : print the GP_HammingDecoderStruct fields\n");
  printf("  \"setParm(arg);\"   : set the GP_HammingDecoderStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
}

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_HammingDecoder (GP_HammingDecoderStruct *GP_HammingDecoder) {
  int output=0;
  //if (GP_HammingDecoder->N==0) {output++;printf("GP_HammingDecoder->N needed, but not set\n");}
  //if (GP_HammingDecoder->M==0) {output++;printf("GP_HammingDecoder->M needed, but not set\n");}
  //if (GP_HammingDecoder->K==0) {output++;printf("GP_HammingDecoder->K needed, but not set\n");}
  //if (GP_HammingDecoder->R==0.0) {output++;printf("GP_HammingDecoder->R needed, but not set\n");}
  //if (GP_HammingDecoder->trainFlag==0) {output++;printf("GP_HammingDecoder->trainFlag needed, but not set\n");}
  //if (GP_HammingDecoder->N_train==0) {output++;printf("GP_HammingDecoder->N_train needed, but not set\n");}
  //if (GP_HammingDecoder->i_train==0) {output++;printf("GP_HammingDecoder->i_train needed, but not set\n");}
  //if (GP_HammingDecoder->numberOfMult==0) {output++;printf("GP_HammingDecoder->numberOfMult needed, but not set\n");}
  //if (GP_HammingDecoder->aveNoOfMultPerFrame==0.0) {output++;printf("GP_HammingDecoder->aveNoOfMultPerFrame needed, but not set\n");}
  //if (GP_HammingDecoder->numberOfAdd==0) {output++;printf("GP_HammingDecoder->numberOfAdd needed, but not set\n");}
  //if (GP_HammingDecoder->aveNoOfAddPerFrame==0.0) {output++;printf("GP_HammingDecoder->aveNoOfAddPerFrame needed, but not set\n");}
  //if (GP_HammingDecoder->numberOfComp==0) {output++;printf("GP_HammingDecoder->numberOfComp needed, but not set\n");}
  //if (GP_HammingDecoder->aveNoOfCompPerFrame==0.0) {output++;printf("GP_HammingDecoder->aveNoOfCompPerFrame needed, but not set\n");}
  //if (GP_HammingDecoder->simTime==0.0) {output++;printf("GP_HammingDecoder->simTime needed, but not set\n");}
  //if (GP_HammingDecoder->aveSimTimePerFrame==0.0) {output++;printf("GP_HammingDecoder->aveSimTimePerFrame needed, but not set\n");}
  //if (GP_HammingDecoder->numberOfCalls==0) {output++;printf("GP_HammingDecoder->numberOfCalls needed, but not set\n");}
  return(output);
}

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_HammingDecoder (GP_HammingDecoderStruct *GP_HammingDecoder) {
  GP_HammingDecoder->i_train=0;
  GP_HammingDecoder->numberOfMult=0;
  GP_HammingDecoder->aveNoOfMultPerFrame=0.0;
  GP_HammingDecoder->numberOfAdd=0;
  GP_HammingDecoder->aveNoOfAddPerFrame=0.0;
  GP_HammingDecoder->numberOfComp=0;
  GP_HammingDecoder->aveNoOfCompPerFrame=0.0;
  GP_HammingDecoder->simTime=0.0;
  GP_HammingDecoder->aveSimTimePerFrame=0.0;
  GP_HammingDecoder->numberOfCalls=0;
}

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_HammingDecoder (GP_HammingDecoderStruct *GP_HammingDecoder, char finishedFlag) {
  GP_HammingDecoder->aveNoOfMultPerFrame=(double)GP_HammingDecoder->numberOfMult/GP_HammingDecoder->numberOfCalls;
  GP_HammingDecoder->aveNoOfAddPerFrame=(double)GP_HammingDecoder->numberOfAdd/GP_HammingDecoder->numberOfCalls;
  GP_HammingDecoder->aveNoOfCompPerFrame=(double)GP_HammingDecoder->numberOfComp/GP_HammingDecoder->numberOfCalls;
  GP_HammingDecoder->aveSimTimePerFrame=(double)GP_HammingDecoder->simTime/GP_HammingDecoder->numberOfCalls;
}

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_HammingDecoder (GP_HammingDecoderStruct *GP_HammingDecoder) {
  GP_HammingDecoder->i_train=0;
}

// Function called after training. Free allocated memory etc...
void posttrainGP_HammingDecoder (GP_HammingDecoderStruct *GP_HammingDecoder) {
}

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_HammingDecoder (GP_HammingDecoderStruct *GP_HammingDecoder, signalStruct *signal) {
  if ((GP_HammingDecoder->trainFlag&1)==1) { // Training complete, call the run function
    printf("Running GP_HammingDecoder\n");
    runGP_HammingDecoder(GP_HammingDecoder,signal);
    return(1);
  } else {                 // Do the training
    printf("Training GP_HammingDecoder %ld/%ld\n",GP_HammingDecoder->i_train,GP_HammingDecoder->N_train);
    // Accumulate the statistics
    GP_HammingDecoder->i_train++;
    if (GP_HammingDecoder->i_train>=GP_HammingDecoder->N_train) { // Statistics accumulated, post-training computation
      GP_HammingDecoder->trainFlag=1;
    }
    return(0);
  }
}

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_HammingDecoder (GP_HammingDecoderStruct *GP_HammingDecoder,berResultStruct *berResult) {
  //pushBerResultField(berResult,"N","int","%1d",&GP_HammingDecoder->N);
  //pushBerResultField(berResult,"M","int","%1d",&GP_HammingDecoder->M);
  //pushBerResultField(berResult,"K","int","%1d",&GP_HammingDecoder->K);
  //pushBerResultField(berResult,"R","double","%1lf",&GP_HammingDecoder->R);
  //pushBerResultField(berResult,"trainFlag","uint8_t","%9"SCNu8"",&GP_HammingDecoder->trainFlag);
  //pushBerResultField(berResult,"N_train","long int","%7ld",&GP_HammingDecoder->N_train);
  //pushBerResultField(berResult,"i_train","long int","%7ld",&GP_HammingDecoder->i_train);
  //pushBerResultField(berResult,"numberOfMult","long unsigned int","%12lu",&GP_HammingDecoder->numberOfMult);
  //pushBerResultField(berResult,"aveNoOfMultPerFrame","double","%19lf",&GP_HammingDecoder->aveNoOfMultPerFrame);
  //pushBerResultField(berResult,"numberOfAdd","long unsigned int","%11lu",&GP_HammingDecoder->numberOfAdd);
  //pushBerResultField(berResult,"aveNoOfAddPerFrame","double","%18lf",&GP_HammingDecoder->aveNoOfAddPerFrame);
  //pushBerResultField(berResult,"numberOfComp","long unsigned int","%12lu",&GP_HammingDecoder->numberOfComp);
  //pushBerResultField(berResult,"aveNoOfCompPerFrame","double","%19lf",&GP_HammingDecoder->aveNoOfCompPerFrame);
  //pushBerResultField(berResult,"simTime","double","%7lf",&GP_HammingDecoder->simTime);
  //pushBerResultField(berResult,"aveSimTimePerFrame","double","%18lf",&GP_HammingDecoder->aveSimTimePerFrame);
  //pushBerResultField(berResult,"numberOfCalls","long unsigned int","%13lu",&GP_HammingDecoder->numberOfCalls);
}

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_HammingDecoder (GP_HammingDecoderStruct *GP_HammingDecoder, signalStruct *signal) {
  int i,c,c1,c2,c3;
  clock_t beginTime, endTime;
  int N_input,N_output;
  uint8_t *input;
  uint8_t *output;
  beginTime=clock();
  printf("In function runGP_HammingDecoder\n");
  // Allocate memory for 1 more signal. The output of this function should go there.
  // USER NEEDS TO EDIT: the LENGTH of the output vector and the TYPE of
  // the output vector 0=uint8_t, 1=char, 2=int, 3=unsigned int, 4=long unsigned int, 5=float, 6=double
  // The type of the input vector should also be set correctly by the USER.
  N_input  = signal->N[signal->N_N-1];        // Length of the input vector
  input    = (uint8_t*) signal->x[signal->N_N-1]; // Assign pointer to the input memory
  N_output = GP_HammingDecoder->N;                               // Length of output vector
  output   = (uint8_t*) incrementByOneSignal(signal,N_output,0,"GP_HammingDecoder");    // Create a new output vector on end of signal list
  
  // Computation engine :

   //for debugging purposes
  

  // printf("\n\n %d \n\n",input[5]);
   
  c1=input[4]^input[0]^input[1]^input[2];
  c2=input[5]^input[0]^input[2]^input[3];
  c3=input[6]^input[0]^input[1]^input[3];

  c=c3*4 + c2*2 +c1; //finding the error position i think

  if(c1==0){
    printf("\n\n\n NO ERROR \n\n\n");
  }

  for (i=0; i<N_output; i++){
    
    //output[i]=input[i];
  }
  
  //for debugging
  printAllSignals(signal); exit(-1);
  
   
  
  // Save the time for the computation engine
  endTime = clock();
  GP_HammingDecoder->simTime+=(double)(endTime-beginTime)/CLOCKS_PER_SEC;
  GP_HammingDecoder->numberOfCalls++;
}


