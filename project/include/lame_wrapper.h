#pragma once

#include "../include/wav_file.h"
#include "../include/mp3_file.h"

#include <lame/lame.h>

namespace folder2cpp
{

class LameWrapper
{
public:

    static void encode(WavFile& wav, Mp3File& mp3);

    static const char* getLameVersion(){return get_lame_version();}

private:
    LameWrapper() = delete;
};

} // namespace folder2cpp
