# Create executable

set(SOURCE_EXE src/main.cpp
			  src/cmd_options.cpp
			  src/wav_file.cpp
			  src/mp3_file.cpp
			  src/lame_wrapper.cpp
			  )


add_executable(folder2mp3 ${SOURCE_EXE})

target_include_directories(folder2mp3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Check all libraries
find_path(LAME_H_DIR lame/lame.h)
message(STATUS ${LAME_H_DIR} )
if(NOT LAME_H_DIR)
    message(FATAL_ERROR "lame.h header cannot be found")
endif()

if (UNIX)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    find_library(LIBMP3LAME mp3lame)
endif()
message(STATUS ${LIBMP3LAME})
if (NOT LIBMP3LAME)
    message(FATAL_ERROR "libmp3lame cannot be found")
endif ()


add_library(libmp3lame STATIC IMPORTED)
set_target_properties(libmp3lame PROPERTIES IMPORTED_LOCATION ${LIBMP3LAME})
target_link_libraries(folder2mp3 pthread libmp3lame)


option(COMPILE_TESTS "Compile the tests" OFF)
if(COMPILE_TESTS)
  add_subdirectory(test)
endif(COMPILE_TESTS)



# Copy demo_flow to bin folder
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/res/sample1.wav
    ${CMAKE_BINARY_DIR}/project/res/sample1.wav
    COPYONLY)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/res/sample2.wav
    ${CMAKE_BINARY_DIR}/project/res/sample2.wav
    COPYONLY)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/res/sample3.wa_
    ${CMAKE_BINARY_DIR}/project/res/sample3.wa_
    COPYONLY)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/res/corrupted.wav
    ${CMAKE_BINARY_DIR}/project/res/corrupted.wav
    COPYONLY)
