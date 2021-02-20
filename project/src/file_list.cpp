#include "../include/file_list.h"

using namespace folder2cpp;

constexpr auto WAV_EXTENSION = ".wav";

FileList::fileList FileList::get(std::string_view path)
{
    fileList lv_fileList;
    for (const auto& file : std::filesystem::directory_iterator(path))
    {
        if(file.path().extension() == WAV_EXTENSION)
            lv_fileList.emplace_back(file);
    }

    return lv_fileList;
}
