#ifndef SONG_DATABASE
#define SONG_DATABASE_H

#include <cstdio>

#include "../third-party/sqlite/sqlite3.h"

class song_library
{
    private:
        sqlite3* connection;

    public:
        void init_database(const char);
        void create_playlist();
        void delete_playlist();
        void add_song(const char, const char);
        void remove_song();
        char* get_song_address();
        
};

#endif