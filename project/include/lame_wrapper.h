#pragma once

#include "../include/wav_file.h"
#include "../include/mp3_file.h"

#include <lame/lame.h>

class LameWrapper
{
public:

    static void encode(WavFile& wav, Mp3File& mp3);

private:
    LameWrapper() = delete;
};
