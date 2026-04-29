#include "song_database.h"

void song_library::init_database(const char* song_db)
{
    int connection_check;
    connection_check = sqlite3_open(song_db, &connection);

    if(connection_check)
    {
        printf("Failed to open song library");
        sqlite3_close(connection);
        return;
    }

    char* error_message;
    const char* create_table = "CREATE TABLE IF NOT EXISTS songs(song_number int PRIMARY KEY, song_name varchar(255), file_address varchar(255));";
    int create_check;

    create_check = sqlite3_exec(connection, create_table, NULL, 0, &error_message);

    if(create_check != SQLITE_OK)
    {
        printf("Failed to create table");
        sqlite3_free(error_message);
    }

    sqlite3_close(connection);

    return;

}

void song_library::add_song(const char* song_db, const char* song_address)
{
    int connection_check;
    connection_check = sqlite3_open(song_db, &connection);

    if(connection_check)
    {
        printf("Failed to open song library");
        sqlite3_close(connection);
    }

    TagLib::FileRef f(song_address);
    TagLib::String tag_song_title = f.tag()->title();
    const char* song_title = tag_song_title.toCString(true);

    const char* insert_song = "INSERT INTO songs(song_number, song_name, file_address) VALUES (?, ?, ?);";
    sqlite3_stmt* insert_stmt;
    int insert_check;

    insert_check = sqlite3_prepare_v2(connection, insert_song, -1, &insert_stmt, nullptr);

    if(insert_check != SQLITE_OK)
    {
        printf("Error Preparing Insert");
        return;
    }

    int table_size = 1;

    sqlite3_bind_int(insert_stmt, 1, table_size);
    sqlite3_bind_text(insert_stmt, 2, song_title, -1, SQLITE_STATIC);
    sqlite3_bind_text(insert_stmt, 3, song_address, -1, SQLITE_STATIC);

    sqlite3_step(insert_stmt);
    sqlite3_finalize(insert_stmt);

    sqlite3_close(connection);
    return;

}

std::string song_library::get_song_address(const char* song_db, int song_number)
{
    std::string song_address;
    int connection_check;
    connection_check = sqlite3_open(song_db, &connection);

    if(connection_check)
    {
        printf("Failed to open song library");
        sqlite3_close(connection);
    }

    const char* select_song = "SELECT file_address FROM songs WHERE song_number = ?;";
    sqlite3_stmt* select_stmt;
    int select_check;
    int row_check;

    select_check = sqlite3_prepare_v2(connection, select_song, -1,  &select_stmt, nullptr);
    if(select_check == SQLITE_OK)
    {
        sqlite3_bind_int(select_stmt, 1, song_number);
        row_check = sqlite3_step(select_stmt);

        if(row_check == SQLITE_ROW)
        {
            song_address = (const char*)sqlite3_column_text(select_stmt, 0);
        }
    }

    sqlite3_finalize(select_stmt);

    sqlite3_close(connection);

    return song_address;

}