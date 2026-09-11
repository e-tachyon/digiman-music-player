#pragma once

#include <iostream>
#include <cstdio>
#include <taglib/fileref.h> 
#include <taglib/tag.h>     
#include <taglib/tstring.h> 

#include "sqlite3.h"

class song_library
{
    private:
        sqlite3* connection;
        const char* song_db;

    public:
        void init_database(const char*);
        void create_playlist();
        void delete_playlist();
        void add_song(const char*);
        void remove_song();
        std::string get_song_address(int);
        //create add_songs_from directory function
        //create get max items of current db function
        
};
