/**
 * \file lame_wrapper.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contans LameWrapper class to provide convinient interface for libmp3lame
 *
 */
#pragma once

#include "../include/wav_file.hpp"
#include "../include/mp3_file.hpp"

#include <lame/lame.h>

namespace folder2cpp
{


/**
 * @brief Class LameWrapper to provide convinient interface for libmp3lame
 *
 * Stateless class. An instance of LameWrapper object cannot be created.
 * Full RAII implementation
 * Has two static functions:
 * 'encode' - convert wav file into mp3
 * 'getLameVersion' - return version of libmp3lame
 *
 */
class LameWrapper
{
    public:

        /**
         * \brief Static method to encode wav file into mp3
         *
         * Take wav file as the first argument abd mp3 file as the second.
         * In Inner loop it read wav, convert data into mp3 and save as mp3
         *
         * If any exception will occure during file conversion it will throw an std::runtime_error
         *
         * \param Wav file
         * \param Mp3 file
         */
        static void encode(WavFile& wav, Mp3File& mp3);


        /**
         * \brief Return version of linked libmp3lame
         */
        static const char* getLameVersion(){return get_lame_version();}

    private:
        /**
         * \brief Deleted constructor. Instance cannot be created
         */
        LameWrapper() = delete;
};

} // namespace folder2cpp
