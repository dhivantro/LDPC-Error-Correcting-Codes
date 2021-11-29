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

#ifndef GP_HAMMINGDECODER_H
#define GP_HAMMINGDECODER_H
#include "../../SWRC.h"


typedef struct GP_HammingDecoderStruct {
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
} GP_HammingDecoderStruct;

typedef struct arrayGP_HammingDecoderStruct {
  GP_HammingDecoderStruct *x;
  long unsigned int N_x;
} arrayGP_HammingDecoderStruct;

typedef struct doubleArrayGP_HammingDecoderStruct {
  GP_HammingDecoderStruct **x;
  long unsigned int *N_x;
  long unsigned int N_N_x;
} doubleArrayGP_HammingDecoderStruct;

// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder);

// Frees up all the memory in the structure
void freeGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder);

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder, char *name, int index, int pre);

// Store random values into the fields of GP_HammingDecoderStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder);

// Initialize an array of GP_HammingDecoderStruct's to sane starting values
void initArrayGP_HammingDecoderStruct(arrayGP_HammingDecoderStruct *GP_HammingDecoder);

// Allocate memory for an array of N GP_HammingDecoderStruct's
void allocateArrayGP_HammingDecoderStruct(arrayGP_HammingDecoderStruct *GP_HammingDecoder,int N);

// Free an array of GP_HammingDecoderStruct's
void freeArrayGP_HammingDecoderStruct(arrayGP_HammingDecoderStruct *GP_HammingDecoder);

// Fill the arrayGP_HammingDecoderStruct with random values.
// The GP_HammingDecoder->N_GP_HammingDecoder parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_HammingDecoderStruct(arrayGP_HammingDecoderStruct *GP_HammingDecoder);

// Print arrayGP_HammingDecoderStruct
void printArrayGP_HammingDecoderStruct(arrayGP_HammingDecoderStruct *GP_HammingDecoder);

// Initialize a double array of GP_HammingDecoderStruct to sane startup values
void initDoubleArrayGP_HammingDecoderStruct(doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder);

// Allocate memory for a rectangular double array of GP_HammingDecoderStruct
void allocateDoubleArrayGP_HammingDecoderStruct(doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder, int N, int M);

// Free a double array of GP_HammingDecoderStruct's
void freeDoubleArrayGP_HammingDecoderStruct(doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder);

// Print arrayGP_HammingDecoderStruct
void printDoubleArrayGP_HammingDecoderStruct(doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder, char *name, int index, int pre);

// Plot function generates any plots associated with the 
// structure
void plotGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder, const char *filename);

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile);

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile);

// Pack the contents of arrayGP_HammingDecoderStruct to a uint8_vector
void packArrayGP_HammingDecoderStruct(arrayGP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile);

// Unpack the contents of arrayGP_HammingDecoderStruct from a uint8_vector.
void unpackArrayGP_HammingDecoderStruct(arrayGP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile);

// Pack the contents of doubleArrayGP_HammingDecoderStruct to a uint8_vector
void packDoubleArrayGP_HammingDecoderStruct(doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile);

// Unpack the contents of doubleArrayGP_HammingDecoderStruct from a uint8_vector
void unpackDoubleArrayGP_HammingDecoderStruct(doubleArrayGP_HammingDecoderStruct *GP_HammingDecoder, uint8_vector *cfgFile);

// Function for loading the struct
int loadGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder, char *filename);

// Function for saving the struct
void saveGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder, char *filename);

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_HammingDecoderStruct(GP_HammingDecoderStruct *GP_HammingDecoder, char *arg);

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_HammingDecoder(GP_HammingDecoderStruct *GP_HammingDecoder, signalStruct *signal, const char *command);

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_HammingDecoder(int index);

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_HammingDecoder(GP_HammingDecoderStruct *GP_HammingDecoder);

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_HammingDecoder(GP_HammingDecoderStruct *GP_HammingDecoder);

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_HammingDecoder(GP_HammingDecoderStruct *GP_HammingDecoder, char finishedFlag);

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_HammingDecoder(GP_HammingDecoderStruct *GP_HammingDecoder);

// Function called after training. Free allocated memory etc...
void posttrainGP_HammingDecoder(GP_HammingDecoderStruct *GP_HammingDecoder);

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_HammingDecoder(GP_HammingDecoderStruct *GP_HammingDecoder, signalStruct *signal);

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_HammingDecoder(GP_HammingDecoderStruct *GP_HammingDecoder,berResultStruct *berResult);

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_HammingDecoder(GP_HammingDecoderStruct *GP_HammingDecoder, signalStruct *signal);

#endif
