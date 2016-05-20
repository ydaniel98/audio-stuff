#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "Wave.h"

Wave wave;
fstream file;
char buffer[10];

int main(void) {

	file.open("330.wav");

	snprintf(buffer, sizeof(buffer), "%02x", wave.getFileSize(file));
	cout << "File Size: 0x" << buffer << endl;

	snprintf(buffer, sizeof(buffer), "%d", wave.getDataLength(file));
	cout << "Length of Data: " << buffer << endl;

	snprintf(buffer, sizeof(buffer), "%d", wave.getFormat(file));
	cout << "Format: " << buffer << endl;

	snprintf(buffer, sizeof(buffer), "%d", wave.getChannels(file));
	cout << "Channels: " << buffer << endl;

	snprintf(buffer, sizeof(buffer), "%d", wave.getSampleRate(file));
	cout << "Sample Rate: " << buffer << endl;

	snprintf(buffer, sizeof(buffer), "%d", wave.getBitsPerSample(file));
	cout << "Bits Per Sample: " << buffer << endl;

	snprintf(buffer, sizeof(buffer), "%02x", wave.getDataSize(file));
	cout << "Data Size: 0x" << buffer << endl;

	file.close();

	return 0;
}