#ifndef FFT_TEST_H
#define FFT_TEST_H

#include <fftw3.h>
#include <iostream>
#include <sys/stat.h>
#include "Wave.hpp"

#define WAVE_PATH "../Sounds/330.wav"

fstream waveFile;
struct stat s;

int main(char * argv[], int argc) {

	wavFile.open(WAVE_PATH);



	wavFile.close();

	return 0;
}

#endif
