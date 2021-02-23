# Introduction

This is test project to implement comman line application which must be able to code all wav files in directory to mp3.

## Sinopsis
```
    folder2mp3 [OPTION]... [DIRECTORY]...
```

## Options
    -v, --verbose       explain what is being done
    -t=N, --threads=N   option to configure how many threads use for coding. Default N = CPU number [1..99]
    --version           output version information and exit

# Compilation

## Linux

For folder2mp3 compilation reqires gcc >= 8.0, cmake >= 3.1 and libmp3lame-dev or manualy compiled lame with -static-lib specifier.

Here is the compilation steps:
```
    mkdir build
    cd build
    cmake ..
    cmake --build .
```

Executable file will locate in project folder

To install folder2mp3 into system PATH:

```
    make install
```
As result folder2mp3 execution file must appear in default PATH directory.

## Windows (MINGW)

For folder2mp3 compilation reqires mingw >= 8.0 and cmake >= 3.1

How to check cmake:
```
cmake --version

{Print cmake version to stdin}
```

How to check mingw:
```
mingw32-make -- version

{Print mingw version to stdin}

g++ --version

{Print gcc version to stdin}
```

Here is the compilaton steps:
```
    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles"
    cmake --build .
```
Executable file will locate in project folder

If lame library was not found or couldn't be linked then need to compile lame and replace libmp3lame.a in ./ext/ folder


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
    cmake .. -DBUILD_TESTING=ON
    cmake --build .
```
To run tests:
```
    ./project/test/folder2mp3_test
```

## Used other testing tools:
For developing and testing was used folowing test tools:
```
    g++ ... -fsanitize=address
    g++ ... -fsanitize=thread
    g++ ... -fsanitize=undefined
    g++ ... -pg
```
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

# Change log
```
version 0            2021.02.20 16:30        Initial commit. Included tests, cmake, file samples 
version 0.0.1        2021.02.20 19:10        Completed CmdOption class + full tests
version 0.0.2        2021.02.20 20:44        Get wav file list class + full tests
version 0.0.3        2021.02.21 23:30        Thread_pool class + full tests
version 0.0.4        2021.02.22 01:30        WavFile class + full tests
version 0.0.5        2021.02.22 12:31        Mp3File class + full tests
version 0.1.0        2021.02.22 15:10        LameWarapper + tests. First working version
version 0.1.1        2021.02.22 17:13        Add verbose and version funcitons. Code refactoring
version 0.2.0        2021.02.22 21.33        Cleaned all source code. Linux version fully working
version 0.3.0        2021.02.24 01.06        Windows version fully working
```

##TODO

```
[ ] Test visual studio
[ ] Check how to encode one file from different threads
```
