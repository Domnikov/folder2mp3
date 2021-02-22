#include "../include/lame_wrapper.hpp"
#include <memory>
#include <functional>

using namespace folder2cpp;


/**
 * \brief Function to configure lame
 *
 * \param lame poiunter
 * \param Wav file
 * \return std::pair of wav buffer size and mp3 buffer size
 */
template <typename LAME>
auto setupLameHelper(LAME& lame, WavFile& wav)
{
    lame_set_num_channels(lame.get(), wav.getChannels());
    lame_set_mode(lame.get(), (wav.getChannels() == 1) ? MONO : STEREO);
    lame_set_in_samplerate(lame.get(), wav.getFrequency());
    lame_set_VBR(lame.get(), vbr_default);
    lame_init_params(lame.get());

    size_t lv_nsamples = 4096 / (wav.getBytesPerCapture() / wav.getChannels());
    size_t lv_wavBufSize = wav.getChannels()*lv_nsamples;
    size_t lv_mp3BufSize = 1.25 * lv_nsamples + 7200;// worst-case estimate from lame API

    return std::pair{lv_wavBufSize, lv_mp3BufSize};
}


/**
 * \brief Function to get encoder function
 *
 * Encoder function is different for STEREO and MONO.
 * To provide the same code can be used this function.
 *
 * \param lame poiunter
 * \param Wav buffer
 * \param Mp3 buffer
 * \param Channel 1 or 2
 * \param Mp3 buffer size
 * \return encoder function
 */
template <typename LAME, typename WAV_BUF, typename MP3_BUF>
std::function<int(int)> getEncodeFunctionHelper(LAME& lame, WAV_BUF& wavBuf, MP3_BUF& mp3Buf, int channels, size_t lv_mp3BufSize)
{
    if (channels == 1)
    {
        return [&lame, &wavBuf, &mp3Buf, lv_mp3BufSize](int read)
            {
                return lame_encode_buffer(lame.get(), wavBuf.get(), NULL, read, mp3Buf.get(), lv_mp3BufSize);
            };
    }
    else
    {
        return [&lame, &wavBuf, &mp3Buf, channels, lv_mp3BufSize](int read)
            {
                return lame_encode_buffer_interleaved(lame.get(), wavBuf.get(), read / channels, mp3Buf.get(), lv_mp3BufSize);
            };
    }
}


void LameWrapper::encode(WavFile& wav, Mp3File& mp3)
{
    auto deleter=[](lame_global_flags* lame){lame_close(lame);};
    std::unique_ptr<lame_global_flags, decltype(deleter)> lv_lame (lame_init(), deleter);

    if (!lv_lame)
    {
        throw std::runtime_error("Lame cannot be initialized!");
    }

    // Configue Lame and recievce buffers sizes
    auto [lv_wavBufSize, lv_mp3BufSize] = setupLameHelper(lv_lame, wav);

    // Create buffers
    auto lv_wavBuf = std::make_unique<short int    []>(lv_wavBufSize);
    auto lv_mp3Buf = std::make_unique<unsigned char[]>(lv_mp3BufSize);

    // Get encode function
    auto lameEncode = getEncodeFunctionHelper(lv_lame, lv_wavBuf, lv_mp3Buf, wav.getChannels(), lv_mp3BufSize);

    // Encoding Loop
    while (auto lv_read = wav.read(lv_wavBuf.get(), lv_wavBufSize))
    {
        auto lv_toWrite = lameEncode(lv_read);

        if (lv_toWrite < 0)
        {
            throw std::runtime_error("Lame encoding returned an error!");
        }
        else if (lv_toWrite && !mp3.write(lv_mp3Buf.get(), lv_toWrite))
        {
            throw std::runtime_error("Mp3 file cannot be written!");
        }
    }

    // Flush leftover data
    auto lv_toWrite = lame_encode_flush(lv_lame.get(), lv_mp3Buf.get(), lv_mp3BufSize);
    if (lv_toWrite < 0)
    {
        throw std::runtime_error("Lame encoding returned an error!");
    }
    else if (lv_toWrite && !mp3.write(lv_mp3Buf.get(), lv_toWrite))
    {
        throw std::runtime_error("Mp3 file cannot be written!");
    }
}
