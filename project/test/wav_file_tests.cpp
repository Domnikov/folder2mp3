#include "../include/wav_file.h"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

using namespace folder2cpp;

TEST(Wav_file_Test, Sample1_test)
{
    auto lv_path = "./project/res/sample1.wav";

    WavFile lv_file(lv_path);

    ASSERT_TRUE(lv_file.isCorrect()) << "Sample 1 must be correct";
    ASSERT_EQ(lv_file.getChannels(), 1) << "Sample 1 must have one channel";
    ASSERT_EQ(lv_file.getFrequency(), 22050) << "Sample 1 frequency must be 22050";
    ASSERT_GE(lv_file.getTextInfo().length(), 50 + strlen(lv_path)) << "Sample 1 text file information incorrect";
}


TEST(Wav_file_Test, Sample2_test)
{
    auto lv_path = "./project/res/sample2.wav";

    WavFile lv_file(lv_path);

    ASSERT_TRUE(lv_file.isCorrect()) << "Sample 2 must be correct";
    ASSERT_EQ(lv_file.getChannels(), 2) << "Sample 2 must have two channel";
    ASSERT_EQ(lv_file.getFrequency(), 44100) << "Sample 2 frequency must be 44100";
    ASSERT_GE(lv_file.getTextInfo().length(), 50 + strlen(lv_path)) << "Sample 2 text file information incorrect";
}


TEST(Wav_file_Test, Sample3_test)
{
    auto lv_path = "./project/res/sample3.wav";

    WavFile lv_file(lv_path);

    ASSERT_FALSE(lv_file.isCorrect()) << "Sample 3 must be correct";
    ASSERT_LE(lv_file.getTextInfo().length(), 50 + strlen(lv_path)) << "Sample 3 text file information must contain an error";
}

} // namespace folder2cpp::tests
