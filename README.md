# Introduction

This is test project to implement comman line application which must be able to code all wav files in directory to mp3.

## Sinopsis
```
    folder2mp3 [OPTION]... [DIRECTORY]...
```

## Options
    -v, --verbose		explain what is being done
    -t=N, -threads=N	option to configure how many threads use for coding. Default N = CPU number
    --version		output version information and exit


# Installation

## Linux

For folder2mp3 compilation reqires gcc >= 7.0, cmake and libmp3lame-dev.
Here is the installation steps:
```
    mkdir build
    cd build
    cmake ..
    cmake --build .
    make install
```
As result folder2mp3 execution file must appear in default PATH directory.


## Using examples

Following example will encode all wav files to mp3 from "HOME/audiobook" folder
```
    folder2mp3 ~/audiobook
```

# Testing 

## Auto testing
Google tests requre for auto tests.
Tests compilation:
```
    mkdir build
    cd build
    cmake .. -DCOMPILE_TESTS=ON
    cmake --build .
```
To run tests:
```
    ./project/test/folder2mp3_test
```

## Used other testing tools:
For developing and testing was used folowing test tools:

g++ ... -fsanitize=address

g++ ... -fsanitize=thread

g++ ... -fsanitize=undefined

g++ ... -pg

valgrind

## Manual test

For sample files included with project:
sample1.wav and sample2.wav	-	normal wav files to test
corrupted.wav			-	corrupted file with wav extension. Must be ignored
sample3.wa_			-	normal wav file but with wrong extension. Must be ignored
To test utility after compilation:
```
./project/folder2mp3 ./project/res
ls ./project/res/*.mp3
```
Must display two new mp3 file:
```
sample1.mp3
sample2.mp3
```

## Change log
version 0	2021.02.20 16:30	Initial commit. Included tests, cmake, file samples 
