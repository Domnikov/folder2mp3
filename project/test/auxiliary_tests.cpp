#include "../include/cmd_options.h"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

TEST(Auxiliary_Tests, Gtest)
{
    ASSERT_EQ(1, 1) << "Gtest doesn't work correct";
}

TEST(Auxiliary_Tests, Command_line_Arguments)
{
    const char* lv_cmdArg_short    [] = {"", "-v", "-t=10", "~"};
    const char* lv_cmdArg_long     [] = {"", "--verbose", "--version", "--threads=5", "./project/res"};
    const char* lv_cmdArg_empty    [] = {""};
    const char* lv_cmdArg_wrong    [] = {"", "-w", "~"};
    const char* lv_cmdArg_wrong_thr[] = {"", "-t=X", "~"};

    const char** args = lv_cmdArg_short;
    int size = sizeof(lv_cmdArg_short)/sizeof(lv_cmdArg_short[0]);
    auto lv_option = CmdOptions::getOptions(size, args);
    ASSERT_TRUE (lv_option.isVerbose()) << "-v command line argument doesn't work";
    ASSERT_FALSE(lv_option.isVersion()) << "--version command line option true by mistake";
    ASSERT_EQ   (lv_option.getThreadsNumb(), 10) << "-t=N command line option doesn't work";
    ASSERT_NE   (lv_option.getPath(), nullptr) << "PATH is null";
    ASSERT_EQ   (strcmp(lv_option.getPath(), args[size - 1]), 0) << "Wrong PATH";

    args = lv_cmdArg_long;
    size = sizeof(lv_cmdArg_long)/sizeof(lv_cmdArg_long[0]);
    lv_option = CmdOptions::getOptions(size, args);
    ASSERT_TRUE (lv_option.isVerbose()) << "-v command line argument doesn't work";
    ASSERT_TRUE (lv_option.isVersion()) << "--version command line option true by mistake";
    ASSERT_EQ   (lv_option.getThreadsNumb(), 5) << "-t=N command line option doesn't work";
    ASSERT_NE   (lv_option.getPath(), nullptr) << "PATH is null";
    ASSERT_EQ   (strcmp(lv_option.getPath(), args[size - 1]), 0) << "Wrong PATH";

    try
    {
        args = lv_cmdArg_empty;
        size = sizeof(lv_cmdArg_empty)/sizeof(lv_cmdArg_empty[0]);
        lv_option = CmdOptions::getOptions(size, args);
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

    try
    {
        args = lv_cmdArg_wrong;
        size = sizeof(lv_cmdArg_wrong)/sizeof(lv_cmdArg_wrong[0]);
        lv_option = CmdOptions::getOptions(size, args);
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

    try
    {
        args = lv_cmdArg_wrong_thr;
        size = sizeof(lv_cmdArg_wrong_thr)/sizeof(lv_cmdArg_wrong_thr[0]);
        lv_option = CmdOptions::getOptions(size, args);
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

}
