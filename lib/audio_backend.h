#pragma once

#include "miniaudio.h"

class audio_playback
{
    private:
        ma_result result;
        ma_decoder decoder;
        ma_device_config device_config;
        ma_device device;
        
    public:
        ~audio_playback();
        audio_playback(const char*);
        void set_volume(int);
        void play_audio();
        void pause_audio();

};

void data_callback(ma_device*, void*, const void*, ma_uint32);
