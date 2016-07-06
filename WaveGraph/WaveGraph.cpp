/*
/ Author: Edwin Daniel Penalo
/ Date: NO IDEA
/ This progam generates a .data file that can be used to plot a .wav
/ file
*/

/*
/ Include
*/
#include <Wave.hpp>
#include <iostream>
#include <stdint.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <string>
/**/

/*
/ Namespaces
*/
using namespace std;
/**/

/*
/ Define
*/
#define LOG_ERR_USAGE 					"Usage: WaveGraph <Wave file> <Wave data dump file> <samples>"
#define LOG_ERR_INPUT 					"Invalid Input"
#define LOG_ERR_OPTION 					"Invalid Option(s)"
#define LOG_ERR_SAMPLES 				"Samples can't be more than 0xFFF"
#define LOG_ERR_MISSING_FILE 		"Could not find "
#define LOG_ERR_BITS_PER_SAMPLE "Only 16 bits per sample and lower is supported"
#define LOG_ERR_CHANNEL					"Invalid channel"
/**/

/*
/	Variables
*/
// Seconds var to print the current second
uint16_t seconds;
// Position for pointer in the Wav file
uint64_t pos;
// Step count
uint64_t dataStepPos;
// Max value for the min-max algorithm
int16_t minVal;
// Min value for the min-max algorithm
int16_t maxVal;

// Position of buffer (End position after reading .wav file)
uint32_t buffPos;
// Buffer for the data dumps
int16_t buff[0xFFF];

// Step for the x of graph
float dataStep;

// Data dump file
fstream dumpsFile;
// Wave file
fstream waveFile;

// Parameter counter for parsing
uint8_t paramsCounter;

// Status of the file being used
struct stat s;

// Name of Wave file to be analyze
string nameOfWav;
// File name where data is for graph is going to be put
string dumpsFileName;

// Samples for the minVal maxVal thing
uint32_t samples;

// Time option flag
bool timeOption;
// Time option value
uint16_t timeLimit;

// Channel option
bool channelOption;
// Selected Channel for the output
uint8_t channelSelect;

// Option error
bool optionErr;
bool maxLast;
/**/


int main(int argc, char * argv[]) {

	/*
	/ Input Params Parsing
	*/

	if (argc < 4) {

			cout << LOG_ERR_USAGE << endl;
			return 1;

	}

	for (uint8_t i = 1; i < argc; i++) {
		/*
		/ Check for options
		*/
		if (string(argv[i]) == string("-t")) {
			timeOption = true;

			if ((i + 1) < argc) {
				i++;
			} else {
				optionErr = true;
				break;
			}

			timeLimit = stoi(argv[i]);

			if (timeLimit == 0) {
				timeLimit = stoi(argv[i], 0, 16);
			}
			continue;
		}

		if (string(argv[i]) == string("-c")) {
			channelOption = true;

			if ((i + 1) < argc) {
				i++;
			} else {
				optionErr = true;
				break;
			}

			channelSelect = stoi(argv[i]);
			continue;
		}
		/**/

		// No valid option cought
		if (argv[i][0] == '-') {
			optionErr = true;
			break;
		}

		switch (paramsCounter) {
			case 0:
				nameOfWav = argv[i];
				paramsCounter++;
				break;
			case 1:
				dumpsFileName = argv[i];
				paramsCounter++;
				break;
			case 2:
				samples = stoi(string(argv[i]));
				paramsCounter++;
				break;
		}
	}

	if (paramsCounter < 2) {
		cout << LOG_ERR_INPUT << endl;
		return 1;
	}

	if (optionErr) {
		cout << LOG_ERR_OPTION << endl;
		return 1;
	}

	if (samples > 0xFFF) {
		cout << LOG_ERR_SAMPLES;
		return 1;
	}

	if (!channelOption)
		channelSelect = 0;

	/**/

	if (stat(nameOfWav.c_str(), &s) == -1) {
		cout << LOG_ERR_MISSING_FILE << nameOfWav << endl;
		return 1;
	}

	waveFile.open(nameOfWav);

	Wave wave(waveFile);

	// cout << "File Size: " << to_string(wave.fileSize) << endl;
	// cout << "Data Lenght: " << to_string(wave.dataLength) << endl;
	// cout << "Format: " << to_string(wave.format) << endl;
	// cout << "Channels: " << to_string(wave.channels) << endl;
	// cout << "Sample Rate: " << to_string(wave.sampleRate) << endl;
	// cout << "Bits Per Sample: " << to_string(wave.bitsPerSample) << endl;
	// cout << "Data Size: " << to_string(wave.dataSize) << endl;

	if (wave.bitsPerSample > 16) {
		cout << LOG_ERR_BITS_PER_SAMPLE << endl;
		return 1;
	}

	if (channelSelect > (wave.channels - 1)) {
		cout << LOG_ERR_CHANNEL << endl;
		return 1;
	}

	dataStepPos = 0;
	dataStep = 1.0 / wave.sampleRate;

	pos += (wave.bitsPerSample / 8) * channelSelect;

	dumpsFile.open(dumpsFileName, ios::out);

	while (!waveFile.eof()) {

		/*
		* minVal maxVal Algorithm
		*/
		pos = wave.readSoundDataAtStep(buff, samples, pos, &buffPos, (uint8_t)(wave.channels - 1));

		maxVal = buff[0];
		minVal = buff[1];

		if (maxVal < minVal) {
			/*
			* Switch the values
			*/
			maxVal = buff[1];
			minVal = buff[0];
			/**/
		}

		cout << buff[0] << endl;
		cout << buff[1] << endl;

		for (uint16_t i = 2; i < buffPos; i++) {

			cout << buff[i] << endl;

			if (buff[i] > maxVal) {
				maxVal = buff[i];
				maxLast = true;
			}

			if (buff[i] < minVal) {
				minVal = buff[i];
				maxLast = false;
			}

		}

		buffPos = 0;
		/**/

		/*
		* Write the data to the dumps file
		*/
		dumpsFile << to_string(dataStep * dataStepPos) << ' ';
		dataStepPos += samples / 2;

		dumpsFile << (maxLast ? minVal : maxVal) << '\n';

		dumpsFile << to_string(dataStep * dataStepPos) << ' ';
		dataStepPos += samples / 2;

		dumpsFile << (maxLast ? maxVal : minVal) << '\n';
		/**/

		if ((uint16_t)(dataStepPos * dataStep) > seconds) {
			seconds = (uint16_t(dataStepPos * dataStep));
			cout << seconds << "s ";
		}

		if (timeOption) {
			if ((dataStep * dataStepPos) >= timeLimit)
				goto quit;
		}
	}

		quit:
			cout << endl;
			waveFile.close();
			return 0;
}
