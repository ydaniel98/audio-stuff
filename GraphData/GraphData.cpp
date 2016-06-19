/*
/ Author: Edwin Daniel Penalo
/ Date: NO IDEA
/ This program takes a .data file and outputs a pdf file with the
/ graph
*/

/*
/ Include
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
/ Define
*/
// For the sake of OCD
#define FILE_NAME               fileName
// For the sake of readability - Data file path/name
#define DATA_FILE               argv[1]
// Plotter file (.sh) (bash code)
#define PLOTTER                 argv[2]

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
uint16_t t;

// Dump file name (pdf)
string fileName;
// Data file to plot
fstream dataFile;
/**/

int main(int argc, char * argv[]) {

  if (argc < 3) {
    cout << LOG_ERR_USAGE << endl;
    return 1;
  }

  if (stat(DATA_FILE, &s) == -1) {
    cout << LOG_ERR_DATA_FILE << DATA_FILE << endl;
    return 1;
  }

  /*
  / Init variables
  */
  buffer = "";
  cbuff = 0;
  fileName = "";
  /**/

  /*
  / Get the name of the pdf graph file
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
  / Create the final pdf file
  */
  buffer = SYS_TOUCH;
  buffer += FILE_NAME;
  system(buffer.c_str());
  /**/

  // Open the data file
  dataFile.open(DATA_FILE);

  /*
  / Find the max value of x
  */

  cout << LOG_GET_MAX_TIME << endl;

  dataFile.seekg(-1, ios_base::end);
  dataFile.seekg(-1, ios::cur);

  while (dataFile.get() != '\n') {
    dataFile.seekg(-2, ios::cur);
  }

  cbuff = dataFile.get();
  buffer = cbuff;

  while (cbuff != '.' || (((cbuff - '0') > 0) && ((cbuff - '0') < 9))) {
    cbuff = dataFile.get();
    buffer += cbuff;
  }
  t = (uint16_t)stoi(buffer);
  /**/

  uint8_t count = 0;

  for (float i = 0; i < t; i += 1.7) {
    cout << LOG_PLOT_RANGE << i << ':' << i + 1.6 << endl;
    /*
    / Plot with gnuplot
    */
    // source <plotter (.sh file)> <data file (.data)> pdf
    // <buffer file>-count.pdf [i:1.6]
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
    buffer += to_string(i + 1.6);
    buffer += "]";

    count++;

    system((buffer).c_str());
    /**/
  }

  /*
  / Merge the files with the user specified file
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
  / Clean Up
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
