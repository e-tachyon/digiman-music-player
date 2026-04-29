#include <iostream>
#include <cstdio>
#include "audio_backend.h"
#include "song_database.h"

int main()
{   
    //test variables
    char user_input;
    char exit_song;

    //database
    const char* song_db = "../song_db.db";

    //test song
    std::string test_song;

    printf("Enter song location: ");
    std::cin >> test_song;

    //decoder init for song
    song_library library;

    library.init_database(song_db);
    library.add_song(song_db, test_song.c_str());

    std::string song_address;
    std::string vol_input;
    int volume;

    song_address = library.get_song_address(song_db, 1);
    audio_playback playback(song_address.c_str());

    //testing menu for features while creating backend
    //planned to be replaced with qt framework for GUI
    do
    {   

        printf("////////////////////\n");
        printf("Controls:\n");
        printf("Pick Song: c\n");
        printf("Quit: q\n");
        printf("Pause: p\n");
        printf("Play: s\n");
        printf("Volume: v\n");
        printf("////////////////////\n");

        std::cin >> user_input;

        switch(user_input)
        {
            case 'c':

            break;

            case 'p': playback.pause_audio();
            break;

            case 's': playback.play_audio();
            break;

            case 'v': 
                printf("Enter volume: ");
                std::cin >> vol_input;
                std::cout << "\n";
                volume = std::stoi(vol_input);
                playback.set_volume(volume);

                

            break;

            case 'q': exit_song = 'q';
            break;

            default: exit_song = '1';
            break;

        }
    }
    while(exit_song != 'q');



    return 0;
}
