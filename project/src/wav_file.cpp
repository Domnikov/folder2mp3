#include "../include/wav_file.h"

#include <cstring>

constexpr auto INFO_FORMAT =
R"(File name        = %s
Id               = %c%c%c%c
Size             = %d bytes
Wave format      = %c%c%c%c%c%c%c%c
Format           = %d
PCM              = %hd
Channels         = %hd
Frequency        = %d
Bytes per second = %d
Bytes by capture = %hd
Bits per sample  = %hd
Data             = %c%c%c%c
Bytes in data    = %d
Duration         = %d:%02d.%03d
)";


template <typename ... Args>
auto printfHelper(std::unique_ptr<char[]>& buf, const char* fmt, Args ... args)
{

    auto lv_length = snprintf(nullptr, 0, fmt, args ...) + 1;
    try
    {
        buf = std::make_unique<char[]>(lv_length);
        snprintf(buf.get(), lv_length, fmt, args ...);
    }
    catch(std::bad_alloc& ex)
    {
        fprintf(stderr, "Error: Memory for wav file information buffer cannot be allocated\n");
    }
    return lv_length;
}


WavFile::WavFile(const std::filesystem::path& filePath)
    :m_path(filePath)
{
    m_file.reset(fopen(filePath.c_str(), "rb"));

    if (m_file.get())
    {
         auto read = fread(&m_header, 1, wavHeaderSize, m_file.get());
         if (read == wavHeaderSize)
         {
             m_isCorrect = (0 == strncmp(m_header.id, "RIFF", 4));

             if (m_isCorrect)
             {
                 m_durationSec = 1000 * m_header.bytesInData / m_header.bytesPerSecond;
             }
         }
    }
}


std::string_view WavFile::getTextInfo()
{
    if (!m_textInfo)
    {
        if (m_isCorrect)
        {
            m_infoLength = printfHelper(m_textInfo, INFO_FORMAT,
                    m_path.c_str(),
                    m_header.id[0],m_header.id[1],m_header.id[2],m_header.id[3],
                    m_header.totalLength,
                    m_header.waveFmt[0],m_header.waveFmt[1],m_header.waveFmt[2],m_header.waveFmt[3],m_header.waveFmt[4],m_header.waveFmt[5],m_header.waveFmt[6],m_header.waveFmt[7],
                    m_header.format,
                    m_header.pcm,
                    m_header.channels,
                    m_header.frequency,
                    m_header.bytesPerSecond,
                    m_header.bytesByCapture,
                    m_header.bitsPerSample,
                    m_header.data[0],m_header.data[1],m_header.data[2],m_header.data[3],
                    m_header.bytesInData,
                    m_durationSec/1000/60,
                    (m_durationSec/1000)%60,
                    m_durationSec%1000);
        }
        else
        {
            m_infoLength = printfHelper(m_textInfo, "Wav file currepted: %s\n", m_path.c_str());
        }
    }

    return std::string_view(m_textInfo.get(), m_infoLength);
}
