/**
 * \file mp3_file.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contans Mp3File class to provide convinient interface for mp3 file
 *
 */
#pragma once

#include <memory>
#include <filesystem>


/**
 * @brief Class Mp3File to provide convinient interface for mp3 file
 *
 * Full RAII implementation class for mp3 file.
 * Class has three function:
 * isCorrect - for checking if file was opened and ready to write
 * getPath - return path to file
 * write - write buffer to file
 *
 */
class Mp3File
{
    public:

        /**
         * \brief Class constructor
         *
         * Take mp3 file path and open it. If file is opened and ready to write then isCorrect will be setup to true
         *
         * \param Path to mp3 file
         */
        Mp3File(const std::filesystem::path& filePath);


        /**
         * \brief Return true if file is opened and ready to write
         */
        bool isCorrect() const noexcept {return m_isCorrect;}


        /**
         * \brief Get path to file
         */
        std::filesystem::path getPath() const noexcept {return m_path;}


        /**
         * \brief Write buffer to file
         *
         * This function must be inlined so it must be in header file
         *
         * \param Pointer to buffer
         * \param Buffer length
         */
        inline size_t write(unsigned char* buf, size_t length)
        {
            return fwrite(buf, sizeof(buf[0]), length, m_file.get());
        }


        /**
         * \brief Copy of Mp3File cannot be created
         */
        Mp3File(const Mp3File& ) = delete;


        /**
         * \brief Mp3File cannot be copied
         */
        Mp3File& operator=(const Mp3File& ) = delete;

    private:

        /**
         * @brief Custom deleter for file
         */
        struct FileDeleter
        {
            void operator()(FILE* file){fclose(file);}
        };

        std::filesystem::path m_path;
        std::unique_ptr<FILE, FileDeleter> m_file;
        bool m_isCorrect = false;
};
