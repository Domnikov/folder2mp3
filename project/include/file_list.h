#pragma once

#include <string_view>
#include <filesystem>
#include <vector>

namespace folder2cpp
{

class FileList
{
public:
    using fileList = std::vector<std::filesystem::path>;

    FileList() = delete;

    static fileList get(std::string_view path, std::string_view extension)
    {
        fileList lv_fileList;
        for (const auto& file : std::filesystem::directory_iterator(path))
        {
            if(file.path().extension() == extension)
                lv_fileList.emplace_back(file);
        }

        return lv_fileList;
    }

};

} // namespace folder2cpp
