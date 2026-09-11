#include <iostream>
#include <cstdio>
#include "audio_backend.h"
#include "song_database.h"
#include "song_queue.h"

int main()
{   
    //test variables
    char user_input;
    char exit_song;
    int song_number;

    //database
    const char* song_db = "../song_db.db";

    //test song
    std::string test_song;

    //library init
    song_library library;
    library.init_database(song_db);

    song_queue track_queue(&library);

    std::string song_address;
    std::string song_address_2;
    std::string vol_input;
    int volume;

    //create class that handles user interactions
    //switch playlists
    //shuffle on/off
    //select song to play
    //add song to queue

    song_address = track_queue.pop_song();
    song_address_2 = track_queue.pop_song();

    std::cout << song_address << std::endl;

    audio_playback playback(song_address.c_str(), song_address_2.c_str());

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
        printf("Add Song: a\n");
        printf("////////////////////\n");

        std::cin >> user_input;

        switch(user_input)
        {
            case 'c': playback.skip_song();
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

            case 'a':
                printf("Enter song location: ");
                std::cin >> test_song;
                library.add_song(test_song.c_str());

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
