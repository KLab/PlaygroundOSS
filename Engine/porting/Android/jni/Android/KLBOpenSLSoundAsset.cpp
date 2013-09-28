/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "CAndroidPathConv.h"
#include "KLBOpenSLAudioPlayer.h"
#include "ivorbisfile.h"
#include "KLBPlatformMetrics.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
size_t KLBOpenSLSoundAsset::read_func(void *ptr, size_t size, size_t nmemb, void *datasource) {
	KLBOpenSLSoundAsset* me = (KLBOpenSLSoundAsset*)datasource;

	// http://xiph.org/vorbis/doc/vorbisfile/callbacks.html
	// > short reads mean nothing special (short reads are not treated as error conditions)
	// So, we actually don't need to perform memcpy(). Just rewrite pointer reference and
	// return length.
	unsigned int requested_size = (unsigned int)nmemb * (unsigned int)size;
	int bytes_read = 0;
	bytes_read = fread(ptr, 1, requested_size, me->fp);
	me->decryptor.decryptBlck(ptr, bytes_read);
	me->src_location += bytes_read;
	// DEBUG_PRINT("AUDIO; read_func(requested=%d, actually read=%d, loc=%d)", requested_size, bytes_read, me->src_location);
	return bytes_read;
}

int KLBOpenSLSoundAsset::seek_func(void *datasource, ogg_int64_t offset, int whence) {
	KLBOpenSLSoundAsset* me = (KLBOpenSLSoundAsset*)datasource;

	unsigned int new_pos = me->src_location;
	// DEBUG_PRINT("new_pos initiated as %d", new_pos);
	// TODO: proper seeking(could contain synchronous blocks reading)
	if (whence == SEEK_SET)
		new_pos = (unsigned int)offset;
	else if (whence == SEEK_CUR)
		new_pos += (unsigned int)offset;
	else if (whence == SEEK_END)
		new_pos = me->getSrcFileSize();
	// DEBUG_PRINT("AUDIO; seek_func(current=%d, offset=%d, whence=%d, new=%d)", me->src_location, (unsigned int)offset, whence, new_pos);
	me->src_location = new_pos;
	
	fseek(me->fp, me->src_location + (me->decryptor.m_useNew ? 4 : 0), SEEK_SET);
	me->decryptor.gotoOffset(me->src_location);
	// TODO: update PCM buffer offset(pcm_total_read_pos)

	return 0;
}

int KLBOpenSLSoundAsset::close_func(void *datasource) {
	KLBOpenSLSoundAsset* me = (KLBOpenSLSoundAsset*)datasource;
	// DEBUG_PRINT("AUDIO; close_func()");
	if (me->fp != NULL) {
		fclose(me->fp);
		me->fp = NULL;
	}
	return 0;
}

long KLBOpenSLSoundAsset::tell_func(void *datasource) {
	KLBOpenSLSoundAsset* me = (KLBOpenSLSoundAsset*)datasource;
	// DEBUG_PRINT("AUDIO; tell_func(): pos=%d", (unsigned int)me->src_location);

	return (long)me->src_location;
}

KLBOpenSLSoundAsset::KLBOpenSLSoundAsset(const char * path, bool is_se) :
pcm_samples(NULL),
fp(NULL),
src_location(0),
src_buf_flags(0x00),
pcm_buffer_read_pos(0),
pcm_buffer_consumed_pos(0),
pcm_total_read_pos(0)
{
    DEBUG_PRINT("AUDIO; construct KLBOpenSLSoundAsset(path: %s)", path);
	KLBOpenSLSoundAsset::is_se = is_se;
	src_path = path;
    src_full_path = CAndroidPathConv::getInstance().fullpath(path, ".ogg");
    // DEBUG_PRINT("path=%s, fullpath=%s", path, src_full_path);
	fp = fopen(src_full_path, "rb");
	assert(fp != NULL);

	fseek(fp, 0, SEEK_END);
	fgetpos(fp, (fpos_t*)&src_file_size);
	fseek(fp, 0, SEEK_SET);

	u8 hdr[4];
	hdr[0] = 0;
	hdr[1] = 0;
	hdr[2] = 0;
	hdr[3] = 0;
	fread(hdr, 1, 4, fp);

	if (is_se)
	{
		this->src_buf_flags |= 0x04;
	}

	decryptor.decryptSetup((const u8*)src_full_path, hdr);
	if (decryptor.m_useNew) {
		src_file_size -= 4;
	}
	else {
		fseek(fp, 0, SEEK_SET);
	}

    DEBUG_PRINT("AUDIO; src_file=%s, src_file_size=%d", src_full_path, src_file_size);
    DEBUG_PRINT("AUDIO; allocating Vorbis-file object");
	vf = (OggVorbis_File*)calloc(1, sizeof(OggVorbis_File));
    // DEBUG_PRINT("AUDIO; setting callbacks");
    ov_callbacks callbacks;
	callbacks.read_func = &KLBOpenSLSoundAsset::read_func;
	callbacks.seek_func = &KLBOpenSLSoundAsset::seek_func;
	callbacks.close_func = &KLBOpenSLSoundAsset::close_func;
	callbacks.tell_func = &KLBOpenSLSoundAsset::tell_func;
    // DEBUG_PRINT("AUDIO; opening ogg-vorbis stream");
    int iRet = ov_open_callbacks(this, vf, NULL, 0, callbacks);
    // DEBUG_PRINT("AUDIO; ov_open_callbacks returned %d", iRet);

    assert(0 == iRet);

	vorbis_info* vi = ov_info(vf, -1);
	ogg_int64_t uiPCMSamples = ov_pcm_total(vf, -1);
    // DEBUG_PRINT("AUDIO; total PCM samples=%d", uiPCMSamples);
	assert(0 < uiPCMSamples);
	DEBUG_PRINT("uiPCMSamples size: %lld, channels: %d, version: %d, %ldHz", uiPCMSamples, vi->channels, vi->version, vi->rate);
	if (uiPCMSamples == OV_EINVAL) {
		// TODO: proper error handling
		return;
	}
	playtime_ms = (int)((uiPCMSamples * 1000) / vi->rate);
	channels = vi->channels;
    DEBUG_PRINT("AUDIO; total channels=%d", channels);
	pcm_total_samples = (unsigned int)uiPCMSamples * channels;
	pcm_buffer_size = isFullyBuffered() ? pcm_total_samples : min(pcm_total_samples, MAX_BUFFER_SAMPLES);
	pcm_samples = (short*)malloc(pcm_buffer_size * sizeof(s16));
	pcm_sampling_rate = vi->rate;
    DEBUG_PRINT("AUDIO; PCM buffer size=%d, PCM samples addr=%d", pcm_buffer_size, (int)pcm_samples);
}

KLBOpenSLSoundAsset::~KLBOpenSLSoundAsset()
{
	DEBUG_PRINT("AUDIO; unloading asset: %s", src_full_path);
	KLBOpenSLEngine::getInstance()->unload(this);
	// REPORT_METRICS("about to clear vf");
	if (vf != NULL) {
		this->closeVorbisFile();
	}
	// REPORT_METRICS("about to free pcm_samples");
	free(pcm_samples);
	// REPORT_METRICS("about to free vf");
	free(vf);
	// REPORT_METRICS("done");
	delete [] src_full_path;
}

void KLBOpenSLSoundAsset::closeVorbisFile()
{
	if (vf != NULL) {
		ov_clear(vf);
		vf = NULL;
	}
	// close file for sure (actually, this should've been done in ov_clear())
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}

void KLBOpenSLSoundAsset::stopAll()
{
	KLBOpenSLEngine::getInstance()->discardCorrespondingSoundHandles(this);
}

void KLBOpenSLSoundAsset::prepare(int frames)
{
	if (frames == -1) {
		is_se = true;
	}
	// DEBUG_PRINT("AUDIO; performing prepare(%d against %d)", frames, pcm_buffer_size);
	if (pcm_buffer_size < frames)
	{
		DEBUG_PRINT("AUDIO; quitting prepare");
		// TODO: proper error handling
		return;
	}
	readVorbisSamples(frames);
}

void KLBOpenSLSoundAsset::readVorbisSamplesImpl(int samplesToRead) {
	bool close_vorbis_after_reading = false;
	if (pcm_buffer_size < samplesToRead)
	{
		// too large samples count specified
		// TODO: proper error handling
		return;
	}
	if (pcm_total_samples == pcm_total_read_pos) {
		DEBUG_PRINT("AUDIO; end of buffer reached");
		return;
	}
	// DEBUG_PRINT("start pos=%d, total samples=%d, total read=%d, samplesToRead=%d, offset=%d", (int)pcm_samples, pcm_total_samples, pcm_total_read_pos, samplesToRead, pcm_buffer_read_pos);
	if (pcm_buffer_read_pos == pcm_buffer_size)
	{
		pcm_buffer_read_pos = 0;
	}
	if (pcm_buffer_consumed_pos == pcm_buffer_size)
	{
		pcm_buffer_consumed_pos = 0;
	}
	short* pcm_buf_read_start_pos = pcm_samples + pcm_buffer_read_pos;
	if (samplesToRead == -1)
	{
		if (isFullyBuffered()) {
			samplesToRead = pcm_buffer_size;
			close_vorbis_after_reading = true;
		}
		else {
			samplesToRead = min(DEFAULT_LOAD_SAMPLES, pcm_total_samples - pcm_total_read_pos);
		}
		// DEBUG_PRINT("auto refill. size=%d", samplesToRead);
	}
	else
	{
		int buffer_size_overflow = pcm_buffer_read_pos + samplesToRead - pcm_buffer_size;
		DEBUG_PRINT("bufsize to overflow=%d", buffer_size_overflow);
		if (0 < buffer_size_overflow)
		{
			// this should normally never happen (or, adjust buffer size not to happen)
			unsigned int buf_read_first_phase = pcm_buffer_size - pcm_buffer_read_pos;
			DEBUG_PRINT("read on first page=%d", buf_read_first_phase);
			readVorbisSamples(buf_read_first_phase);
			pcm_buf_read_start_pos += buf_read_first_phase;
			samplesToRead -= buf_read_first_phase;
		}
	}
	int currentSection = 0;
	s64 bytesRead = 0;
	int bufPos = 0;
	// DEBUG_PRINT("performing actual Vorbis->PCM decode: addr=%d", (int)pcm_buf_read_start_pos);
	do
		{
			// DEBUG_PRINT("filling ptr: %d, snd buffer pos: %d", (int)(pcm_buf_read_start_pos + bufPos), bufPos);
			u16 bytesToRead = min(VORBIS_READ_BUFFER, (samplesToRead - bufPos) * 2);
			bytesRead = ov_read(vf, (char *)(pcm_buf_read_start_pos + bufPos), bytesToRead, &currentSection);
			bufPos += (int)bytesRead >> 1; /* divide by 2 for buffer=short */
		} while (0 < bytesRead && bufPos < samplesToRead);
	pcm_buffer_read_pos += samplesToRead;
	pcm_total_read_pos += samplesToRead;
	if (close_vorbis_after_reading)
	{
		closeVorbisFile();
	}
	// DEBUG_PRINT("snd buffer filled with %d samples(pcm_buffer_read_pos=%d against pcm_buffer_size=%d)", bufPos, pcm_buffer_read_pos, pcm_buffer_size);
}

void KLBOpenSLSoundAsset::fetchNextPcmBuffer(KLBOpenSLSoundHandle* soundHandle) {
	// DEBUG_PRINT("AUDIO; fetching next pcm buf. bits=%d", soundHandle->getPcmDepth() * 8);
	if (!isFullyBuffered()) {
		// DEBUG_PRINT("AUDIO; pcm_buffer_read_pos=%d, pcm_buffer_consumed_pos=%d, pcm_total_samples=%d, pcm_total_read_pos=%d, soundHandle->consumed_pos=%d, pcm_buffer_size=%d", pcm_buffer_read_pos, pcm_buffer_consumed_pos, pcm_total_samples, pcm_total_read_pos, soundHandle->consumed_pos, pcm_buffer_size);
		if (pcm_total_read_pos == pcm_total_samples && pcm_buffer_read_pos == pcm_buffer_consumed_pos) {
			// buffer end reached
			soundHandle->head_bufsize = 0;
			return;
		}
		if (soundHandle->consumed_pos == pcm_buffer_size) {
			soundHandle->consumed_pos = 0;
		}
	}
	soundHandle->current_head = (short*)(pcm_samples + soundHandle->consumed_pos);
	soundHandle->head_bufsize = isFullyBuffered() ? DEFAULT_LOAD_SAMPLES : min(DEFAULT_LOAD_SAMPLES, pcm_buffer_read_pos - pcm_buffer_consumed_pos);
	// DEBUG_PRINT("AUDIO; consumed_pos=%d, head_bufsize=%d", soundHandle->consumed_pos, soundHandle->head_bufsize);
	unsigned int new_consumed_pos = soundHandle->consumed_pos + soundHandle->head_bufsize;
	if (pcm_buffer_size < new_consumed_pos)
	{
		soundHandle->head_bufsize -= new_consumed_pos - pcm_buffer_size;
		new_consumed_pos = pcm_buffer_size;
	}
	soundHandle->consumed_pos = new_consumed_pos;
	if (pcm_buffer_consumed_pos < new_consumed_pos)
	{
		pcm_buffer_consumed_pos = new_consumed_pos;
	}
	soundHandle->head_bufsize *= soundHandle->getPcmDepth();
	return;
}

void KLBOpenSLSoundAsset::close()
{

}

KLBOpenSLSoundHandle* KLBOpenSLSoundAsset::play(KLBOpenSLSoundAsset::REPEAT_MODE mode, s32 _milisec, float _tgtVol, float _startVol)
{
	DEBUG_PRINT("playing sound asset \"%s\" (mode=%d)", src_full_path, mode);
	if (!isFullyBuffered() && mode == KLBOpenSLSoundAsset::INFINITE_LOOP)
	{
		// TODO: implement looping for BGMs
	}
	KLBOpenSLSoundHandle* soundHandle = KLBOpenSLEngine::getInstance()->assignSoundHandle(this);
	soundHandle->play(_milisec, _tgtVol, _startVol);
	return soundHandle;
}

