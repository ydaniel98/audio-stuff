#ifndef _WAVE_H_

#define _WAVE_H_

#include <fstream>
#include <stdint.h>

// Wave file must be preopened

class Wave {

public:

	/*
	* Reading
	*/

	// Basic Read Function
	template <typename T>
	T readRaw												(uint64_t pos, uint8_t size);

	// Function for reading after the start position
	template <typename T>
	T readSample										(uint64_t pos);

	// Function for reading sound data in chunk
	template <typename T>
	uint64_t readSoundData					(T * buffer, uint32_t size, uint64_t startPos, uint32_t * pos);

	// Function for reading sound data at a step to get the proper channel
	template <typename T>
	uint64_t readSoundDataAtStep		(T * buffer, uint32_t size, uint64_t startPos, uint32_t * pos, uint8_t step);
	/**/

	/*
	* Properties Variables
	*/
	uint32_t fileSize;
	uint32_t dataLength;
	uint8_t format;
	uint8_t channels;
	uint32_t sampleRate;
	uint8_t  bitsPerSample;
	uint64_t dataSize;
	uint16_t soundDataStart;
	/**/

	std::istream &wav;

	Wave(std::istream &wav_);

private:

	/*
	* Properties
	*/

	// Gets the file size for the wave file
	uint32_t 			getFileSize				(std::istream &wav);
	// Gets the lenght of the wave file
	uint32_t			getDataLength			(std::istream &wav);
	// Gets the format of the wave file
	uint8_t				getFormat					(std::istream &wav);
	// Gets the number of channels of the wave file
	uint8_t 			getChannels				(std::istream &wav);
	// Gets the sample rate of the wave file
	uint32_t 			getSampleRate			(std::istream &wav);
	// Gets the bit per sample of the wave file
	uint8_t 			getBitsPerSample	(std::istream &wav);
	// Gets the size of the data section
	uint64_t 			getDataSize				(std::istream &wav);
	// Gets the start position of the data section of the wave file
	uint16_t 			getSoundDataStart	(std::istream &wav);
	// Verify that the file is a sound file
	uint8_t 			verifySoundFile		(std::istream &wav);
	/**/

};

#include "Wave.inl"

#endif
