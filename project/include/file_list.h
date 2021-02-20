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

    static fileList get(std::string_view path);
};

} // namespace folder2cpp
