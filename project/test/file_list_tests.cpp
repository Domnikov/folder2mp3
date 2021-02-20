#include "../include/file_list.h"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

using namespace folder2cpp;


TEST(File_List_Test, Project_Res_File_list)
{
    auto lv_path = "./project/res/";

    auto lv_files = FileList::get(lv_path);

    ASSERT_EQ   (lv_files.size(), 3) << "./build/project/res contains only 3 wav files";
}


TEST(File_List_Test, Wrong_path)
{
    auto lv_path = "./project/res/sample1.wav";

    try
    {
        FileList::get(lv_path);
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
