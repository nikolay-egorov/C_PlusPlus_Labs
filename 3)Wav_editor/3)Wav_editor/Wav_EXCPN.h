#pragma once
#include "Wav_Core.h"

class Wav_EXCPN : public exception {
private:
	string textOfError;
public:
	Wav_EXCPN(const string& text);
	~Wav_EXCPN();
	const char* what();
};

class HeaderRiffException : public Wav_EXCPN {
public:
	HeaderRiffException(const string& text) : Wav_EXCPN(text) {}
};

class HeaderFileSizeException : public Wav_EXCPN {
public:
	HeaderFileSizeException(const string& text) : Wav_EXCPN(text) {}
};

class HeaderWaveException : public Wav_EXCPN {
public:
	HeaderWaveException(const string& text) : Wav_EXCPN(text) {}
};

class HeaderFmtException : public Wav_EXCPN {
public:
	HeaderFmtException(const string& text) : Wav_EXCPN(text) {}
};

class HeaderNotPcmException : public Wav_EXCPN {
public:
	HeaderNotPcmException(const string& text) : Wav_EXCPN(text) {}
};

class HeaderSubchunk1Exception : public Wav_EXCPN {
public:
	HeaderSubchunk1Exception(const string& text) : Wav_EXCPN(text) {}
};

class HeaderBytesRateException : public Wav_EXCPN {
public:
	HeaderBytesRateException(const string& text) : Wav_EXCPN(text) {}
};

class HeaderBlockAlignException : public Wav_EXCPN {
public:
	HeaderBlockAlignException(const string& text) : Wav_EXCPN(text) {}
};

class HeaderSubchunk2SizeException : public Wav_EXCPN {
public:
	HeaderSubchunk2SizeException(const string& text) : Wav_EXCPN(text) {}
};

class UnsupportedFormatException : public Wav_EXCPN {
public:
	UnsupportedFormatException(const string& text) : Wav_EXCPN(text) {}
};

class BadParamsException : public Wav_EXCPN {
public:
	BadParamsException(const string& text) : Wav_EXCPN(text) {}
};

class IOException : public Wav_EXCPN {
public:
	IOException(const string& text) : Wav_EXCPN(text) {}
};

class BadFormatException : public Wav_EXCPN {
public:
	BadFormatException(const string& text) : Wav_EXCPN(text) {}
};