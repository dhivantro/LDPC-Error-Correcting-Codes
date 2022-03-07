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

#ifndef GP_HAMMINGENCODER_H
#define GP_HAMMINGENCODER_H
#include "../../SWRC.h"


typedef struct GP_HammingEncoderStruct {
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
///////////////////////////////////////////////////////////////////////////////////////////////////////////
  int N;                              // codeword length (in bits)
  int M;                              // # Number of Parity Check bits
  int K;                              // # Number of message bits
  double R;                           // # rate of this code
///////////////////////////////////////////////////////////////////////
// Fields automatically included in every module that request $args{i}
///////////////////////////////////////////////////////////////////////
  uint8_t trainFlag;                  // Flag indicating training status
  long int N_train;                   // # training iterations
  long int i_train;                   // Training counter
  long unsigned int numberOfMult;     // Number of multiplications for the module
  double aveNoOfMultPerFrame;         // Average number of multiplications per frame
  long unsigned int numberOfAdd;      // Number of additions for the module
  double aveNoOfAddPerFrame;          // Average number of additions per frame
  long unsigned int numberOfComp;     // Number of compares for the module
  double aveNoOfCompPerFrame;         // Average number of compares per frame
  double simTime;                     // Total time for running the current module's compute engine
  double aveSimTimePerFrame;          // Average simulation time per frame
  long unsigned int numberOfCalls;    // Number of times this subroutine is called
} GP_HammingEncoderStruct;

typedef struct arrayGP_HammingEncoderStruct {
  GP_HammingEncoderStruct *x;
  long unsigned int N_x;
} arrayGP_HammingEncoderStruct;

typedef struct doubleArrayGP_HammingEncoderStruct {
  GP_HammingEncoderStruct **x;
  long unsigned int *N_x;
  long unsigned int N_N_x;
} doubleArrayGP_HammingEncoderStruct;

// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder);

// Frees up all the memory in the structure
void freeGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder);

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder, char *name, int index, int pre);

// Store random values into the fields of GP_HammingEncoderStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder);

// Initialize an array of GP_HammingEncoderStruct's to sane starting values
void initArrayGP_HammingEncoderStruct(arrayGP_HammingEncoderStruct *GP_HammingEncoder);

// Allocate memory for an array of N GP_HammingEncoderStruct's
void allocateArrayGP_HammingEncoderStruct(arrayGP_HammingEncoderStruct *GP_HammingEncoder,int N);

// Free an array of GP_HammingEncoderStruct's
void freeArrayGP_HammingEncoderStruct(arrayGP_HammingEncoderStruct *GP_HammingEncoder);

// Fill the arrayGP_HammingEncoderStruct with random values.
// The GP_HammingEncoder->N_GP_HammingEncoder parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_HammingEncoderStruct(arrayGP_HammingEncoderStruct *GP_HammingEncoder);

// Print arrayGP_HammingEncoderStruct
void printArrayGP_HammingEncoderStruct(arrayGP_HammingEncoderStruct *GP_HammingEncoder);

// Initialize a double array of GP_HammingEncoderStruct to sane startup values
void initDoubleArrayGP_HammingEncoderStruct(doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder);

// Allocate memory for a rectangular double array of GP_HammingEncoderStruct
void allocateDoubleArrayGP_HammingEncoderStruct(doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder, int N, int M);

// Free a double array of GP_HammingEncoderStruct's
void freeDoubleArrayGP_HammingEncoderStruct(doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder);

// Print arrayGP_HammingEncoderStruct
void printDoubleArrayGP_HammingEncoderStruct(doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder, char *name, int index, int pre);

// Plot function generates any plots associated with the 
// structure
void plotGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder, const char *filename);

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile);

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile);

// Pack the contents of arrayGP_HammingEncoderStruct to a uint8_vector
void packArrayGP_HammingEncoderStruct(arrayGP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile);

// Unpack the contents of arrayGP_HammingEncoderStruct from a uint8_vector.
void unpackArrayGP_HammingEncoderStruct(arrayGP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile);

// Pack the contents of doubleArrayGP_HammingEncoderStruct to a uint8_vector
void packDoubleArrayGP_HammingEncoderStruct(doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile);

// Unpack the contents of doubleArrayGP_HammingEncoderStruct from a uint8_vector
void unpackDoubleArrayGP_HammingEncoderStruct(doubleArrayGP_HammingEncoderStruct *GP_HammingEncoder, uint8_vector *cfgFile);

// Function for loading the struct
int loadGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder, char *filename);

// Function for saving the struct
void saveGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder, char *filename);

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_HammingEncoderStruct(GP_HammingEncoderStruct *GP_HammingEncoder, char *arg);

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_HammingEncoder(GP_HammingEncoderStruct *GP_HammingEncoder, signalStruct *signal, const char *command);

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_HammingEncoder(int index);

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_HammingEncoder(GP_HammingEncoderStruct *GP_HammingEncoder);

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_HammingEncoder(GP_HammingEncoderStruct *GP_HammingEncoder);

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_HammingEncoder(GP_HammingEncoderStruct *GP_HammingEncoder, char finishedFlag);

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_HammingEncoder(GP_HammingEncoderStruct *GP_HammingEncoder);

// Function called after training. Free allocated memory etc...
void posttrainGP_HammingEncoder(GP_HammingEncoderStruct *GP_HammingEncoder);

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_HammingEncoder(GP_HammingEncoderStruct *GP_HammingEncoder, signalStruct *signal);

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_HammingEncoder(GP_HammingEncoderStruct *GP_HammingEncoder,berResultStruct *berResult);

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_HammingEncoder(GP_HammingEncoderStruct *GP_HammingEncoder, signalStruct *signal);

#endif
