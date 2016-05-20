#ifndef _WAVE_CPP_

#define _WAVE_CPP_

#include <fstream>
#include <stdint.h>
#include "Wave.hpp"


Wave::Wave(std::istream &wav_): wav(wav_) {

}

uint64_t Wave::getFileSize(std::istream &wav) {

}

uint64_t Wave::getDataLength(std::istream &wav) {

}

uint16_t Wave::getFormat(std::istream &wav) {

}

uint16_t Wav::getChannels(std::istream &wav) {

}

uint32_t Wav::getSampleRate(std::istream &wav) {

}

uint16_t Wave::getBitsPerSample(std::istream &wav) {

}

uint32_t Wave::getDataSize(std::istream &wav) {

}

uint32_t Wave::getSoundDataStart(std::istream &wav) {

}

uint8_t verifySoundFile(std::istream &wav) {
  // TODO: Check for 'RIFF and data chunk'
}

#endif
