#include "../lib/song_database.h"

void song_library::init_database(const char song_db)
{
    int connection_check;
    connection_check = sqlite3_open(&song_db, &connection);

    if(connection_check)
    {
        printf("Failed to open song library");
        sqlite3_close(connection);
    }

    char* error_message;
    const char* create_table = "CREATE TABLE IF NOT EXISTS SONGS(song_number int PRIMARY KEY, song_name varchar(255), file_address varchar(255);";
    int create_check;

    create_check = sqlite3_exec(connection, create_table, NULL, 0, &error_message);

    if(create_check != SQLITE_OK)
    {
        printf("Failed to create table");
        sqlite3_free(error_message);
    }

    sqlite3_close(connection);

}

void song_library::add_song(const char song_db, const char song_address)
{
    int connection_check;
    connection_check = sqlite3_open(&song_db, &connection);

    if(connection_check)
    {
        printf("Failed to open song library");
        sqlite3_close(connection);
    }

    
}