#ifndef WAVE_INL_
#define WAVE_INL_

#include <iostream>
#include <iomanip>

template <typename T>
T Wave::readRaw(uint64_t pos, uint8_t size) {

	T buff = 0;

	wav.seekg(pos);

	for (uint8_t i = 0; i < size; i++) {
		buff |= wav.get() << i;
	}

	return buff;
}

template <typename T>
T Wave::readSample(uint64_t pos) {
	return readRaw<T>(pos + soundDataStart, bitsPerSample / 8);
}

template <typename T>
uint64_t Wave::readSoundData(T * buffer, uint32_t size, uint64_t startPos, uint32_t * pos) {

	uint32_t i = 0;

	while ((i < size) && !wav.eof()) {
		buffer[i] = readSample<T>(startPos);
		i++;
		startPos += bitsPerSample / 8;
	}

	*pos = i;

	return startPos;

}

template <typename T>
uint64_t Wave::readSoundDataAtStep(T * buffer, uint32_t size, uint64_t startPos, uint32_t * pos, uint8_t step) {
	uint32_t i = 0;
	while (i < size && !wav.eof()) {
		buffer[i] = readSample<T>(startPos);
		startPos += (bitsPerSample / 8) * (step + 1);
		i++;
	}

	*pos = i;

	return startPos;
}

#endif
