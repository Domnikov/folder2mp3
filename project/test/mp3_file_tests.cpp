#include "../include/mp3_file.h"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

using namespace folder2cpp;

TEST(Mp3_file_Test, Write_test)
{
    auto lv_path = "./project/res/write_test.mp3";
    unsigned char lv_sampleLine[0x100];
    constexpr auto lv_lines = 10;

    for (int c = 0; c <= 0xFF; c++)
    {
        lv_sampleLine[c] = static_cast<unsigned char>(c);
    }

    {
        Mp3File lv_file(lv_path);
        ASSERT_TRUE(lv_file.isCorrect()) << "Mp3 file was not created";

        for (int i = 0; i < lv_lines; i++)
        {
            auto lv_written = lv_file.write(lv_sampleLine, 0xFF);
            ASSERT_EQ(lv_written, 0xFF) << "Write function must return 256 written bytes";
        }
    }

    auto deleter=[](FILE* file){fclose(file);};
    std::unique_ptr<FILE, decltype(deleter)> lv_file(fopen(lv_path, "rb"), deleter);

    ASSERT_GE(lv_file, nullptr) << "Written mp3 file cannot be open";

    unsigned char lv_targetBuf[0x100];
    for (int i = 0; i < lv_lines; i++)
    {
        auto lv_read = fread(lv_targetBuf, sizeof(lv_targetBuf[0]), 0xFF, lv_file.get());
        ASSERT_EQ(lv_read, 0xFF) << "Read function must return 256 written bytes";
        ASSERT_EQ(memcmp(lv_targetBuf, lv_sampleLine, 0xFF), 0) << "Written data to mp3 file and read data doesn't match";
    }

    auto lv_read = fread(lv_targetBuf, sizeof(lv_targetBuf[0]), 0xFF, lv_file.get());
    ASSERT_EQ(lv_read, 0) << "Wrong size of mp3 file";

    auto lv_deletedFiles = std::filesystem::remove_all(lv_path);
    ASSERT_EQ(lv_deletedFiles, 1) << "Must be deleted one temporary mp3 file";
}

} // namespace folder2cpp::tests
