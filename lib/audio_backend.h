#pragma once

#include "miniaudio.h"

class audio_playback
{
    private:
        ma_result result;
        ma_device device;
        ma_device_config device_config;
        ma_resource_manager resource_manager;
        ma_resource_manager_config resource_manager_config;
        ma_resource_manager_data_source song_source;
        ma_resource_manager_data_source song_source_next;

    public:
        ~audio_playback();
        audio_playback(const char*, const char*);
        void buffer_manager();
        void skip_song();
        void set_volume(int);
        void play_audio();
        void pause_audio();

};

void data_callback(ma_device*, void*, const void*, ma_uint32);
