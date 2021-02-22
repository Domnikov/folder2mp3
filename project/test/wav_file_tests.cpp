#include "../include/wav_file.hpp"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

using namespace folder2cpp;

TEST(Wav_file_Test, Sample1_test)
{
    auto lv_path = "./project/res/sample1.wav";

    WavFile lv_file(lv_path);

    ASSERT_TRUE(lv_file.isCorrect()) << "sample1.wav must be correct";
    ASSERT_EQ(lv_file.getChannels(), 1) << "sample1.wav must have one channel";
    ASSERT_EQ(lv_file.getFrequency(), 22050) << "sample1.wav frequency must be 22050";
    ASSERT_GE(lv_file.getTextInfo().length(), 50 + strlen(lv_path)) << "sample1.wav text file information incorrect";
}


TEST(Wav_file_Test, Sample2_test)
{
    auto lv_path = "./project/res/sample2.wav";

    WavFile lv_file(lv_path);

    ASSERT_TRUE(lv_file.isCorrect()) << "sample2.wav must be correct";
    ASSERT_EQ(lv_file.getChannels(), 2) << "sample2.wav must have two channel";
    ASSERT_EQ(lv_file.getFrequency(), 44100) << "sample2.wav frequency must be 44100";
    ASSERT_GE(lv_file.getTextInfo().length(), 50 + strlen(lv_path)) << "sample2.wav text file information incorrect";
}


TEST(Wav_file_Test, Corrupted_test)
{
    auto lv_path = "./project/res/corrupted.wav";

    WavFile lv_file(lv_path);

    ASSERT_FALSE(lv_file.isCorrect()) << "corrupted.wav must be incorrect";
    ASSERT_LE(lv_file.getTextInfo().length(), 50 + strlen(lv_path)) << "corrupted.wav text file information must contain an error";
}

} // namespace folder2cpp::tests
