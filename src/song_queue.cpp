#include "song_queue.h"

song_queue::song_queue(song_library *song_db_ptr)
{
    library = song_db_ptr;
    reload_songs();
    return;
}

void song_queue::reload_songs()
{
    std::string song_file;
    if(shuffle_flag == false)
    {
        for(int i = 1; i <= queue_size; i++)
        {  
            song_file = library->get_song_address(i);
            file_queue.push(song_file);
        }
    }
    else if(shuffle_flag == true)
    {
        //random queue
        std::random_device seed;
        std::mt19937 generation(seed());
        //set up top of distrubution to be max of database
        std::uniform_int_distribution<int> distribution(1, 5);

        for(int i = 1; i <= queue_size; i++)
        {  
            song_file = library->get_song_address(distribution(generation));
            file_queue.push(song_file);
        }
    }

}

std::string song_queue::pop_song()
{
    std::string song_address;
    song_address = file_queue.front();
    file_queue.pop();

    return song_address;
}

void song_queue::shuffle_switch(bool user_input)
{
    if(shuffle_flag != user_input)
    {
        shuffle_flag = user_input;
        reload_songs();
    }

    return;
}