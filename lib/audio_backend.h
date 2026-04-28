#ifndef AUDIO_BACKEND
#define AUDIO_BACKEND_H

#define MINIAUDIO_IMPLEMENTATION
#include "../third-party/miniaudio/miniaudio.h"

void data_callback(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 frame_count)
    {
        ma_decoder *p_decoder = (ma_decoder*)p_device->pUserData;
        if(p_decoder == NULL)
        {
            return;
        }
        ma_decoder_read_pcm_frames(p_decoder, p_output, frame_count, NULL);
    }

class audio_playback
{
    private:
        ma_result result;
        ma_decoder decoder;
        ma_device_config device_config;
        ma_device device;
        
    public:
        void song_init(const char);
        void set_volume(int);
        void play_audio();
        void pause_audio();

};

#endif