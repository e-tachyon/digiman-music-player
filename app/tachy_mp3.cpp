#include <iostream>
#include <cstdio>

#define MINIAUDIO_IMPLEMENTATION
#include "../third-party/miniaudio/miniaudio.h"

#include "../third-party/sqlite/sqlite3.h"

//audio processing
void data_callback(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 frame_count)
    {
        ma_decoder *p_decoder = (ma_decoder*)p_device->pUserData;
        if(p_decoder == NULL)
        {
            return;
        }
        ma_decoder_read_pcm_frames(p_decoder, p_output, frame_count, NULL);
    }


int main()
{
    //simple variables for testing loop
    char user_input = '1';
    char exit_song = '1';
    float volume = 0;
    std::string vol_input;

    //miniaudio decoder and device init
    ma_result result;
    ma_decoder decoder;
    ma_device_config device_config;
    ma_device device;

    //test song
    const char *song_mp3 = "../project/songs/not_for_sale_fossil.mp3";

    //decoder init for song
    result = ma_decoder_init_file(song_mp3, NULL, &decoder);

    printf("Song Play\n");

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

    //testing menu for features while creating backend
    //planned to be replaced with qt framework for GUI
    do
    {   

        printf("////////////////////\n");
        printf("Controls:\n");
        printf("Quit: q\n");
        printf("Pause: p\n");
        printf("Play: s\n");
        printf("Volume: v\n");
        printf("////////////////////\n");

        std::cin >> user_input;
        switch(user_input)
        {
            case 'p': ma_device_stop(&device);
            break;

            case 's': ma_device_start(&device);
            break;

            case 'v': 
                printf("Enter volume: ");
                std::cin >> vol_input;
                std::cout << "\n";
                volume = std::stoi(vol_input) * 0.01;

                if((volume <= 1.0) && (volume >= 0))
                {
                    ma_device_set_master_volume(&device, volume);
                }

            break;

            case 'q': exit_song = 'q';
            break;

            default: exit_song = '1';
            break;

        }
    }
    while(exit_song != 'q');

    printf("Song End\n");

    //uninits device and decoder
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);

    return 0;
}
