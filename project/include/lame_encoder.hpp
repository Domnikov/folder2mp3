/**
 * \file lame_encoder.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contans LameEncoder class to encode wav file into mp3
 *
 */
#pragma once

#include "../include/wav_file.hpp"
#include "../include/mp3_file.hpp"
#include "../include/lame_wrapper.hpp"

#include <filesystem>
#include <mutex>
#include <vector>

namespace folder2cpp
{


/**
 * @brief Class LameEncoder to encode wav file into mp3
 *
 * Stateless class. An instance of LameEncoder object cannot be created.
 * Must be used as template argument for ThreadPool.
 *
 * Static function 'process' will do all work: get file path and convert it into mp3
 *
 */
class LameEncoder
{
    public:

        /**
         * \brief Nickmane with container data type
         */
        using listType = std::vector<std::filesystem::path>;


        /**
         * \brief Static function which do all work: get path to wav file and encode it into wav
         *
         * Function throw std::runtime_error if wav file is corrupted or
         * if LameWrapper threw.
         *
         * \param Path for wav file
         * \param Verbose mode: print ecoded file information to stdout
         */
        static void process(std::filesystem::path&& file, bool verbose)
        {
            WavFile lv_wavFile(file);

            if (!lv_wavFile.isCorrect())
            {
                throw std::runtime_error (lv_wavFile.getTextInfo().data());
            }

            file.replace_extension(".mp3");
            Mp3File lv_mp3File(file);

            if (verbose)
            {
                static std::mutex lv_mutex;
                std::lock_guard<std::mutex> lock(lv_mutex);
                printf("Encoding %s --> %s\n", lv_wavFile.getPath().c_str(), lv_mp3File.getPath().c_str());
                printf("%s\n", lv_wavFile.getTextInfo().data());
            }

            LameWrapper::encode(lv_wavFile, lv_mp3File);
        }

    private:
        /**
         * \brief Deleted constructor. Instance cannot be created
         */
        LameEncoder() = delete;
};

} // namespace folder2cpp
