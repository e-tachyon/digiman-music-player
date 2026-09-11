#pragma once

#include <queue>
#include <iostream>
#include <random>
#include "song_database.h"


class song_queue
{
    private:
        std::queue<std::string> file_queue;
        song_library *library;
        bool shuffle_flag = true;
        const int queue_size = 5;
    public:

    song_queue(song_library*);
    void reload_songs();
    void push_song();
    std::string pop_song();
    void shuffle_switch(bool);
};