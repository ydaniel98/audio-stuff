#ifndef FFT_TEST_H
#define FFT_TEST_H

#include <fftw3.h>
#include <iostream>
#include <sys/stat.h>
#include <complex>
#include <cstring>
#include <mutex>
#include <cmath>
#include "Wave.hpp"

using namespace std;

#define WAVE_PATH "../Sounds/330.wav"
#define SIZE 0xFF

fstream waveFile;
struct stat s;

int16_t soundData[SIZE];
uint32_t pos;

fftw_complex out[SIZE];
double in[SIZE];
fftw_plan p;

// mutex mtx;

int main(int argc, char * argv[]) {

	waveFile.open(WAVE_PATH);

	if (stat(WAVE_PATH, &s) == -1) {
		cout << "Could not find the file" << endl;
		return 1;
	}

	Wave wave(waveFile);

	cout << "Sample Rate: " << to_string(wave.sampleRate) << endl;
	cout << "Bits per sample: " << to_string(wave.bitsPerSample) << endl;
	cout << "Channels: " << to_string(wave.channels) << endl;

	wave.readSoundDataAtStep<int16_t>(soundData, SIZE, 0, &pos, wave.channels - 1);

	for (uint8_t i = 0; i < SIZE; i++) {
		in[i] = (double) soundData[i];
	}

	cout << "About to perform fft analysis... Please dont crash" << endl;

	p = fftw_plan_dft_r2c_1d(SIZE, in, out, FFTW_ESTIMATE);

	cout << "About to execute: p = " << to_string(p == NULL) << endl;

	fftw_execute(p);

	cout << endl << "IN" << endl;
	for (uint8_t i = 0; i < SIZE; i++) {
		cout << to_string(soundData[i]) << ", ";
	}

	cout << endl << "OUT" << endl;
	for (uint8_t i = 0; i < SIZE; i++) {

		double xComp = pow(out[i][0], 2);
		double yComp = pow(out[i][1], 2);

		// cout << "X Comp: " << to_string(xComp) << endl;
		// cout << "Y Comp: " << to_string(yComp) << endl;

		// cout << "Frequency: " << to_string(sqrt(xComp + yComp)) << endl;

		double frequency = sqrt(xComp + yComp);
		cout << to_string(44100 * i / SIZE) << " " << to_string(frequency) << endl;
	}

	fftw_destroy_plan(p);

	waveFile.close();

	return 0;
}

#endif
