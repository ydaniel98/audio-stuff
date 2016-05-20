#ifndef _WAVE_H_

#define _WAVE_H_

#include <fstream>
#include <stdint.h>

// Wave file must be preopened

class Wave {

public:

	/* Reading */
	template <typename T>
	T readSample										(uint64_t pos);

	template <typename T>
	uint64_t readSoundData					(T * buffer, uint32_t size, uint64_t startPos, uint32_t * pos);

	template <typename T>
	uint64_t readSoundDataAtStep		(T * buffer, uint32_t size, uint64_t startPos, uint32_t * pos, uint8_t step);
	/***********/

	/* Properties Variables */
	uint64_t fileSize;
	uint64_t dataLength;
	uint16_t format;
	uint32_t sampleRate;
	uint16_t bitsPerSample;
	uint32_t dataSize;
	uint32_t soundDataStart;
	uint16_t channels;
	/************************/

	std::istream &wav;

	Wave(std::istream &wav_);

private:

	/* Properties */
	uint64_t 			getFileSize				(std::istream &wav);
	uint64_t			getDataLength			(std::istream &wav);
	uint16_t			getFormat					(std::istream &wav);
	uint16_t 			getChannels				(std::istream &wav);
	uint32_t 			getSampleRate			(std::istream &wav);
	uint16_t 			getBitsPerSample	(std::istream &wav);
	uint32_t 			getDataSize				(std::istream &wav);
	uint32_t 			getSoundDataStart	(std::istream &wav);
	uint8_t 			verifySoundFile		(std::istream &wav);
	/**************/

};

#include "Wave.inl"

#endif
