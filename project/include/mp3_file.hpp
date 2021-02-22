#pragma once

#include <memory>
#include <filesystem>

class Mp3File
{
public:
    Mp3File(const std::filesystem::path& filePath);

    bool isCorrect() const noexcept {return m_isCorrect;}

    std::filesystem::path getPath() const noexcept {return m_path;}

    size_t write(unsigned char* buf, size_t length)
    {
        return fwrite(buf, sizeof(buf[0]), length, m_file.get());
    }

    Mp3File(const Mp3File& ) = delete;
    Mp3File& operator=(const Mp3File& ) = delete;

private:

    struct FileDeleter
    {
        void operator()(FILE* file){fclose(file);}
    };

    std::filesystem::path m_path;
    std::unique_ptr<FILE, FileDeleter> m_file;
    bool m_isCorrect = false;
};
