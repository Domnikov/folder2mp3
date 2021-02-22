/**
 * \file cmd_options_tests.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contains unit tests for CmdOptions class
 *
 */
#pragma once

#include "../include/cmd_options.hpp"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

using namespace folder2cpp;


/**
 * \brief Unit test to check if CmdOptions can read short version of arguments
 */
TEST(Cmd_options_Tests, Short_Arguments)
{
    const char* lv_cmdArg_short    [] = {"", "-v", "-t=10", "~"};

    const char** args = lv_cmdArg_short;
    auto size = sizeof(lv_cmdArg_short)/sizeof(lv_cmdArg_short[0]);
    auto lv_option = CmdOptions::getOptions(size, args);
    ASSERT_TRUE (lv_option.isVerbose()) << "-v command line argument doesn't work";
    ASSERT_FALSE(lv_option.isVersion()) << "--version command line option true by mistake";
    ASSERT_EQ   (lv_option.getThreadsNumb(), 10) << "-t=N command line option doesn't work";
    ASSERT_EQ   (lv_option.getPath(), args[size - 1]) << "Wrong PATH";
}


/**
 * \brief Unit test to check if CmdOptions can read long version of arguments
 */
TEST(Cmd_options_Tests, Long_Arguments)
{
    const char* lv_cmdArg_long     [] = {"", "--verbose", "--version", "--threads=5", "./project/res"};

    const char** args = lv_cmdArg_long;
    auto size = sizeof(lv_cmdArg_long)/sizeof(lv_cmdArg_long[0]);
    auto lv_option = CmdOptions::getOptions(size, args);
    ASSERT_TRUE (lv_option.isVerbose()) << "-v command line argument doesn't work";
    ASSERT_TRUE (lv_option.isVersion()) << "--version command line option true by mistake";
    ASSERT_EQ   (lv_option.getThreadsNumb(), 5) << "-t=N command line option doesn't work";
    ASSERT_EQ   (lv_option.getPath(), args[size - 1]) << "Wrong PATH";
}


/**
 * \brief Unit test to check if CmdOptions will throw an exception if there's no arguments
 */
TEST(Cmd_options_Tests, Empty_Arguments)
{
    const char* lv_cmdArg_empty    [] = {""};

    try
    {
        const char** args = lv_cmdArg_empty;
        auto size = sizeof(lv_cmdArg_empty)/sizeof(lv_cmdArg_empty[0]);
        CmdOptions::getOptions(size, args);
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


/**
 * \brief Unit test to check if CmdOptions will throw an exception if there's wrong argument
 */
TEST(Cmd_options_Tests, Wrong_Argument)
{
    const char* lv_cmdArg_wrong    [] = {"", "-w", "~"};

    try
    {
        const char** args = lv_cmdArg_wrong;
        auto size = sizeof(lv_cmdArg_wrong)/sizeof(lv_cmdArg_wrong[0]);
        CmdOptions::getOptions(size, args);
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


/**
 * \brief Unit test to check if CmdOptions will throw an exception if number of threads incorrect
 */
TEST(Cmd_options_Tests, Wrong_threads_Arguments)
{
    const char* lv_cmdArg_wrong_thr[] = {"", "-t=X", "~"};

    try
    {
        const char** args = lv_cmdArg_wrong_thr;
        auto size = sizeof(lv_cmdArg_wrong_thr)/sizeof(lv_cmdArg_wrong_thr[0]);
        CmdOptions::getOptions(size, args);
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
