/**
 * \file file_list.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contans FileList class to request file list from directory with specific file extension
 *
 */
#pragma once

#include <string_view>
#include <filesystem>
#include <vector>

namespace folder2cpp
{


/**
 * @brief Class FileList to request file list from directory with specific file extension
 *
 * Stateless class. An instance of FileList object cannot be created.
 * fileList is a nickname which container type is used
 *
 * Static function 'get' will do all work: get path, file extention and return file list
 *
 */
class FileList
{
    public:

        /**
         * \brief Nickmane with container data type
         */
        using fileList = std::vector<std::filesystem::path>;



        /**
         * \brief Static function which do all work: get path, file extention and return file list
         *
         * Functin simply copy all files into new container
         * Will throw an exception if dirrector if wrong
         *
         * \param Path for folder
         * \param File extension
         * \returns File list in container
         */
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

    private:
        /**
         * \brief Deleted constructor. Instance cannot be created
         */
        FileList() = delete;

};

} // namespace folder2cpp
