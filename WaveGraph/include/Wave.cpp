#ifndef _WAVE_CPP_

#define _WAVE_CPP_

#include <fstream>
#include <stdint.h>
#include <string>
#include "Wave.hpp"


Wave::Wave(std::istream &wav_): wav(wav_) {
  if (verifySoundFile(wav)) {
    fileSize        = getFileSize(wav);
    dataLength      = getDataLength(wav);
    format          = getFormat(wav);
    channels        = getChannels(wav);
    sampleRate      = getSampleRate(wav);
    bitsPerSample   = getBitsPerSample(wav);
    dataSize        = getDataSize(wav);
    soundDataStart  = getSoundDataStart(wav);
  }
}

uint32_t Wave::getFileSize(std::istream &wav) {
  return readRaw<uint32_t>(7, 4);
}

uint32_t Wave::getDataLength(std::istream &wav) {
  return readRaw<uint32_t>(16, 4);

}

uint8_t Wave::getFormat(std::istream &wav) {
  return readRaw<uint8_t>(20, 1);
}

uint8_t Wave::getChannels(std::istream &wav) {
  return readRaw<uint8_t>(22, 1);
}

uint32_t Wave::getSampleRate(std::istream &wav) {
  return readRaw<uint32_t>(24, 4);
}

uint8_t Wave::getBitsPerSample(std::istream &wav) {
  return readRaw<uint8_t>(34, 1);
}

uint64_t Wave::getDataSize(std::istream &wav) {
  return readRaw<uint64_t>(40, 4);
}

uint16_t Wave::getSoundDataStart(std::istream &wav) {
  return 44;
}

uint8_t Wave::verifySoundFile(std::istream &wav) {
  std::string stringCheck = "";

  for (uint8_t i = 0; i < 4; i++) {
    stringCheck += wav.get();
  }

  if (stringCheck != "RIFF") {
    // Temporal debug message TODO: setup as error to check in main
    std::cout << "Could not find \"RIFF\": File not valid" << std::endl;
    return false;
  }

  stringCheck = "";
  wav.seekg(8);

  for (uint8_t i = 0; i < 4; i++) {
    stringCheck += wav.get();
  }

  if (stringCheck != "WAVE") {
    // Temporal debug message TODO: setup as error to check in main
    std::cout << "Could not find \"WAVE\": File not valid" << std::endl;
    return false;
  }

  stringCheck = "";
  wav.seekg(12);

  for (uint8_t i = 0; i < 3; i++) {
    stringCheck += wav.get();
  }

  if (stringCheck != "fmt") {
    // Temporal debug mesasge TODO: setup as error to check in main
    std::cout << "Could not fing \"fmt\": File not valid" << std::endl;
    return false;
  }

  return true;
}

#endif
