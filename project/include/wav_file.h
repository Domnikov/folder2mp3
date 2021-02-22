#pragma once

#include <memory>
#include <filesystem>

class WavFile
{
public:
    WavFile(const std::filesystem::path& filePath);

    std::string_view getTextInfo();

    int getChannels(){return m_header.channels;}

    int getFrequency(){return m_header.frequency;}

    int getBytesPerCapture(){return m_header.bytesByCapture;}

    bool isCorrect(){return m_isCorrect;}

    std::filesystem::path getPath(){return m_path;}

    size_t read(short int* buf, size_t length)
    {
        return fread(buf, sizeof(buf[0]), length, m_file.get());
    }


    WavFile(const WavFile& ) = delete;
    WavFile& operator=(const WavFile& ) = delete;



private:
    struct wavHeader
    {
        char    id[4];           // should always contain "RIFF"
        int32_t totalLength;     // total file length minus 8
        char    waveFmt[8];      // should be "WAVEfmt "
        int32_t format;          // 16 for PCM format
        int16_t pcm;             // 1 for PCM format
        int16_t channels;        // channels
        int32_t frequency;       // sampling frequency
        int32_t bytesPerSecond;
        int16_t bytesByCapture;
        int16_t bitsPerSample;
        char    data[4];         // should always contain "data"
        int32_t bytesInData;
    } __attribute__((__packed__));
    static constexpr size_t wavHeaderSize = 44;
    static_assert(sizeof(wavHeader) == wavHeaderSize, "Wav header structure size incorrect");

    struct FileDeleter
    {
        void operator()(FILE* file){fclose(file);}
    };

    std::filesystem::path m_path;
    std::unique_ptr<FILE, FileDeleter> m_file;
    std::unique_ptr<char[]> m_textInfo;
    size_t m_infoLength = 0;
    wavHeader m_header;
    bool m_isCorrect = false;
    int m_durationSec = 0;
};
