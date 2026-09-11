cmake_minimum_required(VERSION 4.1)
project(digiman VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build TagLib as a static library" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Exclude TagLib examples" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "Exclude TagLib tests" FORCE)


add_subdirectory(third-party/taglib)

add_library(sqlite3_lib STATIC third-party/sqlite/sqlite3.c)
target_include_directories(sqlite3_lib PUBLIC lib)
target_compile_features(sqlite3_lib PUBLIC cxx_std_17)

add_library(audio_backend_lib STATIC src/audio_backend.cpp lib/audio_backend.h)
target_include_directories(audio_backend_lib PUBLIC lib)
target_compile_features(audio_backend_lib PUBLIC cxx_std_17)
target_include_directories(audio_backend_lib PRIVATE third-party/miniaudio)

add_library(song_database_lib STATIC src/song_database.cpp lib/song_database.h)
target_include_directories(song_database_lib PUBLIC lib)
target_compile_features(song_database_lib PUBLIC cxx_std_17)
target_link_libraries(song_database_lib PRIVATE sqlite3_lib)
target_link_libraries(song_database_lib PRIVATE tag)

add_library(song_queue_lib STATIC src/song_queue.cpp lib/song_queue.h)
target_include_directories(song_queue_lib PUBLIC lib)
target_compile_features(song_queue_lib PUBLIC cxx_std_17)
target_link_libraries(song_queue_lib PRIVATE song_database_lib)

add_executable(${PROJECT_NAME} app/digiman.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC audio_backend_lib)
target_link_libraries(${PROJECT_NAME} PUBLIC song_database_lib)
target_link_libraries(${PROJECT_NAME} PUBLIC song_queue_lib)
target_include_directories(${PROJECT_NAME} PRIVATE "third-party/miniaudio")

