/*
/ Author: Edwin Daniel Penalo
/ Date: NO IDEA
/ This program combines multiple resources to create and
/ display the graph of a .wav file
*/

/*
/ Include
*/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdint.h>
#include "../Commun/sysCommands.h"
/**/

/*
/ Define
*/
// Wave file directory/name
#define WAVE_FILE           argv[wavPos]

// Log Messages
#define LOG_ERR_USAGE       "Usage: <wave file> <samples>"
#define LOG_ERR_WAVE_GRAPH  "wave_graph return exit code 1"
#define LOG_ERR_OPTION      "Invalid option "

/**/

/*
/ Name Spaces
*/
using namespace std;
/**/

/*
/ Varaibles
*/
// Parameter Counter for Parsing
uint8_t paramsCounter;
// Position of the wave file in the parameters input
uint8_t wavPos;

// String Buffer for the system commands
string buffer;
// Convinience buffer
uint8_t cbuff;

// Keeps track of the data (.data) file
string dataFileName;
// Keeps track of the samples to use for the graph of the sound file
uint16_t samples;

// Flag for options error
bool optionsErr;
/**/

int main(int argc, char * argv[]) {

  if (argc < 2) {
    // Program requieres a .wav input file
    cout << LOG_ERR_USAGE << endl;
    return 1;
  }

  /*
  / Variable Init
  */
  samples       = 50;
  dataFileName  = "";
  optionsErr    = false;
  paramsCounter = 0;
  wavPos        = 0;
  /**/

  /*
  / Parse Options
  */
  for (uint8_t i = 1; i < argc; i++) {

    if (string(argv[i]) == string(SYS_SAMPLE_OPTION)) {
      if ((i + 1) < argc) {
        i++;
      } else {
        optionsErr = true;
        buffer     = argv[i];
        break;
      }
      samples       = stoi(argv[i]);
    }

    if (argv[i][0] == '-') {
      optionsErr = true;
      break;
    }

    if (paramsCounter == 0) {
      wavPos = i;
      paramsCounter++;
    }
  }
  /**/

  /*
  / Error Handling
  */
  if (optionsErr) {
    cout << LOG_ERR_OPTION << buffer << endl;
    return 1;
  }
  /**/

  /*
  / Get Name for ouput file (DATA)
  */
  for (int8_t i = string(WAVE_FILE).size(); i > 0; i--) {
    // Get the start Position for the file extention (.wav)
    if (WAVE_FILE[i] == '.') {
      cbuff = i;
      break;
    }
  }

  // Get the name of the file excluding the file extention
  for (uint8_t i = 0; i < cbuff; i++)
    dataFileName += WAVE_FILE[i];

  // Add extention .data to the data file
  dataFileName += SYS_EXTENSION_DATA;
  /**/

  /*
  / Generate the graph data
  */
  buffer = SYS_WAVE_GRAPH;
  buffer += WAVE_FILE;
  buffer += SYS_SPACE;
  buffer += dataFileName;
  buffer += SYS_SPACE;
  buffer += to_string(samples);

  if (system(buffer.c_str()) == 1) {
      cout << LOG_ERR_WAVE_GRAPH << endl;
      return 1;
  }
  /**/

  /*
  / Draw the data
  */
  buffer = SYS_GRAPH_DATA;
  buffer += dataFileName;
  buffer += SYS_SPACE;
  buffer += SYS_GNU_PLOT;

  if (system(buffer.c_str()) == 1) {
      cout << LOG_ERR_WAVE_GRAPH << endl;
      return 1;
  }
  /**/

  return 0;
}
