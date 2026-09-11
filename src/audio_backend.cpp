#define MINIAUDIO_IMPLEMENTATION
#include "audio_backend.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_data_source_read_pcm_frames((ma_data_source*)pDevice->pUserData, pOutput, frameCount, NULL);

    (void)pInput;
}

audio_playback::~audio_playback()
{
    ma_device_uninit(&device);
    ma_resource_manager_uninit(&resource_manager);

    return;
}

//decode and device init function
audio_playback::audio_playback(const char* song_1, const char* song_2)
{
    device_config = ma_device_config_init(ma_device_type_playback);
    device_config.playback.format   = ma_format_f32;
    device_config.playback.channels = 2;
    device_config.sampleRate        = 44100;
    device_config.dataCallback = data_callback;
    device_config.pUserData = &song_source;
    result = ma_device_init(NULL, &device_config, &device);

    ma_device_set_master_volume(&device, 0.1);

    resource_manager_config = ma_resource_manager_config_init();
    resource_manager_config.decodedFormat   = device.playback.format;
    resource_manager_config.decodedChannels = device.playback.channels;
    resource_manager_config.decodedSampleRate = device.sampleRate;
    result = ma_resource_manager_init(&resource_manager_config, &resource_manager);
    result = ma_resource_manager_data_source_init(&resource_manager, song_1, NULL, NULL, &song_source);
    result = result = ma_resource_manager_data_source_init(&resource_manager, song_2, NULL, NULL, &song_source_next);

    ma_data_source_set_next(&song_source, &song_source_next);
    return;
}

void audio_playback::buffer_manager()
{
    
}

void audio_playback::skip_song()
{
    ma_device_stop(&device);
    ma_data_source_set_current(&song_source, &song_source_next);
    ma_device_start(&device);

    return;
}

//set playback volume
void audio_playback::set_volume(int level)
{   
    //ensure level within bounds
    if(level < 0)
    {
        level = 0;
    }
    else if(level > 100)
    {
        level = 100;
    }

    //device volume set
    float volume_level = level * 0.01;
    ma_device_set_master_volume(&device, volume_level);
}

//start playback
void audio_playback::play_audio()
{
    ma_device_start(&device);   
    return;
}

//stop playback
void audio_playback::pause_audio()
{
    ma_device_stop(&device);
    return;
}


