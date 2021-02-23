# Create executable
set(SOURCE_EXE src/main.cpp
			  src/cmd_options.cpp
			  src/wav_file.cpp
			  src/mp3_file.cpp
			  src/lame_wrapper.cpp)


add_executable(folder2mp3 ${SOURCE_EXE})

target_include_directories(folder2mp3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



# Check lame.h

find_path(LAME_H_DIR NAMES lame/lame.h PATHS ${CMAKE_SOURCE_DIR}/ext/inc/)
if(NOT LAME_H_DIR)
     message(FATAL_ERROR "lame.h header cannot be found")
endif()
message(STATUS ${LAME_H_DIR} )



# Check libmp3lame

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
find_library(LIBMP3LAME mp3lame)

if (NOT LIBMP3LAME)
    set(CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/ext/lib)
    find_library(LIBMP3LAME mp3lame)
    if (NOT LIBMP3LAME)
        message(FATAL_ERROR "libmp3lame cannot be found")
    endif (NOT LIBMP3LAME)
endif (NOT LIBMP3LAME)
message(STATUS ${LIBMP3LAME})


add_library(libmp3lame STATIC IMPORTED)
set_target_properties(libmp3lame PROPERTIES IMPORTED_LOCATION ${LIBMP3LAME})


# Add libraries
target_link_libraries(folder2mp3 pthread libmp3lame)


# Add tests
option(BUILD_TESTING "Compile the tests" OFF)
if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)
