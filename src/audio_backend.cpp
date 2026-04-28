#define MINIAUDIO_IMPLEMENTATION
#include "../third-party/miniaudio/miniaudio.h"
#include "../lib/audio_backend.h"


//decode and device init function
void audio_playback::song_init(const char song)
{
    //inits decoder
    result = ma_decoder_init_file(&song, NULL, &decoder);

    //sets device with decoder values for playback
    device_config = ma_device_config_init(ma_device_type_playback);
    device_config.playback.format = decoder.outputFormat;
    device_config.playback.channels = decoder.outputChannels;
    device_config.sampleRate = decoder.outputSampleRate;
    device_config.dataCallback = data_callback;
    device_config.pUserData = &decoder;

    //inits device and plays audio
    ma_device_init(NULL, &device_config, &device);
    ma_device_start(&device);
}


//set playback volume
void audio_playback::set_volume(int level)
{   
    //ensure level within bounds
    if(level < 0)
    {
        level = 0;
    }
    else if(level < 100)
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
}

//stop playback
void audio_playback::pause_audio()
{
    ma_device_stop(&device);
}


