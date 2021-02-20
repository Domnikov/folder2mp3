# Create executable
add_executable(folder2mp3 src/main.cpp)

target_include_directories(folder2mp3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/res/corrupted.wav
    ${CMAKE_BINARY_DIR}/project/res/corrupted.wav
    COPYONLY)
