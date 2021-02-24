set(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")

find_package(GTest REQUIRED)
if (NOT GTest_FOUND)
    message(FATAL_ERROR "Cannot find Google Test Framework!")
    return()
endif()

include_directories(${GTEST_INCLUDE_DIRS} ../include)

set(TEST_SRC test_main.cpp) 

foreach(SRC ${SOURCE_EXE})
    if(NOT ${SRC} MATCHES "src/main.cpp")
        message(${SRC})
        set(TEST_SRC  ${TEST_SRC}  ../${SRC})
    endif()
endforeach()

add_executable(folder2mp3_test ${TEST_SRC})

target_link_libraries(folder2mp3_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread libmp3lame)


add_test(NAME UnitTests COMMAND folder2mp3_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR})