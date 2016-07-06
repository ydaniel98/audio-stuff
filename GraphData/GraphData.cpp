/*
* Author: Edwin Daniel Penalo
* Date: NO IDEA
* This program takes a .data file and outputs a pdf file with the
* graph
*/

/*
* Include
*/
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <string>
#include <stdint.h>
#include <fstream>
#include "../Commun/sysCommands.h"
/**/

/*
* Define
*/
// For the sake of OCD
#define FILE_NAME               fileName
// For the sake of readability - Data file path/name
#define DATA_FILE               dataFileName
// Plotter file (.sh) (bash code)
#define PLOTTER                 plotterFileName

// PDF file merger command (OSX only)
#define PDF_MERGE_FILE_CMD      "/System/Library/Automator/Combine\\ PDF\\ Pages.action/Contents/Resources/join.py -o"
// Convinience buffer file to generate the pdf graph file
#define BUFFER_PDF_FILE_NAME    "./graph_data_file_pdf_buffer"

// Log messages
#define LOG_ERR_USAGE           "Usage: <dataFile> <plotter>"
#define LOG_ERR_DATA_FILE       "Could not find data file "
#define LOG_GET_MAX_TIME        "Getting max time from data file"
#define LOG_PLOT_RANGE          "Plotting Range: "
#define LOG_MERGE               "Merging files..."
#define LOG_STEP                "Finding Step"
/**/

/*
* Name Spaces
*/
using namespace std;
/**/

/*
* Variables
*/
// Status check for the file being used
struct stat s;

// Multi-purpouse buffer
string buffer;
// Small buffer
char cbuff;

// Time position on the graph
float t;

// Dump file name (pdf)
string fileName;
// Data file to plot
fstream dataFile;

float plottingStep;
bool plottingStepOption;

string dataFileName;
string plotterFileName;

uint8_t paramsCounter;

bool optionsError;
bool parsingError;
/**/

int main(int argc, char * argv[]) {

  /*
  * Parsing
  */

  if (argc < 3) {
    cout << LOG_ERR_USAGE << endl;
    return 1;
  }

  for (uint8_t i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      // Possible option
      if (argv[i][1] == 'p') {
        plottingStep = (float) atof(argv[i + 1]);
        plottingStepOption = true;
      } else {
        optionsError = true;
        parsingError = true;
        break;
      }
      i++;
    } else {
      switch (paramsCounter) {
        case 0:
          dataFileName = argv[i];
          break;
        case 1:
          plotterFileName = argv[i];
          break;
      }
      paramsCounter++;
    }
  }

  if (paramsCounter < 2)
    parsingError = true;

  if (optionsError) {
    cout << "Invalid Option" << endl;
    return 1;
  }

  if (parsingError) {
    cout << "Parsing Error: Invalid Input" << endl;
    return 1;
  }

  /**/

  if (stat(DATA_FILE.c_str(), &s) == -1) {
    cout << LOG_ERR_DATA_FILE << DATA_FILE << endl;
    return 1;
  }

  /*
  * Init variables
  */
  buffer = "";
  cbuff = 0;
  fileName = "";

  if (!plottingStepOption)
    plottingStep = 1.6;
  /**/

  /*
  * Get the name of the pdf graph file
  */
  for (uint8_t i = string(DATA_FILE).size(); i > 0; i--) {
    if (DATA_FILE[i] == '.') {
      cbuff = i;
      break;
    }
  }

  for (uint8_t i = 0; i < cbuff; i++)
    FILE_NAME += DATA_FILE[i];

  FILE_NAME += SYS_EXTENSION_PDF;
  cout << FILE_NAME << endl;
  /**/

  /*
  * Create the final pdf file
  */
  buffer = SYS_TOUCH;
  buffer += FILE_NAME;
  system(buffer.c_str());
  /**/

  // Open the data file
  dataFile.open(DATA_FILE);

  /*
  * Find the max value of x
  */

  cout << LOG_GET_MAX_TIME << endl;

  dataFile.seekg(-1, ios_base::end);
  dataFile.seekg(-1, ios::cur);

  while (dataFile.get() != '\n') {
    dataFile.seekg(-2, ios::cur);
  }

  cbuff = dataFile.get();
  buffer = cbuff;

  while ((((cbuff - '0') >= 0) && ((cbuff - '0') <= 9)) || cbuff == '.') {
    cbuff = dataFile.get();
    buffer += cbuff;
  }

  t = (float)atof(buffer.c_str());
  cout << to_string(t) << endl;
  /**/

  uint8_t count = 0;

  for (float i = 0; i < t; i += plottingStep + 0.1) {
    cout << LOG_PLOT_RANGE << i << ':' << i + plottingStep << endl;
    /*
    * Plot with gnuplot
    */

    buffer = "";

    buffer += SYS_SOURCE;
    buffer += PLOTTER;
    buffer += SYS_SPACE;
    buffer += DATA_FILE;
    buffer += SYS_PLOT_FORMAT;
    buffer += BUFFER_PDF_FILE_NAME;
    buffer += SYS_LINE;
    buffer += to_string(count);
    buffer += SYS_EXTENSION_PDF;
    buffer += " [";
    buffer += to_string(i);
    buffer += ":";
    buffer += to_string(i + plottingStep);
    buffer += "]";

    count++;

    system((buffer).c_str());
    /**/
  }

  /*
  * Merge the files with the user specified file
  */
  buffer = PDF_MERGE_FILE_CMD;
  buffer += FILE_NAME;
  buffer += SYS_SPACE;
  for (uint8_t j = 0; j < count; j++) {
    buffer += BUFFER_PDF_FILE_NAME;
    buffer += SYS_LINE;
    buffer += to_string(j);
    buffer += SYS_EXTENSION_PDF;
    buffer += SYS_SPACE;
  }
  cout << LOG_MERGE << endl;
  system(buffer.c_str());
  /**/

  /*
  * Clean Up
  */
  for (uint8_t j = 0; j < count; j++) {
    buffer = SYS_RM;
    buffer += BUFFER_PDF_FILE_NAME;
    buffer += SYS_LINE;
    buffer += to_string(j);
    buffer += SYS_EXTENSION_PDF;
    buffer += SYS_SPACE;
    system(buffer.c_str());
  }
  /**/

  buffer = SYS_OPEN;
  buffer += FILE_NAME;
  system(buffer.c_str());

  return 0;
}
