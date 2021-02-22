#pragma once
#include "../include/wav_file.hpp"
#include "../include/mp3_file.hpp"
#include "../include/lame_wrapper.hpp"

#include <filesystem>
#include <mutex>
#include <vector>

namespace folder2cpp
{


class LameEncoder
{
    public:

    static void process(std::filesystem::path&& file, bool verbose)
    {
        try
        {
            WavFile lv_wavFile(file);

            if (!lv_wavFile.isCorrect())
            {
                if (verbose)
                {
                    static std::mutex lv_mutex;
                    std::lock_guard<std::mutex> lock(lv_mutex);
                    fprintf(stdout, "%s\n", lv_wavFile.getTextInfo().data());
                }
                return;
            }

            file.replace_extension(".mp3");
            Mp3File lv_mp3File(file);

            if (verbose)
            {
                static std::mutex lv_mutex;
                std::lock_guard<std::mutex> lock(lv_mutex);
                fprintf(stdout, "Encoding %s --> %s\n", lv_wavFile.getPath().c_str(), lv_mp3File.getPath().c_str());
                fprintf(stdout, "%s\n", lv_wavFile.getTextInfo().data());
            }

            LameWrapper::encode(lv_wavFile, lv_mp3File);
        }
        catch(std::runtime_error& ex)
        {
            fprintf(stderr, "LameEncoder Error: %s\n", ex.what());
        }
    }

    using listType = std::vector<std::filesystem::path>;
};

} // namespace folder2cpp
