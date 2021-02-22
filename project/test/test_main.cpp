#include "cmd_options_tests.hpp"
#include "file_list_tests.hpp"
#include "encoder_pool_tests.hpp"
#include "wav_file_tests.hpp"
#include "mp3_file_tests.hpp"
#include "lame_wrapper_tests.hpp"


#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
