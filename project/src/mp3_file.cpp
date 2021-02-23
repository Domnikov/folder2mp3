#include "../include/mp3_file.hpp"

Mp3File::Mp3File(const std::filesystem::path& filePath)
    :m_path(filePath)
{
    m_file.reset(fopen(filePath.string().c_str(), "wb"));

    if (m_file.get())
    {
         m_isCorrect = true;
    }
}
