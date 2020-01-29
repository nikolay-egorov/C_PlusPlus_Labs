#include "Wav_Core.h"
#include "Wav_EXCPN.h"





void Wav::read_Header(const string & fileName)
{
	cout << ">>>> Read header (" << fileName.c_str() << ")" << endl;

	ClearHDer();

	ifstream file(fileName, ifstream::binary);
	if (!file.good()) {
		throw IOException("IO Error");
	}

	file.seekg(0, ios::beg);
	file.read((char*)&header, sizeof(Wav_HDer));

	if (file.gcount() != sizeof(Wav_HDer)) {
		throw BadFormatException("Bad File Format ");
	}

	file.seekg(0, ios::end);

	checkHDer(file.tellg());
}

void Wav::see_Descript()
{
	cout << "--------HEAdER`s INNER WRLD----------" << endl;
	cout << "AudioFormat - " << header.audioFormat << endl;
	cout << "NumChanneld - " << header.numChannels << endl;
	cout << "SampleRate - " << header.sampleRate << endl;
	cout << "BitsPerSample - " << header.bitsPerSample << endl;
	cout << "ByteRate - " << header.byteRate << endl;
	cout << "BlockAlign - " << header.blockAlign << endl;
	cout << "ChunkSize - " << header.chunkSize << endl;
	cout << "Subchunk1Size - " << header.subchunk1Size << endl;
	cout << "Subchunk2Size - " << header.subchunk2Size << endl;
	cout << "-------------------------" << endl;
}

void Wav::extract_Data_int16(const string & fileName)
{
	cout << ">>>> Extract data int16 (" << fileName.c_str() << ")" << endl;

	read_Header(fileName);

	if (header.bitsPerSample != 16) {
		throw UnsupportedFormatException("Unsupported File Format");
	}

	ifstream file(fileName, ifstream::binary);
	if (!file.good()) {
		throw IOException("IO Error");
	}

	file.seekg(44, ios::beg);

	int channelsCount = header.numChannels;
	int samplesPerChannel = (header.subchunk2Size / sizeof(short)) / channelsCount;

	vector<short> allChannels;
	allChannels.resize(channelsCount * samplesPerChannel);
	file.read((char*)allChannels.data(), header.subchunk2Size);

	if (file.gcount() != header.subchunk2Size) {
		throw IOException("IO Error");
	}

	file.close();

	channelsData.resize(channelsCount);
	for (size_t ch = 0; ch < channelsData.size(); ch++) {
		channelsData[ch].resize(samplesPerChannel);
	}

	for (int ch = 0; ch < channelsCount; ch++) {
		vector<short>& channel = channelsData[ch];
		for (size_t i = 0; i < samplesPerChannel; i++) {
			channel[i] = allChannels[channelsCount * i + ch];
		}
	}
}

void Wav::mke_Wav(const string & fileName)
{
	cout << ">>>> Maki`n out wav file (" << fileName.c_str() << ")" << endl;

	int channelsCount = (int)channelsData.size();

	if (channelsCount < 1) {
		throw BadParamsException("Bad Params Error");
	}

	int samplesCountPerChannel = (int)channelsData[0].size();

	for (size_t ch = 0; ch < channelsCount; ch++) {
		if (channelsData[ch].size() != (size_t)samplesCountPerChannel) {
			throw BadParamsException("Bad Params Error");
		}
	}

	formHDer(channelsCount, 16, header.sampleRate, samplesCountPerChannel);

	vector<short> allChannels;
	allChannels.resize(channelsCount * samplesCountPerChannel);

	for (int ch = 0; ch < channelsCount; ch++) {
		const vector<short>& channelData = channelsData[ch];
		for (size_t i = 0; i < samplesCountPerChannel; i++) {
			allChannels[channelsCount * i + ch] = channelData[i];
		}
	}

	ofstream fileOut(fileName, ofstream::binary | ofstream::out);
	fileOut.write((char*)&header, sizeof(Wav_HDer));
	fileOut.write((char*)allChannels.data(), allChannels.size() * sizeof(short));

	if (fileOut.fail()) {
		throw IOException("IO Error");
	}

	fileOut.close();
}

void Wav::mke_Mono()
{
	int channelsCount = (int)channelsData.size();

	if (channelsCount != 2) {
		throw BadParamsException("Bad Params Error");
	}

	int samplesCountPerChannel = (int)channelsData[0].size();

	for (size_t ch = 0; ch < channelsCount; ch++) {
		if (channelsData[ch].size() != (size_t)samplesCountPerChannel) {
			throw BadParamsException("Bad Params Error");
		}
	}

	vector<short> mono = channelsData[0];
	mono.resize(1);
	mono.resize(samplesCountPerChannel);

	for (size_t i = 0; i < samplesCountPerChannel; i++) {
		mono[i] = (channelsData[0][i] + channelsData[1][i]) / 2;
	}

	channelsData.pop_back();
	channelsData[0] = mono;
	formHDer(channelsData.size(), header.bitsPerSample, header.sampleRate, samplesCountPerChannel);
}

void Wav::mke_Reverb(double delay_seconds, float decay)
{
	int channelsCount = (int)channelsData.size();

	if (channelsCount < 1) {
		throw BadParamsException("Bad Params Error");
	}

	int samplesCountPerChannel = (int)channelsData[0].size();

	for (size_t ch = 0; ch < channelsCount; ch++) {
		if (channelsData[ch].size() != (size_t)samplesCountPerChannel) {
			throw BadParamsException("Bad Params Error");
		}
	}

	int delaySamples = (int)(delay_seconds * header.sampleRate);

	for (size_t ch = 0; ch < channelsCount; ch++) {
		vector<float> tmp;
		tmp.resize(channelsData[ch].size());

		for (size_t i = 0; i < samplesCountPerChannel; i++) {
			tmp[i] = channelsData[ch][i];
		}

		for (size_t i = 0; i < samplesCountPerChannel - delaySamples; i++) {
			tmp[i + delaySamples] += decay * tmp[i];
		}

		float maxMagnitude = 0.0f;
		for (size_t i = 0; i < samplesCountPerChannel - delaySamples; i++) {
			if (abs(tmp[i]) > maxMagnitude) {
				maxMagnitude = abs(tmp[i]);
			}
		}

		float normCoef = 30000.0f / maxMagnitude;
		cout << "Max magnitude = " << maxMagnitude << " coef = " << normCoef << endl;

		for (size_t i = 0; i < samplesCountPerChannel; i++) {
			channelsData[ch][i] = (short)(normCoef * tmp[i]);
		}
	}

	formHDer(channelsData.size(), header.bitsPerSample, header.sampleRate, samplesCountPerChannel);
}

void Wav::CutFirstSeconds(int seconds)
{
	int delet = (header.bitsPerSample / 8) * header.sampleRate * seconds / sizeof(short);
	for (auto &chanel : channelsData) {
		chanel.erase(chanel.begin(), chanel.begin() + delet);
	}
}

void Wav::CutLastSeconds(int seconds)
{
	int delet = (header.bitsPerSample / 8) * header.sampleRate * seconds / sizeof(short);
	for (auto &chanel : channelsData) {
		chanel.erase(chanel.end() - delet, chanel.end());
	}
}


void Wav::ClearHDer()
{
	memset(&header, 0, sizeof(Wav_HDer));
}

void Wav::initHDer()
{
	header.chunkId[0] = 'R';
	header.chunkId[1] = 'I';
	header.chunkId[2] = 'F';
	header.chunkId[3] = 'F';

	header.format[0] = 'W';
	header.format[1] = 'A';
	header.format[2] = 'V';
	header.format[3] = 'E';

	header.subchunk1Id[0] = 'f';
	header.subchunk1Id[1] = 'm';
	header.subchunk1Id[2] = 't';
	header.subchunk1Id[3] = ' ';

	header.subchunk2Id[0] = 'd';
	header.subchunk2Id[1] = 'a';
	header.subchunk2Id[2] = 't';
	header.subchunk2Id[3] = 'a';

	header.audioFormat = 1;
	header.subchunk1Size = 16;
	header.bitsPerSample = 16;
}

void Wav::checkHDer(size_t fileSize)
{
	if (header.chunkId[0] != 'R' ||
		header.chunkId[1] != 'I' ||
		header.chunkId[2] != 'F' ||
		header.chunkId[3] != 'F') {
		throw HeaderRiffException("Header RIFF Error");
	}

	if (header.chunkSize != fileSize - 8) {
		throw HeaderFileSizeException("Header File Size Error");
	}

	if (header.format[0] != 'W' ||
		header.format[1] != 'A' ||
		header.format[2] != 'V' ||
		header.format[3] != 'E') {
		throw HeaderWaveException("Header WAVE Error");
	}

	if (header.subchunk1Id[0] != 'f' ||
		header.subchunk1Id[1] != 'm' ||
		header.subchunk1Id[2] != 't' ||
		header.subchunk1Id[3] != ' ') {
		throw HeaderFmtException("Header FMT Error");
	}

	if (header.audioFormat != 1) {
		throw HeaderNotPcmException("Header Not PCM");
	}

	if (header.subchunk1Size != 16) {
		throw HeaderSubchunk1Exception("Header Subchunk1 Error");
	}

	if (header.byteRate != header.sampleRate * header.numChannels * header.bitsPerSample / 8) {
		throw HeaderBytesRateException("Header Bytes Rate Error");
	}

	if (header.blockAlign != header.numChannels * header.bitsPerSample / 8) {
		throw HeaderBlockAlignException("Header Block Align Error");
	}

	if (header.subchunk2Id[0] != 'd' ||
		header.subchunk2Id[1] != 'a' ||
		header.subchunk2Id[2] != 't' ||
		header.subchunk2Id[3] != 'a') {
		throw HeaderFmtException("Header FMT Error");
	}

	if (header.subchunk2Size != fileSize - 44) {
		throw HeaderSubchunk2SizeException("Header Subchunk2 Size Error");
	}
}

void Wav::formHDer(int channelsCount, int bitsPerSample, int sampleRate, int samplesCountPerChannel)
{
	if (bitsPerSample != 16) {
		throw UnsupportedFormatException("Unsupported Format Error");
	}

	if (channelsCount < 1) {
		throw BadParamsException("Bad Params Error");
	}

	initHDer();

	int fileSizeBytes = 44 + channelsCount * (bitsPerSample / 8) * samplesCountPerChannel;

	header.sampleRate = sampleRate;
	header.numChannels = channelsCount;
	header.bitsPerSample = 16;

	header.chunkSize = fileSizeBytes - 8;
	header.subchunk2Size = fileSizeBytes - 44;

	header.byteRate = header.sampleRate * header.numChannels * header.bitsPerSample / 8;
	header.blockAlign = header.numChannels * header.bitsPerSample / 8;
}



