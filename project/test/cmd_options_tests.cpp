#include "../include/cmd_options.h"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

using namespace folder2cpp;


TEST(Cmd_options_Tests, Short_Arguments)
{
    const char* lv_cmdArg_short    [] = {"", "-v", "-t=10", "~"};

    const char** args = lv_cmdArg_short;
    auto size = sizeof(lv_cmdArg_short)/sizeof(lv_cmdArg_short[0]);
    auto lv_option = CmdOptions::getOptions(size, args);
    ASSERT_TRUE (lv_option.isVerbose()) << "-v command line argument doesn't work";
    ASSERT_FALSE(lv_option.isVersion()) << "--version command line option true by mistake";
    ASSERT_EQ   (lv_option.getThreadsNumb(), 10) << "-t=N command line option doesn't work";
    ASSERT_NE   (lv_option.getPath(), nullptr) << "PATH is null";
    ASSERT_EQ   (strcmp(lv_option.getPath(), args[size - 1]), 0) << "Wrong PATH";
}


TEST(Cmd_options_Tests, Long_Arguments)
{
    const char* lv_cmdArg_long     [] = {"", "--verbose", "--version", "--threads=5", "./project/res"};

    const char** args = lv_cmdArg_long;
    auto size = sizeof(lv_cmdArg_long)/sizeof(lv_cmdArg_long[0]);
    auto lv_option = CmdOptions::getOptions(size, args);
    ASSERT_TRUE (lv_option.isVerbose()) << "-v command line argument doesn't work";
    ASSERT_TRUE (lv_option.isVersion()) << "--version command line option true by mistake";
    ASSERT_EQ   (lv_option.getThreadsNumb(), 5) << "-t=N command line option doesn't work";
    ASSERT_NE   (lv_option.getPath(), nullptr) << "PATH is null";
    ASSERT_EQ   (strcmp(lv_option.getPath(), args[size - 1]), 0) << "Wrong PATH";
}


TEST(Cmd_options_Tests, Empty_Arguments)
{
    const char* lv_cmdArg_empty    [] = {""};

    try
    {
        const char** args = lv_cmdArg_empty;
        auto size = sizeof(lv_cmdArg_empty)/sizeof(lv_cmdArg_empty[0]);
        auto lv_option = CmdOptions::getOptions(size, args);
        FAIL() << "Command line without arguments must throw an exception";
    }
    catch (std::runtime_error& ex)
    {
        ASSERT_NE(strlen(ex.what()), 0) << "Exception text has null length";
    }
    catch (...)
    {
       FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception << std::endl;
    }
}



TEST(Cmd_options_Tests, Wrong_Argument)
{
    const char* lv_cmdArg_wrong    [] = {"", "-w", "~"};

    try
    {
        const char** args = lv_cmdArg_wrong;
        auto size = sizeof(lv_cmdArg_wrong)/sizeof(lv_cmdArg_wrong[0]);
        auto lv_option = CmdOptions::getOptions(size, args);
        FAIL() << "Command line with wrong arguments must throw an exception";
    }
    catch (std::runtime_error& ex)
    {
        ASSERT_NE(strlen(ex.what()), 0) << "Exception text has null length";
    }
    catch (...)
    {
       FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception << std::endl;
    }
}


TEST(Cmd_options_Tests, Wrong_threads_Arguments)
{
    const char* lv_cmdArg_wrong_thr[] = {"", "-t=X", "~"};

    try
    {
        const char** args = lv_cmdArg_wrong_thr;
        auto size = sizeof(lv_cmdArg_wrong_thr)/sizeof(lv_cmdArg_wrong_thr[0]);
        auto lv_option = CmdOptions::getOptions(size, args);
        FAIL() << "Command line with wrong number of threads must throw an exception";
    }
    catch (std::runtime_error& ex)
    {
        ASSERT_NE(strlen(ex.what()), 0) << "Exception text has null length";
    }
    catch (...)
    {
       FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception << std::endl;
    }
}

} // namespace folder2cpp::tests
