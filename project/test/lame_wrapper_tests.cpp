#include "../include/lame_wrapper.h"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

using namespace folder2cpp;

TEST(Lame_Wrapper_Test, Test_output_file_size)
{
    auto lv_wavPath = "./project/res/sample2.wav";
    auto lv_mp3Path = "./project/res/sample2.mp3";
    {
        WavFile lv_wavFile(lv_wavPath);
        Mp3File lv_mp3File(lv_mp3Path);

        ASSERT_TRUE(lv_wavFile.isCorrect()) << "Test wav file cannot be open or corrupted";
        ASSERT_TRUE(lv_mp3File.isCorrect()) << "Output mp3 file cannot be writen";

        LameWrapper::encode(lv_wavFile, lv_mp3File);
    }

    auto mp3Size = std::filesystem::file_size(lv_mp3Path);
    auto lv_deletedFiles = std::filesystem::remove_all(lv_mp3Path);

    ASSERT_GE(mp3Size, 500000) << "Output mp3 file too small";
    ASSERT_EQ(lv_deletedFiles, 1) << "Must be deleted one temporary mp3 file";
}

} // namespace folder2cpp::tests
