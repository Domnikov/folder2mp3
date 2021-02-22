/**
 * \file wav_file.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contans WavFile class to provide convinient interface for wav file
 *
 */
#pragma once

#include <memory>
#include <filesystem>


/**
 * @brief Class WavFile to provide convinient interface for wav file
 *
 * Full RAII implementation class for wav file.
 * After creation object it read WAV file header and setup 'm_isCorrect' to true if file format is correct
 * getTextInfo function can be used for verbose mode. It implement lazy initialisation.
 * Until it will be called information will be not created.
 *
 */
class WavFile
{
    public:

        /**
         * \brief Class constructor
         *
         * Take wav file path and open it. If file is opened and ready to read then
         * wav header will be read. If header contains correct information and file format is matched then
         * isCorrect will be setup to true
         *
         * \param Path to wav file
         */
        WavFile(const std::filesystem::path& filePath);


        /**
         * \brief Get file information for verbose mode.
         *
         * Until first call WavFile will not generate text information.
         * After first time call test information will be stored and next call will return saved data.
         *
         * Attension!!! this function returns std::string_view with external buffer.
         * Result or this function must be used before WavFile object will be deleted.
         *
         * \return file information as std::string_view
         */
        std::string_view getTextInfo();


        /**
         * \brief Returns now many channels this file has
         */
        int getChannels() const noexcept {return m_header.channels;}


        /**
         * \brief Returns wav file frequency
         */
        int getFrequency() const noexcept {return m_header.frequency;}


        /**
         * \brief Returns how many bytes per one capture
         */
        int getBytesPerCapture() const noexcept {return m_header.bytesByCapture;}


        /**
         * \brief Returns true if wav file read to me read and wav format is correct
         */
        bool isCorrect() const noexcept {return m_isCorrect;}


        /**
         * \brief Get path to file
         */
        std::filesystem::path getPath() const noexcept {return m_path;}


        /**
         * \brief Read bytes from file to buffer
         *
         * This function must be inlined so it must be in header file
         *
         * \param Pointer to buffer
         * \param Buffer length
         */
        inline size_t read(short int* buf, size_t length)
        {
            return fread(buf, sizeof(buf[0]), length, m_file.get());
        }


        /**
         * \brief Copy of WavFile cannot be created
         */
        WavFile(const WavFile& ) = delete;


        /**
         * \brief WavFile cannot be copied
         */
        WavFile& operator=(const WavFile& ) = delete;


    private:


        /**
         * \brief WavFile header data structure
         */
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

        // Check wavHeader structure size
        static constexpr size_t wavHeaderSize = 44;
        static_assert(sizeof(wavHeader) == wavHeaderSize, "Wav header structure size incorrect");

        /**
         * @brief Custom deleter for file
         */
        struct FileDeleter
        {
            void operator()(FILE* file){fclose(file);}
        };

        std::filesystem::path m_path;
        wavHeader m_header;

        std::unique_ptr<FILE, FileDeleter> m_file;

        std::unique_ptr<char[]> m_textInfo;
        size_t m_infoLength = 0;

        bool m_isCorrect = false;
        long long m_durationMsec = 0;
};
