/**
 * \file file_list_tests.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contains unit tests for FileList class
 *
 */
#pragma once

#include "../include/file_list.hpp"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

using namespace folder2cpp;

constexpr auto WAV_EXTENSION = ".wav";


/**
 * \brief Unit test to check if test dirrectory can be read
 */
TEST(File_List_Test, Project_Res_File_list)
{
    auto lv_path = "./project/res/";

    auto lv_files = FileList::get(lv_path, WAV_EXTENSION);

    ASSERT_EQ   (lv_files.size(), 3) << "./build/project/res contains only 3 wav files";
}


/**
 * \brief Unit test to check if FileList will throw an exception if dirrectry is wrong
 */
TEST(File_List_Test, Wrong_path)
{
    auto lv_path = "./project/res/sample1.wav";

    try
    {
        FileList::get(lv_path, WAV_EXTENSION);
        FAIL() << "Getting file list from wrong path must throw an exception";
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
