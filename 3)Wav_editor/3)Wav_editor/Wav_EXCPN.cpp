#include "Wav_EXCPN.h"

Wav_EXCPN::Wav_EXCPN(const string& text) {
	textOfError = text;
}

Wav_EXCPN::~Wav_EXCPN() {
}

const char* Wav_EXCPN::what() {
	return textOfError.c_str();
}
