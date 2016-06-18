#ifndef _WAVE_H_

#define _WAVE_H_

#include <fstream>
#include <stdint.h>

// Wave file must be preopened

class Wave {

public:

	/* Reading */
	template <typename T>
	T readRaw												(uint64_t pos, uint8_t size);

	template <typename T>
	T readSample										(uint64_t pos);

	template <typename T>
	uint64_t readSoundData					(T * buffer, uint32_t size, uint64_t startPos, uint32_t * pos);

	template <typename T>
	uint64_t readSoundDataAtStep		(T * buffer, uint32_t size, uint64_t startPos, uint32_t * pos, uint8_t step);
	/***********/

	/* Properties Variables */
	uint32_t fileSize;
	uint32_t dataLength;
	uint8_t format;
	uint8_t channels;
	uint32_t sampleRate;
	uint8_t  bitsPerSample;
	uint64_t dataSize;
	uint16_t soundDataStart;
	/************************/

	std::istream &wav;

	Wave(std::istream &wav_);

private:

	/* Properties */
	uint32_t 			getFileSize				(std::istream &wav);
	uint32_t			getDataLength			(std::istream &wav);
	uint8_t				getFormat					(std::istream &wav);
	uint8_t 			getChannels				(std::istream &wav);
	uint32_t 			getSampleRate			(std::istream &wav);
	uint8_t 			getBitsPerSample	(std::istream &wav);
	uint64_t 			getDataSize				(std::istream &wav);
	uint16_t 			getSoundDataStart	(std::istream &wav);
	uint8_t 			verifySoundFile		(std::istream &wav);
	/**************/

};

#include "Wave.inl"

#endif
