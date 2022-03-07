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

#include "../modules/SWRC.h"
#include "../modules/encoder/GP_HammingEncoder/GP_HammingEncoder.h"
#include "../modules/channel/GP_HammingChannel/GP_HammingChannel.h"
#include "../modules/decoder/GP_HammingDecoder/GP_HammingDecoder.h"
typedef struct swrcGP_HammingStruct {
///////////////////////////////
// Channel module substructures
///////////////////////////////
  GP_HammingEncoderStruct GP_HammingEncoder; // Structure for GP_HammingEncoder
  GP_HammingChannelStruct GP_HammingChannel; // Structure for GP_HammingChannel
  GP_HammingDecoderStruct GP_HammingDecoder; // Structure for GP_HammingDecoder
///////////////////////////////
// General housekeeping fields
///////////////////////////////
  time_t startTime;                   // Start time of the simulation
  time_t endTime;                     // End time of the simulation
  time_t runTime;                     // run time of the simulation
  char startTimeString[26];           // The start time in string format
  char endTimeString[26];             // The end time in string format
  char CPID[99];                      // computer/process ID
  int dumpEvery;                      // dump to berResult file every dumpEvery secs
/////////////////////////////////////
// Fields for running the simulation
/////////////////////////////////////
  int K;                              // Length of user word before coding 
  int M;                              // Number of parity check bits 
  int N;                              // Length of code word after coding 
  int numberOfFrames;                 // Number of frames executed in the simulation
  int numberOfFrameErrors;            // Number of frame errors found in the simulation
  int minNumberOfFrames;              // minimum number of frames before terminate simulation
  int minNumberOfFrameErrors;         // minimum number of frame errors before terminate simulation
  int maxNumberOfFrames;              // maximum number of frames before terminate simulation
  long int numberOfBits;              // Number of bits passed through the channel
  int numberOfBitErrors;              // Number of bit errors found during the simulation
  double BER;                         // Bit error rate
  double FER;                         // Frame error rate
  signalStruct signal;                // Signals passed from one module to the next
  } swrcGP_HammingStruct;

// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initSwrcGP_HammingStruct(swrcGP_HammingStruct *swrcGP_Hamming);

// Frees up all the memory in the structure
void freeSwrcGP_HammingStruct(swrcGP_HammingStruct *swrcGP_Hamming);

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printSwrcGP_HammingStruct(swrcGP_HammingStruct *swrcGP_Hamming, char *name, int index, int pre);

// Plot function generates any plots associated with the 
// structure
void plotSwrcGP_HammingStruct(swrcGP_HammingStruct *swrcGP_Hamming, const char *filename);

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packSwrcGP_HammingStruct(swrcGP_HammingStruct *swrcGP_Hamming, uint8_vector *cfgFile);

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackSwrcGP_HammingStruct(swrcGP_HammingStruct *swrcGP_Hamming, uint8_vector *cfgFile);

// Function for loading the struct
int loadSwrcGP_HammingStruct(swrcGP_HammingStruct *swrcGP_Hamming, char *filename);

// Function for saving the struct
void saveSwrcGP_HammingStruct(swrcGP_HammingStruct *swrcGP_Hamming, char *filename);

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmSwrcGP_HammingStruct(swrcGP_HammingStruct *swrcGP_Hamming, char *arg);

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming, signalStruct *signal, const char *command);

// Provides instructions on the commands that this module is able to process.
void helpCommandSwrcGP_Hamming(int index);

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming);

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming);

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming, char finishedFlag);

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming);

// Function called after training. Free allocated memory etc...
void posttrainSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming);

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file. 
void trainSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming);

// Count the BER/FER between 2 signals in the signal struct
// obi is the original bit index 
// dbi is the detected bit index
void countBERSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming,int obi, int dbi);

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming,berResultStruct *berResult,char *berResultFilename);

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runSwrcGP_Hamming(swrcGP_HammingStruct *swrcGP_Hamming);

