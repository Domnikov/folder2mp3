#pragma once
#include "../include/wav_file.h"
#include "../include/mp3_file.h"
#include "../include/lame_wrapper.h"

#include <filesystem>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <list>

namespace folder2cpp
{


class LameEncoder
{
    public:

    static void process(std::filesystem::path&& file)
    {
        try
        {
            WavFile lv_wavFile(file);

            if (!lv_wavFile.isCorrect())
            {
                static std::mutex lv_mutex;
                std::lock_guard<std::mutex> lock(lv_mutex);
                fprintf(stdout, "%s\n", lv_wavFile.getTextInfo().data());
                return;
            }

            file.replace_extension(".mp3");
            Mp3File lv_mp3File(file);
            {
                static std::mutex lv_mutex;
                std::lock_guard<std::mutex> lock(lv_mutex);
                fprintf(stdout, "Encoding %s --> %s\n", lv_wavFile.getPath().c_str(), lv_mp3File.getPath().c_str());
                fprintf(stdout, "%s\n", lv_wavFile.getTextInfo().data());
            }

            LameWrapper::encode(lv_wavFile, lv_mp3File);
        }
        catch(std::runtime_error& ex)
        {
            fprintf(stderr, "LameEncoder Error: %s\n", ex.what());
        }
    }

    using listType = std::vector<std::filesystem::path>;
};


template <typename Processor>
class ThreadPool final
{
    public:

        static void process(int threadNUmber, typename Processor::listType&& value)
        {
            ThreadPool pool;
            {
                std::lock_guard<std::mutex> lock(pool.m_mutex);
                std::move(value.cbegin(), value.cend(), std::back_inserter(pool.m_queue));
            }
            pool.run(threadNUmber);
        }

    private:

        ThreadPool() = default;

        ~ThreadPool()
        {
            for(auto& t : m_pool)
            {
                t.join();
            }
        }


        void run(int threadNUmber)
        {
            m_pool.reserve(threadNUmber);

            for(int i = 0; i < threadNUmber; ++i)
            {
                m_pool.push_back(std::thread([this, i]{
                    bool lv_done = false;

                    while (!lv_done)
                    {
                        typename Processor::listType::value_type element;
                        {
                            std::lock_guard<std::mutex> lock(m_mutex);
                            if(m_queue.size())
                            {
                                element = std::move(m_queue.front());
                                m_queue.pop_front();
                            }
                            else
                            {
                                lv_done = true;
                            }
                        }
                        if (!lv_done)
                        {
                            Processor::process(std::move(element));
                        }
                    }
                    }));
            }
        }


        std::vector<std::thread> m_pool;
        std::condition_variable m_cond;
        std::list<typename Processor::listType::value_type> m_queue;
        std::mutex m_mutex;

};


using EncoderPool = ThreadPool<LameEncoder>;


} // namespace folder2cpp
