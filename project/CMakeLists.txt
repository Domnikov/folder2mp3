# Create executable
set(SOURCE_EXE src/main.cpp
			  src/cmd_options.cpp
			  src/wav_file.cpp
			  src/mp3_file.cpp
			  src/lame_wrapper.cpp)

add_executable(folder2mp3 ${SOURCE_EXE})


if(UNIX)
target_include_directories(folder2mp3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
elseif(WIN32)
target_include_directories(folder2mp3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/ext/inc)
endif(UNIX)



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


# Add Auto Tests
    enable_testing()

    add_test(RunTest folder2mp3 ${CMAKE_BINARY_DIR}/project/res)
    set_tests_properties(RunTest PROPERTIES
	PASS_REGULAR_EXPRESSION "Error: Wav file currepted:*")
if(UNIX)
    add_test(CheckSample1 find ${CMAKE_BINARY_DIR}/project/res -name sample1.mp3)
    set_tests_properties(CheckSample1 PROPERTIES
        DEPENDS RunTest
        PASS_REGULAR_EXPRESSION "${CMAKE_BINARY_DIR}/project/res/sample1.mp3")

    add_test(CheckSample2 find ${CMAKE_BINARY_DIR}/project/res -name sample2.mp3)
    set_tests_properties(CheckSample2 PROPERTIES
        DEPENDS RunTest
        PASS_REGULAR_EXPRESSION "${CMAKE_BINARY_DIR}/project/res/sample2.mp3")
elseif(WIN32)
    add_test(NAME CheckSample1 COMMAND where sample1.mp3  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/project/res)
    set_tests_properties(CheckSample1 PROPERTIES
        DEPENDS RunTest
        PASS_REGULAR_EXPRESSION "sample1.mp3")

    add_test(NAME CheckSample2 COMMAND where sample2.mp3  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/project/res)
    set_tests_properties(CheckSample2 PROPERTIES
        DEPENDS RunTest
        PASS_REGULAR_EXPRESSION "sample2.mp3")

endif(UNIX)


# Add Unit tests
option(BUILD_TESTING "Compile the tests" OFF)
if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)
