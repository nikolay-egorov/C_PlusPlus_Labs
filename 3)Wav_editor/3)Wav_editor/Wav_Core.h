#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Wav {
private:
	struct Wav_HDer {
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subchunk1Id[4];
		unsigned long subchunk1Size;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long byteRate;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char subchunk2Id[4];
		unsigned long subchunk2Size;
	};
	Wav_HDer header;
	vector<vector<short>> channelsData;
	void ClearHDer();
	void initHDer();
	void checkHDer(size_t fileSize);
	void formHDer(int channelsCount, int bitsPerSample, int sampleRate, int samplesCountPerChannel);
public:
	void read_Header(const string& fileName);
	void see_Descript();
	void extract_Data_int16(const string& fileName);
	void mke_Wav(const string& fileName);
	void mke_Mono();
	void mke_Reverb(double delay_seconds, float decay);
	void CutFirstSeconds(int seconds);
	void CutLastSeconds(int seconds);
};