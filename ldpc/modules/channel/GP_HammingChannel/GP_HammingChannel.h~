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

#ifndef GP_HAMMINGCHANNEL_H
#define GP_HAMMINGCHANNEL_H
#include "../../SWRC.h"


typedef struct GP_HammingChannelStruct {
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
///////////////////////////////////////////////////////////////////////////////////////////////////////////
  int N;                              // Number of bits being written to the channel
  double R;                           // # rate of the code being used over the channel
  double SNR;                         // # The SNR of the noise on the AWGN channel
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
} GP_HammingChannelStruct;

typedef struct arrayGP_HammingChannelStruct {
  GP_HammingChannelStruct *x;
  long unsigned int N_x;
} arrayGP_HammingChannelStruct;

typedef struct doubleArrayGP_HammingChannelStruct {
  GP_HammingChannelStruct **x;
  long unsigned int *N_x;
  long unsigned int N_N_x;
} doubleArrayGP_HammingChannelStruct;

// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel);

// Frees up all the memory in the structure
void freeGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel);

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel, char *name, int index, int pre);

// Store random values into the fields of GP_HammingChannelStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel);

// Initialize an array of GP_HammingChannelStruct's to sane starting values
void initArrayGP_HammingChannelStruct(arrayGP_HammingChannelStruct *GP_HammingChannel);

// Allocate memory for an array of N GP_HammingChannelStruct's
void allocateArrayGP_HammingChannelStruct(arrayGP_HammingChannelStruct *GP_HammingChannel,int N);

// Free an array of GP_HammingChannelStruct's
void freeArrayGP_HammingChannelStruct(arrayGP_HammingChannelStruct *GP_HammingChannel);

// Fill the arrayGP_HammingChannelStruct with random values.
// The GP_HammingChannel->N_GP_HammingChannel parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_HammingChannelStruct(arrayGP_HammingChannelStruct *GP_HammingChannel);

// Print arrayGP_HammingChannelStruct
void printArrayGP_HammingChannelStruct(arrayGP_HammingChannelStruct *GP_HammingChannel);

// Initialize a double array of GP_HammingChannelStruct to sane startup values
void initDoubleArrayGP_HammingChannelStruct(doubleArrayGP_HammingChannelStruct *GP_HammingChannel);

// Allocate memory for a rectangular double array of GP_HammingChannelStruct
void allocateDoubleArrayGP_HammingChannelStruct(doubleArrayGP_HammingChannelStruct *GP_HammingChannel, int N, int M);

// Free a double array of GP_HammingChannelStruct's
void freeDoubleArrayGP_HammingChannelStruct(doubleArrayGP_HammingChannelStruct *GP_HammingChannel);

// Print arrayGP_HammingChannelStruct
void printDoubleArrayGP_HammingChannelStruct(doubleArrayGP_HammingChannelStruct *GP_HammingChannel, char *name, int index, int pre);

// Plot function generates any plots associated with the 
// structure
void plotGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel, const char *filename);

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile);

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile);

// Pack the contents of arrayGP_HammingChannelStruct to a uint8_vector
void packArrayGP_HammingChannelStruct(arrayGP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile);

// Unpack the contents of arrayGP_HammingChannelStruct from a uint8_vector.
void unpackArrayGP_HammingChannelStruct(arrayGP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile);

// Pack the contents of doubleArrayGP_HammingChannelStruct to a uint8_vector
void packDoubleArrayGP_HammingChannelStruct(doubleArrayGP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile);

// Unpack the contents of doubleArrayGP_HammingChannelStruct from a uint8_vector
void unpackDoubleArrayGP_HammingChannelStruct(doubleArrayGP_HammingChannelStruct *GP_HammingChannel, uint8_vector *cfgFile);

// Function for loading the struct
int loadGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel, char *filename);

// Function for saving the struct
void saveGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel, char *filename);

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_HammingChannelStruct(GP_HammingChannelStruct *GP_HammingChannel, char *arg);

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_HammingChannel(GP_HammingChannelStruct *GP_HammingChannel, signalStruct *signal, const char *command);

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_HammingChannel(int index);

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_HammingChannel(GP_HammingChannelStruct *GP_HammingChannel);

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_HammingChannel(GP_HammingChannelStruct *GP_HammingChannel);

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_HammingChannel(GP_HammingChannelStruct *GP_HammingChannel, char finishedFlag);

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_HammingChannel(GP_HammingChannelStruct *GP_HammingChannel);

// Function called after training. Free allocated memory etc...
void posttrainGP_HammingChannel(GP_HammingChannelStruct *GP_HammingChannel);

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_HammingChannel(GP_HammingChannelStruct *GP_HammingChannel, signalStruct *signal);

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_HammingChannel(GP_HammingChannelStruct *GP_HammingChannel,berResultStruct *berResult);

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_HammingChannel(GP_HammingChannelStruct *GP_HammingChannel, signalStruct *signal);

#endif
